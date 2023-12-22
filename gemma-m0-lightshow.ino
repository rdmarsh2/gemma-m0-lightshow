#include <Adafruit_NeoPixel.h>
#include <Adafruit_ZeroFFT.h>

#define DATA_SIZE 2048

#define NUM_PIXELS 9

int16_t pixelData[NUM_PIXELS];
int16_t inputData[DATA_SIZE];

#define MIC_PIN A2

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
    uint32_t avg = 0;
    for (int i = 0; i < DATA_SIZE; i++) {
        uint32_t mic_val = analogRead(MIC_PIN);
        inputData[i] = mic_val;
    }

    avg = avg/DATA_SIZE;
    for(int i=0; i<DATA_SIZE; i++) {
        inputData[i] = (inputData[i] - avg) * 64;
    }

    ZeroFFT(inputData, DATA_SIZE);

	for (int i = 0; i < NUM_PIXELS; i++) {
        uint32_t bucket_avg = 0;
        // TODO: rewrite to handle arbitrary pixel count and input data size. Should be logarithmic...
        for(int j = 1 << i; j < 2<<i; j++) { // this drops the lowest bucket... I think that's OK.
            bucket_avg += inputData[i];
        }
        pixels.setPixelColor(i, pixels.ColorHSV(hues[i]++, 255, 100 + bucket_avg / (1024 << i)));
    }
}
