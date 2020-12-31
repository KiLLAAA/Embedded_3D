#include "engine_3D.h"

////////////////////////////////////////////////////////////////
// 3D representation of font Square Sans Serif 7 by Style-7

#define NUMBER_0_VERTS 8
#define NUMBER_1_VERTS 4
#define NUMBER_2_VERTS 12
#define NUMBER_3_VERTS 12
#define NUMBER_4_VERTS 10
#define NUMBER_5_VERTS 12
#define NUMBER_6_VERTS 12
#define NUMBER_7_VERTS 6
#define NUMBER_8_VERTS 12
#define NUMBER_9_VERTS 12

#define NUMBER_0_TRIS 8
#define NUMBER_1_TRIS 2
#define NUMBER_2_TRIS 10
#define NUMBER_3_TRIS 10
#define NUMBER_4_TRIS 8
#define NUMBER_5_TRIS 10
#define NUMBER_6_TRIS 12
#define NUMBER_7_TRIS 4
#define NUMBER_8_TRIS 14
#define NUMBER_9_TRIS 12

const int8_t number_0_verts[NUMBER_0_VERTS][3] PROGMEM = {
  { -16, -11, 0},
  {16, -11, 0},
  {16, 11, 0},
  { -16, 11, 0},
  { -11, 7, 0},
  {11, 7, 0},
  {11, -7, 0},
  { -11, -7, 0},
};

const uint8_t number_0_tris[NUMBER_0_TRIS][3] PROGMEM = {
  {3, 7, 0},
  {7, 1, 0},
  {7, 6, 1},
  {6, 2, 1},
  {3, 4, 7},
  {5, 2, 6},
  {3, 5, 4},
  {3, 2, 5},
};

const int8_t number_1_verts[NUMBER_1_VERTS][3] PROGMEM = {
  { -2, -11, 0},
  {2, -11, 0},
  {2, 11, 0},
  { -2, 11, 0},
};

const uint8_t number_1_tris[NUMBER_1_TRIS][3] PROGMEM = {
  {3, 1, 0},
  {3, 2, 1},
};

const int8_t number_2_verts[NUMBER_2_VERTS][3] PROGMEM = {
  { -11, 7, 0},
  {16, 7, 0},
  {16, 11, 0},
  { -16, 11, 0},
  { -16, -2, 0},
  {11, -2, 0},
  {11, -7, 0},
  { -16, -7, 0},
  { -16, -11, 0},
  {16, -11, 0},
  {16, 2, 0},
  { -11, 2, 0},
};

const uint8_t number_2_tris[NUMBER_2_TRIS][3] PROGMEM = {
  {7, 9, 8},
  {7, 6, 9},
  {6, 10, 9},
  {5, 10, 6},
  {3, 11, 4},
  {11, 5, 4},
  {11, 10, 5},
  {3, 0, 11},
  {3, 1, 0},
  {3, 2, 1},
};

const int8_t number_3_verts[NUMBER_3_VERTS][3] PROGMEM = {
  { -16, -11, 0},
  {16, -11, 0},
  {16, 11, 0},
  { -16, 11, 0},
  { -16, 7, 0},
  {11, 7, 0},
  {11, 2, 0},
  { -16, 2, 0},
  { -16, -2, 0},
  {11, -2, 0},
  {11, -7, 0},
  { -16, -7, 0},
};

const uint8_t number_3_tris[NUMBER_3_TRIS][3] PROGMEM = {
  {11, 1, 0},
  {11, 10, 1},
  {10, 2, 1},
  {9, 2, 10},
  {7, 9, 8},
  {7, 6, 9},
  {6, 2, 9},
  {5, 2, 6},
  {3, 5, 4},
  {3, 2, 5},
};

const int8_t number_4_verts[NUMBER_4_VERTS][3] PROGMEM = {
  { -16, -11, 0},
  { -11, -11, 0},
  { -11, -2, 0},
  {11, -2, 0},
  {11, -11, 0},
  {16, -11, 0},
  {16, 11, 0},
  {11, 11, 0},
  {11, 2, 0},
  { -16, 2, 0},
};

const uint8_t number_4_tris[NUMBER_4_TRIS][3] PROGMEM = {
  {9, 1, 0},
  {9, 2, 1},
  {3, 5, 4},
  {3, 6, 5},
  {9, 3, 2},
  {9, 8, 3},
  {8, 6, 3},
  {7, 6, 8},
};

const int8_t number_5_verts[NUMBER_5_VERTS][3] PROGMEM = {
  { -16, -11, 0},
  {16, -11, 0},
  {16, -7, 0},
  { -11, -7, 0},
  { -11, -2, 0},
  {16, -2, 0},
  {16, 11, 0},
  { -16, 11, 0},
  { -16, 7, 0},
  {11, 7, 0},
  {11, 2, 0},
  { -16, 2, 0},
};

