#define RD_SWITCHES   _IO('a', 'a')
RD_SWITCHES = ord('a') << (4*2) | 'a'

#define RD_PBUTTONS   _IO('a', 'b')
RD_PBUTTONS = ord('a') << (4*2) | 'b'

#define WR_L_DISPLAY  _IO('a', 'c')
WR_L_DISPLAY = ord('a') << (4*2) | 'c'

#define WR_R_DISPLAY  _IO('a', 'd')
WR_R_DISPLAY = ord('a') << (4*2) | 'd'

#define WR_RED_LEDS   _IO('a', 'e')
WR_RED_LEDS = ord('a') << (4*2) | 'e'

#define WR_GREEN_LEDS _IO('a', 'f')
WR_GREEN_LEDS = ord('a') << (4*2) | 'f'
