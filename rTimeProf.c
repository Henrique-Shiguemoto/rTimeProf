#include "rTimeProf.h"

static rtp_section_stats _rtp_sections[MAX_RTP_SECTIONS];
static int _rtp_sections_cursor = 0;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)

#include <profileapi.h>
#include <BaseTsd.h>

static LARGE_INTEGER _freq = {0};

static int _rtp_get_stats_index(const char* section_name){
	int i = 0;
	while (i < _rtp_sections_cursor) {
		rtp_section_stats result = _rtp_sections[i];

		const char* str1 = section_name;
		const char* str2 = result.section_name;

		while(*str1 && *str1 == *str2){
			str1++;
			str2++;
		}

		if(!( *(const unsigned char*)str1 || *(const unsigned char*)str2 )) break;

		i++;
	}
	return i >= _rtp_sections_cursor ? -1 : i;
}

void rtp_init(){
    QueryPerformanceFrequency(&_freq);
}

void rtp_start(const char* section_name){
	if(_rtp_get_stats_index(section_name) != -1) return;

	rtp_section_stats stats = {.section_name = section_name, .start_time = 0.0, .end_time = 0.0, .start_and_end_set = 0};

	LARGE_INTEGER start_time;
	QueryPerformanceCounter(&start_time);
	stats.start_time = (double)start_time.QuadPart / (double)_freq.QuadPart;

	if(_rtp_sections_cursor < MAX_RTP_SECTIONS - 1) _rtp_sections[_rtp_sections_cursor++] = stats;
}

void rtp_stop(const char* section_name){
	int stats_index = _rtp_get_stats_index(section_name);
	if(stats_index != -1 && !_rtp_sections[stats_index].start_and_end_set){
		LARGE_INTEGER end_time;
		QueryPerformanceCounter(&end_time);
		_rtp_sections[stats_index].end_time = (double)end_time.QuadPart / (double)_freq.QuadPart;
		_rtp_sections[stats_index].start_and_end_set = 1;
	}
}

rtp_section_stats rtp_get_stats(const char* section_name){
	int stats_index = _rtp_get_stats_index(section_name);
	return (stats_index != -1 && _rtp_sections[stats_index].start_and_end_set) ? _rtp_sections[stats_index] : (rtp_section_stats){0};
}

void rtp_quit(){
	for (int i = 0; i < _rtp_sections_cursor; ++i) _rtp_sections[i] = (rtp_section_stats){0};
}

#elif defined(__linux__) || defined(__gnu_linux__)

#define _POSIX_C_SOURCE 199309L
#include <time.h>

static int _rtp_get_stats_index(const char* section_name){
	int i = 0;
	while (i < _rtp_sections_cursor) {
		rtp_section_stats result = _rtp_sections[i];

		const char* str1 = section_name;
		const char* str2 = result.section_name;

		while(*str1 && *str1 == *str2){
			str1++;
			str2++;
		}

		if(!( *(const unsigned char*)str1 || *(const unsigned char*)str2 )) break;

		i++;
	}
	return i >= _rtp_sections_cursor ? -1 : i;
}

void rtp_init(){
	// no need for initialization on Linux
}

void rtp_start(const char* section_name){
	if(_rtp_get_stats_index(section_name) != -1) return;

	rtp_section_stats stats = {.section_name = section_name, .start_time = 0.0, .end_time = 0.0, .start_and_end_set = 0};

	stats.start_time = ((double)clock() / CLOCKS_PER_SEC) * 1000000.0;

	if(_rtp_sections_cursor < MAX_RTP_SECTIONS - 1) _rtp_sections[_rtp_sections_cursor++] = stats;
}

void rtp_stop(const char* section_name){
	int stats_index = _rtp_get_stats_index(section_name);
	if(stats_index != -1 && !_rtp_sections[stats_index].start_and_end_set){
		_rtp_sections[stats_index].end_time = ((double)clock() / CLOCKS_PER_SEC) * 1000000.0;
		_rtp_sections[stats_index].start_and_end_set = 1;
	}
}

rtp_section_stats rtp_get_stats(const char* section_name){
	int stats_index = _rtp_get_stats_index(section_name);
	return (stats_index != -1 && _rtp_sections[stats_index].start_and_end_set) ? _rtp_sections[stats_index] : (rtp_section_stats){0};
}

void rtp_quit(){
	for (int i = 0; i < _rtp_sections_cursor; ++i) _rtp_sections[i] = (rtp_section_stats){0};
}

#endif
