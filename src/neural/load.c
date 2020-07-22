#include <stdio.h>
#include <stdlib.h>
#include "train_data.h"
#include "neurone.h"
#include "load.h"

// Loads
Neurone load(char* path)
{
    FILE* file = fopen(path, "r");
    int nbInput = 0;
    int nbHidden = 0;
    int nbOutput = 0;
    int biases = 0;
    int content = 0;
    // Load header.
    int header = fscanf(file, "%d %d %d\n", &nbInput, &nbHidden, &nbOutput);
    // Build a new tinn.
    Neurone n = neuronal(nbInput, nbHidden, nbOutput);
    // Load biases and weights.
    for(int i = 0; i < n.nbBias; i++)
    {
      biases = fscanf(file, "%f\n", &n.bias[i]);
    }
    for(int i = 0; i < n.nbWeight; i++)
    {
      content = fscanf(file, "%f\n", &n.weight[i]);
    }
    if (biases != 1 || content != 1 || header != 1) {
      printf("[Neural] File loaded!\n");
    }

    fclose(file);
    return n;
}

// Save all weights in a save file
void save(Neurone n, char* path)
{
    FILE* file = fopen(path, "w");
    // Save header.
    fprintf(file, "%d %d %d\n", n.nbInputs, n.nbHiddens, n.nbOutputs);
    // Save biases and weights.
    for(int i = 0; i < n.nbBias; i++)
    {
      fprintf(file, "%f\n", (double) n.bias[i]);
    }
    for(int i = 0; i < n.nbWeight; i++)
    {
      fprintf(file, "%f\n", (double) n.weight[i]);
    }
    fclose(file);
}

// Random datas in the Data structure
void randShuffle(Data data)
{
    for(int i = 0; i < data.nbRows; i++)
    {
        int b = rand() % data.nbRows;
        float* out = data.neurone[i];
        float* in = data.input[i];

        data.neurone[i] = data.neurone[b];
        data.neurone[b] = out;

        data.input[i] = data.input[b];
        data.input[b] = in;
    }
}

// Free data components.
void freeData(Data data)
{
    for(int i = 0; i < data.nbRows; i++)
    {
        free(data.input[i]);
        free(data.neurone[i]);
    }
    free(data.input);
    free(data.neurone);
}
