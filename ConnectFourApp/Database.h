#pragma once
#include <QSqlDatabase>
#include <memory>

#include "ConnectFour.hpp"

class DataBase {
public:
    DataBase();
    void AddGameRecord(const tlCF::GameResult& result);
private:
    QSqlDatabase db_;
};