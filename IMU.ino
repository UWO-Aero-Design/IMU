#include "AERO_ICM20948.hpp"

const int DEFAULT_BAUD = 112500;
const int IMU_IRQ_PIN = 36;

// Sensors
AERO_ICM20948 imu;

bool IMU_data_ready;
void new_data();
void new_data() {
	IMU_data_ready = true;
}

void setup() {
  
  Serial.begin(DEFAULT_BAUD);
  
 	Wire.begin();
 	Wire.setClock(1000000);

	pinMode(IMU_IRQ_PIN, INPUT);

	if (imu.init(Wire)) {
	    Serial.println("IMU online.");
	}
	else {
	    Serial.println("Error connecting to IMU.");
	}

	attachInterrupt(digitalPinToInterrupt(IMU_IRQ_PIN), new_data, RISING);

	delay(500);
	interrupts();
}

float gyro[3];
float accel[3];
float mag[3];
float quat[4];

void loop() {

	if (IMU_data_ready) {
		IMU_data_ready = false;
		imu.update(accel, gyro, quat);
		Serial.printf("accel: %7.4f, %7.4f, %7.4f gyro: %7.4f, %7.4f, %7.4f \r\n\n", accel[0], accel[1], accel[2], gyro[0], gyro[1], gyro[2]);
	}
}
