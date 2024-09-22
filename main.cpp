#define CROW_MAIN
#include "crow.h"
#include "src/database.h" 
#include "src/voiture_controller.h"

int main() {
    crow::SimpleApp app;

    // Définir les routes
    CROW_ROUTE(app, "/voitures")([&]() {
        auto result = getAllVoitures(); 
        // Envelopper le résultat dans une réponse Crow
        return crow::response(200, result.dump()); // .dump() pour convertir en chaîne JSON
    });

    CROW_ROUTE(app, "/")([]() {
        return "Hello world";
    });

    // Configurer l'adresse et le port
    app.bindaddr("127.0.0.1").port(18080).multithreaded().run();

    return 0; // Retourner 0 pour indiquer que le programme s'est terminé correctement
}
