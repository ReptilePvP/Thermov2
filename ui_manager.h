#pragma once
#include <M5CoreS3.h>
#include "config.h"
#include "temperature_monitor.h"

class UIManager {
public:
    enum class Page { MAIN, SETTINGS };

    static UIManager& getInstance() {
        static UIManager instance;
        return instance;
    }

    void begin() {
        setupDisplay();
        currentPage = Page::MAIN;
        needsRedraw = true;
    }

    void update(const TemperatureMonitor::TempData& tempData) {
        if (needsRedraw) {
            CoreS3.Display.fillScreen(TFT_BLACK);
            if (currentPage == Page::MAIN) {
                drawMainMenu();
            } else {
                drawSettingsPage();
            }
            needsRedraw = false;
        }

        if (currentPage == Page::MAIN) {
            updateTemperatureDisplay(tempData);
        }
    }

    void setPage(Page page) {
        if (currentPage != page) {
            currentPage = page;
            needsRedraw = true;
        }
    }

    Page getCurrentPage() const { return currentPage; }

private:
    UIManager() {}
    
    Page currentPage;
    bool needsRedraw;

    void setupDisplay() {
        CoreS3.Display.setTextDatum(middle_center);
        CoreS3.Display.setFont(&fonts::FreeSansBoldOblique12pt7b);
    }

    // ... (Rest of the UI drawing methods from your original code,
    //      but organized within this class)
};