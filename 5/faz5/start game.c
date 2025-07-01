#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>

void chap_w () ; // chap welcome to !
int chap_s () ; // chap BATTLE SHIP !
void bye () ; // quit the game !
int what () ; // what will happen !

int start ()
{
    char c [5] ;
    printf ("Are you ready?\nyes or no : ") ;
    scanf ("%s",c) ;
    if ( c[0] == 'n' || c[0] == 'N' )
    {
        bye() ;
        return -1 ;
    }
    else if ( c[0] != 'y' && c[0] != 'Y' )
    {
        do
        {
            system("cls") ;
            printf ("I don't understand, please enter it agane!\nyes or no : ") ;
            scanf ("%s",c) ;
        } while ( c[0] != 'y' && c[0] != 'Y' && c[0] != 'n' && c[0] != 'N' ) ;
        if ( c[0] == 'n' || c[0] == 'N' )
        {
            bye() ;
            return -1 ;
        }
    }
    system("cls") ;
    int t ;
    chap_w () ;
    t = chap_s () ;
    if ( t == -1 )
        return -1 ;
    system("cls") ;
    return what() ;
}

int what ()
{
    char s [10] ;
    do
    {
        printf ("What will you do?\nCreat a new game or continue a previous game?\ncreate or continue : ") ;
        scanf ("%s",s) ;
    } while ( s[1] != 'r' && s[1] != 'R' && s[1] != 'o' && s[1] != 'O' ) ;
    if ( s [1] == 'r' || s [1] == 'R' )
    {
        do
        {
            system("cls") ;
            printf ("get information from the file or keyboard?\nfile or keyboard : ") ;
            scanf ("%s",s) ;
        } while ( s[0] != 'f' && s[0] != 'F' && s[0] != 'k' && s[0] != 'K' ) ;
        if ( s[0] == 'f' || s[0] == 'F' )
            return 2 ;
        else
            return 1 ;
    }
    else
        return 3 ;
}

void bye ()
{
    system("cls") ;
    printf ("Ok!\nbye....") ;
    al_rest(2) ;
    return  ;
}

void chap_w ()
{
    char s [] = "Welcome to " ;
    for ( int i = 0 ; i < 12 ; i ++ )
    {
        printf ("%c",s[i]) ;
        al_rest(0.5) ;
    }
    return ;
}

int chap_s ()
{
    char c ;
    FILE *file = fopen ("start.txt","r") ;
    if ( !file )
    {
        printf ("start file not found!") ;
        return -1 ;
    }
    printf ("\n\n\n\n\n\n") ;
    fscanf (file ,"%c",&c) ;
    while ( !feof (file) )
    {
        printf ("%c",c) ;
        if ( c == '\n' )
            printf ("\t\t\t\t") ;
        fscanf (file,"%c",&c) ;
    }
    fclose (file) ;
    al_rest(8) ;
    system("cls") ;
    return 0 ;
}
