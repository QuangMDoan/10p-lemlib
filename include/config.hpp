#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "pros/motors.hpp"
#include "pros/imu.hpp"
#include "pros/adi.hpp"
#include "pros/distance.hpp"
#include "lemlib/api.hpp"

// Motor Ports
constexpr int INTAKE_PORT = 3;
constexpr int MIDDLE_ROLLER_PORT = 2;
constexpr int TOP_ROLLER_PORT = -1;

// ============ MOTOR OBJECTS ============

// Intake Motor
inline pros::Motor intake(INTAKE_PORT, pros::v5::MotorGears::blue);

// Roller Motors
inline pros::Motor middle_roller(MIDDLE_ROLLER_PORT, pros::v5::MotorGears::blue);
inline pros::Motor top_roller(TOP_ROLLER_PORT, pros::v5::MotorGears::blue);

// Pneumatics
inline pros::adi::DigitalOut wing('D');
inline pros::adi::DigitalOut matchload_bar('A');
inline pros::adi::DigitalOut stopper('C'); // expansion solenoid

// ============ DRIVETRAIN ============
// left motor group
inline pros::MotorGroup left_motor_group({-14, -15, -16}, pros::MotorGears::blue);
// right motor group
inline pros::MotorGroup right_motor_group({12, 18, 19}, pros::MotorGears::blue);

// drivetrain settings
inline lemlib::Drivetrain drivetrain(&left_motor_group, // left motor group
                              &right_motor_group, // right motor group
                              11.5, // 10 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 4" omnis
                              450, // drivetrain rpm is 360
                              2 // horizontal drift is 2 (for now)
);

// ============ SENSORS ============

// imu
inline pros::Imu imu(13);

// Distance sensors for DSR (Distance Sensor Reset)
// Note: Some may not be wired yet
inline pros::Distance left_distance_sensor(4);     // left side distance sensor
inline pros::Distance front_left_distance_sensor(7);   // front left distance sensor
inline pros::Distance front_right_distance_sensor(6);  // front right distance sensor

// ============ ODOMETRY ============

// odometry settings
inline lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// ============ PID CONTROLLERS ============

// lateral PID controller
inline lemlib::ControllerSettings lateral_controller(9, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              40, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// angular PID controller
inline lemlib::ControllerSettings angular_controller(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// ============ CHASSIS ============

// create the chassis
inline lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);

#endif // CONFIG_HPP
