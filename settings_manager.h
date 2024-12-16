#pragma once
#include <Preferences.h>
#include "config.h"

class SettingsManager {
public:
    struct Settings {
        float emissivity;
        int tempAlert;
    };

    static SettingsManager& getInstance() {
        static SettingsManager instance;
        return instance;
    }

    void begin() {
        loadSettings();
    }

    const Settings& getSettings() const { return settings; }
    
    void updateEmissivity(float delta) {
        settings.emissivity = constrain(
            settings.emissivity + delta,
            0.0f,
            1.0f
        );
        saveSettings();
    }
    
    void updateTempAlert(int delta) {
        settings.tempAlert = constrain(
            settings.tempAlert + delta,
            Config::MIN_TEMP_F,
            Config::MAX_TEMP_F
        );
        saveSettings();
    }

private:
    SettingsManager() {}
    Settings settings;
    Preferences preferences;

    void loadSettings() {
        preferences.begin("settings", true);
        settings.emissivity = preferences.getFloat("emissivity", Config::DEFAULT_EMISSIVITY);
        settings.tempAlert = preferences.getInt("tempAlert", Config::DEFAULT_TEMP_ALERT_F);
        preferences.end();
    }

    void saveSettings() {
        preferences.begin("settings", false);
        preferences.putFloat("emissivity", settings.emissivity);
        preferences.putInt("tempAlert", settings.tempAlert);
        preferences.end();
    }
};