const uint8_t number_5_tris[NUMBER_5_TRIS][3] PROGMEM = {
  {11, 3, 0},
  {3, 1, 0},
  {3, 2, 1},
  {11, 4, 3},
  {11, 5, 4},
  {11, 10, 5},
  {10, 6, 5},
  {9, 6, 10},
  {7, 9, 8},
  {7, 6, 9},
};

const int8_t number_6_verts[NUMBER_6_VERTS][3] PROGMEM = {
  { -16, -11, 0},
  {16, -11, 0},
  {16, -7, 0},
  { -11, -7, 0},
  { -11, -2, 0},
  {16, -2, 0},
  {16, 11, 0},
  { -16, 11, 0},
  { -11, 7, 0},
  {11, 7, 0},
  {11, 2, 0},
  { -11, 2, 0},
};

const uint8_t number_6_tris[NUMBER_6_TRIS][3] PROGMEM = {
  {7, 3, 0},
  {3, 1, 0},
  {3, 2, 1},
  {7, 4, 3},
  {7, 11, 4},
  {11, 5, 4},
  {11, 10, 5},
  {10, 6, 5},
  {7, 8, 11},
  {9, 6, 10},
  {7, 9, 8},
  {7, 6, 9},
};

const int8_t number_7_verts[NUMBER_7_VERTS][3] PROGMEM = {
  { -16, -11, 0},
  {16, -11, 0},
  {16, 11, 0},
  {11, 11, 0},
  {11, -7, 0},
  { -16, -7, 0},
};

const uint8_t number_7_tris[NUMBER_7_TRIS][3] PROGMEM = {
  {5, 1, 0},
  {5, 4, 1},
  {4, 2, 1},
  {3, 2, 4},
};

const int8_t number_8_verts[NUMBER_8_VERTS][3] PROGMEM = {
  { -16, -11, 0},
  {16, -11, 0},
  {16, 11, 0},
  { -16, 11, 0},
  { -11, 7, 0},
  {11, 7, 0},
  {11, 2, 0},
  { -11, 2, 0},
  { -11, -2, 0},
  {11, -2, 0},
  {11, -7, 0},
  { -11, -7, 0},
};

const uint8_t number_8_tris[NUMBER_8_TRIS][3] PROGMEM = {
  {3, 11, 0},
  {11, 1, 0},
  {11, 10, 1},
  {10, 2, 1},
  {3, 8, 11},
  {9, 2, 10},
  {3, 7, 8},
  {7, 9, 8},
  {7, 6, 9},
  {6, 2, 9},
  {3, 4, 7},
  {5, 2, 6},
  {3, 5, 4},
  {3, 2, 5},
};

const int8_t number_9_verts[NUMBER_9_VERTS][3] PROGMEM = {
  {16, 11, 0},
  { -16, 11, 0},
  { -16, 7, 0},
  {11, 7, 0},
  {11, 2, 0},
  { -16, 2, 0},
  { -16, -11, 0},
  {16, -11, 0},
  { -11, -2, 0},
  {11, -2, 0},
  {11, -7, 0},
  { -11, -7, 0},
};

const uint8_t number_9_tris[NUMBER_9_TRIS][3] PROGMEM = {
  {5, 11, 6},
  {11, 7, 6},
  {11, 10, 7},
  {10, 0, 7},
  {5, 8, 11},
  {9, 0, 10},
  {5, 9, 8},
  {5, 4, 9},
  {4, 0, 9},
  {3, 0, 4},
  {1, 3, 2},
  {1, 0, 3},
};

