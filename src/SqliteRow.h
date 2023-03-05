/** ✨ **/
#pragma once

#include <string>
#include <map>
#include "SqliteColumn.h"


namespace fe {

/**
 * Holder for a sqlite row.
 */
class SqliteRow {
public:
    using Column = SqliteColumn;

    SqliteRow &defineValue(std::string name, int value);

    SqliteRow &defineValue(std::string name, double value);

    SqliteRow &defineValue(std::string name, const unsigned char *value, SqliteType type);

    SqliteRow &defineValue(std::string name, std::string value, SqliteType type);

    Column operator[](const std::string &name) const;

protected:
    // The search is by the column name - so it's smarter to do so and not
    // by vector of 'Column' objects.
    std::map<std::string, std::pair<std::string, SqliteType>> _columns;
};

}