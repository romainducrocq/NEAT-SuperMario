#ifndef _ENV_UTILS_HPP
#define _ENV_UTILS_HPP

#include <cstdlib>
#include <thread>

#include <nintaco/nintaco.hpp>

namespace rom
{
    const char RUN[] = "../../opt/java/jre1.8.0_latest/bin/java -jar "
                       "../../opt/nintaco/Nintaco_bin_2020-05-01/Nintaco.jar "
                       "../../res/rom/Super\\ Mario\\ Bros\\ \\(E\\).nes";

    const char SAV[] = "";

    void run()
    {
        std::thread th([&]() {
            std::system(rom::RUN);
        });
        th.detach();
    }

    void load()
    {

    }

}

#endif
