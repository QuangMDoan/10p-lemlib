#include "lemlib/api.hpp" // IWYU pragma: keep
#include "main.h"
#include "config.hpp"
#include "intake_manager.hpp"
#include "autons.h"
#include "lemlib/pose.hpp"
#include "liblvgl/llemu.hpp"
#include "pid_tune.hpp"
#include "pros/llemu.hpp"
#include "pros/misc.h"

// Set pid_tuning_mode to true to enable pid tuning
volatile bool pid_tuning_mode = false;
static PidTune tuning = PidTune(PidTarget::ANGULAR); 
/**
 * A callback function for LLEMU's center button.
 *
 */
void on_center_button() {
	pid_tuning_mode = !pid_tuning_mode;
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	chassis.calibrate(); // calibrate sensors
	pros::Task screen_task([&]() {
		while (true) {
			if (pid_tuning_mode) {
				pros::lcd::print(2, "tuning: %s", tuning.targetName());
				pros::lcd::print(3, "lateral kP, kD: %.3f, %.3f", lateral_controller.kP, lateral_controller.kD);
				pros::lcd::print(4, "angular kP, kD: %.3f, %.3f", angular_controller.kP, angular_controller.kD);
			}

			lemlib::Pose pose = chassis.getPose();
			pros::lcd::print(0, "x,y,theta: %.3f, %.3f, %.3f", pose.x, pose.y, pose.theta); // x
			pros::delay(250);
		}
	});
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous()
{
	sawp();
}
/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
	bool matchload_state = false;
	static bool y_pressed = false;

	if (pid_tuning_mode) {
		while(true){
			tuning.tune(master);
			pros::delay(10);
		}
	}

	while (true) {
		// ============ DRIVETRAIN CONTROL ============
		int left_stick = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int right_stick = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		chassis.arcade(left_stick, right_stick);

		// ============ INTAKE CONTROL ============
		// Priority: R1 > L2 > L1 > X (highest to lowest priority)
		// If multiple buttons pressed, the highest priority one wins

		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
		{
			intake_manager.set_state(IntakeState::INTAKE);
		}

		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
		{
			intake_manager.set_state(IntakeState::SCORE_MID);
		}

		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
		{
			intake_manager.set_state(IntakeState::SCORE_LOW);
		}

		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_X))
		{
			intake_manager.set_state(IntakeState::SCORE_HIGH);
		}

		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B))
		{
			intake_manager.set_state(IntakeState::SCORE_MID_SKILLS);
		}

		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_Y))
		{
			intake_manager.set_state(IntakeState::SCORE_LOW_SKILLS);
		}

		else
		{
			pros::delay(10);
			intake_manager.set_state(IntakeState::IDLE);
		}

		// Y button toggle for matchload and intake lift
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_Y) && !y_pressed)
		{
			matchload_bar.set_value(true);
			intake_lift.set_value(true);
			y_pressed = true;
		}
		else if (!master.get_digital(pros::E_CONTROLLER_DIGITAL_Y) && y_pressed)
		{
			matchload_bar.set_value(false);
			intake_lift.set_value(false);
			y_pressed = false;
		}

		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A))
		{
			matchload_state = !matchload_state;
			matchload_bar.set_value(matchload_state);
			pros::delay(200);
		}

		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
		{
			wing.set_value(true);
		}

		else
		{
			wing.set_value(false);
		}

		pros::delay(10);
	}
}