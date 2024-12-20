/*****************************************************************
 * BUAA Fall 2023 Fundamentals of Computer Hardware
 * Project4 Assembler and Linker
 *****************************************************************
 * my_linker_utils.c
 * Linker Submission
 *****************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "lib_linker/linker_utils.h"
#include "my_linker_utils.h"

/*
 * You should implement functions below.
 * Detailed information is in my_assembler_utils.h.
 */

int inst_needs_relocation(SymbolTable *reltbl, uint32_t offset)
{
    const char *symbol = get_symbol_for_addr(reltbl, offset);
    return symbol != NULL ? 1 : 0;
}

int add_to_symbol_table(FILE *input, SymbolTable *table, uint32_t base_text_offset, uint32_t base_data_offset) {
    char line[256];
    while (fgets(line, sizeof(line), input)) {
        if (line[0] == '\n') {
            break;
        }
        char *number_str = strtok(line, "\t");
        char *symbol = strtok(NULL, "\n");

        if (number_str == NULL || symbol == NULL) {
            return -1;
        }

        uint32_t offset = (symbol[0] == '%') ? base_data_offset : base_text_offset;
        if (symbol[0] == '%') {
            symbol++;
        }

        if (add_to_table(table, symbol, offset + atoi(number_str)) == -1) {
            return -1;
        }
    }
    return 0;
}