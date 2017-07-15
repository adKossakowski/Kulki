#include "FlashCard.h"
#include "Ball.h"

using namespace std;

void welcoming() {
	cout << "+============================================================+\n";
	cout << "| Welcome in Kulki game                                      |" << endl;
	cout << "| Author:  Adam Kossakowski                                  |" << endl;
	cout << "| Version:  1.0    Date:  22.06.20                           |" << endl;
	cout << "+============================================================+" << endl;
	Sleep(8000);
	system("cls");
}

int menu()
{
	setlocale(LC_ALL, "");
	int tmp_choice;
	system("cls");
	while (true) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 121);
		cout << "=========================================================" << endl;
		cout << "Menu                                                     " << endl;
		cout << "+---+---------------------------------------------------+" << endl;
		cout << "| 1 |  Gra z komputerem                                 |" << endl;
		cout << "+---+---------------------------------------------------+" << endl;
		cout << "| 2 |  Ranking                                          |" << endl;
		cout << "+---+---------------------------------------------------+" << endl;
		cout << "| 3 |  Rozpoczêcie ostatniej gry                        |" << endl;
		cout << "+---+---------------------------------------------------+" << endl;
		cout << "| 4 |  Zakoñczenie gry                                  |" << endl;
		cout << "+---+---------------------------------------------------+" << endl << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		cout << "========================================================" << endl;
		cout << "Wybór:\t";
		while (true) {
			cin >> tmp_choice;
			bool czyDobra = cin.good();
			if (czyDobra)
				break;
			else {
				cout << "Niepoprawna dana proszê wybraæ jeszcze raz:\t";
				std::cin.clear();
				std::cin.ignore(1000, '\n');
			}
		}
		if (tmp_choice == 1 || tmp_choice == 2 || tmp_choice == 3 || tmp_choice == 4)
			break;
		else
		{
			cout << "=========================================================" << endl;
			cout << "Niepoprawny znak\nProszê wprowadziæ jeszcze raz";
			Sleep(1000);
			system("cls");
		}
	}
	system("cls");
	return tmp_choice;
}

bool file_exists(const char *cSpecyf_Zbioru)
{
	struct stat buf;
	if (stat(cSpecyf_Zbioru, &buf) == 0)
		return true;
	else return false;
}

int FlashCard::moveBall() {

	char str_tmp[10];
	char m_charF, m_charI;
	char m_intF, m_intI;
	bool textCheck = true, positionCheck = true;

	do {
		if (textCheck == true)
			cout << "Proszê wybraæ któr¹ kulkê do przeniesienia:\t";
		else cout << "Niepoprawnie wprowadzone wpó³rzêdne proszê podaæ jeszcze raz:\t";

		scanf("%s", str_tmp);

		if (str_tmp[0] == 'q' || str_tmp[0] == 'Q') {//wyjscie z gry
			return 1;
		}

		if (isalpha(str_tmp[0]) && isdigit(str_tmp[1])) {
			m_charF = tolower(str_tmp[0]);
			m_intF = str_tmp[1];
			textCheck = true;
		}
		else if (isalpha(str_tmp[1]) && isdigit(str_tmp[0])) {
			m_charF = tolower(str_tmp[1]);
			m_intF = str_tmp[0];
			textCheck = true;
		}
		else textCheck = false;

		if (m_charF > 'i' || m_intF == '0') textCheck = false;
	} while (textCheck == false);

	do {
		if (textCheck == true)
			cout << "Proszê miejsce docelowe kullki:\t";
		else cout << "Niepoprawnie wprowadzone wpó³rzêdne proszê podaæ jeszcze raz:\t";

		scanf("%s", str_tmp);
		if (isalpha(str_tmp[0]) && isdigit(str_tmp[1])) {
			m_charI = tolower(str_tmp[0]);
			m_intI = str_tmp[1];
			textCheck = true;
		}
		else if (isalpha(str_tmp[1]) && isdigit(str_tmp[0])) {
			m_charI = tolower(str_tmp[1]);
			m_intI = str_tmp[0];
			textCheck = true;
		}
		else textCheck = false;

		if (m_charI > 'i' || m_intI == '0') textCheck = false;
	} while (textCheck == false);

	int intoHor = m_charI - 97;
	int fromHor = m_charF - 97;
	int intoVer = m_intI - 49;
	int fromVer = m_intF - 49;

	if (!(fc_board[fromHor][fromVer] != ' ')) {//sprawdza czy wybrano jak¹œ kulkê
		cout << "Nie wybrano ¿adnej kulki, prosze wybraæ jeszcze raz\n";
		Sleep(5000);
		return -1;
	}

	//sprawdzanie czy nie ma po drodze rzadnych innych znaków
	bool translation = true;
	do {
		if (translation == false) {
			cout << "Nie mozna przesun¹æ kulki, proszê wybraæ jeszcze raz\n";
			Sleep(5000);
			return -1;
		}
		if (intoHor == fromHor) {
			translation = checkHor(fromVer, intoVer, intoHor);
		}
		else if (intoVer == fromVer) {
			translation = checkVer(fromHor, intoHor, intoVer);
		}
		else {
			int t1 = abs(fromVer - intoVer);
			int t2 = abs(fromHor - intoHor);
			if (t1 == t2)//sprawdzenie czy mozna przesunaæ na ukos
				translation = checkAcross(fromVer, intoVer, fromHor, intoHor);
			else translation = false;
		}
	} while (!translation);
	this->fc_board[intoHor][intoVer] = this->fc_board[fromHor][fromVer];
	Ball::defaultInsert(this->fc_board[fromHor][fromVer]);
	this->meet(intoHor, intoVer);
	system("cls");
	return 0;
}

