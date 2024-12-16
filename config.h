#pragma once

namespace Config {
    // Temperature Settings
    constexpr int MIN_TEMP_F = 350;
    constexpr int MAX_TEMP_F = 800;
    constexpr int TEMP_STEP = 10;
    constexpr int OPTIMAL_TEMP_MIN_F = 500;
    constexpr int OPTIMAL_TEMP_MAX_F = 650;
    
    // Display Settings
    constexpr uint16_t REFRESH_INTERVAL_MS = 500;
    constexpr int BTN_WIDTH = 100;
    constexpr int BTN_HEIGHT = 40;
    
    // Sensor Settings
    constexpr float DEFAULT_EMISSIVITY = 0.95f;
    constexpr float EMISSIVITY_STEP = 0.01f;
    constexpr int DEFAULT_TEMP_ALERT_F = 500;
    
    // Colors
    constexpr uint32_t LED_GREEN = 0x001100;
    constexpr uint32_t BUTTON_RED = TFT_RED;
    constexpr uint32_t BUTTON_GREEN = TFT_GREEN;
    
    // I2C Settings
    constexpr int I2C_SDA = 2;
    constexpr int I2C_SCL = 1;
}