#include <stdio.h>
#include <stdlib.h>

/*
    0 : water  ~
    1 : injured  O & *
    3 : ship  #
*/

extern int bord1 [9][9][2] ;
extern int ships [27][3][2] ;
extern int k [2] ;

void chap_i ( int , int , char [][25] ) ; // chap informations !
void chap_r ( int , int , int ) ;  // chap radif !
void chap_u ( int ) ; // chap up !
void chap_d ( int ) ; // chap down !

void chap ( int n , int q )
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
        chap_r ( i , n , q ) ;
        chap_d ( n ) ;
    }
    chap_u ( n ) ;
    printf ("           ") ;
    for ( int j = 0 ; j < n ; j ++ )
        printf (" [%d]  ",j+1) ;
    printf("\t\t\t  ") ;
    for ( int j = 0 ; j < n ; j ++ )
        printf (" [%d]  ",j+1) ;
    printf ("\n\n") ;
    return ;
}

void chap_i ( int num1 , int num2 , char p_name [][25] )
{
    int n1 = 0 , n2 = 0 ;
    for ( ; p_name [0][n1] ; n1 ++ ) ;
    for ( ; p_name [1][n2] ; n2 ++ ) ;
    printf ("\t ") ;
    for ( int i = 0 ; i < 10 ; i ++ )
        printf ("___") ;
    printf ("\t\t\t\t") ;
    for ( int i = 0 ; i < 10 ; i ++ )
        printf ("___") ;
    printf ("\n\t| %s :",p_name[0]) ;
    for ( int i = 27 ; i > n1 ; i -- )
        printf (" ") ;
    printf ("|\t\t       | %s :",p_name[1]) ;
    for ( int i = 27 ; i > n2 ; i -- )
        printf (" ") ;
    printf ("|\n\t|   rimaining ship = %d         |\t\t       |    remaining ship = %d        |\n",num1,num2) ;
    printf ("\t|") ;
    for ( int i = 0 ; i < 10 ; i ++ )
        printf ("___") ;
    printf ("|\t\t       |") ;
    for ( int i = 0 ; i < 10 ; i ++ )
        printf ("___") ;
    printf ("|\n\n") ;
    return ;
}

void chap_r ( int i , int n , int q )
{
    printf ("      [%d] |",n-i) ;
    for ( int j = 0 ; j < n ; j ++ )
    {
        if ( !bord1 [n-i-1][j][q] )
            printf ("  ~  |") ;
        else if ( bord1 [n-i-1][j][q] == 1 )
            printf ("  O  |") ;
        else
            printf ("  #  |") ;
    }
    if ( q )
        q = 0 ;
    else
        q = 1 ;
    printf ("\t\t     ") ;
    printf ("[%d] |",n-i) ;
    for ( int j = 0 ; j < n ; j ++ )
    {
        if ( bord1 [n-i-1][j][q] == 1 )
            printf ("  *  |") ;
        else
            printf ("  ~  |") ;
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

