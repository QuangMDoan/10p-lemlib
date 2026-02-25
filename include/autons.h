#ifndef AUTONS_H
#define AUTONS_H

#include <string>

// Autonomous routine declarations
void sawp();
void four_hook();
void four_plus_three_mid();
void four_plus_three_low();
void drive_off();
void skills();
void seventy_skills();
void simple_skills();

// Auton selection arrays
extern const std::string auton_names[];
typedef void (*auton_fn)();
extern const auton_fn autons[];
extern const size_t auton_count;

#endif // AUTONS_H