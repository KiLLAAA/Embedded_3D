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

#ifndef _ENGINE_3D_H_
#define _ENGINE_3D_H_

struct object3D
{
  const int8_t (*vert_list)[3];
  uint16_t numVerts;

  const uint8_t (*faces_list)[3];
  uint16_t numTriPolys;
};

////////////////////////////////
// DEVICE SELECT
extern Adafruit_SSD1306 display;
// extern LCD_UC1609 display;

////////////////////////////////
// FUNCTION PROTOTYPES
void rotate_vertices(int8_t vert_list[][3], int8_t rotated_list[][3], uint8_t vert_count, float rotX, float rotY, float rotZ);
void rotate_vertices(const int8_t (*vert_list)[3], int8_t rotated_list[][3], uint8_t vert_count, float rotX, float rotY, float rotZ);

void scale_vertices(int8_t vert_list[][3], int8_t scaled_list[][3], uint8_t vert_count, float scale);
void scale_vertices(const int8_t (*vert_list)[3], int8_t scaled_list[][3], uint8_t vert_count, float scale);

void draw_vertice(int8_t vert_list[][3], uint8_t vert_index, uint16_t color);
void draw_vertice(const int8_t (*vert_list)[3], uint8_t vert_index, uint16_t color);

void draw_vertices(int8_t vert_list[][3], uint16_t vert_count, int16_t x, int16_t y, float rotX, float rotY, float rotZ, float scale, uint16_t color);
void draw_vertices(const int8_t (*vert_list)[3], uint16_t vert_count, int16_t x, int16_t y, float rotX, float rotY, float rotZ, float scale, uint16_t color);

void draw_tri_faces(int8_t vert_list[][3], uint8_t faces_list[][3], uint8_t list_size, int16_t x, int16_t y);
void draw_tri_faces(int8_t vert_list[][3], const uint8_t (*faces_list)[3], uint8_t list_size, int16_t x, int16_t y);
void draw_tri_faces(const int8_t (*vert_list)[3], const uint8_t (*faces_list)[3], uint8_t list_size, int16_t x, int16_t y);

void draw_tri_face(const int8_t (*vert_list)[3], const uint8_t (*faces_list)[3], uint16_t list_pos, int16_t x, int16_t y, float rotX, float rotY, float rotZ, float scale, uint16_t color);
void fill_tri_face(const int8_t (*vert_list)[3], const uint8_t (*faces_list)[3], uint16_t list_pos, int16_t x, int16_t y, float rotX, float rotY, float rotZ, float scale, uint16_t color);

void draw_tri_faces(const int8_t (*vert_list)[3], const uint8_t (*faces_list)[3], uint16_t list_size, int16_t x, int16_t y, float rotX, float rotY, float rotZ, float scale, uint16_t color);
void fill_tri_faces(const int8_t (*vert_list)[3], const uint8_t (*faces_list)[3], uint16_t list_size, int16_t x, int16_t y, float rotX, float rotY, float rotZ, float scale, uint16_t color);

////////////////////////////////
// ROTATE VERTICES

void rotate_vertices(int8_t vert_list[][3], int8_t rotated_list[][3], uint8_t vert_count, float rotX, float rotY, float rotZ)
{
  float sin_rotX = sin(rotX);
  float cos_rotX = cos(rotX);
  float sin_rotY = sin(rotY);
  float cos_rotY = cos(rotY);
  float sin_rotZ = sin(rotZ);
  float cos_rotZ = cos(rotZ);

  for (uint8_t i = 0; i < vert_count; i++) {
    //rotateY
    float rotz = vert_list[i][2] * cos_rotY - vert_list[i][0] * sin_rotY;
    float rotx = vert_list[i][2] * sin_rotY + vert_list[i][0] * cos_rotY;
    float roty = vert_list[i][1];
    //rotateX
    float rotyy = roty * cos_rotX - rotz * sin_rotX;
    float rotzz = roty * sin_rotX + rotz * cos_rotX;
    float rotxx = rotx;
    //rotateZ
    float rotxxx = rotxx * cos_rotZ - rotyy * sin_rotZ;
    float rotyyy = rotxx * sin_rotZ + rotyy * cos_rotZ;
    float rotzzz = rotzz;

    rotated_list[i][0] = rotxxx;
    rotated_list[i][1] = rotyyy;
    rotated_list[i][2] = rotzzz;
  }
}

