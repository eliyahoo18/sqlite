/** ✨ **/
#include <utility>

#include "Sqlite.h"


fe::SqliteRow &fe::SqliteRow::defineValue(std::string name, int value) {
    return defineValue(std::move(name), std::to_string(value), SqliteType::Integer);
}

fe::SqliteRow &fe::SqliteRow::defineValue(std::string name, double value) {
    return defineValue(std::move(name), std::to_string(value), SqliteType::Float);
}

fe::SqliteRow &fe::SqliteRow::defineValue(std::string name, const unsigned char *value, SqliteType type) {
    return defineValue(std::move(name), reinterpret_cast<const char *>(value), type);
}

fe::SqliteRow &fe::SqliteRow::defineValue(std::string name, std::string value, SqliteType type) {
    _columns[std::move(name)] = std::move(value);
    return *this;
}

fe::SqliteRow::Column fe::SqliteRow::operator[](const std::string &name) const {
    if (_columns.find(name) == _columns.end())
        throw SqliteSyntaxException("no such column '" + name + "'");

    return {name, _columns.at(name)};
}
