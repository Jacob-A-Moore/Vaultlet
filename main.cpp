#include "kvstore.h"
#include <iostream>
#include <string>
#include <sstream>

int main()
{
    std::cout << "Welcome to kvstore CLI. Type --help for options.\n";
    kvstore store;//instantiated object of custom kvstore class

    std::string input;

    while (true)
    {
        //terminal startup
        std::cout << "kvstore> ";
        if (!std::getline(std::cin, input))
        {
            break; // Handle Ctrl+D or EOF3

        }

        //wrapping the user input in a string stream
        std::istringstream iss(input);
        std::string command;
        iss >> command;//string stream extraction operator extracts up to first whitespace char

        if (command == "put")
        {
            // TODO: Handle logic for 'put <key> <value>'
            std::string key, value;
            iss >> key >> value;
            store.put(key, value);
            std::cout << "Provided key [" << key <<"] and value [" << value << "] added successfully";

        }
        else if (command == "get")
        {
            // TODO: Handle logic for 'get <key>'
            std::string key, result_value;
            iss >> key;

            result_value = store.get(key);
            std::cout << "Target KEY: " << key << "Target VALUE: " << result_value;
        }
        else if (command == "remove")
        {
            // TODO: Handle logic for 'remove <key>'
            std::string key;
            iss >> key;

            bool success {store.remove(key)};
            if(!success)
            {
                std::cout << "Target KEY: " << key << " not found in store";
            }

        }
        else if (command == "list")
        {
            // TODO: Handle logic for 'list'
            std::map<std::string, std::string> store_data {store.list()};
            
            std::cout << "KEY:\tVALUE:"<<std::endl;
            for(const auto& pair : store_data)
            {
                std::cout << pair.first << '\t' << pair.second << '\n'<< std::endl;
            }  
        }
        else if (command == "clear")
        {
            // TODO: Handle logic for 'clear' or 'empty'
            std::cout << "Are you sure? Y/n";

        }
        else if (command == "--help")
        {
            std::cout << "Commands:\n"
                      << "  put <key> <value>    : Add a key-value pair\n"
                      << "  get <key>            : Retrieve value for key\n"
                      << "  remove <key>         : Remove key-value pair\n"
                      << "  list                 : List all key-value pairs\n"
                      << "  clear                : Clear all entries\n"
                      << "  exit                 : Exit the CLI\n";
        }
        else if (command == "exit")
        {
            std::cout << "Goodbye!\n";
            break;
        }
        else
        {
            std::cout << "Unknown command. Type --help for options.\n";
        }
    }

    return 0;
}

