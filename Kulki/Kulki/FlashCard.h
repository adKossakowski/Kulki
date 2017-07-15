#ifndef FlashCard_hpp
#define FlashCard_hpp

#include "Ball.h"
#include<iostream>
#include<stdio.h>
#include<string>
#include<vector>
#include<string.h>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<fstream>
#include<Windows.h>

#define SIZE 9

using namespace std;

class FlashCard {

private:

	Ball fc_board[SIZE][SIZE];
	int ball_quantity;
	int points;
	int ballsOnFC;
	char player_name[30];

	bool checkVer(int start, int stop, int column) {
		if (start < stop) {
			for (int i = start + 1; i <= stop; i++) {
				if (fc_board[i][column] != ' ') {
					return false;
				}
			}
			return true;
		}
		else {
			for (int i = start - 1; i >= stop; i--) {
				if (fc_board[i][column] != ' ') {
					return false;
				}
			}
			return true;
		}
	}

	bool checkHor(int start, int stop, int row) {
		if (start < stop) {
			for (int i = start + 1; i <= stop; i++) {
				if (fc_board[row][i] != ' ') {
					return false;
				}
			}
			return true;
		}
		else {
			for (int i = start - 1; i >= stop; i--) {
				if (fc_board[row][i] != ' ') {
					return false;
				}
			}
			return true;
		}
	}

	bool checkAcross(int startFV, int stopIV, int startFH, int stopIH) {
		if (startFH < stopIH) {//w dó³
			if (startFV < stopIV) {//w prawo i w dó³
				for (int i = startFH + 1, j = startFV + 1; i <= stopIH; i++, j++) {
					if (fc_board[i][j] != ' ') {
						return false;
					}
				}
				return true;
			}
			else {//w dó³ i w lewo
				for (int i = startFH + 1, j = startFV - 1; i <= stopIH; i++, j--) {
					if (fc_board[i][j] != ' ') {
						return false;
					}
				}
				return true;
			}
		}
		else {//w górê
			if (startFV < stopIV) {
				for (int i = startFH - 1, j = startFV + 1; i >= stopIH; i--, j++) {
					if (fc_board[i][j] != ' ') {
						return false;
					}
				}
				return true;
			}
			else {
				for (int i = startFH - 1, j = startFV - 1; i >= stopIH; i--, j--) {
					if (fc_board[i][j] != ' ') {
						return false;
					}
				}
				return true;
			}
		}
	}

	int moveBall();

	int ballHorLeft(int t_hor, int t_ver) {
		if ((t_ver - 1) >= 0 && t_ver <= 9 && fc_board[t_hor][t_ver - 1] == fc_board[t_hor][t_ver]) {
			return 1 + this->ballHorLeft(t_hor, t_ver - 1);
		}
		else {
			return 0;
		}
	}

	int ballHorRight(int t_hor, int t_ver) {
		if (t_ver >= 0 && (t_ver + 1) <= 9 && fc_board[t_hor][t_ver + 1] == fc_board[t_hor][t_ver]) {
			return 1 + this->ballHorRight(t_hor, t_ver + 1);
		}
		else {
			return 0;
		}
	}

	int ballVerUp(int t_hor, int t_ver) {
		if ((t_hor - 1) >= 0 && t_hor <= 9 && fc_board[t_hor - 1][t_ver] == fc_board[t_hor][t_ver]) {
			return 1 + this->ballVerUp(t_hor - 1, t_ver);
		}
		else {
			return 0;
		}
	}

	int ballVerDown(int t_hor, int t_ver) {
		if (t_hor >= 0 && (t_hor + 1) <= 9 && fc_board[t_hor + 1][t_ver] == fc_board[t_hor][t_ver]) {
			return 1 + this->ballVerDown(t_hor + 1, t_ver);
		}
		else {
			return 0;
		}
	}

	int ballAcrossUpLeft(int t_hor, int t_ver) {
		if ((t_ver - 1) >= 0 && t_ver <= 9 && (t_hor - 1) >= 0 && t_hor <= 9 && fc_board[t_hor - 1][t_ver - 1] == fc_board[t_hor][t_ver]) {
			return 1 + this->ballAcrossUpLeft(t_hor - 1, t_ver - 1);
		}
		else {
			return 0;
		}
	}

	int ballAcrossUpRight(int t_hor, int t_ver) {
		if (t_ver >= 0 && (t_ver + 1) <= 9 && (t_hor - 1) >= 0 && t_hor <= 9 && fc_board[t_hor - 1][t_ver + 1] == fc_board[t_hor][t_ver]) {
			return 1 + this->ballAcrossUpRight(t_hor - 1, t_ver + 1);
		}
		else {
			return 0;
		}
	}

