#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

/*
   -1 : back to new game ;
    1 : get n ;
    2 : get num ;
    3 : get number of repairing ;
    4 : get p_names ;
    5 : get coordinates ;
   10 : start game... ;
*/

#define length 25

////////
extern int numb [2] ;
extern struct ship
{
    int n ;
    int m ;
    int* ptr ;
}s[2][400];
void add ( int a , int b , int r )
{
    s[r][numb[r]].n ++ ;
    int* p = malloc ( sizeof(int) * (s[r][numb[r]].n) * 2 ) ;
    for ( int i = 0 ; i/2 < s[r][numb[r]].n - 1 ; i += 2 )
    {
        p[i] = s[r][numb[r]].ptr [i] ;
        p[i+1] = s[r][numb[r]].ptr [i+1] ;
    }
    p [(s[r][numb[r]].n-1)*2] = a ;
    p [(s[r][numb[r]].n-1)*2+1] = b ;
    free (s[r][numb[r]].ptr) ;
    s[r][numb[r]].ptr = p ;
    return ;
}
void remov ( int a , int b , int r )
{
    int i , sw = 1 ;
    for ( i = 0 ; i/2 < s[r][numb[r]].n && sw ; i += 2 )
        if ( s[r][numb[r]].ptr[i] == a && s[r][numb[r]].ptr[i+1] == b )
            sw = 0 ;
    for ( ; i/2 < s[r][numb[r]].n ; i ++ )
        s[r][numb[r]].ptr [i-2] = s[r][numb[r]].ptr [i] ;
    s[r][numb[r]].n -- ;
    return ;
}


extern int bord [2][20][20] ;
extern int n , num ;
extern char p_name [2][25] ;
extern int x , y ;
extern int max [2] ;

///////

int key_get_n ( ALLEGRO_FONT* , ALLEGRO_FONT* , ALLEGRO_FONT* , ALLEGRO_EVENT_QUEUE* , ALLEGRO_EVENT , ALLEGRO_BITMAP* ) ;
int key_get_maxrepairing ( ALLEGRO_FONT* , ALLEGRO_FONT* , ALLEGRO_FONT* , ALLEGRO_EVENT_QUEUE* , ALLEGRO_EVENT , ALLEGRO_BITMAP* ) ;
int key_get_num ( ALLEGRO_FONT* , ALLEGRO_FONT* , ALLEGRO_FONT* , ALLEGRO_EVENT_QUEUE* , ALLEGRO_EVENT , ALLEGRO_BITMAP* ) ;
int key_get_pnames ( ALLEGRO_FONT* , ALLEGRO_FONT* , ALLEGRO_FONT* , ALLEGRO_EVENT_QUEUE* , ALLEGRO_EVENT , ALLEGRO_BITMAP* ) ;
int key_get_coordinates ( ALLEGRO_FONT* , ALLEGRO_FONT* , ALLEGRO_FONT* , ALLEGRO_EVENT_QUEUE* , ALLEGRO_EVENT , ALLEGRO_BITMAP* ) ;
void chp ( int ) ;
void chek ( int , int , int ) ;
int asci_to_int ( int , char [] , int ) ;
void int_to_asci ( int , char [] ) ;
void fix ( int ) ;
void unfix ( int ) ;


int new_keyboard ( ALLEGRO_FONT* font , ALLEGRO_FONT* font2 , ALLEGRO_FONT* font3 , ALLEGRO_EVENT_QUEUE* eq , ALLEGRO_EVENT ev , ALLEGRO_BITMAP* bt )
{
    int t = 1 ;
    while ( 1 )
    {
        switch ( t )
        {
            case -1 :
                return 1 ;
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
                t = key_get_pnames (font,font2,font3,eq,ev,bt) ;
                break ;
            case 5 :
                t = key_get_coordinates (font,font2,font3,eq,ev,bt) ;
                break ;
            case 10 :
                return 10 ;
        }
    }
}

