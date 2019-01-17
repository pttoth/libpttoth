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
    };
    cfgAddKey(cfg, fMaxDamage);
    cfgAddKey(cfg, fHealthPoints);
    cfgAddKey(cfg, bInvulnerable);

    char* pathin = "conf.cfg";
    char* pathout = "conf_out.cfg";

    cfg.readF(pathin);
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
