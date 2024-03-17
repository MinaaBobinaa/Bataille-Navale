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


# CUnit
# ----
cunits:
	gcc CUnit/cunits.c jeu.c -o cunits -lcunit
	gcc CUnit/cunits.c jeu.c -o cunits -lcunit -coverage
	./cunits
	gcov ./cunits-cunits
	gcov ./cunits-jeu

# Clean
# ----

clean:
	rm -f $(OBJECTS) $(TARGET) $(FILE)
	rm -f cunits cunits.c.gcov cunits-cunits.gcda cunits-cunits.gcno cunits-jeu.gcda cunits-jeu.gcno jeu.c.gcov

#Phony
#----
.PHONY: build test cunits clean