// breakbeam IR sensor pins
const uint8_t BREAKBEAM_PIN = 1;

// pump motor driver pins
const uint8_t PUMP_INA1_PIN = 2;
const uint8_t PUMP_INA2_PIN = 3;
const uint8_t PUMP_PWMA_PIN = 4;

// UR GPIO pins
const uint8_t UR_READY_PIN = 5;
const uint8_t UR_TO_HOLDER_PIN = 6;
const uint8_t UR_TO_STOW_PIN = 7;

// PWM configuration
const uint8_t PWM_MIN = 0;
const uint8_t PWM_MAX = 255;

// cup fill configuration
const unsigned long MAX_FILL_TIME_MS = 5000;  // 5s

/// Get the desired PWM value given a speed from 0.0 to 1.0.
int normalize_speed(float speed);

/// Check whether or not a cup is located in the cup holder.
bool is_cup_present();

/// Check whether or not the robot is in the fill position.
bool is_manipulator_ready();

/// Move the robot to the fill position.
void move_to_fill_position();

/// Move the robot to the stow position.
void move_to_stow_position();

/// Run the pump.
void run_pump();

/// Stop the pump.
void stop_pump();