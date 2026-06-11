#include "gtest/gtest.h"
#include "../CompatibilityValidator.h"

// Phase 2: 전역 stack[] 대신 CarConfig를 직접 갱신하는 함수들을 테스트
// applyXxx 함수는 UI 코드 없이 CarConfig만 업데이트 → 단위 테스트 가능

void applyCarType(CarConfig& config, int answer);
void applyEngine(CarConfig& config, int answer);
void applyBrakeSystem(CarConfig& config, int answer);
void applySteeringSystem(CarConfig& config, int answer);

TEST(CarConfigTest, ApplyCarType_StoresSedanAs1) {
    CarConfig config;
    applyCarType(config, 1);
    EXPECT_EQ(config.carType, 1);
}

TEST(CarConfigTest, ApplyCarType_StoresTruckAs3) {
    CarConfig config;
    applyCarType(config, 3);
    EXPECT_EQ(config.carType, 3);
}

TEST(CarConfigTest, ApplyEngine_StoresToyotaAs2) {
    CarConfig config;
    applyEngine(config, 2);
    EXPECT_EQ(config.engine, 2);
}

TEST(CarConfigTest, ApplyBrakeSystem_StoresBoschAs3) {
    CarConfig config;
    applyBrakeSystem(config, 3);
    EXPECT_EQ(config.brakeSystem, 3);
}

TEST(CarConfigTest, ApplySteeringSystem_StoresMobisAs2) {
    CarConfig config;
    applySteeringSystem(config, 2);
    EXPECT_EQ(config.steeringSystem, 2);
}

TEST(CarConfigTest, FullAssembly_AllFieldsPopulated) {
    CarConfig config;
    applyCarType(config, 2);       // SUV
    applyEngine(config, 1);        // GM
    applyBrakeSystem(config, 3);   // Bosch
    applySteeringSystem(config, 1); // Bosch

    EXPECT_EQ(config.carType,       2);
    EXPECT_EQ(config.engine,        1);
    EXPECT_EQ(config.brakeSystem,   3);
    EXPECT_EQ(config.steeringSystem, 1);
}
