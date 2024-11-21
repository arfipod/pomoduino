
# Pomoduino
## Description

Pomoduino is an **Arduino-based Pomodoro Timer** utilizing an **Arduino UNO**. The timer features two modes:

- **Work:** 35 minutes
- **Break:** 10 minutes

Equipped with two **TM1637 displays**, a rotary encoder with a button, and two indicator LEDs (red and green), Pomoduino allows seamless switching between work and break periods. It automatically initiates the next timer upon completion of the current one or allows manual switching by pressing the encoder button during a countdown.

## Features

- **Dual Timer:** Switches between a 35-minute work timer and a 10-minute break timer.
- **User-Friendly Interface:** Utilizes a rotary encoder to start, pause, and switch between modes.
- **Visual Indicators:** Red and green LEDs indicate the current timer mode.
- **Clear Displays:** Two TM1637 displays show the remaining time in MM:SS format.
- **Blinking Display Functionality:** Upon timer completion, the corresponding display blinks until the encoder button is pressed to start the next timer.

## Required Components

- **Arduino UNO**
- **2x TM1637 Displays**
- **Rotary Encoder with Button**
- **2x LEDs (Red and Green)**
- **330Ω Resistors (for LEDs)**
- **10kΩ Resistors (if using external resistors for the encoder)**
- **Breadboard and Connecting Wires**
- **Power Supply for Arduino**

## Circuit Diagram

- TO DO

**Main Connections:**

- **TM1637 Displays:**
  - **Display 1 (Break - 10 minutes):**
    - CLK → Arduino Pin 4
    - DIO → Arduino Pin 5
    - VCC → 5V Arduino
    - GND → GND Arduino
  - **Display 2 (Work - 35 minutes):**
    - CLK → Arduino Pin 6
    - DIO → Arduino Pin 7
    - VCC → 5V Arduino
    - GND → GND Arduino

- **Rotary Encoder:**
  - CLK → Arduino Pin 2
  - DT → Arduino Pin 3
  - SW (Button) → Arduino Pin 8
  - VCC → 5V Arduino
  - GND → GND Arduino

- **LEDs:**
  - **Red LED:**
    - Anode → Arduino Pin 9
    - Cathode → 330Ω Resistor → GND
  - **Green LED:**
    - Anode → Arduino Pin 10
    - Cathode → 330Ω Resistor → GND

- **Additional Pin:**
  - Pin 12 configured as an additional GND (optional for extra components).

## Installation

### Prerequisites

- **PlatformIO:** It is recommended to use [PlatformIO](https://platformio.org/) as the development environment.
- **TM1637 Library:** Ensure the TM1637 library is installed. PlatformIO will automatically handle dependencies specified in `platformio.ini`.

### Clone the Repository

```bash
git clone https://github.com/arfipod/pomoduino.git
cd pomoduino
```

### Compile and Upload the Code

1. Open the project in your preferred code editor (Visual Studio Code with PlatformIO is recommended).
2. Connect your Arduino UNO to the computer.
3. Select the appropriate build environment (`uno` in this case).
4. Compile the project:
   ```bash
   pio run
   ```
5. Upload the firmware to the Arduino:
   ```bash
   pio run --target upload
   ```

## Usage

1. **Starting the Timer:**
   - Upon powering up, the timer is in the `IDLE` state, displaying 35:00 on **Display 2** (Work) and 10:00 on **Display 1** (Break).
   - Press the encoder button to start the work timer (35 minutes). The red LED will light up, and **Display 2** will begin counting down.

2. **Switching Timers:**
   - During an active countdown, pressing the encoder button will reset the current timer and start the other timer (switching between work and break).
   - Upon timer completion, the corresponding display will blink until the encoder button is pressed to initiate the next timer.

3. **Visual Indicators:**
   - **Red LED:** Indicates that the work timer is active.
   - **Green LED:** Indicates that the break timer is active.

## Project Structure

```
/pomoduino
│
├── src
│   ├── main.cpp
│   ├── DisplayModule.h
│   ├── DisplayModule.cpp
│   ├── EncoderModule.h
│   ├── EncoderModule.cpp
│   ├── LEDModule.h
│   ├── LEDModule.cpp
│   ├── TimerModule.h
│   ├── TimerModule.cpp
│   ├── Controller.h
│   └── Controller.cpp
│
├── lib
│   └── TM1637Display
│       ├── TM1637Display.h
│       └── TM1637Display.cpp
│
├── images
│   ├── pomodoro_timer.jpg
│   └── circuit_diagram.png
│
└── platformio.ini
```

### File Descriptions

- **main.cpp:** Entry point of the program. Initializes and runs the main logic.
- **DisplayModule.h/cpp:** Class to handle TM1637 displays.
- **EncoderModule.h/cpp:** Class to handle the rotary encoder and its button.
- **LEDModule.h/cpp:** Class to control the indicator LEDs.
- **TimerModule.h/cpp:** Class to manage work and break timers.
- **Controller.h/cpp:** Central class that coordinates all modules and manages Pomodoro timer states.
- **platformio.ini:** Project configuration for PlatformIO, including dependencies and build environment.
- **lib/TM1637Display:** Library for handling TM1637 displays.
- **images/:** Folder to store project images (circuit diagrams, photos, etc.).

## Contributing

Contributions are welcome! If you wish to enhance this project, please follow these steps:

1. Fork the repository.
2. Create a new branch for your feature (`git checkout -b feature/new-feature`).
3. Make your changes and commit them (`git commit -am 'Add new feature'`).
4. Push to the branch (`git push origin feature/new-feature`).
5. Open a pull request.

## License

This project is licensed under the MIT License. See the [LICENSE](https://github.com/arfipod/pomoduino/blob/main/LICENSE) file for details.

## Contact

If you have any questions or suggestions, feel free to contact me:

- **Name:** Ángel R. Rubio Fernández
- **Email:** arfipod@gmail.com
- **GitHub:** [arfipod](https://github.com/arfipod)

---
