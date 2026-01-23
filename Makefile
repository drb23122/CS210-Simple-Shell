# Usage: make to build, make run to run, make clean to remove build and binary files
# Optional Arguments: you can set release=1, sanitize=1 to build in release profile, or with address sanitizer

# Use the gcc compiler
CC := gcc

# A bunch of flags to enforce code safety and best practices
CFLAGS := -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wpointer-arith -Wstrict-overflow=2 -Wformat=2 -Wundef -Wcast-align -Wswitch-enum -Wuninitialized -Wfloat-equal -fstack-protector-strong -D_FORTIFY_SOURCE=2
DEVFLAGS := -g -O
ASFLAGS := -fsanitize=address,undefined,leak

# if release=1 is set, don't include extra debug info
release ?= 0
ifeq ($(release), 0)
	CFLAGS += $(DEVFLAGS)
else
	CFLAGS += -Oz
endif

# If sanitize=1 is set, run with address sanitizer
sanitize ?= 0
ifeq ($(sanitize), 1)
	CFLAGS += $(ASFLAGS)
endif

# List of files to include in build
FILES := $(wildcard src/*.c)
OBJS := $(patsubst src/%.c,build/%.o, $(FILES))

# Ensure these targets are not mistaken as files to make
.PHONY: all run dir clean

all: bin/shell

bin/shell: $(OBJS) | dir
	$(CC) $(OBJS) -o $@

build/%.o: src/%.c | dir
	$(CC) $(CFLAGS) -c $< -o $@

dir:
	@mkdir -p build bin

# make run - Run program
run: bin/shell
	@./bin/shell

# make clean - remove all output files
clean:
	rm -rf build bin
