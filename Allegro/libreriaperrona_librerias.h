#include <iostream>
#include <string>
#include <cstring>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <Windows.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

int menu();

typedef struct TsAnimacion {
	ALLEGRO_BITMAP* img0;
	ALLEGRO_BITMAP* img1;
	ALLEGRO_BITMAP* img2;
	ALLEGRO_BITMAP* img3;
	ALLEGRO_BITMAP* img4;
	ALLEGRO_BITMAP* img5;
} _animaciones;



