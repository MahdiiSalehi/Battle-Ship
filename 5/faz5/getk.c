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
extern FILE* file1 ;

extern void sefreshkon ( int ) ; // all elements = 0 ;
extern int ship ( int , int , char , int , int ) ; // Determine the ship position !
void get_n ( int* , int* ) ; //get n & num  ;
void get_i_co ( int , int , char [][25] ) ; //get p_names & coordinates ;

void getk ( int* n , int* num , char p_name [][25] )
{
    get_n ( n , num ) ;
    sefreshkon(*n) ;
    get_i_co ( *n , *num , p_name ) ;
    system("cls") ;
    return ;
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
    fprintf (file1,"%d %d\n",(*n),(*num)) ;
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
        fprintf(file1,"%s\n",p_name[k]) ;
        for ( int i = 0 ; i < num ; i ++ )
        {
            printf ("Please enter the coordinates of the ship. ( Between 1 and %d )  !\nx = ",n) ;
            scanf ("%d",&x) ;
            printf ("y = ") ;
            scanf ("%d",&y) ;
            printf ("h or v = ");
            scanf (" %c",&c) ;
            fprintf (file1,"%d %d %c\n",x,y,c) ;
            a = ship ( x , y , c , k , n ) ;
            if ( a )
                i -- ;
        }
    }
    return ;
}
