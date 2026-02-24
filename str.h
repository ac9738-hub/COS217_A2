#ifndef STR_H
#define STR_H

#include <stddef.h>

/* returns the number of characters in the string pcSrc,
not including the terminating null character.
pcSrc must not be null */
size_t Str_getLength(const char pcSrc[]);

/* Takes 2 string arguments dest and source with source being the source
string and dest being the destination string. Copies all of
source string including the null terminator into destination
string. Does not check destination string bounds. Returns address of dest */
char *Str_copy(char dest[], const char source[]);

/* Takes 2 string arguments source and dest. appends source to dest
with the first character of source replacing the null terminator and
adds an additional null terminator to the end of the new string. 
Does not work if there is not enough memory at dest to hold new 
string returns address of dest */
char *Str_concat(const char dest[], char source[]);

/* Takes 2 string arguments s1 and s2. compares the two 
lexicographically and returns an int.
Returns negative if s1 < s2
Returns 0 if equal
Returns positive if s1 > s2 */
int Str_compare(const char s1[], const char s2[]);

/* Takes 2 string arguments needle and haystack.
Finds first occurence of substring needle inside haystack 
Returns pointer to first matching position or NULL if
none exist*/
char *Str_search(const char haystack[], const char needle[]);

#endif


