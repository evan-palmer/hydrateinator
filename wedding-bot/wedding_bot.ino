#include "wedding_bot.h"

void setup() {
  // configure the pump
  pinMode(PUMP_INA1_PIN, OUTPUT);
  pinMode(PUMP_INA2_PIN, OUTPUT);
  pinMode(PUMP_PWMA_PIN, OUTPUT);

  // configure the UR GPIO pins
  pinMode(UR_READY_PIN, INPUT);
  pinMode(UR_TO_HOLDER_PIN, OUTPUT);
  pinMode(UR_TO_STOW_PIN, OUTPUT);

  // configure the breakbeam sensor pins and set the internal pullup resistor
  pinMode(BREAKBEAM_PIN, INPUT);
  digitalWrite(BREAKBEAM_PIN, HIGH);
}

void loop() {
  if (is_cup_present()) {
    if (!is_manipulator_ready()) {
      move_to_fill_position();
    } else {
      unsigned long start_time = millis();
      run_pump();

      while (is_cup_present() && (millis() - start_time) < MAX_FILL_TIME_MS) {
        continue;
      }

      stop_pump();
      move_to_stow_position();
    }
  } else {
    stop_pump();
    move_to_stow_position();
  }

  delay(10);
}

int normalize_speed(float speed) {
  speed = constrain(speed, 0.0, 1.0);
  return (int)(speed * (PWM_MAX - PWM_MIN)) + PWM_MIN;
}

bool is_cup_present() {
  return !(bool)digitalRead(BREAKBEAM_PIN);
}

bool is_manipulator_ready() {
  return (bool)digitalRead(UR_READY_PIN);
}

void move_to_fill_position() {
  digitalWrite(UR_TO_STOW_PIN, LOW);
  digitalWrite(UR_TO_HOLDER_PIN, HIGH);
}

void move_to_stow_position() {
  digitalWrite(UR_TO_HOLDER_PIN, LOW);
  digitalWrite(UR_TO_STOW_PIN, HIGH);
}

void run_pump() {
  digitalWrite(PUMP_INA1_PIN, HIGH);
  digitalWrite(PUMP_INA2_PIN, LOW);
  analogWrite(PUMP_PWMA_PIN, normalize_speed(0.7));
}

void stop_pump() {
  digitalWrite(PUMP_INA1_PIN, LOW);
  digitalWrite(PUMP_INA2_PIN, LOW);
}