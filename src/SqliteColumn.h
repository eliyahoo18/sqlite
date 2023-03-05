/** ✨ **/
#pragma once
#include <string>
#include <sqlite3.h>


namespace fe {


enum SqliteType {
    Null = SQLITE_NULL,
    Integer = SQLITE_INTEGER,
    Float = SQLITE_FLOAT,
    Text = SQLITE_TEXT,
    Blob = SQLITE_BLOB
};


/**
* Holder for a sqlite column.
*/
class SqliteColumn {
public:
    SqliteColumn(std::string name, std::string value, SqliteType type);

    [[nodiscard]] const std::string &name() const;

    [[nodiscard]] const std::string &value() const;

    [[nodiscard]] int valueAsInt() const;

    [[nodiscard]] double valueAsDouble() const;

    static bool isDigit(const std::string &str);

private:
    std::string _name;
    std::string _value;
    SqliteType _type;
};

}
