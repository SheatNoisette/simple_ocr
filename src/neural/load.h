#ifndef LOAD_H
#define LOAD_H

#include "neurone.h"
#include "train_data.h"

Neurone load(char* path);

void save(Neurone n, char* path);

void randShuffle(Data data);

void freeData(Data data);

#endif
