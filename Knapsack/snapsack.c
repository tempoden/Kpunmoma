#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MOD 997

static int vector[6] = { 5,7,11,14,17,34 };
int rebuilt[6] = { 0 };
int divided[6][2] = { 0 };

int inverse(int num, int mod) {
	int i;
	for (i = 0; i < mod; i++) {
		if ((num*i) % mod == 1)
			return i;
	}
	return 0;
}

void magic(int n) {
	srand(rebuilt[n]);
	divided[n][0] = 2 + rand() % (MOD - 2);
	divided[n][1] = (rebuilt[n] - divided[n][0]) % MOD;
	printf("%d = %d + %d =",rebuilt[n] , divided[n][0] , divided[n][1]);
}

int main(int argc, char** argv) {
	freopen("out.txt", "w", stdout);

	printf("5 7 11 14 17 32 \n mod=%d \n",MOD);

	unsigned char data[7] = "110101\0";
	printf("data = %s    ", data);
	
	int sum=0,i, 
			a=0, a_inv,
			d0=0,d0_inv,
			d1=0,d1_inv,
			encrypted[2] = { 0 };

	for (i = 0; i < 6; i++) {
		sum += ((data[i] == '1') ? vector[i] : 0);
	}
	printf("sum = %d\n", sum);


	srand(time(NULL));
	a = 2 + rand() % (MOD - 2);

	a_inv = inverse(a, MOD);
	
	printf("(%d)^-1 = %d mod(%d)\n", a, a_inv,MOD);
	
	for (i = 0; i < 6; i++) {
		rebuilt[i] = (vector[i] * a) % MOD;
	}

	for (i = 0; i < 6; i++) {
		printf("%d ", vector[i]);
	}
	printf(" =>  ");
	for (i = 0; i < 6; i++) {
		printf("%d ", rebuilt[i]);
	}
	printf("\n");


	srand(a);
	d0 = 2 + rand() % (MOD-2);


	srand(d0);
	d1 = 2 + rand() % (MOD - 2);


	d0_inv = inverse(d0, MOD);
	d1_inv = inverse(d1, MOD);
	printf("(%d)^-1 = %d mod(%d)\n", d0, d0_inv, MOD);

	printf("(%d)^-1 = %d mod(%d)\n", d1, d1_inv, MOD);


	for (i = 0; i < 6; i++) {
		magic(i);
		divided[i][0] = (divided[i][0] * d0) % MOD;
		divided[i][1] = (divided[i][1] * d1) % MOD;
		printf("(%d , %d) * (%d , %d)\n", divided[i][0],divided[i][1],d0_inv,d1_inv);
		if (data[i] == '1') {
			encrypted[0] = (encrypted[0] + divided[i][0]) % MOD;
			encrypted[1] = (encrypted[1] + divided[i][1]) % MOD;
		}
	}

	printf("\n\n");

	printf("%s => ", data);

	for (i = 0; i < 6; i++) {
		printf(" %c(%d %d)T ",data[i],divided[i][0],divided[i][1]);
		if (i < 5) {
			printf("+");
		}
	}

	printf(" = (%d %d)T\n", encrypted[0],encrypted[1]);

	int ans = ((encrypted[0] * d0_inv) + (encrypted[1] * d1_inv));

	printf("(%d %d)T * (%d %d) = %d ", encrypted[0], encrypted[1], d0_inv, d1_inv, ans);
	ans = ans%MOD;
	printf(" = %d mod(%d)\n", ans, MOD);
	printf("%d * %d = ", ans, a_inv);
	ans *= a_inv;
	printf("%d = ", ans);
	ans = ans%MOD;
	printf("%d mod(%d)", ans, MOD);

	if (ans < 0) {
		ans = MOD - ans;
		printf(" = %d mod(%d)",ans, MOD);
	}
		
	return 0;
}