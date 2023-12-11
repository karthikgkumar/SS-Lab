#include <stdio.h>
#include <stdlib.h>

FILE *object;
int staddr, prevaddr, length, record_len, prog_len, start_addr;
char record_type, text_record[100], progr_name[7];
int main() {
    object = fopen("./object.txt", "r");

    fscanf(object, " %c %6s %X %X", &record_type, progr_name, &start_addr,
           &prog_len);
    if (record_type != 'H')
    {
        printf("Invalid object file\n");
        fclose(object);
        exit(0);
    }
    fscanf(object, " %c %X %X %s", &record_type, &staddr, &record_len,
           text_record);

    int memory[1000];
    int z = 0;
    int mem_loc = staddr;

    while (record_type != 'E') {
        prevaddr = staddr;

        for (int i = 0; i < record_len; i += 2) {
            // Convert ASCII characters representing hexadecimal to integers
            int hex_value = 0;
            sscanf(&text_record[i], "%2X", &hex_value);
            memory[z] = hex_value; // Store the converted hexadecimal value
            z++;
            mem_loc++;
        }

        // Move to the next text record
        prevaddr += record_len;
        fscanf(object, " %c %X %X %s", &record_type, &staddr, &record_len, text_record);

        // Fill memory with 'X's for any gap in the address space
        while (prevaddr < staddr) {
            memory[z] = 'X';
            z++;
            prevaddr++;
        }
    }

    // Print memory contents
    printf("%X ", staddr);
    for (int i = staddr, j = 0, count = 0; j < z; i++, j++) {
        if (count >= 16) {
            printf("\n");
            printf("%X ", i);
            count = 0;
        }
        if (count % 4 == 0) {
            printf(" ");
        }
        printf("%02X", memory[j]); // Print the stored hexadecimal value as characters
        count++;
    }

    fclose(object);
    return 0;
}
