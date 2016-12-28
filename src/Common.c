
#include "Common.h"
#include <stdio.h>

//Simple, mockable wrapper around printf. (Format conversions out of scope for this exercise.)
int CommonOutput(const char *str) {
	return printf("%s\n", str);
}

