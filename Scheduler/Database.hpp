#ifndef Scheduler_Database_hpp
#define Scheduler_Database_hpp

#include <iostream>
#include <sqlite_modern_cpp/hdr/sqlite_modern_cpp.h>
#include <string>
#include <sstream>

namespace Scheduler
{

// A database connection
class Database
{
    private:

        // The filename of the database
        static constexpr auto filename = ".db/scheduler.db";

        // SqliteModernCpp handle
        sqlite::database db;

    public:

        // Open database, and create tables etc. if necessary
        Database();

        // List existing categories on stdout.
        void list_categories();

        // Add a category by asking the user.
        bool add_category();

};

/* Implementations follow */

Database::Database()
:db(filename)
{
    // Set up database
    db << "BEGIN;";

    // Create tasks table
    db << "CREATE TABLE IF NOT EXISTS tasks\
                (id            INTEGER PRIMARY KEY,\
                 name          TEXT UNIQUE NOT NULL,\
                 interval_days INTEGER NOT NULL,\
                 category      INTEGER,\
                 FOREIGN KEY (category) REFERENCES categories (id));";

    // Create categories table
    db << "CREATE TABLE IF NOT EXISTS categories\
                (id     INTEGER PRIMARY KEY,\
                 name   TEXT UNIQUE NOT NULL);";

    db << "COMMIT;";
}

void Database::list_categories()
{
    std::cout << "CATEGORIES:" << std::endl;
    db << "SELECT id, name FROM categories"
       >> [&] (int id, const std::string& name)
          {
              std::cout << id << ' ' << name << '\n'; 
          };
    std::cout << std::endl;
}

bool Database::add_category()
{
    std::cout << "EXISTING ";
    list_categories();

    return true;
}

} // namespace

#endif