	int ballAcrossDownLeft(int t_hor, int t_ver) {
		if ((t_ver - 1) >= 0 && t_ver <= 9 && t_hor >= 0 && (t_hor + 1) <= 9 && fc_board[t_hor + 1][t_ver - 1] == fc_board[t_hor][t_ver]) {
			return 1 + this->ballAcrossDownLeft(t_hor + 1, t_ver - 1);
		}
		else {
			return 0;
		}
	}

	int ballAcrossDownRight(int t_hor, int t_ver) {
		if (t_ver >= 0 && (t_ver + 1) <= 9 && t_hor >= 0 && (t_hor + 1) <= 9 && fc_board[t_hor + 1][t_ver + 1] == fc_board[t_hor][t_ver]) {
			return 1 + this->ballAcrossDownRight(t_hor + 1, t_ver + 1);
		}
		else {
			return 0;
		}
	}

	int removeHor(int t_hor, int t_ver) {
		if ((this->ballHorLeft(t_hor, t_ver/* - 1*/) + this->ballHorRight(t_hor, t_ver/* + 1*/)) >= 2) {
			int i, j;
			i = j = t_ver;
			while (fc_board[t_hor][i - 1] == fc_board[t_hor][t_ver]) {
				fc_board[t_hor][--i] = ' ';
				this->points++;
				this->ballsOnFC--;
			}
			while (fc_board[t_hor][j + 1] == fc_board[t_hor][t_ver]) {
				fc_board[t_hor][++j] = ' ';
				this->points++;
				this->ballsOnFC--;
			}
			return 1;
		}
		else return 0;
	}

	int removeVer(int t_hor, int t_ver) {
		if ((this->ballVerUp(t_hor/* - 1*/, t_ver) + this->ballVerDown(t_hor/* + 1*/, t_ver)) >= 2) {
			int i, j;
			i = j = t_hor;
			while (fc_board[i - 1][t_ver] == fc_board[t_hor][t_ver]) {
				fc_board[--i][t_ver] = ' ';
				this->points++;
				this->ballsOnFC--;
			}
			while (fc_board[j + 1][t_ver] == fc_board[t_hor][t_ver]) {
				fc_board[++j][t_ver] = ' ';
				this->points++;
				this->ballsOnFC--;
			}
			return 1;
		}
		else return 0;
	}

	int removeAcrossLeft(int t_hor, int t_ver) {
		if ((this->ballAcrossUpLeft(t_hor/* - 1*/, t_ver/* - 1*/) + this->ballAcrossDownRight(t_hor/* + 1*/, t_ver/* + 1*/)) >= 2) {
			int i, j, k, l;
			i = j = t_ver;
			k = l = t_hor;
			while (fc_board[k - 1][i - 1] == fc_board[t_hor][t_ver]) {
				fc_board[--k][--i] = ' ';
				this->points++;
				this->ballsOnFC--;
			}
			while (fc_board[l + 1][j + 1] == fc_board[t_hor][t_ver]) {
				fc_board[++l][++j] = ' ';
				this->points++;
				this->ballsOnFC--;
			}
			return 1;
		}
		else return 0;
	}

	int removeAcrossRight(int t_hor, int t_ver) {
		if ((this->ballAcrossUpRight(t_hor/* - 1*/, t_ver/* + 1*/) + this->ballAcrossDownLeft(t_hor/* + 1*/, t_ver/* - 1*/)) >= 2) {
			int i, j, k, l;
			i = j = t_ver;
			k = l = t_hor;
			while (fc_board[k - 1][i + 1] == fc_board[t_hor][t_ver]) {
				fc_board[--k][++i] = ' ';
				this->points++;
				this->ballsOnFC--;
			}
			while (fc_board[l + 1][j - 1] == fc_board[t_hor][t_ver]) {
				fc_board[++l][--j] = ' ';
				this->points++;
				this->ballsOnFC--;
			}
			return 1;
		}
		else return 0;
	}

	void meet(const int t_hor, const int t_ver) {
		if ((removeHor(t_hor, t_ver) + removeVer(t_hor, t_ver) + removeAcrossLeft(t_hor, t_ver) + removeAcrossRight(t_hor, t_ver)) > 0) {
			fc_board[t_hor][t_ver] = ' ';
			this->points++;
			this->ballsOnFC--;
		}
	}

	void errors() {
		cout << "\nUps...";
		Sleep(4000);
		system("cls");
		cout << "Nie uda³o siê otworzyæ pliku do zapisu";
		Sleep(4000);
		system("cls");
	}

	void end_of_game();//{
	//	FILE *s_stream;
	//	if (file_exists("rank.txt")) {
	//		if (((s_stream = fopen("rank.txt", "w")) == NULL) && ((r_stream = fopen("rank.txt", "r")) == NULL)) {
	//			this->errors();
	//		}
	//		else {
	//			vector<int> t_pkt;
	//			vector<string> name;
	//			int l;
	//			char n[30];
	//			string sn;
	//			do {
	//				fscanf(r_stream, "%s" "%d\n", n, &l);
	//				sn = n;
	//				t_pkt.push_back(l);
	//				name.push_back(sn);
	//			} while (!feof(r_stream));
	//			fclose(r_stream);

