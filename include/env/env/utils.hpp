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

    char SAV[] = "../../res/sav/Super_Mario_Bros_E_1-1.save";

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

    void test()
    {
        rom::run();

        char str0[] = "localhost";
        NintacoAPI* api = nintaco_newNintacoAPI(str0, 9999);

        if (api->running) {
            return;
        } else {
            api->running = true;
        }
        char str1[] = "Connecting to %s:%d...";
        char str2[] = "Failed to establish connection.";
        char str3[] = "Connection established.";
        char str4[] = "Disconnected.";
        while(true) {

            nintaco_fireStatusChanged(api, str1, api->host, api->port);
            nintaco_openSocketConnection(api);
            if (api->in == NULL) {
                nintaco_fireStatusChanged(api, str2);
            } else {
                nintaco_fireStatusChanged(api, str3);
                nintaco_sendListeners(api);
                nintaco_sendReady(api);
                while(api->in && api->out && api->in->alive && api->out->alive) {
                    std::cout << "hello mario!\n";
                    rom::load(api);
                    nintaco_probeEvents(api);
                }
                nintaco_closeSocketConnect(api);
                nintaco_fireDeactivated(api);
                nintaco_fireStatusChanged(api, str4);
            }
            nintaco_sleep_ms(nintaco_RETRY_MILLIS);
        }
    }
}

#endif
