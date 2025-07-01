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
extern int n ;
extern char p_name [2][25] ;
extern int x , y ;
char p [20][3] = {
"1" ,
"2" ,
"3" ,
"4" ,
"5" ,
"6" ,
"7" ,
"8" ,
"9" ,
"10" ,
"11" ,
"12" ,
"13" ,
"14" ,
"15" ,
"16" ,
"17" ,
"18" ,
"19" ,
"20" } ;

///////

extern void int_to_asci ( int , char [] ) ;

void chap ( int , ALLEGRO_FONT* ) ;
void chapi ( ALLEGRO_FONT* , int [] , int [] ) ;
void shot ( int* , int , int , int [] ) ;
int repair ( int* , int , int , int [] ) ;
int menu ( ALLEGRO_FONT* , ALLEGRO_EVENT_QUEUE* , ALLEGRO_EVENT , ALLEGRO_BITMAP* ) ;
void saveaction ( FILE* , int , int , int ) ;
void myaction ( FILE* , ALLEGRO_FONT* , ALLEGRO_EVENT_QUEUE* , ALLEGRO_EVENT , ALLEGRO_BITMAP* ) ;
/*
    code 0 : shot ;
    code 1 : repair ;
*/
void save ( int , int [] , int [] ) ;
/*
    n , r ;
    p_name , k , max , numb ;
    while ( numb ) s.n , s.m , while ( s.n ) s.ptr ;
    while ( n ) bord ;
*/

