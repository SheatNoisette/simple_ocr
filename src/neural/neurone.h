#ifndef NEURON_H
#define NEURON_H

/*  Struct of a neurone */
typedef struct Neurone Neurone;
struct Neurone
{
    /*  All the weights. */
    float* weight;
    /*  Hidden to output layer weights. */
    float* h2Lw;
    /*  Biases. */
    float* bias;
    /*  Hidden layer. */
    float* hidden;
    /*  Output layer. */
    float* output;
    /*  Number of biases */
    int nbBias;
    /*  Number of weights. */
    int nbWeight;
    /*  Number of inputs. */
    int nbInputs;
    /*  Number of hidden neurons. */
    int nbHiddens;
    /*  Number of outputs. */
    int nbOutputs;
};

void init_neurone(Neurone n);

Neurone neuronal(int nbInput, int nbHidden, int nbOutput);

char printD(float* array, int size);

float* prediction(Neurone n, float* input); ;

void freez(Neurone n);

#endif
