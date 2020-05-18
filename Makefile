
all: fbtext fbdump

fbtext: main.c
	$(CC) $(CFLAGS) `pkg-config --cflags freetype2` main.c -c -o main.o
	$(CC) $(LDFLAGS) main.o -ldraw2fb -lfreetype -o fbtext

fbdump: dump.c
	$(CC) $(CFLAGS) dump.c -c -o dump.o
	$(CC) $(LDFLAGS) dump.o -o fbdump

clean:
	rm -rf main.o dump.o fbtext fbdump
