#include "s21_string.h"
//Спецификаторы PART 2: c d f s u
typedef struct Specifiers{
    int c, d;
    double f;
    char *s;
    unsigned int u;

    char *argv[BUFF];
    int len;
    int i_len;
} Specifiers;

//Ширина: (число)
//Точность: .(xbckj)
//Длина: h,l

void getINTfromString(int num, int base, Specifiers* spec){
    char tmp[BUFF] = "\0";
    int index = BUFF - 2;
    num = num > 0 ? num : -num;
    if(num == 0){
        tmp[index] = '0';
    }
    while(num > 0){
        index--;
        tmp[index] = "0123456789abcdef"[num%base];
        num/= base;
    }
    strcpy(spec->argv[spec->i_len++], tmp+index);
}

int getSpecFromLine(char format, va_list args, Specifiers *spec){
    int flag = 1;
    switch(format){
        case '*':
             
            break;
        case 'c':
            spec->c = va_arg(args, int);
            spec->argv[spec->i_len][0] = (char)spec->c;
            spec->argv[spec->i_len++][1] = '\0';
            break;
        case 'd':
            spec->d= va_arg(args, int);
            getINTfromString(spec->d, 10, spec);
            break;
        case 'f':
            spec->f = va_arg(args, double);
            gcvt(spec->f, 15, spec->argv[spec->i_len++]);
            break;
        case 's':
            spec->s = va_arg(args, char*);
            strcpy(spec->argv[spec->i_len++], spec->s);
            break;
        case 'u':
            spec->u = va_arg(args, unsigned int);
            getINTfromString(spec->u, 10, spec);
            break;
        default:
            flag = 0;
    }
    return flag;
}

void getSpecFromFormat(const char *format, va_list args, Specifiers *spec){
    char *tmp = (char *)format;
    for(;*tmp++;){
        if(*tmp ====)
        if(getSpecFromLine(*tmp, args, spec)){
            break;
        }
    }
}

void fillArr(char *argv[], int count){
    for(int i = 0; i < count; i++){
        argv[i] = (char *)calloc(BUFF, sizeof(char));
    }
}

void freeArr(char *argv[], int count){
    for(int i = 0; i < count;i++){
        free(argv[i]);
    }
}

int count_spec(const char *format){
    int count = 0;
    for(s21_size_t i = 1; i < s21_strlen(format); i++){
        if(format[i-1] == '%' && format[i] != '%'){
            count++;
        }
    }
    return count;
}

void praseArgs(const char *format, va_list args){
    Specifiers spec = {0};
    spec.len= count_spec(format);
    fillArr(spec.argv, spec.len);
    for(;*format++;){
        if(*format == '%'){
            getSpecFromFormat(format, args, &spec);
        }
    }
    for(int i = 0; i < spec.len; i++){
        printf("%s\n", spec.argv[i]);
    }

    freeArr(spec.argv, spec.len);
}


//Подставить вместо спецификатора наш input
// char *createNewString(char *str, const char *format, Specifiers spec){
//     for(; *format++; str++){

//     }
// }

//Спецификаторы PART 2: c d f s 
//Ширина: (число)
//Точность: .(xbckj)
//Длина: h,l

int s21_sprintf(char *str, const char *format, ...){
    va_list args;
    va_start(args, format);
    praseArgs(format, args);


    va_end(args);


    return 0;
}


int main() {
    char name[] = "Makar";
    int age =  20;
    char str1[BUFF] = "\0";
    s21_sprintf(str1, "Name: %s, Age: %d, float = %f %c", name, age, 3.14, '!');

    return 0;
}