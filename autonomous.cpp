#include "autonomous.h"
#include "ports.h"
#include "state.h"
#include "drivetrain.h"
#include "lift.h"
#include "shooter.h"
#include "AutoShooter.h"
#include "launcher.h"

bool isLeft;
bool auto_state_changed = false;
bool shooter_prepped = false;

int Frisbees = 2;
float Launcher_Speed = 0.4;

const int DRIVE_DIST = 40;
const int TURN_ANGLE = -34; // negative is clockwise, positive is counter-clockwise
const float HIGH_LIFT_ANGLE = 2.58;     //suzie pot angles
const float LOW_LIFT_ANGLE = 2.14;      //suzie pot angles

enum auto_states {
    AUTO_DRIVE,
    AUTO_TURN,
    AUTO_SHOOT,
    DONE
};

State state(AUTO_DRIVE);
AutoTarget shoot_tar;
/*
void ShooterPrep(AutoTarget target) {
    if (!shooter_prepped) {
        if (shooter.getCurrentSpeed() < 1.0) {
            shooter.setSpeed(Launcher_Speed);
        }
        if (target == High_Goal) {
            angleAdjuster.set_angle(HIGH_LIFT_ANGLE);
        } else if (target == Middle_Goal) {
            angleAdjuster.set_angle(LOW_LIFT_ANGLE);
        }
        shooter_prepped = true;
    }
}
*/

void drive(double dist /*inches*/) {
    if (auto_state_changed) {
        drive_train.drive(dist);
        auto_state_changed = false;
    }
    else if (drive_train.isFinished()) {
        state.set_state(AUTO_TURN);
        auto_state_changed = true;
    }
}

void turn(double angle) {
    if (auto_state_changed) {
        drive_train.turn(angle);
        auto_state_changed = false;
    }
    else if (drive_train.isFinished()) {
        state.set_state(AUTO_SHOOT);
        auto_state_changed = true;
    }
}

void shoot() {
    if (auto_state_changed) {
        std::printf("shooting\n");
        auto_shoot.AutoShoot();
        auto_state_changed = false;
    } else if (auto_shoot.doneShooting()) {
        state.set_state(DONE);
        auto_state_changed = true;
    }
}

void choose_routine(Position pos, AutoTarget target){
    auto_state_changed = true;
    shooter_prepped = false;
    shoot_tar = target;
    if ((pos == Back_Left) || (pos == Front_Left)) {
        isLeft = true;
    }
    else
    {
        isLeft = false;
    }
    if((pos == Back_Left) || (pos == Back_Right)) {
        Frisbees = 3;
    }
    else
    {
        Frisbees = 2;
    }
    if (target==Middle_Goal) {
        state.set_state(AUTO_SHOOT);
    }
    if ((pos == Back_Left) || (pos == Back_Right)) {
        state.set_state(AUTO_DRIVE);
        Frisbees = 3;
    } else if ((pos == Front_Left) || (pos == Front_Right)) {
        state.set_state(AUTO_TURN);
    }
}
void do_autonomous() {
    /*if (!shooter_prepped) {
        ShooterPrep(shoot_tar);
    }
    else*/ if (state.get_state()==AUTO_DRIVE) {
        drive(DRIVE_DIST);
    } else if (state.get_state()==AUTO_TURN){
        if (isLeft == true){
            turn(TURN_ANGLE);
        } else {
            turn(-TURN_ANGLE);
        }
    } else if (state.get_state()==AUTO_SHOOT) {
        shoot();
    } else if (state.get_state()==DONE) {
        std:: printf("Autonomous is finished");
    }
}

