#ifndef _ENV_UTILS_HPP
#define _ENV_UTILS_HPP

#include <cstdlib>
#include <thread>

namespace CONST
{
    const char SYSROM[] = "../../opt/java/jre1.8.0_latest/bin/java -jar "
                          "../../opt/nintaco/Nintaco_bin_2020-05-01/Nintaco.jar "
                          "../../res/rom/Super\\ Mario\\ Bros\\ \\(E\\).nes";
}

namespace utils
{
    void sysrom()
    {
        std::thread th([&]() {
            std::system(CONST::SYSROM);
        });
        th.detach();
    }
}

#endif

