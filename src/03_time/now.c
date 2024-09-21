#include <stdio.h>
#include <time.h>
#include <locale.h>

int main() {
	time_t now = time(NULL);

	if (now != (time_t)(-1)) {
		setlocale(LC_TIME, "ja_JP.utf8");
		printf("GMT: %s", asctime(gmtime(&now)));
		printf("JST: %s", asctime(localtime(&now)));
	}
	else
		printf("something wrong");
}
