#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_TXT_REC_LEN 30
int locctr, prevaddr, stdadr, length;
char label[20], opcode[20], operand[20];
FILE *optab, *symtab, *intermediate, *object, *prog_len;
int main()
{
    optab = fopen("../Pass_one/optab.txt", "r");
    symtab = fopen("../Pass_one/symtab.txt", "r");
    intermediate = fopen("../Pass_one/intermediate.txt", "r");
    object = fopen("./object.txt", "w");
    prog_len = fopen("../Pass_one/length.txt", "r");
    fscanf(intermediate, "%s %s %X", label, opcode, &stdadr);
    fscanf(prog_len, "%X", &length);
    printf("\t%s\t%s\t%X\n", label, opcode, stdadr);
    fprintf(object, "H %s %06X %06X\n", label, stdadr, length);
    fscanf(intermediate, "%X %s %s %s", &locctr, label, opcode, operand);
    prevaddr = locctr;
    char text_record[100];
    strcpy(text_record, "");
    int txt_rec_len = 0;
    while (strcmp(opcode, "END") != 0)
    {
        printf("%X\t%s\t%s\t%s\t", locctr, label, opcode, operand);
        if (txt_rec_len >= MAX_TXT_REC_LEN)
        {
            char overflow[100];
            for (int i = 30; i < txt_rec_len; i++)
            {
                overflow[i - 30] = text_record[i];
            }
            overflow[txt_rec_len - 30] = '\0';
            text_record[30] = '\0';
            fprintf(object, "T %06X %02X %s\n", prevaddr, MAX_TXT_REC_LEN,
                    text_record);
            prevaddr += MAX_TXT_REC_LEN;
            txt_rec_len -= 30;
            strcpy(text_record, overflow);
            txt_rec_len = strlen(overflow);
        }
        if (strcmp(opcode, "RESW") == 0 || strcmp(opcode, "RESB") == 0)
        {
            // do nothing
        }
        else if (strcmp(opcode, "BYTE") == 0)
        {
            if (operand[0] == 'C')
            {
                for (int i = 2; i < strlen(operand) - 1; i++)
                {
                    printf("%02X", operand[i]);
                    char hex_byte[3];
                    sprintf(hex_byte, "%02X", operand[i]);
                    strcat(text_record, hex_byte);
                    txt_rec_len += 2;
                }
            }
            else if (operand[0] == 'X')
            {
                for (int i = 2; i < strlen(operand) - 1; i++)
                {
                    printf("%c", operand[i]);
                    strncat(text_record, &operand[i], 1);
                    txt_rec_len += 1;
                }
            }
        }
        else if (strcmp(opcode, "WORD") == 0)
        {
            int word_value;
            sscanf(operand, "%d", &word_value);
            char hex_word[7];
            printf("%06X", word_value);
            sprintf(hex_word, "%06X", word_value);
            strcat(text_record, hex_word);
            txt_rec_len += 6;
        }
        else
        {
            bool opcode_found = false;
            char temp[20], machinecode[20];
            rewind(optab);

            while (fscanf(optab, "%s %s", temp, machinecode) != EOF)
            {
                if (strcmp(temp, opcode) == 0)
                {
                    printf("%s", machinecode);
                    strcat(text_record, machinecode);
                    opcode_found = true;
                    txt_rec_len += 3;
                    break; // Moved break statement to exit loop after finding opcode
                }
            }
           
            if (!opcode_found)
            {
                printf("Error: Invalid opcode %s\n", opcode);
                fclose(symtab);
                fclose(optab);
                exit(0);
            }
            if (strcmp(operand, "-") != 0)
            {
                rewind(symtab);
                char *symaddr = malloc(20 * sizeof(char));
                while (fscanf(symtab, "%s %s", temp, symaddr) != EOF)
                {
                    if (strcmp(temp, operand) == 0)
                    {
                        break;
                    }
                }
                printf("%s", symaddr);
                strcat(text_record, symaddr);
                txt_rec_len += 4;
                free(symaddr);
            }
        }
        printf("\n");
        fscanf(intermediate, "%X %s %s %s", &locctr, label, opcode,
               operand);
    }
    fprintf(object, "T %06X %02d %s\n", prevaddr, txt_rec_len,
            text_record);

    fprintf(object, "E %06X", stdadr);
    fclose(symtab);
    fclose(intermediate);
    fclose(object);
    return 0;
}
