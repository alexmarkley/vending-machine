
#include "Common.h"
#include <stdio.h>

//Simple, mockable wrapper around printf. (Format conversions out of scope for this exercise.)
int CommonOutput(const char *str) {
	return printf("%s\n", str);
}

//Mockable wrapper around scanf. (Again, format conversions are out of scope here.)
//This also may be untestable from a unit test perspective, because scanf() can't be mocked, and anything more involved would be an integration test.
char CommonInput(void) {
	char c = '\0';
	scanf("%c", &c);
	return c;
}

