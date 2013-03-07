CSCI 4229: Computer Graphics
=================
Summer 2012  
University of Colorado at Boulder  
Final Project  

My final project for CSCI 4229: Computer Graphics. It depicts an animation of a tornado. The graphics were created using OpenGL 2.0.

Hours Spent: (40 -> hw3) 36

Student: Patrick Vargas  

Dependencies
------------

###CSCIx229.h  
A library full of functions, provided by [Professor Willem A. (Vlakkies) Schreüder, University of Colorado Boulder] (http://www.prinmath.com/csci5229/)
 * elapsed.c
 * errcheck.c
 * fatal.c
 * fps.c
 * loadtexbmp.c 
 * noise.c
 * object.c
 * print.c
 * project.c
 * shader.c

###Athena.h  
A library used to help draw.
 * axis.c
 * light.c
 * particles.c
 * shapes.c
 * tornado.c

Folders
-------
###img/  
Holds all the textures used. I do not own the rights for any of these textures. Textures found on Google.
 * barn-roof.bmp
 * barn-side.bmp
 * concrete.bmp
 * dot.bmp
 * grass.bmp
 * house-roof.bmp
 * house-wall.bmp
 * road.bmp
 * sky-dome.bmp
 * sky-night.bmp
 * sun.bmp
 * trim.bmp

Files
-----
###final.c  
File that simulates draws a visually appealing scene.

###Makefile  
Building and cleaning

###README  
This File

Executables
-----------
    ./final
Draw a scene filled with visually appealing objects.

Examples
--------

###Building  

####Build All:
    make

####Clean:
    make clean

###Interface  

####Quit:
    Q / q / Escape key

####Zoom In and Out:
    + / -

####Reset Everything:
    0

####Rotate the World:
    arrow keys

####Move in the World:
    a / s / w / d

####Toggle Axes:
    e / E

####Toggle Path of the Sun:
    r / R

####Toggle Movement of Sun:
    x / X

####Move the Sun when Stopped
    z / c
