#include "gtest/gtest.h"
#include "../CarAssemblyApp.h"

// Phase 4: UI와 비즈니스 로직 분리
// CarAssemblyApp의 스텝별 입력 유효성 검사와 스텝 전환 로직을 단위 테스트

class CarAssemblyAppTest : public ::testing::Test {
protected:
    CarAssemblyApp app;
};

// --- 스텝별 입력 유효성 검사 ---

TEST_F(CarAssemblyAppTest, CarTypeStep_ValidRange_1to3) {
    EXPECT_TRUE(app.isValidAnswer(CarAssemblyApp::STEP_CAR_TYPE, 1));
    EXPECT_TRUE(app.isValidAnswer(CarAssemblyApp::STEP_CAR_TYPE, 3));
}

TEST_F(CarAssemblyAppTest, CarTypeStep_InvalidRange_0and4) {
    EXPECT_FALSE(app.isValidAnswer(CarAssemblyApp::STEP_CAR_TYPE, 0));
    EXPECT_FALSE(app.isValidAnswer(CarAssemblyApp::STEP_CAR_TYPE, 4));
}

TEST_F(CarAssemblyAppTest, EngineStep_ZeroAllowed_Back) {
    EXPECT_TRUE(app.isValidAnswer(CarAssemblyApp::STEP_ENGINE, 0));
}

TEST_F(CarAssemblyAppTest, EngineStep_ValidRange_0to4) {
    EXPECT_TRUE(app.isValidAnswer(CarAssemblyApp::STEP_ENGINE, 4));
    EXPECT_FALSE(app.isValidAnswer(CarAssemblyApp::STEP_ENGINE, 5));
}

TEST_F(CarAssemblyAppTest, BrakeStep_ValidRange_0to3) {
    EXPECT_TRUE(app.isValidAnswer(CarAssemblyApp::STEP_BRAKE, 0));
    EXPECT_TRUE(app.isValidAnswer(CarAssemblyApp::STEP_BRAKE, 3));
    EXPECT_FALSE(app.isValidAnswer(CarAssemblyApp::STEP_BRAKE, 4));
}

TEST_F(CarAssemblyAppTest, SteeringStep_ValidRange_0to2) {
    EXPECT_TRUE(app.isValidAnswer(CarAssemblyApp::STEP_STEERING, 0));
    EXPECT_TRUE(app.isValidAnswer(CarAssemblyApp::STEP_STEERING, 2));
    EXPECT_FALSE(app.isValidAnswer(CarAssemblyApp::STEP_STEERING, 3));
}

TEST_F(CarAssemblyAppTest, RunTestStep_ValidRange_0to2) {
    EXPECT_TRUE(app.isValidAnswer(CarAssemblyApp::STEP_RUN_TEST, 0));
    EXPECT_TRUE(app.isValidAnswer(CarAssemblyApp::STEP_RUN_TEST, 2));
    EXPECT_FALSE(app.isValidAnswer(CarAssemblyApp::STEP_RUN_TEST, 3));
}

// --- 스텝 전환 ---

TEST_F(CarAssemblyAppTest, NextStep_CarType_AdvancesToEngine) {
    EXPECT_EQ(app.nextStep(CarAssemblyApp::STEP_CAR_TYPE, 1), CarAssemblyApp::STEP_ENGINE);
}

TEST_F(CarAssemblyAppTest, NextStep_Engine_AdvancesToBrake) {
    EXPECT_EQ(app.nextStep(CarAssemblyApp::STEP_ENGINE, 1), CarAssemblyApp::STEP_BRAKE);
}

TEST_F(CarAssemblyAppTest, NextStep_EngineBack_ReturnsToCareType) {
    EXPECT_EQ(app.nextStep(CarAssemblyApp::STEP_ENGINE, 0), CarAssemblyApp::STEP_CAR_TYPE);
}

TEST_F(CarAssemblyAppTest, NextStep_RunTestReset_ReturnsToCareType) {
    EXPECT_EQ(app.nextStep(CarAssemblyApp::STEP_RUN_TEST, 0), CarAssemblyApp::STEP_CAR_TYPE);
}

TEST_F(CarAssemblyAppTest, NextStep_Steering_AdvancesToRunTest) {
    EXPECT_EQ(app.nextStep(CarAssemblyApp::STEP_STEERING, 1), CarAssemblyApp::STEP_RUN_TEST);
}
