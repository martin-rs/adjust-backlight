#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#define BUFSIZE 6
#define BRIGHTNESS_PATH "/sys/class/backlight/intel_backlight/brightness"
#define MAX_BRIGHTNESS_PATH "/sys/class/backlight/intel_backlight/max_brightness"

void status_check(void);
int get_max(void);

int main(int argc, char **argv) {
	if (argc > 2) {
		printf("Usage: \n\tbr <value>, <status>\n");
		return EXIT_FAILURE;
	} else if (argc == 1 || strcmp(argv[1], "status") == 0)
		status_check();

	FILE *fp = 0;
	char string_current_brightness[BUFSIZE];
	int new = 0, current_brightness = 0, increment = 0, min = 10, max = get_max();

	if ((increment = atoi(argv[1])) == 0) return EXIT_FAILURE;

	if ((fp = fopen(BRIGHTNESS_PATH, "r+")) && fgets(
				string_current_brightness, BUFSIZE, fp)) {
		current_brightness = atoi(string_current_brightness);
		rewind(fp);
		new = current_brightness + increment;
		if (new < min) new = min;
		else if (new > max) new = max;
		fprintf(fp, "%d\n", new);
		fclose(fp);
		fp = NULL;
	} else return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

void status_check(void) {
	FILE *fp = fopen(BRIGHTNESS_PATH, "r");
	if (fp == NULL) {
		fprintf(stderr, "Error opening file.\n");
		exit(EXIT_FAILURE);
	}

	int c = 0;
	while ((c = fgetc(fp)) != EOF) printf("%c", c);

	fclose(fp);
	fp = NULL;
	exit(EXIT_SUCCESS);
}

int get_max(void) {
	FILE *fp = fopen(MAX_BRIGHTNESS_PATH, "r");
	if (fp == NULL) {
		fprintf(stderr, "Error opening file (max_brightness).\n");
		exit(EXIT_FAILURE);
	}

	int max = 0;
	char* string_max = (char *)malloc(sizeof(char) * 6);
	
	fgets(string_max, 6, fp);
	max = atoi(string_max);

	free(string_max);
	fclose(fp);
	fp = NULL;

	return max;
}
