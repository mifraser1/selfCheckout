#include "crow_all.h"
#include "Server.h"
#include "Transaction.h"
#include "Ledger.h"
#include "MockScale.h"
#include <fstream>
#include <sstream>
#include <string>

static std::string readFile(const std::string &path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        return "<h1>Error: Could not open " + path + "</h1>";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// need to pass catalog
void runServer(Transaction &tx, Ledger &ledger, MockScale &scale )
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([]{ return readFile(std::string(FRONTEND_DIR) + "/index.html"); });

    //API to Scan
    CROW_ROUTE(app, "/api/scan").methods("POST"_method)([&tx](const crow::request& req){
        auto body = crow::json::load(req.body);
        int productId = body["id"].i();

        crow::json::wvalue result;
        result["success"] = true;
        result["total"] = tx.getTotal();
        return result;
    });

    // Total Endpoint
    CROW_ROUTE(app, "/api/total")([&tx]{
        crow::json::wvalue result;
        result["subtotal"] = tx.getSubtotal();
        result["tax"]      = tx.getTaxTotal();
        result["total"]    = tx.getTotal();
        return result; });

    // Start the server
    app.port(8080).multithreaded().run();
}
