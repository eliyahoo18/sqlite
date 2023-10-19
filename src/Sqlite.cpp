/** ✨ **/
#include "Sqlite.h"


fe::Sqlite::Sqlite(const std::string &dbName) {
    if (sqlite3_open(dbName.c_str(), &_db) != SQLITE_OK) {
        // the memory of 'err' freed by sqlite3 functions
        const char *err = sqlite3_errmsg(_db);
        throw SqliteException(err);
    }
}

fe::Sqlite::~Sqlite() {
    sqlite3_close(_db);
}

fe::Sqlite::Table fe::Sqlite::exec(const std::string &query) {
    return _exec(query, {});
}

fe::Sqlite::Table fe::Sqlite::_exec(const std::string &query, const std::vector<std::string> &params) {
    sqlite3_stmt *ppStmt;

    // prepare the sqlite query
    if (sqlite3_prepare_v2(_db, query.c_str(), query.size(), &ppStmt, nullptr) != SQLITE_OK)
        _throw_exception(nullptr, SQLITE_ERROR);

    // bind the value to the variables
    int paramIndex = 1;
    for (const auto& param : params) {
        if (sqlite3_bind_text(ppStmt, paramIndex++, param.c_str(), param.size(), SQLITE_STATIC) != SQLITE_OK)
            _throw_exception(ppStmt, SQLITE_ERROR);
    }

    // run the sqlite query and parse the results
    Table results;
    int res;
    while ((res = sqlite3_step(ppStmt)) == SQLITE_ROW) {
        // get the count of the columns
        int columnsCount = sqlite3_column_count(ppStmt);
        if (columnsCount == 0)
            continue;

        SqliteRow row;
        for (int i = 0; i < columnsCount; i++) {
            // gets the column name, column type and column value
            const char *name = sqlite3_column_name(ppStmt, i);
            auto type = (SqliteType) sqlite3_column_type(ppStmt, i);
            const unsigned char *value = sqlite3_column_text(ppStmt, i);
            if (!name || !value)
                _throw_exception(ppStmt, res);

            // inserts the new column
            row.defineValue(name, value, type);
        }

        // inserts the new row
        results.push_back(std::move(row));
    }

    if (res != SQLITE_DONE)
        _throw_exception(ppStmt, res);

    // clean up the prepared statement
    sqlite3_finalize(ppStmt);

    return results;
}

sqlite3_int64 fe::Sqlite::lastInsertId() {
    return sqlite3_last_insert_rowid(_db);
}

std::vector<std::string>& fe::Sqlite::Formatter::args() {
    return _args;
}

void fe::Sqlite::_throw_exception(sqlite3_stmt *pStmt, int sqliteCode) {
    // destroy the prepared statement
    if (pStmt)
        sqlite3_finalize(pStmt);

    // the memory of 'err' freed by sqlite3 functions
    std::string err = sqlite3_errmsg(_db);

    if (sqliteCode == SQLITE_CONSTRAINT)
        throw SqliteConstraintException(err);

    if (err.find("syntax") != std::string::npos)
        throw SqliteSyntaxException(err);

    throw SqliteException(err);
}



