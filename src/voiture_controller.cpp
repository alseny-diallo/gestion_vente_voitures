#include "voiture_controller.h"
#include "crow.h"
#include <vector>

crow::response getAllVoitures() {
    auto con = connectToDatabase();
    if (!con) {
        return crow::response(500, crow::json::wvalue{{"error", "Database connection failed."}}.dump());
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

        return crow::response(200, crow::json::wvalue(list_voitures).dump());

    } catch (sql::SQLException& e) {
        return crow::response(500, crow::json::wvalue{{"error", "Database error: " + std::string(e.what())}}.dump());
    }
}
