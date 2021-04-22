#include "pavii_render.h"

SDL_Window* fnc_sdl_create_window()
{
	SDL_Window* win = SDL_CreateWindow("Cpts 121 PAVII 'Poker (5-Card Draw)'",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT, 0);
	if (!win)
	{
		printf_s("Error creating SDL window: %s ", SDL_GetError());
		return NULL;
	}
	return win;
}

SDL_Renderer* fnc_sdl_create_render(SDL_Window* win, Uint32 sdl_current_render_flags)
{
	SDL_Renderer* render = SDL_CreateRenderer(win, -1, sdl_current_render_flags);
	if (!render)
	{
		printf_s("Error creating SDL render: %s ", SDL_GetError());
		return NULL;
	}
	return render;
}

SDL_Texture* fnc_sdl_create_pic_texture(SDL_Renderer* battleship_main_window_renderer, const char* location_pic)
{
	SDL_Surface* surface = IMG_Load(location_pic);
	if (surface == NULL)
	{
		printf_s("Error creating SDL surface: %s ", SDL_GetError());
	}
	SDL_Texture* tex = SDL_CreateTextureFromSurface(battleship_main_window_renderer, surface);

	//free surface
	SDL_FreeSurface(surface);

	if (!tex)
	{
		printf_s("Error creating SDL texture: %s ", SDL_GetError());
	}
	return tex;
}

SDL_Texture* fnc_sdl_create_text_texture(SDL_Renderer* battleship_main_window_renderer, TTF_Font* font, SDL_Color textColor, char msg_user[100])
{
	SDL_Surface* msg_input = TTF_RenderUTF8_Solid(font, msg_user, textColor);
	SDL_Texture* battleship_fonts = SDL_CreateTextureFromSurface(battleship_main_window_renderer, msg_input);
	SDL_FreeSurface(msg_input);
	return battleship_fonts;
}

void fnc_sdl_create_text_texture_and_location(SDL_Renderer* battleship_main_window_renderer, TTF_Font* font, SDL_Color textColor, SDL_Rect* text_rect, SDL_Texture** text_tex, char msg_user[100])
{
	*text_tex = fnc_sdl_create_text_texture(battleship_main_window_renderer, font, textColor, msg_user);
	SDL_QueryTexture(*text_tex, NULL, NULL, &text_rect->w, &text_rect->h);
}

int fnc_sdl_init(void)
{
	int res = 0;
	res = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_EVENTS);
	if (res != 0)
	{
		printf_s("Error for init SDL: %s ", SDL_GetError());
		return 1;
	}
	if (TTF_Init() == -1)
	{
		return 1;
	}
	printf_s("init success!\n");
	return 0;
}

bool fnc_check_mouse_click_event_checker(SDL_Rect rect_Play_button)
{
	int mouse_state_x;
	int mouse_state_y;
	SDL_GetMouseState(&mouse_state_x, &mouse_state_y);

	if ((mouse_state_x > rect_Play_button.x) && (mouse_state_x < (rect_Play_button.x + rect_Play_button.w)))
	{
		if ((mouse_state_y > rect_Play_button.y) && (mouse_state_y < (rect_Play_button.y + rect_Play_button.h)))
		{
			return true;
		}
	}
	return false;
}

