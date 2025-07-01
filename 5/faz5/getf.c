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

void get_nf ( FILE* , int* , int* ) ; //get n & num  ;
void get_i_cof ( FILE* , int , int , char [][25] ) ; //get p_names & coordinates ;
void sefreshkon ( int ) ; // all elements = 0 ;
int ship ( int , int , char , int , int ) ; // Determine the ship position !


int getf ( int* n , int* num , char p_name [][25] )
{
    FILE *file = fopen ("input.txt","r") ;
    if ( !file )
    {
        printf ("can not open input file") ;
        return -1 ;
    }
    get_nf ( file , n , num ) ;
    sefreshkon ( *n ) ;
    get_i_cof ( file , (*n) , (*num) , p_name ) ;
    fclose(file) ;
    system("cls") ;
    return 0;
}

void get_nf( FILE* file , int* n , int* num )
{
    fscanf (file,"%d",n) ;
    fscanf (file,"%d",num) ;
    fprintf (file1,"%d %d\n",*n,*num) ;
    return ;
}

void get_i_cof ( FILE* file , int n , int num , char p_name [][25] )
{
    int x , y , a ;
    char c ;
    for ( int k = 0 ; k < 2 ; k ++ )
    {
        fscanf (file,"%s",p_name[k]) ;
        fprintf (file1,"%s\n",p_name[k]) ;
        for ( int i = 0 ; i < num ; i ++ )
        {
            fscanf (file,"%d%d%c%c",&x,&y,&c,&c) ;
            fprintf (file1,"%d %d %c\n",x,y,c) ;
            a = ship ( x , y , c , k , n ) ;
            if ( a )
                i -- ;
        }
    }
    return ;
}

void sefreshkon ( int n )
{
    for ( int i = 0 ; i < 2 ; i ++ )
        for ( int j = 0 ; j < n ; j ++ )
            for ( int k = 0 ; k < n ; k ++ )
                bord1 [k][j][i] = 0 ;
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
