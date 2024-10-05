#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main() {
    FILE *input, *symtab, *intermediate, *optab;
    char label[30], opcode[30], operand[30], optabOpcode[30], optabCode[30];
    int start, locctr, flag;

    input = fopen("input.txt", "r");
    optab = fopen("optab.txt", "r");
    intermediate = fopen("intermediate.txt", "w");
    symtab = fopen("symtab.txt", "w");

    if (!input || !optab || !intermediate || !symtab) {
        perror("Error opening file");
        exit(1);
    }

    fscanf(input, "%s %s %s", label, opcode, operand);

    if (strcmp(opcode, "START") == 0) {
        start = atoi(operand);
        locctr = start;
        fprintf(intermediate, "%d %s %s %s\n", locctr, label, opcode, operand);
        fscanf(input, "%s %s %s", label, opcode, operand);
    } else {
        locctr = 0;
    }

    while (strcmp(opcode, "END") != 0) {
        flag = 0;

        if (strcmp(label, "**") != 0) {
            fprintf(symtab, "%s %d\n", label, locctr);
        }

        rewind(optab);

        while (fscanf(optab, "%s %s", optabOpcode, optabCode) != EOF) {
            if (strcmp(opcode, optabOpcode) == 0) {
                flag = 1;
                locctr += 3;
                break;
            }
        }

        if (strcmp(opcode, "WORD") == 0) {
            locctr += 3;
        } else if (strcmp(opcode, "RESW") == 0) {
            locctr += 3 * atoi(operand);
        } else if (strcmp(opcode, "RESB") == 0) {
            locctr += atoi(operand);
        } else if (strcmp(opcode, "BYTE") == 0) {
            locctr += strlen(operand) - 3;
//eof
        } else if (!flag) {
            locctr += 3;
        }

        fprintf(intermediate, "%d %s %s %s\n", locctr - (flag ? 3 : 0), label, opcode, operand);

        fscanf(input, "%s %s %s", label, opcode, operand);
    }

    fprintf(intermediate, "%d %s %s %s\n", locctr, label, opcode, operand);
    int programlength = locctr - start;
    printf("Program Length: %d\n", programlength);

    fclose(input);
    fclose(symtab);
    fclose(intermediate);
    fclose(optab);
}

