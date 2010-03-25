CC = g++
CXXFLAGS = `allegro-config --cppflags` -m32 -g
LDFLAGS = `allegro-config --libs` -m32

OBJS = data.o dogss.o error.o map.o object.o player.o weapon.o window.o

all: dogss

dogss: $(OBJS)

clean:
	$(RM) dogss $(OBJS)
