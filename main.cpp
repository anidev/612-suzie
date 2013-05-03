#include "main.h"
#include "612.h"

robot_class::robot_class():left_front(2,2),
                           left_rear(2,3),
                           right_front(1,3),
                           right_rear(1,4),
                           drive(left_front,left_rear,right_front,right_rear),
                           controller1(1),
                           controller2(2),
                           controller3(3),
                           shift_left(1,6),
                           shift_right(2,4),
                           rollers1(2,1),
                           rollers2(2,2),
                           launcher1(1,1),
                           launcher2(1,2)
{
}

robot_class::~robot_class() {
}

void robot_class::stop_everything() {
    drive.TankDrive(0.0f,0.0f);
#ifdef USE_ROLLERS
    rollers1.Set(Relay::kOff);
    rollers2.Set(Relay::kOff);
#endif
#ifdef USE_SHOOTING
    launcher1.Set(0.0f);
    launcher2.Set(0.0f);
#endif
}

void robot_class::RobotInit() {
#ifdef USE_SHIFTING
    shift_left.Set(SHIFT_HIGHPOS);
    shift_right.Set(SHIFT_HIGHPOS);
#endif
}

void robot_class::DisabledInit() {
    stop_everything();
}

void robot_class::AutonomousInit() {
    stop_everything();
}

void robot_class::TeleopInit() {
    stop_everything();
}

void robot_class::DisabledPeriodic() {
}

void robot_class::AutonomousPeriodic() {
}

void robot_class::TeleopPeriodic() {
#ifdef JOYSTICK
    float left=controller1.GetY();
    float right=controller2.GetY();
#else
    float left=controller1.GetRawAxis(2);
    float right=controller1.GetRawAxis(4);
#endif
    drive.TankDrive(left,right);
// Gamepads only can drive, joysticks can do more
#ifdef JOYSTICK

#ifdef USE_SHIFTING
    if(controller1.GetRawButton(SHIFT_HIGHL)||controller2.GetRawButton(SHIFT_HIGHR)) {
        shift_left.Set(SHIFT_HIGHPOS);
        shift_right.Set(SHIFT_HIGHPOS);
    } else if(controller1.GetRawButton(SHIFT_LOWL)||controller2.GetRawButton(SHIFT_LOWL)) {
        shift_left.Set(SHIFT_HIGHPOS);
        shift_right.Set(SHIFT_HIGHPOS);
    }
#endif
#ifdef USE_ROLLERS
#endif
    if(controller3.GetRawButton(ROLLER_UP)) {
        rollers1.Set(Relay::kForward);
        rollers2.Set(Relay::kForward);
    } else if(controller3.GetRawButton(ROLLER_DOWN)) {
        rollers1.Set(Relay::kReverse);
        rollers2.Set(Relay::kReverse);
    } else {
        rollers1.Set(Relay::kOff);
        rollers2.Set(Relay::kOff);
    }
#endif
#ifdef USE_SHOOTING
    if(controller3.GetRawButton(SPIN_WHEEL)) {
        launcher1.Set(SHOOT_SPEED);
        launcher2.Set(SHOOT_SPEED);
    } else {
        launcher1.Set(BACKSPIN);
        launcher2.Set(BACKSPIN);
    }
#endif
}

START_ROBOT_CLASS(robot_class)
