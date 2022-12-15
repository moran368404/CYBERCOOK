#include "libreriaperrona_funciones.h"

ALLEGRO_DISPLAY* ventana;
ALLEGRO_FONT* cookie;
ALLEGRO_TIMER* segundoTimer;
ALLEGRO_TIMER* fpsTimer;
ALLEGRO_EVENT_QUEUE* queue;

int ancho = 896;
int alto = 768;

void jugar();

void eleccion_De_imagen(TsAnimacion imagen, int band[], int i);
void eleccionScaledimagenes(TsAnimacion chef, int botones[], int tamReX, int tamReY, int tamDesX, int tamDesY, int posX, int posY, int i);
void FundidoANegro(ALLEGRO_BITMAP* img);
int comosejuega();
int instrucciones(ALLEGRO_BITMAP* img, ALLEGRO_EVENT evento);

int menu()
{
	if (!al_init())
	{
		al_show_native_message_box(NULL, "ERROR CRITICO", "ERROR 404", "Hubo un error", NULL, ALLEGRO_MESSAGEBOX_QUESTION);
	}

	int ancho = 896;
	int alto = 768;

	// INICILIZAICON/INSTALACION DE ADDONS
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_mouse();
	al_init_image_addon();
	al_install_keyboard();
	al_install_audio();
	al_init_acodec_addon();

	if (!al_is_audio_installed())
	{
		al_show_native_message_box(NULL, "ERROR CRITICO", "ERROR 404", "Hubo un error con el audio", NULL, ALLEGRO_MESSAGEBOX_QUESTION);
	}

	int anchoW = GetSystemMetrics(SM_CXSCREEN);
	int altoW = GetSystemMetrics(SM_CYSCREEN);

	// DEFINICION DE VENTANA Y DE LA FUENTE
	ventana = al_create_display(ancho, alto);
	cookie = al_load_font("fuentes/Symtext.ttf",100,0);

	// DEFINICION DE LOS TIMERS DE FPS Y DE SEGUNDOS
	segundoTimer = al_create_timer(1.0);
	fpsTimer = al_create_timer(1.0/10);
	
	queue = al_create_event_queue();
	
	// COLORES RESERVADOS
	ALLEGRO_COLOR blanco = al_map_rgb(255,255,255);
	ALLEGRO_COLOR  azar = al_map_rgb(34, 23, 67);

	// IMAGENES DEL MENU
	TsAnimacion menu;
	menu.img0 = al_load_bitmap("imagenes/fondos/menu_null.png");
	menu.img1 = al_load_bitmap("imagenes/fondos/menu_jugar.png");
	menu.img2 = al_load_bitmap("imagenes/fondos/menu_instrucciones.png");
	menu.img3 = al_load_bitmap("imagenes/fondos/menu_comosejuega.png");
	menu.img4 = al_load_bitmap("imagenes/fondos/menu_salir.png");

	// IMAGENES DEL CHEF ANIMACION
	TsAnimacion chef;
	chef.img0 = al_load_bitmap("imagenes/0.png");
	chef.img1 = al_load_bitmap("imagenes/1.png");
	chef.img2 = al_load_bitmap("imagenes/2.png");
	chef.img3 = al_load_bitmap("imagenes/3.png");
	chef.img4 = al_load_bitmap("imagenes/4.png");

	// IMAGENES RANDOM DE MENUS E INSTRUCICONES
	TsAnimacion imag;
	imag.img0 = al_load_bitmap("imagenes/instrucciones.png");

	// SONIDOS
	ALLEGRO_SAMPLE* sound;
	al_reserve_samples(1);
	sound = al_load_sample("sonido/musica.wav");

	// COSAS DE LA VENTANA Y DE EVENTOS
	al_set_window_title(ventana, "CYBERCOOK");
	al_set_window_position(ventana, anchoW / 2 - ancho/2, altoW / 2 - alto/2);

	al_register_event_source(queue, al_get_timer_event_source(fpsTimer));
	al_register_event_source(queue, al_get_timer_event_source(segundoTimer));
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_keyboard_event_source());
	
	// INICIALIZACIION DE LOS TIMER
	al_start_timer(segundoTimer);
	al_start_timer(fpsTimer);
	
	int segundo = 0, fps = 0;
	int x = -1, y = -1;
	
	// posicion 0 = imagenes del menu, posicion 1 = animacion chef mamon, posicion 2 = salir, posicion 3 = bloques de instrucciones blabla
	int botones[] = { 0 , 0 , 0 , 0 };

	while(!botones[2])
	{
		if (!botones[3])
		{
			al_play_sample(sound, 1.0, 0.5, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
			ALLEGRO_EVENT evento;
			al_wait_for_event(queue, &evento);

			eleccion_De_imagen(menu, botones, 0);

			eleccionScaledimagenes(chef, botones, 350, 636, 120, 359, 170, 320, 1);


			if (evento.type == ALLEGRO_EVENT_MOUSE_AXES || evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				x = evento.mouse.x;
				y = evento.mouse.y;

				// 1 = clic izquierdo, 2 = clic derecho, 4= ruedita
				if (x >= 410 && x <= 812 && y >= 359 && y <= 432)
				{
					botones[0] = 1;
					if (evento.mouse.button & 1)
					{
						//FundidoANegro(menu.img0);
						al_destroy_display(ventana);
						juegar();
						botones[0] = 0;

					}
				}
				else
				{
					if (x >= 409 && x <= 810 && y >= 453 && y <= 523)
					{
						botones[0] = 2;

					}
					else
					{
						if (x >= 409 && x <= 810 && y >= 548 && y <= 618)
						{
							botones[0] = 3;
						}
						else
						{
							if (x >= 409 && x <= 810 && y >= 639 && y <= 709)
							{
								botones[0] = 4;
								if (evento.mouse.button & 1)
								{
									botones[2] = 1;
									al_destroy_display(ventana);
								}
							}
							else
							{
								botones[0] = 0;
							}
						}
					}

				}
			}


			if (evento.type == ALLEGRO_EVENT_TIMER) {
				if (evento.timer.source == segundoTimer)
				{
					segundo++;
				}
				else
				{
					fps++;
					if (fps)
					{
						if (botones[1] >= 4)
						{
							botones[1] = -1;
						}
						botones[1]++;
					}
				}
			}
		}

		//al_draw_text(cookie, al_map_rgb(255, 255, 255), 0, 0, NULL, ("Segundos: " + std::to_string(fps)).c_str());

		if (!botones[2])
		{
			al_flip_display();
		}
		
	}

	//al_destroy_display(ventana);
	al_destroy_timer(segundoTimer);
	al_destroy_timer(fpsTimer);
	al_destroy_event_queue(queue);
	al_destroy_bitmap(menu.img0);
	al_destroy_bitmap(menu.img1);
	al_destroy_bitmap(menu.img2);
	al_destroy_bitmap(menu.img3);
	al_destroy_bitmap(menu.img4);
	al_destroy_bitmap(chef.img0);
	al_destroy_bitmap(chef.img1);
	al_destroy_bitmap(chef.img2);
	al_destroy_bitmap(chef.img3);
	al_destroy_bitmap(chef.img4);
	al_destroy_sample(sound);
	al_uninstall_audio();
	al_uninstall_mouse();
	al_uninstall_keyboard();

	return 0;
}

