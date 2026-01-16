module;

#include <pqxx/pqxx>

export module registrar:broker.registrarbroker;


import std;

using std::string;

export class RegistrarBroker
{
public:
    RegistrarBroker();
    virtual ~RegistrarBroker();
    void connect();
protected:
    std::shared_ptr<pqxx::connection> dbConnection;//conn("host=localhost port=5432 dbname=db user=postgres");
    bool status;
};


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
        dbConnection = std::make_unique<pqxx::connection>(connstr);

        if (dbConnection->is_open()) {
                status = true;
                std::cout << "Connected to database: " << dbConnection->dbname() << std::endl;
        }
    } catch (const std::exception &e) {
        status = false;
        std::cerr << "Connection failed: " << e.what() << std::endl;
    }
}
