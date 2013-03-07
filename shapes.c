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
// Define Material
materialStruct whiteShiny = {
  {1.0, 1.0, 1.0, 1.0},
  {1.0, 1.0, 1.0, 1.0},
  {1.0, 1.0, 1.0, 1.0},
  {0.0, 0.0, 0.0, 1.0},
  100.0
};
materialStruct basic = {
  {1.0, 1.0, 1.0, 1.0},
  {1.0, 1.0, 1.0, 1.0},
  {1.0, 1.0, 1.0, 1.0},
  {0.0, 0.0, 0.0, 1.0},
  0.0
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Draw a barn at position (x, y, z), scaled by s, rotated by r; Pass into
//   the function the texture array
void drawBarn(unsigned int *texture, double x, double y, double z,
	      double s, double r) {
  // Push Attributes for Politness
  glPushAttrib(GL_CURRENT_BIT | GL_POINT_BIT | 
	       GL_LINE_BIT | GL_TEXTURE_BIT);

  // Define Materials
  materials(&basic);

  // Save transformation
  glPushMatrix();
  // Offset
  glTranslated(x,y,z);
  glRotated(r,0,1,0);
  glScaled(s, s, s);

  // Add Textures
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  glBindTexture(GL_TEXTURE_2D, texture[BARNSIDE]);  
  glBegin(GL_QUADS);
  // Left
  glNormal3f(-1, 0, 0);
  glTexCoord2f(0.0, 0.0); glVertex3f(-20, -12, -30);
  glTexCoord2f(1.0, 0.0); glVertex3f(-20, -12, +30);
  glTexCoord2f(1.0, 1.0); glVertex3f(-20,  +4, +30);
  glTexCoord2f(0.0, 1.0); glVertex3f(-20,  +4, -30);
  // Right
  glNormal3f(+1, 0, 0);
  glTexCoord2f(0.0, 0.0); glVertex3f(+20, -12, -30);
  glTexCoord2f(1.0, 0.0); glVertex3f(+20, -12, +30);
  glTexCoord2f(1.0, 1.0); glVertex3f(+20,  +4, +30);
  glTexCoord2f(0.0, 1.0); glVertex3f(+20,  +4, -30);
  glEnd();

  // Front
  glBegin(GL_POLYGON);
  glNormal3f(0, 0, +1);
  glTexCoord2f(0.00, 0.00); glVertex3f(-20, -12, +30);
  glTexCoord2f(1.00, 0.00); glVertex3f(+20, -12, +30);
  glTexCoord2f(1.00, 0.67); glVertex3f(+20,  +4, +30);
  glTexCoord2f(0.75, 0.91); glVertex3f(+10, +10, +30);
  glTexCoord2f(0.50, 1.00); glVertex3f( +0, +12, +30);
  glTexCoord2f(0.24, 0.91); glVertex3f(-10, +10, +30);
  glTexCoord2f(0.00, 0.67); glVertex3f(-20,  +4, +30);
  glEnd();
  
  // Back
  glBegin(GL_POLYGON);
  glNormal3f(0, 0, -1);
  glTexCoord2f(0.00, 0.00); glVertex3f(-20, -12, -30);
  glTexCoord2f(1.00, 0.00); glVertex3f(+20, -12, -30);
  glTexCoord2f(1.00, 0.67); glVertex3f(+20,  +4, -30);
  glTexCoord2f(0.75, 0.91); glVertex3f(+10, +10, -30);
  glTexCoord2f(0.50, 1.00); glVertex3f( +0, +12, -30);
  glTexCoord2f(0.24, 0.91); glVertex3f(-10, +10, -30);
  glTexCoord2f(0.00, 0.67); glVertex3f(-20,  +4, -30);
  glEnd();
 
  // Floor
  glBindTexture(GL_TEXTURE_2D, texture[CONCRETE]);    
  glBegin(GL_QUADS);
  glNormal3f(0, +1, 0);
  glTexCoord2f(0.0, 0.0); glVertex3f(-20, -12, -30);
  glTexCoord2f(1.0, 0.0); glVertex3f(-20, -12, +30);
  glTexCoord2f(1.0, 1.0); glVertex3f(+20, -12, +30);
  glTexCoord2f(0.0, 1.0); glVertex3f(+20, -12, -30);
  glEnd();

  // Roof
  glBindTexture(GL_TEXTURE_2D, texture[BARNROOF]);    
  glBegin(GL_QUADS);
  // Bottom
  glNormal3f(-3, -5, 0);
  glTexCoord2f(0.00, 0.00); glVertex3f(+21, +3.4, +31);
  glTexCoord2f(4.00, 0.00); glVertex3f(+21, +3.4, -31);
  glTexCoord2f(4.00, 1.05); glVertex3f(+10,  +10, -31);
  glTexCoord2f(0.00, 1.05); glVertex3f(+10,  +10, +31);
  glNormal3f(-1, -5, 0);
  glTexCoord2f(0.00, 1.05); glVertex3f(+10,  +10, +31);
  glTexCoord2f(4.00, 1.05); glVertex3f(+10,  +10, -31);
  glTexCoord2f(4.00, 2.00); glVertex3f( +0,  +12, -31);
  glTexCoord2f(0.00, 2.00); glVertex3f( +0,  +12, +31);
  glNormal3f(+1, -5, 0);  
  glTexCoord2f(0.00, 2.00); glVertex3f( +0,  +12, +31);
  glTexCoord2f(4.00, 2.00); glVertex3f( +0,  +12, -31);
  glTexCoord2f(4.00, 2.95); glVertex3f(-10,  +10, -31);
  glTexCoord2f(0.00, 2.95); glVertex3f(-10,  +10, +31);
  glNormal3f(+3, -5, 0);
  glTexCoord2f(0.00, 2.95); glVertex3f(-10,  +10, +31);
  glTexCoord2f(4.00, 2.95); glVertex3f(-10,  +10, -31);
  glTexCoord2f(4.00, 4.00); glVertex3f(-21, +3.4, -31);
  glTexCoord2f(0.00, 4.00); glVertex3f(-21, +3.4, +31);
  glEnd();
  // Bottom - End

  // Top
  glBegin(GL_QUADS); 
  glNormal3f(+3, +5, 0);
  glTexCoord2f(0.00, 0.00); glVertex3f(+21, +4.4, +31);
  glTexCoord2f(4.00, 0.00); glVertex3f(+21, +4.4, -31);
  glTexCoord2f(4.00, 1.05); glVertex3f(+10,  +11, -31);
  glTexCoord2f(0.00, 1.05); glVertex3f(+10,  +11, +31);
  glNormal3f(+1, +5, 0);
  glTexCoord2f(0.00, 1.05); glVertex3f(+10,  +11, +31);
  glTexCoord2f(4.00, 1.05); glVertex3f(+10,  +11, -31);
  glTexCoord2f(4.00, 2.00); glVertex3f( +0,  +13, -31);
  glTexCoord2f(0.00, 2.00); glVertex3f( +0,  +13, +31);
  glNormal3f(-1, +5, 0);  
  glTexCoord2f(0.00, 2.00); glVertex3f( +0,  +13, +31);
  glTexCoord2f(4.00, 2.00); glVertex3f( +0,  +13, -31);
  glTexCoord2f(4.00, 2.95); glVertex3f(-10,  +11, -31);
  glTexCoord2f(0.00, 2.95); glVertex3f(-10,  +11, +31);
  glNormal3f(-3, +5, 0);
  glTexCoord2f(0.00, 2.95); glVertex3f(-10,  +11, +31);
  glTexCoord2f(4.00, 2.95); glVertex3f(-10,  +11, -31);
  glTexCoord2f(4.00, 4.00); glVertex3f(-21, +4.4, -31);
  glTexCoord2f(0.00, 4.00); glVertex3f(-21, +4.4, +31);
  glEnd();
  // Top - End

  // Trim
  glBindTexture(GL_TEXTURE_2D, texture[TRIM]);    
  glBegin(GL_QUAD_STRIP);
  glNormal3f(0, 0, +1);
  glTexCoord2f(0.00, 0.00); glVertex3f(+21, +3.4, +31);
  glTexCoord2f(0.00, 0.10); glVertex3f(+21, +4.4, +31);
  glTexCoord2f(1.05, 0.00); glVertex3f(+10,  +10, +31);
  glTexCoord2f(1.05, 0.10); glVertex3f(+10,  +11, +31);
  glTexCoord2f(2.00, 0.00); glVertex3f( +0,  +12, +31);
  glTexCoord2f(2.00, 0.10); glVertex3f( +0,  +13, +31);
  glTexCoord2f(2.95, 0.00); glVertex3f(-10,  +10, +31);
  glTexCoord2f(2.95, 0.10); glVertex3f(-10,  +11, +31);
  glTexCoord2f(4.00, 0.00); glVertex3f(-21, +3.4, +31);
  glTexCoord2f(4.00, 0.10); glVertex3f(-21, +4.4, +31);
  glEnd();

  glBegin(GL_QUAD_STRIP);
  glNormal3f(0, 0, -1);
  glTexCoord2f(0.00, 0.00); glVertex3f(+21, +3.4, -31);
  glTexCoord2f(0.00, 0.10); glVertex3f(+21, +4.4, -31);
  glTexCoord2f(1.05, 0.00); glVertex3f(+10,  +10, -31);
  glTexCoord2f(1.05, 0.10); glVertex3f(+10,  +11, -31);
  glTexCoord2f(2.00, 0.00); glVertex3f( +0,  +12, -31);
  glTexCoord2f(2.00, 0.10); glVertex3f( +0,  +13, -31);
  glTexCoord2f(2.95, 0.00); glVertex3f(-10,  +10, -31);
  glTexCoord2f(2.95, 0.10); glVertex3f(-10,  +11, -31);
  glTexCoord2f(4.00, 0.00); glVertex3f(-21, +3.4, -31);
  glTexCoord2f(4.00, 0.10); glVertex3f(-21, +4.4, -31);
  glEnd();

  glBegin(GL_POLYGON);
  glNormal3f(-1, 0, 0);
  glTexCoord2f(0.00, 0.00); glVertex3f(-21, +3.4, +31);
  glTexCoord2f(0.00, 0.00); glVertex3f(-21, +3.4, -31);
  glTexCoord2f(7.00, 0.10); glVertex3f(-21, +4.4, -31);
  glTexCoord2f(7.00, 0.10); glVertex3f(-21, +4.4, +31);
  glEnd();

  glBegin(GL_POLYGON);
  glNormal3f(+1, 0, 0);
  glTexCoord2f(0.00, 0.00); glVertex3f(+21, +3.4, +31);
  glTexCoord2f(0.00, 0.00); glVertex3f(+21, +3.4, -31);
  glTexCoord2f(7.00, 0.10); glVertex3f(+21, +4.4, -31);
  glTexCoord2f(7.00, 0.10); glVertex3f(+21, +4.4, +31);
  glEnd();
  // Trim - End
  // Roof - End
  
  // Switch off textures
  glDisable(GL_TEXTURE_2D);
  // Undo transofrmations
  glPopMatrix();
  // Pop Attributes for Politness
  glPopAttrib();
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Draws a disc or a cone with height p, radius r, position (x,y,z) with
//   texture text
void drawDisc(unsigned int *texture, int text, materialStruct *mat,
	      double x, double y, double z, double p, double r) {
  int th;
  
  // Push Attributes for Politness
  glPushAttrib(GL_CURRENT_BIT | GL_POINT_BIT | 
	       GL_LINE_BIT | GL_TEXTURE_BIT);
  
  // Save transformation
  glPushMatrix();
  glTranslated(x, y, z);

  // Define Materials
  if (mat != NULL) materials(mat);
  
  // Add Textures
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture[text]);
  
  glBegin(GL_TRIANGLE_FAN);
  glTexCoord2f(0.5, 0.5); glVertex3f(0.0, p, 0.0);
  for (th = 0; th <= 360; th += 10) {
    if (p != 0) glNormal3f(p*r*Cos(th), r, p*r*Sin(th));
    else glNormal3f(0, 1, 0);
    glTexCoord2f((10.0/2.0)*Cos(th) + 0.5, (10.0/2.0)*Sin(th) + 0.5);
    glVertex3f(Cos(th)*r, 0, Sin(th)*r);
  }
  glEnd();

  // Switch off textures
  glDisable(GL_TEXTURE_2D);
  // Pop Attributes for Politness
  glPopAttrib();
  //  Undo transofrmations
  glPopMatrix();
}  
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Draw a farm at position (x, y, z), scaled by s, rotated by r; Pass into
//   the function the texture array
void drawFarm(unsigned int *texture, double x, double y, double z, 
	      double s, double r) {
  // Push Attributes for Politness
  glPushAttrib(GL_CURRENT_BIT | GL_POINT_BIT | 
	       GL_LINE_BIT | GL_TEXTURE_BIT);

  // Save transformation
  glPushMatrix();
  // Offset
  glTranslated(x, y, z);
  glRotated(r, 0, 1, 0);
  glScaled(s, s, s);

  drawBarn(texture, -30, +12, -10, 1, 30);
  drawSilo(texture, +15, +20, -20, 1, 0);
  drawHouse(texture, +30, +4, +15, 1, -30);

  // Undo transofrmations
  glPopMatrix();
  // Pop Attributes for Politness
  glPopAttrib();
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Draw a house at position (x, y, z), scaled by s, rotated by r; Pass into
//   the function the texture array
void drawHouse(unsigned int *texture, double x, double y, 
	       double z, double s, double r) {
  // Push Attributes for Politness
  glPushAttrib(GL_CURRENT_BIT | GL_POINT_BIT | 
	       GL_LINE_BIT | GL_TEXTURE_BIT);

  // Define Materials
  materials(&basic);

  // Save transformation
  glPushMatrix();
  // Offset
  glTranslated(x,y,z);
  glRotated(r,0,1,0);
  glScaled(s, s, s);

  // Add Textures
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  glBindTexture(GL_TEXTURE_2D, texture[HOUSESIDE]);  
  glBegin(GL_QUADS);
  // Left
  glNormal3f(-1, 0, 0);
  glTexCoord2f(0.0, 0.0); glVertex3f(-10, -4, -15);
  glTexCoord2f(1.0, 0.0); glVertex3f(-10, -4, +15);
  glTexCoord2f(1.0, 1.0); glVertex3f(-10, +4, +15);
  glTexCoord2f(0.0, 1.0); glVertex3f(-10, +4, -15);
  // Right
  glNormal3f(+1, 0, 0);
  glTexCoord2f(0.0, 0.0); glVertex3f(+10, -4, -15);
  glTexCoord2f(2.0, 0.0); glVertex3f(+10, -4, +15);
  glTexCoord2f(2.0, 2.0); glVertex3f(+10, +4, +15);
  glTexCoord2f(0.0, 2.0); glVertex3f(+10, +4, -15);
  glEnd();

  // Front
  glBegin(GL_POLYGON);
  glNormal3f(0, 0, +1);
  glTexCoord2f(0.00, 0.00); glVertex3f(-10, -4, +15);
  glTexCoord2f(2.00, 0.00); glVertex3f(+10, -4, +15);
  glTexCoord2f(2.00, 1.60); glVertex3f(+10, +4, +15);
  glTexCoord2f(1.00, 2.00); glVertex3f( +0, +6, +15);
  glTexCoord2f(0.00, 1.60); glVertex3f(-10, +4, +15);
  glEnd();
  
  // Back
  glBegin(GL_POLYGON);
  glNormal3f(0, 0, -1);
  glTexCoord2f(0.00, 0.00); glVertex3f(-10, -4, -15);
  glTexCoord2f(2.00, 0.00); glVertex3f(+10, -4, -15);
  glTexCoord2f(2.00, 1.60); glVertex3f(+10, +4, -15);
  glTexCoord2f(1.00, 2.00); glVertex3f( +0, +6, -15);
  glTexCoord2f(0.00, 1.60); glVertex3f(-10, +4, -15);
  glEnd();
  
  // Floor
  glBindTexture(GL_TEXTURE_2D, texture[CONCRETE]);    
  glBegin(GL_QUADS);
  glNormal3f(0, +1, 0);
  glTexCoord2f(0.0, 0.0); glVertex3f(-10, -4, -15);
  glTexCoord2f(2.0, 0.0); glVertex3f(-10, -4, +15);
  glTexCoord2f(2.0, 2.0); glVertex3f(+10, -4, +15);
  glTexCoord2f(0.0, 2.0); glVertex3f(+10, -4, -15);
  glEnd();

  // Roof
  glBindTexture(GL_TEXTURE_2D, texture[HOUSEROOF]);    
  glBegin(GL_QUADS);
  // Bottom
  glNormal3f(+1, +5, 0);
  glTexCoord2f(0.0, 0.0); glVertex3f(+11, +3.8, +16);
  glTexCoord2f(0.0, 2.0); glVertex3f(+0,  +6.0, +16);
  glTexCoord2f(4.0, 2.0); glVertex3f(+0,  +6.0, -16);
  glTexCoord2f(4.0, 0.0); glVertex3f(+11, +3.8, -16);

  glNormal3f(-1, +5, 0);
  glTexCoord2f(0.0, 4.0); glVertex3f(-11, +3.8, +16);
  glTexCoord2f(0.0, 2.0); glVertex3f(+0,  +6.0, +16);
  glTexCoord2f(4.0, 2.0); glVertex3f(+0,  +6.0, -16);
  glTexCoord2f(4.0, 4.0); glVertex3f(-11, +3.8, -16);
  glEnd();
  // Bottom - End
  
  // Top
  glBegin(GL_QUADS);
  glNormal3f(+1, +5, 0);
  glTexCoord2f(0.0, 0.0); glVertex3f(+11, +4.8, +16);
  glTexCoord2f(0.0, 2.0); glVertex3f( +0, +7.0, +16);
  glTexCoord2f(4.0, 2.0); glVertex3f( +0, +7.0, -16);
  glTexCoord2f(4.0, 0.0); glVertex3f(+11, +4.8, -16);

  glNormal3f(-1, +5, 0);
  glTexCoord2f(0.0, 4.0); glVertex3f(-11, +4.8, +16);
  glTexCoord2f(0.0, 2.0); glVertex3f( +0, +7.0, +16);
  glTexCoord2f(4.0, 2.0); glVertex3f( +0, +7.0, -16);
  glTexCoord2f(4.0, 4.0); glVertex3f(-11, +4.8, -16);
  glEnd();
  // Top - End

  // Trim
  glBindTexture(GL_TEXTURE_2D, texture[TRIM]);    
  glBegin(GL_QUAD_STRIP);
  glNormal3f(0, 0, +1);
  glTexCoord2f(0.0, 0.0); glVertex3f(+11, +3.8, +16);
  glTexCoord2f(0.0, 0.4); glVertex3f(+11, +4.8, +16);
  glTexCoord2f(1.0, 0.0); glVertex3f( +0, +6.0, +16);
  glTexCoord2f(1.0, 0.4); glVertex3f( +0, +7.0, +16);
  glTexCoord2f(2.0, 0.0); glVertex3f(-11, +3.8, +16);
  glTexCoord2f(2.0, 0.4); glVertex3f(-11, +4.8, +16);
  glEnd();

  glBegin(GL_QUAD_STRIP);
  glNormal3f(0, 0, -1);
  glTexCoord2f(0.0, 0.0); glVertex3f(+11, +3.8, -16);
  glTexCoord2f(0.0, 0.4); glVertex3f(+11, +4.8, -16);
  glTexCoord2f(1.0, 0.0); glVertex3f( +0, +6.0, -16);
  glTexCoord2f(1.0, 0.4); glVertex3f( +0, +7.0, -16);
  glTexCoord2f(2.0, 0.0); glVertex3f(-11, +3.8, -16);
  glTexCoord2f(2.0, 0.4); glVertex3f(-11, +4.8, -16);
  glEnd();

  glBegin(GL_POLYGON);
  glNormal3f(+1, 0, 0);
  glTexCoord2f(0.0, 0.0); glVertex3f(+11, +3.8, -16);
  glTexCoord2f(0.0, 0.4); glVertex3f(+11, +4.8, -16);
  glTexCoord2f(2.0, 0.4); glVertex3f(+11, +4.8, +16);
  glTexCoord2f(2.0, 0.0); glVertex3f(+11, +3.8, +16);  
  glEnd();

  glBegin(GL_POLYGON);
  glNormal3f(-1, 0, 0);
  glTexCoord2f(0.0, 0.0); glVertex3f(-11, +3.8, -16);
  glTexCoord2f(0.0, 0.4); glVertex3f(-11, +4.8, -16);
  glTexCoord2f(2.0, 0.4); glVertex3f(-11, +4.8, +16);
  glTexCoord2f(2.0, 0.0); glVertex3f(-11, +3.8, +16);
  glEnd();
  // Trim - End
  // Roof - End

  // Switch off textures
  glDisable(GL_TEXTURE_2D);
  // Undo transofrmations
  glPopMatrix();
  // Pop Attributes for Politness
  glPopAttrib();
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Draws the road
void drawRoad(unsigned int *texture) {
  double length = DIMINIT*(MAXZOOM + 0.2);
  double dis = DIMINIT*MAXZOOM/2;

  // Push Attributes for Politness
  glPushAttrib(GL_CURRENT_BIT | GL_POINT_BIT | 
	       GL_LINE_BIT | GL_TEXTURE_BIT);
  
  // Save transformation
  glPushMatrix();
 
  // Define Materials
  materials(&basic);
  
  // Add Textures
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture[ROAD]);
  
  glBegin(GL_QUADS);
  glNormal3f(0, +1, 0);
  glTexCoord2f(0.0, 0.0);    glVertex3f(-length, 0, -10);
  glTexCoord2f(0.0, 1.0);    glVertex3f(-length, 0, +10);
  glTexCoord2f(length, 1.0); glVertex3f(+length, 0, +10);
  glTexCoord2f(length, 0.0); glVertex3f(+length, 0, -10);

  glTexCoord2f(0.0, 0.0);       glVertex3f(+dis - 10, 0, +dis);
  glTexCoord2f(0.0, 1.0);       glVertex3f(+dis + 10, 0, +dis);
  glTexCoord2f(DIMINIT/2, 1.0); glVertex3f(+dis + 10, 0, +0);
  glTexCoord2f(DIMINIT/2, 0.0); glVertex3f(+dis - 10, 0, +0);

  glTexCoord2f(0.0, 0.0);       glVertex3f(+dis - 10, 0, -dis);
  glTexCoord2f(0.0, 1.0);       glVertex3f(+dis + 10, 0, -dis);
  glTexCoord2f(DIMINIT/2, 1.0); glVertex3f(+dis + 10, 0, +0);
  glTexCoord2f(DIMINIT/2, 0.0); glVertex3f(+dis - 10, 0, +0);

  glTexCoord2f(0.0, 0.0);       glVertex3f(-dis - 10, 0, -dis);
  glTexCoord2f(0.0, 1.0);       glVertex3f(-dis + 10, 0, -dis);
  glTexCoord2f(DIMINIT/2, 1.0); glVertex3f(-dis + 10, 0, +0);
  glTexCoord2f(DIMINIT/2, 0.0); glVertex3f(-dis - 10, 0, +0);
  glEnd();

  // Switch off textures
  glDisable(GL_TEXTURE_2D);
  // Pop Attributes for Politness
  glPopAttrib();
  //  Undo transofrmations
  glPopMatrix();
}  
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Draw a sphere at (x,y,z) with radius (r), with the texture (text) 
//   and material properties materials
void drawSphere(unsigned int *texture, int text, 
		materialStruct *mat, double x, 
		double y, double z, double r) {
  int th,ph;
  int inc =  1;  // Ball increment

  // Push Attributes for Politness
  glPushAttrib(GL_CURRENT_BIT | GL_POINT_BIT | 
	       GL_LINE_BIT | GL_TEXTURE_BIT);
  
  // Save transformation
  glPushMatrix();
  // Offset, scale and rotate
  glTranslated(x, y, z);
  glScaled(r, r, r);
  glRotated(0, 1, 0, 0);

  // Define materials
  if (mat != NULL) materials(mat);

  // Apply texture
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture[text]);
  //  Bands of latitude
  for (ph = -90; ph < 90; ph += inc) {
      glBegin(GL_QUAD_STRIP);
      for (th = 0; th <= 360; th += 2*inc) {
	drawVertex(th, ph, r);
	drawVertex(th, ph + inc, r);
      }
      glEnd();
  }
  // Switch off textures
  glDisable(GL_TEXTURE_2D);
  //  Undo transofrmations
  glPopMatrix();
  // Pop Attributes for Politness
  glPopAttrib();
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Draw a silo at position (x, y, z), scaled by s, rotated by r; Pass into
//   the function the texture array
void drawSilo(unsigned int *texture, double x, double y, 
	      double z, double s, double r) {
  int th;
  // Push Attributes for Politness
  glPushAttrib(GL_CURRENT_BIT | GL_POINT_BIT | 
	       GL_LINE_BIT | GL_TEXTURE_BIT);

  // Define Materials
  materials(&basic);

  // Save transformation
  glPushMatrix();
  // Offset
  glTranslated(x,y,z);
  glRotated(r,0,1,0);
  glScaled(s, s, s);

  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  // Base
  drawDisc(texture, CONCRETE, NULL, 0, -20, 0, 0, 10);
  // Roof
  drawDisc(texture, BARNROOF, NULL, 0, +20, 0, 5, 11);
  drawDisc(texture, BARNROOF, NULL, 0, +21, 0, 5, 11);
  
  // Sides
  glBindTexture(GL_TEXTURE_2D, texture[BARNSIDE]);  
  glBegin(GL_QUAD_STRIP);
  for (th = 0; th <= 360; th += 10) {
    glNormal3f(Cos(th), 0, Sin(th));
    glTexCoord2f((1*th)/360.0, 0.0);
    glVertex3f(Cos(th)*10, -20, Sin(th)*10);
    glTexCoord2f((1*th)/360.0, 1.0);
    glVertex3f(Cos(th)*10, +20, Sin(th)*10);
  }
  glEnd();

  // Trim
  glBindTexture(GL_TEXTURE_2D, texture[TRIM]);  
  glBegin(GL_QUAD_STRIP);
  for (th = 0; th <= 360; th += 10) {
    glNormal3f(Cos(th), 0, Sin(th));
    glTexCoord2f((th*5.0)/360.0, 0.0);
    glVertex3f(Cos(th)*11, +20, Sin(th)*11);
    glTexCoord2f((th*5.0)/360.0, 0.25);
    glVertex3f(Cos(th)*11, +21, Sin(th)*11);
  }
  glEnd();

  // Switch off textures
  glDisable(GL_TEXTURE_2D);
  // Undo transofrmations
  glPopMatrix();
  // Pop Attributes for Politness
  glPopAttrib();
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Draw vertex in polar coordinates with normal
void drawVertex(double th, double ph, double r) {
  double x   = Sin(th)*Cos(ph);
  double y   = Cos(th)*Cos(ph);
  double z   =         Sin(ph);

  // For a sphere at the origin, the position
  //   and normal vectors are the same
  glNormal3d(x, y, z);
  glTexCoord2d(-th/360.0, ph/180.0 + 0.5);
  glVertex3d(x, y, z);

}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Defines the lighting properties of materials.
void materials(materialStruct *materials) {
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   materials -> ambi);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   materials -> diff);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  materials -> spec);
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,  materials -> emis);
  glMaterialf(GL_FRONT_AND_BACK,  GL_SHININESS, materials -> shin);
}
////////////////////////////////////////////////////////////////////////////////
