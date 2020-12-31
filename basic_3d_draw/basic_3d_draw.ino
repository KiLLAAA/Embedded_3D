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

  ////////////////
  // SIGN 3D
  for (int angle = 0; angle < 360; angle = angle + 3) {
    display.clearDisplay();

    float rotX = 0; // analogRead(0) * 0.0174532;
    float rotY = angle * 0.0174532;
    float rotZ = 0.17;
    float scale = 1 - rotY;

    int8_t vertlist_temp[SIGN_3D_VERTS][3]; // create temp to fit vertices

    rotate_vertices(sign_3D_verts, vertlist_temp, SIGN_3D_VERTS, rotX, rotY, rotZ);
    fill_tri_faces( vertlist_temp, sign_3D_tris, SIGN_3D_TRIS, origin_x, origin_y);

    display.display();
  }

  ////////////////
  // TEAPOT
  for (int angle = 0; angle < 360; angle = angle + 2) {
    display.clearDisplay();

    float rotX = 0; // analogRead(0) * 0.0174532;
    float rotY = angle * 0.0174532;
    float rotZ = 0.17;
    float scale = 1;

    draw_vertices(teapot_verts, TEAPOT_VERTS, origin_x, origin_y + 4, rotX, rotY, rotZ, scale, WHITE);

    display.display();
  }

  ////////////////
  // TEAPOT WIREFRAME
  for (int angle = 0; angle < 360; angle = angle + 10) {
    display.clearDisplay();

    float rotX = 0; // analogRead(0) * 0.0174532;
    float rotY = angle * 0.0174532;
    float rotZ = 0.17;
    float scale = 1;

    draw_tri_faces(teapot_verts, teapot_tris, TEAPOT_TRIS, origin_x, origin_y + 4, rotX, rotY, rotZ, scale, WHITE);

    display.display();
  }
}
