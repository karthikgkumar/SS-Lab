#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

FILE *input, *optab, *symtab, *output, *prog_len;
int stdadr, length;
int locctr;
char label[20], opcode[20], operand[20];

int main() {
    input = fopen("./input.txt", "r");
    symtab = fopen("./symtab.txt", "w");
    optab = fopen("./optab.txt", "r");
    output = fopen("./intermediate.txt", "w");
    prog_len = fopen("./length.txt", "w");

    fscanf(input, "%s %s %X", label, opcode, &stdadr);
    
    if (strcmp(opcode, "START") == 0) {
        locctr = stdadr;
        fprintf(output, "\t%s\t%s\t%X\n", label, opcode, stdadr);
        printf("\t%s\t%s\t%d\n", label, opcode, stdadr);
    } else {
        locctr = 0;
    }

    bool end_found = false; // Flag to check if "END" opcode is encountered

    while (fscanf(input, "%s %s %s", label, opcode, operand) != EOF) {
        fprintf(output, "%X\t%s\t%s\t%s\n", locctr, label, opcode, operand);
        printf("%X\t%s\t%s\t%s\n", locctr, label, opcode, operand);

        if (strcmp(label, "-") != 0) {
            fprintf(symtab, "%s\t%X\n", label, locctr);
        }

        if (strcmp(opcode, "END") == 0) {
            end_found = true;
            printf("Completed\n");
            break;
        } else if (strcmp(opcode, "WORD") == 0) {
            locctr += 3;
        } else if (strcmp(opcode, "RESW") == 0) {
            locctr += (3 * atoi(operand));
        } else if (strcmp(opcode, "RESB") == 0) {
            locctr += atoi(operand);
        } else if (strcmp(opcode, "BYTE") == 0) {
            locctr += 1;
        } else {
            bool opcode_found = false;
            char temp[20];
            rewind(optab);
            while (fscanf(optab, "%s %X", temp, &length) != EOF) {
                if (strcmp(temp, opcode) == 0) {
                    locctr += 3;
                    opcode_found = true;
                    break;
                }
            }
        }
    }

    if (end_found) {
        fprintf(prog_len, "Length of the program: %X", locctr - stdadr);
        printf("Length of the program: %X\n", locctr - stdadr);
    }

    fclose(input);
    fclose(symtab);
    fclose(optab);
    fclose(output);
    fclose(prog_len);

    return 0;
}
