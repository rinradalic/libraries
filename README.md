# Arduino Libraries Collection - Micro-Docs

Educational Arduino/ESP32 libraries for hands-on learning and production projects.

## 📚 Library Collection

This workspace contains professionally structured Arduino libraries designed for educational use and real-world projects:

### Core Libraries

1. **Button** - Advanced button handling with debounce and click detection
   - Hardware and software debouncing
   - Single/double/long click detection
   - Interrupt-based examples
   - Perfect for user input interfaces

2. **LEDController** - Comprehensive LED control
   - Blinking patterns
   - State machine integration
   - Multiple LED coordination
   - Status indicators

3. **PotentiometerController** - Analog input management
   - VR (Variable Resistor) reading
   - PWM brightness control
   - Percentage and custom range mapping
   - **Updated for ESP32 Core 3.x**

4. **RelayController** - High-power device control
   - Safe relay switching
   - Temperature-based automation
   - Button integration examples
   - Industrial applications

5. **TemperatureSensor** - DHT11/DHT22 sensor wrapper
   - Simple temperature/humidity reading
   - Hysteresis control for smart fans
   - Manual override capabilities
   - Production-ready examples

6. **DigitalLogic** - 7-segment displays and logic circuits
   - Single and multiplexed displays
   - Binary counters (7493 IC)
   - Clock generators
   - Digital clock implementations

### Advanced Examples (FreeRTOS)

Located in `examples/` folder - demonstrates multi-tasking on ESP32:

- **FreeRTOS_MultiTask_Basic** - Introduction to Tasks
- **FreeRTOS_TempDisplay** - Temperature display with threshold monitoring
- **FreeRTOS_SmartController** - Complete integration project (6 tasks)

All FreeRTOS examples include proper error handling and are compatible with ESP32 Core 3.x.

## ⚠️ Important Platform Notes

### Arduino Board Compatibility

**All core libraries work on all Arduino board families** with these considerations:

#### PWM on Arduino Boards
Use `analogWrite()` instead of ESP32's `ledcAttach()`:

**Arduino Boards (UNO/Nano/Mega/MKR/Due) Code:**
```cpp
// Setup
pinMode(LED_PIN, OUTPUT);

// Control brightness
int brightness = vr.readMapped(0, 255);
analogWrite(LED_PIN, brightness); // See PWM pin table above
```

**Note:** Check PWM pin availability for your specific board in the table above.

**ESP32 Code (Core 3.x):**
```cpp
// Setup
ledcAttach(LED_PIN, 5000, 8);

// Control brightness
int brightness = vr.readMapped(0, 255);
ledcWrite(LED_PIN, brightness);
```

#### ADC Resolution Differences

| Board Family | ADC Resolution | Range | Auto-detected by Library |
|--------------|----------------|-------|-------------------------|
| UNO R3, Nano, Mega, Leonardo | 10-bit | 0-1023 | ✅ Yes |
| UNO R4 | 14-bit | 0-16383 | ⚠️ Mapped to 10-bit |
| Nano Every | 10-bit | 0-1023 | ✅ Yes |
| Nano 33 IoT/BLE | 12-bit | 0-4095 | ⚠️ Default 10-bit |
| MKR Family | 12-bit | 0-4095 | ⚠️ Default 10-bit |
| Due | 12-bit | 0-4095 | ⚠️ Default 10-bit |
| ESP32 | 12-bit | 0-4095 | ✅ Yes |

**Note:** `PotentiometerController` auto-detects ESP32 vs others. SAMD boards (MKR, Nano 33, Due) default to 10-bit but can be configured for 12-bit using `analogReadResolution(12)`.

#### FreeRTOS Multi-tasking
- **All Arduino boards (UNO/Nano/Mega/MKR/Due/Leonardo):** ❌ Not supported - use traditional single-loop programming
- **Nano ESP32:** ✅ Supported (has ESP32-S3)
- **ESP32 boards:** ✅ Fully supported - see `examples/FreeRTOS_*`

**Note:** Only ESP32-based boards have built-in FreeRTOS support.

### ESP32 Core 3.x Compatibility

If you're using **ESP32 Arduino Core 3.x**, note these API changes:

#### PWM Functions (ledcXXX)

**Old API (Core 2.x) - DEPRECATED:**
```cpp
ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
ledcAttachPin(LED_PIN, PWM_CHANNEL);
ledcWrite(PWM_CHANNEL, pwmValue);
```

