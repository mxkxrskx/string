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

void getNUMfromString(int num, int base, Specifiers* spec){
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
    strcat(spec->argv[spec->i_len++], tmp+index);
}

void set_spaces(char *format, int *spaces, va_list args){
    format--;
    if(*(format) == '*'){
        *spaces = va_arg(args, int);
    }
    else if(isdigit(*format) && *format-- != '.'){

        char* tmp = format;
        while((isdigit(*tmp))){
            tmp--;
        }
        *spaces = s21_atoi(++tmp);
    }
}

void procces_width_d(int spaces, Specifiers *spec){
    if((spaces -= (int)log10(spec->d)+1) > 0){
        s21_memset(spec->argv[spec->i_len], ' ', spaces);
        spec->argv[spec->i_len][spaces+1] = '\0';
    }
}

int getSpecFromLine(char *format, va_list args, Specifiers *spec){
    bool flag = 1;
    char *tmp = format;
    int spaces = 0;
    switch(*tmp){
        case 'c':
            spec->c = va_arg(args, int);
            spec->argv[spec->i_len][0] = (char)spec->c;
            spec->argv[spec->i_len++][1] = '\0';
            break;
        case 'd':
            set_spaces(tmp, &spaces, args);
            spec->d= va_arg(args, int);
            procces_width_d(spaces, spec);
            getNUMfromString(spec->d, 10, spec);
            spaces = 0;
            break;
        case 'f':
            set_spaces(tmp, &spaces, args);
            //не работает 3.14 -> 3.140000
            //printf("%f", spec->f);
            spec->f = va_arg(args, double);
            printf("%f", spec->f);
            break;
        case 's':
            spec->s = va_arg(args, char*);
            strcpy(spec->argv[spec->i_len++], spec->s);
            break;
        case 'u':
            set_spaces(tmp, &spaces, args);
            spec->u = va_arg(args, unsigned int);
            getNUMfromString(spec->u, 10, spec);
            break;
        default:
            flag = 0;
    }
    return flag;
}

void getSpecFromFormat(const char *format, va_list args, Specifiers *spec){
    char *tmp = (char *)format;
    for(;*tmp++;){
        if(getSpecFromLine(tmp, args, spec)){
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
    sprintf(str1, "Name: %s, Age: %5d, float = %10.1f %c", name, age, 3.0, '!');
    printf("%s", str1);
    
    
    // long double pi = 3.14;
    // printf("%Lf\n", pi);

    // long double left = 0.0;
    // long double right = modfl(pi, &left);
    // printf("%d, %Lf\n", (int)left, right);
    // while
    return 0;

}