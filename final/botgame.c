#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

#define length 25

////////
extern int numb [2] ;
extern struct ship
{
    int n ;
    int m ;
    int* ptr ;
}s[2][400];

extern int bord [2][20][20] ;
extern int n , num ;
extern char p_name [2][25] ;
extern int x , y ;
extern char p [20][3] ;
int nhb ; // number of houses of bot ships
extern int max [2] ;
///////

extern void add ( int a , int b , int r ) ;
extern void remov ( int a , int b , int r ) ;
extern void chp ( int ) ;
extern void chek ( int , int , int ) ;
extern int asci_to_int ( int , char [] , int ) ;
extern void int_to_asci ( int , char [] ) ;
extern void fix ( int ) ;
extern void unfix ( int ) ;
extern int key_get_n ( ALLEGRO_FONT* , ALLEGRO_FONT* , ALLEGRO_FONT* , ALLEGRO_EVENT_QUEUE* , ALLEGRO_EVENT , ALLEGRO_BITMAP* ) ;
extern int key_get_num ( ALLEGRO_FONT* , ALLEGRO_FONT* , ALLEGRO_FONT* , ALLEGRO_EVENT_QUEUE* , ALLEGRO_EVENT , ALLEGRO_BITMAP* ) ;
extern int key_get_maxrepairing ( ALLEGRO_FONT* , ALLEGRO_FONT* , ALLEGRO_FONT* , ALLEGRO_EVENT_QUEUE* , ALLEGRO_EVENT , ALLEGRO_BITMAP* ) ;
void save ( int , int [] , int [] ) ;
int player_get_pnames ( ALLEGRO_FONT* , ALLEGRO_FONT* , ALLEGRO_FONT* , ALLEGRO_EVENT_QUEUE* , ALLEGRO_EVENT , ALLEGRO_BITMAP* ) ;
int player_get_coordinates ( ALLEGRO_FONT* , ALLEGRO_FONT* , ALLEGRO_FONT* , ALLEGRO_EVENT_QUEUE* , ALLEGRO_EVENT , ALLEGRO_BITMAP* ) ;
void bot_get_coordinates () ;
int  randn ( int n ) ;
int chekhouses ( int p [] , int a , int b ) ;
int gameloop_bot ( ALLEGRO_FONT* , ALLEGRO_FONT* , ALLEGRO_EVENT_QUEUE* , ALLEGRO_EVENT , ALLEGRO_BITMAP* , int [] , int [] ) ;
int shot_player ( int , int , int [] ) ;
int repair_player ( int , int , int [] ) ;
void bot ( int [] , int [] ) ;


int botgame ( ALLEGRO_FONT* font , ALLEGRO_FONT* font2 , ALLEGRO_FONT* font3 , ALLEGRO_EVENT_QUEUE* eq , ALLEGRO_EVENT ev , ALLEGRO_BITMAP* bt )
{
    int t = 1 ;
    while ( 1 )
    {
        switch ( t )
        {
            case -1 :
                return -1 ;
            case 1 :
                t = key_get_n (font,font2,font3,eq,ev,bt) ;
                break ;
            case 2 :
                t = key_get_num (font,font2,font3,eq,ev,bt) ;
                break ;
            case 3 :
                t = key_get_maxrepairing (font,font2,font3,eq,ev,bt) ;
                break ;
            case 4 :
                t = player_get_pnames (font,font2,font3,eq,ev,bt) ;
                break ;
            case 5 :
                t = player_get_coordinates (font,font2,font3,eq,ev,bt) ;
                break ;
            case 10 :
                bot_get_coordinates () ;
                return 11 ;
        }
    }
}

