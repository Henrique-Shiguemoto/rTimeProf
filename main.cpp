#include <iostream>
#include "rTimeProf.h"

#include <windows.h> // for Sleep

// simple print function (not part of the library)
void PrintStats(rtp_section_stats* stats){
	std::cout << "\nStats(" << stats->section_name << "): \n\t"
				 "- Start Time(in s):   " << stats->start_time << " s\n\t" 
				 "- End Time(in s):     " << stats->end_time << " s\n\t" 
				 "- Elapsed Time:       " << (stats->end_time - stats->start_time) * 1000000 << " us\n\n" << std::endl;
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