int comosejuega()
{
	printf("Como se juega :)\n");
	return 1;
}



void FundidoANegro(ALLEGRO_BITMAP* img)
{
	// Muestra la imagen y realiza un fundido a Negro

	int anchoImg = al_get_bitmap_width(img);
	int altoImg = al_get_bitmap_height(img);
	ALLEGRO_BITMAP* imgNegro = al_create_bitmap(anchoImg, altoImg);
	al_set_target_bitmap(imgNegro);
	al_clear_to_color(al_map_rgb_f(0, 0, 0));

	al_set_target_backbuffer(ventana);

	int alfa;
	for (int i = 0; i < 255; i++)
	{
		alfa = 255 - i;
		al_draw_bitmap(img, 0, 0, 0);
		al_draw_tinted_bitmap(imgNegro, al_map_rgba_f(0, 0, 0, alfa), 0, 0, 0);

		al_flip_display();
		al_rest(0.01);
		if (i == 0 || i == 254)
		{
			al_rest(1);
		}
	}
	al_destroy_bitmap(imgNegro);
}

void eleccionScaledimagenes(TsAnimacion chef, int botones[], int tamReX, int tamReY, int tamDesX, int tamDesY, int posX, int posY, int i)
{
	if (botones[i] == 0)
	{
		al_draw_scaled_bitmap(chef.img0, 0, 0, tamReX, tamReY, tamDesX, tamDesY, posX, posY, 0);
	}
	else
	{
		if (botones[i] == 1)
		{
			al_draw_scaled_bitmap(chef.img1, 0, 0, tamReX, tamReY, tamDesX, tamDesY, posX, posY, 0);
		}
		else
		{
			if (botones[i] == 2)
			{
				al_draw_scaled_bitmap(chef.img2, 0, 0, tamReX, tamReY, tamDesX, tamDesY, posX, posY, 0);
			}
			else
			{
				if (botones[i] == 3)
				{
					al_draw_scaled_bitmap(chef.img3, 0, 0, tamReX, tamReY, tamDesX, tamDesY, posX, posY, 0);
				}
				else
				{
					al_draw_scaled_bitmap(chef.img4, 0, 0, tamReX, tamReY, tamDesX, tamDesY, posX, posY, 0);
				}
			}

		}
	}
}


void eleccion_De_imagen(TsAnimacion imagen, int band[], int i)
{
	if (band[i] == 0)
	{
		al_draw_bitmap(imagen.img0, 0, 0, 0);
	}
	else
	{
		if (band[i] == 1)
		{
			al_draw_bitmap(imagen.img1, 0, 0, 0);
		}
		else
		{
			if (band[i] == 2)
			{
				al_draw_bitmap(imagen.img2, 0, 0, 0);
			}
			else
			{
				if (band[i] == 3)
				{
					al_draw_bitmap(imagen.img3, 0, 0, 0);
				}
				else
				{
					al_draw_bitmap(imagen.img4, 0, 0, 0);
				}
			}

		}
	}
}

int instrucciones(ALLEGRO_BITMAP* img, ALLEGRO_EVENT evento)
{
	int x, y;
	unsigned int band = 0;

	while (!band)
	{
		al_draw_bitmap(img, 0, 0, NULL);
		if (evento.type == ALLEGRO_EVENT_MOUSE_AXES || evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			x = evento.mouse.x;
			y = evento.mouse.y;

			// 1 = clic izquierdo, 2 = clic derecho, 4= ruedita
			if (x >= 53 && x <= 312 && y >= 503 && y <= 715)
			{
				if (evento.mouse.button & 1)
				{
					printf("\nvamonos al menu jiji");
					al_destroy_bitmap(img);
					band = 1;
				}
			}
		}
	}

	return band;
}
