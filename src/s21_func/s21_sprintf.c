#include "s21_string.h"
//Спецификаторы PART 2: c d f s u
typedef struct Specifiers{
    int c, d;
    double f;
    char *s;
    unsigned int u;
} Specifiers;


bool s21_isdigit(char c){
    return (c >= '0' && c <= '9');
}


void getNUMfromString(int num, int base, Specifiers* spec){
    char tmp[BUFF] = "\0";
    int index = BUFF - 2;
    int temp = num;
    num = num > 0 ? num : -num;
    if(num == 0){
        tmp[index] = '0';
    }
    while(num > 0){
        index--;
        tmp[index] = "0123456789abcdef"[num%base];
        num/= base;
    }
    if(temp < 0){
        tmp[--index] = '-';
    }
    //поменять на свой
    strcat(spec->argv[spec->i_len++], tmp+index);
}
void getFLOATfromString(double f, Specifiers *spec){
    long double left = 0.0;
    long double right = modfl(f, &left);
    getNUMfromString((int)left, 10, spec);
    spec->i_len--;
    int count = 0;
    while(count != 6){
        right*=10;
        count++;
    }
    strcat(spec->argv[spec->i_len], ".");
    getNUMfromString((int)right, 10, spec);
}

void set_spaces(char *format, int *spaces, va_list args){
    char *tmp = format;
    tmp++;
    if(*(tmp) == '*'){
        *spaces = va_arg(args, int);
    }
    else if(isdigit(*tmp) && *tmp++ != '.'){
        while((s21_isdigit(*tmp))){
            tmp--;
        }
        *spaces = s21_atoi(++tmp);
    }
}


void input_spaces(Specifiers *spec, int spaces){
    s21_memset(spec->argv[spec->i_len], ' ', spaces);
    spec->argv[spec->i_len][spaces+1] = '\0';
}

void is_negative(int num, int *spaces){
    if(num < 0.0){
        *spaces += 1;
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
            is_negative(spec->d, &spaces);
            getNUMfromString(spec->d, 10, spec);
            break;
        case 'f':
            set_spaces(tmp, &spaces, args);
            spec->f = va_arg(args, double);
            getFLOATfromString(spec->f, spec);
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

int count_spec(const char *format){
    int count = 0;
    for(s21_size_t i = 1; i < s21_strlen(format); i++){
        if(format[i-1] == '%' && format[i] != '%'){
            count++;
        }
    }
    return count;
}

// void praseArgs(const char *format, va_list args){
//     for(;*format++;){
//     }



//     for(int i = 0; i < spec.len; i++){
//         printf("%s = %lu\n", spec.argv[i], s21_strlen(spec.argv[i]));
//     }

//     freeArr(spec.argv, spec.len);
// }


//Подставить вместо спецификатора наш input
// char *createNewString(char *str, const char *format, Specifiers spec){
//     for(; *format++; str++){

//     }
// }

//Спецификаторы PART 2: c d f s 
//Ширина: (число)
//Точность: .(xbckj)
//Длина: h,l
//* 5678d

int s21_sprintf(char *str, const char *format, ...){
    va_list args;
    va_start(args, format);

    char temp[BUFF] = "\0";
    int spaces = 0;
    for(;*format;){
        if(*format == '%'){
            set_spaces(format, &spaces, args);
        }
    }
    va_end(args);

    return 0;
}


int main() {
    int age =  -20;
    char str1[BUFF] = "\0";
    s21_sprintf(str1, "Age = %d %u %5f", age, 20, 3.14);
    //sprintf(str1, "%4d", age);
    //printf("%s", str1);

    
    return 0;

}