#!/bin/bash
# Simula dos señales diferentes en GPIO1 y GPIO2

# Asegurar que están exportados
echo 1 > /sys/class/gpio/export
echo 2 > /sys/class/gpio/export

echo out > /sys/class/gpio/gpio1/direction
echo out > /sys/class/gpio/gpio2/direction

while true; do
  # GPIO1: señal cuadrada 1 Hz (0.5s alto, 0.5s bajo)
  # GPIO2: pulso largo, 1.5s alto
  echo 1 > /sys/class/gpio/gpio1/value
  echo 1 > /sys/class/gpio/gpio2/value
  sleep 0.5
  echo 0 > /sys/class/gpio/gpio1/value
  sleep 0.5
  echo 1 > /sys/class/gpio/gpio1/value
  sleep 0.5
  echo 0 > /sys/class/gpio/gpio1/value
  echo 0 > /sys/class/gpio/gpio2/value
  sleep 0.5
done
