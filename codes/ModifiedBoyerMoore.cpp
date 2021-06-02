#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string>
#define ALPHABET 4

using namespace std;


long long getIndex(char c)
{
    if(c=='A' || c=='a')
        return 0;
    else if(c=='C'|| c=='c')
        return 1;
    else if(c=='G'|| c=='g')
        return 2;
    else if(c=='T' || c=='U'|| c=='t'|| c=='u')
        return 3;
    else
        return -1;
}

void BadCharPrecomp(string pattern, long long m, long long badCharShift[])
{
    char c;
    long long i;
    for(i=0; i<ALPHABET; i++)
        badCharShift[i] = m;
    for(i=0; i<m - 1; i++)
    {
        c = pattern[i];
        badCharShift[getIndex(c)] = m - i - 1;
    }
}

void GoodSuffixPrecomp(string pattern, long long m, long long goodSuffShift[])
{
    //Case 1: matched pattern exists elsewhere in pattern with different prefix letter
    //similar precomputation to KMP but right to left, finding the starting index of each border of suffix
    long long i=m, j=m+1;
    long long suffixBorderStart[m+1];
    //initializing everything to 0s
    for(long long k=0; k<=m; k++)
    {
        suffixBorderStart[k] = 0;
        goodSuffShift[k] = 0;
    }
    suffixBorderStart[i]=j;  //for when border starts at last index and is empty
    while (i>0)
    {
        while (j<=m && pattern[i-1]!=pattern[j-1])  //second part makes sure that the character with the mismatch is different
        {
            if (goodSuffShift[j]==0)  //replaces old value only if it was empty i.e. 0
                goodSuffShift[j] = j-i;
            j=suffixBorderStart[j];
        }
        i--; j--;
        suffixBorderStart[i]=j;
    }
    //Case 2: only the suffix of the matched part is a prefix of the pattern
    j=suffixBorderStart[0];
    for (i=0; i<=m; i++)
    {
        if (goodSuffShift[i]==0)
            goodSuffShift[i]=j;
        if (i==j)
            j=suffixBorderStart[j];
    }
}

void BM(string pattern, string text)
{
    //printf("Text: %s\nPattern: %s\n", text, pattern);
    const long long n = text.size();
    const long long m = pattern.size();
    long long i, j, badCharShift[ALPHABET], goodSuffShift[m+1], *sol=(long long*)malloc(10*n), solptr=0;
    float netcomp = 0;
    BadCharPrecomp(pattern, m, badCharShift);
    GoodSuffixPrecomp(pattern, m, goodSuffShift);
    /* printf("Bad Character Shift Table: ");
    for(i=0; i<ALPHABET; i++)
        printf("%d ", badCharShift[i]);
    printf("\n");
    printf("Good Suffix Shift Table: ");
    for(i=0; i<m; i++)
        printf("%d ", goodSuffShift[i+1]);
    printf("\n"); */
    long long shift, comparisons, startSkip=0, resumeCheck=0;
    i = 0;
    while(i<n-m+1)
    {
        //for(j=m-1; j>=0 && pattern[j]==text[i+j]; j--);
        j = m-1;
        comparisons = 0;
        while(j>=0)
        {
            comparisons++;
            if(pattern[j]!=text[i+j]) break;
            j--;
            if(i+j==startSkip) j = resumeCheck-i;
        }
        //printf("Checking at %d; number of comparisons: %d \n", i, comparisons);
        netcomp+=comparisons;
        if(j<0)
        {
            //printf("Solution at: %d \n", i);
            sol[solptr] = i;
            solptr++;
            j=0;  // making it 0 for the shift function
        }
        
        if(goodSuffShift[j+1] >= (badCharShift[getIndex(text[i+j])] - m + 1 + j))
        {
            shift = goodSuffShift[j+1];
            startSkip = i + m - 1;
            resumeCheck = i + j;
        }
        else
        {
            shift = (badCharShift[getIndex(text[i+j])] - m + 1 + j);
            startSkip = i + j;
            resumeCheck = i + j - 1;
        }
        i+=shift;
        //printf("Shift by %d \n", shift);
    }
    if(solptr==0) printf("No Solutions!");
    else{
        printf("\n\nSolutions at: ");
        for(long long k=0; k<solptr; k++) printf("%d ", sol[k]);
    }

    free ((void*)sol);
    //printf("\nTotal comparisons: %0.0f = %0.2fn \n\n", netcomp, (netcomp/n));
}

/* int main()
{
    //char *pattern = "GCAGAGAG";
    //char *pattern = "TTTATACCTTCC";
    char *pattern = "AATAT";
    //char *text = "GCATCGCAGAGAGTATACAGTACG";
    //char *text = "ATTAAAGGTTTATACCTTCCCAGGTAACAAACCAACCAACTTTCGATCTCTTGTAGATCTGTTCTCTAAACGAACTTTAAAATCTGTGTGGCTGTCACTCGGCTGCATGCTTAGTGCACTCACGCAGTATAATTAATAACTAATTACTGTCGTTGACAGGACACGAGTAACTCGTCTATCTTCTGCAGGCTGCTTACGGTTTCGTCCGTGTTGCAGCCGATCATCAGCACATCTAGGTTTCGTCCGGGTGTGACCGAAAGGTAAGATGGAGAGCCTTGTCCCTGGTTTCAACGAGAAAACACACGTCCAACTCAGTTTGCCTGTTTTACAGGTTCGCGACGTGCTCGTACGTGGCTTTGGAGACTCCGTGGAGGAGGTCTTATCAGAGGCACGTCAACATCTTAAAGATGGCACTTGTGGCTTAGTAGAAGTTGAAAAAGGCGTTTTGCCTCAACTTGAACAGCCCTATGTGTTCATCAAACGTTCGGATGCTCGAACTGCACCTCATGGTCATGTTATGGTTGAGCTGGTAGCAGAACTCGAAGGCATTCAGTACGGTCGTAGTGGTGAGACACTTGGTGTCCTTGTCCCTCATGTGGGCGAAATACCAGTGGCTTACCGCAAGGTTCTTCTTCGTAAGAACGGTAATAAAGGAGCTGGTGGCCATAGTTACGGCGCCGATCTAAAGTCATTTGACTTAGGCGACGAGCTTGGCACTGATCCTTATGAAGATTTTCAAGAAAACTGGAACACTAAACATAGCAGTGGTGTTACCCGTGAACTCATGCGTGAGCTTAACGGAGGGGCATACACTCGCTA";
    char *text = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAATAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAATAT";
    BM(pattern, text);
    return 0;
} */
