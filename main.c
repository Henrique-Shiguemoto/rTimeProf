#include <stdio.h>
#include "rTimeProf.h"

#include "random_int_array.c" //just for testing the api, not part of the library

// simple print function (not part of the library)
void PrintStats(rtp_section_stats* stats){
	printf("\nStats(%s): \n\t - Start Time:   %f\n\t - End Time:     %f\n\t - Elapsed Time: %f s\n\n",
			stats->section_name, stats->start_time, stats->end_time, (stats->end_time - stats->start_time) / 1000000);
}

void Bubble_Sort(int arr[], int size){
	for (int i = 0; i < size - 1; ++i) {
		for (int j = 0; j < size - i - 1; ++j) {
			if(arr[j] > arr[j + 1]){
				int aux = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = aux;
			}
		}
	}
}

int main(void) {
	rtp_init(); // initializing profiler

	rtp_start("Sorting 1000 elements"); // starting timer (you can create a name for the section you're timing)
	Bubble_Sort(random_int_array, 1000);
	rtp_stop("Sorting 1000 elements"); // stopping timer (name has to match)

	rtp_section_stats stats = rtp_get_stats("Sorting 1000 elements"); // reading stats from named section
	PrintStats(&stats);

	rtp_quit(); // quitting profiler
	return 0;
}
