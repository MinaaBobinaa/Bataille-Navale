CC=gcc
CFLAGS = -Wall -Wextra -std=c11
SOURCES = main.c jeu.c
OBJECTS=$(SOURCES:.c=.o)
TARGET=bataille_navale


all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)


.PHONY: all clean