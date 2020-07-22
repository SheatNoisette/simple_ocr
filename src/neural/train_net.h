#ifndef TRAIN_NET_H
#define TRAIN_NET_H

void feedforward(Neurone n, float* input);

void backprop(Neurone n, float* input, float* neurone, float rate);

float train_Neural(Neurone n, float* input, float* neurone, float rate);

#endif
