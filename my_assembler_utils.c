/*****************************************************************
 * BUAA Fall 2023 Fundamentals of Computer Hardware
 * Project4 Assembler and Linker
 *****************************************************************
 * my_assembler_utils.c
 * Assembler Submission
 *****************************************************************/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "lib/translate_utils.h"
#include "lib_assembler/assembler_utils.h"
#include "my_assembler_utils.h"

/*
 * You should implement functions below.
 * Detailed information is in my_assembler_utils.h.
 */

int read_data_segment(FILE *input, SymbolTable *symtbl) {
    char lineInput[ASSEMBLER_BUF_SIZE];
    unsigned long long byteCount = 0;
    while (fgets(lineInput, ASSEMBLER_BUF_SIZE, input)) {
        if (lineInput[0] == '\n' || lineInput[0] == '\r') {
            break;
        }
        skip_comment(lineInput);
        char *token = strtok(lineInput, ASSEMBLER_IGNORE_CHARS);
        if (token == NULL) {
            continue;
        }

        if (strcmp(token, ".data") == 0) {
            continue;
        }

        char *label = token;
        size_t len = strlen(label);
        if (label[len - 1] == ':') {
            label[len - 1] = '\0'; // 移除冒号
        }
        token = strtok(NULL, ASSEMBLER_IGNORE_CHARS);
        if (token == NULL || strcmp(token, ".space") != 0) {
            printf("Invalid .data directive.\n");
            return -1;
        }

        char *size_str = strtok(NULL, ASSEMBLER_IGNORE_CHARS);
        if (size_str == NULL) {
            printf("Invalid .data directive.\n");
            return -1;
        }

        int size = atoi(size_str);
        if (size <= 0) {
            printf("Invalid .data directive: size must be positive\n");
            return -1;
        }

        char prefixed_label[ASSEMBLER_BUF_SIZE];
        snprintf(prefixed_label, sizeof(prefixed_label), "%%%s", label);

        if (add_to_table(symtbl, prefixed_label, byteCount) == -1)
        {
            printf("Error adding label to symbol table: %s\n", prefixed_label);
            return -1;
        }
        byteCount += size;
    }
    return byteCount;
}

unsigned write_li(FILE *output, const char *name, char **args, int num_args) {
    if(num_args != 2) {
        return -1;
    }
    int imm = atoi(args[1]);
    if (imm >= -32768 && imm <= 32767) {
        fprintf(output, "addiu %s $0 %d\n", args[0], imm);
        return 1;
    }
    else {
        int upper = (imm >> 16) & 0xFFFF;
        int lower = imm & 0xFFFF;
        fprintf(output, "lui $at %d\n", upper);
        fprintf(output, "ori %s $at %d\n", args[0], lower);
        return 2;
    }
}

int write_rtype(uint8_t funct, FILE *output, char **args, size_t num_args) {
    if (num_args != 3) {
        return -1;
    }
    int rd = translate_reg(args[0]);
    int rs = translate_reg(args[1]);
    int rt = translate_reg(args[2]);

    uint32_t instruction = (rs << 21) | (rt << 16) | (rd << 11) | funct;
    fprintf(output, "%08x\n", instruction);
    return 0;
}