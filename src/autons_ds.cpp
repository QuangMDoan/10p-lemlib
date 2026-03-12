#include "main.h"
#include "config.hpp"
#include "intake_manager.hpp"
#include "auton_utils.hpp"
#include "autons_ds.h"

// These functions always return +ve values.
float distanceFromRightSensor()
{
    return abs(66 - (right_distance_sensor.get() / 25.4));
}

float distanceFromLeftSensor()
{
    return abs(66 - (left_distance_sensor.get() / 25.4));
}

float distanceFromLeftFrontSensor()
{
    return abs(66 - (front_left_distance_sensor.get() / 25.4));
}

float distanceFromRightFrontSensor()
{
    return abs(66 - (front_left_distance_sensor.get() / 25.4));
}

void getToFirstDropOff()
{
    chassis.moveToPoint(-53, 47, 1000, {.forwards = false, .minSpeed = 90}); // 1000
    chassis.turnToPoint(-35, 58, 750, {.forwards = false, .minSpeed = 90});  // 750
    chassis.moveToPoint(-35, 58, 1250, {.forwards = false, .minSpeed = 90}); // 1500
    // chassis.turnToPoint(28, 58, 750, {.forwards = false, .minSpeed = 100});
    chassis.turnToHeading(-90, 750);
    matchload_bar.set_value(false);
    chassis.waitUntilDone();
    float intentedXLocation = 30;
    float intendedYLocation = 59;
    chassis.moveToPoint(intentedXLocation, intendedYLocation, 3000, {.forwards = false, .minSpeed = 80, .earlyExitRange = 3});
    // chassis.waitUntilDone();
    while (true)
    {
        if (chassis.getPose().x >= intentedXLocation)
        {
            break;
        }

        float currentY = distanceFromRightSensor();
        if (currentY <= 59)
        {
            // We got too close to the goal.
            // Reset the drivetrain location and continue.
            chassis.cancelAllMotions();
            // pros::lcd::print(3, "Y: %f\n", currentY);
            chassis.setPose(chassis.getPose().x, currentY, chassis.getPose().theta);
            chassis.moveToPoint(intentedXLocation, intendedYLocation, 3000, {.forwards = false, .minSpeed = 80, .earlyExitRange = 3});
            pros::delay(20);
        }
        pros::delay(10);
    }

    chassis.cancelAllMotions();
    float currentY = distanceFromRightSensor();
    chassis.setPose(chassis.getPose().x, currentY, chassis.getPose().theta);

    // chassis.swingToHeading(90, DriveSide::LEFT, 1500, {.direction = AngularDirection::CW_CLOCKWISE});
    // chassis.waitUntilDone();
    chassis.moveToPose(37, 47, 90, 1800, {.forwards = false});
    chassis.waitUntilDone();

    currentY = distanceFromLeftSensor();
    float currentX = (distanceFromLeftFrontSensor() + distanceFromRightFrontSensor()) / 2;
    chassis.setPose(currentX, currentY, chassis.getPose().theta);
}

