#include <Adafruit_NeoPixel.h>
#include <Adafruit_ZeroFFT.h>

#define DATA_SIZE 256

#define NUM_PIXELS 9

#define SAMPLE_RATE 22000

#define FREQ_MIN 600
#define FREQ_MAX 3000

#define MIN_INDEX FFT_INDEX(FREQ_MIN, SAMPLE_RATE, DATA_SIZE)
#define MAX_INDEX FFT_INDEX(FREQ_MAX, SAMPLE_RATE, DATA_SIZE)

int16_t pixelData[NUM_PIXELS];
int16_t inputData[DATA_SIZE];

Adafruit_NeoPixel pixels(NUM_PIXELS, A0, NEO_GRB + NEO_KHZ800);

uint8_t hues[NUM_PIXELS];

void setup()
{
    for(int i = 0; i < NUM_PIXELS; i++) {
        hues[i] = i*256/NUM_PIXELS;
    }
	pixels.begin();
}

void loop()
{
	for (int i  = 0; i < NUM_PIXELS; i++) {
        pixels.setPixelColor(i, pixels.ColorHSV(hues[i]++));
    }
}
