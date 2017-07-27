#include <stdio.h>
#include <stdlib.h>

/**
 * Issue a warning if the battery capacity drops too low.
 *
 * @author: Hendrik Werner
 */

void print_usage(char *name) {
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

int main(int argc, char **argv) {
	return EXIT_SUCCESS;
}
