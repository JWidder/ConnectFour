#include "Database.h"

DataBase::DataBase()
: db_(QSqlDatabase::addDatabase("QSQLITE")){
    db_.setDatabaseName("gamedata.db3");
    if (!db_.open()) {
        throw std::logic_error("failed to open database");
    }
}