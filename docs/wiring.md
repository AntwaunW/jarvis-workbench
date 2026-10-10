# Wiring — JARVIS Workbench

**Board:** CYD ESP32-2432S028R (2-USB variant)
**Last verified:** 2026-10-09

## Display — ILI9341_2 driver (HSPI)
| Signal | GPIO | Notes |
|---|---|---|
| MISO | 12 | Data from screen to ESP32 |
| MOSI | 13 | Data from ESP32 to screen |
| SCLK | 14 | SPI clock |
| CS   | 15 | Chip select |
| DC   | 2  | Data/command select |
| RST  | -1 | Not connected; tied to board reset |
| BL   | 21 | Backlight, HIGH = on |

## Touch — XPT2046 (VSPI)
| Signal | GPIO | Notes |
|---|---|---|
| CLK  |  |  |
| MOSI |  |  |
| MISO |  |  |
| CS   |  |  |
| IRQ  |  |  |

## Onboard LED
| Signal | GPIO | Notes |
|---|---|---|
| Red LED | 4 | Active-LOW (LOW = on) |

## Reserved — Do Not Use
| GPIO | Reason |
|---|---|
| 2  | Display DC |
| 21 | Backlight |