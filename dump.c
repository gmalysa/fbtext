#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char **argv) {
	uint8_t data[1024];
	uint8_t fb[1024];
	int i, j, k;
	FILE *fp;
	const char *target = "/dev/fb0";
	int W = 16;
	int H = 8;
	int pixheight = 64;
	int pixwidth = 128;

	fp = fopen(target, "r");
	if (!fp) {
		printf("Unable to open %s for reading!\n", target);
		exit(1);
	}

	fread(data, 1024, 1, fp);
	fclose(fp);

	for (i = 0; i < (pixheight / 8); i++) {
        for (j = 0; j < pixwidth; j++) {
            uint32_t array_idx = i * pixwidth + j;
            fb[array_idx] = 0;
            for (k = 0; k < 8; k++) {
                uint32_t page_length = pixwidth * i;
                uint32_t index = page_length + (pixwidth * k + j) / 8;
                uint8_t byte = *(data+ index);
                uint8_t bit = byte & (1 << (j % 8));
                bit = bit >> (j % 8);
                fb[array_idx] |= bit << k;
            }
        }
    }

	for (i = 0; i < H; ++i) {
		for (k = 0; k < 8; ++k) {
			for (j = 0; j < W*8; ++j) {
				int idx = (i * 8 * W) + j;
				if ((fb[idx] & (1 << k)))
					printf(".");
				else
					printf(" ");
			}
			printf("\n");
		}
	}

	return 0;
}
