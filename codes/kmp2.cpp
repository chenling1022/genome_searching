#include <stdio.h>
#include <string.h>
#include <string>

using namespace std;

void KMP_preprocess(string pattern , long long M, long long *lps)
{
    long i=0;
    long j=-1;
    lps[i]=j;
    for (i=0; i<M; )
    {
        while (j>=0 && pattern[i]!=pattern[j])
            j=lps[j];
        i=i+1;
        j=j+1;
        lps[i]=j;
    }
}



void kmpSearch(string pattern, string text)
{
    const long long N = text.size();
    long long *sol=(long long*)malloc(N*10), solptr=0; 
    long long M = pattern.size();
    long long i=0, j=0;
    long long lps[M];

    KMP_preprocess(pattern, M, lps);

    while (i<N)
    {
        while (j>=0 && text[i]!=pattern[j]) 
            j=lps[j];
        i++; j++;
        if (j==M)
        {
            sol[solptr] = i-j;
            solptr++;
            j=lps[j];
        }
    }
    if(solptr==0) printf("No Solutions!");
    else{
        printf("\n\nSolutions at: ");
        for(long long k=0; k<solptr; k++) printf("%d ", sol[k]);
    }
    free ((void*)sol);
}