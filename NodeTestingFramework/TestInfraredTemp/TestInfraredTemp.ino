/*
read_temperature.ino - Example for MLX90614 library returns temperature in Celsius, Kelvin, and Fahrenheit
Copyright (C) 2012 Lara Booth for NanoSatisfi

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
#include <System.h>
#include <SAT_AppStorage.h>
#include <SAT_ExperimentData.h>
#include "SAT_InfraTherm.h"
#include <I2C_add.h>
#include <nanosat_message.h>
#include <Wire.h>
#include <OnboardCommLayer.h>

uint8_t nodeid = 1;
SAT_AppStorage storage = SAT_AppStorage(nodeid);
System mysys = System(nodeid);

SAT_InfraTherm mlx;

void setup(){
Serial.begin(9600); //begin Serial monitor
        
Serial.println("Setup..."); //initialization complete
}

//print temperature in Celsius, Kelvin, and Fahrenheit
void loop(){
    float celsius = 0.0;
    
    celsius = mlx.getTemp();
    float fahrenheit = (celsius * 9.0/5.0) + 32.0;
    float kelvin = celsius + 273.1;
    
    Serial.print("Temperature: ");
    Serial.print(celsius);
    Serial.println(" * C"); //indicate degrees Celsius
    
    Serial.print("Temperature: ");
    Serial.print(fahrenheit);
    Serial.println(" * F"); //indicate degrees Fahrenheit
    
    Serial.print("Temperature: ");
    Serial.print(kelvin);
    Serial.println(" K"); //indicate Kelvin
    storage.store_exp_data((uint8_t*)&fahrenheit, sizeof(float));
    storage.store_exp_data((uint8_t*)&celsius, sizeof(float));
    storage.store_exp_data((uint8_t*)&kelvin, sizeof(float));

    delay(1000); // wait a second before printing again
    mysys.exit();
}