int player_get_pnames ( ALLEGRO_FONT* font , ALLEGRO_FONT* font2 , ALLEGRO_FONT* font3 , ALLEGRO_EVENT_QUEUE* eq , ALLEGRO_EVENT ev , ALLEGRO_BITMAP* bt )
{
    int q = 1 , t = 0 , r = 0 , a ;
    p_name [1][0] = 'B' ;
    p_name [1][1] = 'o' ;
    p_name [1][2] = 't' ;
    p_name [1][3] = 0 ;
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
            if ( t == 3 )
            {
                p_name[0][0] = 0 ;
                return t ;
            }
        }
        else if ( ev.type == ALLEGRO_EVENT_KEY_DOWN )
        {
            a = ev.keyboard.keycode ;
            if ( a < 27 && a > 0 && r < 24 )
            {
                p_name[0][r] = a + 96 ;
                r ++ ;
                p_name[0][r] = 0 ;
            }
            else if ( a == ALLEGRO_KEY_BACKSPACE )
            {
                r -- ;
                p_name [0][r] = 0 ;
            }
            else if ( a == ALLEGRO_KEY_ENTER )
            {
                return 5 ;
            }
        }
        else if ( ev.type == ALLEGRO_EVENT_TIMER )
            i += q ;
        if ( i == 255 || i == 0 )
        {
            q *= -1 ;
            i += q ;
        }
        if ( x <= 720 && x >= 480 && y >= 650 && y <= 750 )
        {
            al_draw_ellipse (600,700,122,52,al_map_rgb(255,255,255),3) ;
            t = 3 ;
        }
        else
            t = 0 ;
        al_draw_text(font,al_map_rgb(i,i,i),600,100,ALLEGRO_ALIGN_CENTER,"BATTLE SHIP") ;
        al_draw_filled_rectangle (375,300,825,430,al_map_rgb(175,255,255)) ;
        al_draw_text(font3,al_map_rgb(0,0,0),600,310,ALLEGRO_ALIGN_CENTER,"Please enter the name of players") ;
        al_draw_text(font3,al_map_rgb(0,0,0),500,340,ALLEGRO_ALIGN_CENTER,"player1 : ") ;
        al_draw_text(font3,al_map_rgb(0,0,0),550,340,ALLEGRO_ALIGN_LEFT,p_name[0]) ;
        al_draw_text(font3,al_map_rgb(0,0,0),500,380,ALLEGRO_ALIGN_CENTER,"player2 : ") ;
        al_draw_text(font3,al_map_rgb(0,0,0),550,380,ALLEGRO_ALIGN_LEFT,p_name[1]) ;
        al_draw_filled_ellipse (600,700,120,50,al_map_rgb(245,245,245)) ;
        al_draw_text(font2,al_map_rgb(0,0,0),600,680,ALLEGRO_ALIGN_CENTER,"Back") ;
        al_draw_bitmap(bt,x-30,y-30,NULL) ;
        al_flip_display() ;
    }
}

int player_get_coordinates ( ALLEGRO_FONT* font , ALLEGRO_FONT* font2 , ALLEGRO_FONT* font3 , ALLEGRO_EVENT_QUEUE* eq , ALLEGRO_EVENT ev , ALLEGRO_BITMAP* bt )
{
    int q = 1 , t = 0 , a , b , k ;
    char c [4] ;
    for ( int i = 1 ; 1 ; )
    {
        al_clear_to_color(al_map_rgb(0,0,0)) ;
        al_wait_for_event(eq,&ev) ;
        if ( ev.type == ALLEGRO_EVENT_MOUSE_AXES )
        {
            x = ev.mouse.x ;
            y = ev.mouse.y ;
        }
        else if ( ev.type == ALLEGRO_EVENT_TIMER )
            i += q ;
        else if ( ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN )
        {
            if ( t == 4 )
            {
                return t ;
            }
            else if ( t == 10 && bord [0][(a-571)/length][(b-286)/length] != 3 )
            {
                if ( bord [0][(a-571)/length][(b-286)/length] == 4 )
                {
                    remov ( (a-571)/length , (b-286)/length , 0 ) ;
                    bord [0][(a-571)/length][(b-286)/length] = 0 ;
                }
                else if ( k )
                {
                    if ( s[0][numb[0]].n )
                        chek (a,b,0) ;
                    else
                    {
                        bord [0][(a-571)/length][(b-286)/length] = 4 ;
                        add ( (a-571)/length , (b-286)/length , 0 ) ;
                    }
                }
                else if ( !k )
                    al_show_native_message_box (NULL,"BATTLE SHIP","Notice!","don't remain ship!",NULL,ALLEGRO_MESSAGEBOX_ERROR) ;
            }
        }
        else if ( ev.type == ALLEGRO_EVENT_KEY_DOWN )
        {
            if ( ev.keyboard.keycode == ALLEGRO_KEY_F )
            {
                fix ( 0 ) ;
                numb[0] ++ ;
            }
            else if ( ev.keyboard.keycode == ALLEGRO_KEY_ENTER )
            {
                unfix ( 0 ) ;
                return 10 ;
            }
        }
        if ( i == 255 || i == 0 )
        {
            q *= -1 ;
            i += q ;
        }
        if ( x <= 420 && x >= 180 && y >= 650 && y <= 750 )
        {
            al_draw_ellipse (300,700,122,52,al_map_rgb(255,255,255),3) ;
            t = 4 ;
        }
        else
            t = 0 ;
        k = num ;
        for ( int i = 0 ; i <= numb[0] ; i ++ )
        k -= s[0][i].n ;
        int_to_asci ( k , c ) ;
        al_draw_text(font,al_map_rgb(i,i,i),600,100,ALLEGRO_ALIGN_CENTER,"BATTLE SHIP") ;
        al_draw_filled_rectangle (60,400,460,550,al_map_rgb(175,255,255)) ;
        al_draw_text (font3,al_map_rgb(0,0,0),260,410,ALLEGRO_ALIGN_CENTER,"Select and remove : mouse buttons") ;
        al_draw_text (font3,al_map_rgb(0,0,0),260,440,ALLEGRO_ALIGN_CENTER,"Fix coordinates : f") ;
        al_draw_text (font3,al_map_rgb(0,0,0),260,470,ALLEGRO_ALIGN_CENTER,"End of arrangement : enter") ;
        al_draw_text (font3,al_map_rgb(0,0,0),260,500,ALLEGRO_ALIGN_CENTER,"remaining :") ;
        al_draw_text (font3,al_map_rgb(0,0,0),350,500,ALLEGRO_ALIGN_CENTER,c) ;
        al_draw_filled_ellipse (300,700,120,50,al_map_rgb(245,245,245)) ;
        al_draw_text(font2,al_map_rgb(0,0,0),300,680,ALLEGRO_ALIGN_CENTER,"Back") ;
        chp( 0 ) ;
        if ( x >= 571 && x < 571+(n)*length && y >= 286 && y < 286+(n)*length)
        {
            a = ((x-571)/length)*length+571 ;
            b = ((y-286)/length)*length+286 ;
            al_draw_rectangle (a,b,a+length,b+length,al_map_rgb(255,255,255),2) ;
            t = 10 ;
        }
        else
            al_draw_bitmap(bt,x-30,y-30,NULL) ;
        al_flip_display() ;
    }
}