**New API (Core 3.x) - CURRENT:**
```cpp
ledcAttach(LED_PIN, PWM_FREQ, PWM_RESOLUTION);
ledcWrite(LED_PIN, pwmValue);
```

### Updated Libraries

✅ **PotentiometerController** - All PWM examples updated
✅ **FreeRTOS examples** - Task creation includes error handling

### Check Your Core Version

Arduino IDE: Tools > Board > Boards Manager > Search "esp32"
- Version 3.x.x → Use new API
- Version 2.x.x → Use old API (deprecated, consider updating)

## 🚀 Quick Start

### Installation

1. **Clone or copy** this repository to your Arduino libraries folder:
   ```bash
   cp -r /path/to/libraries ~/Arduino/libraries/
   ```

2. **Restart Arduino IDE** to detect the new libraries

3. **Open examples**: File > Examples > [Library Name]

### Hardware Requirements

#### Fully Supported Platforms

**Arduino UNO Family:**
- ✅ Arduino Uno R3 (ATmega328P)
- ✅ Arduino Uno R4 Minima (Renesas RA4M1)
- ✅ Arduino Uno R4 WiFi (Renesas RA4M1 + ESP32-S3)
- ✅ Arduino Uno WiFi Rev2 (ATmega4809)

**Arduino Nano Family:**
- ✅ Arduino Nano (ATmega328P)
- ✅ Arduino Nano Every (ATmega4809)
- ✅ Arduino Nano 33 IoT (SAMD21 + Nina W102)
- ✅ Arduino Nano 33 BLE / BLE Sense (nRF52840)
- ✅ Arduino Nano RP2040 Connect (RP2040 + Nina W102)
- ✅ Arduino Nano ESP32 (ESP32-S3)

**Arduino Mega Family:**
- ✅ Arduino Mega 2560 (ATmega2560)
- ✅ Arduino Mega ADK (ATmega2560)

**Arduino MKR Family:**
- ✅ Arduino MKR Zero (SAMD21)
- ✅ Arduino MKR WiFi 1010 (SAMD21 + Nina W102)
- ✅ Arduino MKR FOX 1200 (SAMD21)
- ✅ Arduino MKR WAN 1300/1310 (SAMD21)
- ✅ Arduino MKR GSM 1400 (SAMD21)
- ✅ Arduino MKR NB 1500 (SAMD21)
- ✅ Arduino MKR Vidor 4000 (SAMD21 + FPGA)

**Other Arduino Boards:**
- ✅ Arduino Leonardo (ATmega32U4)
- ✅ Arduino Micro (ATmega32U4)
- ✅ Arduino Due (SAM3X8E ARM Cortex-M3)

**ESP32 Boards:**
- ✅ ESP32 (ICON-32, Dev Module, WROOM, WROVER)
- ✅ ESP32-S2, ESP32-S3, ESP32-C3

#### Platform-Specific Features

| Library | UNO/Nano/Mega | MKR Family | ESP32 | Notes |
|---------|---------------|------------|-------|-------|
| Button | ✅ Full | ✅ Full | ✅ Full | Universal compatibility |
| LEDController | ✅ Full | ✅ Full | ✅ Full | Universal compatibility |
| RelayController | ✅ Full | ⚠️ 3.3V* | ✅ Full | *MKR needs 3.3V relay |
| DigitalLogic | ✅ Full | ✅ Full | ✅ Full | Universal compatibility |
| TemperatureSensor | ✅ Full | ✅ Full | ✅ Full | Universal compatibility |
| PotentiometerController | ⚠️ PWM** | ⚠️ PWM** | ✅ Full | **See PWM notes below |
| FreeRTOS Examples | ❌ N/A | ❌ N/A | ✅ Full | ESP32 exclusive |

**PWM Notes:**

