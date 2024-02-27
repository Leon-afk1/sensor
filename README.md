# Monitoring IoT Simulator

## Introduction

Welcome to the AP4A TP project - an individual mini-project to apply the knowledge gained during the semester. This project involves creating a simulator modeling an IoT ecosystem specialized in monitoring the air quality of a workspace.

## Objective

The main goal is to develop a simulator consisting of a server and various sensors (temperature, humidity, light, sound) distributed in the workspace. Sensor data can be stored in log files or displayed in the console.

## Project Content

### Program Features

Once the program is launched, you can dynamically control:

- Activate or deactivate console and log outputs.
- Add multiple sensors of different types.
- Set individual measurement intervals for each sensor.

### How to Use

- Follow on-screen instructions to enable/disable console and log outputs.
- Add sensors by choosing the sensor type (sound, temperature, humidity, light).
- Set measurement intervals for each sensor.
- Observe sensor data in the console and log files.
- Modify settings at any time during program execution using Q to quit, L or C to use or not log and consol writing, S/T/H/I to add or delete a sound/temperature/humidity/light sensor.

### Code Structure

The project is organized into several classes:

- **`scheduler` Class:** Manages the main program flow and handles different sensors.

- **`Server` Class:** Manages the values of sensors and writes them to files. Includes functions for console and file writing.

- **`sensor` Class:** The base class for different types of sensors. Contains virtual functions for generating random values and printing sensor values.

- **`soundSensor`, `temperatureSensor`, `humiditySensor`, `lightSensor` Classes:** Implement specific sensor types, inheriting from the `sensor` class.

### Solutions Employed

#### Server Class

- **Logging and Console Display:** The `Server` class provides functionality to write sensor data to log files and display it in the console. This is achieved through the `fileWrite` and `consolWrite` functions.

- **Operator Overloading:** Overloaded the assignment operator (`operator=`) and the stream insertion operator (`operator<<`). This allows copying the content of one object to another and redirecting elements to the console or a log file.

#### Sensor Classes

- **Random Sensor Values:** Implemented functions (`aleaSensorValue`) in each sensor class to generate random values specific to the sensor type.

#### Scheduler Class

- **Main Program Flow:** The `scheduler` class manages the overall program flow, including functions to handle each type of sensor.

### Possible Improvements

- Remove the maximum limit on the number of sensors.
- Allow adding multiple instances of the same sensor type (in different locations, for example).
- Enable direct modification of measurement intervals for each sensor during runtime.
