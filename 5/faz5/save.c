#include <stdio.h>
#include <allegro5/allegro.h>

/*
    0 : water  ~
    1 : injured  O & *
    3 : ship  #
*/

extern int bord1 [9][9][2] ;
extern int ships [27][3][2] ;
extern int k [2] ;
extern FILE* file1 ;

extern void sefreshkon ( int ) ; // all elements = 0 ;
extern int ship ( int , int , char , int , int ) ; // Determine the ship position !
extern int shot ( int , int ) ; // ship sank or not ;
int get_sh_cof ( FILE* , int , int ) ;  //get shot coordinates ;

void save ()
{
    FILE *file2 = fopen ("saves/save.txt","w") ;
    if ( !file2 )
    {
        system("cls") ;
        printf ("I could not open the save game file1, the game could not be saved.") ;
        al_rest(3) ;
    }
    else
    {
        char c ;
        fseek(file1,0,SEEK_SET) ;
        fscanf (file1,"%c",&c) ;
        while ( !feof (file1) )
        {
            fprintf (file2,"%c",c) ;
            fscanf (file1,"%c",&c) ;
        }
    }
    return ;
}

int open_save ( int* n , int* num1 , int* num2 , char p_name [][25] , int* q2 )
{
    int x , y , a , t , q ;
    char c ;
    FILE* file2 = fopen ("saves/save.txt","r") ;
    if ( !file2 )
    {
        system("cls") ;
        printf ("I could not open save file") ;
        al_rest(3) ;
        return -1 ;
    }
    fscanf (file2,"%d",n) ;
    fscanf (file2,"%d",num1) ;
    *num2 = *num1 ;
    sefreshkon(*n) ;
    for ( int k = 0 ; k < 2 ; k ++ )
    {
        fscanf (file2,"%s",p_name[k]) ;
        for ( int i = 0 ; i < (*num1) ; i ++ )
        {
            fscanf (file2,"%d%d%c%c",&x,&y,&c,&c) ;
            a = ship ( x , y , c , k , n ) ;
            if ( a )
                i -- ;
        }
    }
    t = get_sh_cof ( file2 , n , q ) ;
    while ( !feof (file2) )
    {
        if ( t )
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
        *q2 = q ;
        t = get_sh_cof ( file2 , n , q ) ;
    }
    fseek(file2,0,SEEK_SET) ;
    fscanf(file2,"%c",&c) ;
    while ( !feof(file2) )
    {
        fprintf (file1,"%c",c) ;
        fscanf(file2,"%c",&c) ;
    }
    fclose (file2) ;
    return ;
}

int get_sh_cof ( FILE* file , int n , int q )
{
    int  x , y , p , t ;
    fscanf (file,"%d",&x) ;
    fscanf (file,"%d",&y) ;
    x -- ;
    y -- ;
    if ( q )
        q = 0 ;
    else
        q = 1 ;
    if ( y < n && y >= 0 && x < n && x >= 0 )
    {
        if ( bord1 [y][x][q] == 3 )
        {
            bord1 [y][x][q] = 1 ;
            p = ((y+1)*10) + x + 1 ;
            t = shot ( p , q ) ;
            if ( t )
                return 1 ;
        }
    }
    return 0 ;
}
