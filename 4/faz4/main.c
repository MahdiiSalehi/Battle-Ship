#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>

/////////////////\\\\\\\\\\\\\\\\\

int bord1 [9][9][2] ;
int ships [27][3][2] ;
int k[2] ;

////////////////\\\\\\\\\\\\\\\\\\\\\

extern int shot ( int , int ) ; // ship sank or not ;
extern void get_i_co ( FILE* , int , int , char [][25] ) ; //get player names & coordinates ;
extern void get_n ( FILE* , int* , int* ) ; //get n & num  ;
extern int get_sh_co ( int , int ) ;  //get shot coordinates ;
extern void sefreshkon ( int ) ; // all elements = 0 ;
extern void chap_i ( int , int , char [][25] ) ; // chap informations !
extern void chap_r ( int , int , int ) ;  // chap radif !
extern void chap_u ( int ) ; // chap up !
extern void chap_d ( int ) ; // chap down !
extern void chap ( int , int ) ; // chap board !
extern int ship ( int , int , char , int , int ) ; // Determine the ship position !
/*
    0 : water  ~
    1 : no bomb  O
    2 : bomb!  *
    3 : ship  #
*/

int main()
{
    int n , q = 0 , num , num1 , num2 , t ;
    char p_name [2][25] ;
    FILE *file = fopen ("input.txt","r") ;
    if ( !file )
    {
        printf ("can not open input file") ;
        return 0 ;
    }
    get_n ( file , &n , &num ) ;
    num1 = num2 = num ;
    sefreshkon ( n ) ;
    get_i_co ( file , n , num , p_name ) ;
    fclose(file) ;
    system("cls") ;
    while ( num1 && num2 )
    {
        chap_i ( num1 , num2 , p_name ) ;
        chap ( n , q ) ;
        t = get_sh_co ( n , q ) ;
        if ( t )
        {
            if ( q )
                num2 -- ;
            else
                num1 -- ;
        }
        if ( q )
            q = 0 ;
        else
            q = 1 ;
        al_rest(4) ;
        system("cls") ;
    }
    if ( num1 )
        printf ("%s sank and %s wone the game!",p_name[0],p_name[1]) ;
    else
        printf ("%s sank and %s wone the game!",p_name[1],p_name[0]) ;
    return 0;
}
