/*
  Copyright (c) 2020, Lukas Vyhnalek aka KiLLA
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

  Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma GCC optimize ("-Ofast") // speed up tests (O2, O3, Ofast)

#include <SPI.h> // OLED
#include <Adafruit_GFX.h> // OLED

#ifdef __AVR__
#include <Adafruit_SSD1306.h> // OLED
#include <avr/pgmspace.h> // PROGMEM
#else
#include <Adafruit_SSD1306_STM32.h> // OLED
#endif

#include "engine_3D.h"
#include "objects_3D.h"
#include "numbers_3D.h"

// OLED display pin defines
#ifdef __AVR__
// Use hardware SPI on AVR
#define OLED_DC     10
#define OLED_CS     8
#define OLED_RESET  9

#elif defined __STM32F1__
// Use hardware SPI on STM
#define OLED_DC    PB1
#define OLED_CS    PA4
#define OLED_RESET PB0
#endif

Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);

//////////////////////////////////////////////////////////////////////

void setup(void)
{
  ////////////////
  // OLED
  display.begin(SSD1306_SWITCHCAPVCC); // OLED init
  display.display(); // display initial buffer -> logo
  delay(2000); // wait
  display.clearDisplay();
  display.display(); //
  delay(1000); // wait
}

void loop(void)
{
  int origin_x = 64;
  int origin_y = 32;

  ///////////////////
  // COUNTDOWN
  for (uint8_t number = 0; number < 10; number = number + 1) {
    unsigned long start_time = micros();
    uint8_t inv_number = 9 - number;
    uint16_t start_angle = 216;
    uint8_t angle_step = 4;
    for (uint16_t angle = start_angle; angle < 360; angle = angle + angle_step) {
      unsigned long current_time = micros(); // start measuring time
      display.clearDisplay();

      float rotX = 0; // analogRead(0) * 0.0174532;
      float rotY = angle * 0.0174532;
      float rotZ = 0.17;
      float scale =  ((float)(angle - start_angle) / (360 - start_angle)) * 3; // 0 to 3.

      //draw_3D_number(inv_number, origin_x, origin_y, rotX, rotY, rotZ, scale); //(uint8_t number, int16_t x, int16_t y, float rotX, float rotY, float rotZ, float scale)
      fill_3D_number(inv_number, origin_x, origin_y, rotX, rotY, rotZ, scale); //

      display.setTextSize(1);
      //display.setTextColor(WHITE, BLACK);
      display.setTextColor(WHITE);
      /*display.setCursor(0, 0);
        display.print("angle "); display.println(angle);
        display.setCursor(0, 10);
        display.print("scale "); display.println(scale);*/
      display.setCursor(0, 50);
      display.print("frame time "); display.print((micros() - current_time) / 1000.0); display.println("ms");

      while ((micros() - current_time) < 27000) { // 36fps cap
      }

      display.display();
    }
    /*
      // info
      unsigned long end_time = micros();
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.print("angle_step "); display.println(angle_step);
      display.setCursor(0, 50);
      display.print("total time "); display.print((end_time - start_time) / 1000); display.println("ms");
      display.display();
      delay(1000);
    */
  }

  ////////////////
  // SIGN 3D ANIM
  int8_t shift_temp[SIGN_3D_TRIS][2]; // create temp to fit shift effect
  for (uint8_t face = 0; face < SIGN_3D_TRIS; face = face + 1) {
    shift_temp[face][0] = random(256) - 127;
    shift_temp[face][1] = random(256) - 127;
  }

  for (int angle = 0; angle < 361; angle = angle + 1) { // 361 to render 360 degerees == 0 => animation goes from zero to zero (just to show last frame)
    display.clearDisplay();

    float rotX = 0; // analogRead(0) * 0.0174532;
    float rotY = angle * 0.0174532;
    float rotZ = 0.17;
    float scale = rotY;
    float current_time = angle * (1.0 / 360); //
    float anim = ( -4.0 * (current_time - 0.5) * (current_time - 0.5) ) + 1; // y = -4(x-0.5)^2 + 1 => ease out and in, hyperbolic function
    //float anim =  (current_time - 1) * (current_time - 1) ; // ease in, hyperbolic function with a=1, k=0

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.print("angle "); display.println(angle);
    display.setCursor(0, 10);
    display.print("anim "); display.println(anim);

    int8_t vertlist_temp[SIGN_3D_VERTS][3]; // create temp to fit vertices

    rotate_vertices(sign_3D_verts, vertlist_temp, SIGN_3D_VERTS, rotX, rotY, rotZ);
    for (uint8_t face = 0; face < SIGN_3D_TRIS; face = face + 1) {
      fill_tri_face( vertlist_temp, sign_3D_tris, face, origin_x + (shift_temp[face][0]*anim), origin_y + (shift_temp[face][1]*anim));
    }

    display.display();
  }
  delay(500); // pause last frame
}
