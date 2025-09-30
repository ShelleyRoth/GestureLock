# Gesture-Controlled Combination Lock (Arduino)

Unlock a lock using hand gestures detected by an ultrasonic sensor.

## Features
- **Ultrasonic sensor (HC-SR04):** detects near / medium / far hand gestures.
- **RGB LED:** shows lock status (red = locked, yellow = waiting, green = unlocked).
- **Buzzer:** gives audio feedback (beeps, error tones).
- **Servo motor:** acts as the lock (rotates when unlocked).
- **Reset system:** resets automatically on wrong input or timeout.

## Hardware
- Arduino UNO
- HC-SR04 ultrasonic sensor
- RGB LED + resistors
- Passive buzzer
- Servo motor
- Jumper wires, breadboard

## Milestones
1. Distance readout via Serial Monitor.
2. Classify distances (near/medium/far).
3. Record and compare gesture sequences.
4. Add LED and buzzer feedback.
5. Servo lock mechanism.
6. Reset & polish.

## Repo Structure
Gesture Lock/
— GestureLock.ino #  main Arduino sketch
— README.md # this file
— .gitignore # ignore build artifacts
— docs/ # wiring diagrams, flowcharts
— media/ #photos or demo videos

## License
MIT
