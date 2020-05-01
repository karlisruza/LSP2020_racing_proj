#include "./handleType/handleAddPlayer.h"
#include "./handleType/handleRequestGame.h"
#include "./handleType/handleCreateGame.h"
#include "./handleType/handleJoinGame.h"
#include "./handleType/handleRequestPlayer.h"

#ifndef HANDLEDATA_H_INCLUDED
#define HANDLEDATA_H_INCLUDED

void handleData(msg_t *message, params_t* params){
    msg_t reply;
    up_pt* data;
    gamelist_t* gameList = params->gameList;;
    playerlist_t* playerList = params->playerList;
    int clientFd = params->clientFd;
    int length;

    printf("handleData enum %d\n", message->type);
    switch (message->type){
        case 1:
            printf("lmao\n");
            data = (up_pt*)(message->payload);
            printf("playerId %d", data->playerID);
            printf("gameId %d", data->playerID);
            printf("keypress x: %d", data->action.x);
            printf("keypress y: %d", data->action.y);
            printf("lmao\n");
            break;
        case JOIN_GAME:
            handleJoinGame(message, &gameList, &playerList);    
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7: //ping
            reply.type = PONG;
            length = ((void*)&reply.payload - (void*)&reply.type);
            sendData(clientFd, (void*)&reply, length, NULL);
            break;
        case 8:
            printf("PONG\n");
            break;
        case REQUEST_GAME:
            handleRequestGame(message, &gameList, clientFd);
            break;
        case CREATE_GAME:
            handleCreateGame(&gameList, clientFd);
            break;
        case ADD_PLAYER:{
            handleAddPlayer(message, clientFd, &playerList);
            break;
        }
        case REQUEST_PLAYER:
            handleRequestPlayer(message, &playerList, clientFd);
            break;
        default:
            perror("invalid message");
    }
}

#endif