int key_get_n ( ALLEGRO_FONT* font , ALLEGRO_FONT* font2 , ALLEGRO_FONT* font3 , ALLEGRO_EVENT_QUEUE* eq , ALLEGRO_EVENT ev , ALLEGRO_BITMAP* bt )
{
    int q = 1 , t = 0 , r = 0 , a ;
    char c [] = "  " ;
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
            if ( t == -1 )
                return t ;
        }
        else if ( ev.type == ALLEGRO_EVENT_KEY_DOWN )
        {
            a = ev.keyboard.keycode ;
            if ( r < 2 )
            {
                if ( a < 37 && a > 26 )
                {
                    if ( a == 27 && r )
                    {
                        c [r] = '0' ;
                        r ++ ;
                    }
                    else if ( a != 27 )
                    {
                        c [r] = a + 21 ;
                        r ++ ;
                    }
                }
            }
            if ( a == ALLEGRO_KEY_BACKSPACE && r )
            {
                r -- ;
                c [r] = 0 ;
            }
            else if ( a == ALLEGRO_KEY_ENTER && r )
            {
                n = asci_to_int ( r , c , 20 ) ;
                return 2 ;
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
            t = -1 ;
        }
        else
            t = 0 ;
        al_draw_text(font,al_map_rgb(i,i,i),600,100,ALLEGRO_ALIGN_CENTER,"BATTLE SHIP") ;
        al_draw_filled_rectangle (375,300,825,430,al_map_rgb(175,255,255)) ;
        al_draw_text(font3,al_map_rgb(0,0,0),600,310,ALLEGRO_ALIGN_CENTER,"Please enter length of the side") ;
        al_draw_text(font3,al_map_rgb(0,0,0),600,340,ALLEGRO_ALIGN_CENTER,"( The maximum value will be 20 )") ;
        al_draw_text(font3,al_map_rgb(0,0,0),530,380,ALLEGRO_ALIGN_LEFT,"N = ") ;
        al_draw_text(font3,al_map_rgb(0,0,0),595,380,ALLEGRO_ALIGN_LEFT,c) ;
        al_draw_filled_ellipse (600,700,120,50,al_map_rgb(245,245,245)) ;
        al_draw_text(font2,al_map_rgb(0,0,0),600,680,ALLEGRO_ALIGN_CENTER,"Back") ;
        al_draw_bitmap(bt,x-30,y-30,NULL) ;
        al_flip_display() ;
    }
}

int key_get_num ( ALLEGRO_FONT* font , ALLEGRO_FONT* font2 , ALLEGRO_FONT* font3 , ALLEGRO_EVENT_QUEUE* eq , ALLEGRO_EVENT ev , ALLEGRO_BITMAP* bt )
{
    int q = 1 , t = 0 , r = 0 , a ;
    char c [] = "   " , s [4] ;
    int_to_asci ( n*n , s ) ;
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
            if ( t == 1 )
                return t ;
        }
        else if ( ev.type == ALLEGRO_EVENT_KEY_DOWN )
        {
            a = ev.keyboard.keycode ;
            if ( r < 3 )
            {
                if ( a < 37 && a > 26 )
                {
                    if ( a == 27 && r )
                    {
                        c [r] = '0' ;
                        r ++ ;
                    }
                    else if ( a != 27 )
                    {
                        c [r] = a + 21 ;
                        r ++ ;
                    }
                }
            }
            if ( a == ALLEGRO_KEY_BACKSPACE && r )
            {
                r -- ;
                c [r] = 0 ;
            }
            else if ( a == ALLEGRO_KEY_ENTER && r )
            {
                num = asci_to_int ( r , c , 20 ) ;
                return 3 ;
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
            t = 1 ;
        }
        else
            t = 0 ;
        al_draw_text(font,al_map_rgb(i,i,i),600,100,ALLEGRO_ALIGN_CENTER,"BATTLE SHIP") ;
        al_draw_filled_rectangle (325,300,875,430,al_map_rgb(175,255,255)) ;
        al_draw_text(font3,al_map_rgb(0,0,0),600,310,ALLEGRO_ALIGN_CENTER,"Please enter the max number of points of ships") ;
        al_draw_text(font3,al_map_rgb(0,0,0),600,340,ALLEGRO_ALIGN_CENTER,"( The maximum value will be        )") ;
        al_draw_text(font3,al_map_rgb(0,0,0),755,340,ALLEGRO_ALIGN_CENTER,s) ;
        al_draw_text(font3,al_map_rgb(0,0,0),530,380,ALLEGRO_ALIGN_LEFT,"NUM = ") ;
        al_draw_text(font3,al_map_rgb(0,0,0),640,380,ALLEGRO_ALIGN_LEFT,c) ;
        al_draw_filled_ellipse (600,700,120,50,al_map_rgb(245,245,245)) ;
        al_draw_text(font2,al_map_rgb(0,0,0),600,680,ALLEGRO_ALIGN_CENTER,"Back") ;
        al_draw_bitmap(bt,x-30,y-30,NULL) ;
        al_flip_display() ;
    }
}

