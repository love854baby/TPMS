CC = gcc
OBJECTS = Main.o TPMS.o

all: $(OBJECTS)
	$(CC) $(OBJECTS) -lm

%.o: %.c TPMS.h
	$(CC) -c $<

clean: $(OBJECTS) a.out
	rm *.o a.out