void rotate_vertices(const int8_t (*vert_list)[3], int8_t rotated_list[][3], uint8_t vert_count, float rotX, float rotY, float rotZ)
{
  //Serial.println("rotate_vertices>PGM");
  for (uint8_t i = 0; i < vert_count; i++) {
    //rotateY
    float rotz = (int8_t)pgm_read_byte(&vert_list[i][2]) * cos(rotY) - (int8_t)pgm_read_byte(&vert_list[i][0]) * sin(rotY); //(int8_t)
    float rotx = (int8_t)pgm_read_byte(&vert_list[i][2]) * sin(rotY) + (int8_t)pgm_read_byte(&vert_list[i][0]) * cos(rotY);
    float roty = (int8_t)pgm_read_byte(&vert_list[i][1]);
    //rotateX
    float rotyy = roty * cos(rotX) - rotz * sin(rotX);
    float rotzz = roty * sin(rotX) + rotz * cos(rotX);
    float rotxx = rotx;
    //rotateZ
    float rotxxx = rotxx * cos(rotZ) - rotyy * sin(rotZ);
    float rotyyy = rotxx * sin(rotZ) + rotyy * cos(rotZ);
    float rotzzz = rotzz;

    rotated_list[i][0] = rotxxx;
    rotated_list[i][1] = rotyyy;
    rotated_list[i][2] = rotzzz;
  }
}

////////////////////////////////
// SCALE VERTICES
void scale_vertices(int8_t vert_list[][3], int8_t scaled_list[][3], uint8_t vert_count, float scale)
{
  for (int i = 0; i < vert_count; i++) {
    //
    scaled_list[i][0] = vert_list[i][0] * scale;
    scaled_list[i][1] = vert_list[i][1] * scale;
    scaled_list[i][2] = vert_list[i][2] * scale;
  }
}

void scale_vertices(const int8_t (*vert_list)[3], int8_t scaled_list[][3], uint8_t vert_count, float scale)
{
  for (int i = 0; i < vert_count; i++) {
    //
    scaled_list[i][0] = (int8_t)pgm_read_byte(&vert_list[i][0]) * scale;
    scaled_list[i][1] = (int8_t)pgm_read_byte(&vert_list[i][1]) * scale;
    scaled_list[i][2] = (int8_t)pgm_read_byte(&vert_list[i][2]) * scale;
  }
}

////////////////////////////////
// DRAW VERTICES
void draw_vertice(int8_t vert_list[][3], uint8_t vert_index, uint16_t color)
{
  // simple and fast
  display.drawPixel(vert_list[vert_index][0], vert_list[vert_index][1], color);
}

void draw_vertice(const int8_t (*vert_list)[3], uint8_t vert_index, uint16_t color)
{
  // simple and fast
  display.drawPixel((int8_t)pgm_read_byte(&vert_list[vert_index][0]), (int8_t)pgm_read_byte(&vert_list[vert_index][1]), color);
}

