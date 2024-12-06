#include <stdio.h>

int main() {
    char str[100];
    scanf("%s", str);
    int number1;
    int number2;
    int value = sscanf(str, "%d | %d", &number1, &number2);
    printf("%d, %d\n", number1, number2);
    printf("value = %d\n", value);
}