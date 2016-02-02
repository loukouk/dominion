#include <stdio.h>

void myassert(int val) {
	if (val)
		printf("PASSED.\n");
    else
		printf("FAILED.\n");
	return;
}
