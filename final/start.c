#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

/*
   -1 : start ;
    0 : quit ;
    1 : new game ;
    2 : load save ;
    3 : new game , keyboard ;
    4 : new game , file ;
    10 : start game... ;
*/

extern int x , y ;
extern int numb [2] ;
extern struct ship
{
    int n ;
    int m ;
    int* ptr ;
}s[2][400];

extern int bord [2][20][20] ;
extern int n ;
extern char p_name [2][25] ;
int mainmenu ( ALLEGRO_FONT* , ALLEGRO_FONT* , ALLEGRO_EVENT_QUEUE* , ALLEGRO_EVENT , ALLEGRO_BITMAP* ) ;
int newgame ( ALLEGRO_FONT* , ALLEGRO_FONT* , ALLEGRO_EVENT_QUEUE* , ALLEGRO_EVENT , ALLEGRO_BITMAP* ) ;
int new_file ( ALLEGRO_FONT* , ALLEGRO_FONT* , ALLEGRO_EVENT_QUEUE* , ALLEGRO_EVENT , ALLEGRO_BITMAP* ) ;
void loadsave ( int* , int [] , int [] ) ;
extern int new_keyboard ( ALLEGRO_FONT* , ALLEGRO_FONT* , ALLEGRO_FONT* , ALLEGRO_EVENT_QUEUE* , ALLEGRO_EVENT , ALLEGRO_BITMAP* ) ;
extern int botgame ( ALLEGRO_FONT* , ALLEGRO_FONT* , ALLEGRO_FONT* , ALLEGRO_EVENT_QUEUE* , ALLEGRO_EVENT , ALLEGRO_BITMAP* ) ;

int start ( ALLEGRO_FONT* font2 , ALLEGRO_FONT* font3 , ALLEGRO_EVENT_QUEUE* eq , ALLEGRO_EVENT ev , ALLEGRO_BITMAP* bt )
{
    int q = 1 , sw = 1 , t = -1 ;
    ALLEGRO_FONT* font = al_load_font("ALGER.TTF",150,NULL) ;
    while ( sw )
    {
        switch ( t )
        {
            case -1 :
                t = mainmenu (font,font2,eq,ev,bt) ;
                break ;
            case 0 :
                sw = 0 ;
                break ;
            case 1 :
                t = newgame(font,font2,eq,ev,bt) ;
                break ;
            case 2 :
                sw = 0 ;
                break ;
            case 3 :
                t = new_keyboard (font,font2,font3,eq,ev,bt) ;
                break ;
            case 4 :
                t = botgame (font,font2,font3,eq,ev,bt) ;
                break ;
            case 10 :
            case 11 :
                sw = 0 ;
                break ;
        }
    }
    al_clear_to_color(al_map_rgb(0,0,0)) ;
    al_flip_display() ;
    al_destroy_font(font) ;
    return t ;
}

int mainmenu ( ALLEGRO_FONT* font , ALLEGRO_FONT* font2 , ALLEGRO_EVENT_QUEUE* eq , ALLEGRO_EVENT ev , ALLEGRO_BITMAP* bt )
{
    int q = 1 , t = -1 ;
    for ( int i = 1 ; 1 ; )
    {
        al_clear_to_color(al_map_rgb(0,0,0)) ;
        al_wait_for_event(eq,&ev) ;
        if ( ev.type == ALLEGRO_EVENT_MOUSE_AXES )
        {
            x = ev.mouse.x ;
            y = ev.mouse.y ;
        }
        else if ( ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN )
        {
            if ( t == 1 || t == 0 || t == 2 )
                return t ;
        }
        else if ( ev.type == ALLEGRO_EVENT_TIMER )
            i += q ;
        if ( i == 255 || i == 0 )
        {
            q *= -1 ;
            i += q ;
        }
        if ( x <= 720 && x >= 480 && y >= 350 && y <= 450 )
        {
            al_draw_ellipse (600,400,122,52,al_map_rgb(255,255,255),3) ;
            t = 1 ;
        }
        else if ( x <= 720 && x >= 480 && y >= 500 && y <= 600 )
        {
            al_draw_ellipse (600,550,122,52,al_map_rgb(255,255,255),3) ;
            t = 2 ;
        }
        else if ( x <= 720 && x >= 480 && y >= 650 && y <= 750 )
        {
            al_draw_ellipse (600,700,122,52,al_map_rgb(255,255,255),3) ;
            t = 0 ;
        }
        else
            t = -1 ;
        al_draw_text(font,al_map_rgb(i,i,i),600,100,ALLEGRO_ALIGN_CENTER,"BATTLE SHIP") ;
        al_draw_filled_ellipse (600,400,120,50,al_map_rgb(245,245,245)) ;
        al_draw_text(font2,al_map_rgb(0,0,0),600,380,ALLEGRO_ALIGN_CENTER,"New game") ;
        al_draw_filled_ellipse (600,550,120,50,al_map_rgb(245,245,245)) ;
        al_draw_text(font2,al_map_rgb(0,0,0),600,530,ALLEGRO_ALIGN_CENTER,"Continue") ;
        al_draw_filled_ellipse (600,700,120,50,al_map_rgb(245,245,245)) ;
        al_draw_text(font2,al_map_rgb(0,0,0),600,680,ALLEGRO_ALIGN_CENTER,"Quit") ;
        al_draw_bitmap(bt,x-30,y-30,NULL) ;
        al_flip_display() ;
    }
}


