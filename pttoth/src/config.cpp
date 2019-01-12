#include "pttoth/config.h"

#include <stdexcept>

#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>

using namespace pttoth;

Config::
        Config(Config &&source){
    _entries    = std::move(source._entries);
    _path       = std::move(source._path);
}

Config &Config::
        operator=(Config &&source){
    _entries    = std::move(source._entries);
    _path       = std::move(source._path);
    return *this;
}

void Config::
        addKey(unsigned id, const char *name){
    printf("value added: %d, %s\n", id, name);
}

void Config::
        read(){
    if( 0 == _path.length() ){
        throw std::logic_error("no path defined");
    }
    readF(_path);
}

void Config::
        readF(const char *path){
    std::ifstream ifs;

    ifs.open(path);
    if( !ifs.is_open() ){
        std::string errormsg = "couldn't open file: ";
        errormsg += path;
        throw std::invalid_argument( errormsg );
    }

    _parseData(ifs);
}

void Config::
        readF(const std::string &path){
    readF( path.c_str() );
}

void Config::
        readS(const std::string &str){
    std::stringstream ss(str);
    _parseData(ss);
}

void Config::
        write(){
    //write(_path);
}

void Config::writeF(const char *path)
{

}

void Config::writeF(const std::string &path) const
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

bool Config::
        hasPath() const{
    return 0 < _path.length();
}

bool Config::
        fileExists(const std::string &path) const{

}

std::string Config::
        trimComments(const std::string &str) const{
    int idx_denom = str.find(";");
    if(-1 < idx_denom){
        return str.substr(0, idx_denom);
    }
    return str;
}

bool Config::
        isEmptyLine(const std::string &str) const{
    return str.length() == 0;
}

bool Config::
        splitEntry(const std::string &str, std::string *retval) const{
    //todo:
    //  validate and split with regex
    //  return value is success or fail (no exception handling)
    std::cout << "MISSING IMPLEMENTATION: splitEntry()!\n";
    return true;
}

bool Config::
        isRecognizedKey(const std::string &str) const{

}

int Config::
        getKeyIndex(int eKey) const{
    for(int i=0; i<_entries.size(); ++i){
        if( eKey == _entries[i].key_id ) return i;
    }
    return -1;
}


int Config::
        getKeyIndex(const std::string &str) const{
    for(int i=0; i<_entries.size(); ++i){
        if( str == _entries[i].key_str ) return i;
    }
    return -1;
}

void Config::
        _processData(const std::string &data){
    std::stringstream ss(data);
    std::string line;
    std::string cfg_text;
    std::string cfg[2]; //[0]: key, [1]: val
    while( std::getline(ss, line) ){
        cfg_text = trimComments(line);
        splitEntry(cfg_text, cfg);
        int idx_key = getKeyIndex( cfg[0] );
        if(-1 < idx_key){
            _entries[idx_key].val_str = cfg[1];
        }else{
            std::cerr << "WARNING: unrecognized config key: " << cfg[0] << "\n";
        }
    }
}

void Config::
        _parseData(std::istream &stream){
    std::stringstream ss;
    std::string data;
    size_t expected_size = 0;
    std::string strbuf;

    while( std::getline(stream, strbuf) ){
        if(0 < strbuf.length()){
            ss << strbuf << "\n";
            expected_size += strbuf.size() + 1; //calculates size avoiding possible LF/CRLF errors later
        }
    }

    //running the code from QtCreator, there seems to be a bug,
    //  where ss.str() is longer than it should be and contains garbage at the end
    //  couldn't find errors in the code, dunno if this is because Qt runs it with different dll-s
    //this cuts off any possible bullshit from the end of the string
    data = ss.str();
    data = data.substr(0, expected_size);

    _processData(data);
}

