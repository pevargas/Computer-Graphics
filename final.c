////////////////////////////////////////////////////////////////////////////////
// File: final.c                        June 2012
// Author: Patrick Vargas               rintintin.colorado.edu/~vargasp/
// CSCI 4229: Computer Graphics         Boulder, CO
//
// Description
//   Creates a simple scene with textures and lighting.
//
// User Controls
//   'e' to toggle axes
//   '0' reset properties
//   'r' toggle path of sun
//   arrows to rotate the world
//   aswd to move in the world
//   +/- to zoom in and out
//   'x' toggle movement of sun
//   z/c move sun
//
// References
//   Angel, E. (2008). OpenGL: A Primer. (3rd ed.). Boston, MA: Pearson
//     Education, Inc.
//   Schreuder, W. (2012). ex9.c, ex12.c, ex14.c, ex17.c  CSCI 4229: Computer 
//     Graphics Boulder, CO: University of Colorado
//   Vargas, P. (2012). hw3.c. Boulder, CO: University of Colorado
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Libraries
#include "CSCIx229.h"
#include "Athena.h"
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Globals
int verbose  = false;            // For Diagnostic information.
int axes     = false;            // Display axes
int rise     = false;            // Make the sun travel horiz. or vert.
int stop     = false;            // Stop the Sun!
int th       = THINIT;           // Azimuth of view angle
int ph       = PHINIT;           // Elevation of view angle
int zh       = 0;                // Light azimuth
int fov      = DIMINIT;          // Field of view (for perspective)
int i        = 0;                // Iterartor
double asp   = 1;                // Aspect ratio
double zoom  = ZOOMINIT;         // Zoom varible
double dim   = DIMINIT;          // Size of world in feet
double offx  = 0;                // Offests
double offy  = 0;                //   "
double offz  = 0;                //   "
double osc   = 0;                // Roation of Tornado
double mov   = 0;                // Movement of Tornado
unsigned int texture[MAXTEXT];   // Texture names
particle part[MAXPART];       // Particle Array
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
materialStruct theSky = {
  {1.0, 1.0, 1.0, 1.0},
  {1.0, 1.0, 1.0, 1.0},
  {1.0, 1.0, 0.0, 1.0},
  {1.0, 1.0, 1.0, 1.0},
  100.0
};

materialStruct TwilightIn = {
  {1.0, 1.0, 1.0, 1.0},
  {1.0, 1.0, 1.0, 1.0},
  {1.0, 1.0, 0.0, 1.0},
  {1.0, 1.0, 1.0, 1.0},
  100.0
};

materialStruct TwilightOut = {
  {1.0, 1.0, 1.0, 1.0},
  {1.0, 1.0, 1.0, 1.0},
  {1.0, 1.0, 0.0, 1.0},
  {1.0, 1.0, 1.0, 1.0},
  100.0
};

materialStruct Night = {
  {1.0, 1.0, 1.0, 1.0},
  {1.0, 1.0, 1.0, 1.0},
  {1.0, 1.0, 0.0, 1.0},
  {0.0, 0.0, 0.0, 1.0},
  0.0
};
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Declarations
// OpenGL (GLUT) calls this routine to display the scene
void display();

// This function is called by GLUT when idle
void idle();

// Funciton for enabling and seting up the situation.
void init();

// GLUT calls this routine when a key is pressed
void key(unsigned char ch,int x,int y);

//  Load textures
void loadTextures(unsigned int *texture);

// GLUT calls this routine when an arrow key is pressed
void special(int key,int x,int y);

// GLUT calls this routine when the window is resized
void reshape(int width,int height);

