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
#include <istream>

namespace pttoth{

#define cfgAddKey(CFG_INSTANCE_NAME, ENUM_NAME) \
            CFG_INSTANCE_NAME.addKey(ENUM_NAME, #ENUM_NAME);

class Config{
public:
    Config()                    = default;
    Config(const Config& other) = default;
    Config(Config&& source);
    virtual ~Config(){}
    Config& operator=(const Config &other)  = default;
    Config& operator=(Config &&source);
    bool operator==(const Config &other) const  = delete;

    void        addKey(unsigned id, char const *name);

    void        read();
    void        readF(char const *path);
    void        readF(const std::string& path);
    void        readS(const std::string& str);

    void        write();
    void        writeF(char const *path);
    void        writeF(const std::string& path) const;

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

private:
    struct entry{
        unsigned int key_id;        //the key's actual enum as integer
        std::string  key_str;       //enum id as string
        std::string  val_str;       //string value associated with key
    };

    std::vector<entry>  _entries;   //the stored data
    std::string         _path;      //file to read from and write to

    bool hasPath() const;
    bool fileExists(const std::string& path) const;

    //TODO: make this generic, not class dependent
    bool ValiatePath(const std::string& path);

    std::string trimComments(const std::string& str) const;
    bool isEmptyLine(const std::string& str) const;
    bool splitEntry(const std::string& str, std::string* retval) const;
    bool isRecognizedKey(const std::string& str) const;
    int getKeyIndex(int eKey) const;
    int getKeyIndex(const std::string& str) const;


    //after the config was read from any input, we have it in a string
    //this is the common processing function, which parses the expected
    //  data from the string
    void _processData(const std::string& data);
    void _parseData(std::istream& stream);
};

}

