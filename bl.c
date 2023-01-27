#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFSIZE 8
#define BRIGHTNESS_PATH "/sys/class/backlight/intel_backlight/brightness"
#define MAX_BRIGHTNESS_PATH "/sys/class/backlight/intel_backlight/max_brightness"
#define PROGNAME "bl"

void status_check(void);
unsigned long get_max(void);

int main(int argc, char **argv) {
	if (argc > 2) {
		fprintf(stderr, "Usage: \n\t%s [(+/-) value, min, max, status]\n", 
				PROGNAME);
		return EXIT_FAILURE;
	} else if (argc == 1 || strcmp(argv[1], "status") == 0)
		status_check();

	FILE *fp = 0;
	char string_current_brightness[BUFSIZE];
	unsigned long new = 0, current_brightness = 0, increment = 0, min = 10, 
		      max = get_max(), mid = max/2;

	if (!(strcmp(argv[1], "max")))
		increment = max;
	else if (!(strcmp(argv[1], "min")))
		increment = min;
	else if (!(strcmp(argv[1], "mid")))
		increment = mid;
	else
		if ((increment = atoi(argv[1])) == 0) 
			return EXIT_FAILURE;

	if ((fp = fopen(BRIGHTNESS_PATH, "r+")) && 
	     fgets(string_current_brightness, BUFSIZE, fp)) {
		current_brightness = atoi(string_current_brightness);
		rewind(fp);
		if (argv[1][0] == '+' || argv[1][0] == '-')
			new = current_brightness + increment;
		else 
			new = increment;
		if (new < min) 
			new = min;
		else if (new > max) 
			new = max;
		fprintf(fp, "%ld\n", new);
		fclose(fp);
		fp = NULL;
	} else {
		fprintf(stderr, "Error opening brightness file or extracting the contents of it.\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void status_check(void) {
	FILE *fp = fopen(BRIGHTNESS_PATH, "r");
	if (fp == NULL) {
		fprintf(stderr, "Error opening file.\n");
		exit(EXIT_FAILURE);
	}

	int c;
	while ((c = fgetc(fp)) != EOF) 
		printf("%c", c);

	fclose(fp);
	fp = NULL;
	exit(EXIT_SUCCESS);
}

unsigned long get_max(void) {
	FILE *fp = fopen(MAX_BRIGHTNESS_PATH, "r");
	if (fp == NULL) {
		fprintf(stderr, "Error opening file (max_brightness).\n");
		exit(EXIT_FAILURE);
	}

	unsigned long max = 0;
	char *string_max = (char *)malloc(sizeof(char) * 8);
	if (string_max == NULL) {
		fprintf(stderr, "Error allocating memory.\n");
		exit(EXIT_FAILURE);
	}
	
	fgets(string_max, 8, fp);
	max = atoi(string_max);

	free(string_max);
	string_max = NULL;
	fclose(fp);
	fp = NULL;

	return max;
}
