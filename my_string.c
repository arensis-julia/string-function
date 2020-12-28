#include "my_string.h"
#include <stdlib.h>

#define isspace(ch) ((ch) == ' ' || (ch) == '\t' || (ch) == '\n' || \
					 (ch) == '\v' || (ch) == '\f' || (ch) == '\r')

/* CONVERT STRING TO NUMERIC FORMAT */
int atoi(const char * str) {
    int len = strlen(str);
    int sign = 1;
    int front_sp = 0;
    int num = 0;
    int i;

    i = 1;
    if(str[0] == '-')   sign = -1;
    else if(str[0] == '+')  sign = 1;
    else    i = 0;

    for(; i<len; i++) {    
        if(isspace(str[i])) {
            if(front_sp != i)
                return sign * num;
            front_sp++;
            continue;
        }
        if(str[i] < '0' || str[i] > '9')
            return sign * num;

        num *= 10;
        num += str[i] - '0';
    }

    return sign * num;
}

long atol(const char * str) {
    int len = strlen(str);
    int sign = 1;
    int front_sp = 0;
    long num = 0;
    int i;

    i = 1;
    if(str[0] == '-')   sign = -1;
    else if(str[0] == '+')  sign = 1;
    else    i = 0;

    for(; i<len; i++) {    
        if(isspace(str[i])) {
            if(front_sp != i)
                return sign * num;
            front_sp++;
            continue;
        }
        if(str[i] < '0' || str[i] > '9')
            return sign * num;

        num *= 10;
        num += str[i] - '0';
    }

    return sign * num;
}


/* CONVERT NUMERIC FORMAT TO STRING */
char * int2str(char * dest, int num) {
    unsigned int mag;
    int sign = 0;
    int len;
    int i=0, j;

    if(*dest == '\0') {
        dest = calloc(12, sizeof(char));
        if(*dest == '\0') return '\0';
    }

    if(num == 0) {
        dest[0] = '0';
        dest[1] = 0;
        return dest;
    }
    if(num < 0) {
        dest[0] = '-';
        mag = num * -1;
        sign = 1;
        i++;
    }
    while(mag) {
        dest[i] = mag % 10 + '0';
        mag /= 10;
        i++;
    }

    len = i - sign;
    for(j=0; j<len/2; j++)      dest[i-1-j] ^= dest[j+sign] ^= dest[i-1-j] ^= dest[j+sign];

    dest[i] = 0;

    return dest;
}


/* STRING MANIPULATION */
char * strcpy(char * dest, const char * src) {
    char * s = (char *)src;
    char * d = dest;

    while(*s != '\0') {
        *d = *s;
        s++;
        d++;
    }
    *d = '\0';
    
    return dest;
}

char * strncpy(char * dest, const char * src, size_t n) {
    char * s = (char *)src;
    char * d = dest;
    int len = strlen(src);
    int min = len > n ? n : len;
    int i;

    for(i=0; i<min; i++) {
        *d = *s;
        s++;
        d++;
    }
    for(i=len; i<n; i++) {
        *d = 0;
        d++;
    }

    return dest;
}

char * strcat(char * dest, const char * src) {
    char * s = (char *)src;
    char * d = dest;

    while(*d != '\0')   d++;
    while(*s != '\0') {
        *d = *s;
        d++;
        s++;
    }
    *d = 0;

    return dest;
}

char * strncat(char * dest, const char * src, size_t n) {
    char * s = (char *)src;
    char * d = dest;
    int i;

    while(*d != '\0')   d++;
    for(i=0; i<n; i++) {
        *d = *s;
        d++;
        s++;
    }
    *d = 0;

    return dest;
}

char * strdup(const char * str) {
    int len = strlen(str);
    char * c = calloc(len, sizeof(char));

    if(*c == '\0')   return '\0';
    return strcpy(c, str);
}


/* STRING EXAMINATION */
size_t strlen(const char * str) {
    char * c = (char *)str;
    int len = 0;

    while(*c != '\0') {
        len++;
        c++;
    }

    return len;
}

