#include <stdio.h>
#include <assert.h>
#include "str.h"


size_t Str_getLength(const char pcSrc[]){
    
    size_t count = 0;
    const char *temp = pcSrc;

    assert(pcSrc != NULL);

    while (*temp != '\0') {
        count ++;
        temp ++;
    }
    return count;
}

char *Str_copy(char dest[], const char source[]) {

    char *tempd = dest;
    const char *temps = source;


    assert(dest != NULL)
    assert(source != NULL);

    while (*temps != '\0') {
        *tempd = *temps;
        tempd ++;
        temps++;
    }

    *tempd = '\0';

    return dest;
}

char *Str_concat(char dest[], const char source[]) {

        char *tempd = dest + Str_getLength(dest);
    const char *temps = source;

    assert(dest != NULL);
    assert(source != NULL);

    while (*temps != '\0') {
        *tempd = *temps;
        tempd ++;
        temps ++;
    }

    *tempd = '\0';
    
    return dest;

}

int Str_compare(const char s1[], const char s2[]) {

    const char *temp1 = s1;
    const char *temp2 = s2;
    
    assert(s1 != NULL);
    assert(s2 != NULL);

    while(*temp1 != '\0' || *temp2 != '\0') {
        
        if (*temp1 > *temp2) return 1;
        if (*temp1 < *temp2) return -1;
        
        temp1 ++;
        temp2 ++;
    }

    return 0;
}

static int search(const char haystack[], const char needle[]) {
    const char *temp1 = haystack;
    const char *temp2 = needle;

    while (*temp1 != '\0' && *temp2 != '\0') {
        if (*temp1 != *temp2) return 0;
        
        temp1 ++;
        temp2 ++;
    }

    if (*temp2 == '\0') return 1;

    return -1;
}

char *Str_search(const char haystack[], const char needle[]) {

    const char *tempneedle = needle;
    const char *temphaystack = haystack;

    assert(haystack != NULL);
    assert(needle != NULL);

    if (*needle == '\0') return haystack;

    while(*temphaystack != '\0') {
        
        if (*tempneedle == *temphaystack) {
            
            int retval = search(temphaystack, tempneedle);

            if (retval == 1) return (char *) temphaystack;

            else if (retval == 0) {
                temphaystack ++;
                continue;
            }

            else return NULL;

        }
        temphaystack ++;
    }

    return NULL;

}


