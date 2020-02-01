#include "phase4.h"
/* Final Result
	1)	The master process reads the "ReducerResult.txt"
	2) 	Print the contents to standard output which is redirected to "FinalResult.txt"
			i.e., on using printf, the statement should be written to "FinalResult.txt"
*/

// read in ReducerResult.txt and pass stdout to FinalResult.txt (stdout)
int read_reducer_result(){
	reducer_result = fopen("ReducerResult.txt", "r");
	final_result = fopen("FinalResult.txt", "a");
	char line[32]; // line buffer
	if (reducer_result == NULL) {
		printf("Error opening ReducerResult.txt\n");
		_exit(-1);
	} else {
		int file_num = fileno(final_result);
		dup2(file_num, STDOUT_FILENO); // redirect stdout to FinalResult.txt file number
		while(fgets(line, 32, reducer_result) != NULL) {
			printf("%s", line); // print to file
		}
	}
	return 0;
}
