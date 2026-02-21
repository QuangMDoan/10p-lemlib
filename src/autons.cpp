#include "main.h"
#include "config.hpp"
#include "intake_manager.hpp"
#include "auton_utils.hpp"

void sawp() {
    chassis.setPose(0, 0, 0);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    AutonUtils::driveDistance(25, true, 127, 1000);
    AutonUtils::driveUntilFrontWall(17, true, 45, 22, 1000);
    pros::delay(50);
    chassis.turnToHeading(90, 750);
    matchload_bar.set_value(true);
    intake_manager.set_state(IntakeState::INTAKE);
    chassis.waitUntilDone();
    AutonUtils::driveDistance(17.7, true, 60, 700);
    chassis.arcade(50, 0);
    pros::delay(400);
    chassis.arcade(0, 0);
    AutonUtils::startDriveDistance(33, false, 127, 1000);
    AutonUtils::waitUntilDistanceTraveled(24);
    intake_manager.set_state(IntakeState::SCORE_HIGH);
    AutonUtils::waitUntilDriveDone();
    chassis.turnToHeading(90, 500);
    chassis.waitUntilDone();
    pros::delay(500);
    AutonUtils::driveDistance(10, true, 127, 650);
    chassis.turnToHeading(-150, 750);
    matchload_bar.set_value(false);
    intake_manager.set_state(IntakeState::INTAKE);
    chassis.waitUntilDone();
    AutonUtils::startDriveDistance(25, true, 127, 750);
    AutonUtils::waitUntilDistanceTraveled(18);
    matchload_bar.set_value(true);
    AutonUtils::waitUntilDriveDone();
    chassis.turnToHeading(180, 500);
    matchload_bar.set_value(false);
    chassis.waitUntilDone();
    AutonUtils::startDriveDistance(44, true, 75, 1250);
    AutonUtils::waitUntilDistanceTraveled(40);
    matchload_bar.set_value(true);
    AutonUtils::waitUntilDriveDone();
    chassis.turnToHeading(135, 750);
    chassis.waitUntilDone();
    AutonUtils::driveDistance(23, false, 127, 750);
    intake_manager.set_state(IntakeState::SCORE_LOW);
    pros::delay(100);
    intake_manager.set_state(IntakeState::SCORE_MID);
    chassis.turnToHeading(145, 500);
    chassis.waitUntilDone();
    intake_manager.set_state(IntakeState::IDLE);
    AutonUtils::driveDistance(50, true, 127, 1250);
    chassis.turnToHeading(90, 750);
    chassis.waitUntilDone();
    AutonUtils::startDriveDistance(20, false, 127, 1000);
    AutonUtils::waitUntilDistanceTraveled(15);
    intake_manager.set_state(IntakeState::SCORE_HIGH);
}

void four_hook() {
	// Autonomous routine here
}

void four_plus_three_mid() {
	chassis.setPose(0, 0, 180);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    AutonUtils::driveDistance(25, true, 127, 1000);
    AutonUtils::driveUntilFrontWall(17.7, true, 45, 22, 1000);
    pros::delay(50);
    chassis.turnToHeading(90, 750);
    matchload_bar.set_value(true);
    intake_manager.set_state(IntakeState::INTAKE);
    chassis.waitUntilDone();
    AutonUtils::driveDistance(17, true, 40, 700);
    chassis.arcade(50, 0);
    pros::delay(400);
    chassis.arcade(0, 0);
    AutonUtils::startDriveDistance(30, false, 127, 1000);
    AutonUtils::waitUntilDistanceTraveled(24);
    intake_manager.set_state(IntakeState::SCORE_HIGH);
    AutonUtils::waitUntilDriveDone();
    chassis.turnToHeading(90, 500);
    chassis.waitUntilDone();
    pros::delay(500);
    AutonUtils::driveDistance(10, true, 127, 650);
    chassis.turnToHeading(-30, 750);
    matchload_bar.set_value(false);
    intake_manager.set_state(IntakeState::INTAKE);
    chassis.waitUntilDone();
    AutonUtils::driveDistance(25, true, 60, 750);
    chassis.turnToHeading(150, 750);
    chassis.waitUntilDone();
    AutonUtils::driveDistance(20, false, 127, 750);
    intake_manager.set_state(IntakeState::SCORE_MID);
    pros::delay(1000);
    AutonUtils::driveDistance(34, true, 127, 1000);
    chassis.turnToHeading(85, 750);
    wing.set_value(true);
    chassis.waitUntilDone();
    AutonUtils::driveDistance(25, false, 40, 1500);
}

