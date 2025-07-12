#ifndef KVSTORE_H
#define KVSTORE_H

#include <string>
#include <map>

class kvstore
{

private:
    std::string filename;
    
public:
    //constructor definition
    kvstore();//const std::string& filename == optional build for constructor arg

    bool exists(const std::string& key); //const std::string& filename == optional build for method arg
    void put(const std::string& key, const std::string& value);
    std::string get(const std::string& key);
    bool remove(std::string target_key);
    std::map<std::string, std::string> list();
    void empty();
};
#endif
