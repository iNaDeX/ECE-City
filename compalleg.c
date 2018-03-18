#include "compalleg.h"

BITMAP *page=NULL;
int page_couleur_fond;

char touche;
char bouton;
int mouse_click;
int mouse_unclick;
int key_press[KEY_MAX];
int key_unpress[KEY_MAX];

int mouse_depx;
int mouse_depy;

void initialiser_allegro(int w, int h)
{
    if (page) return;

    COLOR_MAP global_trans_table;
    PALETTE pal;

    allegro_init();
    install_keyboard();
    set_keyboard_rate(0,0);
    install_mouse();
    install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,NULL); //////////// INDISPENSABLE!!

    create_trans_table(&global_trans_table, pal, 128, 128, 128, NULL);

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,w,h,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    changer_nom_fenetre("ECE City");

    if (get_color_depth() == 8)
	 color_map = &global_trans_table;
      else
	 set_trans_blender(128, 128, 128, 100);

    show_mouse(screen);

    page=create_bitmap(TAILLE_FENETRE_W,TAILLE_FENETRE_H);

    page_couleur_fond = PAGE_COULEUR_INIT;

    effacer_page();

    afficher_page();
}

void fermer_allegro()
{
    if (!page) return;
    destroy_bitmap(page);
    page=NULL;
    allegro_exit();
}

void effacer_page()
{
    if (!page) return;
    clear_to_color(page, page_couleur_fond);
}

void afficher_page()
{
    if (!page) return;
    acquire_screen();
    blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    release_screen();
}

void line_epaisse(BITMAP *bmp, int x1, int y1, int x2, int y2, int coul)
{
    line(bmp, x1, y1, x2, y2, coul);
    line(bmp, x1+1, y1, x2+1, y2, coul);
    line(bmp, x1-1, y1, x2-1, y2, coul);
    line(bmp, x1, y1+1, x2, y2+1, coul);
    line(bmp, x1, y1-1, x2, y2-1, coul);
}

void rafraichir_clavier_souris()
{
    static int mouse_prev, mouse_now;
    static int key_prev[KEY_MAX], key_now[KEY_MAX];
    int k;

    mouse_prev = mouse_now;
    mouse_now = mouse_b;
    mouse_click = mouse_now & ~mouse_prev;
    mouse_unclick = ~mouse_now & mouse_prev;

    bouton = '\0';
    if (mouse_click&1)
        bouton = 'g';
    if (mouse_click&2)
        bouton = 'd';
    if (mouse_click&4)
        bouton = 'm';

    for (k=0; k<KEY_MAX; k++)
    {
        key_prev[k] = key_now[k];
        key_now[k] = key[k];
        key_press[k] = key_now[k] && !key_prev[k];
        key_unpress[k] = !key_now[k] && key_prev[k];
    }

    touche = '\0';
    while (keypressed())
        touche = (char)readkey();

    get_mouse_mickeys(&mouse_depx, &mouse_depy);
}

BITMAP *chargerImage(const char* nomFichierImage)
{
    BITMAP *bmp;
    bmp=load_bitmap(nomFichierImage,NULL);
    if (bmp==NULL)
    {
        allegro_message("pas pu trouver/charger %s",nomFichierImage);
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    printf("Image charg\202e : %s\n", nomFichierImage);
    return bmp;
}

void changer_nom_fenetre(const char* ch)
{
    set_window_title(ch);
}

SAMPLE* chargerSon(const char* nomfichier)
{
    SAMPLE* nouv;
    nouv=load_sample(nomfichier);
    if(nouv==NULL)
    {
        allegro_message("pas pu trouver/charger %s",nomfichier);
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    return nouv;
}
