module;

#include <pqxx/pqxx>

module registrar:broker.enrollmentbroker;

RegistrarBroker::RegistrarBroker()
    :status(false),dbConnection(nullptr)
{
    connect();
}

RegistrarBroker::~RegistrarBroker()
{
    if(status){
        dbConnection->close();
    }
}

void RegistrarBroker::connect()
{
    try {
        std::string connstr = "host=localhost port=5432 dbname=db user=postgres";
        dbConnection = std::make_shared<pqxx::connection>(connstr);

        if (dbConnection->is_open()) {
                status = true;
                std::cout << "Connected to database: " << dbConnection->dbname() << std::endl;
        }
    } catch (const std::exception &e) {
        status = false;
        std::cerr << "Connection failed: " << e.what() << std::endl;
    }
}
