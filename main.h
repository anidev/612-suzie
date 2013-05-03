#ifndef MAIN_H
#define MAIN_H

#include <IterativeRobot.h>
#include <Jaguar.h>
#include <Servo.h>
#include <Relay.h>
#include <Joystick.h>
#include <RobotDrive.h>

class robot_class:public IterativeRobot {
private:
    Jaguar left_front;
    Jaguar left_rear;
    Jaguar right_front;
    Jaguar right_rear;
    RobotDrive drive;
    Joystick controller1;
    Joystick controller2;
    Joystick controller3;
    Servo shift_left;
    Servo shift_right;
    Relay rollers1;
    Relay rollers2;
    Jaguar launcher1;
    Jaguar launcher2;
public:
    robot_class();
    ~robot_class();
    void stop_everything();
    void RobotInit();
    void DisabledInit();
    void AutonomousInit();
    void TeleopInit();
    void DisabledPeriodic();
    void AutonomousPeriodic();
    void TeleopPeriodic();
};

#endif // MAIN_H
