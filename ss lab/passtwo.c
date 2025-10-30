#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *fin, *fsym, *fopt, *fout;
    char label[20], opcode[20], operand[20];
    char mnem[20], code[10];
    char symb[20];
    int addr;

    fin = fopen("intermediate.txt", "r"); // input from pass one
    fsym = fopen("symtab.txt", "r");      // symbol table
    fopt = fopen("optab.txt", "r");       // opcode table
    fout = fopen("objectcode.txt", "w");  // output file

    if (!fin || !fsym || !fopt || !fout) {
        printf("Error opening one of the files.\n");
        return 1;
    }

    // Read first line (START)
    fscanf(fin, "%s %s %s", label, opcode, operand);
    if (strcmp(opcode, "START") == 0) {
        fprintf(fout, "H^%s^00%s\n", label, operand);
        fscanf(fin, "%s %s %s", label, opcode, operand);
    }

    fprintf(fout, "T^"); // start text record

    while (strcmp(opcode, "END") != 0) {
        int flag = 0; // to check if opcode found

        // search OPTAB
        rewind(fopt);
        while (fscanf(fopt, "%s %s", mnem, code) != EOF) {
            if (strcmp(opcode, mnem) == 0) {
                flag = 1;
                break;
            }
        }

        if (flag == 1) {
            // search SYMTAB for operand
            rewind(fsym);
            while (fscanf(fsym, "%s %d", symb, &addr) != EOF) {
                if (strcmp(operand, symb) == 0) {
                    fprintf(fout, "%s%04d ", code, addr);
                    break;
                }
            }
        }
        else if (strcmp(opcode, "WORD") == 0) {
            fprintf(fout, "%06d ", atoi(operand));
        }
        else if (strcmp(opcode, "BYTE") == 0) {
            if (operand[0] == 'C') { // convert characters to hex
                for (int i = 2; operand[i] != '\''; i++) {
                    fprintf(fout, "%X", operand[i]);
                }
                fprintf(fout, " ");
            }
        }
        else if (strcmp(opcode, "RESW") == 0 || strcmp(opcode, "RESB") == 0) {
            fprintf(fout, "- "); // no object code for reserved
        }

        fscanf(fin, "%s %s %s", label, opcode, operand);
    }

    fprintf(fout, "\nE^00%s\n", operand);
    printf("Pass Two completed. Object program generated.\n");

    fclose(fin);
    fclose(fsym);
    fclose(fopt);
    fclose(fout);
    return 0;
}
