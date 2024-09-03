#include "../libc/include/int.h"
#include <stdint.h>
#include <stdbool.h>

int count_digits(int number) {
    int count = 0;

    // Handle negative numbers
    if (number < 0) {
        number = -number;
    }

    // Handle the special case when the number is 0
    if (number == 0) {
        return 1;
    }

    // Count the number of digits
    while (number > 0) {
        number /= 10;
        count++;
    }

    return count;
}

char* to_string(int num) {
    int num_digits = count_digits(num);
    bool is_negative = num < 0;
    // Allocate memory for the string (+1 for the null terminator and +1 for the negative sign if needed)
    char* str = (char*)malloc(num_digits + is_negative + 1);
    int i = 0;
    int sign = num;

    if (num < 0) {
        num = -num;
    }
    
    do {
        str[i++] = num % 10 + '0';
    } while ((num /= 10) > 0);

    if (sign < 0) {
        str[i++] = '-';
    }
    str[i] = '\0';

    // Reverse the string
    for (int j = 0, k = i - 1; j < k; j++, k--) {
        char temp = str[j];
        str[j] = str[k];
        str[k] = temp;
    }

    return str;
}