int randn ( int n )
{
    return ( rand() % n ) ;
}

int chekhouses ( int p [] , int a , int b )
{
    int q = 0 ;
    for ( int i = 0 ; i < 8 ; i ++ )
        p [i] = 0 ;
    /*
        0 : top ;
        1 : top right ;
        2 : right ;
        3 : bottom right ;
        4 : bottom ;
        5 : bottom left ;
        6 : left ;
        7 : top left ;
    */
    if ( b > 0 && bord [1][a][b-1] == 0 )
    {
        p [0] = 1 ;
        q ++ ;
    }
    if ( b > 0 && a < n - 1 && bord [1][a+1][b-1] == 0 )
    {
        p [1] = 1 ;
        q ++ ;
    }
    if ( a < n - 1 && bord [1][a+1][b] == 0 )
    {
        p [2] = 1 ;
        q ++ ;
    }
    if ( a < n - 1 && b < n - 1 && bord [1][a+1][b+1] == 0 )
    {
        p [3] = 1 ;
        q ++ ;
    }
    if ( b < n - 1 && bord [1][a][b+1] == 0 )
    {
        p [4] = 1 ;
        q ++ ;
    }
    if ( a > 0 && b < n - 1 && bord [1][a-1][b+1] == 0 )
    {
        p [5] = 1 ;
        q ++ ;
    }
    if ( a > 0 && bord [1][a-1][b] == 0 )
    {
        p [6] = 1 ;
        q ++ ;
    }
    if ( b > 0 && a > 0 && bord [1][a-1][b-1] == 0 )
    {
        p [7] = 1 ;
        q ++ ;
    }
    return q ;
}

