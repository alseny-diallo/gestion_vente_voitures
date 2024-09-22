
#include "voiture_controller.h"
#include <vector>

crow::json::wvalue getAllVoitures() { // Assure-toi que le nom de la fonction est le même
    auto con = connectToDatabase();
    if (!con) {
        return crow::json::wvalue{{"error", "Database connection failed."}};
    }

    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT * FROM voitures"));
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        std::vector<crow::json::wvalue> list_voitures;

        while (res->next()) {
            crow::json::wvalue voiture;
            voiture["id"] = res->getInt("id");
            voiture["marque"] = res->getString("marque");
            voiture["model"] = res->getString("model");

            list_voitures.push_back(voiture);
        }

        crow::json::wvalue result = move(list_voitures);
        return result; // Retourne la liste des voitures

    } catch (sql::SQLException& e) {
        return crow::json::wvalue{{"error", "Database error: " + std::string(e.what())}};
    }
}

