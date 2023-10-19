cmake_minimum_required(VERSION 3.24)
project(sqlite)

set(CMAKE_CXX_STANDARD 17)


#add_library(sqlite
#
##        src/Sqlite.cpp
##        src/SqliteExceptions.h
##        src/SqliteColumn.cpp
##        src/SqliteColumn.h
##        src/SqliteRow.cpp
##        src/SqliteRow.h
#        test/main.cpp
#        src/a.cpp
#        src/a.h)


add_executable(sqlite test/main.cpp
        src/Sqlite.cpp
        src/Sqlite.h
        src/SqliteColumn.cpp
        src/SqliteRow.cpp
)

target_link_libraries(sqlite sqlite3)
