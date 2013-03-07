////////////////////////////////////////////////////////////////////////////////
// File: shapes.c
// Author: Patrick Vargas               rintintin.colorado.edu/~vargasp
// Definition
//   Supplies a few funcitons to draw things.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
#include "Athena.h"
#include "CSCIx229.h"
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Draw a tornado at position (x, y, z), scaled by s, rotated by r; 
//   Pass into the function the texture array
void drawTor(unsigned int *texture,
	     double x, double y, double z, 
	     double s, double r) {
  double rot;

  // Push Attributes for Politness
  glPushAttrib(GL_CURRENT_BIT | GL_POINT_BIT | 
	       GL_LINE_BIT | GL_TEXTURE_BIT);

  // Save transformation
  glPushMatrix();
  // Offset
  glTranslated(x, y, z);
  glRotated(r, 0, 1, 0);
  glScaled(s, s, s);

  for (rot = 0; rot < M_PI*20; rot += 1)
    drawTri(texture, rot*Sin(10*rot), rot*10, rot*Cos(10*rot), rot*10, rot);

  // Switch off textures
  glDisable(GL_TEXTURE_2D);
  // Undo transofrmations
  glPopMatrix();
  // Pop Attributes for Politness
  glPopAttrib();
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Draw a triangle at position (x, y, z), scaled by s, rotated by r; 
//   Pass into the function the texture array
void drawTri(unsigned int *texture, double x, double y, double z, 
	     double s, double r) {
  // Push Attributes for Politness
  glPushAttrib(GL_CURRENT_BIT | GL_POINT_BIT | 
	       GL_LINE_BIT | GL_TEXTURE_BIT);

  // Save transformation
  glPushMatrix();
  // Offset
  glTranslated(x, y, z);
  glRotated(r, 0, 1, 0);
  glScaled(s, 1, s);
  
  //glDisable(GL_DEPTH_TEST);
  //glEnable(GL_BLEND);
  //glBlendFunc(GL_SRC_ALPHA, GL_ONE);

  // Add Textures
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  glBindTexture(GL_TEXTURE_2D, texture[CLOUD]);  
  // Draw Triangle
  glBegin(GL_TRIANGLES);
  glNormal3f(+0.0, -1.0, +0.0);
  glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -10, -0.433);
  glTexCoord2f(1.0, 0.0); glVertex3f(+0.5, -10, -0.433);
  glTexCoord2f(0.5, 0.433); glVertex3f(+0.0, -10, +0.433);

  glNormal3f(+0.0, +1.0, +0.0);
  glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, +10, -0.433);
  glTexCoord2f(1.0, 0.0); glVertex3f(+0.5, +10, -0.433);
  glTexCoord2f(0.5, 0.433); glVertex3f(+0.0, +10, +0.433);
  glEnd();

  glBegin(GL_QUADS);
  glNormal3f(+0.0, +0.0, -1.0);
  glTexCoord2f(1.0, 0.0); glVertex3f(+0.5, -10, -0.433);
  glTexCoord2f(1.0, 1.0); glVertex3f(+0.5, +10, -0.433);
  glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, +10, -0.433);
  glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -10, -0.433);

  glNormal3f(-0.866, +0.5, +0.0);
  glTexCoord2f(1.0, 0.0); glVertex3f(+0.5, +10, -0.433);
  glTexCoord2f(0.0, 0.0); glVertex3f(+0.5, -10, -0.433);
  glTexCoord2f(0.0, 1.0); glVertex3f(+0.0, -10, +0.433);
  glTexCoord2f(1.0, 1.0); glVertex3f(+0.0, +10, +0.433);

  glNormal3f(+0.866, +0.5, +0.0);
  glTexCoord2f(1.0, 0.0); glVertex3f(+0.0, -10, +0.433);
  glTexCoord2f(1.0, 1.0); glVertex3f(+0.0, +10, +0.433);
  glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, +10, -0.433);
  glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -10, -0.433);
  glEnd();

  // Reset Things
  //  glDisable(GL_BLEND);
  //glEnable(GL_DEPTH_TEST);
  // Switch off textures
  glDisable(GL_TEXTURE_2D);
  // Undo transofrmations
  glPopMatrix();
  // Pop Attributes for Politness
  glPopAttrib();
}
////////////////////////////////////////////////////////////////////////////////
