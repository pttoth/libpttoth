#pragma once

#include "pttoth/config.h"
#include "pttoth/std_extension.hpp"

#include <iostream>

namespace pttoth{

class test_config{

public:
    test_config(){}
    bool run();
    void testTrims();
    bool _testTrimWhitespace(char const *str, char const *expected) const;


};

bool test_config::
        run(){
    Config cfg;
    enum e{
        fMaxDamage,
        fHealthPoints,
        bInvulnerable,
        bNewData1,
        bNewData2,
        fInvalidKey,
        iWriteFReadI,
        fWriteIReadF,
        cChar,
        cCharWithWhiteSpaces,
        cCharTabSpaces,
        cCharString,
    };
    cfgAddKey(cfg, fMaxDamage);
    cfgAddKey(cfg, fHealthPoints);
    cfgAddKey(cfg, bInvulnerable);

    cfgAddKey(cfg, cChar);
    cfgAddKey(cfg, cCharWithWhiteSpaces);
    cfgAddKey(cfg, cCharTabSpaces);
    cfgAddKey(cfg, cCharString);


    char* pathin = "./conf.cfg";
    char* pathout = "./conf_out.cfg";

    try{
        cfg.readF(pathin);
    }catch(std::invalid_argument& e){
        std::cout << "exception caught when trying to read file!\n  reason: " << e.what() << "\n";
    }

    cfg.setF(fMaxDamage, 100.0f);
    cfgAddKey(cfg, bNewData1);
    cfgAddKey(cfg, bNewData2);
    cfg.setB(bNewData1, true);
    cfg.setB(bNewData2, false);

    cfgAddKey(cfg, iWriteFReadI);
    float f = 1.0001f;
    cfg.setF(iWriteFReadI, f);
    std::cout << "write value: (float) " << f << "\n";
    std::cout << "read value: (int) " << cfg.getI(iWriteFReadI) << "\n";


    cfgAddKey(cfg, fWriteIReadF);
    float i = 155;
    cfg.setF(fWriteIReadF, i);
    std::cout << "write value: (int) " << i << "\n";
    std::cout << "read value:  (float)" << cfg.getF(fWriteIReadF) << "\n";

    //cfg.setF(fInvalidKey, 0.01f);

    cfg.writeF(pathout);

    //testTrims();

    std::cout << "------------------------\n";
    std::cout << "testing char handling:\n";
    std::cout << "------------------------\n";
    const char  c_char                  = 'c';
    const char *c_charwithwhitespaces   = "  a  ";
    const char *c_chartabspaces   = " \t ";
    const char *c_charstring            = "strval";


    cfg.setC(cChar, c_char);
    cfg.setS(cCharWithWhiteSpaces, c_charwithwhitespaces);
    cfg.setS(cCharTabSpaces, c_chartabspaces);
    cfg.setS(cCharString, c_charstring);

    try{
        std::cout << "cChar:                  string value: '" << c_char                  << "',\treturned value: '" << cfg.getC(cChar) << "'\n";
        std::cout << "cCharWithWhiteSpaces:   string value: '" << c_charwithwhitespaces   << "',\treturned value: '" << cfg.getC(cCharWithWhiteSpaces) << "'\n";
        try{
            std::cout << "cCharTabSpaces:         string value: '" << c_chartabspaces   << "'\n";
            std::cout << "  this should throw std::invalid_argument...";
            {
                char c = cfg.getC(cCharTabSpaces);
                std::cout << "  FAIL\n  returned char: '" << c << "'\n\n";
            }
        }catch(std::invalid_argument& e){
            std::cout << "  SUCCESS\n  exception caught: " << e.what() << "\n\n";
        }
        try{
            std::cout << "cCharString:            string value: '" << c_charstring << "'\n";
            std::cout << "  this should throw std::invalid_argument...";
            {
                char c = cfg.getC(cCharString);
                std::cout << "  FAIL\n  returned char: '" << c << "'\n\n";
            }
        }catch(std::invalid_argument& e){
            std::cout << "  SUCCESS\n  exception caught: " << e.what() << "\n\n";
        }
    }catch(std::invalid_argument& e){
        std::cout << "\nTEST FAILED:  unexpected exception caught: " << e.what() << "\n";
    }
    std::cout << "------------------------\n";
    return true;
}

void test_config::
        testTrims(){
    std::cout << "-----------------------------------\n";
    std::cout << "---------testing Config------------\n";
    std::cout << "-----------------------------------\n";
    _testTrimWhitespace(" \t    \t  ", "");
    _testTrimWhitespace("asd", "asd");
    _testTrimWhitespace("123", "123");
    _testTrimWhitespace("asd123", "asd123");
    _testTrimWhitespace("123asd", "123asd");
    _testTrimWhitespace("asd123asd", "asd123asd");
    _testTrimWhitespace("123asd123", "123asd123");
    _testTrimWhitespace(" asd  asd \t", "asd  asd");
    _testTrimWhitespace("  asdasd \t", "asdasd");
    _testTrimWhitespace(" 123 asdasd \t", "123 asdasd");
    _testTrimWhitespace("  a", "a");
    _testTrimWhitespace("a  ", "a");
    _testTrimWhitespace(" a ", "a");
    _testTrimWhitespace("  asd", "asd");
    _testTrimWhitespace("asd  ", "asd");
    _testTrimWhitespace(" asd ", "asd");
    std::cout << "-----------------------------------\n";
}

bool test_config::
        _testTrimWhitespace(const char *str, const char *expected) const{
    std::string orig(str);
    std::string ex(expected);
    std::string res = trimWhitespaces(orig);
    std::cout << "orig content: '" << orig << "'\n";
    std::cout << "orig len: " << orig.length() << "\n";
    std::cout << "expected content: '" << ex << "'\n";
    std::cout << "expected len: " << ex.length() << "\n";
    std::cout << "res content: '" << res << "'\n";
    std::cout << "res len: " << res.length() << "\n";
    if(res == ex){ std::cout << "passed\n";
    }else{ std::cout << "failed\n";
    }
    std::cout << "---\n";
    return res == ex;
}

}
