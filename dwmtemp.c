#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void func_val(int temp) {
    char icon[] = "   ";

    if (temp > 99) {
        fprintf(stdout, "  ^c#ff3c4b^^b#222222^%s %d 糖 ^r-65,23,65,5^^b#222222^\n",
                icon, temp);
    } else if (temp > 75) {
        fprintf(stdout, "  ^c#ff3c4b^^b#222222^%s %d 糖 ^r-55,23,55,5^^b#222222^\n",
                icon, temp);
    } else if (temp > 55) {
        fprintf(stdout, "  ^c#FFBF00^^b#222222^%s %d 糖 ^r-55,23,55,5^^b#222222^\n",
                icon, temp);
    } else if (temp >= 9.5) {
        fprintf(
            stdout,
            "  ^c#6666ea^^b#222222^%s %d 糖 ^c#51afef^^r-55,23,55,5^^b#222222^\n",
            icon, temp);
    } else {
        fprintf(
            stdout,
            "  ^c#6666ea^^b#222222^%s%d^ 糖 ^c#51afef^^r-35,23,35,5^^b#222222^\n",
            icon, temp);
    }
}

void func_button_handler(char *button) {

    if (button) {
        if (atoi(button) == 1) {
            system("alacritty -e zsh -c 'watch sensors'");
        } else if (atoi(button) == 3) {
            system("alacritty -e nvim /home/mina/Downloads/dwmscripts/C/dwmtemp.c");
        }
    }
}

int main() {

    int i;
    char temp[90];

    int prevNum = 0;
    int num;
    int finalNum;
    DIR *directory = opendir("/sys/devices/platform/coretemp.0/hwmon/hwmon4/");
    char targetDir[90];

    if (!directory) {
        strcpy(targetDir, "/sys/devices/platform/coretemp.0/hwmon/hwmon5/");
    } else {
        strcpy(targetDir, "/sys/devices/platform/coretemp.0/hwmon/hwmon4/");
    }

    char targetDes[90];

    strcpy(targetDes, targetDir);

    for (i = 0; i < 6; i++) {
        strcpy(targetDir, targetDes);
        switch (i) {
        case 0:
            strcpy(temp, strcat(targetDir, "temp2_input"));
            break;
        case 1:
            strcpy(temp, strcat(targetDir, "temp3_input"));
            break;
        case 2:
            strcpy(temp, strcat(targetDir, "temp4_input"));
            break;
        case 3:
            strcpy(temp, strcat(targetDir, "temp5_input"));
            break;
        case 4:
            strcpy(temp, strcat(targetDir, "temp6_input"));
            break;
        case 5:
            strcpy(temp, strcat(targetDir, "temp7_input"));
            break;
        };

        memset(targetDir, '\0', sizeof(targetDir));
        FILE *file = fopen(temp, "r");

        if (!file) {
            printf("error");
        }

        fscanf(file, "%d", &num);
        prevNum = prevNum + num;
        fclose(file);
    }

    closedir(directory);
    finalNum = prevNum / 6000;

    char *button = getenv("BLOCK_BUTTON");

    /* float temp = func_get_sys_prop(file); */
    func_val(finalNum);
    func_button_handler(button);
}
