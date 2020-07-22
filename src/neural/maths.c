#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <string.h>
#include "train_data.h"
#include "neurone.h"
#include "maths.h"

// Prints an array of floats
void printN(float* array, int size)
{
    for(int i = 0; i < size; i++)
    {
      printf("%f ",  (double) array[i]);
    }
    printf("\n");
}

float randomize()
{
  return (rand() / (float)RAND_MAX);
}

// Another activation function
float mish(float x)
{
	x = (x * tanh(log(1 + exp(x))));
	return x;
}

// Derivate of the mish function
float dMish(float x)
{
	float y = exp(3*x) + 4*exp(2*x) + (6+4*x)*exp(x) + 4*(1+x);
	float z = pow((exp(x) + 1), 2) + 1;
	x = ((exp(x) * y) / pow(z, 2));
	if(x < 0)
	{
		return -x;
	}
	else
	{
		return x;
	}
}

// returns a float between 0 and 1
float sigmoid(float x)
{
	return (1 / (1 + exp(-x)));
}

// Derivate of the sigmoid function
float dSigmoid(float x)
{
	x = sigmoid(x);
	return (x * (1 - x));
}

// These tree functions below determined the error
float mse_loss(float y_true, float y_pred)
{
	return (pow((y_true - y_pred), 2));
}

float dMse_Loss(float y_true, float y_pred)
{
	return (y_true - y_pred);
}

float totalMse(float* neurone, float* output, int size)
{
	float sum = 0;
	for(int i = 0; i < size; i++)
	{
			sum += mse_loss(neurone[i], output[i]);
	}
	return sum;
}
