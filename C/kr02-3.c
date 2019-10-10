#include<stdio.h>
void int_fr_str(char *string) {
    int sign = 1;
    if (*string == '-') {
    	sign = -1;
	++string;
    }
    int digits = 1;
    int digit = -'0';
    int answer = 0;
    int max = 15;
    int min = -10;
    while (*string) {
        while(*string && *string != ',') {
    	    digit += *string;
	    answer += digit * digits;
	    digits *= 10;
	    digit = -'0';
	    /*printf("%d ", answer);*/
	    ++string;
        }
	answer *= sign;
	printf("%d ", answer);
	if (answer > max) {
	    max = answer;
	}
	if (answer < min) {
	    min = answer;
	}
	answer = 0;
	digits = 1;
    }
    answer = max - min + 1;
    printf("%d\n", answer);
}

int main() {
    char * string = "1,2,3,4,5";
    int_fr_str(string);
    return 0;
}
