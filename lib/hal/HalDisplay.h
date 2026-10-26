#pragma once
#include <Arduino.h>
#include <EInkDisplay.h>

class HalDisplay {
 public:
  HalDisplay();

  enum RefreshMode {
    FULL_REFRESH,  // Full refresh with complete waveform
    HALF_REFRESH,  // Scrub refresh: every pixel driven to target
    FAST_REFRESH   // Fast refresh using custom LUT
  };

  void begin();

  void clearScreen(uint8_t color = 0xFF) const;
  void displayBuffer(RefreshMode mode = RefreshMode::FAST_REFRESH, bool turnOffScreen = false);

  // Optional poll during blocking BUSY waits (button edges the main loop would miss).
  void setBusyWaitSliceHook(bool (*sliceHook)(int8_t busyPin, uint8_t busyLevel));

  // Framebuffer stays in normal polarity. The driver inverts while sending.
  void setInverted(bool inverted);
  void deepSleep();
  uint8_t* getFrameBuffer() const;

  uint16_t getDisplayWidth() const;
  uint16_t getDisplayHeight() const;
  uint16_t getDisplayWidthBytes() const;

 private:
  EInkDisplay einkDisplay;
};

extern HalDisplay display;
