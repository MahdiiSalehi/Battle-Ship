#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#define width 1200
#define height 900
#define length 25

/*
    0 : water  ~
    1 : injured  O & *
    3 : ship  #
    4 : previous select ;
*/

struct ship
{
    int n ;
    int m ;
    int* ptr ;
}s[2][400];


extern int start ( ALLEGRO_FONT* , ALLEGRO_FONT* , ALLEGRO_EVENT_QUEUE* , ALLEGRO_EVENT , ALLEGRO_BITMAP* ) ;
extern int gameloop ( ALLEGRO_FONT* , ALLEGRO_FONT* , ALLEGRO_EVENT_QUEUE* , ALLEGRO_EVENT , ALLEGRO_BITMAP* , int [] , int [] , int ) ;
extern int gameloop_bot ( ALLEGRO_FONT* , ALLEGRO_FONT* , ALLEGRO_EVENT_QUEUE* , ALLEGRO_EVENT , ALLEGRO_BITMAP* , int [] , int [] ) ;
extern void loadsave ( int* , int [] , int [] ) ;
void fre ( int* , int [] , int [] ) ;

//
int bord [2][20][20] = {0};
int n , num ;
char p_name [2][25] ;
int numb [2] = {} ; // number of ships ;
int x = 1500 , y = 1500 ; //the coordinates of mouse ;
int max [2] ;
//

int main()
{
    int t = -1 , sw = 1 , r = 0 ;
    int k [2] ;
    p_name [0][0] = 0 ;
    p_name [1][0] = 0 ;
    srand(time(NULL)) ;
    for ( int i = 0 ; i < 2 ; i ++ )
        for ( int j = 0 ; j < 400 ; j ++ )
            s[i][j].n = 0 ;
    al_init() ;
    al_init_font_addon() ;
    al_init_ttf_addon() ;
    al_init_primitives_addon() ;
    al_install_mouse() ;
    al_install_keyboard () ;
    al_init_image_addon() ;
    al_set_new_display_flags (ALLEGRO_DIRECT3D_INTERNAL) ;
    ALLEGRO_DISPLAY* display = al_create_display (1200,900) ;
    ALLEGRO_FONT* font2 = al_load_font("ALGER.TTF",36,NULL) ;
    ALLEGRO_FONT* font3 = al_load_font("CENTAUR.TTF",30,NULL) ;
    ALLEGRO_EVENT_QUEUE* eq = al_create_event_queue() ;
    ALLEGRO_TIMER* timer = al_create_timer(1.0/80) ;
    ALLEGRO_EVENT ev ;
    ALLEGRO_BITMAP* bt = al_load_bitmap ("keshti.png") ;
    al_convert_mask_to_alpha (bt,al_map_rgb(255,255,255)) ;
    al_register_event_source(eq,al_get_timer_event_source(timer)) ;
    al_register_event_source(eq,al_get_mouse_event_source()) ;
    al_register_event_source(eq,al_get_keyboard_event_source()) ;
    al_hide_mouse_cursor(display) ;
    al_start_timer(timer) ;
    while ( sw )
    {
        switch ( t )
        {
            case -1 :
                fre (&r,k,max) ;
                t = start (font2,font3,eq,ev,bt) ;
                break ;
            case 0 :
            case 8 :
            case 9 :
                sw = 0 ;
                break ;
            case 2 :
                loadsave (&r,k,max) ;
                if ( r != 2 )
                    t = gameloop (font2,font3,eq,ev,bt,k,max,r) ;
                else
                    t = gameloop_bot (font2,font3,eq,ev,bt,k,max) ;
                break ;
            case 10 :
                k [0] = numb [0] ;
                k [1] = numb [1] ;
                for ( int m = 0 ; m < 2 ; m ++ )
                    for ( int i = 0 ; i < numb[m] ; i ++ )
                        s[m][i].m = s[m][i].n ;
                t = gameloop (font2,font3,eq,ev,bt,k,max,r) ;
                break ;
            case 11 :
                k [0] = numb [0] ;
                k [1] = numb [1] ;
                for ( int i = 0 ; i < numb[0] ; i ++ )
                    s[0][i].m = s[0][i].n ;
                t = gameloop_bot (font2,font3,eq,ev,bt,k,max) ;
                break ;
        }
    }
    al_destroy_display(display) ;
    if ( t == 8 )
        printf ("%s wone the game\n",p_name[0]) ;
    else if ( t == 9 )
        printf ("%s wone the game\n",p_name[1]) ;
    printf ("bye...") ;
    al_rest(1) ;
    return 0 ;
}

void fre ( int* r , int k [] , int max [] )
{
    for ( int i = 0 ; i < 2 ; i ++ )
    {
        for ( int j = 0 ; j < n ; j ++ )
            for ( int t = 0 ; t < n ; t ++ )
                bord [i][t][j] = 0 ;
        for ( int j = 0 ; j < numb [i] ; j ++ )
        {
            for ( int t = 0 ; t/2 < s[i][j].n ; t += 2 )
                s[i][j].ptr[t] = s[i][j].ptr[t+1] = 0 ;
            s[i][j].n = 0 ;
            s[i][j].m = 0 ;
        }
        p_name[i][0] = max[i] = k [i] = numb[i] = 0 ;
    }
    n = (*r) = 0 ;
}
