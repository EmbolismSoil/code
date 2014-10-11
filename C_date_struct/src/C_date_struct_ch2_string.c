#include <stdio.h>
#include <string.h>

int nfind(char *str, char *pat)
{
    int lasts = strlen(str) - 1;
    int lastp = strlen(pat) - 1;
    int endmatch = lastp;
    int start = 0;
    
    int i;
    for (; endmatch <= lasts; start++, endmatch++){
      if (str[start] == pat[0] && 
		str[endmatch] == pat[lastp]){
        for (i = 0; i < lastp && 
		str[start + i] == pat[i]; i++);
        if(i == lastp)
	    return start + 1;
      }
    }
    return -1;    
}

int main(int argc, char *argv[])
{
    printf("the pos : %d\n",nfind(argv[1],argv[2])); 
    return 0;
}
