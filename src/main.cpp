#include <stdio.h>
#include <iostream>
#include "canvas.h"
#include <string.h>
#include <chrono>
#include <thread>



#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 400
#define BOARD_WIDTH 160
#define BOARD_HEIGHT 100

//Two arrays one for storing the states after each epoch
//other for displaying and comparing
uint32_t* board;
uint32_t* state;

//utility func for getting the board state at loc(x,y)
int cell(int x, int  y) {
	return board[(y * BOARD_WIDTH) + x];
}

//utility func for setting custom initial state
void set(int x, int  y, std::wstring s) {
    int p = 0;
			for (auto c : s)
			{
				state[y*BOARD_WIDTH + x + p] = c == L'#' ? 1 : 0;
				p++;
			}
}

int main(int argc, char** argv)
{
    using namespace std::chrono_literals;
	canvas mycanvas("demo",SCREEN_WIDTH,SCREEN_HEIGHT,BOARD_WIDTH,BOARD_HEIGHT);

	board = new uint32_t[BOARD_WIDTH * BOARD_HEIGHT];
	state = new uint32_t[BOARD_WIDTH * BOARD_HEIGHT];



	memset(board, 0, BOARD_WIDTH * BOARD_HEIGHT * sizeof(uint32_t));
	memset(state, 0, BOARD_WIDTH * BOARD_HEIGHT * sizeof(uint32_t));

	//random initialization
    /*for (size_t i = 0; i < Tw * Th; i++)
	{
		state[i] = rand()%2;
	}*/


    /*set(80, 50, L"  ## ");
	set(80, 51, L" ##  ");
	set(80, 52, L"  #  ");*/

    set(60, 45, L"........................#............");
	set(60, 46, L"......................#.#............");
	set(60, 47, L"............##......##............##.");
	set(60, 48, L"...........#...#....##............##.");
	set(60, 49, L"##........#.....#...##...............");
	set(60, 50, L"##........#...#.##....#.#............");
	set(60, 51, L"..........#.....#.......#............");
	set(60, 52, L"...........#...#.....................");
	set(60, 53, L"............##.......................");
	
	
    
    int pitch = sizeof(board[0]) * BOARD_WIDTH;
	bool quit = false;

	//main loop
	while (!quit) {

        std::this_thread::sleep_for(50ms);
		
		quit = mycanvas.ProcessInput();
		 

		for (size_t i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++)
		{
			board[i] = state[i];
		}



		for (size_t j = 1; j < BOARD_HEIGHT-1; j++)
		{
			for (size_t i = 1; i < BOARD_WIDTH-1; i++)
			{
				int neighbours = cell(i - 1, j - 1) + cell(i - 1, j + 0) + cell(i - 1, j + 1) +
								 cell(i + 0, j - 1) +     + 0 +		       cell(i + 0, j + 1) +
								 cell(i + 1, j - 1) + cell(i + 1, j + 0) + cell(i + 1, j + 1);


				if (cell(i, j) == 1)

					state[(j * BOARD_WIDTH) + i] = neighbours == 2 || neighbours == 3;

				else
					state[(j * BOARD_WIDTH) + i] = neighbours == 3;
			
			}

		}
		
		mycanvas.Update(board, pitch,BOARD_WIDTH,BOARD_HEIGHT);
	}


	return 0;
}