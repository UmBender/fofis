#include "fofis.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

  struct Csv *csv = bopen("Pudim", (union CsvConfig){.config = 1});
  csv->config.config |= INDEX | COLUMNS | MULTITHREADING;
  debug_config(csv);
  printf("%ld\n", sizeof(union CsvConfig));
  printf("%ld\n", sizeof(uint8_t));
  printf("%ld\n", sizeof(struct Cell));
  return 0;
}
