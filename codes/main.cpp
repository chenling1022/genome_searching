#include <fstream>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string>
#include <time.h> 
#include <algorithm>
#include<bits/stdc++.h>
#include <locale> 
//including the algorithm files
#include "brute.cpp"
#include "kmp2.cpp"
#include "ModifiedBoyerMoore.cpp"



using namespace std;

struct GENOME
{
    string name;
    string seq;
    GENOME *next;
};

void readfile(GENOME *&genome, long long &i, char s[], long long MAXLIM)
{
    fstream f;
    cout << "\n";
    f.open(s, ios::in);
    string line, name, content;
    GENOME *temp=0;
    genome=new GENOME;
    temp =genome;
    locale loc;
    i=0;
    while (getline(f, line).good())
    {
        if (line.empty() || line[0] == '>')
        { // Identifier marker
            if (!name.empty())
            { // Print out what we read from the last entry
                //cout << name << " : " << content <<endl;
                temp->name= name;
                  for (std::string::size_type j=0; j<content.length(); ++j)
                        content.at(j)=std::toupper(content[j],loc);
                temp->seq= content;

                 i++;
                 if (i==MAXLIM)
                 {
                    temp->next=0;
                    break;
                 }
                     
                else
                {
                    temp->next = new GENOME;
                    temp = temp-> next;
                }
                
                name.clear();
            }
            if (!line.empty())
            {
                name = line.substr(1);
            }
            content.clear();
        }
        else if (!name.empty())
        {
            if (line.find(' ') != std::string::npos)
            { // Invalid sequence--no spaces allowed
                name.clear();
                content.clear();
            }
            else
            {
                content += line;
            }
        }
    }
    if (!name.empty())
    { // Print out what we read from the last entry
        //cout << name << " : " << content << endl;
        temp->name= name;
        for (std::string::size_type j=0; j<content.length(); ++j)
            content.at(j)=std::toupper(content[j],loc);
        temp->seq= content;
        temp->next=0;

    }

    if (!f.good() and !f.eof()) //don't use f.bad()
        cout << "\n\nFile not found." << endl;
    f.close();
}

int main()
{

    

    GENOME *genome=new GENOME, *temp=0;

    clock_t t_ind, t_tot, t1,t2, t3;
    long long i = 0, j;
    float total_time;
      
    char *seq=(char*)malloc(100000000);
    int choice;
    bool iter = true;
    long long lim;
    char pattern[80];
    while (iter != false)
    {
        cout << "\n*******************************\n";
        cout << " 1 - Input file\n";
        cout << " 2 - Input search String\n";
        cout << " 3 - Brute Force Algorithm\n";
        cout << " 4 - Knuth Morris Pratt Algorithm\n";
        cout << " 5 - Modified Boyer Moore Algorithm\n";
        cout << " 6 - All the Algorithms\n";
        cout << " 7 - Exit";
         cout << "\n*******************************\n";
        cout << " Enter your choice and press return: ";

        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "\nEnter name of file to open: ";
            char f_name[80];
            cin>>f_name;
            cout<<'\n';
            lim=-1;
            cout<<"Enter Max number of Sequences(-1 for all) : ";
            cin>>lim;
            i=0;
            readfile(genome, i, f_name, lim);
            cout<<"Number of sequences read:"<<i<<endl;
            break;
        case 2:
            cout<<" Enter Search string pattern :";
            cin>>pattern;
            
            break;
        case 3:
            cout << "Brute Force\n";
            temp=genome;
            j=0;
            t_tot=clock();
            while(temp!=0)
             {
                 cout<<"Sequence "<<j<<endl;
                 
                 BruteForce(pattern, temp->seq);
                 cout<<"\n";
                 temp=temp->next;
                 j++;
             }
             t_tot=clock()-t_tot;
             total_time= ((float)t_tot)/CLOCKS_PER_SEC;
             cout<<"total time for "<<i<<"sequences in the Brute Force Search = "<<total_time<<"s\n";
            break;
        case 4:
            cout << "KMP\n";
            temp=genome;
            j=0;
            t_tot=clock();
            while(temp!=0)
             {
                 cout<<"Sequence "<<j<<endl;
                 kmpSearch(pattern, temp->seq);
                 cout<<"\n";
                 temp=temp->next;
                 j++;
             }
             t_tot=clock()-t_tot;
             total_time= ((float)t_tot)/CLOCKS_PER_SEC;
             cout<<"total time for "<<i<<"sequences in the KMP Algorithm = "<<total_time<<"s\n";
            break;
        case 5:
            cout << "Boyer Moore\n";
            
            temp=genome;
            j=0;
            t_tot=clock();
            while(temp!=0)
             {
                 cout<<"Sequence "<<j<<endl;
                 j++;

                 BM(pattern, temp->seq);
                 cout<<"\n";
                 temp=temp->next;
             }
             t_tot=clock()-t_tot;
             total_time= ((float)t_tot)/CLOCKS_PER_SEC;
             cout<<"total time for "<<i<<"sequences in the modified Boyer Moore algorithm = "<<total_time<<"s\n";
            break;
        case 6:
            //BF
        cout << "Brute Force\n";
            temp=genome;
            j=0;
            t1=clock();
            while(temp!=0)
             {
                 cout<<"Sequence "<<j<<endl;

                 BruteForce(pattern, temp->seq);
                 cout<<"\n";
                 temp=temp->next;
                 j++;
             }
             t1=clock()-t1;
            //BM
            cout << "Boyer Moore\n";
            temp=genome;
            j=0;
            t2=clock();
            while(temp!=0)
             {
                 cout<<"Sequence "<<j<<endl;
                 j++;

                 BM(pattern, temp->seq);
                 cout<<"\n";
                 temp=temp->next;
             }
             t2=clock()-t2;
             
             //KMP
             cout << "KMP\n";
            temp=genome;
            j=0;
            t3=clock();
            while(temp!=0)
             {
                 cout<<"Sequence "<<j<<endl;

                 kmpSearch(pattern, temp->seq);
                 cout<<"\n";
                 temp=temp->next;
                 j++;
             }
             t3=clock()-t3;
             cout<<"total time for "<<i<<"sequences in the Brute Force Algorithm = "<<((float)t1)/CLOCKS_PER_SEC<<"s\n";
             cout<<"total time for "<<i<<"sequences in the BM Algorithm = "<<((float)t2)/CLOCKS_PER_SEC<<"s\n";
             cout<<"total time for "<<i<<"sequences in the KMP Algorithm = "<<((float)t3)/CLOCKS_PER_SEC<<"s\n";
            break;


        case 7:
            cout << "End of Program.\n";
            iter = false;
            break;
        default:
            cout << "Not a Valid Choice. \n";
            cout << "Choose again.\n";
            break;
        }
    }

    return 0;
}
