cmake_minimum_required(VERSION 3.24)
project(sqlite)

set(CMAKE_CXX_STANDARD 17)

add_library(sqlite src/Sqlite.cpp src/SqliteExceptions.h src/SqliteColumn.cpp src/SqliteColumn.h src/SqliteRow.cpp src/SqliteRow.h)

target_link_libraries(sqlite sqlite3)