int strcmp(const char * str1, const char * str2) {
    char * s1 = (char *)str1;
    char * s2 = (char *)str2;

    while(*s1 != '\0' && *s2 != '\0') {
        if(*s1 > *s2)   return 1;
        if(*s1 < *s2)   return -1;
        s1++;
        s2++;
    }
    if(*s1 != '\0')   return 1;
    if(*s2 != '\0')   return -1;

    return 0;
}

int strncmp(const char * str1, const char * str2, size_t n) {
    char * s1 = (char *)str1;
    char * s2 = (char *)str2;
    int i = 0;

    while(*s1 != '\0' && *s2 != '\0' && i < n) {
        if(*s1 > *s2)   return 1;
        if(*s1 < *s2)   return -1;
        s1++;
        s2++;
        i++;
    }
    if(i < n && *s1 != '\0')   return 1;
    if(i < n && *s2 != '\0')   return -1;

    return 0;
}

char * strchr(const char * str, int c) {
    char * s = (char *)str;

    while(*s != '\0') {
        if(*s == c)     return s;
        s++;
    }
    if(*s == c)     return s;

    return '\0';
}

char * strrchr(const char * str, int c) {
    int len = strlen(str);
    char * s = (char *)str + len;

    while(s >= str) {
        if(*s == c) return s;
        s--;
    }

    return '\0';
}

char * strpbrk(const char * str1, const char * str2) {
    char * s1 = (char *)str1;
    char * s2 = (char *)str2;

    while(*s1 != '\0') {
        while(*s2 != '\0') {
            if(*s1 == *s2)      return s1;
            s2++;
        }
        s2 = (char *)str2;
        s1++;
    }

    return '\0';
}

char * strstr(const char * haystack, const char * needle) {
    char * h = (char *)haystack;
    char * n = (char *)needle;
    char * s = h;
    int nLen = strlen(needle);
    
    if(*needle == '\0')     return (char *)haystack;
    while(*h != '\0') {
        if(strlen(h) < nLen)    return '\0';
        for(s=h, n=(char *)needle; *n!='\0'; s++, n++) {
            if(*s != *n)    break;
        }
        if(*n = '\0')
            return h;
        h++;
    }

    return '\0';
}

char * strtok(char * str, const char * delim) {
    char * s = str;
    char * d = (char *)delim;
    static char *next = '\0';       // for next token
    
    if(*str == '\0')     str = next;
    if(*str == '\0')     return '\0';
    
    s = str;
    while(*s != '\0') {
        while(*d != '\0') {
            if(*s == *d)    break;
            d++;
        }
        if(*d == '\0')  break;
        s++;
        d = (char *)delim;
    }
    if(*s == '\0') {
        next = '\0';
        return '\0';
    }

    str = s;
    d = (char *)delim;
    while(*s != '\0') {
        while(*d != '\0') {
            if(*s == *d) {
                *s = 0;
                next = s + 1;
                return str;
            }
            d++;
        }
        d = (char *)delim;
        s++;
    }
    next = '\0';

    return str;
}

char * strtok_r(char * str, const char * delim, char ** save_ptr) {
    char * s = str;
    char * d = (char *)delim;

    if(*str == '\0')     str = *save_ptr;
    if(*str == '\0')     return '\0';

    s = str;
    while(*s != '\0') {
        while(*d != '\0') {
            if(*s == *d)    break;
            d++;
        }
        if(*d == '\0')  break;
        s++;
        d = (char *)delim;
    }
    if(*s == '\0') {
        *save_ptr = '\0';
        return '\0';
    }

    str = s;
    d = (char *)delim;
    while(*s != '\0') {
        while(*d != '\0') {
            if(*s == *d) {
                *s = 0;
                *save_ptr = s + 1;
                return str;
            }
            d++;
        }
        d = (char *)delim;
        s++;
    }
    *save_ptr = '\0';

    return str;
}


/* ARRAY MANIPULATION */
void * memcpy(void * dest, const void * src, size_t n) {
    int i;
    
    for(i=0; i<n; i++) {
        *((unsigned char *)(dest) + i) = *((unsigned char *)(src) + i);
    }

    return dest;
}

void * memset(void * str, int c, size_t n) {
    int i;

	for(i=0;i<n;i++) {
		*((unsigned char *)(str) + i) = c;
	}

	return str;
}