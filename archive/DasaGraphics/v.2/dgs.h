/* copyright 2016, Craig A. Damon, all rights reserved. */
#ifndef __DGS_H__
#define __DGS_H__

#define SHARED_KEY 3456

#define SHOWER 1
#define JET 2
#define RAIN 3
#define MASSAGE 4

#define ON 1
#define OFF 0

/* the current requested state */
typedef struct DasaServerInfo {
   unsigned char shutdown; // exit server when this becomes true
   char xPos;            // range -50 to 50
   unsigned char yPos;   // range 0 to 100
   unsigned char zPos;   // range 0 to 100
   unsigned char mode;   // one of SHOWER, JET, RAIN, MASSAGE
   unsigned char temp;   // range 75 to 110
   unsigned char onOff;  // either ON or OFF
} DasaServerInfo;


#endif