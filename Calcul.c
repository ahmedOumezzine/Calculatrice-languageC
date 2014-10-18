#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>

#define ANS 15
#define ACS 4
char a[100];
int co=0,R=0;
COORD coord= {0,0}; // this is global variable
void gotoxy(int x,int y){
        coord.X=x;
        coord.Y=y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
///This will set the forground color for printing in a console window.
void SetColor(int ForgC){
     WORD wColor;
     ///We will need this handle to get the current background attribute
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;

     ///We use csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        ///Mask out all but the background attribute, and add in the forgournd color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}

void d_mainmenu(){
    int i;
    const char *menu0[]= {"   1","   4","   7","   C"};
    const char *menu1[]= {"   2","   5","   8","   0"};
    const char *menu2[]= {"   3","   6","   9","   ="};
    const char *menu3[]= {"   +","   -","   *","   /"};
    const char *menu4[]= {"   (","   )","   about_me","   contact_me"};
    SetColor(15);
    for (i=0; i<=3; i++){
        gotoxy(10,22+i+1);
        printf("%s \n \n \n",menu0[i]);
    }
    for (i=0; i<=3; i++){
        gotoxy(20,22+i+1);
        printf("%s \n \n \n",menu1[i]);
    }
    for (i=0; i<=3; i++){
        gotoxy(30,22+i+1);
        printf("%s \n \n \n",menu2[i]);
    }
    for (i=0; i<=3; i++){
        gotoxy(40,22+i+1);
        printf("%s \n \n \n",menu3[i]);
    }
    for (i=0; i<=3; i++){
        gotoxy(50,22+i+1);
        printf("%s \n \n \n",menu4[i]);
    }
    curser(4);
}

void OP(char c){
    a[co]=c;
    gotoxy(31+co,12);
     printf("%c",c);
    co++;
}
int calculer( char *a){
     char *p=a;
    char *r=a;
    char **q=&r;
    int P=1,S=0;
    char signe='+';
    while (**q!='\0'){
    /* on parcourt la fomule de la gauche vers la droite */
        do{
            /* on calcule chaque produit */
            if (*p=='(')
            {/* cas d'un facteur negatif */
                p++;
                P*=strtol(p,q,10);
                *q=*q+1;
                p=*q+1;
            }
            else P*=strtol(p,q,10);
            p=*q+1;
        }
        while (**q=='*');
        if (signe=='+') S+=P ;
        else S-=P;
        signe=**q;
        P=1;/* reinitilisation pour le produit suivant */
    }
    return S;
}
void resultat(){
        a[co]='\o';
        gotoxy(32+co,12);
        printf(" = %d \n",calculer(a));
        R=1;
}
void clr(){
    gotoxy(0,2);
    printf("                                                                             ");
    printf("\n                                                                             ");
    printf("\n                                                                             ");
    printf("\n                                                                             ");
    printf("\n                                                                             ");
    printf("\n                                                                             ");
    printf("\n                                                                             ");
    printf("\n                                                                             ");
    printf("\n                                                                             ");

    gotoxy(31,12);
    printf("                                                                             ");
}
void C(){
    gotoxy(31+co-1,12);
    printf(" ");
    co--;
}

/*function for cursor movement*/
void curser(int no){
    int count=1,DG=0;
    char ch='0';
    gotoxy(10,23);
    while(1){
        switch(ch){
        case 77:
            DG++;
            if (DG>5) DG=0;
            if(R==1) {clr();R=0;co=0;a[0]='\o';};
            break;
        case 75:
            DG--;
            if(DG<0) DG=4;
            if(R==1) {clr();R=0;co=0;a[0]='\o';};
            break;
        case 80:
            count++;
            if (count==no+1) count=1;
            if(R==1) {clr();R=0;co=0;a[0]='\o';};
            break;
        case 72:
            count--;
            if(count==0) count=no;
            if(R==1) {clr();R=0;co=0;a[0]='\o';};
            break;
        }


          switch(DG){
        case 0:
            highlight(count);
            ch=getch();
            if(ch=='\r'){
                if(no==4)
                {
                    if (count==1) OP('1') ;
                    else if(count==2) OP('4');
                    else if(count==3) OP('7');
                    else if (count==4) C();
                    else   exit(0);
                }
            }
            break;
        case 1:
            highlight2(count);
            ch=getch();
            if(ch=='\r'){
                if(no==4){
                    if (count==1) OP('2') ;
                    else if(count==2) OP('5');
                    else if(count==3) OP('8');
                    else if (count==4) OP('0');
                    else   exit(0);
                }
            }
            break;
        case 2:
            highlight3(count);
            ch=getch();
            if(ch=='\r'){
                if(no==4){
                    if (count==1) OP('3') ;
                    else if(count==2) OP('6');
                    else if(count==3) OP('9');
                    else if (count==4) resultat();
                    else   exit(0);
                }
            }
            break;
        case 3:
             highlight4(count);
            ch=getch();
            if(ch=='\r'){
                if(no==4){
                    if (count==1) OP('+') ;
                    else if(count==2) OP('-');
                    else if(count==3) OP('*');
                    else if (count==4) OP('/');
                    else   exit(0);
                }
            }
            break;
        case 4:
            highlight5(count);
            ch=getch();
            if(ch=='\r'){
                if(no==4){
                    if (count==1) OP('(') ;
                    else if(count==2) OP(')');
                    else if(count==3) about_me();
                    else if (count==4) contact_me();
                    else   exit(0);
                }
            }
             break;
          }
    }
}
void menu_cal(){
    SetColor(15);
        gotoxy (10,23);
        printf("   1");
        gotoxy (10,24);
        printf("   4");
        gotoxy (10,25);
        printf("   7");
        gotoxy (10,26);
        printf("   C");
        gotoxy (20,23);
        printf("   2");
        gotoxy (20,24);
        printf("   5");
        gotoxy (20,25);
        printf("   8");
        gotoxy (20,26);
        printf("   0");
        gotoxy (30,23);
        printf("   3");
        gotoxy (30,24);
        printf("   6");
        gotoxy (30,25);
        printf("   9");
        gotoxy (30,26);
        printf("   =");
        gotoxy (40,23);
        printf("   +");
        gotoxy (40,24);
        printf("   -");
        gotoxy (40,25);
        printf("   *");
        gotoxy (40,26);
        printf("   /");
        gotoxy (50,23);
        printf("   (");
        gotoxy (50,24);
        printf("   )");
        gotoxy (50,25);
        printf("   about_me");
        gotoxy (50,26);
        printf("   contact_me");
}
void highlight(int count){
        menu_cal();
        SetColor(13);
        switch(count){
        case 1:
            gotoxy (10,23);
            printf("  1 ");
            break;
        case 2:
            gotoxy (10,24);
            printf("  4 ");
            break;
        case 3:
            gotoxy (10,25);
            printf("  7 ");
            break;
        case 4:
            gotoxy (10,26);
            printf("  C ");
            break;
        }
        SetColor(15);
}
void highlight2(int count){
        menu_cal();
        SetColor(13);
        switch(count){
        case 1:
            gotoxy (20,23);
            printf("  2 ");
            break;
        case 2:
            gotoxy (20,24);
            printf("  5 ");
            break;
        case 3:
            gotoxy (20,25);
            printf("  8 ");
            break;
        case 4:
            gotoxy (20,26);
            printf("  0 ");
            break;
        }
        SetColor(15);
}
void highlight3(int count){
        menu_cal();
        SetColor(13);
        switch(count) {
        case 1:
            gotoxy (30,23);
            printf("  3 ");
            break;
        case 2:
            gotoxy (30,24);
            printf("  6 ");
            break;
        case 3:
            gotoxy (30,25);
            printf("  9 ");
            break;
        case 4:
            gotoxy (30,26);
            printf("  = ");
            break;

        }
        SetColor(15);
}
void highlight4(int count){
        menu_cal();
        SetColor(13);
        switch(count) {
        case 1:
            gotoxy (40,23);
            printf("  + ");
            break;
        case 2:
            gotoxy (40,24);
            printf("  - ");
            break;
        case 3:
            gotoxy (40,25);
            printf("  * ");
            break;
        case 4:
            gotoxy (40,26);
            printf("  / ");
            break;
        }
        SetColor(15);
    }
void highlight5(int count){
       menu_cal();
        SetColor(13);
        switch(count) {
        case 1:
            gotoxy (50,23);
            printf("  ( ");
            break;
        case 2:
            gotoxy (50,24);
            printf("  ) ");
            break;
        case 3:
            gotoxy (50,25);
            printf("  about_me ");
            break;
        case 4:
            gotoxy (50,26);
            printf("  contact_me ");
            break;
        }
        SetColor(15);
    }

void about_me(){
    gotoxy(0,2);
    SetColor(35);
    printf("ESPRIM - Young Developers c'est un club face a toute forme de d%cveloppement. \n",130);
    printf("permet aux %ctudiants d'améliorer leurs comp%ctences techniques et int%cgrés   \n",130,130,130);
    printf("les dans le cœur du d%cveloppement du monde et de l'innovation",130);
}

void contact_me(){
    gotoxy(28,2);
    SetColor(35);
    printf("Ahmed OUMEZZINE");
    gotoxy(30,3);
    printf("Cycle d'ingenieur ");
    gotoxy(22,4);
    printf("Email: Ahmedoumezzine@outlook.fr");
}


int main(void){
    system("cls");

    gotoxy(25,24);
    SetColor(17);
    d_mainmenu();
    return 0;
}
