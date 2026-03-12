#include "main.h"
#include "config.hpp"
#include "intake_manager.hpp"
#include "auton_utils.hpp"

void sawp()
{
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.setPose(-49, -17, 180);
    chassis.moveToPoint(-48, -50, 1000);
    intake_manager.set_state(IntakeState::INTAKE);
    chassis.waitUntilDone();
    chassis.turnToHeading(-90, 750);
    matchload_bar.set_value(true);
    chassis.waitUntilDone();
    chassis.moveToPoint(-64, -53, 1000, {.maxSpeed = 50});
    chassis.waitUntilDone();
    chassis.moveToPoint(-23, -53, 1000, {.forwards = false, .minSpeed = 100});
    chassis.waitUntil(42);
    intake_manager.set_state(IntakeState::SCORE_HIGH);
    chassis.waitUntilDone();
    chassis.arcade(-10, 0);
    pros::delay(600);
    chassis.arcade(0, 0);
    matchload_bar.set_value(false);
    chassis.swingToPoint(-22, -24, DriveSide::RIGHT, 750);
    chassis.waitUntilDone();
    chassis.moveToPoint(-22, -24, 750, {.maxSpeed = 60});
    intake_manager.set_state(IntakeState::INTAKE);
    chassis.waitUntilDone();
    chassis.swingToPoint(-24, 20, DriveSide::LEFT, 500);
    chassis.waitUntilDone();
    chassis.moveToPoint(-24, 20, 1250, {.maxSpeed = 75});
    chassis.waitUntilDone();
    matchload_bar.set_value(true);
    chassis.swingToPoint(-44, 35, DriveSide::LEFT, 500);
    chassis.waitUntilDone();
    chassis.moveToPoint(-44, 35, 1000);
    chassis.waitUntilDone();
    chassis.turnToHeading(-90, 750);
    chassis.waitUntilDone();

    float soft_reset_y = 66 - right_distance_sensor.get() / 25.4;
    chassis.setPose(chassis.getPose().x, soft_reset_y, -90);

    chassis.moveToPoint(-15, 46, 750, {.forwards = false, .minSpeed = 100});
    chassis.waitUntil(10);
    intake_manager.set_state(IntakeState::SCORE_HIGH);
    chassis.arcade(-30, 0);
    pros::delay(600);
    chassis.arcade(0, 0);
    chassis.moveToPose(-62, 47, -90, 1000, {.maxSpeed = 50});
    matchload_bar.set_value(true);
    intake_manager.set_state(IntakeState::INTAKE);
    chassis.waitUntilDone();
    chassis.arcade(50, 0);
    pros::delay(600);
    chassis.arcade(0, 0);

    chassis.moveToPoint(-43, 46, 750, {.forwards = false, .minSpeed = 75, .earlyExitRange = 2});
    chassis.waitUntilDone();
    chassis.swingToPoint(-11, 6, DriveSide::LEFT, 750, {.forwards = false});
    chassis.waitUntilDone();
    chassis.moveToPoint(-11, 6, 1500, {.forwards = false});
    chassis.waitUntil(30);
    intake_manager.set_state(IntakeState::SCORE_MID);
}

void four_hook()
{
    // Autonomous routine here
}

void four_plus_three_mid()
{
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
    AutonUtils::startDriveDistance(34, false, 127, 1000);
    AutonUtils::waitUntilDistanceTraveled(26);
    intake_manager.set_state(IntakeState::SCORE_HIGH);
    AutonUtils::waitUntilDriveDone();
    chassis.turnToHeading(90, 500);
    chassis.waitUntilDone();
    pros::delay(500);
    AutonUtils::driveDistance(11.5, true, 127, 650);
    chassis.turnToHeading(-30, 750);
    matchload_bar.set_value(false);
    intake_manager.set_state(IntakeState::INTAKE);
    chassis.waitUntilDone();
    AutonUtils::driveDistance(25, true, 60, 750);
    chassis.turnToHeading(147, 750);
    chassis.waitUntilDone();
    AutonUtils::driveDistance(20, false, 127, 750);
    intake_manager.set_state(IntakeState::SCORE_MID);
    pros::delay(1000);
    AutonUtils::driveDistance(35.5, true, 127, 1000);
    chassis.turnToHeading(85, 750);
    wing.set_value(true);
    chassis.waitUntilDone();
    AutonUtils::driveDistance(25, false, 40, 1500);
}

