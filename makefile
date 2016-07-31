# makeFile for ConnectFour
#
# Revision History:
# 6/11/2015 (JV): Initial Version
# 6/12/2015 (JB): removed warnings for deprecated functions
# 6/13/2015 (JV): Remove frameworks and used x11 ibraries
# 6/13/2015 (JB): added boardGfx.c

#FRAMEWORK = -framework GLUT
#FRAMEWORK += -framework OpenGL 
#NEW
PROGRAM = ConnectFour
COMPILERFLAGS = -Wall -Wno-deprecated-declarations
LIBRARIES = -L/usr/X11R6/lib -lGL -lGLU -lglut -lXmu -lXi -lm
CC = gcc 
CFLAGS = $(COMPILERFLAGS) 

OBJECTS = connectFour.o
OBJECTS += board.o
OBJECTS += boardGfx.o
OBJECTS += gfxLib.o
OBJECTS += win.o
OBJECTS += computer.o

All: ConnectFour 

${PROGRAM}: 	$(OBJECTS) 
		${CC} ${LIBRARIES} ${CFLAGS} -o ${PROGRAM} ${OBJECTS}

clean:
	rm -f *.o ${PROGRAM}
