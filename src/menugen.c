/* MenuGen
 *
 * Generate menu definition blocks for RISC OS.
 *
 * (c) Stephen Fryatt, 1996-2010
 * Version 1.00 (7 May 2010)
 *
 * Syntax: MenuGen [<options>]
 *
 * Options -In <file>    - definition file
 *         -Out <file>   - menu file to generate
 *         -Verbose      - display details of parsing
 *         -Messagetrans - create file for MessageTrans_MakeMenus
 *         -Embed        - embed template names for dialogue boxes.
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* We use types from this, but don't try to link to any subroutines! */

#include "oslib/wimp.h"

/* Local source headers. */

#include "data.h"
#include "parse.h"
#include "stack.h"


#define MAX_STACK_SIZE 100

static int verbose_output = 0;
static int embed_dialogue_names = 0;


int main(int argc, char *argv[])
{
	int	param, param_error = 0;

	stack_initialise(MAX_STACK_SIZE);

	printf("MenuGen 2.00 - %s\n", BUILD_DATE);
	printf("Copyright Stephen Fryatt, 2010\n");

	if (argc < 3)
		param_error = 1;

	if (!param_error) {
		for (param = 3; param < argc; param++) {
			if (strcmp(argv[param], "-d") == 0)
				embed_dialogue_names = 1;
			else if (strcmp(argv[param], "-v") == 0)
				verbose_output = 1;
			else
				param_error = 1;
		}
	}

	if (param_error) {
		printf("Usage: menugen <sourcefile> <output> [-d] [-v]\n");
		return 1;
	}

	printf("Starting to parse menu definition file...\n");
	if (parse_process_file(argv[1], verbose_output)) {
		printf("Errors in source file: terminating.\n");
		return 1;
	}

	printf("Collating menu data...\n");
	data_collate_structures(embed_dialogue_names, verbose_output);

	if (verbose_output) {
		printf("Printing structure report...\n");
		data_print_structure_report();
	}

	printf("Writing menu file...\n");
	data_write_standard_menu_file(argv[2]);

	return 0;
}