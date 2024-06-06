#include "s21_sscanf.h"
#include <stdio.h>
#include <string.h>

int main() {

//   testing_sscanf("42   99", "%d %d", &s21_int1, &std_int1, 'i');

char *std_input = "99999999.19.4";
float std_float = 0.9;
int std = sscanf(std_input, "%10*lf", &std_float);

printf("%d\n%f\n\n", std, std_float);


}