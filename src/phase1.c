#include "phase1.h"

#define FILENAME_BUFFER 256
// You are free to use your own logic. The following points are just for getting started
/* 	Data Partitioning Phase - Only Master process involved
	1) 	Create 'MapperInput' folder
	2) 	Traverse the 'Sample' folder hierarchy and insert the text file paths
		to Mapper_i.txt in a load balanced manner
	3) 	Ensure to keep track of the number of text files for empty folder condition 

*/

/* create files for each mapper process and put in 
file paths */
void addToMapper(char* path){
	if (cur_mappers_created + 1 == mappers && mappers != 1) {
		cur_mappers_created = -1; // round robin fashion
	}

	// open next mapper files every time the current mapper file reaches the MAX paths
	if (cur_num_files == MAX && mappers != 1){
		fclose(mapper);
		mapper = NULL;
		char buffer [1024];
		buffer[0] = '\0';
		cur_mappers_created += 1;
		char * mapper_path_base = "./MapperInput/Mapper_";
		strcat(buffer, mapper_path_base);
		char num_mappers[3];
		sprintf(num_mappers, "%d", cur_mappers_created);
		strcat(buffer, num_mappers);
		strcat(buffer, ".txt");
		mapper = fopen(buffer, "a");
		cur_num_files = 0; // reset path count for each file
	}
	
	fputs(path, mapper); // add path to mapper txt
	cur_num_files += 1;	
}

void init_mappers(){ // create all mapper files (empty)
	for (int i =0; i < mappers; i++){
		char buffer [1024];
		buffer[0] = '\0';
		char * mapper_path_base = "./MapperInput/Mapper_";
		strcat(buffer, mapper_path_base);
		char num_mappers[3];
		sprintf(num_mappers, "%d", i);
		strcat(buffer, num_mappers);
		strcat(buffer, ".txt");
		mapper = fopen(buffer, "a");
		fclose(mapper);
	}
}

// create MapperInput Directory (in src)
void createFolder(){
	DIR *dr = opendir("/"); // open current directory

	if(dr == NULL){
		perror("Could not open current directory.\n");
		_exit(1);
	}
	mkdir("./MapperInput", 0700);
}

// Traverse directories to count each file path and total it
int count_file_paths(char * path) {
	DIR *dr = opendir(path);
	int count = 0;
	if (dr == NULL) {
		printf("Empty or Invalid Path!\n");
	} else {
		struct dirent *de = NULL;
		while((de = readdir(dr)) != NULL) {
			if(de ->d_type == DT_REG) {
				count += 1;
			} else if (de->d_type == DT_DIR && strcmp(de->d_name, "..") !=0 && strcmp(de->d_name, ".")!=0){
				// recurse to next directory
				char full_buffer[1024];
				full_buffer[0] = '\0';
				char *first = path;
				char *second = "/";
				char *third = de->d_name;
				strcat(full_buffer, first);
				strcat(full_buffer, second);
				strcat(full_buffer, third); // build file path name
				count += count_file_paths (full_buffer);
			}

		}
	}
	return count;
}

// go through each Sample folder directory and add each file path to mapper process text files
int traverse_files(char * path){
	DIR *dr = opendir(path);
	if(dr == NULL) {// opendir returns NULL if directory cannot be opened
		perror("Empty or invalid path!\n");
	} else {
		struct dirent *de = NULL;
		struct stat stats; // extra credit
		stat(de->d_name, &stats);
		while((de = readdir(dr)) != NULL) {
			
			if (de->d_type == DT_REG){
				if (lstat(path, &stats) == 0){
					symbolic +=1;
					//continue; //can identify symbolic link, but don't know how to avoid processing
				} else {
					char full_buffer[1024];
					full_buffer[0] = '\0';
					char *first = path;
					char *second = "/";
					char *third = de->d_name;
					strcat(full_buffer, first);
					strcat(full_buffer, second);
					strcat(full_buffer, third); // build file path name;
					strcat(full_buffer, "\n");
					addToMapper(full_buffer);
				}
				
				// Traverse to next directory
			} else if (de->d_type == DT_DIR && strcmp(de->d_name, "..") != 0 && strcmp(de->d_name, ".")!= 0) {
				char full_buffer[1024];
				full_buffer[0] = '\0';
				char *first = path;
				char *second = "/";
				char *third = de->d_name;
				strcat(full_buffer, first);
				strcat(full_buffer, second);
				strcat(full_buffer, third); // build file path name;
				traverse_files(full_buffer);
			}
		}
	}

	return 0;
}