void bot_get_coordinates ()
{
    int t , q , z , a , b , e , w ;
    int p [8] ;
    q = randn ( num ) + 1 ; // number of ship houses ;
    t = num / q ; // number of ships ;
    numb [1] = t ;
    for ( int i = 0 ; i < t ; i ++ )
    {
        s[1][i].n = s[1][i].m = q ;
        s[1][i].ptr = malloc (sizeof(int)*2*q) ;
        a = randn (n) ;
        b = randn (n) ;
        if ( bord [1][a][b] == 0 )
        {
            s[1][i].ptr[0] = a ;
            s[1][i].ptr[1] = b ;
            bord [1][a][b] = 3 ;
            for ( int j = 2 ; j/2 < q ; j += 2 )
            {
                z = chekhouses ( p , a , b ) ;
                if ( z )
                {
                    e = randn ( z ) + 1  ;
                    for ( w = 0 ; e ; w ++ )
                        if ( p[w] == 1 )
                        {
                            e -- ;
                        }
                    w -- ;
                    switch ( w )
                    {
                        case 0 :
                            b -- ;
                            break ;
                        case 1 :
                            b -- ;
                            a ++ ;
                            break ;
                        case 2 :
                            a ++ ;
                            break ;
                        case 3 :
                            b ++ ;
                            a ++ ;
                            break ;
                        case 4 :
                            b ++ ;
                            break ;
                        case 5 :
                            b ++ ;
                            a -- ;
                            break ;
                        case 6 :
                            a -- ;
                            break ;
                        case 7 :
                            b -- ;
                            a -- ;
                            break ;
                    }
                    bord [1][a][b] = 3 ;
                    s[1][i].ptr[j] = a ;
                    s[1][i].ptr[j+1] = b ;
                }
                else
                {
                    for ( j -= 2 ; j >= 0 ; j -= 2 )
                        bord [1][s[1][i].ptr[j]][s[1][i].ptr[j+1]] = 0 ;
                    j = q ;
                    free ( s[1][i].ptr ) ;
                    i -- ;
                }
            }
        }
        else
        {
            free ( s[1][i].ptr ) ;
            i -- ;
        }
    }
    nhb = q ;
    return ;
}

int gameloop_bot ( ALLEGRO_FONT* font2 , ALLEGRO_FONT* font3 , ALLEGRO_EVENT_QUEUE* eq , ALLEGRO_EVENT ev , ALLEGRO_BITMAP* bt , int k [] , int max [] )
{
    ALLEGRO_FONT* font = al_load_font ("ALGER.TTF",18,NULL) ;
    FILE* file = fopen("actions/act1.txt","w+") ;
    int t = 0 , a , b ;
    while ( k[1] && k[0] )
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
            if ( t == 3 )
            {
                t = menu (font2,eq,ev,bt) ;
                while ( t != 1 )
                {
                    switch ( t )
                    {
                        case 3 :
                            save (2,k,max) ;
                        case 0 :
                            fclose (file) ;
                            return -1 ;
                        case 2 :
                            myaction (file,font2,eq,ev,bt) ;
                          t = menu (font2,eq,ev,bt) ;
                          break ;
                    }
                }
            }
            else if ( t == 8 )
            {
                if ( x >= 640 )
                {
                    saveaction ( file , (a-640)/length , (b-286)/length , 0 ) ;
                    shot_player ( (a-640)/length , (b-286)/length , k ) ;
                    if ( !k[1] )
                        break ;
                    bot ( max , k ) ;
                    al_rest (1.5) ;
                    al_clear_to_color(al_map_rgb(0,0,0)) ;
                    al_flip_display() ;
                    al_rest(1.5) ;
                }
                else
                {
                    t = repair_player ( (a-60)/length , (b-286)/length , max ) ;
                    if ( t )
                    {
                        saveaction ( file , (a-60)/length , (b-286)/length , 1 ) ;
                        bot ( max , k ) ;
                        al_rest (1.5) ;
                        al_clear_to_color(al_map_rgb(0,0,0)) ;
                        al_flip_display() ;
                        al_rest(1.5) ;
                    }
                }
            }
        }
        if ( x <= 1180 && x >= 940 && y >= 10 && y <= 110 )
        {
            al_draw_ellipse (1060,60,122,52,al_map_rgb(255,255,255),3) ;
            t = 3 ;
        }
        else
            t = 0 ;
        chapi (font3,k,max) ;
        chap ( 0 , font ) ;
        al_draw_filled_ellipse (1060,60,120,50,al_map_rgb(245,245,245)) ;
        al_draw_text(font2,al_map_rgb(0,0,0),1060,40,ALLEGRO_ALIGN_CENTER,"menu") ;
        if ( ( x >= 640 && x < 640+(n)*length && y >= 286 && y < 286+(n)*length ) || ( x >= 60 && x < 60+(n)*length && y >= 286 && y < 286+(n)*length ) )
        {
            if ( x >= 640 )
            {
                a = ((x-640)/length)*length+640 ;
                b = ((y-286)/length)*length+286 ;
            }
            else
            {
                a = ((x-60)/length)*length+60 ;
                b = ((y-286)/length)*length+286 ;
            }
            al_draw_rectangle (a,b,a+length,b+length,al_map_rgb(255,255,255),2) ;
            t = 8 ;
        }
        else
            al_draw_bitmap(bt,x-30,y-30,NULL) ;
        al_flip_display() ;
    }
    fclose (file) ;
    if ( k[1] )
        return 9 ;
    else
        return 8 ;
}

