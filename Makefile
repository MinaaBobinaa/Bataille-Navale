CC=gcc
CFLAGS = -Wall -Wextra -std=c11
SOURCES = main.c jeu.c stats.c
OBJECTS=$(SOURCES:.c=.o)
TARGET=bataille_navale stats.txt


all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)


.PHONY: all clean