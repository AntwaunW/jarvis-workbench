# JARVIS Workbench Command Center — v1 Requirements
Version: 0.2 (draft) | Owner: Antwaun | Status: In review

## 1. Purpose
A desk device behind two-way mirror glass that wakes my PC with an RFID
tap and shows a glass HUD (time, active project, current task). RFID
project cards set the active project. v1 is the foundation for power
monitoring (v2), PC voice (v3), on-device voice (v4), and a custom PCB (v5).

## 2. Scope
IN (v1): RFID auth + project cards, wake prompt, PC power press,
PC on/off sensing, HUD (clock, date, project, task), mirror-glass display.
OUT (v1): calendar events, voice, power monitor, PC-side agent,
PC sleep/shutdown from device, OTA updates, final enclosure,
phone NFC, family profiles.

## 3. Functional Requirements
| ID    | Requirement | Test |
|-------|-------------|------|
| FR-01 | The system shall read the UID of a 13.56 MHz card via the PN532 over I2C. | Tap card; UID printed on serial log |
| FR-02 | The system shall map each approved UID to a project record. Unknown UIDs shall show "Card not recognized" for 3 s, then return to idle. | Tap approved + unknown cards; observe screen |
| FR-03 | In idle, the display shall be fully dark so the glass reads as a mirror. | Visual check in room lighting |
| FR-04 | An approved tap shall wake the display and show the project name with "Wake Up" and "Go Back to Sleep" buttons. | Tap card; observe prompt |
| FR-05 | "Wake Up" shall pulse the PC power button ONLY if the PC is sensed as off, then show the HUD. | Test with PC off (boots) and on (no press) |
| FR-06 | "Go Back to Sleep" shall turn the display dark with no PC action. | Press; PC state unchanged |
| FR-07 | The prompt shall time out after 15 s with no PC action. | Tap, wait, time with stopwatch |
| FR-08 | The HUD shall show time (HH:MM), date, active project, and current task. | Visual check |
| FR-09 | Time shall sync via NTP at boot when Wi-Fi is available; the RTC shall keep time without Wi-Fi. | Boot with and without Wi-Fi; compare to phone |
| FR-10 | Tapping a different project card while the HUD is shown shall switch the active project. | Tap card B while A active |
| FR-11 | The active project shall survive a power cycle. | Unplug, replug, check HUD |
| FR-12 | The HUD shall turn dark after 10 min of no interaction (configurable). | Wait; observe |
| FR-13 | The existing case and external power buttons shall keep working. | Press each with device installed |
| FR-14 | The firmware shall log state changes and errors over USB serial. | Watch serial monitor during tests |

## 4. Non-Functional Requirements
| ID     | Requirement | Test |
|--------|-------------|------|
| NFR-01 | Card tap to screen-on shall take under 1 s. | Slow-mo phone video |
| NFR-02 | The power pulse shall be hard-limited in the driver to under 1 s (a 4 s hold force-kills the PC). | Scope/log pulse length; code review |
| NFR-03 | The device shall connect to the PC only through optocouplers (no shared electrical path). | Wiring review + continuity test |
| NFR-04 | The device shall run from its own 5 V supply, independent of PC power. | Works with PC fully off |
| NFR-05 | Wi-Fi credentials and card UIDs shall not be committed to Git. | Check .gitignore + repo history |
| NFR-06 | The device shall boot to idle within 5 s. | Stopwatch |

## 5. Constraints
| ID   | Constraint |
|------|------------|
| C-01 | v1 development hardware: ESP32-2432S028R ("CYD", 2.8" 240x320, resistive touch). |
| C-02 | v1 target hardware: Elecrow CrowPanel 7.0" Advance ESP32-S3. |
| C-03 | App logic must not call display, touch, or RFID libraries directly (HAL) so code ports from CYD to CrowPanel. |
| C-04 | CYD has very few free GPIO pins; all pin assignments recorded in docs/wiring.md. |
| C-05 | Optocouplers are bare PC817 chips (not modules); resistors selected per datasheet. |

## 6. Parts List (BOM)
| Part | Qty | Used In | Status |
|------|-----|---------|--------|
| ESP32-2432S028R "CYD" 2.8" display board | 1 | v1 dev | Purchased |
| JST 1.25mm 4-pin cables (for CYD connectors) | 2+ | v1 dev | Confirm included with CYD |
| PN532 NFC/RFID module (AITRIP 2-pack, I2C) | 1 | v1 | Purchased |
| 13.56 MHz cards/tags (S50 + existing) | 3+ | v1 | Have |
| PC817 optocoupler, bare DIP-4 chip | 2 | v1 | Purchased (50-pack) |
| 220Ω resistor (opto LED side) | 2 | v1 | Have (kit) |
| 10kΩ resistor (bench test pull-up) | 1 | v1 dev | Have (kit) |
| Breadboard, jumpers, multimeter | — | v1 dev | Have |
| Elecrow CrowPanel 7.0" Advance ESP32-S3 | 1 | v1 target | To buy |
| Geekworm 5V 4A USB-C supply | 1 | v1 target | To buy |
| Cable for CrowPanel I2C-OUT connector | 1 | v1 target | To buy (check wiki for type) |
| Two-way mirror film | 1 | v1 target | To buy |
| 2-pin header splitters (power SW + power LED) | 2 | v1 install | To buy |
| microSD card (≤32 GB) | — | — | Not needed v1 (using NVS) |
| Speakers, INMP441 mic, MAX98357A amp | — | v4 | Later |
| INA219/INA226 current sensor | 1 | v2 | Later |

## 7. Open Questions
- OQ-01: Which CrowPanel pins are free for the 2 optocoupler channels? (UART port pins as GPIO?)
- OQ-02: Where do v1 tasks live? (a) JSON file on microSD, (b) edited on-device, (c) pushed from PC later
- OQ-03: Does the PN532 I2C address conflict with the touch controller on the same bus?
- OQ-04: Does the PC817 module fully switch from a 3.3 V GPIO signal?
- OQ-05: Where does the card→project table live so it's not in Git? (SD file? secrets header?)