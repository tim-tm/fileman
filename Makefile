CC=cc
CFLAGS=-Wall -Wextra -pedantic -g
LFLAGS=

ifeq ($(BUILD_TYPE),RELEASE)
CFLAGS=-Wall -Wextra -pedantic -Os -ffunction-sections -fdata-sections
LFLAGS=-Wl,--gc-sections
endif

ifeq ($(LIBC_STATIC),TRUE)
CFLAGS += -static -static-libgcc
endif

SRCDIR=src
BUILDDIR=build
BINARY=$(BUILDDIR)/fileman

SRC=$(wildcard $(SRCDIR)/*.c)
OBJ=$(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SRC))

all: $(BINARY)

$(BINARY): $(BUILDDIR)/$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(BINARY) $(LFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

setup:
	mkdir -p $(BUILDDIR)

clean:
	rm -f $(OBJ)
	rm -f $(BINARY)

install: all
	sudo cp $(BINARY) /usr/bin
