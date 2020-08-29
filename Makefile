# Override C compiler
CC=gcc
CFLAGS = -W -Wall -Wextra -std=c89 -MMD
LDFLAGS = -lm

SDLFLAGS = -lSDL2 -D SDL
GTKFLAGS = `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0` -D GTK \
			-export-dynamic

DEBUGFLAGS = -g3 -O0 -fsanitize=address
RELEASEFLAGS = -O3

SRC = src/main.c \
	src/cli.c \
	src/ocr.c \
	src/bitmap/image.c \
	src/bitmap/bitmap.c \
	src/bitmap/image_drawing.c \
	src/bitmap/image_tools.c \
	src/bitmap/sdl_tools.c \
	$(wildcard src/filters/*.c) \
	$(wildcard src/neural/*.c)	\
	$(wildcard src/commons/*.c)	\
	$(wildcard src/recognition/*.c)

OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

# --------------------------------
#WASM

WASM_MAKEFILE = Makefile_wasm
WASM_PARAMS = 

# --------------------------------
# Check if we are in debug mode
ifdef debug
	CFLAGS += $(DEBUGFLAGS)
else 
	CFLAGS += $(RELEASEFLAGS)
endif

# --------------------------------
# Add SDL if needed
ifdef nosdl
	WASM_PARAMS = nosdl=1
else
	LDFLAGS += $(SDLFLAGS)
endif

# --------------------------------
# Add GTK if required

ifndef nogtk
	# Add gui source file
	SRC += src/gui_gtk.c
	LDFLAGS += $(GTKFLAGS)
endif

# --------------------------------
# Rules

all: ocr

clean:
	rm -rf bin/ocr
	rm -rf $(OBJ) $(DEP)
	make -f $(WASM_MAKEFILE) clean

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ -c $<

ocr: $(OBJ)
	@mkdir -p bin
	@mkdir -p bin/exported
	@cp src/ocr_gui.glade bin/ocr_gui.glade
	@cp src/dataset.txt bin/dataset.txt
	$(CC) $(CFLAGS) $(OBJ) -o bin/ocr $(LDFLAGS)

debug:
	$(CC) $(CFLAGS) $(SRC) -g3 -o bin/ocr $(LDFLAGS)

wasm:
	make -f $(WASM_MAKEFILE) $(WASM_PARAMS)

demo: ocr
	@cp samples/*.bmp bin/
	cd bin;./ocr -t train_data.txt


.PHONY: clean all wasm debug ocr