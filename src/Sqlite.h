/** ✨ **/
#pragma once

#include <string>
#include <vector>
#include <sqlite3.h>
#include "SqliteRow.h"


namespace fe {

/**
 * Warping the sqlite standards library with cpp options
 */
class Sqlite {
public:
    using SqliteId = sqlite3_int64;
    using Row = SqliteRow;
    using Table = std::vector<Row>;

    explicit Sqlite(const std::string &dbName);

    ~Sqlite();

    Table exec(const std::string &query);
    Table exec(const std::string &query, const std::vector<std::string> &params);
    sqlite3_int64 readLastInsertId();

private:
    sqlite3 *_db;

    /**
     * throw runtime exception with the sqlite3 massage
     * @param pStmt 'sqlite3_stmt' to clean
     */
    void _throw_exception(sqlite3_stmt *pStmt, int sqliteCode);
};

}
