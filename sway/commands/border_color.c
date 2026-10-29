#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "sway/commands.h"
#include "sway/config.h"
#include "sway/tree/container.h"
#include "util.h"

struct cmd_results *cmd_border_color(int argc, char **argv) {
	struct cmd_results *error = NULL;
	if ((error = checkarg(argc, "border_color", EXPECTED_EQUAL_TO, 1))) {
		return error;
	}
	struct sway_container *container = config->handler_context.container;
	if (!container) {
		return cmd_results_new(CMD_INVALID,
				"Only valid containers can have a border_color");
	}
	bool reset = strcasecmp(argv[0], "none") == 0;
	uint32_t color;
	if (!reset && !parse_color(argv[0], &color)) {
		return cmd_results_new(CMD_INVALID,
				"Invalid color %s, expected #rrggbb, #rrggbbaa or none", argv[0]);
	}
	free(container->border_color);
	container->border_color = reset ? NULL : strdup(argv[0]);
	container_update(container);
	return cmd_results_new(CMD_SUCCESS, NULL);
}
