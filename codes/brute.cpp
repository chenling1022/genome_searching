#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>


#include <ctype.h>


using namespace std;


void BruteForce(string pattern, string text)
{
    const long long n = text.size();
    const long long m = pattern.size();

    long long *sol=(long long*)malloc(n*10), solptr=0, i=0, j=0;
    for(i=0; i<n-m+1; i++)
    {
        for(j=0; j<m && text[i+j]==pattern[j]; j++);
        if(j==m)
        {
            sol[solptr] = i;
            solptr++;
        }
    }
    if(solptr==0)
    {
        printf("No solutions!\n");
    }
    else
    {
        printf("Solutions at: ");
        for(i=0; i<solptr; i++) printf("%d ", sol[i]);
        printf("\n");
    }
    free ((void*)sol);
}