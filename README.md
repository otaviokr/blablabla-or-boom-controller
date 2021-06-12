# blablabla-or-boom-controller
This is the master controller

These are the default values, but you can provide a new `pins.h` to define different pins.

| Port         | Type           | Arduino# | ESP32#     |
| ============ | ============== | ======== | ========== |
| Start Signal | Input Digital  | 13       | GPIO2  D2  |
| Running LED  |                |          | GPIO13 D13 |
| Piezo Signal | Output Digital | 12       | GPIO18 D18 |
| 7-seg 1/e    | Output Digital | 11       | GPIO33  |
| 7-seg 2/d    | Output Digital | 10       | GPIO25  |
| 7-seg 3/dec  | Output Digital | 9        | GPIO26  |
| 7-seg 4/c    | Output Digital | 11       | GPIO27  |
| 7-seg 5/g    | Output Digital | 10       | GPIO14  |
| 7-seg 6/d4   | Output Digital | 9        | GPIO12  |
| 7-seg 7/B    | Output Digital | 8        | GPIO5   |
| 7-seg 8/d3   | Output Digital | 7        | GPIO18   |
| 7-seg 9/d2   | Output Digital | 6        | GPIO19   |
| 7-seg 10/f   | Output Digital | 5        | GPIO21   |
| 7-seg 11/a   | Output Digital | 4        | GPIO RXD   |
| 7-seg 12/d1  | Output Digital | 4        | GPIO22   |
| Game Mode    | Output Digital | 3        |          |
| Game Active  | Output Digital | 2        | D13      |
| Game Select  | Input Analog   | A5       | ADC1_CH0 |

# Details on the components

## 4x7-Segment display

```
    +-A-+                12 11 10  9  8  7
  F |   | B           +---|--|--|--|--|--|---+
    +-G-+             |                      |
  E |   | C           |    8 . 8 . 8 . 8 .   |
    +-D-+             |                      |
                      +---|--|--|--|--|--|---+
                          1  2  3  4  5  6

1 - segment E              7 - segmenet B
2 - segment D              8 - control digit 3
3 - decimal point          9 - control digit 2
4 - segment C             10 - segement F
5 - semgment G            11 - segment A
6 - control Digit 4       12 - control digit 1
```