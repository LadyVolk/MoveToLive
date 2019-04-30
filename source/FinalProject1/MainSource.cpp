#include <iostream>
#include <time.h>
#include <string>
#include <stdlib.h>
#include "pch.h"
using namespace std;


int throw_bull(int p) {

	//  Throw for the bull with accuracy p%  (20<p<85)

	int r = rand() % 100;

	if (r < (p - 20))
		return 50;
	else if (r < 85)
		return 25;
	else
		return 1 + rand() % 20;
}


int throw_treble(int d, int p) {

	//  return result of throwing for treble d with accuracy p%  (o<90)

	// Board neighbours ignoring slot zero
	int bd[2][21] = { {0,20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5},
			   {0,18,17,19,13,20,10,16,11,12,15,14,5,6,9,2,8,3,4,7,1} };

	int r = rand() % 100;

	if (r < p)
		return 3 * d;
	else if (r < 90)
		return d;
	else if (r < 93)
		return 3 * bd[0][d];
	else if (r < 96)
		return 3 * bd[1][d];
	else if (r < 98)
		return bd[0][d];
	else
		return bd[1][d];
}


int throw_double(int d) {

	//  return result of throwing for double d with accuracy 80%

	// Board neighbours ignoring slot zero
	int bd[2][21] = { {0,20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5},
			   {0,18,17,19,13,20,10,16,11,12,15,14,5,6,9,2,8,3,4,7,1} };
	int r = rand() % 100;

	if (r < 80)
		return 2 * d;
	else if (r < 85)
		return 0;
	else if (r < 90)
		return d;
	else if (r < 93)
		return 2 * bd[0][d];
	else if (r < 96)
		return 2 * bd[1][d];
	else if (r < 98)
		return bd[0][d];
	else
		return bd[1][d];
}



int throw_single(int d) {

	//  return result of throwing for single d with accuracy 88% (or 80% for the outer)

	// Board neighbours ignoring slot zero
	int bd[2][21] = { {0,20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5},
			   {0,18,17,19,13,20,10,16,11,12,15,14,5,6,9,2,8,3,4,7,1} };
	int r = rand() % 100;

	if (d == 25) {		// outer  80%
		if (r < 80)
			return 25;
		else if (r < 90)
			return 50;
		else
			return 1 + rand() % 20;
	}
	else			// 1 to 20 single
		if (r < 88)
			return d;
		else if (r < 92)
			return bd[0][d];
		else if (r < 96)
			return bd[1][d];
		else if (r < 98)
			return 3 * d;
		else
			return 2 * d;
}




int main() {

	int players[2], current_player, current_darts, target, save, winner = -1, starting_player,
		game_score[2], set_score[2], i, j, number_tests = 100; //0 is sid, 1 is joe
	int stats[2][7];

	srand(time(NULL));

	for (i = 0; i < 2; i++) {
		for (j = 0; j < 7; j++) {
			stats[i][j] = 0;
		}
	}

	//several competitions to generate graph
	for (i = 0; i < number_tests; i++) {

		cout << "calculating test... " << i << endl;

		set_score[0] = 0;
		set_score[1] = 0;

		//start competition
		while (set_score[0] < 7 && set_score[1] < 7) {

			starting_player = 0;

			game_score[0] = 0;
			game_score[1] = 0;

			//start of set
			while (game_score[0] != 3 && game_score[1] != 3) {

				players[0] = 501; // reseting sids score
				players[1] = 501; // reseting joes score

				current_player = starting_player;

				winner = -1;

				//starts a game
				while (winner == -1) {
					current_darts = 3;
					save = players[current_player];
					//turn
					while (current_darts > 0) {
						if (players[current_player] >= 62) {
							players[current_player] -= throw_treble(20, 40);
						}
						else if (players[current_player] > 50) {
							target = players[current_player] - 50;
							players[current_player] -= throw_single(target);
						}
						else if (players[current_player] == 50) {
							players[current_player] -= throw_bull(60);
							if (players[current_player] == 0) {
								winner = current_player;
								break;
							}
						}
						else if (players[current_player] > 40) {
							target = players[current_player] - 40;
							players[current_player] -= throw_single(target);
						}
						else if (players[current_player] % 2 == 0 && players[current_player] != 0) {
							target = players[current_player] / 2;
							players[current_player] -= throw_double(target);
							if (players[current_player] == 0) {
								winner = current_player;
								break;
							}
						}
						else if (players[current_player] % 2 == 1 && players[current_player] != 1) {
							players[current_player] -= throw_single(1);
						}
						// if got here, score is <= 1
						else {
							players[current_player] = save;
							current_darts = 0;
						}
						current_darts--;
					}
					// invert player after end of turn
					current_player = 1 - current_player;
				}
				game_score[winner]++;

				//change first player
				starting_player = 1 - current_player;
			}
			if (game_score[0] > game_score[1]) {
				set_score[0]++;
			}
			else {
				set_score[1]++;
			}
		}
		
		//adding score to stats matrix
		if (set_score[0] > set_score[1]) {
			stats[0][set_score[1]]++;
		}
		else {
			stats[1][set_score[0]]++;
		}
	}
	cout << "result based on " << number_tests << " tests" << endl;
	cout << "sid/joe frequency" << endl;
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 7; j++) {
			if (i==0) {
				cout << "  7/" << j << "   " << ((double)stats[i][j]/number_tests)*100 << "%" << endl;
			}
			else {
				cout << "  " << j << "/7" << "   " << ((double)stats[i][j]/number_tests)*100 << "%" << endl;
			}
		}
	}
	return 0;
}
