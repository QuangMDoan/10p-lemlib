#ifndef INTAKE_MANAGER_HPP
#define INTAKE_MANAGER_HPP

#include "config.hpp"

enum class IntakeState
{
	IDLE,
	SCORE_LOW,
	SCORE_MID,
	SCORE_HIGH,
	INTAKE,
	SCORE_MID_SKILLS,
	SCORE_LOW_SKILLS,
	UNJAM,
	SCORE_MID_FAST
};

class IntakeManager
{
private:
	IntakeState current_state = IntakeState::IDLE;
	uint32_t last_high_goal_time = 0;

public:
	IntakeManager()
	{
		// Set all motors to hold
		intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
		middle_roller.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
		top_roller.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	}

	void set_state(IntakeState state)
	{
		if (current_state == IntakeState::SCORE_HIGH && state != IntakeState::SCORE_HIGH)
		{
			last_high_goal_time = pros::millis();
		}

		current_state = state;
		update();
	}

	IntakeState get_state() const
	{
		return current_state;
	}

	void update()
	{

		bool in_cooldown = (pros::millis() - last_high_goal_time) < 250;

		switch (current_state)
		{
		case IntakeState::IDLE:
			stopper.set_value(in_cooldown ? false : true);
			intake.move(0);
			middle_roller.move(0);
			top_roller.move(0);
			break;

		case IntakeState::SCORE_LOW:
			// all rollers run reversed
			stopper.set_value(in_cooldown ? false : true);
			intake.move(-127);
			middle_roller.move(-127);
			top_roller.move(-127);
			break;

		case IntakeState::SCORE_MID:
			// intake and middle roller run forward, top roller runs reversed
			stopper.set_value(in_cooldown ? false : true);
			intake.move(127);
			middle_roller.move(127);
			top_roller.move(-67);
			break;

		case IntakeState::SCORE_HIGH:
			// all rollers run forward
			stopper.set_value(false);
			intake.move(127);
			middle_roller.move(127);
			top_roller.move(127);
			break;

		case IntakeState::INTAKE:
			// intake and middle roller run forward, top roller is idle
			stopper.set_value(true);
			intake.move(127);
			middle_roller.move(127);
			top_roller.move(36);
			break;

		case IntakeState::SCORE_MID_SKILLS:
			// intake and middle roller run forward, top roller runs reversed
			stopper.set_value(in_cooldown ? false : true);
			intake.move(127);
			middle_roller.move(35);
			top_roller.move(-25);
			break;

		// TODO: tune with pistonized intake once built
		case IntakeState::SCORE_LOW_SKILLS:
			// all rollers run reversed
			stopper.set_value(in_cooldown ? false : true);
			intake.move(-40);
			middle_roller.move(-127);
			top_roller.move(-127);
			break;

		case IntakeState::UNJAM:
			intake.move(-127);
			middle_roller.move(-127);
			break;

		case IntakeState::SCORE_MID_FAST:
			stopper.set_value(in_cooldown ? false : true);
			intake.move(127);
			middle_roller.move(127);
			top_roller.move(-127);
			break;
		}
	}
};

// Global intake manager instance
inline IntakeManager intake_manager;

#endif // INTAKE_MANAGER_HPP
