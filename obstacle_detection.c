#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define TRIGGER_PIN 9  // Pin for the trigger signal
#define ECHO_PIN 10    // Pin for the echo signal
#define MAX_DISTANCE 200 // Maximum distance in centimeters

int main(int argc, char *argv[])
{
  // Set the trigger and echo pins as output and input, respectively
  gpio_export(TRIGGER_PIN);
  gpio_direction(TRIGGER_PIN, OUTPUT_PIN);
  gpio_export(ECHO_PIN);
  gpio_direction(ECHO_PIN, INPUT_PIN);

  while (1) {
    // Send a trigger pulse to the sensor
    gpio_set_value(TRIGGER_PIN, 1);
    usleep(10);
    gpio_set_value(TRIGGER_PIN, 0);

    // Read the echo pulse and calculate the distance
    int duration = gpio_pulse_in(ECHO_PIN, 1);
    int distance = (duration / 2) / 29.1;  // Distance in centimeters

    // Check if an obstacle is present
    if (distance < MAX_DISTANCE) {
      // An obstacle is present, take action
      printf("Obstacle detected!\n");
    } else {
      // No obstacle detected, continue as normal
      printf("No obstacle detected.\n");
    }

    // Wait a short period of time before taking another measurement
    usleep(500000);
  }

  return 0;
}
