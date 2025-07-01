#include <stdio.h>
#include <stdlib.h>

/////////////////\\\\\\\\\\\\\\\\\

#define PLAYER1 "FOCP1"
#define PLAYER2 "FOCP2"

////////////////\\\\\\\\\\\\\\\\\\\\

int bord1 [9][9][2] ;

////////////////\\\\\\\\\\\\\\\\\\\\\

void sefreshkon ( int ) ; // all elements = 0 ;
void chap_i ( int ) ; // chap informations !
void chap_r ( int , int ) ;  // chap radif !
void chap_u ( int ) ; // chap up !
void chap_d ( int ) ; // chap down !
void chap ( int ) ; // chap board !

/*
    0 : water  ~
    1 : no bomb  O
    2 : bomb!  *
    3 : ship  #
*/

int main()
{
    int n , num , x , y , p_num ;
    printf ("Please enter the length of the land! ( Between 1 and 9 )!\nn = ") ;
    scanf ("%d",&n) ;
    while ( n > 9 || n < 1 )
    {
        system("cls") ;
        printf ("Please re-enter \"n\" . ( Between 1 and 9 )! \nn = ") ;
        scanf ("%d",&n) ;
    }
    system ("cls") ;
    printf ("Please enter the number of ships!\nnum = ") ;
    scanf ("%d",&num) ;
    system ("cls") ;
    sefreshkon ( n ) ;
    for ( int i = 0 ; i < 2 ; i ++ )
    {
        for ( int j = 0 ; j < 3 ; j ++ )
        {
            printf ("Please enter the coordinates of the ship. ( Between 1 and %d )!\nx = ",n) ;
            scanf ("%d",&x) ;
            printf ("y = ") ;
            scanf ("%d",&y) ;
            if (  x > 0 && x <= n && y > 0 && y <= n )
                bord1 [y-1][x-1][i] = 2 ;
            system ("cls") ;
        }
    }
    chap_i ( num ) ;
    printf ("\n") ;
    chap ( n ) ;
    printf ("\n") ;
    return 0;
}
///////////
void sefreshkon ( int n )
{
    for ( int i = 0 ; i < 2 ; i ++ )
        for ( int j = 0 ; j < n ; j ++ )
            for ( int k = 0 ; k < n ; k ++ )
                bord1 [k][j][i] = 0 ;
    return ;
}

void chap_i ( int num )
{
    printf ("\t ") ;
    for ( int i = 0 ; i < 8 ; i ++ )
        printf ("___") ;
    printf ("\t\t\t") ;
    for ( int i = 0 ; i < 8 ; i ++ )
        printf ("___") ;
    printf ("\n\t| %s :\t\t |\t\t       | %s :\t\t|\n",PLAYER1,PLAYER2) ;
    printf ("\t|   rimaining ship = %d   |\t\t       |    remaining ship = %d  |\n",num,num) ;
    printf ("\t|") ;
    for ( int i = 0 ; i < 8 ; i ++ )
        printf ("___") ;
    printf ("|\t\t       |") ;
    for ( int i = 0 ; i < 8 ; i ++ )
        printf ("___") ;
    printf ("|\n") ;
    return ;
}

void chap_r ( int i , int n )
{
    printf ("      [%d] |",n-i) ;
        for ( int j = 0 ; j < n ; j ++ )
        {
            if ( !bord1 [n-i-1][j][0] )
                printf ("  ~  |") ;
            else if ( bord1 [n-i-1][j][0] == 1 )
                printf ("  O  |") ;
            else if ( bord1 [n-i-1][j][0] == 2 )
                printf ("  *  |") ;
            else
                printf ("  #  |") ;
        }
        printf ("\t\t     ") ;
        printf ("[%d] |",n-i) ;
        for ( int j = 0 ; j < n ; j ++ )
        {
            if ( !bord1 [n-i-1][j][1] )
                printf ("  ~  |") ;
            else if ( bord1 [n-i-1][j][1] == 1 )
                printf ("  O  |") ;
            else if ( bord1 [n-i-1][j][1] == 2 )
                printf ("  *  |") ;
            else
                printf ("  #  |") ;
        }
    printf ("\n") ;
    return ;
}

void chap_u ( int n )
{
    printf ("\t  |") ;
    for ( int i = 0 ; i < n ; i ++ )
        printf ("     |") ;
    printf ("\t\t\t |") ;
    for ( int i = 0 ; i < n ; i ++ )
        printf ("     |") ;
    printf ("\n") ;
    return ;
}

void chap_d ( int n )
{
    printf ("\t__|") ;
    for ( int i = 0 ; i < n ; i ++ )
        printf ("_____|") ;
    printf ("\t\t       __|") ;
    for ( int i = 0 ; i < n ; i ++ )
        printf ("_____|") ;
    printf ("\n") ;
    return ;
}

void chap ( int n )
{
    printf ("\t__") ;
    for ( int i = 6*n + 1 ; i > 0 ; i -- )
        printf ("_") ;
    printf ("\t\t       __") ;
    for ( int i = 6*n + 1 ; i > 0 ; i -- )
        printf ("_") ;
    printf ("\n") ;
        for ( int i = 0 ; i < n ; i ++ )
    {
        chap_u ( n ) ;
        chap_r ( i , n ) ;
        chap_d ( n ) ;
    }
    chap_u ( n ) ;
    printf ("           ") ;
    for ( int j = 0 ; j < n ; j ++ )
        printf (" [%d]  ",j+1) ;
    printf("\t\t\t  ") ;
    for ( int j = 0 ; j < n ; j ++ )
        printf (" [%d]  ",j+1) ;
    return ;
}
