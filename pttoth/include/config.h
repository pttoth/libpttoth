/** -----------------------------------------------------------------------------
  * FILE:    config.h
  * AUTHOR:  pttoth
  * EMAIL:   peter.t.toth92@gmail.com
  * PURPOSE:
  * -----------------------------------------------------------------------------
  */

#pragma once

#include <cstdlib>
#include <string>
#include <vector>

namespace pttoth{

#define cfgAddKey(CFG_INSTANCE_NAME, ENUM_NAME) \
            CFG_INSTANCE_NAME.addKey(ENUM_NAME, #ENUM_NAME);

class Config{
    struct entry{
        unsigned int id;
        std::string  str;
        std::string  val;
    };

    std::vector<entry>  _entries;
    std::string         _path;

public:
    Config();
    Config(const Config& other);
    Config(Config&& other);
    virtual ~Config();
    Config& operator=(const Config &other);
    Config& operator=(Config &&other);
    bool operator==(const Config &other)const;

    void addKey(unsigned id, char const *name);

    void        read();
    void        readS(const std::string& str);
    void        readF(char const *path);
    void        readF(const std::string& path);

    void        write() const;
    void        write(const std::string& path)const;

    void        setPath(const std::string& path);
    std::string getPath() const;

    std::string getS(unsigned id) const;
    float       getF(unsigned id) const;
    double      getD(unsigned id) const;
    int         getI(unsigned id) const;
    char        getC(unsigned id) const;

    void        setS(unsigned id, std::string& str);
    void        setF(unsigned id, float f);
    void        setD(unsigned id, double d);
    void        setI(unsigned id, int i);
    void        setC(unsigned id, char c);

};

}

