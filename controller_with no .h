#include <Adafruit_NeoPixel.h>

#define PIN         6       // LED strip data pin
#define NUM_LEDS    50      // Number of LEDs on the strip
#define BRIGHTNESS  50      // Default brightness

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

enum Effect {
    BREATHING,
    BLINKING,
    USER_CONTROL
};

// Function prototypes
void ledStripEffect(Effect effect);
void breathingEffect();
void blinkingEffect();
void userControlEffect();

void setup() {
    strip.begin();
    strip.setBrightness(BRIGHTNESS);
    strip.show();
    Serial.begin(9600);
}

void loop() {
    // Example usage: Cycle through effects
    for (int i = 0; i < 3; i++) {
        ledStripEffect(static_cast<Effect>(i));
        delay(5000); // Pause between effects
    }
}

void ledStripEffect(Effect effect) {
    switch (effect) {
        case BREATHING:
            breathingEffect();
            break;
        case BLINKING:
            blinkingEffect();
            break;
        case USER_CONTROL:
            userControlEffect();
            break;
    }
}

void breathingEffect() {
    static unsigned long previousMillis = 0;
    static int brightness = 0;
    static int direction = 1;
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= 10) {
        previousMillis = currentMillis;
        brightness += direction;
        if (brightness <= 0 || brightness >= 255) {
            direction *= -1;
        }
        for (int i = 0; i < NUM_LEDS; i++) {
            strip.setPixelColor(i, strip.Color(brightness, brightness, brightness));
        }
        strip.show();
    }
}

void blinkingEffect() {
    static unsigned long blinkingTimer = 0;
    static bool isOn = false;
    unsigned long currentMillis = millis();

    if (currentMillis - blinkingTimer >= (isOn ? 700 : 300)) {
        blinkingTimer = currentMillis;
        isOn = !isOn;
        for (int i = 0; i < NUM_LEDS; i++) {
            strip.setPixelColor(i, isOn ? strip.Color(255, 255, 255) : strip.Color(0, 0, 0));
        }
        strip.show();
    }
}

void userControlEffect() {
    if (Serial.available() > 0) {
        int value = Serial.parseInt();
        if (value >= 0 && value <= 255) {
            strip.setBrightness(value);
            strip.show();
        }
    }
}