int key_get_maxrepairing ( ALLEGRO_FONT* font , ALLEGRO_FONT* font2 , ALLEGRO_FONT* font3 , ALLEGRO_EVENT_QUEUE* eq , ALLEGRO_EVENT ev , ALLEGRO_BITMAP* bt )
{
    int q = 1 , t = 0 , r = 0 , a ;
    char c [] = "  " ;
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
            if ( t == 2 )
                return t ;
        }
        else if ( ev.type == ALLEGRO_EVENT_KEY_DOWN )
        {
            a = ev.keyboard.keycode ;
            if ( r < 1 )
            {
                if ( a < 37 && a > 26 )
                {
                    c [r] = a + 21 ;
                    r ++ ;
                }
            }
            if ( a == ALLEGRO_KEY_BACKSPACE && r )
            {
                r -- ;
                c [r] = 0 ;
            }
            else if ( a == ALLEGRO_KEY_ENTER && r )
            {
                max[0] = max[1] = asci_to_int ( r , c , 20 ) ;
                return 4 ;
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
            t = 2 ;
        }
        else
            t = 0 ;
        al_draw_text(font,al_map_rgb(i,i,i),600,100,ALLEGRO_ALIGN_CENTER,"BATTLE SHIP") ;
        al_draw_filled_rectangle (375,300,825,430,al_map_rgb(175,255,255)) ;
        al_draw_text(font3,al_map_rgb(0,0,0),600,310,ALLEGRO_ALIGN_CENTER,"Please enter the max number of repairing") ;
        al_draw_text(font3,al_map_rgb(0,0,0),600,340,ALLEGRO_ALIGN_CENTER,"( The maximum value will be 9 )") ;
        al_draw_text(font3,al_map_rgb(0,0,0),530,380,ALLEGRO_ALIGN_LEFT,"Max = ") ;
        al_draw_text(font3,al_map_rgb(0,0,0),615,380,ALLEGRO_ALIGN_LEFT,c) ;
        al_draw_filled_ellipse (600,700,120,50,al_map_rgb(245,245,245)) ;
        al_draw_text(font2,al_map_rgb(0,0,0),600,680,ALLEGRO_ALIGN_CENTER,"Back") ;
        al_draw_bitmap(bt,x-30,y-30,NULL) ;
        al_flip_display() ;
    }
}

