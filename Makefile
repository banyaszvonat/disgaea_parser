CFLAGS += -std=c99 -Wall -Werror

# find our hammer build - adjust this to your needs
# i have, for instance, symlinks:
# hammer@ -> ../hammer/src
# lib@ -> ../hammer/build/opt/src
HAMMER_INCLUDE = .
HAMMER_LIB = ./lib
CFLAGS += -I$(HAMMER_INCLUDE)
LDFLAGS += -L$(HAMMER_LIB)
SOURCES = d1achar.c d1aitemtypes.c

#.PHONY: all test clean
.PHONY: all clean
all: d1achar

d1achar: $(SOURCES)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(SOURCES) -lhammer

clean:
	rm -f d1achar
