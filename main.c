#include <stdio.h>
#include "rTimeProf.h"

int main(void) {
	rtp_init();

	rtp_start("Count to 1.");
	for (int i = 0; i < 1000000; ++i);
	rtp_stop("Count to 1.");

	rtp_section_stats stats = rtp_get_stats("Count to 1.");
	printf("Start time: %f, End time: %f, Elapsed time: %f s\n", stats.start_time, stats.end_time, (stats.end_time - stats.start_time) / 1000000.0f);

	rtp_quit();
	return 0;
}