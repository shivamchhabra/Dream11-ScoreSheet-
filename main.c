#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
char name[20];
int score;
int runs;
struct node *next;
};
struct node *top1=NULL;
struct node *top2=NULL;
struct node *bats1,*bats2;
struct node *bowler=NULL;
struct node *forward;
struct node *onstrike;
int score=0;
int scorea=0;



struct node* push(struct node *top,char Name[20])
{

    struct node *temp=(struct node*)malloc(sizeof(struct node));

    strcpy(temp->name,Name);
    temp->runs=0;
    temp->score=0;
    if(top==NULL)
    {
      top=temp;
      temp->next=NULL;
    }else
    {
        struct node *temp2=top;
        while(temp2->next!=NULL)
        {
            temp2=temp2->next;
        }
        temp2->next=temp;
    }
    return top;
}



void checkbowler(struct node *top)
{
    char naam[20];
    scanf("%s", &naam);
    struct node *temp=top;
    int count=0;
    while(temp!=NULL)
    {
        if (strcmp(temp->name,naam)==0)
        {
            bowler=temp;
            return;
        }
        temp=temp->next;
    }
    printf("put valid name\n");
    checkbowler(top);
}


void scoresheet()
{
    struct node *temp1=top1, *temp2=top2;
    while(temp1!=NULL && temp2!=NULL)
    {
        printf("\n%s:%d \t %s:%d\n", temp1->name,temp1->score,temp2->name,temp2->score);
        temp1=temp1->next;
        temp2=temp2->next;
    }
}

struct node* checkbatsman(struct node *bat,struct node *top)
{
    if (forward==NULL )
    {
        bat=top;
        forward=top;
    }
    else
    {
        bat=forward->next;
        forward=forward->next;
    }
    return bat;
}

void reversestrike()
{
    if(onstrike==bats1)
    {
        onstrike=bats2;
    }
    else
    {
        onstrike=bats1;
    }
}




void boundary()
{
        score+=4;
        onstrike->runs=onstrike->runs+4;
        onstrike->score=onstrike->score+4;
}

void six()
{
        score+=6;
        onstrike->runs=onstrike->runs+6;
        onstrike->score=onstrike->score+6;
}
void bowled()
{

    bowler->score+=20;
    if(onstrike==bats1)
    {
        bats1=forward->next;
        forward=forward->next;
        onstrike=bats1;
    }else
    {
        bats2=forward->next;
        forward=forward->next;
        onstrike=bats2;
    }


}


void runout()
{
    printf("NO of runs completed before run out...");
    int runs;
    scanf("%d", &runs);
    onstrike->runs+=runs;
    onstrike->score+=runs;
    score+=runs;
    if(runs%2==0)
    {
        reversestrike();
    }
    printf("who got runout");
    char Name[20];
    scanf("%s", &Name);
    int count=1;
    if(onstrike==bats1)
    {
        count=1;
    }
    else
    {
        count=2;
    }
    if(strcmp(bats1->name, Name)==0)
    {
      bats1=forward->next;
      forward=forward->next;
    }
    else if(strcmp(bats2->name, Name)==0)
    {
        bats2=forward->next;
        forward=forward->next;
    }
    if(count==1)
    {
       onstrike=bats1;
    }
    else
    {
        onstrike=bats2;
    }

}

void wide()
{
  score++;
}

void single()
{

    score=score+1;
    onstrike->runs=onstrike->runs+1;
    onstrike->score=onstrike->score+1;
    reversestrike();
}

void twos()
{

    score=score+2;
    onstrike->runs=onstrike->runs+2;
    onstrike->score=onstrike->score+2;
}

void threes()
{

    score=score+3;
    onstrike->runs=onstrike->runs+3;
    onstrike->score=onstrike->score+3;
    reversestrike();
}


void cach(struct node *head)
{
    printf("who got catch?");
    char Name[20];
    scanf("%s", & Name);
    struct node *temp=head;
    while(temp!=NULL)
    {

        if(strcmp(temp->name, Name)==0)
        {

            temp->score+=10;
            bowler->score+=10;
            break;
        }
        temp=temp->next;

    }
    if(onstrike==bats1)
    {
        bats1=forward->next;
        onstrike=bats1;
        forward=forward->next;

    }
    else
    {
        bats2=forward->next;
        onstrike=bats2;
        forward=forward->next;

    }
    printf("Strike chaged or not? 1-no 2-yes");
    int cc;
    scanf("%d", &cc);
    if(cc==2)
    {
        reversestrike();
    }
}


void scoreboard()
{
    printf("Batsman 1 \t name:%s \t score:%d \nBatsman2 \t name:%s \t score:%d \nOnstrike \t name:%s", bats1->name, bats1->runs, bats2->name, bats2->runs, onstrike->name);
}



