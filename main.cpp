#include "trace_io.h"
#include "train_images.h"
#include "train_labels.h"
#include "lenet_layer.h"
#include "timer.h"
#include <cmath>



int main() {
    trace_print("== Extended Bare-metal LeNet Test ==\n\n");
    double input_image[28][28];
    uint64_t start_cycle = read_cycle();

    for (int idx = 0; idx < 100; ++idx) {
        trace_print("Loading image idx = ");
        trace_print_int(idx);
        trace_putchar('\n');

        for (int i = 0; i < 28; ++i)
            for (int j = 0; j < 28; ++j)
                input_image[i][j] = train_images[idx][i][j]/255.0;

        //trace_print("Image loaded.\n");



        int pred;
        double max_prob;
        lenet_forward(input_image, pred, max_prob);

        trace_print("Image ");
        trace_print_int(idx);
        trace_print(": Predicted ");
        trace_print_int(pred);
        trace_print(", Label ");
        trace_print_int(train_labels[idx]);
        trace_print(", Confidence ");
        trace_print_int((int)(max_prob * 1000));  // 乘1000转整数，代表精度0.001
        trace_print(" /1000");
        trace_putchar('\n');
    }

    uint64_t end_cycle = read_cycle();
    report_elapsed_time_seconds(start_cycle, end_cycle);

 
    asm volatile ("ecall");
  //while(1);
}

