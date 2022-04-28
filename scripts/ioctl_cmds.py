#define RD_SWITCHES   _IO('a', 'a')
RD_SWITCHES = ord('a') << (4*2) | 61

#define RD_PBUTTONS   _IO('a', 'b')
RD_PBUTTONS = ord('a') << (4*2) | 62

#define WR_L_DISPLAY  _IO('a', 'c')
WR_L_DISPLAY = ord('a') << (4*2) | 63

#define WR_R_DISPLAY  _IO('a', 'd')
WR_R_DISPLAY = ord('a') << (4*2) | 64

#define WR_RED_LEDS   _IO('a', 'e')
WR_RED_LEDS = ord('a') << (4*2) | 65

#define WR_GREEN_LEDS _IO('a', 'f')
WR_GREEN_LEDS = ord('a') << (4*2) | 66
