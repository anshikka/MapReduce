#include "phase2.h"
/* 	Map Function
	1)	Each mapper selects a Mapper_i.txt to work with
	2)	Creates a list of letter, wordcount from the text files found in the Mapper_i.txt
	3)	Send the list to Reducer via pipes with proper closing of ends
*/

// Fork child processes
void make_children(int pipes[][2], int num_processes){
	pid_t mapper_process[num_processes];
	int status;
	for (int i = 0; i < num_processes; i++){
		pipe(pipes[i]);
		mapper_process[i] = fork();
		if (mapper_process[i] == 0){
			printf("Creating mapper process %d\n", i);
			doMapper(i, pipes);
			exit(0);
		}
		else {
			wait(NULL);
		}

		
	}
	
}

// fill structs with data and write to pipe for each process
void doMapper(int i, int pipes[][2]){
	letter_count counts[26];
	init_counts(counts);
	process_mapper_file(i, counts);
	//send to pipes
	close(pipes[i][0]);
	write(pipes[i][1], counts, 26*sizeof(letter_count));
	close(pipes[i][1]);
}

// initialize struct with letters and counts = 0
void init_counts (letter_count counts[]){
	for (int i = 0; i < 26; i++){
		counts[i].letter = 65+i;
		counts[i].count = 0;
	}
}

// Go through each file path in each mapper process
void process_mapper_file(int file_num, letter_count counts[]){
	char mapper_file_buf[1024];
	char num_buf[3];
	char path[MAX_CHAR];
	sprintf(num_buf, "%d", file_num);
	mapper_file_buf[0] = '\0';
	strcat(mapper_file_buf, "./MapperInput/Mapper_");
	strcat(mapper_file_buf, num_buf);
	strcat(mapper_file_buf, ".txt");
	mapper = fopen(mapper_file_buf, "r");
	if (mapper == NULL) {
		perror("Could not open mapper text file!\n");
		_exit(-1);
	} else {
		while(fgets(path, MAX_CHAR, mapper) != NULL){ 
			process_text_file(path, counts);
		}
	}
}
/* Remove newline character if found */
void remove_newline_character (char * token){
	int len = strlen(token) - 1;
	if(token[len] == '\n'){
		token[len] = '\0';
	}
}

//line by line get words and get first letter
void process_text_file(char * path, letter_count counts[]){
	remove_newline_character(path);
	text_file = fopen(path, "r");
	char word[MAX_CHAR];
	if (text_file == NULL) {
		printf("Could not open word text file: %s\n", path);
		_exit(-1);
	} else {
		// line by line
		while(fgets(word, MAX_CHAR, text_file) != NULL) {
			char f_letter = word[0];
			process_first_letter(f_letter, counts);
		}
	}

}

// for each word, get the first letter and increase count
void process_first_letter (char letter, letter_count counts[]){
	for (int i = 0; i < 26; i++){
		if (counts[i].letter == toupper(letter)){
			counts[i].count += 1;
		}
	}
}

// print passed in structure
void print_struct(letter_count counts[]){
	for (int i = 0; i < 26; i++){
		printf("%c: %d\n", counts[i].letter, counts[i].count);
	}
}

