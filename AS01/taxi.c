/**
 * CS1010 Semester 1 AY21/22
 * Assignment 1: Taxi
 *
 * Read in four positive integer corresponding to the day of the week,
 * the hour and minute of boarding, and the distance travelled.  Print
 * to the standard output, the taxi fare for the trip.
 *
 * @file: taxi.c
 * @author: TAN YU XIANG, GARETH (Group D07)
 */

#include "cs1010.h"
#include <stdbool.h>

bool weekday(long day) {
	if (day <= 5) {
		return true;
	} 
	
	return false;
}

bool morning_peak(long hour, long minutes) {
	if ((hour >= 6) && (hour < 9)) {
		return true;
	}

	if (hour == 9) {
		if (minutes < 30) {
			return true;
		}
	}

	return false;
}

bool evening_peak(long hour) {
	if ((hour >= 18) && (hour <= 23)) {
		return true;
	} 
		return false;
}

bool midnight(long hour) {
	if ((hour >= 0) && (hour <= 5)) {
		return true;
	} 
	
	return false;
}

double basic_fare(long distance) {
	long counter = 0;

	if (distance <= 1000) {
		counter = 0;
	} else {

		if (distance <= 10000)  {
			counter = (distance - 1000) / 400;
		
			if (((distance - 1000) % 400) > 0) {
				counter += 1;
			}
		} else {
			counter = 23; // minus away first 1km to get 9km, which is 22.5 times of 400, so set counter to 23 (22+1)
			long remainding_distance = distance - 10000;
			counter = counter + (remainding_distance / 350);
		
			if ((remainding_distance % 350) > 0) {
				counter += 1;
			}
		}
	}

	double fare = 3.70 + (counter * 0.22);
	return fare;
}

double add_surcharge(double fare, bool is_weekday, bool is_morning, bool is_evening, bool is_midnight) {
	if (is_morning == true) {
		if (is_weekday == true) {
			fare = fare * 1.25;
		} 
	}

	if (is_evening == true) {
		fare = fare * 1.25;
	}
	
	if (is_midnight == true) {
		fare = fare * 1.50;
	}

	return fare;
}

int main()
{
	long day = cs1010_read_long();
	long hour = cs1010_read_long();
	long minutes = cs1010_read_long();
	long distance = cs1010_read_long();

	bool is_weekday = weekday(day);
	bool is_morning = morning_peak(hour,minutes);
	bool is_evening = evening_peak(hour);
	bool is_midnight = midnight(hour);

	double fare = basic_fare(distance);
	double total = add_surcharge(fare, is_weekday, is_morning, is_evening, is_midnight);

	cs1010_println_double(total);
}
