#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float func_sum(float a, float b, float c, float idle) {
  float sum = a + b + c + idle;
  return sum;
}

void func_val(float final) {
  char icon[] = " ^b#222222^  ";

  if (final >= 99.5) {
    fprintf(stdout,
            "^b#222222^ ^c#ff3c4b^%s %.0f%%^b#222222^ "
            "^c#ff3c4b^^r-54,23,51,5^^b#222222^\n",
            icon, final);
  } else if (final > 60) {
    fprintf(stdout,
            "^b#222222^ ^c#ff3c4b^%s %.0f%%^b#222222^ "
            "^c#ff3c4b^^r-49,23,46,5^^b#222222^\n",
            icon, final);
  } else if (final > 30) {
    fprintf(stdout,
            "^b#222222^ ^c#FFBF00^%s %.0f%%^b#222222^ "
            "^c#FFBF00^^r-49,23,46,5^^b#222222^\n",
            icon, final);
  } else if (final >= 9.5) {
    fprintf(
        stdout,
        "^b#222222^ %s %.0f%%^b#222222^ ^c#51afef^^r-49,23,46,5^^b#222222^\n",
        icon, final);
  } else {
    fprintf(stdout, "^b#222222^ %s %.0f%%^b#222222^ ^c#51afef^^r-42,23,39,5^\n",
            icon, final);
  }
}

void func_wait(int msec) {
  struct timespec ts;
  ts.tv_sec = msec / 1000;
  ts.tv_nsec = (msec % 1000) * 1000000;
  nanosleep(&ts, &ts);
}

void func_button_handler(char *button) {

  if (button) {
    if (atoi(button) == 1) {
      system("alacritty -e htop");
    } else if (atoi(button) == 3) {
      system("alacritty -e nvim /home/mina/Downloads/dwmscripts/C/dwmcpu.c");
    }
  }
}
int main(int argc, char *argv[]) {
  FILE *file = fopen("/proc/stat", "r");
  char *button = getenv("BLOCK_BUTTON"), cpu;
  float a, b, c, idle, rest;

  fscanf(file, "%s %f %f %f %f %f", &cpu, &a, &b, &c, &idle, &rest);
  float prevIdle = idle;
  float prevTotal = func_sum(a, b, c, idle);

  func_wait(300);

  rewind(file);
  fscanf(file, "%s %f %f %f %f %f", &cpu, &a, &b, &c, &idle, &rest);
  fclose(file);

  float total = func_sum(a, b, c, idle);
  float final = abs((int)(((total - prevTotal) - (idle - prevIdle)) * 100 /
                          (total - prevTotal)));

  if (!final) {
    final = 0;
  }
  func_val(final);
  func_button_handler(button);
}
