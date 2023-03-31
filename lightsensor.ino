// Bevan Fairleigh
// 

// This #include statement was automatically added by the Particle IDE.
#include <BH1750.h>

// This #include statement was automatically added by the Particle IDE.
// #include <ThingSpeak.h>


// Define our instance of the BH1750 light meter
BH1750 lightMeter;



void setup()
{

    // Open the I2C channel, and turn the sensor on to read light levels
    lightMeter.begin();
    lightMeter.switch_power_on();

}


// Set a const value to determine what is 'low' light levels
const int lowLight = 10000;


// Define a status variable to keep track of the current state of the light, notify on change
int status = 0;




void loop()
{
    // Poll the BH1750 to get current light level in lux
    float lux = lightMeter.get_light_level();
    String lux_string = String(lux);
    

    // Let's use a little logic to determine if the current status has changed
    
    if (status == 0 and lux > lowLight) {
        status = 1;
        Particle.publish("LightSensor_On", lux_string, PRIVATE);
    }
    else if (status == 1 and lux <= lowLight) {
        status = 0;
        Particle.publish("LightSensor_Off", lux_string, PRIVATE);
    }
    

    
    
    delay(30000);
    
}
