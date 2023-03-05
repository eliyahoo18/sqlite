/** ✨ **/
#pragma once
#include <string>

namespace fe {


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

}
