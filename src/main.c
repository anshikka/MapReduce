#include "main.h"

int phase1(char* path){
	createFolder(); // create directory
	char * sample_path = path;
	num_file_paths = count_file_paths(sample_path);
	mappers = MAPPERS;
	MAX = num_file_paths/mappers; // determine how many text file paths per mapper process
	printf("Maximum paths per mapper file is %d\n", MAX);
	init_mappers();
	mapper = fopen("./MapperInput/Mapper_0.txt", "a"); // start by opening first mapper process file
	cur_num_files = 0;
	cur_mappers_created = 0;
	symbolic = 0;
	traverse_files(sample_path); // go through and add files
	fclose(mapper); // close any open mapper
	printf("%d Symbolic Links Found\n", symbolic);
	return 0;
}

int phase2(int pipes[][2]){
	make_children(pipes, MAPPERS); // create mapper processes
	return 0;

}

int phase3(int pipes[][2]) {
	reduce(pipes, MAPPERS); // read from pipes and produce ReducerResult.txt
}

int phase4(){
	read_reducer_result(); // read from reducer process and produce FinalResult.txt
}


int main(int argc, char *argv[]){

	// argument count check
	if (argc == 3) {

	//just make a function call to code in phase1.c
	//phase1 - Data Partition Phase
		MAPPERS = atoi(argv[2]);
		phase1(argv[1]);
		//create pipes
		int letter_pipes[MAPPERS][2];

		
		//just make a function call to code in phase2.c
		//phase2 - Map Function
		phase2(letter_pipes);

		//just make a function call to code in phase3.c
		//phase3 - Reduce Function
		phase3(letter_pipes);

		//phase4
		//wait for all processes to reach this point			
		//just make a function call to code in phase4.c
		//master process reports the final output
		phase4();

		
		return 0;
	}
	else {
		perror("Not enough arguments!\n");

	}

	

}
