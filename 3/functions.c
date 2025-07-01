#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>

/*
    0 : water  ~
    1 : injured  O & *
    3 : ship  #
*/

extern int bord1 [9][9][2] ;
extern int ships [27][3][2] ;
extern int k [2] = {0,0} ;

int shot ( int , int ) ; // ship sank or not ;
void get_n ( int* , int* ) ; //get n & num  ;
void get_i_co ( int , int , char [][25] ) ; //get p_names & cordinates ;
int get_sh_co ( int , int ) ;  //get shot coordinates ;
void sefreshkon ( int ) ; // all elements = 0 ;
void chap_i ( int , int , char [][25] ) ; // chap informations !
void chap_r ( int , int , int ) ;  // chap radif !
void chap_u ( int ) ; // chap up !
void chap_d ( int ) ; // chap down !
void chap ( int , int ) ; // chap board !
int ship ( int , int , char , int , int ) ; // Determine the ship position !

/////////////////////////////////

int shot ( int p , int q )
{
    int sw = 1 , i , j ;
    for ( i = 0 ; i < k[q] && sw ; i ++ )
        for ( j = 0 ; j < 3 && sw ; j ++ )
            if ( ships [i][j][q] == p )
            {
                sw = 0 ;
                ships [i][j][q] = 0 ;
            }
    i -- ;
    sw = 1 ;
    for ( j = 0 ; j < 3 && sw ; j ++ )
        if ( ships [i][j][q] )
            sw = 0 ;
    if ( sw )
        return 1 ;
    else
        return 0 ;
}

void get_n( int* n , int* num )
{
    printf ("Please enter the length of the land! ( Between 1 and 9 )!\nn = ") ;
    scanf ("%d",n) ;
    while ( (*n) > 9 || (*n) < 1 )
    {
        system("cls") ;
        printf ("Please re-enter \"n\" . ( Between 1 and 9 )! \nn = ") ;
        scanf ("%d",n) ;
    }
    system ("cls") ;
    printf ("Please enter the number of ships!\nnum_ships = ") ;
    scanf ("%d",num) ;
    system ("cls") ;
    return ;
}

void get_i_co ( int n , int num , char p_name [][25] )
{
    int x , y , a ;
    char c ;
    for ( int k = 0 ; k < 2 ; k ++ )
    {
        system ("cls") ;
        printf ("Please enter the name of Player%d ! \nPlayer%d name : ",k+1,k+1) ;
        scanf ("%s",p_name[k]) ;
        for ( int i = 0 ; i < num ; i ++ )
        {
            printf ("Please enter the coordinates of the ship. ( Between 1 and %d )  !\nx = ",n) ;
            scanf ("%d",&x) ;
            printf ("y = ") ;
            scanf ("%d",&y) ;
            printf ("h or v = ");
            scanf (" %c",&c) ;
            a = ship ( x , y , c , k , n ) ;
            if ( a )
                i -- ;
        }
    }
    return ;
}

int get_sh_co ( int n , int q )
{
    int a = 1 , x , y , p , r ;
    printf ("Please enter the shot coordinates . ( Between 1 and %d )  !\nx = ",n) ;
    scanf ("%d",&x) ;
    printf ("y = ") ;
    scanf ("%d",&y) ;
    x -- ;
    y -- ;
    if ( q )
        q = 0 ;
    else
        q = 1 ;
    while ( a )
    {
        if ( y < n && y >= 0 && x < n && x >= 0 )
        {
            if ( bord1 [y][x][q] == 3 )
            {
                bord1 [y][x][q] = 1 ;
                p = ((y+1)*10) + x + 1 ;
                r = shot ( p , q ) ;
                al_show_native_message_box (NULL,"BATTLE SHIP","GOOD SHOT!","This coordinate is ship!",NULL,NULL) ;
                if ( r )
                {
                    al_show_native_message_box (NULL,"BATTLE SHIP","WELL DONE!","The ship sank!",NULL,NULL) ;
                    return 1 ;
                }
            }
            else
                al_show_native_message_box (NULL,"BATTLE SHIP","BAD SHOT!","This coordinates is null!",NULL,NULL) ;
            a = 0 ;
        }
        else
            a = al_show_native_message_box (NULL,"BATTLE SHIP","NOTICE!","This coordinates are not in the board\nDo you want re_enter coordinates?",NULL,ALLEGRO_MESSAGEBOX_YES_NO) ;
    }
    return 0 ;
}

void sefreshkon ( int n )
{
    for ( int i = 0 ; i < 2 ; i ++ )
        for ( int j = 0 ; j < n ; j ++ )
            for ( int k = 0 ; k < n ; k ++ )
                bord1 [k][j][i] = 0 ;
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

int ship ( int x , int y , char c , int p_num , int n )
{
    int a ;
    x -- ;
    y -- ;
    if ( c == 'v' || c == 'V' )
    {
        if ( ( y+2 < n ) && !(bord1 [y][x][p_num]) && !(bord1 [y+1][x][p_num]) && !(bord1 [y+2][x][p_num]) )
        {
            for ( int i = y + 2 , j = 0 ; i >= y ; i -- , j ++ )
            {
                bord1 [i][x][p_num] = 3 ;
                ships [k[p_num]][j][p_num] = (10*(i+1)) + x + 1 ;
            }
            k[p_num] ++ ;
            return 0 ;
        }
        else if ( ( y-1 > 0 ) && !(bord1 [y][x][p_num]) && !(bord1 [y-1][x][p_num]) && !(bord1 [y-2][x][p_num]) )
        {
            for ( int i = y - 2 , j = 0 ; i <= y ; i ++ , j ++ )
            {
                bord1 [i][x][p_num] = 3 ;
                ships [k[p_num]][j][p_num] = (10*(i+1)) + x + 1 ;
            }
            k[p_num] ++ ;
            return 0 ;
        }
        else
            {
                a = al_show_native_message_box (NULL,"BATTLE SHIP","The ships collided!","Your ships are not placed correctly.\n Do you want re_enter coordinates?",NULL,ALLEGRO_MESSAGEBOX_YES_NO) ;
                return a ;
            }
    }
    else
    {
        if ( ( x+2 < n ) && !(bord1 [y][x][p_num]) && !(bord1 [y][x+1][p_num]) && !(bord1 [y][x+2][p_num]) )
        {
            for ( int i = x + 2 , j = 0 ; i >= x ; i -- , j ++ )
            {
                bord1 [y][i][p_num] = 3 ;
                ships [k[p_num]][j][p_num] = (10*(y+1)) + i + 1 ;
            }
            k[p_num] ++ ;
            return 0 ;
        }
        else if ( ( x-1 > 0 ) && !(bord1 [y][x][p_num]) && !(bord1 [y][x-1][p_num]) && !(bord1 [y][x-2][p_num]) )
        {
            for ( int i = x - 2 , j = 0 ; i <= x ; i ++ , j ++ )
            {
                bord1 [y][i][p_num] = 3 ;
                ships [k[p_num]][j][p_num] = (10*(y+1)) + i + 1 ;
            }
            k[p_num] ++ ;
            return 0 ;
        }
        else
            {
                a = al_show_native_message_box (NULL,"BATTLE SHIP","The ships collided!","Your ships are not placed correctly.\n Do you want re_enter coordinates?",NULL,ALLEGRO_MESSAGEBOX_YES_NO) ;
                return a ;
            }
    }
    return 0 ;
}