void getToThirdDropOff()
{
    chassis.moveToPoint(50, -47, 1000, {.forwards = false, .minSpeed = 100});
    chassis.turnToPoint(37, -58, 750, {.forwards = false, .minSpeed = 100}, false);
    chassis.moveToPoint(37, -58, 1000, {.forwards = false, .minSpeed = 100}, false);
    // chassis.turnToPoint(-28, -61, 750, {.forwards = false, .minSpeed = 100}, false);
    chassis.turnToHeading(90, 750);
    matchload_bar.set_value(false);
    chassis.waitUntilDone();
    float intentedXLocation = -32;
    float intendedYLocation = -60;
    chassis.moveToPoint(intentedXLocation, intendedYLocation, 3000, {.forwards = false, .minSpeed = 100});
    while (true)
    {
        if (chassis.getPose().x <= intentedXLocation)
        {
            break;
        }

        float currentY = distanceFromRightSensor();
        if (currentY <= 59)
        {
            // We got too close to the goal.
            // Reset the drivetrain location and continue.
            chassis.cancelAllMotions();
            // pros::lcd::print(3, "Y: %f\n", currentY);
            // Need to make the currentY negative as its in the third quadrant
            chassis.setPose(chassis.getPose().x, -1 * currentY, chassis.getPose().theta);
            chassis.moveToPoint(intentedXLocation, intendedYLocation, 3000, {.forwards = false, .minSpeed = 100});
            pros::delay(20);
        }
        pros::delay(10);
    }
    chassis.cancelAllMotions();
    float currentY = distanceFromRightSensor();
    chassis.setPose(chassis.getPose().x, -1 * currentY, chassis.getPose().theta);

    // chassis.swingToHeading(90, DriveSide::LEFT, 1500, {.direction = AngularDirection::CW_CLOCKWISE});
    // chassis.waitUntilDone();
    chassis.moveToPose(-25, -46.5, -90, 2000, {.forwards = false, .earlyExitRange = 3});
    chassis.waitUntilDone();

    currentY = -1 * distanceFromLeftSensor();
    float currentX = -1 * (distanceFromLeftFrontSensor() + distanceFromRightFrontSensor()) / 2;
    chassis.setPose(currentX, currentY, chassis.getPose().theta);

    // pros::lcd::print(0, "X: %f", currentX);                    // x
    // pros::lcd::print(1, "Y: %f", currentY);                    // y
    // pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
}

void skills_ds()
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
    float soft_reset_y = (left_distance_sensor.get() / 25.4) - 66.14;
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
    chassis.turnToPoint(-5.5, 2.5, 750, {.forwards = false});
    chassis.waitUntilDone();
    intake_manager.set_state(IntakeState::INTAKE);
    chassis.moveToPoint(-5.5, 2.5, 1000, {.forwards = false});
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

    // Get to the frist dropoff on the other side of the field.
    // chassis.setPose(-65, 47, -90);
    getToFirstDropOff();

    // score balls from first matchloader
    chassis.moveToPoint(14, 46, 1000, {.forwards = false, .maxSpeed = 100, .minSpeed = 80});
    chassis.waitUntilDone();
    pros::delay(300);
    intake_manager.set_state(IntakeState::SCORE_HIGH);
    chassis.arcade(-30, 0);
    pros::delay(2000);
    chassis.arcade(0, 0);
    lemlib::Pose p = chassis.getPose();
    chassis.setPose(p.x, distanceFromLeftSensor(), p.theta);

    // go to second matchloader
    chassis.moveToPose(68, 46.5, 90, 1500, {.lead = 0.01, .maxSpeed = 50});
    matchload_bar.set_value(true);
    chassis.waitUntilDone();
    intake_manager.set_state(IntakeState::INTAKE);
    chassis.arcade(20, 0);
    pros::delay(1500);
    chassis.arcade(0, 0);

    // score balls from second matchloader
    chassis.moveToPoint(10, 47, 1250, {.forwards = false, .maxSpeed = 80});
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

    // Align against the park zone.
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

    // Get to the third dropoff zone.
    getToThirdDropOff();

    // score blocks from third matchloader
    chassis.moveToPoint(-7, -48, 1000, {.forwards = false, .minSpeed = 127}, false);
    pros::delay(300);
    intake_manager.set_state(IntakeState::SCORE_HIGH);
    chassis.arcade(-10, 0);
    pros::delay(1500);
    chassis.arcade(0, 0);
    lemlib::Pose p1 = chassis.getPose();
    chassis.setPose(p1.x, -1 * distanceFromLeftSensor(), p1.theta);
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
    chassis.moveToPoint(-21, -43, 1000, {}, false);
    chassis.turnToHeading(0, 750, {}, false);
    chassis.moveToPoint(-21, -2, 1500, {}, false);
    chassis.turnToHeading(-90, 750, {}, false);
    chassis.arcade(127, 0);
}

/*
// Array of auton names for display
const std::string auton_names[] = {
    "SkillsDS"};

// Array of auton functions
typedef void (*auton_fn)();
const auton_fn autons[] = {
    skills_ds,
};

const size_t auton_count = sizeof(autons) / sizeof(autons[0]);
*/
