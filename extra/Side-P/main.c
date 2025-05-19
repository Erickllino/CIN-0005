#include <stdio.h>
FILE *fptr;





int main(){

	fptr = fopen("test.txt", "r");
	char test[100];

	fgets(test, 100, fptr);
	printf("%s", test);

	
	fclose(fptr);
	return 0;
}
