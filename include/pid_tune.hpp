#ifndef PID_TUNE_HPP
#define PID_TUNE_HPP

#include "config.hpp" 
#include "lemlib/chassis/chassis.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motors.h"

enum class PidTarget {ANGULAR, LATERAL};

class PidTune {
public:
    explicit PidTune(PidTarget target) : pidTarget(target) {}
    
    PidTarget getTarget() {return pidTarget;}
    void setTarget(PidTarget target) {pidTarget = target;}

    const char* targetName() const {
        switch (pidTarget) {
            case PidTarget::ANGULAR: return "angular";
            default: return "lateral";
        }
    }

    void recycle() {
        if (pidTarget == PidTarget::ANGULAR){
            pidTarget = PidTarget::LATERAL;
        } else {
            pidTarget = PidTarget::ANGULAR;
        } 
    }

    void tune(pros::Controller& controller) {
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X) &&
            controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
            recycle();
        }

        lemlib::ControllerSettings& controllerSettings = activeController();

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
            if (pidTarget == PidTarget::ANGULAR){
                testTurn(steeringTuneTarget);
            } else {
                testMove(lateralTuneTarget);
            }
        } else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)){
            controllerSettings.kP += stepKp;
        } else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)){
            controllerSettings.kP -= stepKp;
        } else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)){
            controllerSettings.kD += stepKd;
        } else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)){
            controllerSettings.kD -= stepKd;
        }
    }
private:
    float stepKp = 0.5f;
    float stepKd = 1.0f;

    static constexpr float steeringTuneTarget = 90.0;   // degrees
    static constexpr int lateralTuneTarget = 48;        // inches

    lemlib::ControllerSettings& activeController() {
        switch (pidTarget) {
            case PidTarget::ANGULAR:
                return angular_controller;
            default:
                return lateral_controller;
        }
    }

    PidTarget pidTarget;
    
    void rebuildChassis(pros::motor_brake_mode_e break_mode=pros::E_MOTOR_BRAKE_COAST){
        chassis.cancelAllMotions();
        while(chassis.isInMotion()) {
            pros::delay(5);
        }
        chassis.~Chassis();
        new (&chassis) lemlib::Chassis(
            drivetrain,
            lateral_controller,
            angular_controller,
            sensors
        );
        chassis.setBrakeMode(break_mode);
    }

    void testTurn(float angle_deg) {
        rebuildChassis();
        chassis.setPose(0, 0, 0);
        chassis.resetLocalPosition();
        chassis.turnToHeading(angle_deg, 100000);        
    }

    void testMove(float yTarget) {
        rebuildChassis();
        chassis.setPose(0, 0, 0);
        chassis.resetLocalPosition();
        chassis.moveToPoint(0, yTarget, 100000);
    }
};

#endif 