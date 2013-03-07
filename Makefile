# Makefile
# Author: Willem Shreuder
# Student: Patrick Vargas

# The program to build
GL = final

# Libraries - Linux
LIBS = -lglut -lGLU
# Libraries - OSX
#LIBS=-framework GLUT -framework OpenGL
# Libraries - MinGW
#LIBS=-lglut32cu -lglu32 -lopengl32

# Main Target
all: $(GL)

# Generic Compile Rules
.c.o:
	gcc -c -O -Wall $<

# Generic Compile and Link
%: %.c CSCIx229.a Athena.a
	gcc -Wall -O3 -o $@ $^ $(LIBS)

# Delete unwanted files - Linux or OX/X
clean:;rm -f $(GL) *.o *.a *~
# Delete unwanted files - MinGW
#clean:;del *.exe *.o *.a

# Create archive (include glWindowPos here if you need it)
CSCIx229.a:fatal.o loadtexbmp.o print.o project.o errcheck.o object.o fps.o elapsed.o shader.o noise.o
	ar -rcs CSCIx229.a $^

Athena.a:axis.o shapes.o particles.o light.o tornado.o
	ar -rcs Athena.a $^

# Obligatory UNIX inside joke
love:
	@echo "not war?"