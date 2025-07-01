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
extern int k [2] ;
extern FILE* file1 ;

extern void chap ( int , int ) ; // chap board !
extern void chap_i ( int , int , char [][25] ) ; // chap informations !
int shot ( int , int ) ; // ship sank or not ;
int get_sh_co ( int , int ) ;  //get shot coordinates ;

int game_loop ( int* num1 , int* num2 , char p_name [][25] , int n , int q )
{
    int t ;
    while ( (*num1) && (*num2) )
    {
        chap_i ( (*num1) , (*num2) , p_name ) ;
        chap ( n , q ) ;
        t = get_sh_co ( n , q ) ;
        if ( t == -1 )
            return -1 ;
        else if ( t )
        {
            if ( q )
                (*num2) -- ;
            else
                (*num1) -- ;
        }
        if ( q )
            q = 0 ;
        else
            q = 1 ;
        al_rest(4) ;
        system("cls") ;
    }
    if ( (*num1) )
        printf ("%s sank and %s wone the game!",p_name[0],p_name[1]) ;
    else
        printf ("%s sank and %s wone the game!",p_name[1],p_name[0]) ;
    return 0 ;
}

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

int get_sh_co ( int n , int q )
{
    int a = 1 , x , y , p , r ;
    printf ("Please enter the shot coordinates . ( Between 1 and %d )  !\n[ if you want to quit game, enter -1 ]\nx = ",n) ;
    scanf ("%d",&x) ;
    if ( x == -1 )
        return -1 ;
    printf ("y = ") ;
    scanf ("%d",&y) ;
    if ( y == -1 )
        return -1 ;
    fprintf(file1,"%d %d\n",x,y) ;
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