void four_plus_three_low()
{
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

void drive_off()
{
    chassis.setPose(0, 0, 0);
    chassis.moveToPoint(0, 5, 10000);
    chassis.waitUntilDone();
    chassis.arcade(0, 0);
}

void jiggle_task(void *param)
{
    while (true)
    {
        chassis.turnToHeading(30, 300, {.minSpeed = 120});
        pros::delay(400);
        chassis.turnToHeading(-30, 300, {.minSpeed = 120});
        pros::delay(400);
    }
}

void seventy_skills()
{
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
    chassis.moveToPoint(22, 59, 3000, {.forwards = false, .maxSpeed = 75});
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
    float heading_before_goal = chassis.getPose().theta;
    chassis.setPose(27, 47, heading_before_goal);
    chassis.moveToPoint(62, 48, 1500, {.maxSpeed = 60});
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
    chassis.moveToPoint(-15, -48, 1500, {.forwards = false, .minSpeed = 127});
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
    chassis.moveToPoint(-15, -47, 1500, {.forwards = false}, false);
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
    while (true)
    {
        chassis.arcade(20, 0);
        pros::delay(333);
        chassis.arcade(-20, 0);
        pros::delay(333);
    }
}

void skills()
{
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    intake_manager.set_state(IntakeState::INTAKE);
    chassis.setPose(-55, 0, -90);
    chassis.arcade(20, 0);
    pros::delay(650);
    chassis.arcade(-10, 0);
    pros::delay(200);
    chassis.arcade(0, 0);
    pros::delay(1000);
    chassis.arcade(50, 0);
    pros::delay(650);

    chassis.arcade(-20, 0);
    pros::delay(400);
    chassis.arcade(0, 0);

    pros::delay(500);

    chassis.arcade(-67, 0);
    pros::delay(900);
    chassis.arcade(0, 0);

    pros::delay(100);

    chassis.turnToHeading(-90, 400);
    chassis.waitUntilDone();

    // chassis.arcade(20, 0);
    // pros::delay(1000);

    // 17 in
    float soft_reset_x = -62 + (front_left_distance_sensor.get() + front_right_distance_sensor.get()) / 50.8;
    float soft_reset_y = left_distance_sensor.get() / 25.4 - 66.14;
    chassis.setPose(soft_reset_x, soft_reset_y, -90);

    chassis.moveToPoint(-29, 0, 1000, {.forwards = false});
    chassis.waitUntilDone();

    chassis.turnToPoint(-20, 17, 750);
    chassis.waitUntilDone();
    chassis.moveToPoint(-20, 17, 1500, {.maxSpeed = 50});
    pros::delay(1050);
    intake_manager.set_state(IntakeState::IDLE);
    chassis.waitUntilDone();

    // get to mid goal
    chassis.turnToPoint(-4, 4, 750, {.forwards = false});
    chassis.waitUntilDone();
    intake_manager.set_state(IntakeState::INTAKE);
    chassis.moveToPoint(-4, 4, 1000, {.forwards = false});
    matchload_bar.set_value(true);
    chassis.waitUntilDone();

    chassis.arcade(30, 0);
    pros::delay(70);
    intake_manager.set_state(IntakeState::SCORE_HIGH);
    pros::delay(75);
    chassis.arcade(0, 0);

    intake_manager.set_state(IntakeState::SCORE_MID_SKILLS);
    pros::delay(4250);
    matchload_bar.set_value(false);

    chassis.arcade(-20, 0);
    pros::delay(200);
    chassis.arcade(0, 0);
    pros::delay(100);

    chassis.moveToPoint(-43, 45, 2000);
    pros::delay(100);
    intake_manager.set_state(IntakeState::INTAKE);
    chassis.waitUntilDone();
    matchload_bar.set_value(true);
    chassis.turnToHeading(-90, 1000, {.maxSpeed = 70});
    chassis.waitUntilDone();

    // get to first matchloader
    soft_reset_y = 66 - right_distance_sensor.get() / 25.4;
    chassis.setPose(chassis.getPose().x, soft_reset_y, -90);
    chassis.moveToPoint(-65, 47, 1000, {.maxSpeed = 40});
    intake_manager.set_state(IntakeState::INTAKE);
    chassis.waitUntilDone();
    chassis.arcade(50, 0);
    pros::delay(1500);
    chassis.arcade(0, 0);
    chassis.moveToPoint(-53, 47, 1000, {.forwards = false, .minSpeed = 90});
    chassis.waitUntilDone();
    chassis.turnToPoint(-35, 57, 750, {.forwards = false, .minSpeed = 90});
    chassis.waitUntilDone();
    chassis.moveToPoint(-35, 57, 1500, {.forwards = false, .minSpeed = 90});
    chassis.waitUntilDone();
    // chassis.turnToPoint(28, 58, 750, {.forwards = false, .minSpeed = 100});
    chassis.turnToHeading(-90, 750);
    matchload_bar.set_value(false);
    chassis.waitUntilDone();
    chassis.moveToPoint(30, 60, 3000, {.forwards = false, .minSpeed = 80, .earlyExitRange = 3});
    chassis.waitUntilDone();
    // chassis.swingToHeading(90, DriveSide::LEFT, 1500, {.direction = AngularDirection::CW_CLOCKWISE});
    // chassis.waitUntilDone();
    chassis.turnToPoint(37, 47, 750, {.forwards = false, .minSpeed = 60});
    chassis.waitUntilDone();
    chassis.moveToPoint(37, 47, 1250, {.forwards = false});
    chassis.waitUntilDone();
    chassis.turnToHeading(90, 750);
    chassis.waitUntilDone();

    // score balls from first matchloader
    soft_reset_y = 66 - (left_distance_sensor.get() / 25.4);
    chassis.setPose(chassis.getPose().x, soft_reset_y, chassis.getPose().theta);
    chassis.moveToPoint(15, 48, 1000, {.forwards = false, .maxSpeed = 100});
    chassis.waitUntilDone();
    intake_manager.set_state(IntakeState::SCORE_HIGH);
    chassis.arcade(-30, 0);
    pros::delay(1500);
    chassis.arcade(0, 0);

    // go to second matchloader
    chassis.moveToPose(68, 48, 90, 1500, {.lead = 0.01, .maxSpeed = 50});
    matchload_bar.set_value(true);
    chassis.waitUntilDone();
    intake_manager.set_state(IntakeState::INTAKE);
    chassis.arcade(20, 0);
    pros::delay(1500);
    chassis.arcade(0, 0);

    // score balls from second matchloader
    chassis.moveToPoint(10, 48, 1250, {.forwards = false, .maxSpeed = 100});
    chassis.waitUntilDone();
    intake_manager.set_state(IntakeState::SCORE_HIGH);
    chassis.arcade(-30, 0);
    pros::delay(1800);
    matchload_bar.set_value(false);
    chassis.arcade(0, 0);

    float heading = chassis.getPose().theta;
    chassis.setPose(15, 52, heading);
    chassis.moveToPoint(35, 52, 1000);
    chassis.waitUntilDone();
    intake_manager.set_state(IntakeState::INTAKE);

    pros::delay(100000);

    // clear opposite park zone
    chassis.moveToPoint(54, 25, 1500);
    chassis.waitUntilDone();
    chassis.turnToHeading(170, 500);
    chassis.waitUntilDone();
    chassis.arcade(67, 0);
    pros::delay(2000);
    chassis.turnToHeading(-165, 750);
    chassis.waitUntilDone();
    chassis.arcade(0, 0);
    chassis.arcade(-30, 0);
    pros::delay(1800);
    chassis.arcade(0, 0);

    soft_reset_x = 67 - left_distance_sensor.get() / 25.4;
    soft_reset_y = -64 + front_right_distance_sensor.get() / 25.4;
    chassis.setPose(soft_reset_x, soft_reset_y, 180);

    chassis.moveToPoint(45, -52, 2000);
    intake_manager.set_state(IntakeState::UNJAM);
    pros::delay(150);
    intake_manager.set_state(IntakeState::INTAKE);
    chassis.waitUntilDone();
    chassis.turnToHeading(90, 1250);
    matchload_bar.set_value(true);
    intake_manager.set_state(IntakeState::SCORE_HIGH);
    pros::delay(350);
    intake_manager.set_state(IntakeState::INTAKE);
    chassis.waitUntilDone();

    pros::delay(50);

    // go to third matchloader
    soft_reset_y = -66 + right_distance_sensor.get() / 25.4;
    chassis.setPose(chassis.getPose().x, soft_reset_y, chassis.getPose().theta);
    chassis.moveToPoint(65, -47, 1000, {.maxSpeed = 50});
    chassis.waitUntilDone();
    chassis.arcade(20, 0);
    pros::delay(1600);
    chassis.arcade(0, 0);
    chassis.moveToPoint(50, -47, 1000, {.forwards = false, .minSpeed = 100});
    chassis.turnToPoint(35, -58, 750, {.forwards = false, .minSpeed = 100}, false);
    chassis.moveToPoint(35, -58, 1000, {.forwards = false, .minSpeed = 100}, false);
    // chassis.turnToPoint(-28, -61, 750, {.forwards = false, .minSpeed = 100}, false);
    chassis.turnToHeading(90, 750, {}, false);
    matchload_bar.set_value(false);
    chassis.moveToPoint(-28, -60, 3000, {.forwards = false, .minSpeed = 100}, false);
    chassis.turnToPoint(-32, -47, 750, {.forwards = false, .minSpeed = 100}, false);
    chassis.moveToPoint(-32, -47, 1250, {.forwards = false}, false);
    chassis.turnToHeading(-90, 750, {}, false);

    // score blocks from third matchloader
    soft_reset_y = -66 + left_distance_sensor.get() / 25.4;
    chassis.setPose(chassis.getPose().x, soft_reset_y, -90);
    chassis.moveToPoint(-7, -48, 1000, {.forwards = false, .minSpeed = 127}, false);

    intake_manager.set_state(IntakeState::SCORE_HIGH);
    chassis.arcade(-10, 0);
    pros::delay(1500);
    chassis.arcade(0, 0);
    matchload_bar.set_value(true);

    // go to fourth matchloader
    chassis.moveToPose(-72, -47, -90, 1250, {.lead = 0.01, .maxSpeed = 50}, false);
    intake_manager.set_state(IntakeState::INTAKE);
    chassis.arcade(20, 0);
    pros::delay(1500);
    chassis.arcade(0, 0);

    // score blocks from fourth matchloader
    chassis.moveToPoint(-7, -48, 1750, {.forwards = false, .minSpeed = 100}, false);
    intake_manager.set_state(IntakeState::SCORE_HIGH);
    chassis.arcade(-10, 0);
    pros::delay(1500);
    matchload_bar.set_value(false);
    chassis.arcade(0, 0);

    // Park
    chassis.moveToPoint(-21, -50, 1000, {}, false);
    chassis.turnToHeading(0, 750, {}, false);
    chassis.moveToPoint(-21, -2, 1500, {}, false);
    chassis.turnToHeading(-90, 750, {}, false);
    chassis.arcade(127, 0);
}

void simple_skills()
{
    intake_manager.set_state(IntakeState::SCORE_HIGH);
    chassis.arcade(20, 0);
    pros::delay(1000);
    chassis.arcade(0, 0);
    pros::delay(6000);
    chassis.arcade(50, 0);
    pros::delay(3000);
    while (true)
    {
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
    "Skills"};

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
