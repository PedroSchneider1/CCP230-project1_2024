#include <stdio.h>

void limpaBuffer(){
    char c;
    while((c = getchar()) != '\n' && c != EOF);
}
