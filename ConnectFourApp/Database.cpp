#include "Database.h"

#include <QSqlQuery>
#include <QVariant>
#include <sstream>

DataBase::DataBase()
: db_(QSqlDatabase::addDatabase("QSQLITE")){
    db_.setDatabaseName("gamedata.db3");
    if (!db_.open()) {
        throw std::logic_error("failed to open database");
    }
    
    QSqlQuery query;
    query.prepare("CREATE TABLE IF NOT EXISTS games (gamerecord TEXT PRIMARY KEY, yellow TEXT, red TEXT, winner INT);");
    query.exec();
}

void DataBase::AddGameRecord(const tlCF::GameResult& result) {
    std::stringstream game;
    for (int i=0; i<42; ++i) {
        if (result.moves[i]==0xFF) {
            break;
        }
        game << static_cast<int>(result.moves[i]);
    }
    QString gamerecord = game.str().c_str();
    QString yellow = result.yellow.c_str();
    QString red = result.red.c_str();
    int winnerIndex = static_cast<int>(result.result);
    QSqlQuery query;
    query.prepare("INSERT INTO games (gamerecord, yellow, red, winner) VALUES (:gamerecord, :yellow, :red, :winner);");
    query.bindValue(":gamerecord", gamerecord);
    query.bindValue(":yellow", yellow);
    query.bindValue(":red", red);
    query.bindValue(":winner", winnerIndex);
    auto exec_result = query.exec();
}