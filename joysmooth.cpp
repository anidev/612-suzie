<<<<<<< HEAD
#include <Joystick.h>
#include <bitset>
#include "612.h"
#include "joysmooth.h"

const static int NUMBUTTONS = 12;
const static int WAIT_TIME = 3;

joysmooth::joysmooth(UINT32 port):Joystick(port) {
    updateRegistry.addUpdateFunction(&updateHelper,(void*)this);
}

joysmooth::~joysmooth () {
}

void joysmooth::update(){
    for (int f = 0; f < NUMBUTTONS; f++){
        for (int s = 1; s < WAIT_TIME; s++){
            buttons[f][s - 1] = buttons [f][s];
        }
        buttons[f][WAIT_TIME - 1] = Joystick::GetRawButton(f+1);
    }
    
}
bool joysmooth::GetRawButton(UINT32 btn) {
   for (int i = 0; i < WAIT_TIME; i++){
       if (!buttons[btn - 1][i]){
           return false;
       }
   }
   return true;
}
void joysmooth::updateHelper(void* o) {
    ((joysmooth*)o) -> update();
}

=======
#include <Joystick.h>
#include <bitset>
#include "612.h"
#include "joysmooth.h"

joysmooth::joysmooth(UINT32 port):Joystick(port) {
    updateRegistry.addUpdateFunction(&updateHelper,(void*)this);
}

joysmooth::~joysmooth () {
}

void joysmooth::update(){
    for (int f = 0; f < NUMBUTTONS; f++){
        for (int s = 1; s < WAIT_TIME; s++){
            buttons[f][s - 1] = buttons [f][s];
        }
        buttons[f][WAIT_TIME - 1] = Joystick::GetRawButton(f + 1);
    }
}
bool joysmooth::GetRawButton(UINT32 btn) {
   for (int i = 0; i < WAIT_TIME; i++){
       if (!buttons[btn - 1][i]){
           return false;
       }
   }
   return true;
}
void joysmooth::updateHelper(void* o) {
    ((joysmooth*)o) -> update();
}
>>>>>>> eab6503e44d2c00d597b972acc6c3a51efb7b743
