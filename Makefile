bats=bats/bats-core/bin/bats
CC=gcc
CFLAGS = -Wall -Wextra -std=c99
SOURCES = main.c jeu.c stats.c
OBJECTS=$(SOURCES:.c=.o)
TARGET=bataille_navale 
FILE=stats.txt
CUNITSFILE=cunits cunits.c.gcov cunits-cunits.gcda cunits-cunits.gcno 
JEUFILE=cunits-jeu.gcda cunits-jeu.gcno jeu.c.gcov
STATFILE=cunits-stats.gcda cunits-stats.gcno stats.c.gcov stats_test_output.txt

# Build
# -----
pre-build: clean

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
	$(CC) CUnit/cunits.c jeu.c stats.c -o cunits -lcunit -coverage
	./cunits
	gcov ./cunits-cunits
	gcov ./cunits-jeu
	gcov ./cunits-stats

# Clean
# ----

clean:
	rm -f $(OBJECTS) $(TARGET) $(FILE)
	rm -f $(CUNITSFILE) $(JEUFILE) $(STATFILE)

#Phony
#----
.PHONY: build test cunits clean