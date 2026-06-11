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
