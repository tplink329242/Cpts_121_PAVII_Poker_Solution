#include "pavii_logic.h"

//sdl include	
#include "include\SDL_mutex.h"
#include "include/SDL.h"
#include "include/SDL_timer.h"
#include "include/SDL_image.h"
#include "include/SDL_ttf.h"
#include "include/SDL_thread.h"


typedef enum
{
	Phase_Init,
	Phase_In_Menu,
	Phase_FirstRound,
	Phase_SecondRound
	
}Poker_Phase; 

//init sdl window
SDL_Window* fnc_sdl_create_window();

//create render
SDL_Renderer* fnc_sdl_create_render(SDL_Window* win, Uint32 sdl_current_render_flags);

//create texture from picture
SDL_Texture* fnc_sdl_create_pic_texture(SDL_Renderer* battleship_main_window_renderer, const char* location_pic);

//create text texture
SDL_Texture* fnc_sdl_create_text_texture(SDL_Renderer* battleship_main_window_renderer, TTF_Font* font, SDL_Color textColor, char msg_user[100]);

//create text texture,  return rect and tex
void fnc_sdl_create_text_texture_and_location(SDL_Renderer* battleship_main_window_renderer, TTF_Font* font, SDL_Color textColor, SDL_Rect* text_rect, SDL_Texture** text_tex, char msg_user[100]);

//init sdl environment
int fnc_sdl_init(void);

//mouse click checker
bool fnc_check_mouse_click_event_checker(SDL_Rect rect_Play_button);

//main window
int fnc_sdl_render_main(void* poker_shared_data);

//init array poker face
int fnc_init_array_poker_face(SDL_Renderer* poker_renderer, SDL_Texture* array_poker_tex[4][13]);
