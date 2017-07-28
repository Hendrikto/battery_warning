#include <stdio.h>
#include <stdlib.h>

/**
 * Issue a warning if the battery capacity drops too low.
 *
 * @author: Hendrik Werner
 */

#define BATTERY_DIR "/sys/class/power_supply/BAT%d/"

void print_usage(char const *name) {
	printf(
		"Usage: %1$s <battery_id> <threshold> <timeout>\n"
		"\tbattery_id >= 0\n"
		"\tthreshold > 0\n"
		"\ttimeout >= 0\n"
		"\n"
		"Example: %1$s 0 15 300\n",
		name
	);
}

char *format_path(char const *path_template, int const battery_id) {
	size_t path_size = snprintf(NULL, 0, path_template, battery_id) + 1;
	char *path = malloc(path_size);
	snprintf(path, path_size, path_template, battery_id);
	return path;
}

FILE *open_file(char const *path) {
	FILE *file = fopen(path, "r");
	if (file == NULL) {
		fprintf(stderr, "Failed to open: %s\n", path);
		exit(EXIT_FAILURE);
	}
	return file;
}

int main(int argc, char **argv) {
	if (argc != 4) {
		print_usage(argv[0]);
		return EXIT_FAILURE;
	}
	int const battery_id = strtol(argv[1], NULL, 10);
	int const threshold = strtol(argv[2], NULL, 10);
	int const timeout = strtol(argv[3], NULL, 10);
	if (threshold < 1 || timeout < 0) {
		print_usage(argv[0]);
		return EXIT_FAILURE;
	}

	char *capacity_path = format_path(BATTERY_DIR "capacity", battery_id);
	FILE *capacity = open_file(capacity_path);
	setbuf(capacity, NULL);
	free(capacity_path);

	char *status_path = format_path(BATTERY_DIR "status", battery_id);
	FILE *status = open_file(status_path);
	setbuf(status, NULL);
	free(status_path);

	fclose(capacity);
	fclose(status);
	return EXIT_SUCCESS;
}
