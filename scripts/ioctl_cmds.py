#define RD_SWITCHES   _IO('a', 'a')
#RD_SWITCHES = ord('a') << (4*2) | 61
RD_SWITCHES = 24929

#define RD_PBUTTONS   _IO('a', 'b')
#RD_PBUTTONS = ord('a') << (4*2) | 62
RD_PBUTTONS = 24930

#define WR_L_DISPLAY  _IO('a', 'c')
#WR_L_DISPLAY = ord('a') << (4*2) | 63
WR_L_DISPLAY = 24931

#define WR_R_DISPLAY  _IO('a', 'd')
#WR_R_DISPLAY = ord('a') << (4*2) | 64
WR_R_DISPLAY = 24932

#define WR_RED_LEDS   _IO('a', 'e')
#WR_RED_LEDS = ord('a') << (4*2) | 65
WR_RED_LEDS = 24933

#define WR_GREEN_LEDS _IO('a', 'f')
#WR_GREEN_LEDS = ord('a') << (4*2) | 66
WR_GREEN_LEDS = 24934
