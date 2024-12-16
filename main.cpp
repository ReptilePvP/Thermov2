#include <M5CoreS3.h>
#include <Wire.h>
#include "config.h"
#include "settings_manager.h"
#include "temperature_monitor.h"
#include "ui_manager.h"

void setup() {
    auto cfg = M5.config();
    CoreS3.begin(cfg);
    
    Wire.begin(Config::I2C_SDA, Config::I2C_SCL);
    
    SettingsManager::getInstance().begin();
    TemperatureMonitor::getInstance().begin(Wire);
    UIManager::getInstance().begin();
}

void loop() {
    CoreS3.update();
    
    auto& tempMonitor = TemperatureMonitor::getInstance();
    auto& uiManager = UIManager::getInstance();
    
    auto tempData = tempMonitor.update();
    uiManager.update(tempData);
    
    // Handle touch events based on current page
    if (uiManager.getCurrentPage() == UIManager::Page::MAIN) {
        handleMainMenuTouch();
    } else {
        handleSettingsTouch();
        
        // Check for button press to return to main menu
        int buttonStatus = tempMonitor.getButtonStatus();
        static bool wasPressed = false;
        
        if (buttonStatus == 1 && !wasPressed) {
            wasPressed = true;
            uiManager.setPage(UIManager::Page::MAIN);
        } else if (buttonStatus == 0) {
            wasPressed = false;
        }
    }
}