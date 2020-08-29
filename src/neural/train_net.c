#include <stdio.h>
#include <stdlib.h>
#include "neurone.h"
#include "maths.h"
#include "train_net.h"

/*  Feedforward */
void feedforward(Neurone n, float* input)
{
    int i;
    int j;
    float sum;
    /*  For hidden layer */
    for(i = 0; i < n.nbHiddens; i++)
    {
        sum = 0.0f;
        for(j = 0; j < n.nbInputs; j++)
        {
          sum += input[j] * n.weight[i * n.nbInputs + j];
        }
        n.hidden[i] = mish(sum + n.bias[0]);
    }
    /*  For output layer */
    for(i = 0; i < n.nbOutputs; i++)
    {
        sum = 0.0f;
        for(j = 0; j < n.nbHiddens; j++)
        {
          sum += n.hidden[j] * n.h2Lw[i * n.nbHiddens + j];
        }
        n.output[i] = mish(sum + n.bias[1]);
    }
}

/*  Update weights and bias */
void backprop(Neurone n, float* input, float* neurone, float rate)
{
    int i;
    int j;
    float sum;
    float a;
    float b;
    for(i = 0; i < n.nbHiddens; i++)
    {
        sum = 0.0f;
        /*  Total error */
        for(j = 0; j < n.nbOutputs; j++)
        {
            a = dMse_Loss(n.output[j], neurone[j]);
            b = dMish(n.output[j]);
            sum += a * b * n.h2Lw[j * n.nbHiddens + i];
            /*  Correct weights in hidden to output layer. */
            n.h2Lw[j * n.nbHiddens + i] -= rate * a * b * n.hidden[i];
        }
        /*  Update weights */
        for(j = 0; j < n.nbInputs; j++)
        {
          n.weight[i * n.nbInputs + j] -= rate * sum * dMish(n.hidden[i]) * input[j];
        }
    }
}

/*  Train the NN */
float train_Neural(Neurone n, float* input, float* neurone, float rate)
{
    feedforward(n, input);
    backprop(n, input, neurone, rate);
    return (totalMse(neurone, n.output, n.nbOutputs));
}
