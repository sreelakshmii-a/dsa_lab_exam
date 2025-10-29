#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char record_type, obje[20], name[10];
    int saddr, proglength, addr, new_start, relocation_factor;
    FILE *f1;

    f1 = fopen("object_program.txt", "r");
    if (!f1) {
        printf("Error in reading file!\n");
        return 1;
    }

    // --- Step 1: Read Header Record ---
    fscanf(f1, "%c", &record_type);
    if (record_type == 'H') {
        fscanf(f1, "%s\t%X\t%X\n", name, &saddr, &proglength);
        printf("Program Name: %s\n", name);
        printf("Original Starting Address: %04X\n", saddr);
        printf("Program Length: %04X\n\n", proglength);

        printf("Enter the new starting address: ");
        scanf("%X", &new_start);

        relocation_factor = new_start - saddr;
        printf("Relocation Factor = %04X\n\n", relocation_factor);
    }

    // --- Step 2: Read next record ---
    fscanf(f1, "%c", &record_type);

    while (record_type != 'E') {
        if (record_type == 'T') {
            fscanf(f1, "%X", &addr);
            printf("\nText Record starts at %04X\n", addr);
            addr = addr + relocation_factor;  // Apply relocation

            while (fscanf(f1, "%s", obje) == 1) {
                if (obje[0] == 'E' || obje[0] == 'T' || obje[0] == 'M') {
                    break;
                }
                printf("%s loaded at relocated address %04X\n", obje, addr);
                addr += 3; // assuming 3-byte instruction
            }
            record_type = obje[0];
            continue;
        }

        // --- Step 3: Handle Modification Records ---
        if (record_type == 'M') {
            int mod_addr, len;
            fscanf(f1, "%X\t%X", &mod_addr, &len);
            printf("Modification Record found at %04X (Length %02X)\n", mod_addr, len);
            printf("→ After relocation: %04X\n", mod_addr + relocation_factor);
        }

        fscanf(f1, "%c", &record_type);
    }

    // --- Step 4: End Record ---
    if (record_type == 'E') {
        fscanf(f1, "%X", &addr);
        printf("\nExecution starts at relocated address: %04X\n", addr + relocation_factor);
    }

    fclose(f1);
    return 0;
}
