#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void func_button_handler(char *button) {

  if (button) {
    if (atoi(button) == 3) {
      system("alacritty -e nvim /home/mina/Downloads/dwmscripts/C/dwmup.c");
    } else if (atoi(button) == 1) {
            system("sudo alacritty -e bandwhich");
  }
}
}

float func_eval(float result) {
  char unit;
  char *p = &unit;
  p = "kB/s";

  if (result > 99) {
  result = (result / 1024);
  p = "mB/s";
  fprintf(stdout,"^c#6666ea^^b#222222^ ﯴ  %1.1f %s ^b#222222^\n", result, p);
  } else {
  fprintf(stdout,"^c#6666ea^^b#222222^ ﯴ  %1.0f %s ^b#222222^\n", result, p);
  }
  return 0;

}

int main(int argc, char *argv[]) {
  FILE *file = fopen("/sys/class/net/eno1/statistics/tx_bytes", "r");
  float up1, up2;
  char *button;
  fscanf(file, "%f", &up1);
  rewind(file);
  sleep(1);
  fscanf(file, "%f", &up2);
  fclose(file);
  float result = (up2 - up1) / 1024;
  func_eval(result);
  button = getenv("BLOCK_BUTTON");
  func_button_handler(button);
  return 0;
}
