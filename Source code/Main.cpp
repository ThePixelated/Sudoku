#include <windows.h>
#include <iostream>
#include <conio.h>
#include <vector>

// Output Message
// --------------
void clearance(int size, int column = 0, int line = 0, bool return_point = true) {
	COORD coor;
	coor.X = column;
	coor.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coor);

	for (int lines = 0; lines < size; lines++) {
		std::cout << "                                                               \n";
		//std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n";
	}

	if (return_point) SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coor);
}

void print_tile(std::vector<std::vector<std::vector<int>>> grid_tile, int cursor_style = 239) {
	int counter = 0;

	std::cout << " =========================\n";
	for (int z = 0; z < 9; z++) {
		std::cout << " | ";

		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				if (grid_tile[y + counter][z % 3][x] == cursor_style) {
					std::cout << char(cursor_style) << " ";
					continue;
				}

				if (grid_tile[y + counter][z % 3][x] == 0) {
					std::cout << "  ";
					continue;
				}

				std::cout << grid_tile[y + counter][z % 3][x] << " ";
			} std::cout << "| ";
		}

		if ((z > 0 && z < 8) && (z + 1) % 3 == 0) {
			counter += 3;
			std::cout << "\n -------------------------";
		} std::cout << "\n";

	} std::cout << " =========================\n";
}

void start_title() {
	int text[5][47] = { {219, 219, 219, 219, 219, 219, 32, 219, 219, 32, 32, 32, 219, 219, 32, 219, 219, 219, 219, 219, 219, 32, 32, 32,
						219, 219, 219, 219, 219, 219, 219, 32, 219, 219, 32, 32, 32, 219, 219, 32, 219, 219, 32, 32, 32, 219, 219},
						{219, 219, 219, 32, 32, 32, 32, 219, 219, 32, 32, 32, 219, 219, 32, 219, 219, 32, 32, 32, 219, 219, 32, 32,
						219, 219, 32, 32, 32, 219, 219, 32, 219, 219, 32, 32, 219, 219, 32, 32, 219, 219, 32, 32, 32, 219, 219},
						{219, 219, 219, 219, 219, 219, 32, 219, 219, 32, 32, 32, 219, 219, 32, 219, 219, 32, 32, 32, 32, 219, 219,
						32, 219, 219, 32, 32, 32, 219, 219, 32, 219, 219, 219, 219, 219, 32, 32, 32, 219, 219, 32, 32, 32, 219, 219},
						{32, 32, 32, 219, 219, 219, 32, 219, 219, 32, 32, 32, 219, 219, 32, 219, 219, 32, 32, 32, 219, 219, 32, 32,
						219, 219, 32, 32, 32, 219, 219, 32, 219, 219, 32, 32, 219, 219, 32, 32, 219, 219, 32, 32, 32, 219, 219},
						{219, 219, 219, 219, 219, 219, 32, 219, 219, 219, 219, 219, 219, 219, 32, 219, 219, 219, 219, 219, 219, 32, 32,
						32, 219, 219, 219, 219, 219, 219, 219, 32, 219, 219, 32, 32, 32, 219, 219, 32, 219, 219, 219, 219, 219, 219, 219}
	};

	std::cout << " +=========================================================+\n";
	std::cout << " |[]                                                     []|\n";

	// Printing out the text
	for (int i = 0; i < 5; i++) {
		std::cout << " |     ";

		for (int letter_text = 0; letter_text < 47; letter_text++) {
			std::cout << char(text[i][letter_text]);
		}

		std::cout << "     |\n";
	}

	std::cout << " |[]                                                     []|\n";
	std::cout << " +=========================================================+\n";
}

void main_menu_sect() {
	std::cout << "\n [1] Play\t [Work in progress]\n [2] Leaderboard [Coming soon..]\n [3] Credit\n [4] Exit\n ";
}

void credit_msg() {
	std::cout << ",----------------------,\n";
	std::cout << "| Name : Opik          |\n";
	std::cout << "\n";
}

bool credit_session() {
	while (true) {
		clearance(30);
		credit_msg();
		std::cout << "\n Press 'Esc' or [B] to go to main menu.. ";

		int credits_input = _getch();
		if (credits_input == 27 || credits_input == 66 || credits_input == 98) return 0;
	}
}

void exit_msg() {
	clearance(30);
	std::cout << "\n thanks for playing.. \n";
}

