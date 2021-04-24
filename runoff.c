#include <cs50.h>
#include <stdio.h>
#include<string.h>

#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

int chart [MAX_VOTERS][MAX_CANDIDATES];

typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidates;
candidates neta[MAX_CANDIDATES];
int candidate_count;
int voter_count;

bool vote(int voter,int rank ,string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);


int main(int argc ,string argv[])
{
    if(argc<2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }
    candidate_count = argc-1;
    if(candidate_count>MAX_CANDIDATES)
    {
        printf("max candidate exceed %d",MAX_CANDIDATES);
        return 1;
    }
    voter_count =get_int("enter number of voters:");
    for(int i=0 ;i<candidate_count;i++)
    {
        neta[i].name = argv[i]+1;
        neta[i].votes = 0;
        neta[i].eliminated =false;
    }
    if(voter_count>MAX_VOTERS)
    {
        printf("max no. of voters %d reached",MAX_VOTERS);
        return 1;
    }


    for(int i=0;i<voter_count;i++)
    {
        for(int j=0;i<candidate_count;j++)
        {
           string name=get_string("rank%d\n",j+1);

           if(!vote(i,j,name))
           {
               printf("invalid vote\n");
           }
        }
    }
    while(true)
    {
        tabulate();
         bool won =print_winner();
         if(won)
         {
             break;
         }
         int min = find_min();
         bool tie = is_tie(min);
         if(tie)
         {
             for(int i=0;i<candidate_count;i++)
             {
                 if(!neta[i].eliminated)
                 {
                     printf("winners are %s",neta[i].name);
                 }
             }
             break;

         }
         eliminate(min);
         for(int i=0;i<candidate_count;i++)
         {
             neta[i].votes=0;
         }

    }
    return 0;
}
bool vote(int voter,int rank ,string name)
{
    int tabular_index=-1;
    for(int i=0;i<voter_count;i++)
    {
        if(strcmp(neta[i].name,name)==0)
        {
            tabular_index =i;
            break;
        }
    }
    if(tabular_index==-1)
    {
        return false;
    }
    chart[voter][rank]=tabular_index;
    return true;
}

void tabulate(void)
{
    for(int i=0;i<voter_count;i++)
    {
        for(int j=0;j<candidate_count;j++)
        {
             int index=chart[i][j];
             if(!neta[index].eliminated)
             {
                 neta[index].votes++;
                 break;

             }
        }
    }
    return;

}
bool print_winner(void)
{
   int max =voter_count/2;
    for(int i=0;i<candidate_count;i++)
    {
        if(!neta[i].eliminated && neta[i].votes>max)
        {
            printf("%s",neta[i].name);
            return true;
        }
    }
    return false;
}
int find_min(void)
{
    int min =neta[0].votes;
    for(int i=0;i<candidate_count;i++)
    {
        if(neta[i].votes<min)
        {
            min = neta[i].votes;
        }
    }
  return min==neta[0].votes?neta[0].votes:min;
}
bool is_tie(int min)
{
 // (2,4,4,0) ->
 int eliminated =0;
 int same_votes =0;
 int votes=0;
 for(int i=0 ;i<candidate_count;i++)
 {
     if(!neta[i].eliminated)
     {
         eliminated++;
         neta[i].votes=votes;
     }
 }
 for(int i=0;i<candidate_count;i++)
 {
     if(!neta[i].eliminated &&neta[i].votes==votes)
     {
         same_votes++;
     }
 }
 return same_votes==eliminated;
}
void eliminate(int min)
{
    for(int i=0;i<candidate_count;i++)
    {
        if( neta[i].votes==min)
        {
            neta[i].eliminated =true;
        }
    }
    return;
}