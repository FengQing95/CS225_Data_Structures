#include "epoch.h"
/* Your code here! */
int hours(time_t t){
	int minute = t / 60;
	int hour = minute / 60;
	return hour;
}

int days(time_t t){
	int hour = hours(t);
	int day = hour / 24;
	return day;
}

int years(time_t t){
	int day = days(t);
	int year = day / 365;
	return year;
}
