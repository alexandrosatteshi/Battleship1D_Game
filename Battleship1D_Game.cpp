#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;

string board_userview, board_main;
const char icon_user = '$', icon_hit = 'X', icon_miss = 'o', icon_oponent = '^', icon_sea = '_';
bool get_hit, get_left, get_right, turn_finish;

//Default line used in game
void line() {
	cout << "________________________________________________________________________________________________________________________" << endl;
}

//First header (Always displayed on top)
void start_header() {
	line();
	cout << "                                                    Battleship 1D                                   (with A.I.Smart Hit)" << endl;
	line();
}

//Information (Displayed when user enters information)
void stats() {
	cout << "                                                     Information" << endl;
	cout << "~Limits are calculated throught the numbers you enter" << endl;
	cout << "~Number of ships is (How many ships is you and your oponent would have)" << endl;
	cout << "~Ships cannot overlap!" << endl;
	cout << "~\"A.I.Smart Hit\" can make inteligent decisions as to where it should hit" << endl;
	line();
}

//Retern's the posisions of given icon
void check_board(int board_lenght, char icon) {
	for (int r = 0; r < board_lenght; r++) {
		if (board_userview[r] == icon) {
			cout << " " << r + 1;
		}
	}
}

//This function checks if there is enough space(bigger or iqual than ship size) between some limits for a ship to occupie the possision
bool space_check(int rand_possition, int ship_size, int board_lenght) {
	int space_available = 0, x = 0;
	bool way = false;

	if (board_main[rand_possition] == icon_user) {
		return true;
	}


	for (int r = 0; r < ship_size + 1; r++) {
		if (!way) {
			if ((rand_possition + x < board_lenght) && (board_main[rand_possition + x] == icon_sea || board_main[rand_possition + x] == icon_oponent || board_main[rand_possition + x] == icon_user)) {
				space_available++;
				x++;
			}
			else {
				way = true;
				x = -1;
			}
		}
		else {
			if ( (rand_possition + x > 0) && (board_main[rand_possition + x] == icon_sea || board_main[rand_possition + x] == icon_oponent || board_main[rand_possition + x] == icon_user)) {
				space_available++;
				x--;
			}
			else {
				break;
			}
		}
	}

	if (space_available >= ship_size) {
		return true;
	}
	else {
		return false;
	}
}

//Displays all possitions in board and explains them (Used in the game)
void data_header(string username, int board_lenght, int ship_size) {
	cout << endl;
	line();

	cout << "Those are the icons we use in the game:" << endl;
	cout << username << " ship: " << icon_user << "    Torpido Hit: " << icon_hit << "    Torpido Miss: " << icon_miss << "    Sea: " << icon_sea << endl;

	line();

	cout << endl << username << " board:" << endl;
	cout << board_userview << endl;

	cout << "                                                    Coordinates" << endl;
	cout << "Your ships posisions   : ";
	check_board(board_lenght, icon_user);

	cout << endl << "Open sea Possitions    : ";
	check_board(board_lenght, icon_sea);

	cout << endl << "Torpidos Hits Possition: ";
	check_board(board_lenght, icon_hit);

	cout << endl << "Torbito Miss Posision  : ";
	check_board(board_lenght, icon_miss);

	cout << endl;
	line();
}

//Create the board (fills it with sea)
void string_create(int board_lenght, int &max_size){
	for (int c = 0; c < board_lenght; c++) {
		board_main += icon_sea;
	}

	board_userview = board_main;
	max_size = board_lenght / 4;
}

//When the player enters coordinates this function check's what it hit, tells the user and updates the board
void player_hitwhat (int cannon_coordinates, int &counter_user, int &counter_opponent) {
	if (board_main[cannon_coordinates] == icon_hit || board_main[cannon_coordinates] == icon_miss) {
		cout << "You already hit this possition!!" << endl;
	}
	if (board_main[cannon_coordinates] == icon_sea) {
		cout << "You missed!!" << endl;

		system("color 6F");
		board_main[cannon_coordinates] = icon_miss;
		board_userview[cannon_coordinates] = icon_miss;
	}
	if (board_main[cannon_coordinates] == icon_oponent) {
		cout << "You got a hit!!" << endl;

		system("color 2F");
		counter_user++;
		board_main[cannon_coordinates] = icon_hit;
		board_userview[cannon_coordinates] = icon_hit;
	}
	if (board_main[cannon_coordinates] == icon_user) {
		cout << "You hit one of your own ships!!" << endl;

		system("color 4F");
		counter_opponent++;
		board_main[cannon_coordinates] = icon_hit;
		board_userview[cannon_coordinates] = icon_hit;
	}
}

