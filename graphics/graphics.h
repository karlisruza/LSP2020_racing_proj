#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#define MAP_COLOR     		COLOR_PAIR(1)
#define PLAYER_ONE_COLOR    COLOR_PAIR(2)
#define PLAYER_TWO_COLOR    COLOR_PAIR(3)

#define MAP_HEIGHT          40
#define MAP_WIDTH           150

void winSizeCheck (WINDOW* win){
	while (COLS < MAP_WIDTH || LINES < MAP_HEIGHT+10){
		//basically, before the game begins, it checks it the 
		// race track fits on the screen and won't start the 
		// game until everything is order. It's to prevent ncurses glitches. 
	
		mvwprintw(win, 1, 3, "You need to increase the window size.\nTry decreasing character size (ctrl + [-])\nor increasing the terminal window size.");
		//outputs if the terminal width is not enough
		if (COLS < MAP_WIDTH){
			mvwprintw(win, 4, 3, "Window width should increase to %d. Increase it by %d.", MAP_WIDTH, MAP_WIDTH - COLS);
		}
		else {
			move(4, 3);
			clrtoeol();	//this removes all chars from the cursor
		}
		//outputs if the terminal height is not enough
		if (LINES < MAP_HEIGHT + 10){
			mvwprintw(win, 5, 3, "Window height should increase to %d. Increase it by %d.", MAP_HEIGHT + 10, MAP_HEIGHT - LINES+10);
		}
		else {
			move(5, 3);
			clrtoeol();
		}
		mvwprintw(win, 7, 1, "Press [enter] to check again.");
		refresh();
		wrefresh(win);
		//loop for pressing enter
		char enter = 0;
		while (enter != '\r' && enter != '\n') {
	 		enter = getchar(); 
	 	};
	}
	werase(win);
	return;
}

#endif