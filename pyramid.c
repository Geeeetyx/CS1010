/**
 * CS1010 Semester 1 AY21/22
 * Assignment 1: Pyramid
 *
 * Read in three positive integer corresponding to the width,
 * length, and height of a pyramid from the standard input, and
 * print the total surface area to the standard output.
 *
 * @file: pyramid.c
 * @author: TAN YU XIANG, GARETH (Group D07)
 */

#include "cs1010.h"
#include <math.h>

long square(long x) { //function to return sqaure of any number
	long sq = x*x;
	return sq;
}

double hyp_base(long w, long l) {
	double hyp = sqrt(square(w) + square(l));
	return hyp/2;
}

double hypotenuse_of(double base, long h) {
	double hypotenuse = sqrt(base*base + square(h));
	return hypotenuse;
}

long area_of_rectangle(long w, long l) {
	long a = w*l;
	return a;
}

double area_of_triangle(double hyp, double c) {
	double s = (hyp + hyp + c)/2;
	double area = sqrt(s*(s-hyp)*(s-hyp)*(s-c));
	return area;
}

int main() 
{
	long w = cs1010_read_long();
	long l = cs1010_read_long();
	long h = cs1010_read_long();
	
	double base = hyp_base(w,l);
	double hyp = hypotenuse_of(base,h);

	double area_triangle_w = area_of_triangle(hyp,w);
	double area_triangle_l = area_of_triangle(hyp,l);

	double area_base = area_of_rectangle(w,l);

	double total_area = area_base + 2*area_triangle_w + 2*area_triangle_l;
	cs1010_println_double(total_area);
}
