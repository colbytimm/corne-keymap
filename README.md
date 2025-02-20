<p align="center">
    <img src="./imgs/corne_cherry_logo.png" width="40%" />
</p>

# Corne Cherry v3 Keymap
This repository stores my keymap file for my Corne Cherry v3 keyboard and builds my firmware.

<p align="center">
    <img src="./imgs/corne_photo.png" width="90%" />
</p>

## Design
- Keyboard Design
    - [Corne Keyboard](https://github.com/foostan/crkbd/tree/v3-final)
- Switches
    - Gateron KS-9 RGB Mechanical Red
- Keycaps
    - JOMKIZ Keycaps Constellation

## Visual Keymap

<img src="./imgs/visual_keymap.svg" />

## Keymap Configuration

<img src="./imgs/corne_keymap.svg" />

## Run Locally

To build the firmware locally, run the following:

```bash
qmk compile -c -kb crkbd/rev1 -km feynman -e CONVERT_TO=helios
```
