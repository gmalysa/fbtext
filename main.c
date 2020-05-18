#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#include <draw2fb.h>

void usage() {
	printf("\n");
	printf("Usage:\n");
	printf("\n");
	printf("    fbtext [options] \"string to display\"\n");
	printf("\n");
	printf("    where options are:\n");
	printf("       -f [file] - Use [file] as the truetype font (default /usr/share/fonts/ttf/LiberationMono-Regular.ttf)\n");
	printf("       -s [size] - Set font size to [size] px (default 16)\n");
	printf("       -W        - Disable automatic word wrapping (default no)\n");
	printf("       -l [line] - Start writing on line [line] (there are only 128/size lines available) (default 0)\n");
	printf("       -o        - Overdraw mode, do not erase the framebuffer first (default no)\n");
	printf("       -x [off]  - Use an [off] pixel horizontal offset for text (default 0)\n");
	printf("       -t [dest] - Use [dest] as the framebuffer destination (default /dev/fb0)\n");
	printf("       -y [off]  - Use an [off] pixel vertical offset for text (default 0)\n");
	printf("\n");
	exit(1);
}

int main(int argc, char *argv[]) {
	uint8_t data[1024] = {0};
	uint8_t fb[1024] = {0};
	int c;
	const char *target = "/dev/fb0";
	FILE *fp;
	int pixheight = 64;
	int pixwidth = 128;

	struct draw2fb_opts_t config = {
		.font = "/usr/share/fonts/ttf/LiberationMono-Regular.ttf",
		.fontSize = 16,
		.kerning = 0,
		.startline = 0,
		.wrap = 1,
		.xoffset = 0,
		.yoffset = 0,
		.overdraw = 0,
		.W = 128,
		.H = 64,
	};

	while ((c = getopt(argc, argv, "hWof:s:l:x:y:t:")) != -1) {
		switch (c) {
		case 'f':
			config.font = optarg;
			break;
		case 's':
			config.fontSize = atoi(optarg);
			break;
		case 'W':
			config.wrap = 0;
			break;
		case 'l':
			config.startline = atoi(optarg);
			break;
		case 'o':
			config.overdraw = 1;
			break;
		case 'x':
			config.xoffset = atoi(optarg);
			break;
		case 'y':
			config.yoffset = atoi(optarg);
			break;
		case 't':
			target = optarg;
			break;
		case 'h':
			printf("Help\n");
			usage();
			break;
		default:
			printf("Unrecognized option '%c'\n", c);
			usage();
		}
	}

	if (optind >= argc) {
		printf("Input string to display missing!\n");
		usage();
	}

	fp = fopen(target, "r");
	if (!fp) {
		printf("Unable to open %s for reading!\n", target);
		usage();
	}

	fread(data, 1024, 1, fp);
	fclose(fp);

	draw2fb_string(&config, argv[optind], data);

	fp = fopen(target, "w");
	fwrite(data, 1024, 1, fp);
	fclose(fp);

	return 0;
}