int fnc_sdl_render_main(void* poker_shared_data)
{
	//seeds
	srand((unsigned)time(NULL));

	//init render environment
	fnc_sdl_init();
	bool close_request = false;


	//player basic info
	/* initialize deck array */
	int deck[4][13] = { 0 };
	int num_already_used_cards = 0;

	int num_get_cards_from_array_player = 0;
	int num_get_cards_from_array_ai = 0;

	Poker_Card array_card[MAX_CARD_NUM_LENGTH];

	//init user
	Poker_User user_player = { 0, 0, player , {0} };
	Poker_User user_ai = { 0, 0, ai , {0} };


	//sdl event
	SDL_Event poker_event;

	//game phase
	Poker_Phase game_phase = Phase_Init;
	
	//define a winner
	Poker_PlayerType winner = init;
	
	//sdl const var
	const Uint32 poker_sdl_render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	const char* pic_background = "res/pic/main_menu.jpg";

	//init main window
	SDL_Window* poker_main_window = fnc_sdl_create_window();
	SDL_Renderer* poker_renderer = fnc_sdl_create_render(poker_main_window, poker_sdl_render_flags);
	SDL_Texture* tex_menu_background = fnc_sdl_create_pic_texture(poker_renderer, pic_background);

	//init font and size
	TTF_Font* font = TTF_OpenFont("res/data/calibri.ttf", 25);
	TTF_Font* font_medium = TTF_OpenFont("res/data/calibri.ttf", 50);
	TTF_Font* font_big = TTF_OpenFont("res/data/calibri.ttf", 80);
	const SDL_Color textColor_blue = { 0, 0, 255 };
	const SDL_Color textColor_Fuchsia = { 255, 0, 255 };


	//main menu text var
	//welcome text generator
	SDL_Rect rect_menu_main_text = { 200,100, 0, 0 };
	SDL_Texture* tex_menu_main_text = NULL;
	fnc_sdl_create_text_texture_and_location(poker_renderer, font_big, textColor_blue, &rect_menu_main_text, &tex_menu_main_text, "Welcome To Poker!");

	//play button generator
	SDL_Rect rect_menu_play_button = { 700,400, 0, 0 };
	SDL_Texture* tex_menu_play_button = NULL;
	fnc_sdl_create_text_texture_and_location(poker_renderer, font_big, textColor_Fuchsia, &rect_menu_play_button, &tex_menu_play_button, "Play!");

	//rule button generator
	SDL_Rect rect_menu_rule_button = { 700,500, 0, 0 };
	SDL_Texture* tex_menu_rule_button = NULL;
	fnc_sdl_create_text_texture_and_location(poker_renderer, font_big, textColor_Fuchsia, &rect_menu_rule_button, &tex_menu_rule_button, "Rule");

	//rule pic generator
	SDL_Rect rect_menu_rule_pic = { 0,400, 700, 200 };
	SDL_Texture* tex_menu_rule_pic = fnc_sdl_create_pic_texture(poker_renderer, "res/pic/rules.PNG");
	
	//bool show rules picture
	bool is_show_rules_picture = false;


	//first round tex
	bool is_already_pickup_cards = false;

	//poker tex and back face tex
	SDL_Texture* array_poker_tex[4][13];

	fnc_init_array_poker_face(poker_renderer, array_poker_tex);
	SDL_Texture* array_poker_hide_tex = fnc_sdl_create_pic_texture(poker_renderer, "res/pic/poker_back.PNG");

	//10 card locations
	SDL_Rect rect_cards_player[5];
	SDL_Rect rect_cards_ai[5];
	
	
	
	//winner text and location
	SDL_Rect rect_winner_player_round_title = { 90,80, 0, 0 };
	SDL_Rect rect_winner_ai_round_title = { 90,80, 0, 0 };
	SDL_Texture* tex_winner_player_round_title = NULL;
	SDL_Texture* tex_winner_ai_round_title = NULL;

	fnc_sdl_create_text_texture_and_location(poker_renderer, font_medium, textColor_blue, &rect_winner_player_round_title, &tex_winner_player_round_title, "The winner is player!");
	fnc_sdl_create_text_texture_and_location(poker_renderer, font_medium, textColor_blue, &rect_winner_ai_round_title, &tex_winner_ai_round_title, "The winner is AI!");


	//start game
	game_phase = Phase_In_Menu;
	

	while (!close_request)
	{
		// clear the window
		SDL_RenderClear(poker_renderer);

		//copy the main background
		SDL_RenderCopy(poker_renderer, tex_menu_background, NULL, NULL);

		//reset sdl event states;
		poker_event.type = SDL_FIRSTEVENT;
		
		//quit identify
		while (SDL_PollEvent(&poker_event))
		{
			if (poker_event.type == SDL_QUIT)
			{
				//close flag
				close_request = true;
			}
		}

		//start switch phase for logic
		switch (game_phase)
		{
		case Phase_In_Menu:
			break;
		case Phase_FirstRound:
			if (is_already_pickup_cards == false)
			{
				//init environment
				fnc_Shuffle(deck);
				fnc_InitArrayCard(array_card);
				fnc_ApplyDeckToDealer(deck, array_card);

				//get numbers from array
				num_get_cards_from_array_player = fnc_GetHowManyCardWillGetFromArray(user_player);
				num_get_cards_from_array_ai = fnc_GetHowManyCardWillGetFromArray(user_ai);

				num_already_used_cards = fnc_GetCardsFromArray(num_already_used_cards, num_get_cards_from_array_player, &user_player, array_card);
				num_already_used_cards = fnc_GetCardsFromArray(num_already_used_cards, num_get_cards_from_array_ai, &user_ai, array_card);


				is_already_pickup_cards = true;
			}
			break;
		case Phase_SecondRound:
			break;

		default:;
		}

		
		//start switch phase for render
		switch (game_phase)
		{
			case Phase_In_Menu:
				SDL_RenderCopy(poker_renderer, tex_menu_main_text, NULL, &rect_menu_main_text);
				SDL_RenderCopy(poker_renderer, tex_menu_play_button, NULL, &rect_menu_play_button);
				SDL_RenderCopy(poker_renderer, tex_menu_rule_button, NULL, &rect_menu_rule_button);
				if (is_show_rules_picture == true)
				{
					SDL_RenderCopy(poker_renderer, tex_menu_rule_pic, NULL, &rect_menu_rule_pic);

					//test card pic load
					//SDL_RenderCopy(poker_renderer, array_poker_tex[0][0], NULL, &rect_menu_rule_pic);
				}
				break;
			case Phase_FirstRound:
				break;
			case Phase_SecondRound:
				break;
				
			default:;
		}

		//start switch phase for inactive
		switch (game_phase)
		{
		case Phase_In_Menu:
			if (poker_event.type == SDL_MOUSEBUTTONUP)
			{
				if (fnc_check_mouse_click_event_checker(rect_menu_play_button))
				{
					game_phase = Phase_FirstRound;
				}
				if (fnc_check_mouse_click_event_checker(rect_menu_rule_button))
				{
					if (is_show_rules_picture == false)
					{
						is_show_rules_picture = true;
					}
					else is_show_rules_picture = false;
				}
			}

			break;
		case Phase_FirstRound:
			break;
		case Phase_SecondRound:
			break;

		default:;
		}



		
		//show the render
		SDL_RenderPresent(poker_renderer);

		// wait 1/60th of a second
		SDL_Delay(1000 / 60);
	}
	
	return 0;
}

int fnc_init_array_poker_face(SDL_Renderer* poker_renderer, SDL_Texture* array_poker_tex[4][13])
{
	char string_location[20] = "res/pic/1-1.gif";
	//char string_location[20] = "poker_back.PNG";
	SDL_Texture* test_tex = NULL;
	
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 13; ++j)
		{
			string_location[8] = (char)(i + 49);
			string_location[10] = (char)(j + 49);
			if (j > 8)
			{
				string_location[10] = (char)(j + 88);
			}
			array_poker_tex[i][j] = fnc_sdl_create_pic_texture(poker_renderer, string_location);
			//test_tex = fnc_sdl_create_pic_texture(poker_renderer, string_location);
		}
	}
	return 0;
}
