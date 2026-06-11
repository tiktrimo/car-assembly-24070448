#pragma once
#include "CompatibilityValidator.h"
#include "InputParser.h"

class CarAssemblyApp {
public:
    // 스텝 상수 (테스트와 main 양쪽에서 사용)
    static const int STEP_CAR_TYPE = 0;
    static const int STEP_ENGINE   = 1;
    static const int STEP_BRAKE    = 2;
    static const int STEP_STEERING = 3;
    static const int STEP_RUN_TEST = 4;

    // 메인 루프 실행
    void run();

    // 순수 비즈니스 로직 (단위 테스트 가능)
    bool isValidAnswer(int step, int answer) const;
    int  nextStep(int currentStep, int answer) const;

private:
    CarConfig           config_;
    CompatibilityValidator validator_;
    InputParser         parser_;

    void printMenu(int step) const;
    void applyAnswer(int step, int answer);
    void runCar() const;
    void testCar() const;
};
