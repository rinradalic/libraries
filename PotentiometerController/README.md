# PotentiometerController

Analog input library for reading potentiometers (VR - Variable Resistor) on ESP32/Arduino. Designed for Analog Control with VR.

## Features

- ✅ Simple ADC reading with automatic platform detection
- ✅ Built-in percentage conversion (0-100%)
- ✅ Custom range mapping
- ✅ Support for both ESP32 (12-bit) and Arduino (10-bit) ADC
- ✅ Examples for PWM LED control, dual LED, and running lights

## What is a VR (Potentiometer)?

A **Variable Resistor (VR)** or **Potentiometer** is a three-terminal resistor with a rotating shaft that changes resistance.

### Physical Structure

```
Pin 1 ──────┐
            │
      Resistive Element
            │
Pin 3 ──────┘

Pin 2 (Wiper/Center) → Moves along resistive element
```

### Three Pins

1. **Pin 1** → Connect to VCC (3.3V on ESP32)
2. **Pin 2** (Center/Wiper) → Connect to ADC pin (outputs variable voltage)
3. **Pin 3** → Connect to GND

## Theory: Voltage Divider

When you rotate the VR:
- The wiper (center pin) voltage changes from **0V to VCC**
- This creates a **voltage divider** circuit
- The microcontroller reads this voltage as a **digital value**

```
VCC (3.3V) ───┐
              │
            [ VR ]
              │
GND ──────────┘

Wiper voltage: 0V to 3.3V
ADC reading:   0 to 4095 (ESP32) or 0 to 1023 (Arduino)
```

## Hardware Connection (ESP32)

### ⚠️ Important: Use 3.3V, NOT 5V on ESP32!

```
ESP32 (ESP32)
┌────────────┐
│ 3.3V ──────┼──► VR Pin 1
│            │
│ GPIO 34 ───┼──► VR Pin 2 (Wiper)
│ (ADC)      │
│            │
│ GND ───────┼──► VR Pin 3
└────────────┘
```

### Recommended ADC Pins (ESP32)

- ✅ GPIO 34, 35, 36, 39 (Input only, ideal for ADC)
- ✅ GPIO 32, 33, 25, 26, 27 (Can be input/output, also work)
- ⚠️ Avoid GPIO 0, 2, 12, 15 (boot pins)

## Installation

### Arduino IDE

```bash
cp -r PotentiometerController ~/Arduino/libraries/
```

### PlatformIO

```ini
lib_deps = 
    file:///path/to/Micro-Docs/PotentiometerController
```

## ⚠️ ESP32 Core 3.x Compatibility

**Important:** This library's PWM examples have been updated for **ESP32 Arduino Core 3.x**.

### Breaking Changes in Core 3.x

The PWM API changed in ESP32 Core 3.x:

#### Old API (Core 2.x) - DEPRECATED
```cpp
ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
ledcAttachPin(LED_PIN, PWM_CHANNEL);
ledcWrite(PWM_CHANNEL, pwmValue);
```

#### New API (Core 3.x) - CURRENT
```cpp
ledcAttach(LED_PIN, PWM_FREQ, PWM_RESOLUTION);
ledcWrite(LED_PIN, pwmValue);
```

### What Changed?
- `ledcSetup()` + `ledcAttachPin()` → Combined into `ledcAttach()`
- No longer need to manage PWM channels manually
- `ledcWrite()` now uses **pin number** instead of channel number

### Updated Examples
All PWM examples in this library use the new API:
- ✅ `VR_LED_Brightness` - Updated
- ✅ `VR_DualLED_Control` - Updated
- ✅ `VR_RunningLight_Speed` - No changes needed (uses digitalWrite)

### Checking Your Core Version

```cpp
// In Arduino IDE:
// Tools > Board > Boards Manager > Search "esp32"
// Version 3.x.x = Use new API
// Version 2.x.x = Use old API (deprecated)
```

## Quick Start

### Example 1: Read Raw Value

```cpp
#include <PotentiometerController.h>

PotentiometerController vr(34); // GPIO 34

void setup() {
  Serial.begin(115200);
  vr.begin();
}

void loop() {
  int value = vr.read();
  Serial.println(value); // 0-4095 on ESP32
  delay(200);
}
```

### Example 2: Read as Percentage

```cpp
void loop() {
  int percent = vr.readPercent();
  Serial.print(percent);
  Serial.println("%");
  delay(200);
}
```

### Example 3: LED Brightness Control (PWM) - ESP32 Core 3.x

```cpp
#include <PotentiometerController.h>

PotentiometerController vr(34);
const int ledPin = 2;

// PWM configuration
const int pwmFreq = 5000;
const int pwmResolution = 8;

void setup() {
  vr.begin();
  
  // ESP32 Core 3.x API
  ledcAttach(ledPin, pwmFreq, pwmResolution);
}

void loop() {
  int brightness = vr.readMapped(0, 255);
  ledcWrite(ledPin, brightness);
  delay(50);
}
```

### Example 4: Dual LED Control (ESP32 Core 3.x)

```cpp
const int LED1_PIN = 2;
const int LED2_PIN = 4;

void setup() {
  vr.begin();
  
  // Setup two PWM pins
  ledcAttach(LED1_PIN, 5000, 8);
  ledcAttach(LED2_PIN, 5000, 8);
}

void loop() {
  int pwm1 = vr.readMapped(0, 255);  // Normal
  int pwm2 = 255 - pwm1;             // Inverted
  
  ledcWrite(LED1_PIN, pwm1);
  ledcWrite(LED2_PIN, pwm2);
  delay(50);
}
```

## API Reference

