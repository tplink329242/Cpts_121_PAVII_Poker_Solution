#include "CppUnitTest.h"
#include "../Cpts_121_PAVII_Poker_Solution/pavii_logic.h"
#include <limits.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PAVIIUnitTest
{
	TEST_CLASS(PAVIIUnitTest)
	{

		
	public:
		Poker_Card array_card[MAX_CARD_NUM_LENGTH];
		//init user
		Poker_User user_player = { 0, 0, player , {0} };
		Poker_User user_ai = { 0, 0, ai , {0} };

		/* initialize deck array */
		int deck[4][13] = { 0 };
		int num_already_used_cards = 0;

		int num_get_cards_from_array_player = 0;
		int num_get_cards_from_array_ai = 0;
		
		
		TEST_METHOD(TestMethod1)
		{
			fnc_InitArrayCard(array_card);
			Assert::IsNotNull(array_card);
		}

		TEST_METHOD(Test_GetCorrectCardNUM)
		{
			//init environment
			fnc_Shuffle(deck);
			fnc_InitArrayCard(array_card);
			fnc_ApplyDeckToDealer(deck, array_card);
			
			num_get_cards_from_array_player = fnc_GetHowManyCardWillGetFromArray(user_player);
			num_get_cards_from_array_ai = fnc_GetHowManyCardWillGetFromArray(user_ai);

			num_already_used_cards = fnc_GetCardsFromArray(num_already_used_cards, num_get_cards_from_array_player, &user_player, array_card);
			num_already_used_cards = fnc_GetCardsFromArray(num_already_used_cards, num_get_cards_from_array_ai, &user_ai, array_card);

			Assert::AreEqual(10, num_already_used_cards);
		}

		TEST_METHOD(Test_GetCardsInfo)
		{
			
		}

		TEST_METHOD(Test_fnc_CheckCardsKind)
		{
			//base case
			int array_num[5] = {0,1,2,3,4};
			Assert::AreEqual(0, fnc_CheckCardsKind(array_num, 3));
			Assert::AreEqual(0, fnc_CheckCardsKind(array_num, 4));

			array_num[0] = 1;
			Assert::AreEqual(1, fnc_CheckCardsKind(array_num, 3));
			Assert::AreEqual(1, fnc_CheckCardsKind(array_num, 4));

			array_num[0] = 4;
			array_num[1] = 5;
			array_num[2] = 6;
			array_num[3] = 6;
			array_num[4] = 8;
			Assert::AreEqual(4, fnc_CheckCardsKind(array_num, 3));
			Assert::AreEqual(-1, fnc_CheckCardsKind(array_num, 4));


			array_num[0] = 4;
			array_num[1] = 5;
			array_num[2] = 6;
			array_num[3] = 6;
			array_num[4] = 7;
			Assert::AreEqual(4, fnc_CheckCardsKind(array_num, 3));
			Assert::AreEqual(4, fnc_CheckCardsKind(array_num, 4));

			array_num[0] = 4;
			array_num[1] = 5;
			array_num[2] = 6;
			array_num[3] = 7;
			array_num[4] = 8;
			Assert::AreEqual(4, fnc_CheckCardsKind(array_num, 5));
			
		}
		
	};
}
