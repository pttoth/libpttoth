#include "pttoth/config.h"

#include <stdexcept>

using namespace pttoth;

Config::
        Config(){
}

Config::
        Config(const Config &other){
}

Config::
        Config(Config &&other){
}

Config::
        ~Config(){
}

Config &Config::
        operator=(const Config &other){
}

Config &Config::
        operator=(Config &&other){
}

bool Config::
        operator==(const Config &other) const{
}

void Config::
        addKey(unsigned id, const char *name){
    printf("value added: %d, %s\n", id, name);
}

void Config::read()
{

}

void Config::readS(const std::string &str)
{

}

void Config::readF(const char *path)
{

}

void Config::readF(const std::string &path)
{

}

void Config::write() const
{

}

void Config::write(const std::string &path) const
{

}

void Config::
        setPath(const std::string &path){
    _path = path;
}

std::string Config::
        getPath() const{
    return _path;
}

std::string Config::
        getS(unsigned id) const{
    /*
    for(entry& e : _entries){
        if(e.id == id){
            return e.val;
        }
    }
    throw std::logic_error("id not contained");
    */
}

float Config::getF(unsigned id) const
{

}

double Config::getD(unsigned id) const
{

}

int Config::getI(unsigned id) const
{

}

char Config::getC(unsigned id) const
{

}