void draw_vertices(int8_t vert_list[][3], uint16_t vert_count, int16_t x, int16_t y, float rotX, float rotY, float rotZ, float scale, uint16_t color)
{
  // featured and slower
  int8_t vert_temp[1][3]; // single vertex cache

  for (uint16_t i = 0; i < vert_count; i++) {
    //
    vert_temp[0][0] = (int8_t)vert_list[i][0] * scale;
    vert_temp[0][1] = (int8_t)vert_list[i][1] * scale;
    vert_temp[0][2] = (int8_t)vert_list[i][2] * scale;

    rotate_vertices(vert_temp, vert_temp, 1, rotX, rotY, rotZ);

    display.drawPixel(x + vert_temp[0][0], y + vert_temp[0][1], color);
    if (vert_temp[0][2] < 0) {
      display.drawPixel(x + vert_temp[0][0] + 1, y + vert_temp[0][1], color);
      if (vert_temp[0][2] < -16) {
        display.drawPixel(x + vert_temp[0][0], y + vert_temp[0][1] + 1, color);
        display.drawPixel(x + vert_temp[0][0] + 1, y + vert_temp[0][1] + 1, color);
      }
    }
  }
}

void draw_vertices(const int8_t (*vert_list)[3], uint16_t vert_count, int16_t x, int16_t y, float rotX, float rotY, float rotZ, float scale, uint16_t color)
{
  // featured and slower
  int8_t vert_temp[1][3]; // single vertex cache
  for (uint16_t i = 0; i < vert_count; i++) {
    //
    vert_temp[0][0] = (int8_t)pgm_read_byte(&vert_list[i][0]) * scale;
    vert_temp[0][1] = (int8_t)pgm_read_byte(&vert_list[i][1]) * scale;
    vert_temp[0][2] = (int8_t)pgm_read_byte(&vert_list[i][2]) * scale;

    rotate_vertices(vert_temp, vert_temp, 1, rotX, rotY, rotZ);

    display.drawPixel(x + vert_temp[0][0], y + vert_temp[0][1], color);
    if (vert_temp[0][2] < 0) {
      display.drawPixel(x + vert_temp[0][0] + 1, y + vert_temp[0][1], color);
      if (vert_temp[0][2] < -16) {
        display.drawPixel(x + vert_temp[0][0], y + vert_temp[0][1] + 1, color);
        display.drawPixel(x + vert_temp[0][0] + 1, y + vert_temp[0][1] + 1, color);
      }
    }
  }
}

////////////////////////////////
// DRAW FACES
void draw_tri_faces(int8_t vert_list[][3], uint8_t faces_list[][3], uint8_t list_size, int16_t x, int16_t y)
{
  for (int i = 0; i < list_size; i++) {
    display.drawLine(x + vert_list[faces_list[i][0]][0], y + vert_list[faces_list[i][0]][1], x + vert_list[faces_list[i][1]][0], y + vert_list[faces_list[i][1]][1], WHITE);
    display.drawLine(x + vert_list[faces_list[i][1]][0], y + vert_list[faces_list[i][1]][1], x + vert_list[faces_list[i][2]][0], y + vert_list[faces_list[i][2]][1], WHITE);
    display.drawLine(x + vert_list[faces_list[i][2]][0], y + vert_list[faces_list[i][2]][1], x + vert_list[faces_list[i][0]][0], y + vert_list[faces_list[i][0]][1], WHITE);
  }
}

void draw_tri_faces(int8_t vert_list[][3], const uint8_t (*faces_list)[3], uint8_t list_size, int16_t x, int16_t y)
{
  for (int i = 0; i < list_size; i++) {
    display.drawLine(x + vert_list[pgm_read_byte(&faces_list[i][0])][0], y + vert_list[pgm_read_byte(&faces_list[i][0])][1], x + vert_list[pgm_read_byte(&faces_list[i][1])][0], y + vert_list[pgm_read_byte(&faces_list[i][1])][1], WHITE);
    display.drawLine(x + vert_list[pgm_read_byte(&faces_list[i][1])][0], y + vert_list[pgm_read_byte(&faces_list[i][1])][1], x + vert_list[pgm_read_byte(&faces_list[i][2])][0], y + vert_list[pgm_read_byte(&faces_list[i][2])][1], WHITE);
    display.drawLine(x + vert_list[pgm_read_byte(&faces_list[i][2])][0], y + vert_list[pgm_read_byte(&faces_list[i][2])][1], x + vert_list[pgm_read_byte(&faces_list[i][0])][0], y + vert_list[pgm_read_byte(&faces_list[i][0])][1], WHITE);
  }
}

