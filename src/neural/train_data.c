#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "train_data.h"

// Returns the number of lines in a file.
int nbLines(FILE* file)
{
    int ch = EOF;
    int lines = 0;
    int pc = '\n';
    while((ch = getc(file)) != EOF)
    {
        if(ch == '\n')
        {
          lines += 1;
        }
        pc = ch;
    }
    if(pc != '\n')
    {
      lines += 1;
    }
    rewind(file); //The function moves the file position indicator to the beginning of the specified stream, while also clearing the error and EOF flags associated with that stream.
    return lines;
}

// Reads a line from a file.
char* readLines(FILE* file)
{
    int chare = EOF;
    int reads = 0;
    int size = 128;
    char* line = (char*) malloc((size) * sizeof(char));
    while((chare = getc(file)) != '\n' && chare != EOF)
    {
        line[reads++] = chare;
        if(reads + 1 == size)
        {
          line = (char*) realloc((line), (size *= 2) * sizeof(char));
        }
    }
    line[reads] = '\0';
    return line;
}

// New 2D array of floats
float** new2d(int rows, int cols)
{
    float** row = (float**) malloc((rows) * sizeof(float*));
    for(int r = 0; r < rows; r++)
    {
      row[r] = (float*) malloc((cols) * sizeof(float));
    }
    return row;
}

// New data for the Data struct
Data newData(int nbInput, int nbOutput, int rows)
{
    Data data = { new2d(rows, nbInput), new2d(rows, nbOutput), nbInput, nbOutput, rows };
    return data;
}

// Gets one row of inputs and outputs from a string.
// atof : converts a string into a floating point numerical representation
// strtok : breaks string and remove 2nd param (of the function) in the string
void parse(Data data, char* line, int row)
{
    int cols = data.nbInputs + data.nbOutputs;
    for(int i = 0; i < cols; i++)
    {
        float val = atof(strtok(i == 0 ? line : NULL, " "));
        if(i < data.nbInputs)
        {
          data.input[row][i] = val;
        }
        else
        {
          data.neurone[row][i - data.nbInputs] = val;
        }
    }
}

// Parse file in order to get all input
Data build(char* path, int nbInput, int nbOutput)
{
    FILE* file = fopen(path, "r");
    if(file == NULL)
    {
        printf("Could not open %s\n", path);
        exit(1);
    }
    int rows = nbLines(file);
    Data data = newData(nbInput, nbOutput, rows);
    for(int i = 0; i < rows; i++)
    {
        char* line = readLines(file);
        parse(data, line, i);
        free(line);
    }
    fclose(file);
    return data;
}
