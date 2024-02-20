bool any_peak_detected = false;
bool first_peak_detected = false;
unsigned long first_pulse_time = 0;
unsigned long second_pulse_time = 0;
unsigned long pulse_period = 0;
int upper_threshold = 900;
int lower_threshold = 750;

const int sensor_pin = A0;
int pulse_signal = 0;
float BPM = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  pulse_signal = analogRead(sensor_pin);
  //Serial.println(pulse_signal);
  delay(50);

  if (pulse_signal > upper_threshold && any_peak_detected == false) {
    any_peak_detected = true;
    // Do something about this peak
    if (first_peak_detected == false) {
      first_pulse_time = millis();
      first_peak_detected = true;
      } 
    else {
      second_pulse_time = millis();
      pulse_period = second_pulse_time - first_pulse_time;
      first_peak_detected = false;
      }
  }

  if (pulse_signal < lower_threshold) {
    any_peak_detected = false;
  }

  //pulse_in_sec = pulse_period / 1000;
  //Serial.println(pulse_period);
  BPM = 60.0 * (1/(pulse_period/1000.0));
  Serial.println(BPM);
}
