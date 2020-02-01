#ifndef PHASE3_H
#define PHASE3_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "phase2.h"
FILE *reducer_text;

FILE *reducer_text;
// Function prototype for 
//			reduce function that will receive list from all the Mappers to create a single list
//			the single list is then written to ReducerResult.txt

void create_entry(letter_count data[]);
void reduce(int pipes[][2], int num_processes);

#endif
