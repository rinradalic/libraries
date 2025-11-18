# PotentiometerController

Analog input library for reading potentiometers (VR - Variable Resistor) on ESP32/Arduino. Designed for Analog Control with VR.

## Features

- ✅ Simple ADC reading with automatic platform detection
- ✅ Built-in percentage conversion (0-100%)
- ✅ Custom range mapping
- ✅ Support for all Arduino board families (UNO, Nano, Mega, MKR, Due, Leonardo)
- ✅ Support for ESP32 (12-bit) with auto-detection
- ✅ Examples for all major platforms
- ✅ PWM LED control examples for both Arduino and ESP32

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
┌────────────┌
│ 3.3V ──────├──► VR Pin 1
│            │
│ GPIO 34 ───├──► VR Pin 2 (Wiper)
│ (ADC)      │
│            │
│ GND ───────├──► VR Pin 3
└────────────┘
```

### Recommended ADC Pins (ESP32)

- ✅ GPIO 34, 35, 36, 39 (Input only, ideal for ADC)
- ✅ GPIO 32, 33, 25, 26, 27 (Can be input/output, also work)
- ⚠️ Avoid GPIO 0, 2, 12, 15 (boot pins)

## Hardware Connection (5V Arduino Boards)

### UNO R3/R4, Nano, Mega, Leonardo - Can use 5V

```
Arduino (5V)
┌────────────┌
│ 5V ────────├──► VR Pin 1
│            │
│ A0 ────────├──► VR Pin 2 (Wiper)
│ (ADC)      │
│            │
│ GND ───────├──► VR Pin 3
└────────────┘
```

### Analog Pins by Board

| Board | Analog Input Pins | ADC Resolution |
|-------|-------------------|----------------|
| **Uno R3** | A0-A5 (6 pins) | 10-bit (0-1023) |
| **Uno R4** | A0-A5 (6 pins) | 14-bit (mapped to 10-bit) |
| **Nano** | A0-A7 (8 pins) | 10-bit (0-1023) |
| **Nano Every** | A0-A7 (8 pins) | 10-bit (0-1023) |
| **Mega 2560** | A0-A15 (16 pins) | 10-bit (0-1023) |
| **Leonardo** | A0-A5, A6-A11 (12 pins) | 10-bit (0-1023) |

## Hardware Connection (3.3V Arduino Boards)

### MKR Family, Nano 33 IoT/BLE, Due - Use 3.3V ONLY!

```
Arduino (3.3V)
┌────────────┌
│ 3.3V ──────├──► VR Pin 1  ⚠️ NOT 5V!
│            │
│ A0 ────────├──► VR Pin 2 (Wiper)
│ (ADC)      │
│            │
│ GND ───────├──► VR Pin 3
└────────────┘
```

### ⚠️ CRITICAL: 3.3V Boards

**These boards are NOT 5V tolerant:**
- MKR Family (all variants)
- Nano 33 IoT
- Nano 33 BLE / BLE Sense
- Arduino Due

**Connecting 5V to these boards can permanently damage them!**

### Analog Pins (3.3V Boards)

| Board | Analog Input Pins | ADC Resolution |
|-------|-------------------|----------------|
| **MKR Family** | A0-A6 (7 pins) | 12-bit (0-4095)* |
| **Nano 33 IoT** | A0-A7 (8 pins) | 12-bit (0-4095)* |
| **Nano 33 BLE** | A0-A7 (8 pins) | 12-bit (0-4095)* |
| **Due** | A0-A11 (12 pins) | 12-bit (0-4095)* |

*Default is 10-bit (0-1023). Use `analogReadResolution(12)` for full resolution.

### Recommended ADC Pins (ESP32)

- ✅ GPIO 34, 35, 36, 39 (Input only, ideal for ADC)
- ✅ GPIO 32, 33, 25, 26, 27 (Can be input/output, also work)
- ⚠️ Avoid GPIO 0, 2, 12, 15 (boot pins)

## Hardware Connection (Arduino Uno R3/R4)

### Can use 5V on Uno

```
Arduino Uno R3/R4
┌────────────┐
│ 5V ────────┼──► VR Pin 1
│            │
│ A0 ────────┼──► VR Pin 2 (Wiper)
│ (ADC)      │
│            │
│ GND ───────┼──► VR Pin 3
└────────────┘
```

### Analog Input Pins (Uno R3/R4)

- ✅ A0, A1, A2, A3, A4, A5 (all are ADC inputs)
- Note: Uno R3/R4 has 10-bit ADC (0-1023) vs ESP32's 12-bit (0-4095)

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

### Example 3b: LED Brightness Control - Arduino Uno R3/R4

```cpp
#include <PotentiometerController.h>

PotentiometerController vr(A0);  // Use analog pin A0
const int ledPin = 9;             // PWM pin (3,5,6,9,10,11)