int key_get_pnames ( ALLEGRO_FONT* font , ALLEGRO_FONT* font2 , ALLEGRO_FONT* font3 , ALLEGRO_EVENT_QUEUE* eq , ALLEGRO_EVENT ev , ALLEGRO_BITMAP* bt )
{
    int q = 1 , t = 0 , r = 0 , s = 0 , a ;
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
                p_name[1][0] = 0 ;
                return t ;
            }
        }
        else if ( ev.type == ALLEGRO_EVENT_KEY_DOWN )
        {
            a = ev.keyboard.keycode ;
            if ( a < 27 && a > 0 && r < 24 )
            {
                p_name[s][r] = a + 96 ;
                r ++ ;
                p_name[s][r] = 0 ;
            }
            else if ( a == ALLEGRO_KEY_BACKSPACE )
            {
                r -- ;
                p_name [s][r] = 0 ;
            }
            else if ( a == ALLEGRO_KEY_ENTER )
            {
                if ( !s )
                {
                    s = 1 ;
                    r = 0 ;
                }
                else
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

int key_get_coordinates ( ALLEGRO_FONT* font , ALLEGRO_FONT* font2 , ALLEGRO_FONT* font3 , ALLEGRO_EVENT_QUEUE* eq , ALLEGRO_EVENT ev , ALLEGRO_BITMAP* bt )
{
    int q = 1 , t = 0 , r = 0 , a , b , k ;
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
            else if ( t == 10 && bord [r][(a-571)/length][(b-286)/length] != 3 )
            {
                if ( bord [r][(a-571)/length][(b-286)/length] == 4 )
                {
                    remov ( (a-571)/length , (b-286)/length , r ) ;
                    bord [r][(a-571)/length][(b-286)/length] = 0 ;
                }
                else if ( k )
                {
                    if ( s[r][numb[r]].n )
                        chek (a,b,r) ;
                    else
                    {
                        bord [r][(a-571)/length][(b-286)/length] = 4 ;
                        add ( (a-571)/length , (b-286)/length , r ) ;
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
                fix ( r ) ;
                numb[r] ++ ;
            }
            else if ( ev.keyboard.keycode == ALLEGRO_KEY_ENTER )
            {
                unfix( r ) ;
                if ( !r )
                    r ++ ;
                else
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
        for ( int i = 0 ; i <= numb[r] ; i ++ )
        k -= s[r][i].n ;
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
        chp( r ) ;
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

void chp ( int r )
{
    for ( int i = 0 ; i < n ; i ++ )
    {
        for ( int j = 0 ; j < n ; j ++ )
        {
            if ( bord [r][j][i] == 0 )
                al_draw_filled_rectangle (571+(j*length),286+(i*length),571+((1+j)*length),286+((1+i)*length),al_map_rgb(0,0,200)) ;
            else if ( bord [r][j][i] == 3 )
                al_draw_filled_rectangle (571+(j*length),286+(i*length),571+((1+j)*length),286+((1+i)*length),al_map_rgb(255,69,0)) ;
            else
                al_draw_filled_rectangle (571+(j*length),286+(i*length),571+((1+j)*length),286+((1+i)*length),al_map_rgb(255,215,0)) ;
        }
    }
    for ( int i = 1 ; i < n ; i ++ )
        al_draw_line (571+(i*length),286,571+(i*length),286+(n)*length,al_map_rgb(0,0,0),2) ;
    for ( int i = 1 ; i < n ; i ++ )
        al_draw_line (571,286+(i*length),571+(n)*length,286+(i*length),al_map_rgb(0,0,0),2) ;
    return ;
}

void chek ( int a , int b , int r )
{
    int sw = 0 ;
    a = (a-571)/length ;
    b = (b-286)/length ;
    if ( a > 0 && b > 0 &&  bord [r][a-1][b-1] == 4 )
        sw = 1 ;
    else if ( b > 0 && bord [r][a][b-1] == 4 )
        sw = 1 ;
    else if ( a < n - 1 && b > 0 && bord [r][a+1][b-1] == 4 )
        sw = 1 ;
    else if ( a > 0 && bord [r][a-1][b] == 4 )
        sw = 1 ;
    else if ( a < n - 1 && bord [r][a+1][b] == 4 )
        sw = 1 ;
    else if ( a > 0 && b < n - 1 && bord [r][a-1][b+1] == 4 )
        sw = 1 ;
    else if ( b < n - 1 && bord [r][a][b+1] == 4 )
        sw = 1 ;
    else if ( a < n - 1 && b < n - 1 && bord [r][a+1][b+1] == 4 )
        sw = 1 ;
    if ( sw )
    {
        bord [r][a][b] = 4 ;
        add ( a , b , r ) ;
    }
    else
    {
        al_show_native_message_box (NULL,"BATTLE SHIP","Notice!","ship points must be connected",NULL,ALLEGRO_MESSAGEBOX_WARN) ;
    }
    return ;
}

void fix ( int r )
{
    for ( int i = 0 ; i/2 < s[r][numb[r]].n ; i += 2 )
        bord [r][s[r][numb[r]].ptr[i]][s[r][numb[r]].ptr[i+1]] = 3 ;
    return ;
}

void unfix ( int r )
{
    for ( int i = 0 ; i/2 < s[r][numb[r]].n ; i += 2 )
        bord [r][s[r][numb[r]].ptr[i]][s[r][numb[r]].ptr[i+1]] = 0 ;
    free (s[r][numb[r]].ptr) ;
    s[r][numb[r]].n = 0 ;
}

int asci_to_int ( int r , char c [] , int max )
{
    int n = 0 ;
    for ( int i = 0 ; i < r ; i ++ )
    {
        n = (n*10) + c[i] - 48 ;
    }
    if ( n > max )
        return 20 ;
    else
        return n ;
}

void int_to_asci ( int n , char c [] )
{
    int i ;
    char s [4] ;
    for ( i = 0 ; n ; n /= 10 , i ++ )
    {
        s[i] = n%10 + 48 ;
    }
    c[i] = 0 ;
    i -- ;
    for ( int j = 0 ; i >= 0 ; j ++ , i -- )
        c [j] = s [i] ;
    return ;
}
