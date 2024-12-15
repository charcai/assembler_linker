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
    return 0;
}

int add_to_symbol_table(FILE *input, SymbolTable *table, uint32_t base_text_offset, uint32_t base_data_offset)
{
    return 0;
}