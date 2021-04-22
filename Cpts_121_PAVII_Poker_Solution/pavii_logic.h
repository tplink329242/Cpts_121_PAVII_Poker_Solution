#ifndef PAVII_LOGIC_FUNCTIONS_H
#define PAVII_LOGIC_FUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

	//def base marco
#define _CRT_SECURE_NO_WARNINGS
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define MAX_STRING_LENGTH 10
#define MAX_CARD_NUM_LENGTH 52
#define MAX_CARD_NUM_HOLD 5

	//def face marco
#define FACE_HEARTS 0
#define FACE_DIAMONDS 1
#define FACE_CLUBS 2
#define FACE_SPADES 3

	//def base score
#define SCORE_A_PAIR 600
#define SCORE_TWO_PAIRS 500	
#define SCORE_THREE_OF_A_KIND 400
#define SCORE_A_FLUSH 300
#define SCORE_A_FOUR_OF_A_KIND 200
#define SCORE_A_STRAIGHT 100
	
	//std library	
#include <stdio.h>
#include <math.h>
#include <stdlib.h> 
#include <time.h> 
#include <Windows.h>
#include <stdbool.h>
#include <string.h>

	typedef enum
	{
		init,
		player,
		ai
		
	}Poker_PlayerType;

	typedef enum
	{
		hide,
		show,
		drop
		
	}Poker_CardShowState;
	
	typedef struct
	{
		int num_id;
		int num_suit_id;
		int num_face_id;
		Poker_CardShowState show_state;
		char suit[MAX_STRING_LENGTH];
		char face[MAX_STRING_LENGTH];
		
	}Poker_Card;

	typedef struct
	{
		int num_hold;
		int num_max_score;
		Poker_PlayerType player_type;
		Poker_Card card_hold[MAX_CARD_NUM_HOLD];
		
	}Poker_User;

	//init array card
	void fnc_InitArrayCard(Poker_Card array_card[MAX_CARD_NUM_LENGTH]);
	
	//init deck
	void fnc_Shuffle(int wDeck[][13]);

	//apply deck to dealer
	void fnc_ApplyDeckToDealer(const int wDeck[][13], Poker_Card array_card[52]);

	//get how many cards will get in user's hands
	int fnc_GetHowManyCardWillGetFromArray(Poker_User user);
	
	//get cards from array
	int fnc_GetCardsFromArray(int num_already_used_cards, int num_get_cards_from_array, Poker_User* user , Poker_Card array_card[MAX_CARD_NUM_LENGTH]);

	//compare func
	int fnc_CompareIncrease(const void* a, const void* b);

	//calc the highest score
	void fnc_GetHighScore(Poker_User* user);

	//check kind
	int fnc_CheckCardsKind(int array_increase[5], int size);

	//logic test
	void fnc_PokerLogicTest();
	
	
#ifdef __cplusplus
}
#endif
#endif
