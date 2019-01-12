#pragma once

#include "pttoth/config.h"

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

        cfg.readF("conf.cfg");


    }
};

}
