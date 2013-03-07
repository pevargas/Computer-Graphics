////////////////////////////////////////////////////////////////////////////////
// File: Athena.h
// Author: Patrick Vargas               rintintin.colorado.edu/~vargasp
// Definition
//   A usefull library full of wonderful things.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
#ifndef Athena
#define Athena
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Include Standard Headers
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
// Include GLEW if you need access to advanced features
#ifdef USEGLEW
#include <GL/glew.h>
#endif
// Include GLUT and GL
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Define Boolean Values
#define true  1
#define false 0

#define DIMINIT  1000.0  // Size of World Inital
#define THINIT   135.0   // Initial Azimuth
#define PHINIT   145.0   // Initial Elevation
#define ZOOMINIT 2.00    // Initial zoom level
#define MAXZOOM  5.0     // Max zoom level
#define MAXPART  10000   // Max number of Particles
#define SKYDOME  10500.0 // Radius of Sky Dome
#define TORH     11000   // Height of a Tornado

#define MODE 2

// Define Texture Indicies
#define CONCRETE  0
#define BARNSIDE  1
#define BARNROOF  2
#define TRIM      3
#define SUN       4
#define GRASS     5
#define SKY       6
#define HOUSESIDE 7
#define HOUSEROOF 8
#define ROAD      9
#define DIRT      10
#define NIGHT     11
#define PART      12
#define BASKET    13
#define MOON      14
#define CLOUD     15
#define MAXTEXT   16 // Total Number of Textures
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Define a few Structs
typedef struct {
  GLfloat ambi[4];
  GLfloat diff[4];
  GLfloat spec[4];
} lightingStruct;

typedef struct {
  GLfloat ambi[4];
  GLfloat diff[4];
  GLfloat spec[4];
  GLfloat emis[4];
  GLfloat shin;
} materialStruct;

typedef struct {
  int active;       // Active (Yes/No)
  float life;       // Particle Life
  float fade;       // Fade Speed
  float r, g, b;    // RGB color values
  float xp, yp, zp; // X, Y, Z position coordinates
  float xd, yd, zd; // X, Y, Z direction
  float xg, yg, zg; // X, Y, Z gravity
} particle;
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions provided by the library
//-----( From axis.c )----------------------------------------------------------
// Distance Forumla
float distance(double x0, double y0, double x1, double y1);

// Function to Draw Axis related to dimension of the world
void drawAxis(double dim, double x, double y, double z);

//-----( From light.c )---------------------------------------------------------
// Defines the lighting properties.
void lightings(GLenum light, lightingStruct *l, const GLfloat *pos);

// Draws the moon or the sun as the light source
void mainLight(GLenum light, int rise, int nightTime, int zh, 
	       unsigned int *texture, materialStruct *mat, 
	       int lightText, double dim);
//-----( From particles.c )-----------------------------------------------------
// Color Each Particle
void ColorPart(particle *part, int i, float red, float green, float blue);

// Draw particles
void DrawPart(unsigned int *texture, particle *part, 
	      double x, double y, double z,
	      double s, double r);

// Random numbers with range and offset
float frand(float rng,float off);

// Initialize ALL the particles
void InitPart(particle *part);

// Initialize individual particles
void partinit(particle *part, int i);

//-----( From shapes.c )--------------------------------------------------------
// Draw a barn at position (x, y, z), scaled by s, rotated by r; Pass into
//   the function the texture array
void drawBarn(unsigned int *texture, double x, double y, double z,
	      double s, double r);

// Draws a disc or a cone with height p, radius r, position (x,y,z) with
//   texture text
void drawDisc(unsigned int *texture, int text, materialStruct *mat,
	      double x, double y, double z, double p, double r);

// Draw a farm at position (x, y, z), scaled by s, rotated by r; Pass into
//   the function the texture array
void drawFarm(unsigned int *texture, double x, double y, double z,
	      double s, double r);

// Draw a house at position (x, y, z), scaled by s, rotated by r; Pass into
//   the function the texture array
void drawHouse(unsigned int *texture, double x, double y, 
	       double z, double s, double r);

// Draws the road
void drawRoad(unsigned int *texture);

// Draw a sphere at (x,y,z) with radius (r), with the texture (text) 
//   and material properties materials
void drawSphere(unsigned int *texture, int text, 
		materialStruct *mat, double x, 
		double y, double z, double r);

// Draw a silo at position (x, y, z), scaled by s, rotated by r; Pass into
//   the function the texture array
void drawSilo(unsigned int *texture, double x, double y, 
	      double z, double s, double r);

// Draw vertex in polar coordinates with normal
void drawVertex(double th,double ph, double r);

// Defines the lighting properties of materials.
void materials(materialStruct *materials);

//-----( From tornado.c )-------------------------------------------------------
// Draw a tornado at position (x, y, z), scaled by s, rotated by r; 
//   Pass into the function the texture array
void drawTor(unsigned int *texture, 
	     double x, double y, double z, 
	     double s, double r);

// Draw a triangle at position (x, y, z), scaled by s, rotated by r; 
//   Pass into the function the texture array
void drawTri(unsigned int *texture, double x, double y, double z,
	     double s, double r);

#endif
////////////////////////////////////////////////////////////////////////////////
