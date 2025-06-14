#include "swap.h"

void Swap(char *left, char *right){
	char a = *left;
	*left = *right;
	*right = a; 
}