void setup() {
  vr.begin();
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int brightness = vr.readMapped(0, 255);
  analogWrite(ledPin, brightness);  // Use standard analogWrite()
  delay(50);
}
```

**Key Differences:**
- Uno: Use `analogWrite()` on PWM pins (3, 5, 6, 9, 10, 11)
- ESP32: Use `ledcAttach()` / `ledcWrite()` on any GPIO

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

### Example 4b: Dual LED Control (Arduino Boards)

```cpp
#include <PotentiometerController.h>

PotentiometerController vr(A0);
const int LED1_PIN = 9;   // PWM pin
const int LED2_PIN = 10;  // PWM pin

void setup() {
  vr.begin();
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
}

void loop() {
  int pwm1 = vr.readMapped(0, 255);  // Normal
  int pwm2 = 255 - pwm1;             // Inverted
  
  analogWrite(LED1_PIN, pwm1);
  analogWrite(LED2_PIN, pwm2);
  delay(50);
}
```

**Note:** For MKR/Nano 33 IoT/BLE/Due, optionally use 12-bit ADC:
```cpp
void setup() {
  analogReadResolution(12);  // SAMD boards support 12-bit
  vr.begin();
  // ...
}

void loop() {
  int rawValue = analogRead(A0);  // 0-4095 on SAMD
  int pwm = map(rawValue, 0, 4095, 0, 255);
  analogWrite(LED1_PIN, pwm);
  // ...
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

### PWM on Arduino Uno R3/R4

Arduino uses `analogWrite()` on specific PWM pins:

```cpp
pinMode(pin, OUTPUT);
analogWrite(pin, dutyCycle);  // 0-255
```

#### PWM Pins by Arduino Board Family

| Board Family | PWM Pins | Count | Notes |
|--------------|----------|-------|-------|
| **Uno R3** | 3, 5, 6, 9, 10, 11 | 6 | Timer-based |
| **Uno R4 Minima/WiFi** | D3, D4, D5, D6, D9, D10, D11 | 7 | More capable |
| **Nano (328P)** | 3, 5, 6, 9, 10, 11 | 6 | Same as Uno R3 |
| **Nano Every** | 3, 5, 6, 9, 10 | 5 | Pin 11 not PWM |
| **Nano 33 IoT** | 2, 3, 5, 6, 9, 10, 11, 12, A2, A3, A5 | 11 | SAMD21 |
| **Nano 33 BLE** | All digital pins | 14 | nRF52840 |
| **Nano ESP32** | All GPIO | Many | Use `ledcAttach()` |
| **Mega 2560** | 2-13, 44-46 | 15 | Many options |
| **MKR Family** | 0-8, 10, A3, A4 | 13 | SAMD21 |
| **Leonardo/Micro** | 3, 5, 6, 9, 10, 11, 13 | 7 | ATmega32U4 |
| **Due** | 2-13 | 12 | ARM Cortex |

**Example for most Arduino boards:**
```cpp
const int LED_PIN = 9;  // Use appropriate PWM pin
pinMode(LED_PIN, OUTPUT);
analogWrite(LED_PIN, 128);  // 50% brightness
```

| Value | Brightness |
|-------|------------|
| 0 | Off |
| 64 | 25% |
| 128 | 50% |
| 192 | 75% |
| 255 | 100% (Full) |

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

**ESP32 Advantage:** Any GPIO can be PWM (except input-only pins 34-39)

**Note:** Pin number is now used directly instead of channel numbers.

## Examples

### 1. Basic Reading
Read and display raw ADC value and percentage.

**Hardware**: VR on GPIO 34 (ESP32), A0 (Arduino)

**Skills**: analogRead(), map()

**Compatible**: ✅ All Arduino boards (UNO, Nano, Mega, MKR, Leonardo, Due), ✅ ESP32

### 2. LED Brightness
Control LED brightness with VR using PWM.

**Hardware**: 
- ESP32: VR on GPIO 34, LED on GPIO 2
- UNO/Nano/Leonardo: VR on A0, LED on Pin 9
- Mega: VR on A0, LED on Pin 2-13
- MKR: VR on A0, LED on Pin 0-8

**Skills**: PWM, ledcWrite() (ESP32) or analogWrite() (Arduino), analog-to-PWM conversion

**Compatible**: ✅ All boards - see platform-specific code examples

### 3. Dual LED Control
Two LEDs with normal and inverted brightness.

**Hardware**: 
- ESP32: VR on GPIO 34, LEDs on GPIO 2, 4
- Arduino: VR on A0, LEDs on PWM pins (see PWM table)

**Skills**: Multiple PWM channels, inverted mapping

**Compatible**: ✅ All boards - use platform-appropriate PWM pins

### 4. Running Light Speed
Control running light speed with VR.

**Hardware**: VR on A0 (Arduino) or GPIO 34 (ESP32), 4 LEDs on any digital pins

**Skills**: Combining concepts, timing control

**Compatible**: ✅ All Arduino boards, ✅ ESP32

## Platform Comparison

| Feature | UNO R3 | UNO R4 | Nano | Nano Every | Nano 33 IoT/BLE | Mega 2560 | MKR Family | Leonardo | Due | ESP32 |
|---------|--------|--------|------|------------|-----------------|-----------|------------|----------|-----|-------|
| **Logic Voltage** | 5V | 5V | 5V | 5V | 3.3V | 5V | 3.3V | 5V | 3.3V | 3.3V |
| **ADC Resolution** | 10-bit | 14-bit* | 10-bit | 10-bit | 12-bit** | 10-bit | 12-bit** | 10-bit | 12-bit** | 12-bit |
| **ADC Range** | 0-1023 | 0-16383 | 0-1023 | 0-1023 | 0-4095 | 0-1023 | 0-4095 | 0-1023 | 0-4095 | 0-4095 |
| **ADC Pins** | 6 | 6 | 8 | 8 | 8 | 16 | 7 | 12 | 12 | Many |
| **PWM Method** | `analogWrite` | `analogWrite` | `analogWrite` | `analogWrite` | `analogWrite` | `analogWrite` | `analogWrite` | `analogWrite` | `analogWrite` | `ledcWrite` |
| **PWM Pins** | 6 pins | 6 pins | 6 pins | 5 pins | Many | 15 pins | 13 pins | 7 pins | 12 pins | All GPIO |
| **PWM Resolution** | 8-bit | 8-bit | 8-bit | 8-bit | 8-bit | 8-bit | 8-bit | 8-bit | 8-bit | 1-16 bit |
| **PWM Frequency** | ~490 Hz | ~490 Hz | ~490 Hz | ~490 Hz | ~732 Hz | ~490 Hz | ~732 Hz | ~490 Hz | 1 kHz | 1 Hz-40 MHz |
| **Library Support** | ✅ Full | ✅ Full | ✅ Full | ✅ Full | ✅ Full | ✅ Full | ✅ Full | ✅ Full | ✅ Full | ✅ Full |

*UNO R4 has 14-bit ADC but Arduino core maps it to 10-bit by default
**SAMD boards default to 10-bit, use `analogReadResolution(12)` for full 12-bit

## Key Functions Summary

### Library API (Platform Independent)

| Function | Purpose | Example |
|----------|---------|---------|
| `PotentiometerController(pin)` | Constructor | `PotentiometerController vr(A0);` |
| `void begin()` | Initialize | `vr.begin();` |
| `int read()` | Read raw ADC | `int val = vr.read();` |
| `int readPercent()` | Read as % | `int pct = vr.readPercent();` |
| `int readMapped(min, max)` | Map to range | `int pwm = vr.readMapped(0, 255);` |
| `int getRaw()` | Get last value | `int last = vr.getRaw();` |
| `int getMaxRaw()` | Get max ADC value | `int max = vr.getMaxRaw();` // 1023 or 4095 |

### Arduino Standard Functions

| Function | Purpose | Example |
|----------|---------|---------|
| `analogRead(pin)` | Read ADC value | `int x = analogRead(A0);` // 0-1023 on Uno |
| `map(val, in_min, in_max, out_min, out_max)` | Convert value range | `map(raw, 0, 1023, 0, 255);` |
| `analogWrite(pin, val)` | PWM output (Uno) | `analogWrite(9, 128);` // 50% brightness |

### ESP32 PWM Functions (Core 3.x)

| Function | Purpose | Example |
|----------|---------|---------|
| `ledcAttach(pin, freq, res)` | Setup PWM on pin | `ledcAttach(2, 5000, 8);` |
| `ledcWrite(pin, val)` | Write PWM value | `ledcWrite(2, 128);` |
| `ledcDetach(pin)` | Detach PWM from pin | `ledcDetach(2);` |

### Legacy ESP32 Functions (Core 2.x - Deprecated)

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
| Values always 0 or max | Check VR connections (Pin 1=VCC, Pin 3=GND, Pin 2=ADC) |
| Noisy/jittery readings | Add smoothing (average multiple readings) |
| Board won't boot | Check you're not using critical pins for ADC |
| Wrong voltage range | **5V boards:** Use 5V. **3.3V boards:** Use 3.3V ONLY! |
| PWM not working | Check pin supports PWM - see PWM pin table above |
| `ledcSetup` not declared (ESP32) | Update to ESP32 Core 3.x or use new `ledcAttach()` API |
| `ledcAttach` not declared (ESP32) | Using Core 2.x - update or use old API |
| MKR/Nano 33 damaged | Did you connect 5V? These boards are 3.3V only! |
| Low ADC resolution on SAMD | Use `analogReadResolution(12)` for full 12-bit |
| Uno R4 ADC seems wrong | R4 maps 14-bit to 10-bit by default - library handles this |

### Board-Specific Issues

**MKR Family / Nano 33 IoT / Nano 33 BLE / Due:**
- ⚠️ **NEVER connect 5V** to analog pins - use 3.3V only
- Default ADC is 10-bit; use `analogReadResolution(12)` for 12-bit
- PWM pins differ from Uno - check PWM pin table

**Uno R4:**
- Has 14-bit ADC but Arduino core defaults to 10-bit mode
- Library auto-detects and works correctly
- More PWM pins than Uno R3

**Mega 2560:**
- Has 16 analog inputs (A0-A15)
- 15 PWM pins available
- Fully compatible with library

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
