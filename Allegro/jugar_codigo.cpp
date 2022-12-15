#include "libreriaperrona_librerias.h"

void salir(ALLEGRO_TIMER* timer, ALLEGRO_BITMAP* img, ALLEGRO_EVENT evento, ALLEGRO_DISPLAY* ventana, int botones[], int i);
void eleccionScaledimagenes1(TsAnimacion chef, int botones[], int tamReX, int tamReY, int tamDesX, int tamDesY, int posX, int posY, int i);

int juegar()
{
	printf("Jugar");
	int ancho = 896;
	int alto = 768;

	ALLEGRO_DISPLAY* ventana2;
	ALLEGRO_FONT* cookie;
	ALLEGRO_FONT* reloj;
	ALLEGRO_TIMER* segundoTimer;
	ALLEGRO_TIMER* fpsTimer;
	ALLEGRO_TIMER* temptemp;
	ALLEGRO_EVENT_QUEUE* queue;

	if (!al_init())
	{
		al_show_native_message_box(NULL, "ERROR CRITICO", "ERROR 404", "Hubo un error", NULL, ALLEGRO_MESSAGEBOX_QUESTION);
	}


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
	ventana2 = al_create_display(ancho, alto);
	cookie = al_load_font("fuentes/Symtext.ttf", 100, 0);
	reloj = al_load_font("fuentes/reloj.ttf",70,0);

	// DEFINICION DE LOS TIMERS DE FPS Y DE SEGUNDOS
	segundoTimer = al_create_timer(1.0);
	fpsTimer = al_create_timer(1.0 / 10);
	temptemp = al_create_timer(1.0);

	queue = al_create_event_queue();

	// COLORES RESERVADOS
	ALLEGRO_COLOR blanco = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR  azar = al_map_rgb(34, 23, 67);


	// IMAGENES DEL MENU
	TsAnimacion juego;
	juego.img0 = al_load_bitmap("imagenes/fondos/jugar_main.png");
	juego.img1 = al_load_bitmap("imagenes/fondos/jugar_dificultad.png");
	juego.img2 = al_load_bitmap("imagenes/fondos/jugar_ganaste.png");
	juego.img3 = al_load_bitmap("imagenes/fondos/jugar_perdiste.png");

	// IMAGENES DEL CHEF RATITA ANIMACION
	TsAnimacion chefratita;
	chefratita.img0 = al_load_bitmap("imagenes/chefsito/chefsitofrent1.png");
	chefratita.img1 = al_load_bitmap("imagenes/chefsito/chefsitofrent2.png");
	chefratita.img2 = al_load_bitmap("imagenes/chefsito/chefsitofrent3.png");
	
	// BOTON START
	ALLEGRO_BITMAP* start = al_load_bitmap("imagenes/comenzar.png");
	
	// IMAGENES DEL CHEF MARIO ANIMACION
	TsAnimacion chefMario;
	chefMario.img0 = al_load_bitmap("imagenes/chefm/chefm0.png");
	chefMario.img1 = al_load_bitmap("imagenes/chefm/chefm1.png");
	chefMario.img2 = al_load_bitmap("imagenes/chefm/chefm2.png");
	chefMario.img3 = al_load_bitmap("imagenes/chefm/chefm3.png");
	chefMario.img4 = al_load_bitmap("imagenes/chefm/chefmf.png");
	chefMario.img5 = al_load_bitmap("imagenes/chefm/chefmn.png");

	// IMAGENES COMIDA
	TsAnimacion comida;
	comida.img0 = al_load_bitmap("imagenes/comida/leche.png");
	comida.img1 = al_load_bitmap("imagenes/comida/webos.png");
	comida.img2 = al_load_bitmap("imagenes/comida/harina.png");
	comida.img3 = al_load_bitmap("imagenes/comida/fresa.png");
	comida.img4 = al_load_bitmap("imagenes/comida/pastel.png");

	// SONIDOS
	ALLEGRO_SAMPLE* sound;
	al_reserve_samples(1);
	sound = al_load_sample("sonido/musica.wav");

	// COSAS DE LA VENTANA Y DE EVENTOS
	al_set_window_title(ventana2, "CYBERCOOK - JUGAR");
	al_set_window_position(ventana2, anchoW / 2 - ancho / 2, altoW / 2 - alto / 2);

	al_register_event_source(queue, al_get_timer_event_source(fpsTimer));
	al_register_event_source(queue, al_get_timer_event_source(segundoTimer));
	al_register_event_source(queue, al_get_timer_event_source(temptemp));
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_keyboard_event_source());

	// INICIALIZACIION DE LOS TIMER
	al_start_timer(segundoTimer);
	al_start_timer(fpsTimer);

	int segundo = 0, fps = 0, temp = 0;
	int x = -1, y = -1;
	int k, h;
	char cadena[50];

	// posicion 0 = Chef Mario, posicion 1 = Chef Ratita, posicion 2 = timer, posicion 3 = teclado, posicion 4 = fondos, posicion 5 = dificultades, posicion 6 = abrir/cerrar ventana
	int botones[] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 };

	ALLEGRO_EVENT evento;



	while (!botones[6])
	{
		//al_draw_text(cookie, al_map_rgb(255, 255, 255), 0, 0, NULL, "djsakdnsjk pipipi");
		al_wait_for_event(queue, &evento);
		if (!botones[4])
		{
			al_draw_bitmap(juego.img1, 0, 0, NULL);

			if (evento.type == ALLEGRO_EVENT_MOUSE_AXES || evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				k = evento.mouse.x;
				h = evento.mouse.y;

				// 1 = clic izquierdo, 2 = clic derecho, 4= ruedita
				if (k >= 39 && k <= 294 && h >= 387 && h <= 512)
				{
					if (evento.mouse.button & 1)
					{
						botones[5] = 0;
						botones[4]++;
					}
				}
				else
				{
					if (k >= 318 && k <= 578 && h >= 387 && h <= 512)
					{
						if (evento.mouse.button & 1)
						{
							botones[5] = 1;
							botones[4]++;
						}
					}
					else
					{
						if (k >= 604 && k <= 861 && h >= 387 && h <= 512)
						{
							botones[0] = 3;
							if (evento.mouse.button & 1)
							{
								botones[5] = 2;
								botones[4]++;
							}
						}
					}

				}
			}
		}
		else
		{
			al_draw_bitmap(juego.img0, 0, 0, 0);

			eleccionScaledimagenes1(chefMario, botones, 65, 77, 465, 225, 264, 236, 0);
			eleccionScaledimagenes1(chefratita, botones, 34, 69, 250, 495, 105, 200, 1);

			if (botones[3])
			{
				al_draw_text(reloj, al_map_rgb(0, 0, 0), 410, 58, NULL, cadena);
			}

			if (botones[3] == 5)
			{
				printf("\nTerminaste de imprimir Leche.");
				al_draw_scaled_bitmap(comida.img0, 0, 0, 27, 27, 345, 559, 60, 60, NULL);
			}

			if (botones[3] == 10)
			{
				printf("\nTerminaste de imprimir huevo.");
				al_draw_scaled_bitmap(comida.img1, 0, 0, 27, 27, 345, 559, 60, 60, NULL);
			}

			if (botones[3] == 16)
			{
				printf("\nTerminaste de imprimir harina.");
				al_draw_scaled_bitmap(comida.img2, 0, 0, 27, 27, 345, 559, 60, 60, NULL);
			}

			if (botones[3] == 21)
			{
				printf("\nTerminaste de imprimir fresa.");
				al_draw_scaled_bitmap(comida.img3, 0, 0, 27, 27, 345, 559, 60, 60, NULL);

			}

			if (botones[3] == 27)
			{
				printf("\nTerminaste de imprimir pastel.");
				al_draw_text(reloj, al_map_rgb(0, 0, 0), 410, 58, NULL, cadena);
				al_draw_scaled_bitmap(comida.img0, 0, 0, 27, 27, 345, 559, 60, 60, NULL);
				al_stop_timer(temptemp);
				al_rest(1);
				botones[3]++;
			}


			if (botones[2] == 0)
			{
				al_draw_bitmap(start, 10, 20, NULL);
			}
			else
			{
				al_draw_tinted_bitmap(start, al_map_rgb(255, 0, 0), 10, 20, NULL);
				if (botones[3] < 5)
				{
					al_draw_scaled_bitmap(comida.img0, 0, 0, 27, 27, 678, 303, 90, 90, NULL);
				}
				else
				{
					if (botones[3] < 10)
					{
						al_draw_scaled_bitmap(comida.img1, 0, 0, 27, 27, 678, 303, 90, 90, NULL);
					}
					else
					{
						if (botones[3] < 16)
						{
							al_draw_scaled_bitmap(comida.img2, 0, 0, 27, 27, 678, 303, 90, 90, NULL);
						}
						else
						{
							if (botones[3] < 21)
							{
								al_draw_scaled_bitmap(comida.img3, 0, 0, 27, 27, 678, 303, 90, 90, NULL);
							}
							else
							{
								if (botones[3] < 27)
								{
									al_draw_scaled_bitmap(comida.img4, 0, 0, 27, 27, 678, 303, 90, 90, NULL);
								}
							}
						}
					}
				}

				//al_draw_filled_rectangle(392, 40, 833, 121, al_map_rgb(255, 255, 255));

				if (evento.type == ALLEGRO_EVENT_KEY_DOWN)
				{
					switch (evento.keyboard.keycode)
					{
					case ALLEGRO_KEY_L:
					{
						if (botones[3] == 0 || botones[3] == 26)
						{
							if (botones[3] == 0)
							{
								strcpy_s(cadena, "L");
								botones[3] = 1;
							}
							else
							{
								botones[3] = 27;
								strcat_s(cadena, "L");
							}
						}
						break;
					}

					case ALLEGRO_KEY_E:
					{
						if (botones[3] == 1 || botones[3] == 4 || botones[3] == 7 || botones[3] == 18 || botones[3] == 25)
						{
							strcat_s(cadena, "E");
							botones[3]++;
						}
						break;
					}

					case ALLEGRO_KEY_C:
					{
						if (botones[3] == 2)
						{
							strcat_s(cadena, "C");
							botones[3] = 3;
						}
						break;
					}

					case ALLEGRO_KEY_H:
					{
						if (botones[3] == 5)
						{
							botones[3] = 6;
							strcpy_s(cadena, "H");
						}
						if (botones[3] == 3)
						{
							strcat_s(cadena, "H");
							botones[3] = 4;
						}
						if (botones[3] == 10)
						{
							strcpy_s(cadena, "H");
							botones[3] = 11;
						}
						break;
					}

					case ALLEGRO_KEY_U:
					{
						if (botones[3] == 6)
						{
							botones[3]++;
							strcat_s(cadena, "U");
						}

						break;
					}

					case ALLEGRO_KEY_V:
					{
						if (botones[3] == 8)
						{
							botones[3]++;
							strcat_s(cadena, "V");
						}

						break;
					}

					case ALLEGRO_KEY_O:
					{
						if (botones[3] == 9)
						{
							botones[3]++;
							strcat_s(cadena, "O");
						}
						break;
					}

					case ALLEGRO_KEY_A:
					{
						if (botones[3] == 11)
						{
							botones[3] = 12;
							strcat_s(cadena, "A");
						}
						if (botones[3] == 15)
						{
							strcat_s(cadena, "A");
							botones[3] = 16;
						}
						if (botones[3] == 20)
						{
							strcat_s(cadena, "A");
							botones[3] = 21;
						}
						if (botones[3] == 22)
						{
							strcat_s(cadena, "A");
							botones[3] = 23;
						}
						break;
					}

					case ALLEGRO_KEY_R:
					{
						if (botones[3] == 12 || botones[3] == 17)
						{
							strcat_s(cadena, "R");
							botones[3]++;
						}
						break;
					}

					case ALLEGRO_KEY_I:
					{
						if (botones[3] == 13)
						{
							botones[3]++;
							strcat_s(cadena, "I");
						}

						break;
					}

					case ALLEGRO_KEY_N:
					{
						if (botones[3] == 14)
						{
							botones[3]++;
							strcat_s(cadena, "N");
						}
						break;
					}

					case ALLEGRO_KEY_F:
					{
						if (botones[3] == 16)
						{
							botones[3]++;
							strcpy_s(cadena, "F");
						}
						break;
					}

					case ALLEGRO_KEY_S:
					{
						if (botones[3] == 19 || botones[3] == 23)
						{
							strcat_s(cadena, "S");
							botones[3]++;
						}
						break;
					}

					case ALLEGRO_KEY_P:
					{
						if (botones[3] == 21)
						{
							botones[3]++;
							strcpy_s(cadena, "P");
						}
						break;
					}

					case ALLEGRO_KEY_T:
					{
						if (botones[3] == 24)
						{
							botones[3]++;
							strcat_s(cadena, "T");
						}
						break;
					}
					}
				}

			}

			if (evento.type == ALLEGRO_EVENT_MOUSE_AXES || evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				x = evento.mouse.x;
				y = evento.mouse.y;

				// 1 = clic izquierdo, 2 = clic derecho, 4= ruedita
				if (x >= 13 && x <= 176 && y >= 19 && y <= 82)
				{
					if (evento.mouse.button & 1)
					{
						if (botones[2] == 0)
						{
							al_start_timer(temptemp);
							printf("\ntemptemp");
							botones[2] = 1;
						}

					}
				}
			}

			al_draw_text(reloj, al_map_rgb(0, 0, 0), 206, 0, NULL, (std::to_string(temp)).c_str());


			if (evento.type == ALLEGRO_EVENT_TIMER) {
				if (evento.timer.source == temptemp)
				{
					temp++;
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
						if (botones[0] >= 3)
						{
							botones[0] = -1;
						}
						botones[0]++;

						if (botones[1] >= 2)
						{
							botones[1] = -1;
						}
						botones[1]++;
					}
				}
			}

			if (botones[3] == 28)
			{
				salir(temptemp, juego.img2, evento, ventana2, botones, 6);
				al_draw_text(reloj, al_map_rgb(0, 0, 0), 234, 350, NULL, (std::to_string(temp)).c_str());
			}

			if (botones[5] == 0)
			{
				if (temp == 20)
				{
					salir(temptemp, juego.img3, evento, ventana2, botones, 6);
				}
			}
			else
			{
				if (botones[5] == 1)
				{
					if (temp == 15)
					{
						salir(temptemp, juego.img3, evento, ventana2, botones, 6);
					}
				}
				else
				{
					if (temp == 10)
					{
						salir(temptemp, juego.img3, evento, ventana2, botones, 6);
					}
				}
			}
		}
			
		al_flip_display();
	}
	

	return 0;
}


void eleccionScaledimagenes1(TsAnimacion chef, int botones[], int tamReX, int tamReY, int tamDesX, int tamDesY, int posX, int posY, int i)
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

void salir(ALLEGRO_TIMER* timer, ALLEGRO_BITMAP* img, ALLEGRO_EVENT evento, ALLEGRO_DISPLAY* ventana, int botones[],int i)
{
	int x, y;
	al_stop_timer(timer);
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
				al_destroy_display(ventana);
				menu();
				botones[i] = 1;

			}
		}
	}
}
