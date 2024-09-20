#include <stdio.h>
#include <stdlib.h>

int main() {
	const char* fname = "./conf/config";
	int is_ok = EXIT_FAILURE;

	printf("fname: %s\n", fname);

    FILE* fp = fopen(fname, "r");
	if (!fp){
		perror("File opening failed");
		return is_ok;
	}

	int c;
	while ((c = fgetc(fp)) != EOF)
		printf("%c", c);

	if (ferror(fp))
		puts("I/O error when reading");
	else if (feof(fp)){
		puts("End of file is reached successfully");
		is_ok = EXIT_SUCCESS;
	}

	fclose(fp);
	return is_ok;
}
