#ifndef LENET_LAYER_H
#define LENET_LAYER_H

void conv1_forward(const double input[28][28], double output[6][24][24]);
void flatten(const double input[6][24][24], double output[3456]);
void fc_forward(const double input[3456], double output[10]);
int argmax(const double input[10]);
void lenet_forward(const double input[28][28], int& predicted, double& confidence);

#endif

