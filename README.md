# 🕒 Arduino Real-Time Clock with Alarm

A comprehensive real-time clock (RTC) and alarm system built with an Arduino. This project displays the current date and time on an I2C LCD, allows for easy time and alarm configuration via navigation buttons, and triggers a buzzer at the set alarm time.

## 🌟 About The Project

This project serves as a practical and interactive timekeeping device. It's designed to be a standalone unit that not only tells you the precise time and date but also helps you set alarms for important reminders. The user-friendly menu system, navigated with five push buttons, makes it simple to adjust the system time or configure a specific alarm down to the second.

### ✨ Key Features

* **Real-Time Clock:** Displays the current year, month, day, hour, minute, and second.
* **Manual Time Setting:** Easily adjust the system date and time using the onboard navigation buttons.
* **Alarm Functionality:** Set a precise alarm for a specific date and time.
* **Audible Alert:** A buzzer activates when the alarm time is reached.
* **Alarm Control:** Manually stop the alarm with the press of a button or let it auto-stop after one minute.

---

## 🛠️ Built With

This project relies on the following hardware components and Arduino libraries.

### 📦 Components Required
* Arduino (Uno, Nano, Pro Mini, etc.)
* DS3231 RTC Module
* 20x4 I2C LCD Display (Address: `0x27`)
* 5 x Push Buttons
* Buzzer
* Jumper Wires & Breadboard

### 📚 Libraries Used
* [`LiquidCrystal_I2C`](https://github.com/johnrickman/LiquidCrystal_I2C)
* [`DS3231`](https://github.com/NorthernWidget/DS3231)

---

## 🚀 Getting Started

Follow these steps to get your Arduino Timekeeper up and running.

### 1. Prerequisites
Ensure you have the Arduino IDE installed on your computer. If not, [download it here](https://www.arduino.cc/en/software).

### 2. Wiring
Connect the components according to the pin configuration below:

| Component         | Arduino Pin |
| ----------------- | ----------- |
| **I2C LCD** - SDA | `A4`        |
| **I2C LCD** - SCL | `A5`        |
| **UP** Button     | `D3`        |
| **DOWN** Button   | `D5`        |
| **RIGHT** Button  | `D4`        |
| **LEFT** Button   | `D2`        |
| **MENU** Button   | `D6`        |
| **Buzzer** | `D7`        |

### 3. Installation
1.  **Install Libraries:** Open the Arduino IDE, go to **Sketch > Include Library > Manage Libraries...**, and install `LiquidCrystal_I2C` and `DS3231`.
2.  **Upload Sketch:** Open the project sketch file (`.ino`) in the Arduino IDE.
3.  **Set Initial Time:** Before uploading, you can set the initial time and date within the `setup()` function of the code.
    ```cpp
    // Example: Set time to May 18, 2024, 06:56:00
    RTC.setYear(24);
    RTC.setMonth(5);
    RTC.setDate(18);
    RTC.setHour(6);
    RTC.setMinute(56);
    RTC.setSecond(0);
    ```
4.  **Upload:** Connect your Arduino to the computer and upload the sketch.

---

## 📖 Usage

The system is controlled using the five navigation buttons.

* **MENU Button (`D6`):** Press to enter the mode for adjusting the system's current time and date. Use the **UP**/**DOWN** buttons to change values and **LEFT**/**RIGHT** to move between fields.
* **RIGHT or LEFT Button (`D4`/`D2`):** Press from the main screen to enter the alarm setting mode.
* **UP/DOWN Buttons (`D3`/`D5`):** Use these to increment or decrement the selected value (e.g., hour, minute, day).

### Alarm Control
When an alarm is triggered, the buzzer will sound.
* **Stop Manually:** Press the **RIGHT** or **LEFT** button to silence the alarm immediately.
* **Auto-Stop:** If no button is pressed, the alarm will automatically stop after one minute.

---


## 📜 License
This project is open-source and available under the **MIT License**.  
Feel free to modify and improve it for your own projects!
