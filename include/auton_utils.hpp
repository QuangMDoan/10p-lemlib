#ifndef AUTON_UTILS_HPP
#define AUTON_UTILS_HPP

#include "config.hpp"
#include <cmath>
#include <algorithm>

namespace AutonUtils {

	/* ================= ENUMS ================= */

	enum class DistanceComparison {
		LESS_THAN,
		GREATER_THAN,
		LESS_EQUAL,
		GREATER_EQUAL
	};

	/* ================= BASIC LEMLIB DRIVING ================= */

	inline void driveDistance(float distance_inches, bool forwards = true,
	                          float maxSpeed = 127, int timeout_ms = 5000) {

		lemlib::Pose pose = chassis.getPose();

		float dist = forwards ? std::abs(distance_inches) : -std::abs(distance_inches);

		float heading_rad = pose.theta * M_PI / 180.0f;
        float target_x = pose.x + dist * std::sin(heading_rad);
        float target_y = pose.y + dist * std::cos(heading_rad);

		chassis.moveToPoint(
			target_x,
			target_y,
			timeout_ms,
			{ .forwards = forwards, .maxSpeed = maxSpeed }
		);
        chassis.waitUntilDone();
	}

	inline void driveForwardDistance(float distance_inches,
	                                 int maxSpeed = 127,
	                                 int timeout_ms = 5000) {
		driveDistance(distance_inches, true, maxSpeed, timeout_ms);
	}

	inline void driveBackwardDistance(float distance_inches,
	                                  int maxSpeed = 127,
	                                  int timeout_ms = 5000) {
		driveDistance(distance_inches, false, maxSpeed, timeout_ms);
	}

	/* ================= SENSOR-BASED DRIVING ================= */

	inline float smoothDistanceInches(pros::Distance& sensor) {
		// 5-sample moving average to kill jitter
		const int SAMPLES = 3;
		float sum = 0;
		int valid = 0;

		for (int i = 0; i < SAMPLES; i++) {
			int mm = sensor.get();
			if (mm > 0) {
				sum += mm / 25.4f;
				valid++;
			}
			pros::delay(2);
		}

		if (valid == 0) return -1;
		return sum / valid;
	}

	inline bool driveUntilDistanceSensor(
		pros::Distance& sensor,
		float target_distance,
		DistanceComparison comparison,
		bool forwards = true,
		int maxSpeed = 60,
		int minSpeed = 30,
		int timeout_ms = 1500
	) {
		maxSpeed = std::clamp(maxSpeed, 0, 127);
		minSpeed = std::clamp(minSpeed, 0, maxSpeed);

		// BIG decel buffer – tune 8–12 inches depending on robot
		const float DECEL_BUFFER = 6.0f;

		// Predictive stopping based on speed (inches)
		const float STOP_OFFSET = (maxSpeed / 127.0f) * 4.0f;

		unsigned long start = pros::millis();

		left_motor_group.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
		right_motor_group.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

		while (pros::millis() - start < (unsigned long)timeout_ms) {

			float dist = smoothDistanceInches(sensor);
			if (dist < 0) {
				int cmd = forwards ? maxSpeed : -maxSpeed;
				left_motor_group.move(cmd);
				right_motor_group.move(cmd);
				continue;
			}

			bool condition_met = false;
			switch (comparison) {
				case DistanceComparison::LESS_THAN:
					condition_met = (dist < target_distance + STOP_OFFSET);
					break;
				case DistanceComparison::LESS_EQUAL:
					condition_met = (dist <= target_distance + STOP_OFFSET);
					break;
				case DistanceComparison::GREATER_THAN:
					condition_met = (dist > target_distance - STOP_OFFSET);
					break;
				case DistanceComparison::GREATER_EQUAL:
					condition_met = (dist >= target_distance - STOP_OFFSET);
					break;
			}

			if (condition_met) {
				left_motor_group.move(0);
				right_motor_group.move(0);
				pros::delay(80);
				return true;
			}

			float error = std::abs(dist - target_distance);
			int speed = maxSpeed;

			if (error < DECEL_BUFFER) {
				float ratio = error / DECEL_BUFFER;
				speed = minSpeed + (int)((maxSpeed - minSpeed) * ratio);
			}

			int cmd = forwards ? speed : -speed;
			left_motor_group.move(cmd);
			right_motor_group.move(cmd);

			pros::delay(10);
		}

		left_motor_group.move(0);
		right_motor_group.move(0);
		pros::delay(80);
		return false;
	}

	/* ================= WALL HELPERS ================= */

	inline bool driveUntilFrontWall(float target_distance,
	                                bool forwards = true,
	                                int maxSpeed = 60,
	                                int minSpeed = 30,
	                                int timeout_ms = 1500) {

		pros::Distance* sensor = nullptr;

		if (front_right_distance_sensor.get() > 0) {
			sensor = &front_right_distance_sensor;
		} else if (front_left_distance_sensor.get() > 0) {
			sensor = &front_left_distance_sensor;
		}

		if (!sensor) return false;

		return driveUntilDistanceSensor(
			*sensor,
			target_distance,
			DistanceComparison::LESS_THAN,
			forwards,
			maxSpeed,
			minSpeed,
			timeout_ms
		);
	}

	inline bool driveUntilLeftWall(float target_distance,
	                               bool forwards = true,
	                               int maxSpeed = 60,
	                               int minSpeed = 30,
	                               int timeout_ms = 1500) {

		if (left_distance_sensor.get() <= 0) return false;

		return driveUntilDistanceSensor(
			left_distance_sensor,
			target_distance,
			DistanceComparison::LESS_THAN,
			forwards,
			maxSpeed,
			minSpeed,
			timeout_ms
		);
	}

}

#endif // AUTON_UTILS_HPP