| Method | Description | Returns |
|--------|-------------|---------|
| `PotentiometerController(pin)` | Constructor with ADC pin | - |
| `void begin()` | Initialize (optional on most platforms) | - |
| `int read()` | Read raw ADC value | 0-4095 (ESP32) or 0-1023 (Arduino) |
| `int readPercent()` | Read as percentage | 0-100 |
| `int readMapped(min, max)` | Read and map to custom range | min to max |
| `int getRaw()` | Get last raw value without reading | Last value |
| `int getMaxRaw()` | Get ADC resolution | 4095 or 1023 |

## Understanding PWM (Pulse Width Modulation)

PWM creates the illusion of variable brightness by rapidly turning the LED **on and off**.

### PWM Concepts

```
Duty Cycle 0% (OFF):     ___________________________
                         
Duty Cycle 25%:          ▄▄▄_______▄▄▄_______▄▄▄___
                         
Duty Cycle 50%:          ▄▄▄▄▄▄____▄▄▄▄▄▄____▄▄▄▄▄▄
                         
Duty Cycle 100% (ON):    ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
```

### PWM on ESP32 (Core 3.x)

ESP32 uses `ledc` (LED Control) functions with simplified API in Core 3.x:

```cpp
// Setup PWM on a pin (replaces ledcSetup + ledcAttachPin)
ledcAttach(pin, frequency, resolution);

// Write PWM value
ledcWrite(pin, dutyCycle);

// Detach (optional cleanup)
ledcDetach(pin);
```

| Resolution | Range | Example |
|------------|-------|---------|
| 8-bit | 0-255 | `ledcWrite(2, 128)` = 50% brightness |
| 10-bit | 0-1023 | `ledcWrite(2, 512)` = 50% brightness |
| 12-bit | 0-4095 | `ledcWrite(2, 2048)` = 50% brightness |

**Note:** Pin number is now used directly instead of channel numbers.

## Examples

### 1. Basic Reading
Read and display raw ADC value and percentage.

**Hardware**: VR on GPIO 34

**Skills**: analogRead(), map()

### 2. LED Brightness
Control LED brightness with VR using PWM.

**Hardware**: VR on GPIO 34, LED on GPIO 2

**Skills**: PWM, ledcWrite(), analog-to-PWM conversion

### 3. Dual LED Control
Two LEDs with normal and inverted brightness.

**Hardware**: VR on GPIO 34, LED1 on GPIO 2, LED2 on GPIO 4

**Skills**: Multiple PWM channels, inverted mapping

### 4. Running Light Speed
Control running light speed with VR.

**Hardware**: VR on GPIO 34, 4 LEDs on GPIO 2, 4, 5, 18

**Skills**: Combining concepts, timing control

## Key Functions Summary

| Function | Purpose | Example |
|----------|---------|---------|
| `analogRead(pin)` | Read ADC value | `int x = analogRead(34);` // 0-4095 |
| `map(val, in_min, in_max, out_min, out_max)` | Convert value range | `map(raw, 0, 4095, 0, 255);` |
| `ledcAttach(pin, freq, res)` | Setup PWM on pin (Core 3.x) | `ledcAttach(2, 5000, 8);` |
| `ledcWrite(pin, val)` | Write PWM value (Core 3.x) | `ledcWrite(2, 128);` |
| `ledcDetach(pin)` | Detach PWM from pin | `ledcDetach(2);` |

### Legacy Functions (Core 2.x - Deprecated)

| Function | Replaced By |
|----------|-------------|
| `ledcSetup(ch, freq, res)` | `ledcAttach(pin, freq, res)` |
| `ledcAttachPin(pin, ch)` | Integrated into `ledcAttach()` |
| `ledcWrite(ch, val)` | `ledcWrite(pin, val)` |

## Practical Applications

- 🎚️ Volume control knob
- 💡 Brightness dimmer
- 🌡️ Manual setpoint adjustment
- 🏎️ Speed control for motors
- 📊 Manual calibration interface

## Troubleshooting

| Problem | Solution |
|---------|----------|
| Values always 0 or max | Check VR connections (pin 1 = 3.3V, pin 3 = GND) |
| Noisy/jittery readings | Add smoothing (average multiple readings) |
| ESP32 won't boot | Don't use GPIO 0, 2, 12, 15 for ADC |
| Wrong voltage range | Ensure using 3.3V, NOT 5V on ESP32 |
| `ledcSetup` not declared | Update to ESP32 Core 3.x or use new `ledcAttach()` API |
| PWM not working | Check pin supports PWM output (most ESP32 pins do) |

### ESP32 Core Version Issues

**Error:** `'ledcSetup' was not declared in this scope`

**Solution:**
1. **Update to Core 3.x** (recommended): Tools > Board > Boards Manager > Update esp32
2. **Use new API**: Replace `ledcSetup()`/`ledcAttachPin()` with `ledcAttach()`

**Error:** `'ledcAttach' was not declared in this scope`

**Solution:** You're using Core 2.x - either update to Core 3.x or use old API (not recommended)

## Advanced: Reading Smoothing

For stable readings, average multiple samples:

```cpp
int smoothRead(int samples = 10) {
  long sum = 0;
  for (int i = 0; i < samples; i++) {
    sum += analogRead(pin);
    delay(5);
  }
  return sum / samples;
}
```

## Safety Notes

- ⚠️ **Never exceed 3.3V** on ESP32 ADC pins (can damage chip)
- ✅ Use voltage dividers if measuring higher voltages
- ✅ Always check polarity before connecting

## Related Libraries

- [LEDController](../LEDController/) - LED control with blinking
- [Button](../Button/) - Debounced button input
- [RelayController](../RelayController/) - Relay control

## License

MIT License
