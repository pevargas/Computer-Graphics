////////////////////////////////////////////////////////////////////////////////
// File: particles.c
// Author: Patrick Vargas               rintintin.colorado.edu/~vargasp
// Definition
//   Supplies a few funcitons to draw things.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
#include "Athena.h"
#include "CSCIx229.h"
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
float slow = 0.1f;
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
GLfloat tetra[][3] = {
  {+1.0, +0.0, -0.7071},
  {-1.0, +0.0, -0.7071},
  {+0.0, +1.0, +0.7071},
  {+0.0, -1.0, +0.7071}
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Color Each Particle
void ColorPart(particle *part, int i, float red, float green, float blue) {
  // Push Attributes for Politness
  glPushAttrib(GL_CURRENT_BIT | GL_POINT_BIT | 
	       GL_LINE_BIT | GL_TEXTURE_BIT);


  // Pop Attributes for Politness
  glPopAttrib();
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Draw particles
void DrawPart(unsigned int *texture, particle *part, 
	      double x, double y, double z,
	      double s, double r) {
  int i;            // Iterator
  float px, py, pz; // Position

  // Push Attributes for Politness
  glPushAttrib(GL_CURRENT_BIT | GL_POINT_BIT | 
	       GL_LINE_BIT | GL_TEXTURE_BIT);

  // Save transformation
  glPushMatrix();
  // Offset
  glTranslated(x,y,z);
  glRotated(r,0,1,0);
  glScaled(s, s, s);

  // Add Textures
  /* 
  glDisable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);
  */
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture[DIRT]);  

  for (i = 0; i < MAXPART; ++i) {
    if (part[i].active) { // Make sure it's active!
      px = part[i].xp;
      py = part[i].yp;
      pz = part[i].zp;

      if (py < 0)
	partinit(part, i);
      else {
	//glColor4f(part[i].r, part[i].g, part[i].b, 1 /*part[i].life*/);
	
	glBegin(GL_QUADS);
	glNormal3d(0, 0, -1);
	glTexCoord2d(1.0, 0.0); glVertex3f(px + 0.5, py - 0.5, pz - 0.5);
	glTexCoord2d(1.0, 1.0); glVertex3f(px + 0.5, py + 0.5, pz - 0.5);
	glTexCoord2d(0.0, 1.0); glVertex3f(px - 0.5, py + 0.5, pz - 0.5);
	glTexCoord2d(0.0, 0.0); glVertex3f(px - 0.5, py - 0.5, pz - 0.5);

	glNormal3d(0, 0, +1);
	glTexCoord2d(1.0, 0.0); glVertex3f(px + 0.5, py - 0.5, pz + 0.5);
	glTexCoord2d(1.0, 1.0); glVertex3f(px + 0.5, py + 0.5, pz + 0.5);
	glTexCoord2d(0.0, 1.0); glVertex3f(px - 0.5, py + 0.5, pz + 0.5);
	glTexCoord2d(0.0, 0.0); glVertex3f(px - 0.5, py - 0.5, pz + 0.5);

	glNormal3d(0, -1, 0);
	glTexCoord2d(1.0, 0.0); glVertex3f(px + 0.5, py - 0.5, pz - 0.5);
	glTexCoord2d(1.0, 1.0); glVertex3f(px + 0.5, py - 0.5, pz + 0.5);
	glTexCoord2d(0.0, 1.0); glVertex3f(px - 0.5, py - 0.5, pz + 0.5);
	glTexCoord2d(0.0, 0.0); glVertex3f(px - 0.5, py - 0.5, pz - 0.5);      

	glNormal3d(0, +1, 0);
	glTexCoord2d(1.0, 0.0); glVertex3f(px + 0.5, py + 0.5, pz - 0.5);
	glTexCoord2d(1.0, 1.0); glVertex3f(px + 0.5, py + 0.5, pz + 0.5);
	glTexCoord2d(0.0, 1.0); glVertex3f(px - 0.5, py + 0.5, pz + 0.5);
	glTexCoord2d(0.0, 0.0); glVertex3f(px - 0.5, py + 0.5, pz - 0.5);      

	glNormal3d(-1, 0, 0);
	glTexCoord2d(1.0, 0.0); glVertex3f(px - 0.5, py - 0.5, pz + 0.5);
	glTexCoord2d(1.0, 1.0); glVertex3f(px - 0.5, py + 0.5, pz + 0.5);
	glTexCoord2d(0.0, 1.0); glVertex3f(px - 0.5, py + 0.5, pz - 0.5);
	glTexCoord2d(0.0, 0.0); glVertex3f(px - 0.5, py - 0.5, pz - 0.5);
		
	glNormal3d(+1, 0, 0);
	glTexCoord2d(1.0, 0.0); glVertex3f(px + 0.5, py - 0.5, pz + 0.5);
	glTexCoord2d(1.0, 1.0); glVertex3f(px + 0.5, py + 0.5, pz + 0.5);
	glTexCoord2d(0.0, 1.0); glVertex3f(px + 0.5, py + 0.5, pz - 0.5);
	glTexCoord2d(0.0, 0.0); glVertex3f(px + 0.5, py - 0.5, pz - 0.5);
	glEnd();
       
	  /*
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2d(0.0, 1.0); glVertex3f(tetra[0][0] + px, tetra[0][1] + py, tetra[0][2] + pz);
	glTexCoord2d(1.0, 0.0); glVertex3f(tetra[1][0] + px, tetra[1][1] + py, tetra[1][2] + pz);
	glTexCoord2d(0.5, 1.0); glVertex3f(tetra[2][0] + px, tetra[2][1] + py, tetra[2][2] + pz);
	glTexCoord2d(0.5, 0.0); glVertex3f(tetra[3][0] + px, tetra[3][1] + py, tetra[3][2] + pz);
	glTexCoord2d(0.0, 1.0); glVertex3f(tetra[0][0] + px, tetra[0][1] + py, tetra[0][2] + pz);
	glTexCoord2d(1.0, 0.0); glVertex3f(tetra[1][0] + px, tetra[1][1] + py, tetra[1][2] + pz);
	glEnd();
	  */

	// Move Particle
	part[i].xp += part[i].xd/(slow*1000); // Move on X-Axis By X Speed
	part[i].yp += part[i].yd/(slow*1000); // Move on Y-Axis By Y Speed
	part[i].zp += part[i].zd/(slow*1000); // Move on Z-Axis By Z Speed
	
	// Add Gravity
	part[i].xd += part[i].xg; // Add X-Axis Gravity
	part[i].yd += part[i].yg; // Add Y-Axis Gravity
	part[i].zd += part[i].zg; // Add Z-Axis Gravity
	
	// Reduce particle Life by 'Fade'
	part[i].life -= part[i].fade;
	
	if (part[i].life < 0)
	  partinit(part, i);
      }
    }
  }

  // Reset Things
  glDisable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  // Switch off textures
  glDisable(GL_TEXTURE_2D);
  // Undo transofrmations
  glPopMatrix();
  // Pop Attributes for Politness
  glPopAttrib();
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Random numbers with range and offset
float frand(float rng,float off) {
  return rand()*rng/RAND_MAX+off;
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Initialize ALL the particles
void InitPart(particle *part) {
  int i; // Iterator
  
  for (i = 0; i < MAXPART; ++i)
    partinit(part, i);
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Initialize individual particles
void partinit(particle *part, int i) {
  float v = rand()%1000;   // Velocity
  float th = rand()%360; // Angle

  part[i].active = true;                 // Make ALL the particles active
  part[i].life = 1.0;                    // Give ALL the particles full life
  part[i].fade = frand(100, 0.003);      // Random Fade Speed
  /*part[i].r    = red;               // Red Color
  part[i].g    = green;               // Green Color
  part[i].b    = blue;               // Blue Color
  */part[i].xp   = 0.0;                    // Center
  part[i].yp   = 0.0;                    // Oscilating
  part[i].zp   = 0.0;                    // Center
  part[i].xd   = Sin(th) * v;            // X Speed;
  part[i].yd   = v; //frand(50, -25) * v;     // Y Speed;
  part[i].zd   = Cos(th) * v;            // Z Speed;
  part[i].xg   = 0;                      // No X-Axis pull
  part[i].yg   = -10;                   // Vertical pull down
  part[i].zg   = 0;                      // No Z-Axis pull
}
////////////////////////////////////////////////////////////////////////////////