void draw_tri_faces(const int8_t (*vert_list)[3], const uint8_t (*faces_list)[3], uint8_t list_size, int16_t x, int16_t y)
{
  for (int i = 0; i < list_size; i++) {
    display.drawLine(x + (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][0])][0]), y + (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][0])][1]), x + (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][1])][0]), y + (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][1])][1]), WHITE);
    display.drawLine(x + (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][1])][0]), y + (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][1])][1]), x + (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][2])][0]), y + (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][2])][1]), WHITE);
    display.drawLine(x + (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][2])][0]), y + (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][2])][1]), x + (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][0])][0]), y + (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][0])][1]), WHITE);
  }
}

void fill_tri_face(int8_t vert_list[][3], const uint8_t (*faces_list)[3], uint8_t list_pos, int16_t x, int16_t y)
{
  display.fillTriangle(x + vert_list[pgm_read_byte(&faces_list[list_pos][0])][0], y + vert_list[pgm_read_byte(&faces_list[list_pos][0])][1], x + vert_list[pgm_read_byte(&faces_list[list_pos][1])][0], y + vert_list[pgm_read_byte(&faces_list[list_pos][1])][1], x + vert_list[pgm_read_byte(&faces_list[list_pos][2])][0], y + vert_list[pgm_read_byte(&faces_list[list_pos][2])][1], WHITE);
}

void fill_tri_faces(int8_t vert_list[][3], const uint8_t (*faces_list)[3], uint8_t list_size, int16_t x, int16_t y)
{
  for (int i = 0; i < list_size; i++) {
    display.fillTriangle(x + vert_list[pgm_read_byte(&faces_list[i][0])][0], y + vert_list[pgm_read_byte(&faces_list[i][0])][1], x + vert_list[pgm_read_byte(&faces_list[i][1])][0], y + vert_list[pgm_read_byte(&faces_list[i][1])][1], x + vert_list[pgm_read_byte(&faces_list[i][2])][0], y + vert_list[pgm_read_byte(&faces_list[i][2])][1], WHITE);
  }
}

void draw_tri_face(const int8_t (*vert_list)[3], const uint8_t (*faces_list)[3], uint16_t list_pos, int16_t x, int16_t y, float rotX, float rotY, float rotZ, float scale, uint16_t color)
{
  int8_t vert_temp[3][3];
  //
  vert_temp[0][0] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[list_pos][0])][0]) * scale;
  vert_temp[0][1] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[list_pos][0])][1]) * scale;
  vert_temp[0][2] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[list_pos][0])][2]) * scale;

  vert_temp[1][0] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[list_pos][1])][0]) * scale;
  vert_temp[1][1] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[list_pos][1])][1]) * scale;
  vert_temp[1][2] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[list_pos][1])][2]) * scale;

  vert_temp[2][0] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[list_pos][2])][0]) * scale;
  vert_temp[2][1] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[list_pos][2])][1]) * scale;
  vert_temp[2][2] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[list_pos][2])][2]) * scale;

  rotate_vertices(vert_temp, vert_temp, 3, rotX, rotY, rotZ);

  display.drawLine(x + vert_temp[0][0], y + vert_temp[0][1], x + vert_temp[1][0], y + vert_temp[1][1], color);
  display.drawLine(x + vert_temp[1][0], y + vert_temp[1][1], x + vert_temp[2][0], y + vert_temp[2][1], color);
  display.drawLine(x + vert_temp[2][0], y + vert_temp[2][1], x + vert_temp[0][0], y + vert_temp[0][1], color);
}