| Board Family | PWM Method | PWM Pins | Resolution |
|--------------|------------|----------|------------|
| **UNO R3** | `analogWrite()` | 3, 5, 6, 9, 10, 11 | 8-bit (0-255) |
| **UNO R4** | `analogWrite()` | D3-D6, D9-D11 | 8-bit (0-255) |
| **Nano (328P)** | `analogWrite()` | 3, 5, 6, 9, 10, 11 | 8-bit (0-255) |
| **Nano Every** | `analogWrite()` | 3, 5, 6, 9, 10 | 8-bit (0-255) |
| **Nano 33 IoT** | `analogWrite()` | 2, 3, 5, 6, 9-13, A2, A3, A5 | 8-bit (0-255) |
| **Nano 33 BLE** | `analogWrite()` | All digital pins | 8-bit (0-255) |
| **Nano ESP32** | `ledcAttach()` | All GPIO | 1-16 bit |
| **Mega 2560** | `analogWrite()` | 2-13, 44-46 | 8-bit (0-255) |
| **MKR Family** | `analogWrite()` | 0-8, 10, A3, A4 | 8-bit (0-255) |
| **Leonardo** | `analogWrite()` | 3, 5, 6, 9, 10, 11, 13 | 8-bit (0-255) |
| **Due** | `analogWrite()` | 2-13 | 8-bit (0-255) |
| **ESP32** | `ledcAttach()` | All GPIO | 1-16 bit |

- ESP32 examples use `ledcAttach()` - needs code adjustment for Arduino boards
- See PotentiometerController README for platform-specific code examples

### Recommended Starter Kit Components

**For 5V Arduino Boards (UNO, Nano, Mega, Leonardo):**
- Arduino board (UNO R3/R4, Nano, Mega 2560, etc.)
- Breadboard and jumper wires
- LEDs (various colors) + 220Ω resistors
- Push buttons + 10kΩ pull-down resistors (or use INPUT_PULLUP)
- DHT11 or DHT22 temperature sensor
- Potentiometer (10kΩ)
- 4-digit 7-segment display (Common Cathode)
- Relay module (5V with optocoupler)
- Transistors (2N2222 or BC547)

**For 3.3V Arduino Boards (MKR Family, Nano 33 IoT/BLE, Due):**
- Arduino board (MKR WiFi 1010, Nano 33 IoT, etc.)
- Breadboard and jumper wires
- LEDs (various colors) + 220Ω resistors
- Push buttons (INPUT_PULLUP recommended)
- DHT11 or DHT22 temperature sensor
- Potentiometer (10kΩ)
- 4-digit 7-segment display (Common Cathode)
- Relay module (3.3V or use level shifter for 5V relay)
- Transistors (2N2222 or BC547)

**For ESP32:**
- ESP32 development board (ICON-32 recommended)
- Breadboard and jumper wires
- LEDs (various colors) + 220Ω resistors
- Push buttons (INPUT_PULLUP recommended)
- DHT11 or DHT22 temperature sensor
- Potentiometer (10kΩ)
- 4-digit 7-segment display (Common Cathode)
- Relay module (3.3V or 5V with level shifter)
- Transistors (2N2222 or similar)

**⚠️ Voltage Compatibility:**

| Board Family | Logic Voltage | ADC Voltage | Notes |
|--------------|---------------|-------------|-------|
| UNO R3, Nano, Mega, Leonardo | 5V | 5V max | Use 5V components |
| UNO R4 | 5V | 5V max | Modern architecture |
| MKR Family | 3.3V | 3.3V max | ⚠️ NOT 5V tolerant |
| Nano 33 IoT/BLE | 3.3V | 3.3V max | ⚠️ NOT 5V tolerant |
| Due | 3.3V | 3.3V max | ⚠️ NOT 5V tolerant |
| ESP32 | 3.3V | 3.3V max | Some pins 5V tolerant |

**Important:** Always check your board's voltage specifications before connecting sensors!

## 📖 Documentation

