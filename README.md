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

## ⚠️ Important: ESP32 Core 3.x Compatibility

### Breaking Changes

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

Most examples are designed for:
- **ESP32** (recommended - ICON-32 or ESP32 Dev Module)
- Arduino Uno/Nano (limited features, no FreeRTOS)

### Recommended Starter Kit Components

- ESP32 development board
- Breadboard and jumper wires
- LEDs (various colors) + 220Ω resistors
- Push buttons
- DHT11 or DHT22 temperature sensor
- Potentiometer (10kΩ)
- 4-digit 7-segment display
- Relay module (5V)
- Transistors (2N2222 or similar)

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

**Micro-Docs Library Collection**
Version: 2025.11
Last Updated: November 18, 2025
Compatible with: ESP32 Arduino Core 3.x
