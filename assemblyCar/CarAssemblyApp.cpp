#include "CarAssemblyApp.h"
#include <cstdio>
#include <iostream>

#define CLEAR_SCREEN "\033[H\033[2J"

// ---- 순수 비즈니스 로직 ----

bool CarAssemblyApp::isValidAnswer(int step, int answer) const {
    switch (step) {
    case STEP_CAR_TYPE: return answer >= 1 && answer <= 3;
    case STEP_ENGINE:   return answer >= 0 && answer <= 4;
    case STEP_BRAKE:    return answer >= 0 && answer <= 3;
    case STEP_STEERING: return answer >= 0 && answer <= 2;
    case STEP_RUN_TEST: return answer >= 0 && answer <= 2;
    default: return false;
    }
}

int CarAssemblyApp::nextStep(int currentStep, int answer) const {
    if (currentStep == STEP_RUN_TEST && answer == 0) return STEP_CAR_TYPE;
    if (answer == 0 && currentStep > 0)              return currentStep - 1;
    if (currentStep < STEP_RUN_TEST)                 return currentStep + 1;
    return currentStep;
}

// ---- UI 출력 ----

void CarAssemblyApp::printMenu(int step) const {
    printf(CLEAR_SCREEN);
    switch (step) {
    case STEP_CAR_TYPE:
        printf("        ______________\n");
        printf("       /|            | \n");
        printf("  ____/_|_____________|____\n");
        printf(" |                      O  |\n");
        printf(" '-(@)----------------(@)--'\n");
        printf("===============================\n");
        printf("어떤 차량 타입을 선택할까요?\n");
        printf("1. Sedan\n2. SUV\n3. Truck\n");
        break;
    case STEP_ENGINE:
        printf("어떤 엔진을 탑재할까요?\n");
        printf("0. 뒤로가기\n1. GM\n2. TOYOTA\n3. WIA\n4. 고장난 엔진\n");
        break;
    case STEP_BRAKE:
        printf("어떤 제동장치를 선택할까요?\n");
        printf("0. 뒤로가기\n1. MANDO\n2. CONTINENTAL\n3. BOSCH\n");
        break;
    case STEP_STEERING:
        printf("어떤 조향장치를 선택할까요?\n");
        printf("0. 뒤로가기\n1. BOSCH\n2. MOBIS\n");
        break;
    case STEP_RUN_TEST:
        printf("멋진 차량이 완성되었습니다.\n어떤 동작을 할까요?\n");
        printf("0. 처음 화면으로 돌아가기\n1. RUN\n2. Test\n");
        break;
    }
}

void CarAssemblyApp::applyAnswer(int step, int answer) {
    switch (step) {
    case STEP_CAR_TYPE: applyCarType(config_, answer);       break;
    case STEP_ENGINE:   applyEngine(config_, answer);        break;
    case STEP_BRAKE:    applyBrakeSystem(config_, answer);   break;
    case STEP_STEERING: applySteeringSystem(config_, answer); break;
    }
}

void CarAssemblyApp::runCar() const {
    if (!validator_.isValid(config_)) {
        printf("자동차가 동작되지 않습니다\n");
        return;
    }
    if (config_.engine == 4) {
        printf("엔진이 고장나있습니다.\n자동차가 움직이지 않습니다.\n");
        return;
    }
    const char* carNames[]    = { "", "Sedan", "SUV", "Truck" };
    const char* engineNames[] = { "", "GM", "TOYOTA", "WIA" };
    const char* brakeNames[]  = { "", "Mando", "Continental", "Bosch" };
    const char* steerNames[]  = { "", "Bosch", "Mobis" };
    printf("Car Type : %s\n",       carNames[config_.carType]);
    printf("Engine : %s\n",         engineNames[config_.engine]);
    printf("Brake System : %s\n",   brakeNames[config_.brakeSystem]);
    printf("SteeringSystem : %s\n", steerNames[config_.steeringSystem]);
    printf("자동차가 동작됩니다.\n");
}

void CarAssemblyApp::testCar() const {
    if (validator_.isValid(config_)) {
        printf("자동차 부품 조합 테스트 결과 : PASS\n");
        return;
    }
    printf("자동차 부품 조합 테스트 결과 : FAIL\n");
    // 원인 출력은 기존 enum 숫자와 동일한 정수 값 사용
    if (config_.carType == 1 && config_.brakeSystem == 2)
        printf("Sedan에는 Continental제동장치 사용 불가\n");
    else if (config_.carType == 2 && config_.engine == 2)
        printf("SUV에는 TOYOTA엔진 사용 불가\n");
    else if (config_.carType == 3 && config_.engine == 3)
        printf("Truck에는 WIA엔진 사용 불가\n");
    else if (config_.carType == 3 && config_.brakeSystem == 1)
        printf("Truck에는 Mando제동장치 사용 불가\n");
    else if (config_.brakeSystem == 3 && config_.steeringSystem != 1)
        printf("Bosch제동장치에는 Bosch조향장치 이외 사용 불가\n");
}

// ---- 메인 루프 ----

void CarAssemblyApp::run() {
    int step = STEP_CAR_TYPE;
    while (true) {
        printMenu(step);
        printf("===============================\n");
        printf("INPUT > ");

        std::string input;
        std::getline(std::cin, input);

        if (parser_.isExitCommand(input)) {
            printf("바이바이\n");
            break;
        }

        auto parsed = parser_.parseNumber(input);
        if (!parsed.has_value()) {
            printf("ERROR :: 숫자만 입력 가능\n");
            continue;
        }
        int answer = parsed.value();

        if (!isValidAnswer(step, answer)) {
            printf("ERROR :: 범위를 벗어난 입력\n");
            continue;
        }

        if (step == STEP_RUN_TEST && answer == 1) { runCar();  continue; }
        if (step == STEP_RUN_TEST && answer == 2) { testCar(); continue; }

        if (answer != 0 && step < STEP_RUN_TEST)
            applyAnswer(step, answer);

        step = nextStep(step, answer);
    }
}
