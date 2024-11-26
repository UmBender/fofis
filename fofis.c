#include "fofis.h"

void alloc_grid(struct Cell ***grid, size_t *lines, size_t *columns,
                char *file_name) {
  *lines = 0;
  *columns = 1;
  char buffer[BUFF_SIZE] = "";
  FILE *f = fopen(file_name, "r");
  if (f == NULL) {
    perror("Error, file there is not exists\n");
    return;
  }

  fgets(buffer, BUFF_SIZE, f);
  for (size_t i = 0; buffer[i]; ++i) {
    if (buffer[i] == ',') {
      (*columns)++;
    }
  }

  (*lines)++;
  while (fgets(buffer, 131072, f)) {
    (*lines)++;
  }
  fclose(f);
  *grid = (struct Cell **)malloc(sizeof(struct Cell *) * (*lines));
  for (int i = 0; i < *lines; i++) {
    (*grid)[i] = (struct Cell *)malloc(sizeof(struct Cell) * (*columns));
  }
}
void construct(struct Csv *csv, char *file_name) {
  struct Cell **grid;
  size_t lines = 0;
  size_t columns = 0;
  alloc_grid(&grid, &lines, &columns, file_name);
  FILE *f = fopen(file_name, "r");
  for (int i = 0; i < lines; i++) {
    grid[i] = (struct Cell *)malloc(sizeof(struct Cell) * columns);
  }
}
struct Csv *bopen(const char *path, union CsvConfig build) {
  struct Csv *csv = (struct Csv *)malloc(sizeof(struct Csv));
  (*csv) = (struct Csv){.lines = 0,
                        .columns = 0,
                        .config = (union CsvConfig){
                            .internal = {.indexes = 0,
                                         .named_columns = 0,
                                         .semicolon = 0,
                                         .treat_missing_values = 0,
                                         .multithreading = 0},
                        }};
  return csv;
}

struct Csv *iopen(const char *path, int8_t build) {
  return bopen(path, (union CsvConfig){
                         .config = build,
                     });
}

void debug_config(struct Csv *csv) {
  if (csv == NULL) {
    perror("CSV not created\n");
    return;
  }
  union CsvConfig config = csv->config;
  printf("INDEXES: ");
  if (config.internal.indexes) {
    printf("TRUE\n");
  } else {
    printf("FALSE\n");
  }
  printf("NAMED COLUMNS: ");
  if (config.internal.named_columns) {
    printf("TRUE\n");
  } else {
    printf("FALSE\n");
  }
  printf("SEMICOLON: ");
  if (config.internal.semicolon) {
    printf("TRUE\n");
  } else {
    printf("FALSE\n");
  }
  printf("TREAT MISSING VALUES: ");
  if (config.internal.treat_missing_values) {
    printf("TRUE\n");
  } else {
    printf("FALSE\n");
  }
  printf("MULTITHREADING: ");
  if (config.internal.multithreading) {
    printf("TRUE\n");
  } else {
    printf("FALSE\n");
  }
}
