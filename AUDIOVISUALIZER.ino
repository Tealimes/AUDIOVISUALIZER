#include <arduinoFFT.h>

const int MIC_IN = A4; //mic pin

// FFT
const int SAMPLES = 1024;
const int SAMPLE_FREQ = 40000;

// FFT arrays
double vReal[SAMPLES];
double vImag[SAMPLES];

ArduinoFFT<double> FFT = ArduinoFFT<double>(vReal,vImag,SAMPLES,SAMPLE_FREQ);


void setup(){
  //initialize
  Serial.begin(9600);
  while(!Serial) {
    //blink until Serial acquired
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
  }

  //activate pin mode
  pinMode(MIC_IN, INPUT);
}
void loop(){
  //gets samples from microphone
}
