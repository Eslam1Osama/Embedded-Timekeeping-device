# 🕒 Arduino Timekeeper with Alarm

This project is a **Real-Time Clock (RTC) with alarm functionality** using an Arduino, DS3231 RTC module, I2C LCD display, navigation buttons, and a buzzer.  

It allows you to:
- Display current date & time on an LCD.
- Set and update system date/time.
- Configure alarms with year, month, day, hour, minute, and second.
- Trigger a buzzer when the alarm time is reached.

---

## 📦 Components Required
- Arduino (Uno/Nano/Pro Mini, etc.)
- DS3231 RTC Module
- I2C 20x4 LCD Display (address: `0x27`)
- Push Buttons (5x)  
  - **UP** → Pin `3`  
  - **DOWN** → Pin `5`  
  - **RIGHT** → Pin `4`  
  - **LEFT** → Pin `2`  
  - **MENU** → Pin `6`  
- Buzzer → Pin `7`
- Jumper Wires
- Breadboard / PCB

---

## 🔌 Pin Configuration

| Component | Pin |
|-----------|-----|
| LCD (I2C) | SDA → A4, SCL → A5 |
| UP Button | D3 |
| DOWN Button | D5 |
| RIGHT Button | D4 |
| LEFT Button | D2 |
| MENU Button | D6 |
| Buzzer | D7 |

---

## ⚙️ Features
- ✅ Displays **real-time clock (RTC)** data (Year, Month, Day, Hour, Minute, Second).  
- ✅ Allows **manual adjustment** of time and date using navigation buttons.  
- ✅ Supports **alarm configuration** with full date & time precision.  
- ✅ Activates buzzer when alarm triggers.  
- ✅ Alarm can be **stopped manually** with RIGHT or LEFT button.  
- ✅ Auto-stops after 1 minute if not manually dismissed.  

---

## 📖 Instructions for Use

### 1. Upload the Code
- Open Arduino IDE.
- Install required libraries:
  - `LiquidCrystal_I2C`
  - `DS3231`
- Upload the provided sketch to your Arduino.

### 2. Default Time Setup
In the `setup()` function, initial date/time is set:
```cpp
RTC.setYear(24);   // Example: 2024
RTC.setMonth(5);   // May
RTC.setDate(18);   // 18th
RTC.setHour(6);    // 06:00
RTC.setMinute(56); // 56 minutes

Change these values if you want to set a different startup time.

3. Menu Navigation

MENU Button (D6): Adjust system time/date.

RIGHT or LEFT Button (D4/D2): Enter Alarm mode.

UP/DOWN Buttons (D3/D5): Increment/Decrement values.

BUZZER (D7): Rings at alarm time.

4. Alarm Control

When alarm rings:

Stop it manually with RIGHT/LEFT button.

Or it will auto-stop after 1 minute.

🛠️ Libraries Used

Make sure to install the following libraries via Arduino IDE Library Manager:

LiquidCrystal_I2C

DS3231

📷 Demo Setup

LCD shows date & time.

Buttons allow easy navigation & adjustment.

Buzzer beeps at alarm time.

🚀 Future Improvements

Multiple alarm support.

Store alarms in EEPROM to keep after reset.

Add 12/24-hour mode switch.

Low-power mode for battery operation.


---

Would you like me to also add a **`Getting Started`** section with a step-by-step wiring guide (like a checklist) so beginners can follow it without needing a circuit diagram?
