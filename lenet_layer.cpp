#include <cstdint>
#include <algorithm>
#include "lenet_layer.h"
#include "conv1_weight.h"
#include "conv1_bias.h"
#include "trace_io.h"
#include "fc_bias.h"
#include "fc_weight.h"
#include "conv3_weight.h"
#include "conv3_bias.h"
#include "conv5_weight.h"
#include "conv5_bias.h"
#include "timer.h"

double conv1_output[6][24][24] = {0};
double s2_output[6][12][12] = {0};
double c3_output[16][8][8] = {0}; 
double s4_output[16][4][4] = {0};
double c5_output[120] = {0};
double fc_output[10] = {0};


void conv1_forward(const double input[28][28], double output[6][24][24]) {
   // trace_print("Enter conv1_forward\n");
//uint64_t start_cyclecv1 = read_cycle(); 
    for (int oc = 0; oc < 6; ++oc) {
        for (int i = 0; i < 24; ++i) {
            for (int j = 0; j < 24; ++j) {
                double sum = conv1_bias[oc];
                for (int m = 0; m < 5; ++m)
                    for (int n = 0; n < 5; ++n)
                        sum += input[i + m][j + n] * conv1_weight[oc][0][m][n];
                output[oc][i][j] = sum > 0 ? sum : 0;
                //output[oc][i][j] = sum;
              
          }
        }
    }
//uint64_t end_cyclecv1 = read_cycle();
//report_elapsed_time_seconds(start_cyclecv1, end_cyclecv1);
}
//flatten not used
void flatten(const double input[6][24][24], double output[3456]) {
   // trace_print("Enter flatten\n");
    int idx = 0;
    for (int c = 0; c < 6; ++c) {
        for (int i = 0; i < 24; ++i) {
            for (int j = 0; j < 24; ++j) {
                output[idx++] = input[c][i][j];
            }
        }
    }
   // trace_print("Flatten idx = ");
    //trace_print_int(idx);
    //trace_putchar('\n');
}

void fc_forward(const double input[120], double output[10]) {
//uint64_t start_cyclecv1 = read_cycle(); 
    for (int i = 0; i < 10; ++i) {
        double sum = fc_bias[i];
        for (int j = 0; j < 120; ++j) {
            sum += input[j] * fc_weight[i][j];
        }
        output[i] = sum;
    }
    //trace_print("FC done\n");
  //  uint64_t end_cyclecv1 = read_cycle();
   // report_elapsed_time_seconds(start_cyclecv1, end_cyclecv1);
}

int argmax(const double input[10]) {
    int max_idx = 0;
    for (int i = 1; i < 10; ++i) {
        if (input[i] > input[max_idx]) {
            max_idx = i;
        }
    }
    return max_idx;
}

static void maxpool2x2_6(const double input[6][24][24], double output[6][12][12]) {
   // trace_print("== pool_forward input[0][0][0] ==\n");
   // trace_print_float(input[0][0][0], 2);
    //trace_putchar('\n');
    //trace_print("pool in addr = ");
    //trace_print_int((long)(uintptr_t)&input[0][0][0]);
    //trace_putchar('\n');
 // uint64_t start_cyclecv1 = read_cycle();
    for (int c = 0; c < 6; ++c)
        for (int i = 0; i < 12; ++i)
            for (int j = 0; j < 12; ++j) {
                double m = input[c][2*i][2*j];
                m = std::max(m, input[c][2*i][2*j+1]);
                m = std::max(m, input[c][2*i+1][2*j]);
                m = std::max(m, input[c][2*i+1][2*j+1]);
                output[c][i][j] = m;
            }
 //uint64_t end_cyclecv1 = read_cycle();
//report_elapsed_time_seconds(start_cyclecv1, end_cyclecv1);
}

static void maxpool2x2_16(const double input[16][8][8], double output[16][4][4]) {
//uint64_t start_cyclecv1 = read_cycle();
    for (int c = 0; c < 16; ++c) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                int x = 2 * i;
                int y = 2 * j;

                double a = input[c][x][y];
                double b = input[c][x][y+1];
                double d = input[c][x+1][y];
                double e = input[c][x+1][y+1];
                double m = std::max({a, b, d, e});
                output[c][i][j] = m;
    
                
            }
        }
    }
              //uint64_t end_cyclecv1 = read_cycle();
//report_elapsed_time_seconds(start_cyclecv1, end_cyclecv1);       
}


