#include <stdio.h>
#include <stdlib.h>

/////////////////\\\\\\\\\\\\\\\\\

int bord1 [9][9][2] ;

////////////////\\\\\\\\\\\\\\\\\\\\\

void sefreshkon ( int ) ; // all elements = 0 ;
void chap_i ( int , char [] , char [] ) ; // chap informations !
void chap_r ( int , int ) ;  // chap radif !
void chap_u ( int ) ; // chap up !
void chap_d ( int ) ; // chap down !
void chap ( int ) ; // chap board !
void ship ( int , int , char , int p_num ) ; // Determine the ship position !

/*
    0 : water  ~
    1 : no bomb  O
    2 : bomb!  *
    3 : ship  #
*/

int main()
{
    int n , num , x , y ;
    char c ;
    char p1_name [25] , p2_name [25] ;
    printf ("Please enter the length of the land! ( Between 1 and 9 )!\nn = ") ;
    scanf ("%d",&n) ;
    while ( n > 9 || n < 1 )
    {
        system("cls") ;
        printf ("Please re-enter \"n\" . ( Between 1 and 9 )! \nn = ") ;
        scanf ("%d",&n) ;
    }
    system ("cls") ;
    printf ("Please enter the number of ships!\nnum_ships = ") ;
    scanf ("%d",&num) ;
    system ("cls") ;
    sefreshkon ( n ) ;
    printf ("Please enter the name of Player1 ! \n Player1 name : ") ;
    scanf ("%s",p1_name) ;
    for ( int i = 0 ; i < num ; i ++ )
    {
        printf ("Please enter the coordinates of the ship. ( Between 1 and %d )  !\nx = ",n) ;
        scanf ("%d",&x) ;
        printf ("y = ") ;
        scanf ("%d",&y) ;
        printf (" h or v : ");
        scanf ("%c",&c) ;
        if (  x > 0 && x <= n && y > 0 && y <= n )
            bord1 [y-1][x-1][0] = 2 ;
        system ("cls") ;
    }
    scanf ("%s",p2_name) ;
    printf ("Please enter the name of Player2 ! \n Player2 name : ") ;
    scanf ("%s",p2_name) ;
    for ( int i = 0 ; i < num ; i ++ )
    {
        printf ("Please enter the coordinates of the ship. ( Between 1 and %d )  !\nx = ",n) ;
        scanf ("%d",&x) ;
        printf ("y = ") ;
        scanf ("%d",&y) ;
        printf (" h or v : ");
        scanf ("%c",&c) ;
        if (  x > 0 && x <= n && y > 0 && y <= n )
            bord1 [y-1][x-1][1] = 2 ;
        system ("cls") ;
    }
    chap_i ( num , p1_name , p2_name ) ;
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

void chap_i ( int num , char p1_name [] , char p2_name [] )
{
    int n1 = 0 , n2 = 0 ;
    for ( ; p1_name [n1] ; n1 ++ ) ;
    for ( ; p2_name [n2] ; n2 ++ ) ;
    printf ("\t ") ;
    for ( int i = 0 ; i < 10 ; i ++ )
        printf ("___") ;
    printf ("\t\t\t\t") ;
    for ( int i = 0 ; i < 10 ; i ++ )
        printf ("___") ;
    printf ("\n\t| %s :",p1_name) ;
    for ( int i = 27 ; i > n1 ; i -- )
        printf (" ") ;
    printf ("|\t\t       | %s :",p2_name) ;
    for ( int i = 27 ; i > n2 ; i -- )
        printf (" ") ;
    printf ("|\n\t|   rimaining ship = %d         |\t\t       |    remaining ship = %d        |\n",num,num) ;
    printf ("\t|") ;
    for ( int i = 0 ; i < 10 ; i ++ )
        printf ("___") ;
    printf ("|\t\t       |") ;
    for ( int i = 0 ; i < 10 ; i ++ )
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

void ship ( int x , int y , char c , int p_num )
{
    x -- ;
    y -- ;
    p_num -- ;
    int i , j ;
    if ( c == 'h' || c == 'H' )
    {
        if ( !(bord [x][y+2][p_num]) && !(bord [x][y+1][p_num]) )
        {
            for ( int i = y + 2 ; i >= y ; i -- )
                bord [x][i][p_num] = 3 ;
            return ;
        }
        else ( !(bord [x][y-2][p_num]) && !(bord [x][y-1][p_num]) )
        {
            for ( int i = y - 2 ; i >= y ; i ++ )
                bord [x][i][p_num] = 3 ;
            return ;
        }
        else
            al_show
    }
    else
    {

    }
    return ;
}
