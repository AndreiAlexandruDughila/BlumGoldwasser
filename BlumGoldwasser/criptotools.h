#pragma once

#ifndef CRIPTOTOOLS_H
#define CRIPTOTOOLS_H

#include <iostream>
#include <math.h>
#include <fstream>
#include <time.h>
#include <string.h>
#include <bitset>
#include "setofbits.h""

#define CRIPTOSISTEM
#define DEBUG 1
#define TEST  0


long long modulo(long long k, long long n)
{
	if (k < 0)k = n - (-k) % n;
	if (k >= n) return k % n;
	return k;
}

long long invers(long long a, long long n) {
	long long q, r, x0 = 1, x1 = 0, copy_n = n;
	a = modulo(a, n);
	while (n != 0)
	{
		r = n;
		q = a / n;
		n = a % n;
		a = r;
		r = x1;
		x1 = x0 - q * x1;
		x0 = r;
	}
	if (a == 1)//daca numarul este inversabil
		return modulo(x0, copy_n);
	return -1;//daca numarul nu este inversabil, vom intoarce -1, pentru a putea afisa mesajul corespunzator
}

unsigned long long a_la_b_mod_c(unsigned long long int a, unsigned int b, unsigned long long int c)
{
	unsigned long long p = 1;
	a %= c;
	while (b > 0)
	{
		if (b % 2)
			p = (p * a) % c;
	      a = (a * a) % c;
		b /= 2;
	}
	return p;
}
unsigned long long cmmdc(unsigned long long a, unsigned long long b)
{
	if (a == 0 || b == 0) return a + b;
	unsigned long long r;
	do
	{
		r = a % b;
		a = b;
		b = r;
	} while (r != 0);
	return a;
}

bool prim(unsigned long long x) {
	unsigned long long i;
	if ((x == 1) || (x == 2)) return true;
	if (x % 2 == 0) return false;
	for (i = 3; i <= sqrt((double)x); i += 2)
		if (x % i == 0) return false;
	return true;
}



#endif // CRIPTOTOOLS_H
