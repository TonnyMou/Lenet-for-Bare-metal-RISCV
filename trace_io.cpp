#define TRACE (*(volatile unsigned char*)0x40000000)
#include <stdint.h> 
#include <cstdint>
void trace_putchar(char c);  // ✅ 添加这行声明

void trace_print(const char *s) {
    while (*s) {
        TRACE = *s++;
    }
}

void trace_putchar(char c) {
    TRACE = c;
}


void trace_print_int(int x) {
    char buf[12];
    uint32_t i = 0;
    uint32_t ux;

    if (x == 0) {
        trace_putchar('0');
        return;
    }

    // 判断负数
    if (x < 0) {
        trace_putchar('-');
        // 注意：-(x + 1) + 1 避免 MIN_INT 溢出
        ux = ((uint32_t)(-(x + 1))) + 1;
    } else {
        ux = (uint32_t)x;
    }

    // 转换成字符串
    while (ux > 0 && i < sizeof(buf)) {
        buf[i++] = '0' + (ux % 10);
        ux /= 10;
    }

    // 倒序输出
    while (i > 0) {
        trace_putchar(buf[--i]);
    }
}

void trace_print_float(double x, int precision) {
    // 处理符号
    if (x < 0) {
        trace_putchar('-');
        x = -x;
    }

    // 拆整数部分和小数部分
    long int_part = (long)x;
    double frac_part = x - (double)int_part;

    // 打印整数部分
    trace_print_int((int)int_part);

    // 如果不打印小数位，直接返回
    if (precision <= 0) return;

    trace_putchar('.');

    // 打印小数位
    for (int i = 0; i < precision; i++) {
        frac_part *= 10.0;
        int digit = (int)frac_part;
        trace_putchar('0' + digit);
        frac_part -= digit;
    }
}

void trace_print_double_array(const double* arr, int len, int precision) {
    for (int i = 0; i < len; ++i) {
        trace_print_float(arr[i], precision);
        trace_putchar(' ');
    }
    trace_putchar('\n');
}

void trace_print_double_matrix(const double* matrix, int rows, int cols, int precision) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int idx = i * cols + j;
            trace_print_float(matrix[idx], precision);
            trace_putchar(' ');
        }
        trace_putchar('\n');
    }
}

void trace_print_double_tensor(const double* tensor, int channels, int rows, int cols, int precision) {
    for (int c = 0; c < channels; ++c) {
        trace_print("Channel ");
        trace_print_int(c);
        trace_putchar('\n');

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                int idx = c * rows * cols + i * cols + j;
                trace_print_float(tensor[idx], precision);
                trace_putchar(' ');
            }
            trace_putchar('\n');
        }
        trace_putchar('\n');
    }
}
void trace_print_uint64(uint64_t x) {
    char buf[21];  // 最大 20 位 + '\0'
    int i = 0;
    if (x == 0) {
        trace_putchar('0');
        return;
    }
    while (x > 0) {
        buf[i++] = '0' + (x % 10);
        x /= 10;
    }
    while (i > 0) {
        trace_putchar(buf[--i]);
    }
}





