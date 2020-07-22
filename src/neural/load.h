#ifndef LOAD_H
#define LOAD_H

Neurone load(char* path);

void save(Neurone n, char* path);

void randShuffle(Data data);

void freeData(Data data);

#endif