	//			bool insert = false;
	//			for (int i = 0; i < t_pkt.size(); i++)
	//			{
	//				if (t_pkt[i] <= punkty && insert == false) {
	//					fprintf(plik, "%s %d\n", this->player_name, this->points);
	//					fprintf(plik, "%s %d\n", name[i].c_str(), t_pkt[i]);
	//					insert = true;
	//				}
	//				else
	//					printf(plik, "%s %d\n", name[i].c_str(), t_pkt[i]);
	//				cout << "\nZapisywanie\n";
	//				system("cls");
	//			}
	//			if (insert == false)
	//				fprintf(plik, "%s %d\n", this->player_name, this->points);

	//			fclose(s_stream);

	//			/*fprintf(s_stream, "%s %d\n", this->player_name, this->points);
	//			fclose(s_stream);*/
	//		}
	//	}
	//	else {
	//		if (s_stream = fopen("rank.txt", "w") != NULL) {
	//			fprintf(s_stream, "%s %d\n", this->player_name, this->points);
	//			fclose(s_stream);
	//		} else this->errors();

	//	}
	//}

protected:

public:

	FlashCard():points(0), ballsOnFC(0), ball_quantity(9) {
		cout << "Proszê podaæ nazwê gracza:\t";
		cin >> this->player_name;
		for (int i = 0, k = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				fc_board[i][j].defaultBall(fc_board[i][j], i, j);
			}
		}
	}

	FlashCard(FILE *s_stream):ball_quantity(9),ballsOnFC(0) {
		char t_pattern;
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				fscanf(s_stream, "%c ", &t_pattern);
				if (t_pattern != 'c') {
					this->fc_board[i][j].newBall(t_pattern, i, j);
					this->ballsOnFC++;
				}
				else
					this->fc_board[i][j].defaultBall(fc_board[i][j], i, j);
			}
			//t_pattern = fgetc(s_stream);
		}
		fscanf(s_stream, "%d\n", &this->points);
		fscanf(s_stream, "%s\n", this->player_name);
		fclose(s_stream);
	}
	
	bool display_board() {

		char d_char = 'A';
		cout << "\nYour nickname:\t" << this->player_name << endl << endl;
		cout << "\t   1   2   3   4   5   6   7   8   9\n";
		for (int i = 0, l = 0; i < 2 * SIZE; i++) {
			if (i % 2 == 0) {
				cout << "  \t+---+---+---+---+---+---+---+---+---+" << endl;
			}
			else {
				printf("%c\t", d_char);
				for (int j = 0; j < SIZE; j++) {
					printf("| %c ", fc_board[l][j].ballPattern);
				}
				printf("|\n");
				l++;
				d_char++;
			}
		}
		cout << "  \t+---+---+---+---+---+---+---+---+---+" << endl;
		cout << "\n\nAby wyjœæ z gry wciœnij q\n";
		cout << "\nPunkty:\t" << this->points << endl << endl;;
		int translation;
		do {

			translation = this->moveBall();
			if (translation == 1) {

				system("cls");
				//zapisnaie stanu gry przed zamknieciem gry
				FILE *s_stream;
				if ((s_stream = fopen("fc_saving.txt", "w")) == NULL) {
					this->errors();
					return false;
				}
				for (int i = 0; i < SIZE; i++) {
					for (int j = 0; j < SIZE; j++) {
						if(fc_board[i][j].ballPattern != ' ')
							fprintf(s_stream, "%c ", fc_board[i][j].ballPattern);
						else
							fprintf(s_stream, "%c ", 'c');
					}
					fputc('\n', s_stream);
				}
				fprintf(s_stream,"%d\n", this->points);
				fprintf(s_stream, "%s\n", this->player_name);
				fclose(s_stream);
				return false;//wyjscie z gry
			}

		} while (translation == -1);

		return true;
	}

	bool drawing (Ball **tmp_ball) {//losuje 3 nowe kulki

		int *ballTab = new int[3];
		for (int i = 0; i < 3; i++) {
			ballTab[i] = (rand() % ball_quantity) + 0;
		}

		for (int i = 0; i < 3; i++) {
			int ver, hor;
			do {
				hor = rand() % SIZE;//losuje wspolrzedne kulki na planszy
				ver = rand() % SIZE;
				if (fc_board[hor][ver].ballPattern == ' ') {//sprawdzenie czy dane miejsce jest wolne
					fc_board[hor][ver] = tmp_ball[ballTab[i]];//przypasowuje dana kulke do planszy
					if (++this->ballsOnFC >= 81) {
						this->end_of_game();
						return false;//przepelnienie planszy, koniec gry
					}
					break;
				}
			} while (true);
		}
		return true;
		//////
	}

};

#endif