void four_plus_three_low() {
	chassis.setPose(0, 0, 0);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    AutonUtils::driveDistance(25, true, 127, 1000);
    AutonUtils::driveUntilFrontWall(17, true, 45, 22, 1000);
    pros::delay(50);
    chassis.turnToHeading(90, 750);
    matchload_bar.set_value(true);
    intake_manager.set_state(IntakeState::INTAKE);
    chassis.waitUntilDone();
    AutonUtils::driveDistance(17, true, 60, 700);
    chassis.arcade(50, 0);
    pros::delay(400);
    chassis.arcade(0, 0);
    AutonUtils::startDriveDistance(30, false, 127, 1000);
    AutonUtils::waitUntilDistanceTraveled(24);
    intake_manager.set_state(IntakeState::SCORE_HIGH);
    AutonUtils::waitUntilDriveDone();
    chassis.turnToHeading(90, 500);
    chassis.waitUntilDone();
    pros::delay(500);
    AutonUtils::driveDistance(10, true, 127, 650);
    chassis.turnToHeading(-150, 750);
    matchload_bar.set_value(false);
    intake_manager.set_state(IntakeState::INTAKE);
    chassis.waitUntilDone();
    AutonUtils::driveDistance(42, true, 60, 1500);
    intake_manager.set_state(IntakeState::SCORE_LOW);
    pros::delay(1000);
    AutonUtils::driveDistance(31, false, 127, 1000);
    chassis.turnToHeading(-90, 750);
    wing.set_value(true);
    chassis.waitUntilDone();
    AutonUtils::driveDistance(20, true, 50, 1500);
}

void drive_off() {
	chassis.setPose(0, 0, 0);
    chassis.moveToPoint(0, 5, 10000);
    chassis.waitUntilDone();
    chassis.arcade(0, 0);
}

void jiggle_task(void *param) {
    while (true) {
        chassis.turnToHeading(30, 300, {.minSpeed = 120});
        pros::delay(400);
        chassis.turnToHeading(-30, 300, {.minSpeed = 120});
        pros::delay(400);
    }
}