const object3D number_0 [] PROGMEM = {number_0_verts, sizeof(number_0_verts) / sizeof(number_0_verts[0]), number_0_tris, sizeof(number_0_tris) / sizeof(number_0_tris[0])};
const object3D number_1 [] PROGMEM = {number_1_verts, sizeof(number_1_verts) / sizeof(number_1_verts[0]), number_1_tris, sizeof(number_1_tris) / sizeof(number_1_tris[0])};
const object3D number_2 [] PROGMEM = {number_2_verts, sizeof(number_2_verts) / sizeof(number_2_verts[0]), number_2_tris, sizeof(number_2_tris) / sizeof(number_2_tris[0])};
const object3D number_3 [] PROGMEM = {number_3_verts, sizeof(number_3_verts) / sizeof(number_3_verts[0]), number_3_tris, sizeof(number_3_tris) / sizeof(number_3_tris[0])};
const object3D number_4 [] PROGMEM = {number_4_verts, sizeof(number_4_verts) / sizeof(number_4_verts[0]), number_4_tris, sizeof(number_4_tris) / sizeof(number_4_tris[0])};
const object3D number_5 [] PROGMEM = {number_5_verts, sizeof(number_5_verts) / sizeof(number_5_verts[0]), number_5_tris, sizeof(number_5_tris) / sizeof(number_5_tris[0])};
const object3D number_6 [] PROGMEM = {number_6_verts, sizeof(number_6_verts) / sizeof(number_6_verts[0]), number_6_tris, sizeof(number_6_tris) / sizeof(number_6_tris[0])};
const object3D number_7 [] PROGMEM = {number_7_verts, sizeof(number_7_verts) / sizeof(number_7_verts[0]), number_7_tris, sizeof(number_7_tris) / sizeof(number_7_tris[0])};
const object3D number_8 [] PROGMEM = {number_8_verts, sizeof(number_8_verts) / sizeof(number_8_verts[0]), number_8_tris, sizeof(number_8_tris) / sizeof(number_8_tris[0])};
const object3D number_9 [] PROGMEM = {number_9_verts, sizeof(number_9_verts) / sizeof(number_9_verts[0]), number_9_tris, sizeof(number_9_tris) / sizeof(number_9_tris[0])};

const object3D* const numbers3D[10] PROGMEM = {number_0, number_1, number_2, number_3, number_4, number_5, number_6, number_7, number_8, number_9};

void draw_3D_number(uint8_t number, int16_t x, int16_t y, float rotX, float rotY, float rotZ, float scale) {
  number = number % 10;
  /*if (number > 9) {
    return;
    };*/
#ifdef __AVR__
  const object3D* object = (const object3D*) pgm_read_ptr(&numbers3D[number]);
  uint8_t vertcount = pgm_read_word(&object->numVerts); //number_0
  uint8_t polycount = pgm_read_word(&object->numTriPolys); //number_0
  const int8_t (*vert_list)[3] = pgm_read_ptr(&object->vert_list);
  const uint8_t (*faces_list)[3] = pgm_read_ptr(&object->faces_list);
#elif defined (__arm__) // __STM32F1__
  const object3D* object = (const object3D*)(numbers3D[number]);
  uint16_t vertcount = object->numVerts; //number_0
  uint16_t polycount = object->numTriPolys; //number_0
  const int8_t (*vert_list)[3] = object->vert_list;
  const uint8_t (*faces_list)[3] = object->faces_list;
#endif

  int8_t vertlist_temp[vertcount][3]; // temp
  rotate_vertices(vert_list, vertlist_temp, vertcount, rotX, rotY, rotZ); // rotate
  scale_vertices(vertlist_temp, vertlist_temp, vertcount, scale); // scale
  draw_tri_faces(vertlist_temp, faces_list, polycount, x, y);

  //draw_tri_faces(vert_list, faces_list, polycount, x, y, scale, rotX, rotY, rotZ); // TODO
  //draw_tri_faces(vert_list, faces_list, polycount, x, y);
};

void fill_3D_number(uint8_t number, int16_t x, int16_t y, float rotX, float rotY, float rotZ, float scale) {
  number = number % 10;
  /*if (number > 9) {
    return;
    };*/
#ifdef __AVR__
  const object3D* object = (const object3D*) pgm_read_ptr(&numbers3D[number]);
  uint8_t vertcount = pgm_read_word(&object->numVerts); //number_0
  uint8_t polycount = pgm_read_word(&object->numTriPolys); //number_0
  const int8_t (*vert_list)[3] = pgm_read_ptr(&object->vert_list);
  const uint8_t (*faces_list)[3] = pgm_read_ptr(&object->faces_list);
#elif defined (__arm__) // __STM32F1__
  const object3D* object = (const object3D*)(numbers3D[number]);
  uint16_t vertcount = object->numVerts; //number_0
  uint16_t polycount = object->numTriPolys; //number_0
  const int8_t (*vert_list)[3] = object->vert_list;
  const uint8_t (*faces_list)[3] = object->faces_list;
#endif

  int8_t vertlist_temp[vertcount][3]; // temp
  rotate_vertices(vert_list, vertlist_temp, vertcount, rotX, rotY, rotZ); // rotate
  scale_vertices(vertlist_temp, vertlist_temp, vertcount, scale); // scale
  fill_tri_faces(vertlist_temp, faces_list, polycount, x, y);

  //draw_tri_faces(vert_list, faces_list, polycount, x, y, scale, rotX, rotY, rotZ); // TODO
  //draw_tri_faces(vert_list, faces_list, polycount, x, y);
};
