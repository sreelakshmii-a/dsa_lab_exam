#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp1, *fp2, *fp3;
    char label[10], opcode[10], operand[10];
    int locctr, start_addr;
    char line[50];

    fp1 = fopen("input.asm", "r");         // Input source file
    fp2 = fopen("symtab.txt", "w");        // Symbol table file
    fp3 = fopen("intermediate.txt", "w");  // Intermediate file

    if (fp1 == NULL) {
        printf("Error: Cannot open input file.\n");
        exit(1);
    }

    fscanf(fp1, "%s %s %s", label, opcode, operand);

    // Check for START
    if (strcmp(opcode, "START") == 0) {
        start_addr = atoi(operand);
        locctr = start_addr;
        fprintf(fp3, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);
        fscanf(fp1, "%s %s %s", label, opcode, operand);
    } else {
        locctr = 0;
    }

    // Process each line until END
    while (strcmp(opcode, "END") != 0) {
        fprintf(fp3, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);

        // If there is a label, add it to symbol table
        if (strcmp(label, "**") != 0) {
            fprintf(fp2, "%s\t%d\n", label, locctr);
        }

        // Update LOCCTR based on opcode
        if (strcmp(opcode, "WORD") == 0)
            locctr += 3;
        else if (strcmp(opcode, "RESW") == 0)
            locctr += 3 * atoi(operand);
        else if (strcmp(opcode, "RESB") == 0)
            locctr += atoi(operand);
        else if (strcmp(opcode, "BYTE") == 0)
            locctr += strlen(operand) - 3;  // Example: C'EOF'
        else
            locctr += 3; // Default size for instructions

        fscanf(fp1, "%s %s %s", label, opcode, operand);
    }

    fprintf(fp3, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);

    printf("Pass 1 completed successfully.\n");
    printf("Symbol table written to symtab.txt\n");
    printf("Intermediate file written to intermediate.txt\n");

    printf("Program length = %d\n", locctr - start_addr);

    return 0;
}
