#include <stdio.h>
#include <stdlib.h>
#include "maths.h"
#include "neurone.h"
#include "train_net.h"

/*  Randomizes neurone weights and biases. */
void init_neurone(Neurone n)
{
    for(int i = 0; i < n.nbWeight; i++)
    {
      n.weight[i] = randomize() - 0.5f;
    }
    for(int i = 0; i < n.nbBias; i++)
    {
      n.bias[i] = randomize() - 0.5f;
    }
}

/*  Constructs a neurone with number of inputs, number of hidden neurons, and number of outputs */
Neurone neuronal(int nbInput, int nbHidden, int nbOutput)
{
    Neurone n;

    n.nbBias = 2;
    n.nbWeight = nbHidden * (nbInput + nbOutput);
    n.weight = (float*) calloc(n.nbWeight, sizeof(*n.weight));
    n.h2Lw = n.weight + nbHidden * nbInput;
    n.bias = (float*) calloc(n.nbBias, sizeof(*n.bias));
    n.hidden = (float*) calloc(nbHidden, sizeof(*n.hidden));
    n.output = (float*) calloc(nbOutput, sizeof(*n.output));
    n.nbInputs = nbInput;
    n.nbHiddens = nbHidden;
    n.nbOutputs = nbOutput;
    init_neurone(n);
    return n;
}

/*  Prints the char recognised */
char printD(float* array, int size)
{
    char dataset[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    float tab[36];
    int count = 0;
    for(int i = 0; i < size; i++)
    {
      /* printf("%f ", sigmoid(array[i])); */
      tab[i] = (sigmoid(array[i]));
    }
    /* printf("\n"); */
    for(int j = 0; j < 36; j++)
    {
      if(tab[count] < tab[j])
      {
        count = j;
      }
    }
    return dataset[count];
}

/*  Return expected value we should get at this end for a output neuron */
float* prediction(Neurone n, float* input)
{
    feedforward(n, input);
    return (n.output);
}

/*  Free all data of a neuron */
void freez(Neurone n)
{
    free(n.weight);
    free(n.bias);
    free(n.hidden);
    free(n.output);
}
