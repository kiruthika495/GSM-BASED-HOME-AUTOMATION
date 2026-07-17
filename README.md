# 🏠 GSM Based Home Automation System using LPC2129

## 📖 Description

The **GSM Based Home Automation System** is an embedded systems project developed using the **LPC2129 ARM7 Microcontroller** and a **GSM module (SIM800C)** to remotely control home appliances through SMS commands. Unlike Wi-Fi-based automation systems, this project operates entirely over the GSM network, allowing users to control appliances from anywhere with mobile network coverage.

The GSM module communicates with the LPC2129 via **UART serial communication**. When a user sends predefined SMS commands from a mobile phone, the microcontroller reads the received message, identifies the requested operation, and controls the connected appliances accordingly. The current appliance status and received commands are also displayed on a **16×2 LCD** for user convenience.


---

# ✨ Features

* 📱 Remote control of home appliances using SMS
* 📶 Works without Wi-Fi or Internet connection
* ⚡ Controls multiple appliances independently
* 💡 Controls two lighting units
* 🌀 Controls a DC motor representing a fan
* 📟 Displays received SMS commands on a 16×2 LCD
* 🔄 Processes commands in real time
* 📡 UART communication between LPC2129 and GSM module
* 🔌 GPIO-based appliance control
* 🛠 Modular Embedded C implementation
* 💰 Low-cost and easy-to-build hardware

---

# 🔌 Hardware Components

* LPC2129 ARM7 Development Board
* SIM800C GSM Module
* 16×2 LCD Display
* DC Motor (Fan)
* Motor Driver (L293D/L298N)
* LEDs (Light1 & Light2)
* Power Supply
* Connecting Wires

---

# 📍 Hardware Pin Mapping

| LPC2148 Pin   | Connected Device     | Description                 |
| ------------- | -------------------- | --------------------------- |
| P0.0 (TXD0)   | GSM RX               | UART Transmission           |
| P0.1 (RXD0)   | GSM TX               | UART Reception              |
| P1.23         | LED1                 | Light 1 Control             |
| P1.24         | LED2                 | Light 2 Control             |
| P1.25         | Motor Driver Input 1 | Fan Control                 |
| P1.26         | Motor Driver Input 2 | Fan Direction / OFF Control |
| LCD Data Pins | LCD Display          | Display Commands & Status   |
| LCD RS        | LCD Register Select  | LCD Control                 |
| LCD E         | LCD Enable           | LCD Control                 |

---

# ⚙️ How It Works

### Step 1 – System Initialization

After power-on, the LPC2148 initializes the following peripherals:

* UART0 Communication
* GSM Module
* 16×2 LCD
* GPIO Pins for LEDs and Motor

The GSM module is configured using AT commands:

* `AT`
* `AT+CMGF=1` (Text Mode)
* `AT+CNMI=2,2,0,0,0` (Direct SMS Reception)

---

### Step 2 – GSM Module Ready

Once initialized, the GSM module waits for incoming SMS messages from the user's mobile phone.

---

### Step 3 – User Sends SMS Command

The user sends a predefined SMS command.

Example:

```text
*LIGHT1 ON#
*LIGHT2 OFF#
*FAN ON#
*ALL OFF#
```

---

### Step 4 – Receive SMS

The GSM module forwards the received SMS to the LPC2129 through UART0.

The program waits for:

* `*` → Start of command
* `#` → End of command

The received message is stored in a buffer for processing.

---

### Step 5 – Command Processing

The microcontroller compares the received SMS with predefined commands using string comparison.

Supported commands include:

* FAN ON
* FAN OFF
* LIGHT1 ON
* LIGHT1 OFF
* LIGHT2 ON
* LIGHT2 OFF
* ALL ON
* ALL OFF

If the command is valid, the corresponding GPIO pins are updated to control the connected appliances.

---

### Step 6 – Appliance Control

Depending on the received command:

* LED1 turns ON/OFF
* LED2 turns ON/OFF
* Fan motor starts or stops through the motor driver
* All appliances can be controlled simultaneously using ALL ON or ALL OFF commands

---

### Step 7 – LCD Status Display

The received SMS command and the current appliance status are displayed on the 16×2 LCD for easy monitoring.

Example:

```text
FAN ON
```

or

```text
LIGHT1 OFF
```

If an invalid command is received, the LCD displays:

```text
Invalid cmd....
```

---

# 📨 Supported SMS Commands

| SMS Command  | Action                  |
| ------------ | ----------------------- |
| *LIGHT1 ON#  | Turn ON Light 1         |
| *LIGHT1 OFF# | Turn OFF Light 1        |
| *LIGHT2 ON#  | Turn ON Light 2         |
| *LIGHT2 OFF# | Turn OFF Light 2        |
| *FAN ON#     | Start Fan               |
| *FAN OFF#    | Stop Fan                |
| *ALL ON#     | Turn ON All Appliances  |
| *ALL OFF#    | Turn OFF All Appliances |

---


# 📚 Technologies Used

* Embedded C
* LPC2129 ARM7 Microcontroller
* UART Communication
* GSM Module (SIM800C)
* LCD Interfacing
* GPIO Programming
* Motor Driver Interfacing
* Keil uVision
* Flash Magic

---

# 🔮 Future Enhancements

* Password-protected SMS commands
* IoT (Wi-Fi) support
* Voice command functionality
* Sensor-based automatic control
* Appliance status feedback via SMS