bool exit_session() {
	while (true) {
		clearance(30);
		std::cout << "  Are you sure you want\n   to leave the game ?\n";
		std::cout << "      Yes     No.\n      [Y]     [N]\n\t   ";

		int exit_input = _getch();

		if (exit_input == 89 || exit_input == 121) return 1;
		else if (exit_input == 78 || exit_input == 110) return 0;
	}

	return 0;
}


std::vector<std::vector<std::vector<int>>> generate_tile() {
	std::vector<std::vector<std::vector<int>>> arr;
	for (int i = 0; i < 9; i++) {
		arr.push_back({ { 0, 1, 0 }, { 1, 0, 1 }, { 0, 1, 0 } });
	} return arr;
}

// Movement
// --------
int cursor_x_pos = 1;	// Center set point - Row
int cursor_y_pos = 1;	// Center set point - Column
int cursor_z_pos = 4;	// Center set point - Square block

int tile_loct_check(int key_pressed, bool debug_mode = false) {
	// Upward
	if ((key_pressed == 87 || key_pressed == 119) && (cursor_y_pos <= 0 && cursor_z_pos > 2)) {
		if (debug_mode) std::cout << "\n *CHNG : Y pos = 2, Z pos -= 3*";
		cursor_z_pos -= 3;
		cursor_y_pos = 2;

		return 1;
	}

	// Left
	if ((key_pressed == 65 || key_pressed == 97) && (cursor_x_pos <= 0 && (cursor_z_pos != 0 && cursor_z_pos != 3 && cursor_z_pos != 6))) {
		if (debug_mode) std::cout << "\n *CHNG : X pos = 2, Z pos -= 1*";
		cursor_z_pos -= 1;
		cursor_x_pos = 2;

		return 1;
	}

	// Downward
	if ((key_pressed == 83 || key_pressed == 115) && (cursor_y_pos >= 2 && cursor_z_pos < 6)) {
		if (debug_mode) std::cout << "\n *CHNG : Y pos = 0, Z pos += 3*";
		cursor_z_pos += 3;
		cursor_y_pos = 0;

		return 1;
	}

	// Right
	if ((key_pressed == 68 || key_pressed == 100) && (cursor_x_pos >= 2 && (cursor_z_pos != 2 && cursor_z_pos != 5 && cursor_z_pos != 8))) {
		if (debug_mode) std::cout << "\n *CHNG : X pos = 0, Z pos += 1*";
		cursor_z_pos += 1;
		cursor_x_pos = 0;

		return 1;
	}

	if (debug_mode) std::cout << "\n [. . . .]";

	return 0;
}

int cursor_movement(std::vector<std::vector<std::vector<int>>> arr, int user_input, bool initiate_cache = false, bool debug_mode = false) {
	if (!initiate_cache) return -1;
	std::vector<std::vector<std::vector<int>>> grid_tile = arr;

	clearance(30, 0, 0);
	if (debug_mode) std::cout << " Default coor :\n X: " << cursor_x_pos << "\n Y: " << cursor_y_pos << "\n Z: " << cursor_z_pos << "\n";

	int cursor = 178;
	grid_tile[cursor_z_pos][cursor_y_pos][cursor_x_pos] = cursor;

	bool temp_state = tile_loct_check(user_input, debug_mode);
	if (debug_mode) std::cout << "\n Check change :\n X: " << cursor_x_pos << "\n Y: " << cursor_y_pos << "\n Z: " << cursor_z_pos;

	// Input related logic
	// -------------------
	if (user_input == 27) return 0;

	if ((user_input == 87 || user_input == 119)) {		// W - up
		if (temp_state) grid_tile[cursor_z_pos + 3][0][cursor_x_pos] = arr[cursor_z_pos][cursor_y_pos][cursor_x_pos];
		else grid_tile[cursor_z_pos][cursor_y_pos][cursor_x_pos] = arr[cursor_z_pos][cursor_y_pos][cursor_x_pos];

		if (cursor_y_pos > 0 && !temp_state) cursor_y_pos -= 1;
		grid_tile[cursor_z_pos][cursor_y_pos][cursor_x_pos] = cursor;
	}

	else if (user_input == 65 || user_input == 97) {	// A - left
		if (temp_state) grid_tile[cursor_z_pos + 1][cursor_y_pos][0] = arr[cursor_z_pos][cursor_y_pos][cursor_x_pos];
		else grid_tile[cursor_z_pos][cursor_y_pos][cursor_x_pos] = arr[cursor_z_pos][cursor_y_pos][cursor_x_pos];

		if (cursor_x_pos > 0 && !temp_state) cursor_x_pos -= 1;
		grid_tile[cursor_z_pos][cursor_y_pos][cursor_x_pos] = cursor;
	}

	else if (user_input == 83 || user_input == 115) {	// S - down
		if (temp_state) grid_tile[cursor_z_pos - 3][2][cursor_x_pos] = arr[cursor_z_pos][cursor_y_pos][cursor_x_pos];
		else grid_tile[cursor_z_pos][cursor_y_pos][cursor_x_pos] = arr[cursor_z_pos][cursor_y_pos][cursor_x_pos];

		if (cursor_y_pos < 2 && !temp_state) cursor_y_pos += 1;
		grid_tile[cursor_z_pos][cursor_y_pos][cursor_x_pos] = cursor;
	}

	else if (user_input == 68 || user_input == 100) {	// D - right
		if (temp_state) grid_tile[cursor_z_pos - 1][cursor_y_pos][2] = arr[cursor_z_pos][cursor_y_pos][cursor_x_pos];
		else grid_tile[cursor_z_pos][cursor_y_pos][cursor_x_pos] = arr[cursor_z_pos][cursor_y_pos][cursor_x_pos];

		if (cursor_x_pos < 2 && !temp_state) cursor_x_pos += 1;
		grid_tile[cursor_z_pos][cursor_y_pos][cursor_x_pos] = cursor;
	}

	if (debug_mode) std::cout << "\n\n Input change :\n X: " << cursor_x_pos << "\n Y: " << cursor_y_pos << "\n Z: " << cursor_z_pos;

	std::cout << "\n";
	print_tile(grid_tile, cursor);
	std::cout << " [Edit mode] : ";
	std::cout << "\n Key pressed [" << char(user_input) << "] ";

	return 0;
}

