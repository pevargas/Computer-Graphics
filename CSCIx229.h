////////////////////////////////////////////////////////////////////////////////
// File: CSCIx229.h
// Author: Willem Schruder
// Includes function from CSCIx239.h (Advanced Computer Graphics)
////////////////////////////////////////////////////////////////////////////////
#ifndef CSCIx229
#define CSCIx229
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//  Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//  Include GLEW if you need access to advanced features
#ifdef USEGLEW
#include <GL/glew.h>
#endif
//  Include GLUT and GL
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//  Handy macros for cos and sin in degrees
#define Cos(th) cos(3.1415926/180*(th))
#define Sin(th) sin(3.1415926/180*(th))
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//  Functions provided by the library

// Coherent noise function over 1, 2 or 3 dimensions
//   (copyright Ken Perlin)
int CreateNoise3D(int unit);

// Create Shader
void CreateShader(int prog,const GLenum type,const char* file);

// Create Shader Program
int CreateShaderProg(const char* VertFile,const char* FragFile);

// Create Shader Program with Location Names
int CreateShaderProgLoc(char* VertFile,char* FragFile,char* Name[]);

// Return elapsed wall time since last call (seconds)
double Elapsed(void);

// Check for OpenGL errors
void ErrCheck(char* where);

// Print message to stderr and exit
void Fatal(const char* format , ...);

// Frames per seconds
int FramesPerSecond(void);

// Load an OBJ file
//   Vertex, Normal and Texture coordinates are supported
//   Materials are supported
//   Textures must be BMP files
//   Surfaces are not supported
int LoadOBJ(const char* file);

// Load texture from BMP file
unsigned int LoadTexBMP(const char* file);

// Convenience routine to output raster text
//   Use VARARGS to make this more flexible
void Print(const char* format , ...);

// Print Program Log
void PrintProgramLog(int obj);

// Set projection
void Project(double fov,double asp,double dim);
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
