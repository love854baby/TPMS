CC = gcc
OBJECTS = Main.o TPMS.o

all: $(OBJECTS)
	$(CC) $(OBJECTS) -lm -g3

%.o: %.c TPMS.h
	$(CC) -c $<

clean: $(OBJECTS) a.out
	rm *.o a.out