void FlashCard::end_of_game() {
	FILE *s_stream, *r_stream;
	if (file_exists("rank.txt")) {
		vector<int> t_pkt;
		vector<string> name;
		int l;
		char n[30];
		string sn;
		if ((r_stream = fopen("rank.txt", "r")) == NULL) {
			this->errors();
		}
		else {
			do {
				fscanf(r_stream, "%s %d\n", n, &l);
				sn = n;
				t_pkt.push_back(l);
				name.push_back(sn);
			} while (!feof(r_stream));
			fclose(r_stream);
		}

		if ((s_stream = fopen("rank.txt", "w")) == NULL) {
			this->errors();
		}
		else {
			bool insert = false;
			for (int i = 0; i < t_pkt.size(); i++)
			{
				if (t_pkt[i] <= this->points && insert == false) {
					fprintf(s_stream, "%s %d\n", this->player_name, this->points);
					fprintf(s_stream, "%s %d\n", name[i].c_str(), t_pkt[i]);
					insert = true;
				}
				else
					fprintf(s_stream, "%s %d\n", name[i].c_str(), t_pkt[i]);
				cout << "\nZapisywanie\n";
				system("cls");
			}
			if (insert == false)
				fprintf(s_stream, "%s %d\n", this->player_name, this->points);

			fclose(s_stream);
		}
			/*fprintf(s_stream, "%s %d\n", this->player_name, this->points);
			fclose(s_stream);*/
		
	}
	else {
		if ((s_stream = fopen("rank.txt", "w")) != NULL) {
			fprintf(s_stream, "%s %d\n", this->player_name, this->points);
			fclose(s_stream);
		}
		else this->errors();
	}
}

int main() {
	srand(time(NULL));
	//welcoming();
	int m_choice;
	//tworzenie kulek
	Ball *ballType[9];
	ballType[0] = new Ball('@');
	ballType[1] = new Ball('$');
	ballType[2] = new Ball('&');
	ballType[3] = new Ball('#');
	ballType[4] = new Ball('@');
	ballType[5] = new Ball('!');
	ballType[6] = new Ball('?');
	ballType[7] = new Ball('^');
	ballType[8] = new Ball('+');

	do {
		m_choice = menu();
		//cout << "Hello\n\n";
		if (m_choice == 2) {
			FILE *f_stream;
			int t_points;
			char t_name[30];
			cout << "\t\tRank\n";
			cout << "+------------------------------+--------+\n";
			cout << "|Palyer Name                   | Points |\n";
			cout << "+------------------------------+--------+\n";
			if (file_exists("rank.txt") && ((f_stream = fopen("rank.txt", "r")) != NULL)) {
				do {
					fscanf(f_stream, "%s %d\n", t_name, &t_points);
					printf("|%-30s|%8d|\n", t_name, t_points);
					cout << "+------------------------------+--------+\n";
				} while (!feof(f_stream));
				fclose(f_stream);
			}

			cout << "\nNaciœnij Q aby wyjœæ\n";
			char z;
			while (true)
			{
				z = getchar();
				if (z == 'q' || z == 'Q')
					break;
			}
			system("cls");
		}

		if (m_choice == 1 || m_choice == 3) {

			bool game = true;
			FlashCard *fc;

			if (m_choice == 1) {
				fc = new FlashCard();
				game = fc->drawing(ballType);
			}
			else {
				FILE *f_stream;
				if (file_exists("fc_saving.txt") && ((f_stream = fopen("fc_saving.txt", "r")) != NULL)) {
					fc = new FlashCard(f_stream);
					fclose(f_stream);
				}
			}

			while (game) {
				if(game == true)
					game = fc->display_board();
				game = fc->drawing(ballType);
			}

		}
		
	} while (m_choice != 4);
	return 0;
}