#ifndef TRAIN_DATA_H
#define TRAIN_DATA_H

/*  Data struct. */
typedef struct Data Data;
struct Data
{
    /*  array d'input à 2 dimensions. */
    float** input;
    /*  array de neurones à 2 dimensions. */
    float** neurone;
    /*  Number of inputs to neural network. */
    int nbInputs;
    /*  Number of outputs to neural network. */
    int nbOutputs;
    /*  Number of rows in file (number of sets for neural network). */
    int nbRows;
};

int nbLines(FILE* file);

char* readLines(FILE* file);

float** new2d(int rows, int cols);

Data newData(int nbInput, int nbOutput, int rows);

void parse(Data data, char* line, int row);

Data build(char* path, int nbInput, int nbOutput);

#endif
