/* Copyright 2015, Stephen Fryatt (info@stevefryatt.org.uk)
 *
 * This file is part of MenuTest:
 *
 *   http://www.stevefryatt.org.uk/software/
 *
 * Licensed under the EUPL, Version 1.1 only (the "Licence");
 * You may not use this work except in compliance with the
 * Licence.
 *
 * You may obtain a copy of the Licence at:
 *
 *   http://joinup.ec.europa.eu/software/page/eupl
 *
 * Unless required by applicable law or agreed to in
 * writing, software distributed under the Licence is
 * distributed on an "AS IS" basis, WITHOUT WARRANTIES
 * OR CONDITIONS OF ANY KIND, either express or implied.
 *
 * See the Licence for the specific language governing
 * permissions and limitations under the Licence.
 */

/* MenuGen
 *
 * Generate menu definition blocks for RISC OS in a cross-compilation
 * environment.
 *
 * Syntax: MenuGen [<options>]
 *
 * Options -d  - Embed dialogue box names into the output
 *         -v  - Produce verbose output
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <ctype.h>

/* We use types from this, but don't try to link to any subroutines! */

// #include "oslib/wimp.h"

/* Local source headers. */

#include "file.h"
#include "parse.h"


#define MAX_STACK_SIZE 100

int main(int argc, char *argv[])
{
	bool	param_error = false;
	int8_t	*data;
	size_t	length;

	printf("MenuTest %s - %s\n", BUILD_VERSION, BUILD_DATE);
	printf("Copyright Stephen Fryatt, 2001-%s\n", BUILD_DATE + 7);

	if (argc < 2)
		param_error = true;

/*	if (!param_error) {
		for (param = 3; param < argc; param++) {
			if (strcmp(argv[param], "-d") == 0)
				embed_dialogue_names = true;
			else if (strcmp(argv[param], "-m") == 0)
				embed_menu_names = true;
			else if (strcmp(argv[param], "-v") == 0)
				verbose_output = true;
			else
				param_error = true;
		}
	} */

	if (param_error) {
		printf("Usage: menutest <sourcefile>\n");
		return 1;
	}

	data = file_load(argv[1], &length);

	if (data == NULL) {
		printf("Failed to load file\n");
		return 1;
	}

	parse_process(data, length);

	return 0;
}

