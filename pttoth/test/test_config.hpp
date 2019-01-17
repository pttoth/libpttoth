#pragma once

#include "pttoth/config.h"
#include "pttoth/std_extension.hpp"

#include <iostream>

namespace pttoth{

class test_config{

public:
    test_config(){}
    bool run(){

        Config cfg;

        enum e{
            fMaxDamage,
            fHealthPoints,
            bInvulnerable
        };
        cfgAddKey(cfg, fMaxDamage);
        cfgAddKey(cfg, fHealthPoints);
        cfgAddKey(cfg, bInvulnerable);

        //cfg.readF("conf.cfg");

        cfg.setF(fMaxDamage, 100.0f);
        //cfg.getF(fMaxDamage);

        testTrimWhitespace(" \t    \t  ", "");
        testTrimWhitespace("asd", "asd");
        testTrimWhitespace("123", "123");
        testTrimWhitespace("asd123", "asd123");
        testTrimWhitespace("123asd", "123asd");
        testTrimWhitespace("asd123asd", "asd123asd");
        testTrimWhitespace("123asd123", "123asd123");
        testTrimWhitespace(" asd  asd \t", "asd  asd");
        testTrimWhitespace("  asdasd \t", "asdasd");
        testTrimWhitespace(" 123 asdasd \t", "123 asdasd");
        testTrimWhitespace("  a", "a");
        testTrimWhitespace("a  ", "a");
        testTrimWhitespace(" a ", "a");
        testTrimWhitespace("  asd", "asd");
        testTrimWhitespace("asd  ", "asd");
        testTrimWhitespace(" asd ", "asd");

    }

    bool testTrimWhitespace(char const *str, char const *expected) const{
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

};

}
