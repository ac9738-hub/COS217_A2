/*--------------------------------------------------------------------*/
/* stra.c                                                          */
/* Author: Allen Chen                                               */
/*--------------------------------------------------------------------*/


#include <stdio.h>
#include <assert.h>
#include "str.h"


size_t Str_getLength(const char pcSrc[]){

    size_t count = 0;
    
    assert(pcSrc != NULL);
    
    while(pcSrc[count] != '\0') {
        count++;
    }

    return count;
}

char *Str_copy(char dest[], const char source[]) {

    size_t count = 0;

    assert(dest != NULL);
    assert(source != NULL);
    
    while (source[count] != '\0') {
        dest[count] = source[count];
        count ++;
    }

    dest[count] = '\0';

    return dest;
}

char *Str_concat(char dest[], const char source[]) {

    size_t count1 = 0;
    size_t count2 = 0;

    assert(dest != NULL);
    assert(source != NULL);

    while (dest[count1] != '\0') count1 ++;

    while (source[count2] != '\0') {
        dest[count1] = source[count2];
        count1 ++;
        count2 ++;
    }

    dest[count1] = '\0';

    return dest;
}

int Str_compare(const char s1[], const char s2[]) {

    size_t count = 0;

    assert(s1 != NULL);
    assert(s2 != NULL);

    while (s1[count] != '\0' && s2[count] != '\0') {
        if(s1[count] < s2[count]) return -1;
        if(s1[count] > s2[count]) return 1;
        
        count ++;
    }

    if (s1[count] == s2[count]) return 0;

    else if (s1[count] == '\0') return -1;

    return 1;

}
/* determine whether needle is at this index of haystack. Return 1 if yes
0, if no, -1 if remaining haystack is shorter than needle */
static int Str_searcher(const char haystack[], const char needle[], size_t count) {

    assert(haystack != NULL);
    assert(needle != NULL);

    size_t count1 = 0;

    while (haystack[count + count1] != '\0' && needle[count1] != '\0') {
        if (haystack[count + count1] != needle[count1]) return 0;
        
        count1++;
    }

    if ( needle[count1] == '\0') return 1;

    return -1;
}

char *Str_search(const char haystack[], const char needle[]) {

    size_t count = 0;

    assert(haystack != NULL);
    assert(needle != NULL);

    if (needle[0] == '\0') return (char *) haystack;

    while(haystack[count] != '\0') {
        if(haystack[count] == needle[0]) {

            int val = Str_searcher(haystack, needle, count);
            if (val == 1) return (char *)&haystack[count];
            
            else if (val == 0){
                count ++;
                continue;
            } 

            return NULL;
        }
        
        count ++;
    }

    return NULL;    
}

