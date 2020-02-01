#ifndef PHASE2_H
#define PHASE2_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <dirent.h>


#define MAX_CHAR 512

typedef struct count_struct {
    char letter;
    int count;
} letter_count;

FILE *mapper;

FILE *text_file;


// Function prototypes for
//			map function that will go through text files in the Mapper_i.txt to get the (letter, wordcount)

void make_children();
void doMapper();
void init_counts (letter_count counts[]);
void process_mapper_file(int file_num, letter_count counts[]);
void process_text_file(char * path, letter_count counts[]);
void process_first_letter(char letter, letter_count counts[]);
void print_struct(letter_count counts[]);


#endif