//Check's if the user gave a number that overlaps with another ship (Used before the program creates the ships)
bool ship_overlap(int ship_size, int ship_position, int board_lenght) {
	bool check_if = false;

	--ship_position;

	for (int r = 0; r < ship_size; r++) {
		if ((board_main[ship_position + r] == icon_user) || ((ship_position + ship_size - 1) > board_lenght)) {
			cout << "Ships cannot overlap!" << endl << endl;
			check_if = true;
			break;
		}
		else {
			check_if = false;
		}
	}

	if (check_if) {
		return true;
	}
	else {
		return false;
	}
}

//Displays the possision of the users ship (Used after the player gave a possision for a ship to generate)
void user_boardview(string username, int ship_position, int ship_size) {
	cout << endl << username << " board view:" << endl;
	cout << "Your ship occupied this posisions: ";

	--ship_position; //Need this because string start's from 0

	for (int r = 0; r < ship_size; r++) {
		board_main[ship_position++] = icon_user;
		cout << ship_position << " ";
	}
	board_userview = board_main;

	cout << endl << board_userview << endl << endl;
}

//Generates the computer ships
void ship_generator(int ship_number, int ship_size,  int board_lenght) {
	//flag there was a return 0 were break is now
	int ship_position, counter_max = 0;
	bool check_if;

	for (int c = 1; c <= ship_number; c++) {
		do {
			ship_position = rand() % board_lenght;
			for (int r = 0; r < ship_size; r++) {
				if ((board_main[ship_position + r] == icon_user) || (board_main[ship_position + r] == icon_oponent) || ((ship_position + ship_size) > board_lenght)) {
					check_if = true;
					break;
				}
				else {
					check_if = false;
				}

				if (++counter_max > board_lenght) {
					cout << "Oups.. You left no space for your oponent!" << endl;
					break;
				}
			}
		} while (check_if);

		for (int q = 0; q < ship_size; q++) {
			board_main[ship_position++] = icon_oponent;
		}
	}
}

//A.I.Smart Hit generates a random possision for the computer to hit, returns the random number
int get_hitcoords(int board_lenght, int ship_size, int &counter_opponent) {
	int rand_possition;

	do {
		rand_possition = rand() % board_lenght;

	} while (board_main[rand_possition] == icon_hit || board_main[rand_possition] == icon_miss || board_main[rand_possition] == icon_oponent || !space_check(rand_possition, ship_size, board_lenght));

	if (board_main[rand_possition] == icon_user) {
		board_main[rand_possition] = icon_hit;
		board_userview[rand_possition] = icon_hit;

		cout << "Computer got a hit!!" << endl;

		get_hit = false;
		get_right = true;
		get_left = false;
		turn_finish = true;
		counter_opponent++;
	}
	else {
		board_main[rand_possition] = icon_miss;
		board_userview[rand_possition] = icon_miss;

		cout << "Computer missed!!" << endl;

		get_hit = true;
		get_right = false;
		get_left = false;
		turn_finish = true;
	}

	return rand_possition;
}

//A.I.Smart Hit (Used if get_hitcoords hit a ship to go right)
void go_right(int computer_hitplace, int board_lenght, int &counter_opponent) {
	if (computer_hitplace > board_lenght || board_main[computer_hitplace] == icon_hit || board_main[computer_hitplace] == icon_miss || board_main[computer_hitplace] == icon_oponent) {
		get_hit = false;
		get_right = false;
		get_left = true;

	}
	else if (board_main[computer_hitplace] == icon_sea) {
		board_main[computer_hitplace] = icon_miss;
		board_userview[computer_hitplace] = icon_miss;

		cout << "Computer missed!!" << endl;

		get_hit = false;
		get_right = false;
		get_left = true;
		turn_finish = true;
	}
	else if (board_main[computer_hitplace] == icon_user) {
		board_main[computer_hitplace] = icon_hit;
		board_userview[computer_hitplace] = icon_hit;

		cout << "Computer got a hit!!" << endl;

		get_hit = false;
		get_right = true;
		get_left = false;
		turn_finish = true;
		counter_opponent++;
	}
}

//A.I.Smart Hit (Used after go_right to left)
void go_left(int computer_hitplace, int board_lenght, int &counter_opponent) {
	if (computer_hitplace < 0 || board_main[computer_hitplace] == icon_hit || board_main[computer_hitplace] == icon_miss || board_main[computer_hitplace] == icon_oponent) {
		get_hit = true;
		get_right = false;
		get_left = false;
	}
	else if (board_main[computer_hitplace] == icon_sea) {
		board_main[computer_hitplace] = icon_miss;
		board_userview[computer_hitplace] = icon_miss;

		cout << "Computer missed!!" << endl;

		get_hit = true;
		get_right = false;
		get_left = false;
		turn_finish = true;
	}
	else if (board_main[computer_hitplace] == icon_user) {
		board_main[computer_hitplace] = icon_hit;
		board_userview[computer_hitplace] = icon_hit;

		cout << "Computer got a hit!!" << endl;

		get_hit = false;
		get_right = false;
		get_left = true;
		turn_finish = true;

		counter_opponent++;
	}
}

