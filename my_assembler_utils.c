/*****************************************************************
 * BUAA Fall 2023 Fundamentals of Computer Hardware
 * Project4 Assembler and Linker
 *****************************************************************
 * my_assembler_utils.c
 * Assembler Submission
 *****************************************************************/

#include <string.h>
#include <stdlib.h>

#include "lib/translate_utils.h"
#include "lib_assembler/assembler_utils.h"
#include "my_assembler_utils.h"

/*
 * You should implement functions below.
 * Detailed information is in my_assembler_utils.h.
 */

int read_data_segment(FILE *input, SymbolTable *symtbl)
{
    return 0;
}

unsigned write_li(FILE *output, const char *name, char **args, int num_args)
{
    return 0;
}

int write_rtype(uint8_t funct, FILE *output, char **args, size_t num_args)
{
    return 0;
}