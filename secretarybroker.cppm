module;

#include <pqxx/pqxx>
#include <pqxx/zview>
#include <pqxx/params>
export module registrar:broker.teachersecretarybroker;
import :broker.registrarbroker;
import :domain.teacherSecretary;
import std;

using std::string;
using std::cerr;
using std::endl;
using std::shared_ptr;
using std::vector;

export class TeacherSecretaryBroker : public RegistrarBroker
{
public:
    using RegistrarBroker::RegistrarBroker;

    std::shared_ptr<class TeacherSecretary> findTeacherSecretaryById(const std::string& id);
    void initialize();

private:
    vector<std::shared_ptr<class TeacherSecretary>> _teachersecretary;
    shared_ptr<class TeacherSecretary> findTeacherSecretaryByIdLocal(const string &id);
    shared_ptr<class TeacherSecretary> findTeacherSecretaryByIdDB(const string& id);
};

void TeacherSecretaryBroker::initialize()
{
    if (!status) {
        cerr << "数据库未连接" << endl;
        return;
    }
    pqxx::read_transaction t(*dbConnection);
    pqxx::result res = t.exec("SELECT tsno,tsname,tsacademy FROM tsecretary LIMIT 5"); //只读入前5行进入缓存
    t.commit();
    _teachersecretary.clear();
    for(const auto& row : res) {
        _teachersecretary.push_back(std::make_shared<TeacherSecretary>(
            res[0]["tsno"].as<string>(),
            res[0]["tsname"].as<string>(),
            res[0]["tsacademy"].as<string>()));
    }
}

shared_ptr<TeacherSecretary> TeacherSecretaryBroker::findTeacherSecretaryById(const std::string& id)
{
    if(auto local = findTeacherSecretaryByIdLocal(id))  //先从本地缓存中找
        return local;
    return findTeacherSecretaryByIdDB(id); //没有就去数据库中找
}

shared_ptr<TeacherSecretary> TeacherSecretaryBroker::findTeacherSecretaryByIdLocal(const string &id)
{
    for(auto& teachersecretary : _teachersecretary){
        if(teachersecretary->hasId(id))
            return teachersecretary;
    }
    return nullptr;
}

shared_ptr<TeacherSecretary> TeacherSecretaryBroker::findTeacherSecretaryByIdDB(const string& id)
{
    if (!status) {
        cerr << "数据库未连接" << endl;
        return nullptr;
    }
    try {
        pqxx::work t(*dbConnection);
        pqxx::result res = t.exec(pqxx::zview{"SELECT tsno,tname,tacademy FROM tsecretary WHERE tsno = $1"},pqxx::params{id});
        t.commit();
        if (res.empty()) {
            std::cout << "未找到教学秘书ID：" << id << endl;
            return nullptr;
        }
        auto teachersecretary = std::make_shared<TeacherSecretary>(
            res[0]["tsno"].as<string>(),
            res[0]["tsname"].as<string>(),
            res[0]["tsacademy"].as<string>());
        _teachersecretary.push_back(std::move(teachersecretary));   //把用到的存入缓存区
        return teachersecretary;
    } catch (const std::exception& e) {
        cerr << "查询失败：" << e.what() << endl;
        return nullptr;
    }
}
