////////////////////////////////////////////////////////////////////////////////
// File: light.c
// Author: Patrick Vargas               rintintin.colorado.edu/~vargasp
// Definition
//   Supplies a few functions to draw things.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
#include "Athena.h"
#include "CSCIx229.h"
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Define some lighting structs
lightingStruct sunLight = {
  {0.3, 0.3, 0.3, 1.0},
  {1.0, 1.0, 1.0, 1.0},
  {0.0, 0.0, 0.0, 1.0}
};

lightingStruct whiteLighting = {
  {0.0, 0.0, 0.0, 1.0},
  {1.0, 1.0, 1.0, 1.0},
  {1.0, 1.0, 1.0, 1.0}
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Defines the lighting properties.
void lightings(GLenum light, lightingStruct *l, const GLfloat *pos) {
  glLightfv(light, GL_AMBIENT , l -> ambi);
  glLightfv(light, GL_DIFFUSE , l -> diff);
  glLightfv(light, GL_SPECULAR, l -> spec);
  glLightfv(light, GL_POSITION, pos);
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Draws the moon or the sun as the light source
void mainLight(GLenum light, int rise, int nightTime, int zh, 
	       unsigned int *texture, materialStruct *mat, 
	       int lightText, double dim){
  int dis  =  DIMINIT*MAXZOOM; // Light distance
  int deg  = rise? (nightTime? (zh - 180) : zh) : zh; // Degree fixing for moon
  float Pos[] = {
    dis*Cos(deg),
    rise? dis*Sin(deg) : dim/2.0,
    rise? 0 : dis*Sin(deg),
    0.5
  };

  // Enable Light0
  glEnable(GL_LIGHT0);
  lightings(GL_LIGHT0, &sunLight, Pos);

  drawSphere(texture, lightText, mat, Pos[0], Pos[1], Pos[2], 100);
}
////////////////////////////////////////////////////////////////////////////////
