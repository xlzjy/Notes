#include "stack.h"

int main(void)
{
    char inputarray[InputMaxSize];
    int l = Input_Array(inputarray, InputMaxSize);

    char *s = generate_expression(inputarray, l);
    printf("%s\n", s);
}
