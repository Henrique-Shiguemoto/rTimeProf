#include "rTimeProf.h"

static rtp_section_stats _rtp_sections[MAX_RTP_SECTIONS];
static int _rtp_sections_cursor = 0;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)

#include <profileapi.h>
#include <BaseTsd.h>

static LONGLONG _freq = {0};

void rtp_init(){
    LARGE_INTEGER result;
    QueryPerformanceFrequency(&result);
    _freq = result.QuadPart;
}

void rtp_start(const char* section_name){
	rtp_section_stats stats = {.section_name = section_name, .start_time = 0.0, .end_time = 0.0, .start_and_end_set = 0};

	LARGE_INTEGER start_time;
	QueryPerformanceCounter(&start_time);
	stats.start_time = (start_time.QuadPart * 1000000) / _freq;

	if(_rtp_sections_cursor < MAX_RTP_SECTIONS - 1) _rtp_sections[_rtp_sections_cursor++] = stats;
}

void rtp_stop(const char* section_name){
	int stats_index = rtp_get_stats_index(section_name);
	if(stats_index != -1){
		LARGE_INTEGER end_time;
		QueryPerformanceCounter(&end_time);
		_rtp_sections[stats_index].end_time = (end_time.QuadPart * 1000000) / _freq;
		_rtp_sections[stats_index].start_and_end_set = 1;
	}
}

int rtp_get_stats_index(const char* section_name){
	int i = 0;
	while (i < _rtp_sections_cursor) {
		rtp_section_stats result = _rtp_sections[i];

		while(*section_name && *section_name == *result.section_name){
			section_name++;
			result.section_name++;
		}

		if(!( *(const unsigned char*)section_name || *(const unsigned char*)result.section_name )) break;

		i++;
	}
	return i >= _rtp_sections_cursor ? -1 : i;
}

rtp_section_stats rtp_get_stats(const char* section_name){
	int stats_index = rtp_get_stats_index(section_name);
	return (stats_index != -1 && _rtp_sections[stats_index].start_and_end_set) ? _rtp_sections[stats_index] : (rtp_section_stats){0};
}

void rtp_quit(){
	for (int i = 0; i < _rtp_sections_cursor; ++i) _rtp_sections[i] = (rtp_section_stats){0};
}


#elif defined(__linux__) || defined(__gnu_linux__)

#define _POSIX_C_SOURCE 199309L
#include <time.h>

void rtp_init(){

}

void rtp_start(const char* section_name){

}

void rtp_stop(const char* section_name){

}

rtp_section_stats rtp_get_stats(const char* section_name){

}

void rtp_quit(){

}


#endif
