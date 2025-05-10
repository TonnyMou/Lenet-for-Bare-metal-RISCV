// trace_io.h
#pragma once
#include <cstdint>

void trace_print(const char *s);
void trace_print_int(int x);
void trace_putchar(char c);
void trace_print_float(double x, int precision);
void trace_print_double_array(const double* arr, int len, int precision);
void trace_print_double_matrix(const double* matrix, int rows, int cols, int precision);
void trace_print_double_tensor(const double* tensor, int channels, int rows, int cols, int precision);
void trace_print_uint64(uint64_t x);


