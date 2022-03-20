#pragma once

#include "OfficeLamp.h"
#include <map>

namespace ApplianceController
{
    class OfficeLampController
    {
    private:
        char* currentMode;

        std::map<const std::string, const uint32_t> availableModes = {
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

        PhysicalToy::OfficeLamp officeLamp {};

        void init();

        void changeMode(char* modeToSet);
    };
}
