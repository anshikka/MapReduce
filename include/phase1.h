#ifndef PHASE1_H
#define PHASE1_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int cur_num_files;
int num_file_paths;
int mappers;
int MAX;
int symbolic;
int cur_mappers_created;
FILE *mapper;

// create mapper files for determined number of mapper processes
void init_mappers();

// add a file path to a mapper file
void addToMapper(char* path);

// Create a MapperInput Folder
void createFolder();

// count how many files there are total
int count_file_paths();

// Traverse the Folder
int traverse_files(char* path);


#endif

