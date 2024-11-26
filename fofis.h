#include <stdbit.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef FOFIS_H
#define FOFIS_H

#define INDEX 0x1
#define COLUMNS 0x2
#define SEMICOLON 0x4
#define TREAT_MISSING_VALUES 0x8
#define MULTITHREADING 0x10
#define BUFF_SIZE 131072

struct Cell {
  enum { INT, DOUBLE, STRING, BOOL } cell_type;
  union {
    int64_t integer;
    double floating_point;
    char *string;
    int64_t boolean;
  } cell_value;
};

union CsvConfig {
  struct {
    uint8_t indexes : 1;
    uint8_t named_columns : 1;
    uint8_t semicolon : 1;
    uint8_t treat_missing_values : 1;
    uint8_t multithreading : 1;
  } internal;
  int8_t config;
};

struct Csv {
  size_t lines;
  size_t columns;
  union CsvConfig config;
  char **columns_names;
  struct Cell **grid;
};

void alloc_grid(struct Cell ***grid, size_t *lines, size_t *columns,
                char *file_name);
void construct(struct Csv *csv, char *file_name);
struct Csv *bopen(const char *path, union CsvConfig build);
struct Csv *iopen(const char *path, int8_t build);
void debug_config(struct Csv *csv);

#endif // !FOFIS_H
