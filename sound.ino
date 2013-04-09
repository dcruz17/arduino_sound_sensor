/****************************************
  Example Sound Level Sketch for the 
  Adafruit Microphone Amplifier
http://learn.adafruit.com/adafruit-microphone-amplifier-breakout/measuring-sound-levels
 ****************************************/

// if sampleWindow == 50, barGraph printing doesn't work correctly
// Sample window width in mS (50 mS = 20 Hz)
const int sampleWindow = 1000;

unsigned int sample;

int barLength = 0;
const int barLengthTotal = 40;
char barGraph[barLengthTotal] = "";

void setup() 
{
    Serial.begin(9600);
}


void loop() 
{
    unsigned long startMillis= millis();  // Start of sample window
    unsigned int peakToPeak = 0;   // peak-to-peak level

    unsigned int signalMax = 0;
    unsigned int signalMin = 1024;

    // collect data for sampleWindow mS
    while (millis() - startMillis < sampleWindow)
    {
        sample = analogRead(0);
        if (sample < 1024)  // toss out spurious readings
        {
            if (sample > signalMax)
            {
                signalMax = sample;  // save just the max levels
            }
            else if (sample < signalMin)
            {
                signalMin = sample;  // save just the min levels
            }
        }
    }

    peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
    // convert to volts
    //double volts = (3.3 * peakToPeak) / 1024;
    // convert to millivolts
    int millivolts = int(1000 * (3.3 * peakToPeak) / 1024);

    Serial.println(millivolts);

    barLength = int(millivolts/10);
    for (int i = 0; i < barLengthTotal; i++) {
        if (i <= barLength) {
            barGraph[i] = '*';
        } else {
            barGraph[i] = ' ';
        }
    }
    Serial.println(barGraph);
}