int shot_player ( int a , int b , int k [] )
{
    int sw = 1 ;
    if ( bord [1][a][b] == 3 )
    {
        bord [1][a][b] = 1 ;
        al_show_native_message_box (NULL,"BATTLE SHIP","GOOD SHOT!","This was the coordinate of the ship!",NULL,NULL) ;
        for ( int i = 0 ; i < numb[1] && sw ; i ++ )
            for ( int j = 0 ; j/2 < s[1][i].n && sw ; j += 2 )
                if ( s[1][i].ptr[j] == a && s[1][i].ptr[j+1] == b )
                {
                    s[1][i].m -- ;
                    sw = 1 ;
                    if ( s[1][i].m == 0 )
                    {
                        al_show_native_message_box (NULL,"BATTLE SHIP","WELL DONE!","The ship sank!",NULL,NULL) ;
                        k[1] -- ;
                    }
                }
    }
    else
        al_show_native_message_box (NULL,"BATTLE SHIP","BAD SHOT!","This coordinate is empty!",NULL,NULL) ;
    return ;
}

int repair_player ( int a , int b , int max [] )
{
    int sw = 1 ;
    if ( max [0] == 0 )
    {
        al_show_native_message_box (NULL,"BATTLE SHIP","Notice!","The number of repairing completed",NULL,NULL) ;
        return 0 ;
    }
    if ( bord [0][a][b] == 3 )
    {
        al_show_native_message_box (NULL,"BATTLE SHIP","Notice!","This point is not damaged!",NULL,NULL) ;
        return 0 ;
    }
    if ( bord [0][a][b] == 0 )
    {
        al_show_native_message_box (NULL,"BATTLE SHIP","Notice!","This is not the point of the ship!",NULL,NULL) ;
        return 0 ;
    }
    for ( int i = 0 ; i < numb[0] && sw ; i ++ )
        for ( int j = 0 ; j/2 < s[0][i].n && sw ; j += 2 )
            if ( s[0][i].ptr[j] == a && s[0][i].ptr[j+1] == b )
            {
                sw = 0 ;
                if ( s[0][i].m )
                {
                    s[0][i].m ++ ;
                    bord [0][a][b] = 3 ;
                    max[0] -- ;
                    al_show_native_message_box (NULL,"BATTLE SHIP","Notice!","The repair was done successfully",NULL,NULL) ;
                    return 1 ;
                }
                else
                {
                    al_show_native_message_box (NULL,"BATTLE SHIP","Notice!","Can not repair this coordinates\nbecause this ship sank completely!",NULL,NULL) ;
                    return 0 ;
                }
            }
    if ( sw )
        al_show_native_message_box (NULL,"BATTLE SHIP","Notice!","This coordinates is not ship!",NULL,NULL) ;
    return 0 ;
}

void bot ( int max [] , int k [] )
{
    int t = randn (2) , sw = 1 , a , b ;
    if ( t && max[1] ) // repair
    {
        for ( int i = 0 ; i < numb[1] ; i ++ )
        {
            if ( s[1][i].m < nhb && s[1][i].m )
            {
                for ( int j = 0 ; j/2 < s[1][i].n ; j += 2 )
                {
                    a = s[1][i].ptr[j] ;
                    b = s[1][i].ptr[j+1] ;
                    if ( bord [1][a][b] == 1 )
                    {
                        bord [1][a][b] = 3 ;
                        s[1][i].m ++ ;
                        max [1] -- ;
                        return ;
                    }
                }
            }
        }
    }
    // shot
    do
    {
        a = randn (n) ;
        b = randn (n) ;
    } while ( bord [0][a][b] == 1 ) ;
    if ( bord [0][a][b] == 3 )
    {
        sw = 1 ;
        bord [0][a][b] = 1 ;
        for ( int i = 0 ; i < numb[0] && sw ; i ++ )
            for ( int j = 0 ; j/2 < s[0][i].n && sw ; j += 2 )
                if ( s[0][i].ptr[j] == a && s[0][i].ptr[j+1] == b )
                {
                    s[0][i].m -- ;
                    sw = 0 ;
                    if ( s[0][i].m == 0 )
                    {
                        k [0] -- ;
                    }
                }
    }
    return ;
}
