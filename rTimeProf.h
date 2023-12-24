#ifndef R_TIME_PROF
#define R_TIME_PROF

#define MAX_RTP_SECTIONS 100

// in microseconds
typedef struct rtp_section_stats {
	const char* section_name;
	double start_time;
	double end_time;
	int start_and_end_set;
} rtp_section_stats;

void rtp_init();
void rtp_start(const char* section_name);
void rtp_stop(const char* section_name);
int rtp_get_stats_index(const char* section_name);
rtp_section_stats rtp_get_stats(const char* section_name);
void rtp_quit();

#endif // R_TIME_PROF