static void conv3_forward(const double input[6][12][12], double output[16][8][8]) {
 //uint64_t start_cyclecv1 = read_cycle();
    for (int oc = 0; oc < 16; ++oc)
        for (int i = 0; i < 8; ++i)
            for (int j = 0; j < 8; ++j) {
                double sum = conv3_bias[oc];
                for (int ic = 0; ic < 6; ++ic)
                    for (int m = 0; m < 5; ++m)
                        for (int n = 0; n < 5; ++n)
                            sum += input[ic][i + m][j + n] * conv3_weight[oc][ic][m][n];
                output[oc][i][j] = sum > 0 ? sum : 0;
            }
//uint64_t end_cyclecv1 = read_cycle();
//report_elapsed_time_seconds(start_cyclecv1, end_cyclecv1);
}

static void conv5_forward(const double input[16][4][4], double output[120]) {
//uint64_t start_cyclecv1 = read_cycle(); 
    for (int oc = 0; oc < 120; ++oc) {
        double sum = conv5_bias[oc];
        for (int ic = 0; ic < 16; ++ic)
            for (int m = 0; m < 4; ++m)
                for (int n = 0; n < 4; ++n)
                    sum += input[ic][m][n] * conv5_weight[oc][ic][m][n];
        output[oc] = sum > 0 ? sum : 0;
        }
              // uint64_t end_cyclecv1 = read_cycle();
              // report_elapsed_time_seconds(start_cyclecv1, end_cyclecv1);
    
}
#define EXP_LUT_STEP   0.5
#define EXP_LUT_SIZE   21
static const double exp_lut[EXP_LUT_SIZE] = {
  1.0,0.6065306597,0.3678794412,0.2231301601,0.1353352832,
  0.0820849986,0.0497870684,0.0301973834,0.0183156389,0.0111089965,
  0.0067379470,0.0040867714,0.0024787522,0.0015034392,0.0009118820,
  0.0005530844,0.0003354626,0.0002034684,0.0001234098,0.0000742736,
  0.0000453999
};
static double softexp(double x) {
  if (x >= 0.0) return 1.0;
  if (x < -10.0) x = -10.0;
  double idx = -x/EXP_LUT_STEP;
  int lo = (int)idx;
  if (lo >= EXP_LUT_SIZE-1) return exp_lut[EXP_LUT_SIZE-1];
  double frac = idx - lo;
  double v0 = exp_lut[lo], v1 = exp_lut[lo+1];
  return v0 + (v1 - v0)*frac;
}

void compute_softmax_and_confidence(double fc_output[10], int predicted, double &confidence) {
    // 1) 找到最大 logit
    double maxv = fc_output[0];
    for (int i = 1; i < 10; i++) {
        if (fc_output[i] > maxv) maxv = fc_output[i];
    }

    // 2) 计算 exp(x - maxv) 并累加
    double sum = 0.0;
    for (int i = 0; i < 10; i++) {
        double shifted = fc_output[i] - maxv;   // 确保 shifted ≤ 0
        double e = softexp(shifted);
        fc_output[i] = e;
        sum += e;
    }

    // 3) 归一化得到 confidence
    confidence = fc_output[predicted] / sum;
}


void lenet_forward(const double input[28][28], int& predicted, double& confidence) {

 //double conv1_output[6][24][24];
 //double s2_output[6][12][12];
 //double c3_output[16][8][8]; 
 //double s4_output[16][4][4];
//double c5_output[120];
//double fc_output[10];
 
    conv1_forward(input, conv1_output);
    maxpool2x2_6(conv1_output, s2_output);
    conv3_forward(s2_output, c3_output);
    maxpool2x2_16(c3_output, s4_output);
    conv5_forward(s4_output, c5_output);
    fc_forward(c5_output, fc_output);
    predicted = argmax(fc_output);

//debug
trace_print("C1 out example: ");
trace_print_int((int)(conv1_output[0][0][0] * 1000));
trace_putchar('\n');
//trace_print("C1[0][0][0] = ");
//trace_print_int((int)(conv1_output[0][0][0]));
//trace_putchar('\n');
//trace_print("FC bias[0] = ");
//trace_print_float(fc_bias[0],3);
//trace_putchar('\n');
trace_print("FC input[0] = ");
trace_print_float(input[0][0],3);
//trace_putchar('\n');
//trace_print("FC weight[0][0] = ");
//trace_print_int((int)(fc_weight[0][0] * 1000));
trace_putchar('\n');
trace_print("S2 out example: ");
trace_print_int((int)(s2_output[0][0][0] * 1000));
trace_putchar('\n');
trace_print("C3 out example: ");
trace_print_float(c3_output[2][2][2], 3);
trace_putchar('\n');
trace_print("S4 output example = ");
trace_print_float(s4_output[0][0][1], 3);
trace_putchar('\n');

trace_print("logits = ");
for(int i = 0; i < 10; i++){
    trace_print_float(fc_output[i], 4);
   if(i < 9) trace_print(", ");
}
trace_putchar('\n');
compute_softmax_and_confidence(fc_output, predicted, confidence);
trace_print("Confidence = ");
trace_print_float(confidence, 4);
trace_putchar('\n');

}