Each library includes:
- **README.md** - Theory, API reference, examples
- **keywords.txt** - Syntax highlighting
- **library.properties** - Metadata
- **examples/** - Working code with detailed comments

### Learning Path

**Beginner:**
1. LEDController - Basic digital output
2. Button - Digital input with debouncing
3. PotentiometerController - Analog input

**Intermediate:**
4. TemperatureSensor - Sensor integration
5. RelayController - High-power control
6. DigitalLogic - Multiplexing and timing

**Advanced:**
7. FreeRTOS examples - Multi-tasking systems
8. Integration projects - Combining multiple libraries

## 🔧 Production Readiness

### Recent Updates (2025-11-18)

✅ **ESP32 Core 3.x compatibility** - All PWM code updated
✅ **FreeRTOS error handling** - All task creations now check for failures
✅ **Improved documentation** - Core 3.x migration guide added

### Known Issues & Solutions

#### DHT Sensor Libraries

This workspace may contain **two** DHT libraries:
- `DFRobot_DHT11`
- `DHT_sensor_library` (Adafruit)

**Recommendation:** Use Adafruit's DHT library for better compatibility.

#### Compilation Errors

**Error:** `'ledcSetup' was not declared in this scope`
**Solution:** Update to ESP32 Core 3.x, or check PotentiometerController README for migration guide

**Error:** `Failed to create Task[Name]!`
**Solution:** Insufficient memory or invalid task parameters - check Serial output for details

## 🎓 For Educators

These libraries are designed for classroom use:
- **Clear documentation** in both English and Thai
- **Progressive difficulty** from basic to advanced
- **Real-world applications** to maintain engagement
- **Safety notes** included in all examples
- **Teaching guides** in FreeRTOS examples README

### Suggested Curriculum

**Week 1-2:** Digital I/O (LEDController, Button)
**Week 3-4:** Analog I/O (PotentiometerController)
**Week 5-6:** Sensors (TemperatureSensor, RelayController)
**Week 7-8:** Displays (DigitalLogic)
**Week 9-10:** Multi-tasking (FreeRTOS examples)
**Week 11-12:** Final project (Integration)

## 🤝 Contributing

These libraries are maintained for educational purposes. If you find issues:
1. Document the problem clearly
2. Include hardware setup and code
3. Note your ESP32 Core version
4. Submit via your preferred method

## 📄 License

MIT License - Free for educational and commercial use.

## 🔗 Related Resources

- Arduino official documentation: https://www.arduino.cc/reference/
- ESP32 documentation: https://docs.espressif.com/
- FreeRTOS documentation: https://www.freertos.org/

## 📧 Support

For installation help: http://www.arduino.cc/en/Guide/Libraries

---

## 📊 Quick Reference: Board Specifications

### Voltage & ADC Specifications

| Board Family | Logic Voltage | ADC Pins | ADC Resolution | ADC Range | PWM Pins |
|--------------|---------------|----------|----------------|-----------|----------|
| **UNO R3** | 5V | A0-A5 (6) | 10-bit | 0-1023 | 6 pins |
| **UNO R4** | 5V | A0-A5 (6) | 14-bit* | 0-16383 | 7 pins |
| **Nano (328P)** | 5V | A0-A7 (8) | 10-bit | 0-1023 | 6 pins |
| **Nano Every** | 5V | A0-A7 (8) | 10-bit | 0-1023 | 5 pins |
| **Nano 33 IoT** | 3.3V ⚠️ | A0-A7 (8) | 12-bit** | 0-4095 | 11 pins |
| **Nano 33 BLE** | 3.3V ⚠️ | A0-A7 (8) | 12-bit** | 0-4095 | All pins |
| **Nano ESP32*** | 3.3V | Many GPIO | 12-bit | 0-4095 | All GPIO |
| **Mega 2560** | 5V | A0-A15 (16) | 10-bit | 0-1023 | 15 pins |
| **MKR Family** | 3.3V ⚠️ | A0-A6 (7) | 12-bit** | 0-4095 | 13 pins |
| **Leonardo** | 5V | A0-A11 (12) | 10-bit | 0-1023 | 7 pins |
| **Due** | 3.3V ⚠️ | A0-A11 (12) | 12-bit** | 0-4095 | 12 pins |
| **ESP32** | 3.3V | Many GPIO | 12-bit | 0-4095 | All GPIO |

*UNO R4: 14-bit ADC mapped to 10-bit by Arduino core (library auto-detects)  
**SAMD boards: Default 10-bit, use `analogReadResolution(12)` for 12-bit  
***Nano ESP32: Uses ESP32-S3, same as regular ESP32  
⚠️ **NOT 5V TOLERANT** - permanent damage if 5V applied!

### 5V vs 3.3V Board Quick Check

**✅ 5V Boards (can use 5V sensors/components):**
- Arduino UNO R3, R4, WiFi Rev2
- Arduino Nano (ATmega328P), Nano Every
- Arduino Mega 2560
- Arduino Leonardo, Micro

**⚠️ 3.3V Boards (use 3.3V sensors ONLY, NOT 5V tolerant):**
- Arduino MKR Family (all variants)
- Arduino Nano 33 IoT
- Arduino Nano 33 BLE / BLE Sense
- Arduino Nano RP2040 Connect
- Arduino Nano ESP32
- Arduino Due
- ESP32 (all variants)

---

**Micro-Docs Library Collection**
Version: 2025.11
Last Updated: November 18, 2025
Compatible with: All Arduino boards + ESP32 Arduino Core 3.x
