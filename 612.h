#ifndef _612_H
#define _612_H

#define JOYSTICK
//#define GAMEPAD

//#define USE_BRIDGEARM // FIXME not implemented
//#define USE_WINCH     // FIXME not implemented
//#define USE_TURRET    // FIXME not implemented
//#define USE_SHOOTPOT  // FIXME not implemented
#define USE_SHOOTING
#define USE_ROLLERS
#define USE_SHIFTING

// Following are all joystick controls

static const float SHIFT_HIGHPOS = 0.8f;
static const float SHIFT_LOWPOS =  0.2f;
static const float SHOOT_SPEED =   1.0f;
static const float BACKSPIN =     -0.18f;

// Driver controls
static const int SHIFT_HIGHL =  6;
static const int SHIFT_LOWL =   7;
static const int SHIFT_HIGHR =  11;
static const int SHIFT_LOWR =   10;

// Gunner controls
static const int TURRET =      1;
static const int SPIN_WHEEL =  2;
static const int ROLLER_UP =   6;
static const int ROLLER_DOWN = 7;
static const int ARM_DOWN =    10;
static const int ARM_UP =      11;


#endif // _612_H
