#pragma once
#include <M5UNIT_NCIR2.h>
#include "config.h"

class TemperatureMonitor {
public:
    struct TempData {
        float celsius;
        int fahrenheit;
        bool inOptimalRange;
        bool hasChanged;
    };

    static TemperatureMonitor& getInstance() {
        static TemperatureMonitor instance;
        return instance;
    }

    void begin(TwoWire& wire) {
        ncir2.begin(&wire, Config::I2C_SDA, Config::I2C_SCL, M5UNIT_NCIR2_DEFAULT_ADDR);
        ncir2.setLEDColor(Config::LED_GREEN);
    }

    TempData update() {
        if (millis() - lastUpdate < Config::REFRESH_INTERVAL_MS) {
            return lastTempData;
        }

        lastUpdate = millis();
        float tempC = static_cast<float>(ncir2.getTempValue()) / 100.0f;
        int tempF = celsiusToFahrenheit(tempC);
        
        TempData newData = {
            .celsius = tempC,
            .fahrenheit = tempF,
            .inOptimalRange = isInOptimalRange(tempF),
            .hasChanged = (tempF != lastTempData.fahrenheit)
        };

        lastTempData = newData;
        return newData;
    }

    int getButtonStatus() const {
        return ncir2.getButtonStatus();
    }

private:
    TemperatureMonitor() : lastUpdate(0) {}
    
    M5UNIT_NCIR2 ncir2;
    unsigned long lastUpdate;
    TempData lastTempData = {};

    static int celsiusToFahrenheit(float celsius) {
        return static_cast<int>((celsius * 9.0f / 5.0f) + 32.0f);
    }

    static bool isInOptimalRange(int tempF) {
        return tempF >= Config::OPTIMAL_TEMP_MIN_F && 
               tempF <= Config::OPTIMAL_TEMP_MAX_F;
    }
};