void skills() {
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.setPose(-50, 16, 0);
    chassis.moveToPoint(-50, 48, 2000, {.maxSpeed = 75});
    chassis.waitUntilDone();
    chassis.turnToHeading(-90, 750);
    matchload_bar.set_value(true);
    intake_manager.set_state(IntakeState::INTAKE);
    chassis.waitUntilDone();
    chassis.moveToPoint(-62, 46, 1500, {.maxSpeed = 40});
    chassis.waitUntilDone();
    chassis.arcade(25, 0);
    pros::delay(2250);
    chassis.arcade(0, 0);
    chassis.moveToPoint(-53, chassis.getPose().y, 1500, {.forwards = false});
    chassis.waitUntilDone();
    chassis.turnToPoint(-29, 58.5, 750, {.forwards = false});
    chassis.waitUntilDone();
    chassis.moveToPoint(-29, 58.5, 1500, {.forwards = false});
    chassis.waitUntilDone();
    chassis.turnToPoint(22, 58.5, 750, {.forwards = false});
    matchload_bar.set_value(false);
    chassis.waitUntilDone();
    chassis.moveToPoint(22, 57.5, 3000, {.forwards = false, .maxSpeed = 75});
    chassis.waitUntilDone();
    chassis.turnToPoint(45, 46, 750, {.forwards = false});
    chassis.waitUntilDone();
    chassis.moveToPoint(45, 46, 1500, {.forwards = false});
    chassis.waitUntilDone();
    chassis.turnToHeading(90, 750);
    chassis.waitUntilDone();
    chassis.moveToPoint(15, 49, 1500, {.forwards = false, .minSpeed = 127});
    chassis.waitUntilDone();
    intake_manager.set_state(IntakeState::UNJAM);
    chassis.arcade(-35, 0);
    pros::delay(250);
    intake_manager.set_state(IntakeState::SCORE_HIGH);
    matchload_bar.set_value(true);
    pros::delay(1500);
    chassis.arcade(0, 0);
    pros::delay(500);
    chassis.setPose(27, 47, chassis.getPose().theta);
    chassis.moveToPoint(62, 46, 1500, {.maxSpeed = 60});
    chassis.waitUntilDone();
    intake_manager.set_state(IntakeState::INTAKE);
    chassis.arcade(25, 0);
    pros::delay(2250);
    chassis.arcade(0, 0);
    chassis.moveToPoint(27, 48, 1500, {.forwards = false});
    chassis.waitUntilDone();
    intake_manager.set_state(IntakeState::UNJAM);
    chassis.arcade(-25, 0);
    pros::delay(250);
    intake_manager.set_state(IntakeState::SCORE_HIGH);
    matchload_bar.set_value(false);
    pros::delay(1500);
    chassis.arcade(0, 0);
    chassis.moveToPoint(40, 48, 1000);
    chassis.waitUntilDone();
    chassis.turnToHeading(180, 750);
    chassis.waitUntilDone();
    chassis.moveToPoint(45, -48, 5000, {.maxSpeed = 75});
    chassis.waitUntilDone();
    chassis.turnToHeading(90, 750);
    matchload_bar.set_value(true);
    intake_manager.set_state(IntakeState::INTAKE);
    stopper.set_value(true);
    chassis.waitUntilDone();
    chassis.moveToPoint(61, chassis.getPose().y, 1500, {.maxSpeed = 40});
    chassis.waitUntilDone();
    chassis.arcade(25, 0);
    pros::delay(2250);
    chassis.arcade(0, 0);
    chassis.moveToPoint(56, chassis.getPose().y, 1500, {.forwards = false});
    chassis.waitUntilDone();
    chassis.turnToPoint(25, -58, 750, {.forwards = false});
    chassis.waitUntilDone();
    chassis.moveToPoint(25, -58, 1500, {.forwards = false});
    chassis.waitUntilDone();
    chassis.turnToPoint(-23, -56, 750, {.forwards = false});
    matchload_bar.set_value(false);
    chassis.waitUntilDone();
    chassis.moveToPoint(-23, -56, 3000, {.forwards = false, .maxSpeed = 75});
    chassis.waitUntilDone();
    chassis.turnToPoint(-43, -43, 750, {.forwards = false});
    chassis.waitUntilDone();
    chassis.moveToPoint(-43, -44, 1500, {.forwards = false});
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 1000, {}, false);
    chassis.moveToPoint(-15, -49, 1500, {.forwards = false, .minSpeed = 127});
    chassis.waitUntilDone();
    intake_manager.set_state(IntakeState::UNJAM);
    chassis.arcade(-35, 0);
    pros::delay(250);
    intake_manager.set_state(IntakeState::SCORE_HIGH);
    matchload_bar.set_value(true);
    pros::delay(1500);
    chassis.arcade(0, 0);
    pros::delay(500);
    chassis.setPose(-15, -47, chassis.getPose().theta);
    chassis.moveToPoint(-61, -46, 1500, {.maxSpeed = 40}, false);
    intake_manager.set_state(IntakeState::INTAKE);
    chassis.arcade(25, 0);
    pros::delay(2250);
    chassis.arcade(0, 0);
    chassis.moveToPoint(-15, -48, 1500, {.forwards = false}, false);
    intake_manager.set_state(IntakeState::UNJAM);
    chassis.arcade(-25, 0);
    pros::delay(250);
    intake_manager.set_state(IntakeState::SCORE_HIGH);
    pros::delay(2000);
    chassis.arcade(0, 0);
    matchload_bar.set_value(false);
    chassis.moveToPoint(-25, -47, 1500, {}, false);
    chassis.turnToHeading(0, 750, {}, false);
    chassis.moveToPoint(-30, -1, 1500, {.maxSpeed = 70}, false);
    chassis.turnToHeading(-90, 750, {}, false);
    chassis.moveToPoint(-60, -1, 2000, {.maxSpeed = 70}, false);
    chassis.arcade(20, 0);
    pros::delay(1000);
    chassis.arcade(0, 0);
    pros::delay(750);
    chassis.arcade(50, 0);
    pros::delay(1500);
    while (true) {
        chassis.arcade(20, 0);
        pros::delay(333);
        chassis.arcade(-20, 0);
        pros::delay(333);
    }
}

void simple_skills(){
    intake_manager.set_state(IntakeState::SCORE_HIGH);
    chassis.arcade(20, 0);
    pros::delay(1000);
    chassis.arcade(0, 0);
    pros::delay(6000);
    chassis.arcade(50, 0);
    pros::delay(3000);
    while (true) {
        chassis.arcade(20, 0);
        pros::delay(1000);
        chassis.arcade(-20, 0);
        pros::delay(1000);
    }
}

// Array of auton names for display
const std::string auton_names[] = {
	"SAWP",
	"4 High Hook",
	"6 High + 3 Mid",
	"6 High + 3 Low",
	"Drive off Line",
	"Skills"
};

// Array of auton functions
typedef void (*auton_fn)();
const auton_fn autons[] = {
	sawp,
	four_hook,
	four_plus_three_mid,
	four_plus_three_low,
	drive_off,
	skills,
    simple_skills,
};

const size_t auton_count = sizeof(autons) / sizeof(autons[0]);