//A.I.Smart Hit Coordinates get_hitcoords, go_right, go, left)
void smart_hit(int board_lenght, int ship_size, int &counter_opponent, int &computer_hitplace,int &computer_hitplace2) {
	do {
		turn_finish = false;

		if (get_hit && !get_left && !get_right) {
			computer_hitplace = get_hitcoords(board_lenght, ship_size, counter_opponent);
			computer_hitplace2 = computer_hitplace;
		}

		if (!get_hit && !get_left && get_right && !turn_finish) {
			go_right(++computer_hitplace2, board_lenght, counter_opponent);
		}

		if (!get_hit && get_left && !get_right && !turn_finish) {
			go_left(--computer_hitplace, board_lenght, counter_opponent);
		}

	} while (!turn_finish);
}

//Displays the overal result (Won/Lost)
void result(int counter_user, int counter_opponent, int counter_max) {
	system("cls");
	start_header();

	if (counter_user == counter_max) {
		if (counter_opponent == counter_max) {
			cout << endl << "                                         You both sunk all of your ships!!.. Its a draw" << endl;
		}
		else {
			system("color 2F");
			cout << endl << "                                                 You won the game!!" << endl;
		}
	}
	else {
		system("color 4F");
		cout << endl << "                                                      You lost!!" << endl;
	}

	line();
}

//Used in the end of program
void end_header() {
	line();
	cout << "@Programm by Alexandros" << endl;
	line();
}

//Ask's the user if he want's to play again
bool play_again() {
	bool check_if;
	char repeat;

	do {
		cout << "Do you want to play again? Y/N: ";
		cin >> repeat;

		if (repeat != 'y' && repeat != 'Y' && repeat != 'n' && repeat != 'N') {
			cout << "'" << repeat << "' is not recognized as a program command." << endl << endl;
			check_if = true;
		}
		else {
			check_if = false;
		}
	} while (check_if);

	if (repeat == 'y' || repeat == 'Y') {
		return true;
	}
	else {
		return false;
	}
}

//Checks if an input is an intiger and between given limits
bool input_check(int min, int max, int input) {
	if (!cin.good() || (input < min || input > max)) {
		cin.clear();
		cin.ignore();
		cout << "Incorect Value! Give an integer number between " << min << "-" << max << endl << endl;
		return false;
	}
	else {
		return true;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////// MAIN FUNCTION //////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
	string username;
	int board_lenght, ship_size, max_size, ship_number, max_ships, ship_position, cannon_coordinates, computer_hitplace, computer_hitplace2;

	srand(time(0));

	do {
		//First part of programm / Information on game parameters 
		board_userview = {}, board_main = {};
		get_hit = true, get_left = false, get_right = false;
		int counter_user = 0, counter_opponent = 0, counter_max = 0, computer_hitcounter = 0;
		system("cls");
		system("color 07");

		start_header();
		stats();

		cout << "Fisrt lets take your username." << endl;
		cout << "Username: ";
		cin >> username;
		cout << endl << "Good, now " << username << " let's set the parameters." << endl;

		do {
			cout << "Lenght of board(1-119): ";
			cin >> board_lenght;
		} while (!input_check(1, 119, board_lenght));

		string_create(board_lenght, max_size);

		do {
			cout << "Size of ships(1-" << max_size << "): ";
			cin >> ship_size;
		} while (!input_check(1, max_size, ship_size) || (ship_size > board_lenght));

		max_ships = (board_lenght / ship_size) / 2;

		do {
			cout << "Number of ships(1-" << max_ships << "): ";
			cin >> ship_number;
		} while (!input_check(1, max_ships, ship_number));

		cout << endl;

		for (int c = 1; c <= ship_number; c++) {
			do {
				cout << c << " ship position: ";
				cin >> ship_position;
			} while (!input_check(1, board_lenght, ship_position) || ship_overlap(ship_size, ship_position, board_lenght));

			user_boardview(username, ship_position, ship_size);
		}

		ship_generator(ship_number, ship_size, board_lenght);

		cout << "We are ready to play!!" << endl << endl;

		system("pause");
		counter_max = ship_size * ship_number;

		//Second part of programm / The game
		do {
			system("cls");
			system("color 07");
			start_header();
			data_header(username, board_lenght, ship_size);

			do {
				cout << "Cannon coordinates(1-" << board_lenght << "): ";
				cin >> cannon_coordinates;
			} while (!input_check(1, board_lenght, cannon_coordinates));

			--cannon_coordinates;

			cout << endl << "**************************" << endl;

			player_hitwhat(cannon_coordinates, counter_user, counter_opponent);
			smart_hit(board_lenght, ship_size, counter_opponent, computer_hitplace, computer_hitplace2);

			cout << "**************************" << endl;
			cout << username << " board:" << endl;
			cout << board_userview << endl << endl;

			system("pause");
		} while (counter_user < counter_max && counter_opponent < counter_max);

		result(counter_user, counter_opponent, counter_max);
	} while (play_again());

	end_header();

	return 0;
}