// Prints out instructions on the use of command line options.
void usage();
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Start up GLUT and tell it what to do
int main(int argc, char** argv) {
  char c;               // Used for line parsing
  // Parse the line
  while ((c = getopt(argc, argv, "hv")) != EOF) {
    switch (c) {
    case 'h': // Help message on command line options.
      usage();
      break;
    case 'v': // Print Diagnostic information.
      verbose = true;
      break;
    default:
      usage();
    }
  }
  if (verbose) { printf("Verbose turned on.\n"); }

  // Initialize GLUT
  glutInit(&argc,argv);
  // Request double buffered, true color window with Z buffering at 600x600
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
  glutInitWindowSize(600,600);
  glutCreateWindow("Final - Patrick Vargas");
  
  // Set callbacks
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutSpecialFunc(special);
  glutKeyboardFunc(key);
  glutIdleFunc(idle);

  loadTextures(texture);

  InitPart(part);
  
  // Pass control to GLUT so it can interact with the user
  ErrCheck("display");
  glutMainLoop();
  return 0;
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// OpenGL (GLUT) calls this routine to display the scene
void display() {
  int winHeight = glutGet(GLUT_WINDOW_HEIGHT);
  double Ex, Ey, Ez; // Eye Position
  int lightText = SUN;
  int time = SKY;
  materialStruct dayMat = theSky;
  //  int trans = ((zh%180 < 10) || (zh%180 > 170)) ? true: false;
  int nightTime = zh > 180; // Is it night time?

  // Erase the window and the depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // Undo previous transformations
  glLoadIdentity();

  // Perspective - set eye position
  Ex = -zoom*dim*Sin(th)*Cos(ph);
  Ey = +zoom*dim        *Sin(ph);
  Ez = +zoom*dim*Cos(th)*Cos(ph);
  gluLookAt(Ex + offx, Ey + offy, Ez + offz, offx, offy, offz, 0, Cos(ph), 0);

  // Smooth things over
  glShadeModel(GL_SMOOTH);
    
  // Location of viewer for specular calculations
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);
  // OpenGL should normalize normal vectors
  glEnable(GL_NORMALIZE);
  // Enable lighting
  glEnable(GL_LIGHTING);
  // Enable Object Material Coloring
  glEnable(GL_COLOR_MATERIAL);
  // glColor sets ambient and diffuse color materials
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

  // Draw sky dome
  if (rise) {
    if (nightTime) {
      lightText = MOON;
      time = NIGHT;
      dayMat = Night;
    } 
    else {
      lightText = SUN;
      time = SKY;
      dayMat = theSky;
    } 
  }
  else { 
    lightText = SUN;
    time = SKY;
    dayMat = theSky;
  }

  // SkyDome
  drawSphere(texture, time, &dayMat, offx, offy, offz, SKYDOME);

  // Draw the SUN! or Moon...
  mainLight(GL_LIGHT0, rise, nightTime, zh, 
	    texture, &theSky, 
	    lightText, dim);

  // Enable Z-buffering in OpenGL
  glEnable(GL_DEPTH_TEST);

  // Draw grass
  glEnable(GL_POLYGON_OFFSET_FILL);
  if (abs(ph) > 180) glPolygonOffset(-1, -1);
  else glPolygonOffset(+1, +1);
  drawDisc(texture, GRASS, &dayMat, 0, 0, 0, 0, SKYDOME);
  glDisable(GL_POLYGON_OFFSET_FILL);

  // Draw Structures
  drawFarm(texture, +SKYDOME/2, 0, +SKYDOME/2, 2, 150);
  drawFarm(texture, +SKYDOME/2, 0, -SKYDOME/2, 2, -120);
  drawFarm(texture, -SKYDOME/2, 0, -SKYDOME/2, 2, 45);
  drawFarm(texture, 0, 0, 0, 2, 0);

  drawTor(texture, (SKYDOME/4)*Cos(mov), 0, (SKYDOME/4)*Sin(mov), 2, osc);
  DrawPart(texture, part, (SKYDOME/4)*Cos(mov), 0, (SKYDOME/4)*Sin(mov), 10, 0);
  
  // Draw axes
  glDisable(GL_LIGHTING);
  if (axes) drawAxis(500*zoom, offx, offy, offz);
    
  // Display parameters
  glWindowPos2i(5, winHeight - 15);
  Print("Angle(%4d, %4d) Zoom=%.2f Pos(%5d, %5d) Elevation=%5dft", 
	th, ph, zoom, (int)offx, (int)offz, (int)offy);
  glWindowPos2i(5, 5);
  Print("FPS=%3d", FramesPerSecond());
  // Render the scene and make it visible
  glFlush();
  glutSwapBuffers();
  if (verbose) verbose = false;
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// This function is called by GLUT when idle
void idle() {  
  //  Elapsed time in seconds
  if (!stop) {
    double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
    zh = fmod(15*t, 360.0);
    osc = fmod(150*t, 360.0);
    mov = fmod(30*t, 360.0);
  }
  //  Request display update
  glutPostRedisplay();
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GLUT calls this routine when a key is pressed
void key(unsigned char ch,int x,int y) {
  // Exit on ESC, or Q
  if (ch == 27 || ch == 'Q' || ch == 'q') exit(0);
  // Reset view angle
  else if (ch == '0') { 
    th = THINIT;
    ph = PHINIT;
    dim = DIMINIT;
    zoom = ZOOMINIT;
    offx = offy = offz = 0;
  }
  // Change zoom
  else if ((ch == '+' || ch == '=') && zoom > 0.2) zoom -= 0.1;
  else if (ch == '-' && zoom < MAXZOOM) zoom += 0.1;
  // Toggle axes
  else if (ch == 'e' || ch == 'E') axes = 1 - axes;
  // Toggle sun orbit
  else if (ch == 'r' || ch == 'R') rise = 1 - rise;
  // Change Elevation
  else if (ch == 'F') offy += 100*zoom;
  else if (ch == 'f') offy -= 100*zoom;
  // Move camera
  else if (ch == 'w' || ch == 'W') {
    offx += 100*zoom*Cos(th + 90);
    offz += 100*zoom*Sin(th + 90);
  }
  else if (ch == 's' || ch == 'S') {
    offx += 100*zoom*Cos(th - 90);
    offz += 100*zoom*Sin(th - 90);
  }
  if (ch == 'a' || ch == 'A') {
    offx += 100*zoom*Cos(th);
    offz += 100*zoom*Sin(th);
  }
  else if (ch == 'd' || ch == 'D') { 
    offx -= 100*zoom*Cos(th);
    offz -= 100*zoom*Sin(th);
  }
  // Stop the Sun
  else if (ch == 'x' || ch == 'X') stop = 1 - stop;
  else if (ch == 'z' || ch == 'Z') --zh;
  else if (ch == 'c' || ch == 'C') ++zh;
  // Tell GLUT it is necessary to redisplay the scene
  glutPostRedisplay();
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//  Load textures
void loadTextures(unsigned int *texture) {
  texture[CONCRETE]  = LoadTexBMP("img/concrete.bmp");
  texture[BARNSIDE]  = LoadTexBMP("img/barn-side.bmp");
  texture[BARNROOF]  = LoadTexBMP("img/barn-roof.bmp");
  texture[TRIM]      = LoadTexBMP("img/trim.bmp");
  texture[SUN]       = LoadTexBMP("img/sun.bmp");
  texture[GRASS]     = LoadTexBMP("img/grass.bmp");
  texture[SKY]       = LoadTexBMP("img/sky-dome.bmp");
  texture[HOUSESIDE] = LoadTexBMP("img/house-wall.bmp");
  texture[HOUSEROOF] = LoadTexBMP("img/house-roof.bmp");
  texture[ROAD]      = LoadTexBMP("img/road.bmp");
  texture[DIRT]      = LoadTexBMP("img/dirt.bmp");
  texture[NIGHT]     = LoadTexBMP("img/sky-night.bmp");
  texture[PART]      = LoadTexBMP("img/particle.bmp");
  texture[BASKET]    = LoadTexBMP("img/basket.bmp");
  texture[MOON]      = LoadTexBMP("img/moon.bmp");
  texture[CLOUD]     = LoadTexBMP("img/clouds.bmp");
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GLUT calls this routine when an arrow key is pressed
void special(int key,int x,int y) {
  //  Right arrow key - increase angle by 5 degrees
  if (key == GLUT_KEY_RIGHT) th += 5;
  //  Left arrow key - decrease angle by 5 degrees
  else if (key == GLUT_KEY_LEFT) th -= 5;
  //  Up arrow key - increase elevation by 5 degrees
  else if (key == GLUT_KEY_UP) ph += 5;
  //  Down arrow key - decrease elevation by 5 degrees
  else if (key == GLUT_KEY_DOWN) ph -= 5;
  //  Keep angles to +/-360 degrees
  th %= 360;
  ph %= 360;
  //  Tell GLUT it is necessary to redisplay the scene
  glutPostRedisplay();
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GLUT calls this routine when the window is resized
void reshape(int width,int height) {
   // Ratio of the width to the height of the window
   double asp = (height > 0) ? (double)width/height : 1;
   // Set the viewport to the entire window
   glViewport(0, 0, width, height);
   // Set projection
   Project(fov, asp, dim);
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Prints out instructions on the use of command line options.
void usage() {
  printf("Flags:\n"
	 "\t-h\t\tPrints this message.\n"
	 "\t-v\t\tPrint diagnostic info\n");
}
////////////////////////////////////////////////////////////////////////////////
