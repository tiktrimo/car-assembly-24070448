#include "CompatibilityValidator.h"

namespace {
    // CarType
    const int SEDAN_TYPE = 1, SUV_TYPE = 2, TRUCK_TYPE = 3;
    // Engine
    const int TOYOTA_ENG = 2, WIA_ENG = 3;
    // BrakeSystem
    const int MANDO_BRK = 1, CONTINENTAL_BRK = 2, BOSCH_BRK = 3;
    // SteeringSystem
    const int BOSCH_STR = 1;
}

void applyCarType(CarConfig& config, int answer)       { config.carType       = answer; }
void applyEngine(CarConfig& config, int answer)        { config.engine        = answer; }
void applyBrakeSystem(CarConfig& config, int answer)   { config.brakeSystem   = answer; }
void applySteeringSystem(CarConfig& config, int answer){ config.steeringSystem = answer; }

bool CompatibilityValidator::isValid(const CarConfig& config) const {
    if (config.carType == SEDAN_TYPE && config.brakeSystem == CONTINENTAL_BRK)
        return false;
    if (config.carType == SUV_TYPE && config.engine == TOYOTA_ENG)
        return false;
    if (config.carType == TRUCK_TYPE && config.engine == WIA_ENG)
        return false;
    if (config.carType == TRUCK_TYPE && config.brakeSystem == MANDO_BRK)
        return false;
    if (config.brakeSystem == BOSCH_BRK && config.steeringSystem != BOSCH_STR)
        return false;
    return true;
}
