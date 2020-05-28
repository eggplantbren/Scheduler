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

    // Completions
    db << "CREATE TABLE IF NOT EXISTS completions\
                (id     INTEGER PRIMARY KEY,\
                 time   INTEGER NOT NULL,\
                 task   INTEGER NOT NULL,\
                 FOREIGN KEY (task) REFERENCES tasks (id));";

    db << "COMMIT;";
}

void Database::list_categories()
{
    std::cout << "CATEGORIES:" << std::endl;
    db << "SELECT id, name FROM categories"
       >> [&] (int id, const std::string& name)
          {
              std::stringstream ss;
              ss << '[' << id << ']';
              while(ss.str().size() < 10)
                  ss << ' ';
              ss << name << '\n';
              std::cout << ss.str();
          };
    std::cout << std::endl;
}

bool Database::add_category()
{
    // Print out the categories that already exist
    list_categories();

    // Get the new category from the user
    std::cout << "Enter the name of the new category: ";
    std::string response;
    std::cin >> response;

    // Try to insert into the database
    bool success = true;
    try
    {
        db << "BEGIN;";
        db << "INSERT INTO categories (name) VALUES (?)" << response;
        db << "COMMIT;";
    }
    catch(...)
    {
        std::cerr << "Error adding new category." << std::endl;
        success = false;
    }

    return success;
}

} // namespace

#endif

