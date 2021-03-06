#include "Config.h"

void ltm_read();
void ltm_check();

#define LIGHTTELEMETRY_START1 0x24 //$
#define LIGHTTELEMETRY_START2 0x54 //T
#define LIGHTTELEMETRY_GFRAME 0x47 //G for GPS + Baro altitude data
#define LIGHTTELEMETRY_GFRAMELENGTH 18
	
void telemetry_off(void);
extern boolean telemetry_ok;
extern int lastpacketreceived;
extern String protocol;
extern float uav_lat;
extern float uav_lon;
extern int uav_satellites_visible;
extern int uav_fix_type;
extern long uav_alt;
extern int uav_groundspeed;

#if defined(TEENSYPLUS2)
extern HardwareSerial Uart;
#endif
