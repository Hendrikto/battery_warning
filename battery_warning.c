#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/wait.h>

/**
 * Issue a warning if the battery capacity drops too low.
 *
 * @author: Hendrik Werner
 */

#define BATTERY_DIR "/sys/class/power_supply/BAT%d/"
#define STATUS_MAX 16

static char * const nagbar_argv[] = {NAGBAR_PATH, "-m", "Low battery!", NULL};

void print_usage(char const *const name) {
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

char *format_path(char const *const path_template, int const battery_id) {
	size_t const path_size = snprintf(NULL, 0, path_template, battery_id) + 1;
	char *const path = malloc(path_size);
	snprintf(path, path_size, path_template, battery_id);
	return path;
}

FILE *open_file(char const *const path) {
	FILE *const file = fopen(path, "r");
	if (file == NULL) {
		fprintf(stderr, "Failed to open: %s\n", path);
		exit(EXIT_FAILURE);
	}
	return file;
}

void monitoring_loop(
	FILE *const capacity_file
	,FILE *const status_file
	,int const threshold
	,int const timeout
) {
	int capacity;
	char status[STATUS_MAX];
	for (;;) {
		fgets(status, STATUS_MAX, status_file);
		rewind(status_file);
		if (!strcmp(status, "Discharging\n")) {
			fscanf(capacity_file, "%d", &capacity);
			rewind(capacity_file);
			if (capacity < threshold) {
				if (!fork()) {
					execv(nagbar_argv[0], nagbar_argv);
				} else {
					wait(NULL);
				}
			}
		}
		sleep(timeout);
	}
}

int main(int const argc, char const *const *const argv) {
	if (argc != 4) {
		print_usage(argv[0]);
		return EXIT_FAILURE;
	}
	int const battery_id = strtol(argv[1], NULL, 10);
	int const threshold = strtol(argv[2], NULL, 10);
	int const timeout = strtol(argv[3], NULL, 10);
	if (battery_id < 0 || threshold < 1 || timeout < 0) {
		print_usage(argv[0]);
		return EXIT_FAILURE;
	}

	char *const capacity_path = format_path(BATTERY_DIR "capacity", battery_id);
	FILE *const capacity = open_file(capacity_path);
	free(capacity_path);
	setbuf(capacity, NULL);

	char *const status_path = format_path(BATTERY_DIR "status", battery_id);
	FILE *const status = open_file(status_path);
	free(status_path);
	setbuf(status, NULL);

	monitoring_loop(capacity, status, threshold, timeout);

	fclose(capacity);
	fclose(status);
	return EXIT_SUCCESS;
}
