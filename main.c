#include <stdio.h>
#include "rTimeProf.h"

void PrintStats(rtp_section_stats* stats){
	printf("\nStats(%s): \n\t - Start Time:   %f\n\t - End Time:     %f\n\t - Elapsed Time: %f s\n\n",
			stats->section_name, stats->start_time, stats->end_time, (stats->end_time - stats->start_time) / 1000000);
}

int main(void) {
	return 0;
}
