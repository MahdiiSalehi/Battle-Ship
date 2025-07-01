#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>

/////////////////\\\\\\\\\\\\\\\\\

int bord1 [9][9][2] ;
int ships [27][3][2] ;
int k[2] ;
FILE* file1 ;

////////////////\\\\\\\\\\\\\\\\\\\\\

extern int getf ( int* , int* , char [][25] ) ; // getting basic information from the file !
extern int game_loop ( int* , int* , char [][25] , int , int ) ; // game loop!
extern int start () ;//start the game !
extern void getk ( int* , int* , char [][25]) ; // getting basic information from the keyboard !
extern void bye () ; // quit the game !
extern void save () ; // save game !
extern int open_save ( int* , int* , int* , char [][25] , int* ) ; // open save game !

/*
    0 : water  ~
    1 : no bomb  O
    2 : bomb!  *
    3 : ship  #
*/

int main()
{
    int n , num1 , num2 , t , t2 , q = 0 ;
    char p_name [2][25] ;
    file1 = fopen ("saves/input.txt","w+") ;
    t = start() ;
    system("cls") ;
    switch ( t )
    {
        case -1 :
            return 0 ;
        case 1 :
            getk( &n , &num1 , p_name ) ;
            num2 = num1 ;
            break ;
        case 2 :
            t2 = getf ( &n , &num1 , p_name ) ;
            if ( t2 == -1 )
                return 0 ;
            num2 = num1 ;
            break ;
        case 3 :
            t2 = open_save ( &n , &num1 , &num2 , p_name , &q ) ;
            if ( t2 == -1 )
                return 0 ;
            break ;
    }
    t = game_loop ( &num1 , &num2 , p_name , n , q ) ;
    if ( t == -1 )
    {
        char s [10] ;
        do
        {
            system("cls") ;
            printf ("Are you want to save this game?\nyes or no : ") ;
            scanf ("%s",s) ;
        } while ( s[0] != 'y' && s[0] != 'Y' && s[0] != 'n' && s[0] != 'N' ) ;
        if ( s[0] == 'y' || s[0] == 'Y' )
        {
            save () ;
        }
        bye() ;
    }
    return 0;
}
