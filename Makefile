bats=bats/bats-core/bin/bats
CC=gcc
CFLAGS = -Wall -Wextra -std=c99
SOURCES = main.c jeu.c stats.c
OBJECTS=$(SOURCES:.c=.o)
TARGET=bataille_navale 
FILE=stats.txt

# Build
# -----

build: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Test
# ----

test: test-bataille_navale

test-bataille_navale: $(TARGET) bataille_navale.bats
	$(bats) bataille_navale.bats

# Clean
# ----

clean:
	rm -f $(OBJECTS) $(TARGET) $(FILE)


.PHONY: build test clean