#include "pavii_logic.h"

void fnc_InitArrayCard(Poker_Card array_card[MAX_CARD_NUM_LENGTH])
{
	for (int i = 0; i < MAX_CARD_NUM_LENGTH; ++i)
	{
		array_card[i].num_face_id = 0;
		array_card[i].num_face_id = 0;
		array_card[i].num_face_id = 0;
		array_card[i].show_state = hide;
		for (int j = 0; j < MAX_STRING_LENGTH; ++j)
		{
			array_card[i].face[j] = '\0';
		}	
	}
}

void fnc_Shuffle(int wDeck[][13])
{
	int row = 0;    /* row number */
	int column = 0; /*column number */
	int card = 0;   /* card counter */

	/* for each of the 52 cards, choose slot of deck randomly */
	for (card = 1; card <= MAX_CARD_NUM_LENGTH; card++)
	{
		/* choose new random location until unoccupied slot found */
		do
		{
			row = rand() % 4;
			column = rand() % 13;
		} while (wDeck[row][column] != 0);

		/* place card number in chosen slot of deck */
		wDeck[row][column] = card;
	}
}

void fnc_ApplyDeckToDealer(const int wDeck[][13], Poker_Card array_card[52])
{
	int row = 0;    /* row number */
	int column = 0; /*column number */
	int card = 0;   /* card counter */
	int count_card = 0;

	/* initialize suit array */
	const char* suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };

	/* initialize face array */
	const char* face[13] = { "Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
		"Nine", "Ten", "Jack", "Queen", "King" };


	/* deal each of the 52 cards */
	for (card = 1; card <= MAX_CARD_NUM_LENGTH; card++)
	{
		/* loop through rows of wDeck */
		for (row = 0; row <= 3; row++)
		{
			/* loop through columns of wDeck for current row */
			for (column = 0; column <= 12; column++)
			{
				/* if slot contains current card, display card */
				if (wDeck[row][column] == card)
				{
					printf("%5s of %-8s%c", face[column], suit[row], card % 2 == 0 ? '\n' : '\t');
					array_card[count_card].num_id = card;
					array_card[count_card].num_face_id = column;
					array_card[count_card].num_suit_id = row;
					strcpy(array_card[count_card].face, face[column]);
					strcpy(array_card[count_card].suit, suit[row]);
					count_card++;
				}
			}
		}
	}
}

int fnc_GetHowManyCardWillGetFromArray(Poker_User user)
{
	int num_rtn_cards = 0;
	for (int i = 0; i < MAX_CARD_NUM_HOLD; ++i)
	{
		if (user.card_hold[i].num_id == 0 || user.card_hold[i].show_state == drop)
		{
			num_rtn_cards++;
		}
	}
	return num_rtn_cards;
}

int fnc_GetCardsFromArray(int num_already_used_cards, int num_get_cards_from_array, Poker_User* user, Poker_Card array_card[MAX_CARD_NUM_LENGTH])
{
	const int num_sum = num_already_used_cards + num_get_cards_from_array;
	
	if (num_sum > 52)
	{
		return -1;
	}
	
	for (int i = num_already_used_cards; i < num_sum; ++i)
	{
		for (int j = 0; j < MAX_CARD_NUM_HOLD; ++j)
		{
			if (user->card_hold[j].num_id == 0 || user->card_hold[j].show_state == drop)
			{
				user->card_hold[j].num_id = array_card[i].num_id;
				user->card_hold[j].num_face_id = array_card[i].num_face_id;
				user->card_hold[j].num_suit_id = array_card[i].num_suit_id;
				strcpy(user->card_hold[j].face, array_card[i].face);
				strcpy(user->card_hold[j].suit, array_card[i].suit);
				user->card_hold[j].show_state = hide;
				break;
			}
		}
	}
	return num_sum;
}

int fnc_CompareIncrease(const void* a, const void* b)
{
	const int* p = a;
	const int* q = b;
	return *p - *q;
}

