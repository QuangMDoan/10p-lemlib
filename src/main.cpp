#include "lemlib/api.hpp" // IWYU pragma: keep
#include "main.h"
#include "config.hpp"
#include "intake_manager.hpp"
#include "autons.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button()
{
	static bool pressed = false;
	pressed = !pressed;
	
	// TODO: we should change this to a more useful, such as an autonomous selector 
	// or a screen for displaying information about the robot.
	if (pressed)
	{
		pros::lcd::set_text(3, "I was pressed!");
	}
	else
	{
		pros::lcd::clear_line(3);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
	pros::lcd::initialize();
	pros::lcd::register_btn1_cb(on_center_button);

	pros::lcd::set_text(2, "Init: calibrating sensors");
	chassis.calibrate();

	const auto imu_status = imu.get_status();
	if (imu_status == pros::ImuStatus::ready) {
		pros::lcd::set_text(2, "IMU ready");
	} else if (imu_status == pros::ImuStatus::calibrating) {
		pros::lcd::set_text(2, "IMU still calibrating");
	} else {
		pros::lcd::set_text(2, "IMU calibrating error");
	}

	static pros::Task screen_task([]() {
			while (true)
			{
				const auto pose = chassis.getPose();
				pros::lcd::print(1, "x, y, theta: %.2f, %.2f, %.1f", 
					pose.x, pose.y, pose.theta);

				pros::delay(500);
			}
		}, "Pose display");
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
	skills();
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
void opcontrol()
{
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
	bool matchload_state = false;
	static bool y_pressed = false;

	while (true)
	{
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

		// Y button toggle for matchload sequence
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_Y) && !y_pressed)
		{
			matchload_bar.set_value(true);
			pros::delay(150);
			intake_lift.set_value(true);
			pros::delay(150);
			matchload_bar.set_value(false);
			intake_manager.set_state(IntakeState::SCORE_HIGH);
			y_pressed = true;
		}
		else if (!master.get_digital(pros::E_CONTROLLER_DIGITAL_Y) && y_pressed)
		{
			intake_manager.set_state(IntakeState::IDLE);
			intake_lift.set_value(false);
			pros::delay(100);
			matchload_bar.set_value(false);
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