void fill_tri_face(const int8_t (*vert_list)[3], const uint8_t (*faces_list)[3], uint16_t list_pos, int16_t x, int16_t y, float rotX, float rotY, float rotZ, float scale, uint16_t color)
{
  int8_t vert_temp[3][3];
  //
  vert_temp[0][0] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[list_pos][0])][0]) * scale;
  vert_temp[0][1] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[list_pos][0])][1]) * scale;
  vert_temp[0][2] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[list_pos][0])][2]) * scale;

  vert_temp[1][0] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[list_pos][1])][0]) * scale;
  vert_temp[1][1] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[list_pos][1])][1]) * scale;
  vert_temp[1][2] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[list_pos][1])][2]) * scale;

  vert_temp[2][0] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[list_pos][2])][0]) * scale;
  vert_temp[2][1] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[list_pos][2])][1]) * scale;
  vert_temp[2][2] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[list_pos][2])][2]) * scale;

  rotate_vertices(vert_temp, vert_temp, 3, rotX, rotY, rotZ);

  display.fillTriangle(x + vert_temp[0][0], y + vert_temp[0][1], x + vert_temp[1][0], y + vert_temp[1][1], x + vert_temp[2][0], y + vert_temp[2][1], color);
}

void draw_tri_faces(const int8_t (*vert_list)[3], const uint8_t (*faces_list)[3], uint16_t list_size, int16_t x, int16_t y, float rotX, float rotY, float rotZ, float scale, uint16_t color)
{
  int8_t vert_temp[3][3];
  for (uint16_t i = 0; i < list_size; i++) {
    //
    vert_temp[0][0] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][0])][0]) * scale;
    vert_temp[0][1] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][0])][1]) * scale;
    vert_temp[0][2] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][0])][2]) * scale;

    vert_temp[1][0] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][1])][0]) * scale;
    vert_temp[1][1] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][1])][1]) * scale;
    vert_temp[1][2] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][1])][2]) * scale;

    vert_temp[2][0] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][2])][0]) * scale;
    vert_temp[2][1] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][2])][1]) * scale;
    vert_temp[2][2] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][2])][2]) * scale;

    rotate_vertices(vert_temp, vert_temp, 3, rotX, rotY, rotZ);

    display.drawLine(x + vert_temp[0][0], y + vert_temp[0][1], x + vert_temp[1][0], y + vert_temp[1][1], color);
    display.drawLine(x + vert_temp[1][0], y + vert_temp[1][1], x + vert_temp[2][0], y + vert_temp[2][1], color);
    display.drawLine(x + vert_temp[2][0], y + vert_temp[2][1], x + vert_temp[0][0], y + vert_temp[0][1], color);
  }
}

void fill_tri_faces(const int8_t (*vert_list)[3], const uint8_t (*faces_list)[3], uint16_t list_size, int16_t x, int16_t y, float rotX, float rotY, float rotZ, float scale, uint16_t color)
{
  int8_t vert_temp[3][3];
  for (uint16_t i = 0; i < list_size; i++) {
    //
    vert_temp[0][0] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][0])][0]) * scale;
    vert_temp[0][1] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][0])][1]) * scale;
    vert_temp[0][2] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][0])][2]) * scale;

    vert_temp[1][0] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][1])][0]) * scale;
    vert_temp[1][1] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][1])][1]) * scale;
    vert_temp[1][2] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][1])][2]) * scale;

    vert_temp[2][0] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][2])][0]) * scale;
    vert_temp[2][1] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][2])][1]) * scale;
    vert_temp[2][2] = (int8_t)pgm_read_byte(&vert_list[pgm_read_byte(&faces_list[i][2])][2]) * scale;

    rotate_vertices(vert_temp, vert_temp, 3, rotX, rotY, rotZ);

    display.fillTriangle(x + vert_temp[0][0], y + vert_temp[0][1], x + vert_temp[1][0], y + vert_temp[1][1], x + vert_temp[2][0], y + vert_temp[2][1], color);
  }
}

/////////////////////////////////////////////////////////

////////////////
// TODO
void char_to_vertices(uint8_t character, uint8_t out_vertices_array[][3], uint16_t array_size)
{
  uint8_t pixel_diameter = 6;
  // TODO:
}

#endif
