/** ✨ **/
#pragma once

#include <string>
#include <vector>
#include <sqlite3.h>
#include <sstream>
#include <map>


namespace fe {

/*****|  exceptions  |*****/
class SqliteException : public std::runtime_error {
public:
    explicit SqliteException(const std::string &msg) : runtime_error(msg) {}
};


class SqliteConstraintException : public SqliteException {
public:
    explicit SqliteConstraintException(const std::string &msg) : SqliteException(msg) {}
};

class SqliteSyntaxException : public SqliteException {
public:
    explicit SqliteSyntaxException(const std::string &msg) : SqliteException(msg) {}
};

/*****|  Sqlite Columns  |*****/
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
    SqliteColumn(std::string name, std::string value);

    [[nodiscard]] const std::string &name() const;

    [[nodiscard]] const std::string &value() const;

    [[nodiscard]] int valueAsInt() const;

    [[nodiscard]] double valueAsDouble() const;

    static bool isDigit(const std::string &str);

private:
    std::string _name;
    std::string _value;
};

/**
 * Holder for a sqlite row.
 */
class SqliteRow {
public:
    using Column = SqliteColumn;

    SqliteRow&  defineValue(std::string name, int value);
    SqliteRow&  defineValue(std::string name, double value);
    SqliteRow&  defineValue(std::string name, const unsigned char *value, SqliteType type);
    SqliteRow&  defineValue(std::string name, std::string value, SqliteType type);

    Column      operator[](const std::string &name) const;

    auto        begin() const  { return _columns.begin(); }
    auto        end() const    { return _columns.end(); }

protected:
    // The search is by the column name - so it's smarter to do so and not
    // by vector of 'Column' objects.
    std::map<std::string, std::string> _columns;
};

/**
 * Warping the sqlite standards library with cpp options
 */
class Sqlite {
public:
    using SqliteId = sqlite3_int64;
    using Row      = SqliteRow;
    using Table    = std::vector<Row>;

    explicit  Sqlite(const std::string &dbName);
             ~Sqlite();

    Table          exec(const std::string &query);
    template<typename... Arg>
    Table          exec(const std::string &query, Arg... arg);

    sqlite3_int64  lastInsertId();
private:

    /**
     * Adapter between template and the sqlite3 formatting
     */
    class Formatter {
    public:
        template<typename T, typename... Args>
        void                       format(T type, Args... args);
        std::vector<std::string>&  args();

    private:
        std::vector<std::string>   _args;

    };

    sqlite3 *_db;
    /**
     * throw runtime exception with the sqlite3 massage
     * @param pStmt 'sqlite3_stmt' to clean
     */
    void        _throw_exception(sqlite3_stmt *pStmt, int sqliteCode);
    Table       _exec(const std::string &query, const std::vector<std::string> &params);

};

template<typename T, typename... Args>
void fe::Sqlite::Formatter::format(T type, Args... args) {
    std::stringstream in;
    in << type;
    _args.push_back(in.str());

    if constexpr (sizeof...(args) > 0) {
        format(args...);
    }
}


template<typename... Arg>
fe::Sqlite::Table fe::Sqlite::exec(const std::string &query, Arg... arg) {
    // format the args to vector of strings
    Formatter formatter;
    formatter.format(arg...);

    // and pass it to the exec function to compile the query
    return _exec(query, formatter.args());
}


}