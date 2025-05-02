#include <arduinoFFT.h> // FFT library

// Depending on the board, built in LED might not be defined
#ifndef LED_BUILTIN
#define LED_BUILTIN 2
#endif

const int MIC_IN = A4; //mic pin

// function definitions
void micCapture(void *parameter); // gets microphone inpiut

// Globals
static TaskHandle_t mic_capture;

// FFT
const int SAMPLES = 1024;
const int SAMPLE_FREQ = 40000;

// FFT arrays
double vReal[SAMPLES];
double vImag[SAMPLES];

//creates FFT
ArduinoFFT<double> FFT = ArduinoFFT<double>(vReal,vImag,SAMPLES,SAMPLE_FREQ);

void setup(){

  //activate pin modes
  pinMode(MIC_IN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  //initialize
  Serial.begin(9600);
  digitalWrite(LED_BUILTIN, HIGH);

  xTaskCreatePinnedToCore(
    micCapture,     // function to call
    "Mic Capture",  // task name
    4096,           // memory allocated
    NULL,           // parameters
    2,              // priority (higher = more prio)
    &mic_capture,   // task handle
    0               // core
  );

  // intial delay
  vTaskDelay(10000 / portTICK_PERIOD_MS);

  // unsuspend tasks
  vTaskResume(mic_capture);

  //turn LED off when setup complete
  digitalWrite(LED_BUILTIN, LOW);
  
}

// Mostly empty 
void loop(){
  vTaskDelay(1000 / portTICK_PERIOD_MS);

}

// captures analog input from the microphone
void micCapture(void *parameter){
  vTaskSuspend(NULL); //initially suspend this task
  Serial.println("Getting Microphone Input");
  while(1){
    digitalWrite(LED_BUILTIN, HIGH);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    digitalWrite(LED_BUILTIN, LOW);
  }
}
