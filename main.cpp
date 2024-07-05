#include <iostream>
#include <sqlite3.h>
#include <sstream>
#include <string>
#include <random>


//Generatinig an random uint64_t value;
uint64_t generate()
{
    //Setting up the random generator
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64_t> distr(0, std::numeric_limits<uint64_t>::max());

    //Generating the ticket and return the value
    uint64_t ticket = distr(gen);
    return ticket;
}

//Gets an uint64_t value and stores it into a database
int buy(sqlite3* db)
{
    //Getting the ticket_number
    uint64_t ticket_number = generate();

    //Setting up the command
    std::stringstream cmd;
    cmd << "INSERT INTO tickets(ticket, arrived) VALUES(" << ticket_number << ", FALSE);";
    std::string query = cmd.str();

    //Variables
    char *errmsg = nullptr;

    //Executing the command
    int rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &errmsg);

    //Error Handling
    if (rc != SQLITE_OK)
    {
        std::cout << "[!] Command execution failur." << std::endl;
        return 1;
    }
    return 0;
}

//Gives back result for if the ticket exists
int callback(void* success, int column_count, char** _not_used_a, char** _not_used_b) {
    if (column_count == 1 && success != NULL) {
        int* success_ptr = reinterpret_cast<int*>(success);
        *success_ptr = 1;
        return 0;
    }
    return 1;
}

//Verifies the ticket
int verify(sqlite3* db, uint64_t ticket)
{
    //Setting up the query
    std::stringstream cmd;
    cmd << "SELECT ticket FROM tickets WHERE ticket LIKE "<< ticket<<" AND arrived LIKE " << "FALSE;";
    std::string query = cmd.str();

    //Variables
    int success = 0;
    char* errmsg = nullptr;
    int rc = sqlite3_exec(db, query.c_str(), callback, reinterpret_cast<void*>(&success), &errmsg);

    //Error Handling
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errmsg << std::endl;
        return 1;
    }

    //Verifing the ticket
    if (success)
    {
        cmd.clear();
        cmd << "UPDATE tickets SET arrived = TRUE WHERE ticket LIKE " << ticket << " AND arrived LIKE " << "FALSE;";
        query = cmd.str();

        rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &errmsg);

        if (rc != SQLITE_OK)
        {
            std::cout << "[!] Commmand execution error." << std::endl;
            return 1;
        }
        return 0;
    }
    return 1;
}

int main() 
{
    //Variables
    int choice;
    int result;
    uint64_t ticket;
    sqlite3* db = nullptr;
    char* errmsg;

    //Creating the database file
    int rc = sqlite3_open("ticket.db", &db);

    //Error Handling
    if (rc)
    {
        std::cout << "[!] Couldn't create database." << std::endl;
    }
    else 
    {
        std::cout << "[*] Database is setup!" << std::endl;
    }

    //Creating the table
    rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS tickets(id INT PRIMARY KEY ASC, ticket, arrived);", NULL, NULL, &errmsg);
    
    //Error Handling
    if (rc != SQLITE_OK)
    {
        std::cout << "[!] Command error" << std::endl;
    }
    else
    {
        std::cout << "[*] Command executed!" << std::endl;
    }
    
    //Display Options
    std::cout << "\033[2J\033[H" << std::flush;
    std::cout << "[1] Buy \n[2]Verify" << std::endl;
    std::cout << "Enter: ";
    std::cin >> choice;

    //Error Handling for user input
    while (choice > 2 or choice < 1)
    {
        std::cout << "\033[2J\033[H" << std::flush;
        std::cout << "[1] Buy \n[2] Verify" << std::endl;
        std::cout << "Enter: ";
        std::cin >> choice;
    }

    //Checking user input
    switch (choice)
    {
        //Buy
        case 1:
            
            //Buying a ticket
            result = buy(db);

            //Result
            if (result == 0)
            {
                std::cout << "[*] Purchase was successful." << std::endl;
                break;
            }
            else 
            {
                std::cout << "[!] Error...!" << std::endl;
                break;
            }

        //Verify
        case 2:
            //Asking for the ticket number
            std::cout << "\033[2J\033[H" << std::flush;
            std::cout << "Enter Ticket Number: ";
            std::cin >> ticket;
            
            //Verifying the ticket
            result = verify(db, ticket);

            //result
            if (result == 0)
            {
                std::cout << "[*] Ticket is Valid!" << std::endl;
                break;
            }
            else
            {
                std::cout << "[*] Ticket is Invalid!" << std::endl; 
                break;
            }
    }

}
