/* ✨ */
#include <iostream>
#include <iomanip>
#include "../src/Sqlite.h"

int main() {

    fe::Sqlite db("test.db");

    db.exec("CREATE TABLE IF NOT EXISTS Users (\n"
            "    UserID INTEGER PRIMARY KEY AUTOINCREMENT,\n"
            "    FirstName TEXT NOT NULL,\n"
            "    LastName TEXT NOT NULL,\n"
            "    Age INTEGER\n"
            ");");

    // db.exec("INSERT INTO Users (FirstName, LastName, Age) VALUES (?, ?, ?);", "John", "Doe", 30);
    // db.exec("INSERT INTO Users (FirstName, LastName, Age) VALUES (?, ?, ?);", "Jane", "Smith", 25);
    fe::Sqlite::Table table = db.exec("SELECT * FROM Users;");
    if (table.empty()) {
        std::cout << "table is empty" << std::endl;
        return 0;
    }

    for (auto& col : *table.begin())
        std::cout << "|_" << std::setw(15) << std::setfill('_') << std::left  << col.first;
    std::cout << "|" << std::endl;

    for (auto& row : table) {
        for (auto& col : row) {
            std::cout << "| " << std::setw(15) << std::setfill(' ')<< std::left  << col.second;
        }
        std::cout << "|" << std::endl;
    }


    std::cout << "Hello World" << std::endl;
    return 0;
}