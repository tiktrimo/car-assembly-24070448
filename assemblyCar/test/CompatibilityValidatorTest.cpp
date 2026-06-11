#include "gtest/gtest.h"
#include "../CompatibilityValidator.h"

class CompatibilityValidatorTest : public ::testing::Test {
protected:
    CompatibilityValidator validator;
};

// Sedan + Continental 제동장치 조합 불가
TEST_F(CompatibilityValidatorTest, Sedan_Continental_IsInvalid) {
    CarConfig config{ SEDAN, GM_ENGINE, CONTINENTAL_BRAKE, BOSCH_STEERING };
    EXPECT_FALSE(validator.isValid(config));
}

// SUV + Toyota 엔진 조합 불가
TEST_F(CompatibilityValidatorTest, SUV_Toyota_IsInvalid) {
    CarConfig config{ SUV, TOYOTA_ENGINE, MANDO_BRAKE, BOSCH_STEERING };
    EXPECT_FALSE(validator.isValid(config));
}

// Truck + WIA 엔진 조합 불가
TEST_F(CompatibilityValidatorTest, Truck_WIA_IsInvalid) {
    CarConfig config{ TRUCK, WIA_ENGINE, CONTINENTAL_BRAKE, BOSCH_STEERING };
    EXPECT_FALSE(validator.isValid(config));
}

// Truck + Mando 제동장치 조합 불가
TEST_F(CompatibilityValidatorTest, Truck_Mando_IsInvalid) {
    CarConfig config{ TRUCK, GM_ENGINE, MANDO_BRAKE, BOSCH_STEERING };
    EXPECT_FALSE(validator.isValid(config));
}

// Bosch 제동장치 + 비Bosch 조향장치 조합 불가
TEST_F(CompatibilityValidatorTest, BoschBrake_MobisSteering_IsInvalid) {
    CarConfig config{ SEDAN, GM_ENGINE, BOSCH_BRAKE, MOBIS_STEERING };
    EXPECT_FALSE(validator.isValid(config));
}

// 정상 조합: Sedan + GM + Mando + Bosch
TEST_F(CompatibilityValidatorTest, ValidCombination_Sedan_GM_Mando_Bosch) {
    CarConfig config{ SEDAN, GM_ENGINE, MANDO_BRAKE, BOSCH_STEERING };
    EXPECT_TRUE(validator.isValid(config));
}

// 정상 조합: SUV + GM + Continental + Mobis
TEST_F(CompatibilityValidatorTest, ValidCombination_SUV_GM_Continental_Mobis) {
    CarConfig config{ SUV, GM_ENGINE, CONTINENTAL_BRAKE, MOBIS_STEERING };
    EXPECT_TRUE(validator.isValid(config));
}

// 정상 조합: Truck + GM + Bosch 제동 + Bosch 조향
TEST_F(CompatibilityValidatorTest, ValidCombination_Truck_GM_Bosch_Bosch) {
    CarConfig config{ TRUCK, GM_ENGINE, BOSCH_BRAKE, BOSCH_STEERING };
    EXPECT_TRUE(validator.isValid(config));
}

// Bosch 제동장치 + Bosch 조향장치는 유효
TEST_F(CompatibilityValidatorTest, BoschBrake_BoschSteering_IsValid) {
    CarConfig config{ SEDAN, GM_ENGINE, BOSCH_BRAKE, BOSCH_STEERING };
    EXPECT_TRUE(validator.isValid(config));
}
