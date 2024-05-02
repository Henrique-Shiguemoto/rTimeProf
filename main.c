#include <stdio.h>
#include "rTimeProf.h"

#include <windows.h> // for Sleep

// simple print function (not part of the library)
void PrintStats(rtp_section_stats* stats){
	printf("\nStats(%s): \n\t"
		   "- Start Time(in s):   %f s\n\t" 
		   "- End Time(in s):     %f s\n\t" 
		   "- Elapsed Time:       %f us\n\n",
		   stats->section_name, 
		   stats->start_time, 
		   stats->end_time, 
		   (stats->end_time - stats->start_time) * 1000000);
}

int main(void) {
	rtp_init();

	rtp_start("Sleeping");
	Sleep(1000);
	rtp_stop("Sleeping");

	rtp_section_stats stats = rtp_get_stats("Sleeping");
	PrintStats(&stats);

	rtp_quit();
	return 0;
}
