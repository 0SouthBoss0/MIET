#include "revert_string.h"
#include <string.h>

void RevertString(char *str)
{
	int length = strlen(str);
	for (int i = 0; i < length / 2; i++)
	{
		char temp = str[i];
		str[i] = str[length - 1 - i];
		str[length - 1 - i] = temp;

	}
}

