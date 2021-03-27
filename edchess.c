#include<stdio.h>
#include<string.h>
#include<math.h>
//#include<cs50.h>
#include <stdlib.h>
char board[8][8];
bool enp[8][2];
int k1[2];
int k2[2];
bool movedk[2];
bool movedr[2][2];
bool white(int c1,int c2)
{
    if(board[c1][c2]>='A' && board[c1][c2]<='Z')return 1;
    return 0;
}
bool black(int c1,int c2)
{
    if(board[c1][c2]>='a' && board[c1][c2]<='z')return 1;
    return 0;
}
bool checkbishopmove(int c1,int c2,int c3,int c4)
{
    if(c1<0 || c1>7 || c2<0 || c2>7 || c3<0 || c3>7 || c4<0 || c4>7)return 0;
    if(abs(c1-c3)!=abs(c2-c4))return 0;
    int s1=c1;
    int e1=c3;
    int d1,d2;
    int s2=c2;
    int e2=c4;
    if(s1>e1)d1=-1;
    else
    {
        d1=1;
    }
    if(s2>e2)d2=-1;
    else
    {
        d2=1;
    }
    s1+=d1;
    s2+=d2;
    while(s1!=e1)
    {
        if(board[s1][s2]!='*')
        {
            return 0;
        }
        s1+=d1;
        s2+=d2;
    }
    if(white(c1,c2) && white(c3,c4))return 0;
    if(black(c1,c2) && black(c3,c4))return 0; 
    return 1;
}
bool checkrookmove(int c1,int c2,int c3,int c4)
{
    if(c1<0 || c1>7 || c2<0 || c2>7 || c3<0 || c3>7 || c4<0 || c4>7)return 0;
    if(c1==c3)
    {
        int s=c2;
        int e=c4;
        int d;
        if(s>e)d=-1;
        else
        {
            d=1;
        }
        s+=d;
        while(s!=e)
        {
            if(board[c1][s]!='*')
            {
                return 0;
            }
            s+=d;
        }
        if(white(c1,c2) && white(c3,c4))return 0;
        if(black(c1,c2) && black(c3,c4))return 0;
        return 1;
    }
    else if(c2==c4)
    {
        int s=c1;
        int e=c3;
        int d;
        if(s>e)d=-1;
        else
        {
            d=1;
        }
        s+=d;
        while(s!=e)
        {
            if(board[s][c2]!='*')
            {
                return 0;
            }
            s+=d;
        }
        if(white(c1,c2) && white(c3,c4))return 0;
        if(black(c1,c2) && black(c3,c4))return 0;
        return 1;
    }
    return 0;
}
bool checkknightmove(int c1,int c2,int c3,int c4)
{
    if(c1<0 || c1>7 || c2<0 || c2>7 || c3<0 || c3>7 || c4<0 || c4>7)return 0;
    if(abs(c1-c3)==1 && abs(c2-c4)==2)
    {
        if(white(c1,c2) && white(c3,c4))return 0;
        if(black(c1,c2) && black(c3,c4))return 0;
        return 1;
    }
    if(abs(c1-c3)==2 && abs(c2-c4)==1)
    {
        if(white(c1,c2) && white(c3,c4))return 0;
        if(black(c1,c2) && black(c3,c4))return 0;
        return 1;
    }
    return 0;
}
bool checkqueenmove(int c1,int c2,int c3,int c4)
{
    if(checkrookmove(c1,c2,c3,c4))return 1;
    if(checkbishopmove(c1,c2,c3,c4))return 1;
    return 0;
}
bool checkkingmove(int c1,int c2,int c3,int c4)
{
    if(c1<0 || c1>7 || c2<0 || c2>7 || c3<0 || c3>7 || c4<0 || c4>7)return 0;
    if(abs(c1-c3)<=1 && abs(c2-c4)<=1)
    {
        if(white(c1,c2) && white(c3,c4))return 0;
        if(black(c1,c2) && black(c3,c4))return 0;
        return 1;
    }
    return 0;
}
bool checkpawnmove(int c1,int c2,int c3,int c4)
{
    if(c1<0 || c1>7 || c2<0 || c2>7 || c3<0 || c3>7 || c4<0 || c4>7)return 0;
    if(c2==c4)
    {
        if(abs(c1-c3)==1)
        {
            if(board[c3][c4]!='*')return 0;
            return 1;
        }
        else if(abs(c1-c3)==2)
        {
            if(c1==1 || c1==6)
            {
                int g;
                if(c1==6)
                {
                    g=5;
                }
                if(c1==1)
                {
                    g=2;
                }
                if(board[g][c2]!='*')
                {
                    return 0;
                }
                if(board[c3][c4]!='*')
                {
                    return 0;
                }
                if(g==5)
                {
                    enp[c4][1]=1;
                }
                else if(g==2)
                {
                    enp[c4][0]=1;
                }
                return 1;
            }
            return 0;
        }
        return 0;
    }
    else if(abs(c2-c4)==1)
    {
        if(abs(c1-c3)!=1)return 0;
        if(board[c3][c4]!='*')
        {
            if(white(c1,c2) && white(c3,c4))return 0;
            if(black(c1,c2) && black(c3,c4))return 0;
            return 1;
        }
        else
        {
            if(white(c1,c2) && white(c1,c4))return 0;
            if(black(c1,c2) && black(c1,c4))return 0;
            int ind;
            if(white(c1,c2))ind=0;
            if(black(c1,c2))ind=1;
            if(enp[c4][ind])
            {
                board[c1][c4]='*';
                return 1;
            }
            return 0;
        }
    }
    return 0;
}
void print(void)
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}
bool iskingincheck(int color,int c1,int c2)
{
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(color && black(i,j))
            {
                if(board[i][j]=='p')
                {
                    if(checkpawnmove(i,j,c1,c2))return 1;
                }
                else if(board[i][j]=='n')
                {
                    if(checkknightmove(i,j,c1,c2))return 1;
                }
                else if(board[i][j]=='b')
                {
                    if(checkbishopmove(i,j,c1,c2))return 1;
                }
                else if(board[i][j]=='r')
                {
                    if(checkrookmove(i,j,c1,c2))return 1;
                }
                else if(board[i][j]=='q')
                {
                    if(checkqueenmove(i,j,c1,c2))return 1;
                }
                else if(board[i][j]=='k')
                {
                    if(checkkingmove(i,j,c1,c2))return 1;
                }
            }
            else if(!color && white(i,j))
            {
                if(board[i][j]=='P')
                {
                    if(checkpawnmove(i,j,c1,c2))return 1;
                }
                else if(board[i][j]=='N')
                {
                    if(checkknightmove(i,j,c1,c2))return 1;
                }
                else if(board[i][j]=='B')
                {
                    if(checkbishopmove(i,j,c1,c2))return 1;
                }
                else if(board[i][j]=='R')
                {
                    if(checkrookmove(i,j,c1,c2))return 1;
                }
                else if(board[i][j]=='Q')
                {
                    if(checkqueenmove(i,j,c1,c2))return 1;
                }
                else if(board[i][j]=='K')
                {
                    if(checkkingmove(i,j,c1,c2))return 1;
                }
            }
        }
    }
    return 0;
}
int main(void)
{
    for(int i = 0; i < 8; i++)
    {
        board[1][i]='p';
        board[6][i]='P';
    }
    int wk1,wk2,bk1,bk2;
    board[0][0]=board[0][7]='r';
    board[7][0]=board[7][7]='R';
    board[0][1]=board[0][6]='n';
    board[7][1]=board[7][6]='N';
    board[0][2]=board[0][5]='b';
    board[7][2]=board[7][5]='B';
    board[0][3]='q';
    board[0][4]='k';
    board[7][3]='Q';
    board[7][4]='K';
    k1[0]=0;
    k2[0]=4;
    k1[1]=7;
    k2[1]=4;
    for(int i=2;i<6;i++)
    {
        for(int j=0;j<8;j++)
        {
            board[i][j]='*';
        }
    }
    print();
    char str[4];
    char promote[6];
    scanf("%s", str);
    int turn=1;
    while (strncmp(str,"END",3) != 0)
    {
        if (turn && strncmp(str,"o-o",3) == 0)
        {
            if(movedk[turn] || movedr[turn][1])
            {
                printf("Illegal move\n");
                scanf("%s", str);
                continue;
            }
            if(iskingincheck(turn,7,4) || iskingincheck(turn,7,5) || iskingincheck(turn,7,6))
            {
                printf("Illegal move\n");
                scanf("%s", str);
                continue;
            }
            if(board[7][5]!='*' || board[7][6]!='*')
            {
                printf("Illegal move\n");
                scanf("%s", str);
                continue;
            }
            board[7][4]='*';
            board[7][7]='*';
            board[7][5]='R';
            board[7][6]='K';
            print();
            scanf("%s", str);
            turn^=1;
            continue;
        }
        else if (!turn && strncmp(str,"o-o",3) == 0)
        {
            if(movedk[turn] || movedr[turn][1])
            {
                printf("Illegal move\n");
                scanf("%s", str);
                continue;
            }
            if(iskingincheck(turn,0,4) || iskingincheck(turn,0,5) || iskingincheck(turn,0,6))
            {
                printf("Illegal move\n");
                scanf("%s", str);
                continue;
            }
            if(board[0][5]!='*' || board[0][6]!='*')
            {
                printf("Illegal move\n");
                scanf("%s", str);
                continue;
            }
            board[0][4]='*';
            board[0][7]='*';
            board[0][5]='r';
            board[0][6]='k';
            print();
            scanf("%s", str);
            turn^=1;
            continue;
        }
        else if (turn && strncmp(str,"O-O",3) == 0)
        {
            if(movedk[turn] || movedr[turn][0])
            {
                printf("Illegal move\n");
                scanf("%s", str);
                continue;
            }
            if(iskingincheck(turn,7,4) || iskingincheck(turn,7,3) || iskingincheck(turn,7,2))
            {
                printf("Illegal move\n");
                scanf("%s", str);
                continue;
            }
            if(board[7][3]!='*' || board[7][2]!='*' || board[7][1]!='*')
            {
                printf("Illegal move\n");
                scanf("%s", str);
                continue;
            }
            board[7][4]='*';
            board[7][0]='*';
            board[7][3]='R';
            board[7][2]='K';
            print();
            scanf("%s", str);
            turn^=1;
            continue;
        }
        else if (!turn && strncmp(str,"O-O",3) == 0)
        {
            if(movedk[turn] || movedr[turn][0])
            {
                printf("Illegal move\n");
                scanf("%s", str);
                continue;
            }
            if(iskingincheck(turn,0,4) || iskingincheck(turn,0,3) || iskingincheck(turn,0,2))
            {
                printf("Illegal move\n");
                scanf("%s", str);
                continue;
            }
            if(board[0][3]!='*' || board[0][2]!='*' || board[0][1]!='*')
            {
                printf("Illegal move\n");
                scanf("%s", str);
                continue;
            }
            board[0][4]='*';
            board[0][0]='*';
            board[0][3]='r';
            board[0][2]='k';
            print();
            scanf("%s", str);
            turn^=1;
            continue;
        }
        int c1 = str[0]-'a';
        int c2 = str[1]-'0';
        int c3 = str[2]-'a';
        int c4 = str[3]-'0';
        c2=8-c2;
        c4=8-c4;
        if(turn && black(c2,c1))
        {
            printf("Illegal move\n");
            scanf("%s", str);
            continue;
        }
        if(!turn && white(c2,c1))
        {
            printf("Illegal move\n");
            scanf("%s", str);
            continue;
        }
        if(board[c2][c1]=='*')
        {
            printf("Illegal move\n");
            scanf("%s", str);
            continue;
        }
        int color = white(c2,c1);
        for(int i=0;i<8;i++)
        {
            enp[i][color]=0;
        }
        if((color && board[c2][c1]=='P') || (!color && board[c2][c1]=='p'))
        {
            if(!checkpawnmove(c2,c1,c4,c3))
            {
                printf("Illegal move\n");
                scanf("%s", str);
                continue;
            }
        }
        if((color && board[c2][c1]=='N') || (!color && board[c2][c1]=='n'))
        {
            if(!checkknightmove(c2,c1,c4,c3))
            {
                printf("Illegal move\n");
                scanf("%s", str);
                continue;
            }
        }
        if((color && board[c2][c1]=='B') || (!color && board[c2][c1]=='b'))
        {
            if(!checkbishopmove(c2,c1,c4,c3))
            {
                printf("Illegal move\n");
                scanf("%s", str);
                continue;
            }
        }
        if((color && board[c2][c1]=='R') || (!color && board[c2][c1]=='r'))
        {
            if(!checkrookmove(c2,c1,c4,c3))
            {
                printf("Illegal move\n");
                scanf("%s", str);
                continue;
            }
        }
        if((color && board[c2][c1]=='Q') || (!color && board[c2][c1]=='q'))
        {
            if(!checkqueenmove(c2,c1,c4,c3))
            {
                printf("Illegal move\n");
                scanf("%s", str);
                continue;
            }
        }
        if((color && board[c2][c1]=='K') || (!color && board[c2][c1]=='k'))
        {
            if(!checkkingmove(c2,c1,c4,c3))
            {
                printf("Illegal move\n");
                scanf("%s", str);
                continue;
            }
        }
        char prevpiece1=board[c2][c1];
        char prevpiece2=board[c4][c3];
        board[c4][c3]=board[c2][c1];
        board[c2][c1]='*';
        if(iskingincheck(turn,k1[turn],k2[turn]))
        {
            board[c2][c1]=prevpiece1;
            board[c4][c3]=prevpiece2;
            printf("Illegal move\n");
            scanf("%s", str);
            continue;
        }
        if(board[c4][c3]=='K')
        {
            k1[1]=c4;
            k2[1]=c3;
            movedk[1]=1;
        }
        else if(board[c4][c3]=='k')
        {
            k1[0]=c4;
            k2[0]=c3;
            movedk[0]=1;
        }
        else if(board[c4][c3]=='R')
        {
            if(c1==7)
            {
                movedr[1][1]=1;
            }
            else if(c1==0)
            {
                movedr[1][0]=1;
            }
        }
        else if(board[c4][c3]=='r')
        {
            if(c1==7)
            {
                movedr[0][1]=1;
            }
            else if(c1==0)
            {
                movedr[0][0]=1;
            }
        }
        else if(board[c4][c3]=='P' && c4==0)
        {
            scanf("%s", promote);
            if(!strncmp(promote,"Queen",5))
            {
                board[c4][c3]='Q';
            }
            if(!strncmp(promote,"Knight",6))
            {
                board[c4][c3]='N';
            }
            if(!strncmp(promote,"Bishop",6))
            {
                board[c4][c3]='B';
            }
            if(!strncmp(promote,"Rook",4))
            {
                board[c4][c3]='R';
            }
        }
        else if(board[c4][c3]=='p' && c4==7)
        {
            scanf("%s", promote);
            if(!strncmp(promote,"Queen",5))
            {
                board[c4][c3]='q';
            }
            if(!strncmp(promote,"Knight",6))
            {
                board[c4][c3]='n';
            }
            if(!strncmp(promote,"Bishop",6))
            {
                board[c4][c3]='b';
            }
            if(!strncmp(promote,"Rook",4))
            {
                board[c4][c3]='r';
            }
        }
        print();
        turn^=1;
        scanf("%s", str);
    }
    return 0;
}