int gameloop ( ALLEGRO_FONT* font2 , ALLEGRO_FONT* font3 , ALLEGRO_EVENT_QUEUE* eq , ALLEGRO_EVENT ev , ALLEGRO_BITMAP* bt , int k [] , int max [], int r )
{
    ALLEGRO_FONT* font = al_load_font ("ALGER.TTF",18,NULL) ;
    FILE* file[2] = {fopen("actions/act1.txt","w+"),fopen("actions/act2.txt","w+")} ;
    int t = 0 , a , b ;
    while ( k[0] && k[1] )
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
                            save (r,k,max) ;
                        case 0 :
                            fclose (file[0]) ;
                            fclose (file[1]) ;
                            return -1 ;
                        case 2 :
                            myaction (file[r],font2,eq,ev,bt) ;
                          t = menu (font2,eq,ev,bt) ;
                          break ;
                    }
                }
            }
            else if ( t == 8 )
            {
                if ( x >= 640 )
                {
                    saveaction ( file[r] , (a-640)/length , (b-286)/length , 0 ) ;
                    shot ( &r , (a-640)/length , (b-286)/length , k ) ;
                    al_rest (1.5) ;
                    al_clear_to_color(al_map_rgb(0,0,0)) ;
                    al_flip_display() ;
                    al_rest(1.5) ;
                }
                else
                {
                    t = repair ( &r , (a-60)/length , (b-286)/length , max ) ;
                    if ( t )
                    {
                        if ( r )
                            t = 0 ;
                        else
                            t = 1 ;
                        saveaction ( file[t] , (a-60)/length , (b-286)/length , 1 ) ;
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
        chap ( r , font ) ;
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
    fclose (file[0]) ;
    fclose (file[1]) ;
    if ( k[0] )
        return 8 ;
    else
        return 9 ;
}


void chap ( int r , ALLEGRO_FONT* font )
{
    int a , b ;
    for ( int i = 0 ; i < n ; i ++ )
        for ( int j = 0 ; j < n ; j ++ )
        {
            a = 60+(j*length) ;
            b = 286+(i*length) ;
            if ( bord [r][j][i] == 0 )
                al_draw_filled_rectangle (a,b,a+length,b+length,al_map_rgb(0,0,200)) ;
            else if ( bord [r][j][i] == 3 )
                al_draw_filled_rectangle (a,b,a+length,b+length,al_map_rgb(255,215,0)) ;
            else
                al_draw_filled_rectangle (a,b,a+length,b+length,al_map_rgb(255,69,0)) ;
        }
    if ( r == 0 )
        r = 1 ;
    else
        r = 0 ;
    for ( int i = 0 ; i < n ; i ++ )
        for ( int j = 0 ; j < n ; j ++ )
        {
            a = 640+(j*length) ;
            b = 286+(i*length) ;
            if ( bord [r][j][i] == 1 )
                al_draw_filled_rectangle (a,b,a+length,b+length,al_map_rgb(255,69,0)) ;
            else
                al_draw_filled_rectangle (a,b,a+length,b+length,al_map_rgb(0,0,200)) ;
        }
    al_draw_filled_rectangle (35,286,60,286+(n*length),al_map_rgb(0,191,255)) ;
    al_draw_filled_rectangle (615,286,640,286+(n*length),al_map_rgb(0,191,255)) ;
    al_draw_filled_rectangle (60,286-length,60+(n*length),286,al_map_rgb(0,191,255)) ;
    al_draw_filled_rectangle (640,286-length,640+(n*length),286,al_map_rgb(0,191,255)) ;
    for ( int i = 0 ; i < n ; i ++ )
        al_draw_text (font,al_map_rgb(0,0,0),47,290+(i*length),ALLEGRO_ALIGN_CENTER,p[i]) ;
    for ( int i = 0 ; i < n ; i ++ )
        al_draw_text (font,al_map_rgb(0,0,0),627,290+(i*length),ALLEGRO_ALIGN_CENTER,p[i]) ;
    for ( int i = 0 ; i < n ; i ++ )
        al_draw_text (font,al_map_rgb(0,0,0),72+(i*length),289-length,ALLEGRO_ALIGN_CENTER,p[i]) ;
    for ( int i = 0 ; i < n ; i ++ )
        al_draw_text (font,al_map_rgb(0,0,0),652+(i*length),289-length,ALLEGRO_ALIGN_CENTER,p[i]) ;
    for ( int i = 0 ; i <= n ; i ++ )
        al_draw_line (640+(i*length),286-length,640+(i*length),286+(n+1)*length,al_map_rgb(0,0,0),2) ;
    for ( int i = 0 ; i < n ; i ++ )
        al_draw_line (615,286+(i*length),640+(n)*length,286+(i*length),al_map_rgb(0,0,0),2) ;
    for ( int i = 0 ; i <= n ; i ++ )
        al_draw_line (60+(i*length),286-length,60+(i*length),286+(n+1)*length,al_map_rgb(0,0,0),2) ;
    for ( int i = 0 ; i < n ; i ++ )
        al_draw_line (35,286+(i*length),60+(n)*length,286+(i*length),al_map_rgb(0,0,0),2) ;
    return ;
}

void chapi ( ALLEGRO_FONT* font3 , int k [] , int max [] )
{
    char c [4][4] ;
    int_to_asci ( k[0] , c[0] ) ;
    int_to_asci ( k[1] , c[1] ) ;
    int_to_asci ( max[0] , c[2] ) ;
    int_to_asci ( max[1] , c[3] ) ;
    al_draw_filled_rectangle (60,100,350,230,al_map_rgb(175,255,255)) ;
    al_draw_filled_rectangle (640,100,930,230,al_map_rgb(175,255,255)) ;
    al_draw_text (font3,al_map_rgb(0,0,0),80,110,ALLEGRO_ALIGN_LEFT,p_name[0]) ;
    al_draw_text (font3,al_map_rgb(0,0,0),80,140,ALLEGRO_ALIGN_LEFT,"remaining ships : ") ;
    al_draw_text (font3,al_map_rgb(0,0,0),280,140,ALLEGRO_ALIGN_LEFT,c[0]) ;
    al_draw_text (font3,al_map_rgb(0,0,0),80,170,ALLEGRO_ALIGN_LEFT,"remaining repairing : ") ;
    al_draw_text (font3,al_map_rgb(0,0,0),320,170,ALLEGRO_ALIGN_LEFT,c[2]) ;
    al_draw_text (font3,al_map_rgb(0,0,0),660,110,ALLEGRO_ALIGN_LEFT,p_name[1]) ;
    al_draw_text (font3,al_map_rgb(0,0,0),660,140,ALLEGRO_ALIGN_LEFT,"remaining ships : ") ;
    al_draw_text (font3,al_map_rgb(0,0,0),860,140,ALLEGRO_ALIGN_LEFT,c[1]) ;
    al_draw_text (font3,al_map_rgb(0,0,0),660,170,ALLEGRO_ALIGN_LEFT,"remaining repairing : ") ;
    al_draw_text (font3,al_map_rgb(0,0,0),900,170,ALLEGRO_ALIGN_LEFT,c[3]) ;
    return ;
}

void shot ( int* r , int a , int b , int k [] )
{
    int sw = 1 ;
    if ( *r )
        *r = 0 ;
    else
        *r = 1 ;
    int m = *r ;
    if ( bord [m][a][b] == 3 )
    {
        bord [m][a][b] = 1 ;
        al_show_native_message_box (NULL,"BATTLE SHIP","GOOD SHOT!","This was the coordinate of the ship!",NULL,NULL) ;
        for ( int i = 0 ; i < numb[m] && sw ; i ++ )
            for ( int j = 0 ; j/2 < s[m][i].n && sw ; j += 2 )
                if ( s[m][i].ptr[j] == a && s[m][i].ptr[j+1] == b )
                {
                    s[m][i].m -- ;
                    sw = 0 ;
                    if ( s[m][i].m == 0 )
                    {
                        al_show_native_message_box (NULL,"BATTLE SHIP","WELL DONE!","This ship sank!",NULL,NULL) ;
                        k[m] -- ;
                    }
                }
    }
    else
        al_show_native_message_box (NULL,"BATTLE SHIP","BAD SHOT!","This coordinate is empty!",NULL,NULL) ;
    return ;
}

int repair ( int * r  , int a , int b , int max [] )
{
    int m = (*r) , sw = 1 ;
    if ( max [m] == 0 )
    {
        al_show_native_message_box (NULL,"BATTLE SHIP","Notice!","The number of repairing completed",NULL,NULL) ;
        return 0 ;
    }
    if ( bord [m][a][b] == 3 )
    {
        al_show_native_message_box (NULL,"BATTLE SHIP","Notice!","This point is not damaged!",NULL,NULL) ;
        return 0 ;
    }
    if ( bord [m][a][b] == 0 )
    {
        al_show_native_message_box (NULL,"BATTLE SHIP","Notice!","This is not the point of the ship!",NULL,NULL) ;
        return 0 ;
    }
    for ( int i = 0 ; i < numb[m] && sw ; i ++ )
        for ( int j = 0 ; j/2 < s[m][i].n && sw ; j += 2 )
            if ( s[m][i].ptr[j] == a && s[m][i].ptr[j+1] == b )
            {
                sw = 0 ;
                if ( s[m][i].m )
                {
                    s[m][i].m ++ ;
                    bord [m][a][b] = 3 ;
                    max[m] -- ;
                    al_show_native_message_box (NULL,"BATTLE SHIP","Notice!","The repair was done successfully",NULL,NULL) ;
                    if ( m == 0 )
                        *r = 1 ;
                    else
                        *r = 0 ;
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
    return 0;
}

int menu ( ALLEGRO_FONT* font2 , ALLEGRO_EVENT_QUEUE* eq , ALLEGRO_EVENT ev , ALLEGRO_BITMAP* bt )
{
    int t = -1 , q = 1 ;
    ALLEGRO_FONT* font = al_load_font("ALGER.TTF",150,NULL) ;
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
            if ( t == 1 || t == 0 || t == 2 || t == 3 )
                return t ;
        }
        else if ( ev.type == ALLEGRO_EVENT_TIMER )
            i += q ;
        if ( i == 255 || i == 0 )
        {
            q *= -1 ;
            i += q ;
        }
        if ( x <= 720 && x >= 480 && y >= 310 && y <= 410 )
        {
            al_draw_ellipse (600,360,122,52,al_map_rgb(255,255,255),3) ;
            t = 1 ;
        }
        else if ( x <= 720 && x >= 480 && y >= 460 && y <= 560 )
        {
            al_draw_ellipse (600,510,122,52,al_map_rgb(255,255,255),3) ;
            t = 2 ;
        }
        else if ( x <= 720 && x >= 480 && y >= 610 && y <= 710 )
        {
            al_draw_ellipse (600,660,122,52,al_map_rgb(255,255,255),3) ;
            t = 3 ;
        }
        else if ( x <= 720 && x >= 480 && y >= 760 && y <= 860 )
        {
            al_draw_ellipse (600,810,122,52,al_map_rgb(255,255,255),3) ;
            t = 0 ;
        }
        else
            t = -1 ;
        al_draw_text(font,al_map_rgb(i,i,i),600,100,ALLEGRO_ALIGN_CENTER,"BATTLE SHIP") ;
        al_draw_filled_ellipse (600,360,120,50,al_map_rgb(245,245,245)) ;
        al_draw_text(font2,al_map_rgb(0,0,0),600,340,ALLEGRO_ALIGN_CENTER,"Resume") ;
        al_draw_filled_ellipse (600,510,120,50,al_map_rgb(245,245,245)) ;
        al_draw_text(font2,al_map_rgb(0,0,0),600,490,ALLEGRO_ALIGN_CENTER,"My actions") ;
        al_draw_filled_ellipse (600,660,120,50,al_map_rgb(245,245,245)) ;
        al_draw_text(font2,al_map_rgb(0,0,0),600,640,ALLEGRO_ALIGN_CENTER,"Save & quit") ;
        al_draw_filled_ellipse (600,810,120,50,al_map_rgb(245,245,245)) ;
        al_draw_text(font2,al_map_rgb(0,0,0),600,790,ALLEGRO_ALIGN_CENTER,"Quit") ;
        al_draw_bitmap(bt,x-30,y-30,NULL) ;
        al_flip_display() ;
    }
}

void saveaction ( FILE* file , int a , int b , int c )
{
    if ( c == 0 )
        fprintf (file,"Shot ") ;
    else
        fprintf (file,"Repair ") ;
    fprintf (file,"%d %d\n",a+1,b+1) ;
    return ;
}

void myaction ( FILE* file , ALLEGRO_FONT* font2 , ALLEGRO_EVENT_QUEUE* eq , ALLEGRO_EVENT ev , ALLEGRO_BITMAP* bt )
{
    int a , b , t = 0 ;
    ALLEGRO_FONT* font = al_load_font("ALGER.TTF",22,NULL) ;
    char s [9] , c [2][3] ;
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
                return ;
        }
        if ( x <= 720 && x >= 480 && y >= 760 && y <= 860 )
        {
            al_draw_ellipse (600,810,122,52,al_map_rgb(255,255,255),3) ;
            t = -1 ;
        }
        else
            t = 0 ;
        fseek (file,0,SEEK_SET) ;
        fscanf (file,"%s",s) ;
        for ( int i = 0 ; !feof (file) ; i ++ )
        {
            fscanf (file,"%d%d",&a,&b) ;
            int_to_asci ( a , c[0] ) ;
            int_to_asci ( b , c[1] ) ;
            al_draw_text (font,al_map_rgb(255,255,255),10,10+(i*25),ALLEGRO_ALIGN_LEFT,s) ;
            al_draw_text (font,al_map_rgb(255,255,255),100,10+(i*25),ALLEGRO_ALIGN_LEFT,c[0]) ;
            al_draw_text (font,al_map_rgb(255,255,255),120,10+(i*25),ALLEGRO_ALIGN_LEFT,c[1]) ;
            fscanf (file,"%s",s) ;
        }
        al_draw_filled_ellipse (600,810,120,50,al_map_rgb(245,245,245)) ;
        al_draw_text(font2,al_map_rgb(0,0,0),600,790,ALLEGRO_ALIGN_CENTER,"Back") ;
        al_draw_bitmap(bt,x-30,y-30,NULL) ;
        al_flip_display() ;
    }
    return ;
}

void save ( int r , int k [] , int max [] )
{
    FILE* file = fopen ("saves/save.txt","w") ;
    fprintf (file,"%d %d\n",n,r) ;
    for ( int i = 0 ; i < 2 ; i ++ )
    {
        fprintf (file,"%s %d %d %d\n",p_name[i],k[i],max[i],numb[i]) ;
        for ( int j = 0 ; j < numb[i] ; j ++ )
        {
            fprintf (file,"%d %d ",s[i][j].n,s[i][j].m) ;
            for ( int t = 0 ; t/2 < s[i][j].n ; t += 2 )
                fprintf (file,"%d %d ",s[i][j].ptr[t],s[i][j].ptr[t+1]) ;
            fprintf (file,"\n") ;
        }
        for ( int j = 0 ; j < n ; j ++ )
        {
            for ( int t = 0 ; t < n ; t ++ )
                fprintf (file,"%d ",bord[i][t][j]) ;
            fprintf (file,"\n") ;
        }
    }
    fclose (file) ;
    return ;
}
