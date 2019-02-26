/*
 *there are 3 files for easy , medium and hard 
 *easy -5 marks
 *medium-10 marks
 *hard-15 marks
 * 
 * the questions are generated in random order using rand() function
 * the question starts from medium and goes to easy if answered wrong 
 * and hard if correct answer
 * if easy is printed 3 times then the questions shifts to medium
 * a recursive function has been used to implement the logic
 *  
 * 
 * an attempt to plot the question vs score is done using user-defined function
 * it is able to plot if there is a change in trend of scores
 * 
 * 
 * after the quiz , the name , email , scores after each question and 
 * the total score is printed along with the plot
 */

#include <stdio.h>
#include <stdlib.h>

#define clearScreen() printf("\e[1;1H\e[2J")

char name[20],email[20];
int scor[10];
int score=0;
int asked[3][10];
int questCount=1;

void init_array(){
    for(int i=0;i<3;i++){
        for(int j=0;j<10;j++)
            asked[i][j]=0;
    }
}
void init_scores(){
        for(int j=0;j<10;j++)
            scor[j]=0;
}

//print scores
void get_scores(){
    printf("\nthe scores after each question :\n");
    for(int j=0;j<10;j++)
        printf(" %d ",scor[j]);
}

void Welcome(){
    printf("\n      WELCOME TO ADAPTIVE LEARNING ASSESMENT TEST!\n\n");
    printf("\nenter your name   :");
    scanf("%s",name);
    printf("\nenter your email  :");
    scanf("%s",email);
    clearScreen();   
}

//logic for printing easy questions from a file
//here q is the question number to be printed
int readEasyquestions(int q){
    //if q has already been asked , move to next unasked question
    while(asked[0][q]==1)
        q=(q+1)%15;
    asked[0][q]=1;
    
    printf("\nquestion %d \nlevel :easy\n",questCount);
    
    //print the question from file
    FILE *fp;
    char c;
    int count=0;
    int cnt=(q-1)*6+1;
    char ans,x;
    fp = fopen("/Users/sahanas/Desktop/QuestionPoolEasy.txt", "r");
     while((c = fgetc(fp)) != EOF) {
         //this loop places file pointer to the required question number to be printed
        if (c == '\n') {
            count++;
            if(count==cnt){
                break;
        }
    }
     }
                count=0;
                while((c = fgetc(fp)) != EOF) {
                    //this loop prints the question 
                 if (c == '\n') {
            count++;
            putc(c, stdout);
            if(count==5){
                //get the correct answer 
                ans=fgetc(fp);
                break;
            }
            
                 }
        putc(c, stdout);
    }
    //ask user answer  and accept only valid options
     printf("\nenter the choice : ");
    getchar();
    scanf("%c",&x);
    while(!(x=='a'||x=='b'||x=='c'||x=='d')){
        printf("\nenter a valid choice! \n");
        getchar();
        scanf("%c",&x);
    }
    if(x==ans){
        return 5;
    }else 
        return 0;
}

//logic for printing medium questions from a file
int readMediumquestions(int q){
    while(asked[1][q]==1)
        q=(q)%25+1;
    asked[1][q]=1;
    printf("\nquestion %d \nlevel :medium\n",questCount);
    FILE *fp;
    char c;
    int count=0;
    int cnt=(q-1)*6+1;
    char ans,x;
    fp = fopen("/Users/sahanas/Desktop/QuestionPoolMedium.txt", "r");
     while((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            count++;
            if(count==cnt){
                break;
        }
    }
     }
     count=0;
                while((c = fgetc(fp)) != EOF) {
                 if (c == '\n') {
            count++;
            putc(c, stdout);
            if(count==5){
                ans=fgetc(fp);
                break;
            }
        }
        putc(c, stdout);
    }
    printf("\nenter the choice : ");
    getchar();
    scanf("%c",&x);
    while(!(x=='a'||x=='b'||x=='c'||x=='d')){
        printf("\nenter a valid choice! \n");
        getchar();
        scanf("%c",&x);
    }
    if(x==ans){
        return 10;
    }
    else 
        return 0;
}

//logic for printing hard questions from a file
int readHardquestions(int q){
    while(asked[2][q]==1)
        q=(q+1)%10;
    asked[2][q]=1;
    printf("\nquestion %d \nlevel :hard\n",questCount);
    //questCount++;
    FILE *fp;
    char c;
    int count=0;
    int cnt=(q-1)*6+1;
    char ans,x;
    fp = fopen("/Users/sahanas/Desktop/QuestionPoolHard.txt", "r");
     while((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            count++;
            if(count==cnt){
                break;
        }
    }
     }
     count=0;
                while((c = fgetc(fp)) != EOF) {
                 if (c == '\n') {
            count++;
            putc(c, stdout);
            if(count==5){// print '\n', as it is part of the line
                ans=fgetc(fp);
                break;
            }
        }
        putc(c, stdout);
    }
    printf("\nenter the choice : ");
    getchar();
    scanf("%c",&x);
    while(!(x=='a'||x=='b'||x=='c'||x=='d')){
        printf("\nenter a valid choice! \n");
        getchar();
        scanf("%c",&x);
    }
    if(x==ans)
        return 15;
    else 
        return 0;
}

//main logic to generate questions
void askquestion(){
    if(questCount>10){
        return ;
    }
    else{   
    int a=0,ques,count_easy=0;
    ques=rand() % (25)+1;
    a=readMediumquestions(ques);
    questCount++;
    score+=a;
    scor[questCount-1]=score;
    printf("\nscore=%d and %d\n",score,scor[questCount-1]);
    if(a==0){
        while(a==0&&questCount<=10){
         a=readEasyquestions(rand()%15+1);
         questCount++;
         score+=a;
         scor[questCount-1]=score;
         printf("\nscore=%d and %d\n",score,scor[questCount-1]);
         count_easy++;
         if(count_easy==3||a!=0) //after 3 easy questions , medium is printed 
            askquestion(); 
    } 
    }
    else if(a!=0){
        while(a!=0&&questCount<=10){
         a=readHardquestions(rand()%10+1);
         questCount++;
         score+=a;
         scor[questCount-1]=score;
         printf("\nscore=%d and %d\n",score,scor[questCount-1]);
         if(a==0)
            askquestion(); 
    }
    }
    }
   
}


//this plots only when there is a change in value
void plot(){
    int i;
    printf("\n\n*****************************************************************\n                                 PLOT\n\n");
    printf("score");
    printf("\n    ^");
    for(i=0;i<11;i++){
        
        if(i%2==0&&(150-15*i>99))
            printf("\n%d-|",150-15*i);
        else if(i%2==0&&(150-15*i>9))
            printf("\n%d -|",150-15*i);
        printf("\n    |");
        for(int j=0;j<10;j++)
            if(scor[j]>135-15*i){
                printf(" ");
                for(int k=0;k<j;k++)
                printf("   ");
                printf(" *");
                break;
            }
    }
    
    printf("\n    |----|----|----|----|----|----|----|----|----|----|--> Questions\n    ");
    for(i=0;i<11;i++)
        printf("%d    ",i);
        
}


int main() {
    Welcome();
    init_array();
    init_scores();
    askquestion();
    printf("\nname :%s \nemail :%s",name,email);
    
    printf("\nfinal score is=%d",scor[9]);
    get_scores();
    plot();
    return (EXIT_SUCCESS);
}
