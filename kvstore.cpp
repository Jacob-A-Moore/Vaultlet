#include "kvstore.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
/* DEV PROJECT NOTES: 
 * --> Any instanct of getline() may be able to be replaced by '>>' extraction
 * operator. Look into it further then implement if functionality is either more optimal or simplified
 * -->
 */

/* constructor; sets filename member equal to filename arg in (const std::string& filename)
 * kvstore::kvstore(const std::string& filename) : filename(filename){}; 
 */
kvstore::kvstore()
{
    filename = "./vaultlet/kvdata.txt";
}

/*func; args std::string& key + filename; takes args and ensures given keys existence
  within kvstore persistent state file
 */
bool kvstore::exists(const std::string& key)
{
    if(filename.empty())
    {
        throw std::invalid_argument("Filename cannot be empty.");
    }


    std::ifstream in_file(filename);
    if(!in_file)
    {
        throw std::runtime_error("Could not open file " + filename);
    }

    std::string line;

    /* DEV NOTE : getline() works on any object that is a derivative of std::istream 
     * args for ifstream == getline(std::ifstream& , std::string&)
     * args for istringstream == getline(std::istringstream&, std::string&, char)
     */
    while(std::getline(in_file, line))
    {
        std::istringstream in_str_stream(line);
        std::string file_key;

        if(getline(in_str_stream, file_key, '\t'))
        {
            if(file_key == key)
            {
                in_file.close();
                return true;
            }
        }

    }
    in_file.close();
    return false;
}


//func; args std::string key + value; takes args and attempts to append them to kvstore file
/* DEV NOTE: May change return type to int OR bool for status coded results */
void kvstore::put(const std::string& key, const std::string& value)
{
    if(filename.empty())
    {
        throw std::runtime_error("No file selected for operation");
    }

    if(!exists(key) && !key.empty()) //!key.empty() is C++ optimal version of: key != " "
    {
        std::ofstream out_file(filename, std::ios::app);
        if(!out_file)
        {
            throw std::runtime_error("Could not open file for writing");
        }

        out_file << key << '\t' << value << ",\n";
        out_file.close();
    }

    else
    {
        std::cout << "Given key " << key << " already exists ";
    }
}


/* func; args std::string& key; takes key arg and searches through persistent kvstore file for matching 
 * key and returns the associated value with the key
 */
std::string kvstore::get(const std::string& key)
{
    if(!exists(key))
    {
        std::cout << "No such key " << key << " exists";
    }

    std::ifstream in_file(filename);
    if(!in_file)
    {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::string line;
    while(std::getline(in_file, line))
    {
        //create a string stream for extracting lines from the in_file
        std::istringstream in_str_stream(line);
        //strings for storing the file line_key and file line_value
        std::string file_key;
        std::string file_value;

        /*NOTE: calls getline up to not including the tab char, extracting the key
         * calls std::getline again continuing post tab char to the newline (\n) char, 
         * extracting the value associated with extracted value.
         */
        if(std::getline(in_str_stream, file_key, '\t') && std::getline(in_str_stream, file_value))
        {
            if(file_key == key)
            {
                return file_value;
            }
        }

    }
    in_file.close();
    return "";
}


/* func; std::string arg; searches I/O File for given target_key arg, if found will remove from store
 * if not found will return early false meaning given target_key does not exist
 */
bool kvstore::remove(std::string target_key)
{
    std::ifstream in_file(filename);
    if(!in_file)
    {
        throw std::runtime_error("File " + filename + " not found");
    }

    /* vector here stores the current lines of the persistent kvstore storage file to be modified and 
     * then rewriting it to the storage file
     */
    std::vector<std::string> lines;
    std::string line;

    //boolean flag for when target_key is discovered in the I/O Store File
    bool found = false;

    while(getline(in_file, line))
    {
        std::istringstream in_str_stream(line);
        std::string key, value;

        if(getline(in_str_stream, key, '\t') && getline(in_str_stream, value))
        {
            if(key != target_key)
            {
                lines.push_back(key + '\t' + value);
            }
            else
            {
                found = true;
            }
        }
    }
    in_file.close();

    //early return key_not_found
    if(!found)
    {
        return false;
    }
    
    std::ofstream out_file(filename, std::ios::trunc);
    if(!out_file)
    {
        throw std::runtime_error("No such file" + filename + "exists for writing");
    }

    for(size_t i=0; i < lines.size(); i++)
    {
        out_file << lines[i];
        if(i < lines.size()-1 )
        {
            out_file << '\n';
        }
    }
    out_file.close();
    return true;
}


//func; no args; returns a map object populated from the extraction of key value pairs from I/O File
std::map<std::string, std::string> kvstore::list()
{ 
    std::ifstream in_file(filename);
    if(!in_file) 
    {
        throw std::runtime_error("File" + filename + " not found");
    }

    std::map<std::string, std::string> temp_store;
    std::string line;

    while(getline(in_file, line))
    {
        std::istringstream in_str_stream(line);
        std::string key;
        std::string value;

        if(getline(in_str_stream, key, '\t') && getline(in_str_stream, value))
        {
            temp_store[key] = value;
        }
    }
    return temp_store;
}


//func;
void kvstore::empty()
{
    std::ofstream out_file(filename, std::ios::trunc);
    if(!out_file)
    {
        std::runtime_error("No such file exists for voiding");
    }

    out_file.close();
}









