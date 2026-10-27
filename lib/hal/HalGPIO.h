#pragma once

#include <Arduino.h>
#include <InputManager.h>

// X3 display SPI. Shared with the SD card (MISO).
#define EPD_SCLK 8
#define EPD_MOSI 10
#define EPD_CS 21
#define EPD_DC 4
#define EPD_RST 5
#define EPD_BUSY 6
#define SPI_MISO 7

// TI BQ27220 Current(). X3 has no USB-detect GPIO, so charging current stands in.
#define I2C_ADDR_BQ27220 0x55
#define BQ27220_CUR_REG 0x0C

class HalGPIO {
 public:
  enum class DeviceType : uint8_t { X4, X3 };

  HalGPIO() = default;

  bool deviceIsX3() const { return _deviceType == DeviceType::X3; }

  // "x3" or "x4c". X4 Classic keeps DeviceType::X4: it is not an X3.
  const char* shortName() const;

  bool isXteinkDevice() const;

  void begin();
  void update();

  bool isPressed(uint8_t buttonIndex) const;
  bool wasPressed(uint8_t buttonIndex) const;
  bool wasAnyPressed() const;
  bool wasReleased(uint8_t buttonIndex) const;
  bool wasAnyReleased() const;
  unsigned long getPowerButtonHeldTime() const;

  // Hold-time check after a power-button wake. False means go back to sleep.
  bool verifyPowerButtonWakeup(uint16_t requiredDurationMs, bool shortPressAllowed);

  bool isUsbConnected() const;

  enum class WakeupReason { PowerButton, AfterFlash, AfterUSBPower, Other };
  WakeupReason getWakeupReason() const;

  static constexpr uint8_t BTN_BACK = 0;
  static constexpr uint8_t BTN_CONFIRM = 1;
  static constexpr uint8_t BTN_LEFT = 2;
  static constexpr uint8_t BTN_RIGHT = 3;
  static constexpr uint8_t BTN_UP = 4;
  static constexpr uint8_t BTN_DOWN = 5;
  static constexpr uint8_t BTN_POWER = 6;

 private:
  InputManager inputMgr;
  DeviceType _deviceType = DeviceType::X4;
};

extern HalGPIO gpio;