// load, save, create system
// .....cws


int main() {
	std::vector<std::vector<std::vector<int>>> grid_tile = generate_tile();

	bool activation_state = false;	//  Technical
	bool debug_mode = false;		//    stuff

	bool screen_title = true;		// screen title
	bool levels_menu = false;		// consist of levels
	bool main_menu = false;			// consist of level menu, exit, leaderboard, and credit
	bool play_mode = false;			// we play

	while (true) {
		if (screen_title) {
			screen_title = false;
			main_menu = true;
	
			std::cout << "\n"; start_title();; std::cout << "\n Press any key to start..";	// Screen title
			_getch();
	
			clearance(30, 0, 0);
			continue;
		}
	
		if (main_menu) {
			clearance(30);
	
			main_menu_sect();
			int menu_input = _getch();
			
			// Key input 4
			if (menu_input == 52 && exit_session() == 1) {
				exit_msg();
				return 0;
			}
			
			// Key input 1
			else if (menu_input == 49) {	// bruhh come on. proper input for gameplay
				clearance(30);
				main_menu = false;
				play_mode = true;			// ke menu level duru baru nanti play mode
				continue;
			}

			// Key input 2
			else if (menu_input == 50) {
				// duh ini lagi, ada leaderboard segala, bismillah dah
			}

			// Key input 3
			else if (menu_input == 51) {
				credit_session();
			}

			continue;
		}
	
		//if (levels_menu)
	
		if (play_mode) {
			// Default output when activation state is false
			if (!activation_state) {
				clearance(30, 0, 0);
				std::cout << "\n"; print_tile(grid_tile);
				std::cout << " [View mode] : ";
	
				if (debug_mode) std::cout << "\n Debug mode on ";
			}
	
			int user_input = _getch();
	
			// Exit command - sementara pencet esc
			if (user_input == 27) {
				play_mode = false;
				main_menu = true;
				continue;
			}
	
			// Input mode
			// pressed E or e for enabling and disabling activation_state 
			if (user_input == 69 || user_input == 101) activation_state ? activation_state = false : activation_state = true;
	
			// pressed captial G for enabling and disabling debug mode
			if (user_input == 71) debug_mode ? debug_mode = false : debug_mode = true;
	
			// For input mode, enable when acvitation state is true
			cursor_movement(grid_tile, user_input, activation_state, debug_mode);
			continue;
		}
	}

	return 0;
}

// Requirement
// -----------
// Fixing 'cursor' move, (Left, Down, Right)						[Finished]
// Add Screen title													[Finished]
// Add Start menu													[On Going]
// // Input system in edit mode                                     
// Add level section																				
// Validation check (for each row, column and block of square)		
// Check input system (wave function collapse, advance validation)	
// Cursor overlay information										
// load, save level system											
// create level system												
// Cursor and border customization (player can choose)				
// Tidying it up													[On going]