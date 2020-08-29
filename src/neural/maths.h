#ifndef MATHS_H
#define MATHS_H

void printN(float* array, int size);

float randomize();

float mish(float x);

float dMish(float x);

float sigmoid(float x);

float dSigmoid(float x);

float mse_loss(float y_true, float y_pred);

float dMse_Loss(float y_true, float y_pred);

/* Total error of a neurone at the end */
float totalMse(float* neurone, float* output, int size);

#endif
