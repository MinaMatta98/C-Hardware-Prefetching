#include <stdio.h>
#include <stdlib.h>

float func_get_sys_prop(FILE *file) {

    int j, total_lines = 3;
    float number, memTotal, memAvailable, memFree;
    char c[60];

    for (j = 0; j < total_lines; j++) {

        fscanf(file, "%s %f %s %f %s %f", c, &number, c, &memTotal, c,
               &memAvailable);

        if (j == 0) {
            memTotal = number;
        } else if (j == 2) {
            memAvailable = number;
        } else {
            memFree = number;
        }
    }

    float mem = (1.0 - (memAvailable / memTotal)) * 100;

    return mem;
}

int func_string_count(FILE *file) {

    int i;

    for (i = 0; !feof(file) && !ferror(file); i++) {
        fgetc(file);
    }

    rewind(file);

    return i;
}

void func_val(float mem) {
    char icon[] = "  ";

    if (mem > 99) {
        fprintf(stdout, "^c#ff3c4b^ %s %.0f%%^r-55,23,51,5^^b#222222^\n", icon,
                mem);
    } else if (mem >= 70) {
        fprintf(stdout, "^c#ff3c4b^ %s %.0f%%^r-46,23,55,5^^b#222222^\n", icon,
                mem);
    } else if (mem > 55) {
        fprintf(stdout, "^c#FFBF00^ %s %.0f%%^r-46,23,55,5^^b#222222^\n", icon,
                mem);
    } else if (mem >= 9.5) {
        fprintf(stdout, "^d^^b#222222^ %s %.0f%%^r-46,23,55,5^^b#222222^\n", icon,
                mem);
    } else {
        fprintf(stdout, "^d^^b#222222^ %s %.0f%%^r-40,23,41,5^^b#222222^\n", icon,
                mem);
    }
}

void func_button_handler(char *button) {

    if (button) {
        if (atoi(button) == 1) {
            system("alacritty -e bpytop -b proc");
        } else if (atoi(button) == 3) {
            system("alacritty -e nvim /home/mina/Downloads/dwmscripts/C/dwmmemory.c");
        }
    }
}

int main(int argc, char *argv[]) {
    FILE *file = fopen("/proc/meminfo", "r");
    char *button = getenv("BLOCK_BUTTON");
    if (!file) {
        return 1;
    }
    int i = func_string_count(file);
    float mem = func_get_sys_prop(file);
    fclose(file);
    func_val(mem);
    func_button_handler(button);
}
