#define CROW_MAIN
#include "crow.h"
#include "src/database.h" 
#include "src/voiture_controller.h"

int main() {
    crow::SimpleApp app;

    // routes
    CROW_ROUTE(app, "/voitures")([&]() {
        auto result = getAllVoitures();
        return result;
    });

    CROW_ROUTE(app, "/")([]() {
        return "Hello world";
    });

    app.bindaddr("127.0.0.1").port(18080).multithreaded().run();

    return 0;
}
