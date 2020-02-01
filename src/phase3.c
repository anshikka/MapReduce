#include "phase3.h"
/* Reduce Function
	1)	The reducer receives the list from 'm' mappers via pipes
	2)	Ensure proper closing of pipe ends
	3) 	Combine the lists to create a single list
	4) 	Write the list to "ReducerResult.txt" in the current folder
*/

// produce each letter, count in the ReducerResult.txt file
void create_entry(letter_count data[]){
	reducer_text = fopen("ReducerResult.txt", "a");
	for (int i=0; i < 26; i++){
		char* buf = (char*) malloc(32 * sizeof(char));
		buf[1] = '\0';
		buf[0] = data[i].letter;
		char* num = (char*) malloc(12 * sizeof(char));
		sprintf(num, "%d",data[i].count);
		strcat(buf, " ");
		strcat(buf, num);
		strcat(buf, "\n");
		fputs(buf, reducer_text);
		free(num);
		free(buf);

	}
	fclose(reducer_text);

}

// init reducer process and read from pipes
void reduce(int pipes[][2], int num_processes){
	pid_t reducer_pid;
	printf("Running reducer process\n");
	letter_count total[26];
	reducer_pid = fork();
	init_counts(total);
	if (reducer_pid == 0){
		for (int i = 0; i < num_processes; i++){
			letter_count * tmp = malloc (26 * sizeof(letter_count));
			close(pipes[i][1]);
			read(pipes[i][0], tmp, 26*sizeof(letter_count));
			close(pipes[i][0]);
			for (int j = 0; j < 26; j++){
				total[j].count+=tmp[j].count;
			}
			free(tmp);

		}
		create_entry(total); // put data in ReducerResult.txt
		exit(0);
		
	} else {
		wait(NULL);
	}


}
