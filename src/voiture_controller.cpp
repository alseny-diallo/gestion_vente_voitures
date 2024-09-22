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
            voiture["prix"] = res->getInt("prix");

            list_voitures.push_back(voiture);
        }

        return crow::response(200, crow::json::wvalue(list_voitures).dump());

    } catch (sql::SQLException& e) {
        return crow::response(500, crow::json::wvalue{{"error", "Database error: " + std::string(e.what())}}.dump());
    }
}

crow::response getVoitureById(int id) {
    auto con = connectToDatabase();
    if (!con) {
        return crow::response(500, crow::json::wvalue{{"error", "Database connection failed."}}.dump());
    }

    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT * FROM voitures WHERE id = ?"));
        pstmt->setInt(1, id); // Lier l'ID
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        if (res->next()) {
            crow::json::wvalue voiture;
            voiture["id"] = res->getInt("id");
            voiture["marque"] = res->getString("marque");
            voiture["model"] = res->getString("model");
            voiture["annee"] = res->getString("annee");
            voiture["kilométrage"] = res->getString("kilométrage");
            voiture["prix"] = res->getInt("prix");
            voiture["description"] = res->getString("description");

            return crow::response(200, voiture.dump());
        } else {
            return crow::response(404, crow::json::wvalue{{"error", "Voiture not found."}}.dump());
        }

    } catch (sql::SQLException& e) {
        return crow::response(500, crow::json::wvalue{{"error", "Database error: " + std::string(e.what())}}.dump());
    }
}
