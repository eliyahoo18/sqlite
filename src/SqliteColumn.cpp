/** ✨ **/
#include "SqliteColumn.h"


fe::SqliteColumn::SqliteColumn(std::string name, std::string value, SqliteType type) : _name(std::move(name)),
                                                                                       _value(std::move(value)),
                                                                                       _type(type) {}

const std::string &fe::SqliteColumn::name() const {
    return _name;
}

const std::string &fe::SqliteColumn::value() const {
    return _value;
}

int fe::SqliteColumn::valueAsInt() const {
    return std::stoi(_value);
}

double fe::SqliteColumn::valueAsDouble() const {
    return std::stod(_value);
}

bool fe::SqliteColumn::isDigit(const std::string &str) {
    auto it = str.begin();
    while (std::isdigit(*it) && it++ != str.end());
    return !str.empty() && it == str.end();
}
