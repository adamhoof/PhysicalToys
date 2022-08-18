#pragma once

#include <IRsend.h>
#include <map>
#include <cstring>

    class OfficeLampController
    {
    public:
        std::map<const std::string, const uint32_t> modes = {
                {"on", 0x00F7C03F },
                {"white", 0x00F7E01F },
                {"yellow", 0x00F728D7 },
                {"blue", 0x00F7609F },
                {"green", 0x00F7A05F },
                {"red", 0x00F720DF },
                {"pink", 0x00F76897 },
                {"off", 0x00F740BF },
        };
    public:
        OfficeLampController();

        void changeMode(IRsend* irCodeSender, char* modeToSet);
    };
