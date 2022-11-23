#ifndef _ENV_UTILS_HPP
#define _ENV_UTILS_HPP

#include <cstdlib>
#include <thread>

#include <nintaco/nintaco.hpp>

namespace rom
{
    char RUN[] = "../../opt/java/jre1.8.0_latest/bin/java -jar "
                 "../../opt/nintaco/Nintaco_bin_2020-05-01/Nintaco.jar "
                 "../../res/rom/Super_Mario_Bros_E.nes";

    char SAV[] = "../../../res/sav/Super_Mario_Bros_E_1-1.save";

    void run()
    {
        std::thread th([&]() {
            std::system(rom::RUN);
        });
        th.detach();
    }

    void load(NintacoAPI* api)
    {
        nintaco_loadState(api, rom::SAV);
    }
}

#endif