void fnc_GetHighScore(Poker_User* user)
{
	//create 3 index array
	int array_suit[4] = { 0 };
	int array_num[13] = { 0 };
	int array_increase[5] = { 0 };

	//define each score
	int score_a_pair = 1000;
	int score_two_pairs = 1000;
	int score_three_of_a_kind = 1000;
	int score_a_flush = 1000;
	int score_four_of_a_kind = 1000;
	int score_a_straight = 1000;

	//pair counts
	int counts_pair = 0;

	//fill index array
	for (int i = 0; i < MAX_CARD_NUM_HOLD; ++i)
	{
		//fill suit array
		switch (user->card_hold[i].num_suit_id)
		{
			case FACE_HEARTS:
				array_suit[FACE_HEARTS] = array_suit[FACE_HEARTS] + 1;
				break;
			case FACE_DIAMONDS:
				array_suit[FACE_DIAMONDS] = array_suit[FACE_DIAMONDS] + 1;
				break;
			case FACE_CLUBS:
				array_suit[FACE_CLUBS] = array_suit[FACE_CLUBS] + 1;
				break;
			case FACE_SPADES:
				array_suit[FACE_SPADES] = array_suit[FACE_SPADES] + 1;
				break;
			default:;
		}

		//fill face array
		switch (user->card_hold[i].num_face_id)
		{
			case 0:
				array_num[0] = array_num[0] + 1;
				break;
			case 1:
				array_num[1] = array_num[1] + 1;
				break;
			case 2:
				array_num[2] = array_num[2] + 1;
				break;
			case 3:
				array_num[3] = array_num[4] + 1;
				break;
			case 4:
				array_num[4] = array_num[4] + 1;
				break;
			case 5:
				array_num[5] = array_num[5] + 1;
				break;
			case 6:
				array_num[6] = array_num[6] + 1;
				break;
			case 7:
				array_num[7] = array_num[7] + 1;
				break;
			case 8:
				array_num[8] = array_num[8] + 1;
				break;
			case 9:
				array_num[9] = array_num[9] + 1;
				break;
			case 10:
				array_num[10] = array_num[10] + 1;
				break;
			case 11:
				array_num[11] = array_num[11] + 1;
				break;
			case 12:
				array_num[12] = array_num[12] + 1;
				break;
				
			default:;
		}

		//fill the increase array
		array_increase[i] = user->card_hold[i].num_face_id;
	}

	//sort increase array
	qsort(array_increase, 5, sizeof(array_increase[0]), fnc_CompareIncrease);

	//check cards kind
	//score_three_of_a_kind = fnc_CheckCardsKind(array_increase, 3);
	//score_four_of_a_kind = fnc_CheckCardsKind(array_increase, 4);

	//check a pair
	for (int i = 0; i < 13; ++i)
	{
		if (array_num[i] == 2)
		{
			score_a_pair = SCORE_A_PAIR + i;
			break;
		}
	}

	//check two pairs
	for (int i = 0; i < 13; ++i)
	{
		
		if (array_num[i] == 2)
		{
			counts_pair++;
			if (counts_pair == 2)
			{
				break;
			}
			score_two_pairs = SCORE_TWO_PAIRS + i;
		}
	}

	//check three of a kind
	for (int i = 0; i < 13; ++i)
	{
		if (array_num[i] == 3)
		{
			score_three_of_a_kind = SCORE_THREE_OF_A_KIND + i;
			break;
		}
	}

	//check four of a kind
	for (int i = 0; i < 13; ++i)
	{
		if (array_num[i] == 4)
		{
			score_four_of_a_kind = SCORE_A_FOUR_OF_A_KIND + i;
			break;
		}
	}

	//check straight
	if (fnc_CheckCardsKind(array_increase, 5) != -1)
	{
		score_a_straight = SCORE_A_STRAIGHT + fnc_CheckCardsKind(array_increase, 5);
	}
	
	//check flush
	for (int i = 0; i < 4; ++i)
	{
		if (array_suit[i] == 5)
		{
			score_a_flush = SCORE_A_FLUSH + i;
			break;
		}
	}

	//final score
	user->num_max_score = score_a_pair;
	if (user->num_max_score > score_two_pairs)
	{
		user->num_max_score = score_two_pairs;
	}
	if (user->num_max_score > score_three_of_a_kind)
	{
		user->num_max_score = score_three_of_a_kind;
	}
	if (user->num_max_score > score_four_of_a_kind)
	{
		user->num_max_score = score_four_of_a_kind;
	}
	if (user->num_max_score > score_a_straight)
	{
		user->num_max_score = score_a_straight;
	}
	if (user->num_max_score > score_a_flush)
	{
		user->num_max_score = score_a_flush;
	}
	
	user->num_max_score = 1000 - user->num_max_score;

	
	printf_s("calc done\n");
}

int fnc_CheckCardsKind(const int array_increase[5], int size)
{
	int base = 0, base_1 = 0, base_2 = 0;
	
	int count = 1;
	//base = array_increase[0];
	for (int i = 0; i < MAX_CARD_NUM_HOLD; ++i)
	{
		base = array_increase[i];
		base_1 = base;
		for (int j = i + 1; j < MAX_CARD_NUM_HOLD; ++j)
		{
			base_2 = array_increase[j];
			if (base_2 - base_1 == 1)
			{
				count++;
				base_1 = base_2;
			}
			if (count == size)
			{
				return base;
			}
		}
		count = 1;
	}
	return -1;
}

void fnc_PokerLogicTest()
{
	/* initialize deck array */
	int deck[4][13] = { 0 };
	int num_already_used_cards = 0;

	int num_get_cards_from_array_player = 0;
	int num_get_cards_from_array_ai = 0;

	Poker_Card array_card[MAX_CARD_NUM_LENGTH];

	srand((unsigned)time(NULL)); /* seed random-number generator */

	//init environment
	fnc_Shuffle(deck);
	fnc_InitArrayCard(array_card);
	fnc_ApplyDeckToDealer(deck, array_card);

	//init user
	Poker_User user_player = { 0, 0, player , {0} };
	Poker_User user_ai = { 0, 0, ai , {0} };

	//get numbers from array
	num_get_cards_from_array_player = fnc_GetHowManyCardWillGetFromArray(user_player);
	num_get_cards_from_array_ai = fnc_GetHowManyCardWillGetFromArray(user_ai);

	num_already_used_cards = fnc_GetCardsFromArray(num_already_used_cards, num_get_cards_from_array_player, &user_player, array_card);
	num_already_used_cards = fnc_GetCardsFromArray(num_already_used_cards, num_get_cards_from_array_ai, &user_ai, array_card);


	//calc score
	fnc_GetHighScore(&user_player);
	fnc_GetHighScore(&user_ai);
}
