#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#define INI_1 5
#define INI_2 7
#define INI_3 11

unsigned vector[16] = { 0 };
size_t vectorSize = 0;
unsigned countedValues[10000] = { 0 };
size_t count = 0;

unsigned c(unsigned n, unsigned k) {
	if (k == 0 || n == k) {
		return 1;
	}
	return c(n - 1, k) + c(n - 1, k - 1);
}

bool isVector(unsigned toCheck) {
	size_t i,j;
	for (i = 0; i < count; i++) {
		if (toCheck == countedValues[i]) {
			return false;
		}
	}
	for (i = 0; i < count; i++) {
		for (j = 0; j < count; j++) {
			if (i == j) {
				continue;
			}
			else {
				if (toCheck + countedValues[i] == countedValues[j]) {
					return false;
				}
			}
		}
	}
	return true;
}

void upcount(unsigned newValue) {
	size_t lim = count, i;
	for (i = 0; i < lim-1;i++){
		countedValues[i + lim] = newValue + countedValues[i];
		count++;
	}
}

int main(int argc, char **argv) {
	vector[0] = INI_1; vector[1] = INI_2; vector[2] = INI_3;
	vectorSize = 3;
	size_t i, j;
	countedValues[0] = INI_1;
	countedValues[1] = INI_2;
	countedValues[2] = INI_1 + INI_2;
	countedValues[3] = INI_3;
	countedValues[4] = INI_1+ INI_3;
	countedValues[5] = INI_2 + INI_3;
	countedValues[6] = INI_1+ INI_2+ INI_3;
	count = 7;
	for (i = 3; i < 16; i++) {
		j = 1;
		unsigned toCheck = vector[i - 1];
		while (!isVector(toCheck+j)) {
			j++;
		}
		vector[i] = toCheck + j;
		printf("%d\n", vector[i]);
		count++;
		countedValues[count - 1] = vector[i];
		upcount(vector[i]);
	}
	return 0;
}