CFLAGS += -std=c99 -Wall -Werror

# find our hammer build - adjust this to your needs
# i have, for instance, symlinks:
# hammer@ -> ../hammer/src
# lib@ -> ../hammer/build/opt/src
HAMMER_INCLUDE = .
HAMMER_LIB = ./lib
CFLAGS += -I$(HAMMER_INCLUDE)
LDFLAGS += -L$(HAMMER_LIB)
SOURCES = d1achar.c d1aitemtypes.c d1aspecialist.c d1askills.c d1aweaponmasteries.c

#.PHONY: all test clean
.PHONY: all clean
all: d1achar d1achar_debug

d1achar: $(SOURCES)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(SOURCES) -lhammer

d1achar_debug: $(SOURCES)
	$(CC) -o $@ $(CFLAGS) -g $(LDFLAGS) $(SOURCES) -lhammer

clean:
	rm -f d1achar d1achar_debug
