#pragma once
#include <QSqlDatabase>
#include <memory>

class DataBase {
public:
    DataBase();
private:
    QSqlDatabase db_;
};