int main()
{
    int nop,teamid=0,count=0;
    printf("No of players playing...\n");
    scanf("%d", &nop);
   while(count!=nop)
    {
        char Name[20];
        printf("Name of %d th player in first batting team...\n", ++count);
        scanf("%s", & Name);
        top1=push(top1, Name);

    }
    count=0;

    while(count!=nop)
    {
        printf("Name of %d th player in second batting team...\n", ++count);
        char Name[20];
        scanf("%s", & Name);
        top2=push(top2, Name);

    }


    struct node *temp=top1;
    printf("Name of players in first batting team");
    while(temp!=NULL)
    {
        printf(" %s", temp->name);
        temp=temp->next;
    }
    temp=top2;
    printf("\nName of players in second batting team");
    while(temp!=NULL)
     {
        printf(" %s", temp->name);
        temp=temp->next;
     }


    bats1=NULL;
    bats1=checkbatsman(bats1,top1);
    bats2=checkbatsman(bats2,top1);
    onstrike=bats1;


    printf("\nNO of overs in Match...\n");
    int overs,ovdone=0;
    scanf("%d", &overs);
    while(ovdone<overs)
    {
        printf("Enter the bowler bowling...\n");
        checkbowler(top2);
        int balls=1;
        while(balls<=6)
        {
            printf("\nbowl:%d.%d  \t Totalscore:%d \n", ovdone, balls, score);
            printf("%s is now onstrike and his score is %d\n", onstrike->name, onstrike->runs);
            printf("press 0-Dotball 1-single 2-twos 3-threes 4-boundary 5-catch 6-six 7-Scoreboard 8-runout 9-bowled 10-wide 11-scoresheet\n");
            int check;
            scanf("%d", &check);
            switch(check)
            {
                case 0:
                    balls++;
                    break;
                case 1:
                    single();
                    balls++;
                    break;
                case 2:
                    twos();
                    balls++;
                    break;
                case 3:
                    threes();
                    balls++;
                    break;
                case 4:
                    boundary();
                    balls++;
                    break;
                case 5:
                    cach(top2);
                    balls++;
                    break;
                case 6:
                    six();
                    balls++;
                    break;
                case 7:
                    scoreboard();
                    break;
                case 8:
                    runout();
                    balls++;
                    break;
                case 9:
                    bowled();
                    balls++;
                    break;
                case 10:
                    wide();
                    break;
                case 11:
                    scoresheet();
                    break;
                default:
                    printf("Please input valid numbers...");

             }
             if(forward==NULL)
             {

                 break;
             }

        }
         if(forward==NULL)
             {

                 break;
             }
        ovdone++;
        reversestrike();
        printf("\n");
    }


    printf("Your Total Score is %d", score);
    forward=NULL;
    scorea=score;
    score=0;
    bats1=NULL;
    bats1=checkbatsman(bats1,top2);
    bats2=checkbatsman(bats2,top2);
    onstrike=bats1;
    ovdone=0;

    printf("\n\nSECOND INNINGS STARTS HERE... required score is:%d\n\n", scorea+1);

    while(ovdone<overs)
    {
        printf("Enter the bowler bowling...\n");
        checkbowler(top1);
        int balls=1;
        while((balls<=6) && (score<scorea))
        {
            printf("\nbowl:%d.%d  \t Totalscore:%d \n", ovdone, balls, score);
            printf("%s is now onstrike and his score is %d\n", onstrike->name, onstrike->runs);
            printf("press 0-Dotball 1-single 2-twos 3-threes 4-boundary 5-catch 6-six 7-Scoreboard 8-runout 9-bowled 10-wide 11-scoresheet\n");
            int check;
            scanf("%d", &check);
            switch(check)
            {
                case 0:
                    balls++;
                    break;
                case 1:
                    single();
                    balls++;
                    break;
                case 2:
                    twos();
                    balls++;
                    break;
                case 3:
                    threes();
                    balls++;
                    break;
                case 4:
                    boundary();
                    balls++;
                    break;
                case 5:
                    cach(top1);
                    balls++;
                    break;
                case 6:
                    six();
                    balls++;
                    break;
                case 7:
                    scoreboard();
                    break;
                case 8:
                    runout();
                    balls++;
                    break;
                case 9:
                    bowled();
                    balls++;
                    break;
                case 10:
                    wide();
                    break;
                case 11:
                    scoresheet();
                    break;
                default:
                    printf("Please input valid numbers...");

             }
             if(forward==NULL)
             {

                 break;
             }

        }
         if(forward==NULL)
             {

                 break;
             }
        ovdone++;
        reversestrike();
        printf("\n");
    }

    printf("Second inning score is %d", score);
     if(score>scorea)
     {
         printf("HURRAY TEAM 2ND WON...");
     }else if(score<scorea)
     {
         printf("HURRAY 1ST TEAM WON...");
     }
     else
     {
         printf("ITS A TIE...\n");
     }
     scoresheet();




}
