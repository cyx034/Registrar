module;

#include <pqxx/pqxx>

export module registrar:broker.teachersecretarybroker;
import :broker.registrarbroker;
import std;

using std::string;
using std::cerr;
using std::endl;
using std::unique_ptr;

export class TeacherSecretaryBroker : public RegistrarBroker
{
public:
    using RegistrarBroker::RegistrarBroker;

    std::unique_ptr<TeacherSecretary> findTeacherSecretaryById(const std::string& id);
    void initialize();

private:
    vector<std::unique_ptr<TeacherSecretary>> _teachersecretary;
    unique_ptr<TeacherSecretary> findTeacherSecretaryByIdLocal(const string &id);
    unique_ptr<TeacherSecretary> findTeacherSecretaryByIdDB(const string& id);
};

void TeacherSecretaryBroker::initialize()
{
    if (!status) {
        cerr << "数据库未连接" << endl;
        return;
    }
    pqxx::read_transaction t(*dbConnection);
    pqxx::result res = rtx.exec("SELECT tsno,tsname,tsacademy FROM teachersecretary LIMIT 5;"); //只读入前5行进入缓存
    rtx.commit();
    _teachersecretary.clear();
    for(const auto& row : res) {
        _teachersecretary.push_back(std::make_unique<TeacherSecretary>(
            res[0]["tsno"].as<string>(),
            res[0]["tsname"].as<string>(),
            res[0]["tsacademy"].as<string>()));
    }
}

unique_ptr<TeacherSecretary> TeacherSecretaryBroker::findTeacherSecretaryById(const std::string& id)
{
    if(auto local = findTeacherSecretaryByIdLocal(id))  //先从本地缓存中找
        return local;
    return findTeacherSecretaryByIdDB(id); //没有就去数据库中找
}

unique_ptr<TeacherSecretary> TeacherSecretaryBroker::findTeacherSecretaryByIdLocal(const string &id)
{
    for(auto& teachersecretary : _teachersecretary){
        if(teachersecretary->hasId(id))
            return teachersecretary;
    }
    return nullptr;
}

unique_ptr<TeacherSecretary> TeacherSecretaryBroker::findTeacherSecretaryByIdDB(const string& id)
{
    if (!status) {
        cerr << "数据库未连接" << endl;
        return nullptr;
    }
    try {
        pqxx::work t(*dbConnection);
        auto res = t.exec_params("SELECT tno,tname,tacademy FROM teachersecretary WHERE tsno = $1;",id);
        t.commit();
        if (res.empty()) {
            std::cout << "未找到教学秘书ID：" << id << endl;
            return nullptr;
        }
        auto teachersecretary = std::make_unique<TeacherSecretary>(
            res[0]["tsno"].as<string>(),
            res[0]["tsname"].as<string>(),
            res[0]["tsacademy"].as<string>());
        _teachersecretary.pushback(std::move(teachersecretary));   //把用到的存入缓存区
    } catch (const std::exception& e) {
        cerr << "查询失败：" << e.what() << endl;
        return nullptr;
    }
}
