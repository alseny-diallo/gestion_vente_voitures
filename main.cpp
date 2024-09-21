#define CROW_MAIN 
#include "crow.h"
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <vector>

using namespace std;

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/voitures")([&]() {
        try {
            // Initialiser le driver et la connexion MySQL
            sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
            unique_ptr<sql::Connection> con(driver->connect("tcp://localhost:3306", "root", "password"));
            cout << "Successfully connected to MySQL." << endl;
            con->setSchema("gestionVenteVoiture");

            unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT * FROM voiture"));
            unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

            // Utiliser un tableau standard pour stocker les résultats
            vector<crow::json::wvalue> list_voitures;

            while (res->next()) {
                crow::json::wvalue voiture;
                voiture["id"] = res->getInt("idVoiture");
                voiture["marque"] = res->getString("marque");
                voiture["model"] = res->getString("model");

                // Ajouter chaque voiture au tableau
                list_voitures.push_back(voiture);
            }

            // Mettre le tableau dans le résultat final
            crow::json::wvalue result = move(list_voitures);
            return crow::response(200, result);
           
        } catch (sql::SQLException& e) {
            cout << "Database error: " << e.what() << endl;
            return crow::response(500, "Database error: " + std::string(e.what()));
        }

        // Ajouter un return statement ici pour éviter le warning
        return crow::response(500, "Internal server error");
    });

    CROW_ROUTE(app, "/")([](){
        return "Hello world";
    });
    
    app.bindaddr("127.0.0.1").port(18080).multithreaded().run();
}
