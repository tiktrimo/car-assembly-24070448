#pragma once

// 부품 조합 정보를 담는 순수 데이터 구조체
struct CarConfig {
    int carType      = 0;
    int engine       = 0;
    int brakeSystem  = 0;
    int steeringSystem = 0;
};

class CompatibilityValidator {
public:
    bool isValid(const CarConfig& config) const;
};

// CarConfig 필드를 갱신하는 순수 함수 (전역 상태 없음)
void applyCarType(CarConfig& config, int answer);
void applyEngine(CarConfig& config, int answer);
void applyBrakeSystem(CarConfig& config, int answer);
void applySteeringSystem(CarConfig& config, int answer);
