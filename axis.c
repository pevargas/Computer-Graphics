////////////////////////////////////////////////////////////////////////////////
// File: axis.c
// Author: Patrick Vargas               rintintin.colorado.edu/~vargasp
// Definition
//   Supplies a function to draw an axis
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
#include "Athena.h"
#include "CSCIx229.h"
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Distance Forumla
float distance(double x0, double y0, double x1, double y1) {
  float dx = pow(x1 - x0, 2);
  float dy = pow(y1 - y0, 2);
  return abs(sqrt(dx+dy));
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
void drawAxis(double dim, double x, double y, double z) {
  double dot;
  double len = (3*dim)/4.0;
  double div = (len/5);

  // Push Attributes for Politness
  glPushAttrib(GL_CURRENT_BIT | GL_POINT_BIT);

  // Draw axes in white
  glColor3f(1.0, 1.0, 1.0); // White
  glBegin(GL_LINES);
  glVertex3d(x, y, z); glVertex3d(x + len, y, z);
  glVertex3d(x, y, z); glVertex3d(x, y + len, z);
  glVertex3d(x, y, z); glVertex3d(x, y, z + len);
  
  // Draw Negative axis
  glColor3f(0.25, 0.25, 0.25); // Charcoal
  glVertex3d(x, y, z); glVertex3d(x - len, y, z);
  glVertex3d(x, y, z); glVertex3d(x, y - len, z);
  glVertex3d(x, y, z); glVertex3d(x, y, z - len);
  glEnd();

  // Draw Tick Marks
  glPointSize(4);
  glColor3f(0.25, 0.25, 0.25); // Charcoal
  glBegin(GL_POINTS);
  for (dot = -len; dot < 0; dot += div) {
    glVertex3d(x + dot, y, z);
    glVertex3d(x, y + dot, z);
    glVertex3d(x, y, z + dot);
  }
  glEnd();

  glColor3f(1.0, 1.0, 1.0); // White
  glBegin(GL_POINTS);
  for (; dot < len; dot += div) {
    glVertex3d(x + dot, y, z);
    glVertex3d(x, y + dot, z);
    glVertex3d(x, y, z + dot);    
  }
  glEnd();

  // Reset
  glPointSize(1);

  // Label axes
  glRasterPos3d(x + len + (div/2), y, z);
  Print("X");
  glRasterPos3d(x, y + len + (div/2), z);
  Print("Y");
  glRasterPos3d(x, y, z + len + (div/2));
  Print("Z");

  // Pop Attributes for Politness
  glPopAttrib();
}
////////////////////////////////////////////////////////////////////////////////
