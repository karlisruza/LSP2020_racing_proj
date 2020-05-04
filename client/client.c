#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ncurses.h>
#include <math.h>       

#include "../data/payload/payload.h"
#include "../data/game/game.h"
#include "connect/connect.h"
#include "handleData/handleData.h"
#include "sendMessage/sendName.h"
#include "sendMessage/requestGame.h"
#include "sendMessage/createGame.h"
#include "sendMessage/joinGame.h"
#include "sendMessage/requestPlayer.h"
#include "sendMessage/ping.h"

#include "display/const.h"
#include "display/car.h"
#include "display/graphics.h"
#include "display/controls.h"


/*typedef struct Game{
    int gameid;
    int status; //(0- WAITING_PLAYERS, 1- STARTED, -1- ENDED);
    int hostId;
    playerlist_t* playerList;
    struct Game* next;
    struct Game* prev;
}game_t;

typedef struct Game_list{
    int count;
    game_t* head;
    game_t* tail;
}gamelist_t;

void displayGameCreator (WINDOW* win, gamelist_t** list){
    clear(win);
    attron(A_BOLD);
    mvwprintw(win, 1, 3, "ENTER GAME CREDENTIALS");

    game_t* newGame = (game_t*) malloc(sizeof(game_t));

    newGame

}*/




int main(int argc, char* argv[]){
    // ./c 8015 10.0.2.15 8014
    int clientFd;
    if (argc > 1){
        clientFd = clientConnect(argv[1], argv[2], argv[3]); //sets up connection
    } 
    else{    
        printf("There are three arguments - client port, server IP and server port. Autoset to 8015, 127.0.0.1, and 8014.\n");
        clientFd = clientConnect("8015", "127.0.0.1", "8014"); //sets up connection
    }

    player_t* clientPlayer = (player_t*)malloc(sizeof(player_t));
    playerlist_t* playerList = (playerlist_t*)malloc(sizeof(playerlist_t)); //contains all players in lobby
    gamelist_t* gameList = (gamelist_t*)malloc(sizeof(gamelist_t));

    WINDOW* win = startGraphics();  //graphics.h
    enableRawMode();                //controls.h


    enterName(win);                 //in graphics.h
    clientPlayer->name = writePrompt(win, 3, 4); //in controls.h


    if(clientPlayer->name != NULL){
        clientPlayer->ID = sendName(clientPlayer->name, clientFd); //receives id as response from server
    } else {
        exit(1);
    };
    
        //populate gamelist and then display it, and initialize navigator
    requestGame(&gameList, clientFd);
    displayGameList(win, &gameList); //in graphics.h
    clientPlayer->gameID = gameListNav(win, &gameList);


    //game_t enteredGame = (game_t*) malloc (sizeof(game_t));
    if (clientPlayer->gameID == 0){
        // int createGame(player_t** player, int clientFd){
        if (createGame(&clientPlayer, clientFd) < 1){
            exit(1);
        }
    } 

    joinGame (&playerList, &clientPlayer, clientFd);
        //join game
    //create listener thread
    mvwprintw(win, 20, 20, "Player name: %s", playerList -> head -> name);

    drawLobby(win, &playerList);


//     void displayGameList (WINDOW * win, gamelist_t** list){
        
//         werase(win);

//         if ((*list) != NULL && (*list) -> head != NULL){
//             game_t* current = (game_t*)malloc(sizeof(game_t));
//             current = (*list) -> head;
//             int entryCount = 1; 
            
//             mvwprintw(win, 3, 3, "--- LIST OF GAMES ---");

//             while (current != NULL){
//                 wattron(win, A_DIM);
//                     mvwprintw(win, 5*entryCount, 3, "Game number: %d", entryCount);

//                     mvwprintw(win, 5*entryCount + 1, 6, "Game ID: %d", current -> gameid);
//                     mvwprintw(win, 5*entryCount + 2, 6, "Host ID: %d", current -> hostId);
//                     mvwprintw(win, 5*entryCount + 3, 6, "Status: %d", current -> status);
//                 wattroff(win, A_DIM);

//                 current = current -> next;
//                 entryCount++;
//             }

//         wattron(win, A_BOLD);
//             mvwprintw(win, 5*entryCount, 3, "CREATE YOUR OWN GAME (PRESS C)");
//         wattroff(win, A_BOLD);

        
//         //free (current);
//         wrefresh(win);
//         refresh();
//         }
//         else {
//             printf("games list is empty");
//             endwin();
//             exit(1);
//         }

//     return;
// }
    


    exit(1);


    //displayGames();
   // createGame(&clientPlayer, clientFd);
   // int gameId = 4;
   // joinGame(&playerList, &clientPlayer, clientFd, gameId);

    // while(true){
    //     //WaitForInput(&playerlist)-> either joingGame() or createGame()
    //     //displayLobby(&playerlist)
    //     //
    //     //waitForStart(); 
    // }     
}
