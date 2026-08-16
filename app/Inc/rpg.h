
#ifndef _RPG_H_
#define _RPG_H_

typedef enum {
    RPG_Init_OK,
    RPG_Init_Error,
} RPG_Init_State;

typedef enum {
    RPG_Loop_OK,
    RPG_Loop_Error,
} RPG_Loop_State;

RPG_Init_State RPG_Init();
RPG_Loop_State RPG_Loop();

#endif