int newgame ( ALLEGRO_FONT* font , ALLEGRO_FONT* font2 , ALLEGRO_EVENT_QUEUE* eq , ALLEGRO_EVENT ev , ALLEGRO_BITMAP* bt )
{
    int q = 1 , t = 0 ;
    for ( int i = 1 ; 1 ; )
    {
        al_clear_to_color(al_map_rgb(0,0,0)) ;
        al_wait_for_event(eq,&ev) ;
        if ( ev.type == ALLEGRO_EVENT_MOUSE_AXES )
        {
            x = ev.mouse.x ;
            y = ev.mouse.y ;
        }
        else if ( ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN )
        {
            if ( t == -1 || t == 3 || t == 4 )
                return t ;
        }
        else if ( ev.type == ALLEGRO_EVENT_TIMER )
            i += q ;
        if ( i == 255 || i == 0 )
        {
            q *= -1 ;
            i += q ;
        }
        if ( x <= 720 && x >= 480 && y >= 350 && y <= 450 )
        {
            al_draw_ellipse (600,400,122,52,al_map_rgb(255,255,255),3) ;
            t = 4 ;
        }
        else if ( x <= 720 && x >= 480 && y >= 500 && y <= 600 )
        {
            al_draw_ellipse (600,550,122,52,al_map_rgb(255,255,255),3) ;
            t = 3 ;
        }
        else if ( x <= 720 && x >= 480 && y >= 650 && y <= 750 )
        {
            al_draw_ellipse (600,700,122,52,al_map_rgb(255,255,255),3) ;
            t = -1 ;
        }
        else
            t = 0 ;
        al_draw_text(font,al_map_rgb(i,i,i),600,100,ALLEGRO_ALIGN_CENTER,"BATTLE SHIP") ;
        al_draw_filled_ellipse (600,400,120,50,al_map_rgb(245,245,245)) ;
        al_draw_text(font2,al_map_rgb(0,0,0),600,380,ALLEGRO_ALIGN_CENTER,"One player") ;
        al_draw_filled_ellipse (600,550,120,50,al_map_rgb(245,245,245)) ;
        al_draw_text(font2,al_map_rgb(0,0,0),600,530,ALLEGRO_ALIGN_CENTER,"Tow player") ;
        al_draw_filled_ellipse (600,700,120,50,al_map_rgb(245,245,245)) ;
        al_draw_text(font2,al_map_rgb(0,0,0),600,680,ALLEGRO_ALIGN_CENTER,"Back") ;
        al_draw_bitmap(bt,x-30,y-30,NULL) ;
        al_flip_display() ;
    }
}

void loadsave ( int* r , int k [] , int max [] )
{
    FILE* file = fopen ("saves/save.txt","r") ;
    fseek(file,0,SEEK_SET) ;
    fscanf (file,"%d%d",&n,r) ;
    for ( int i = 0 ; i < 2 ; i ++ )
    {
        fscanf (file,"%s%d%d%d",p_name[i],&k[i],&max[i],&numb[i]) ;
        for ( int j = 0 ; j < numb [i] ; j ++ )
        {
            fscanf (file,"%d%d",&s[i][j].n,&s[i][j].m) ;
            s[i][j].ptr = malloc (sizeof(int)*s[i][j].n*2) ;
            for ( int t = 0 ; t/2 < s[i][j].n ; t += 2 )
            {
                fscanf (file,"%d%d",&s[i][j].ptr[t],&s[i][j].ptr[t+1]) ;
            }
        }
        for ( int j = 0 ; j < n ; j ++ )
            for ( int t = 0 ; t < n ; t ++ )
                fscanf (file,"%d",&bord[i][t][j]) ;
    }
    return ;
}
