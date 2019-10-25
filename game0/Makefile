#
# Makefile for saucer shoot game using Dragonfly
#
# Copyright Mark Claypool and WPI, 2016-2019
#
# 'make' to build executable
# 'make depend' to generate new dependency list
# 'make clean' to remove all constructed files
#
# Variables of interest:
#   GAMESRC is the source code files for the game
#   GAME is the game main() source
#   EXECUTABLE is the name of the runnable game
#

# Compiler
CC= g++ 

# Libraries and includes.
LINKDIR= -L../dragonfly/lib # path to dragonfly library
INCDIR= -I../dragonfly/include # path to dragonfly includes

# Uncomment and update below if using local SFML installation.
LINKDIR:= $(LINKDIR) -L$(HOME)/src/SFML-2.5.1/lib 
INCDIR:= $(INCDIR) -I$(HOME)/SFML-2.5.1/include

### Uncomment only 1 of the below! ###

# 1) Uncomment below for Linux (64-bit)
CFLAGS= -Wall
LINKLIB= -ldragonfly-linux64 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lrt

# 2) Uncomment below for Mac (64-bit)
# Note: if homebrew install sfml, may be in:
#   /usr/local/Cellar/sfml
#CFLAGS=
#LINKLIB= -ldragonfly-mac64 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio 
#LINKDIR= -L/usr/local/Cellar/sfml/2.5.0/lib/ -L../dragonfly/lib/ 
#INCDIR= -I/usr/local/Cellar/sfml/2.5.0/include/ -I../dragonfly/include/

######

GAMESRC= \

GAME= game.cpp
EXECUTABLE= game
OBJECTS= $(GAMESRC:.cpp=.o)

all: $(EXECUTABLE) Makefile

$(EXECUTABLE): $(OBJECTS) $(GAME) $(GAMESRC) 
	$(CC) $(CFLAGS) $(GAME) $(OBJECTS) -o $@ $(INCDIR) $(LINKDIR) $(LINKLIB) 

.cpp.o: 
	$(CC) $(CFLAGS) -c $(INCDIR) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) core dragonfly.log Makefile.bak *~
# DO NOT DELETE
