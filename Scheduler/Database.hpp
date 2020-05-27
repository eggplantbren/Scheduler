#ifndef Scheduler_Database_hpp
#define Scheduler_Database_hpp

#include <sqlite_modern_cpp/hdr/sqlite_modern_cpp.h>

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

};

/* Implementations follow */

Database::Database()
:db(filename)
{
    // Set up database
    db << "BEGIN;";

    // Create tasks table
    db << "CREATE TABLE IF NOT EXISTS tasks\
                (id     INTEGER PRIMARY KEY,\
                 name   TEXT NOT NULL);";

    db << "COMMIT;";
}

} // namespace

#endif

