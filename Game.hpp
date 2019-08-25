/******************************************************************************
 *
 *  @project Connect Four
 *
 *  @file    Game.hpp
 *
 *  @date    2019-08-23
 *
 *  @author  Arthur Ackermann
 *
 *  @class   Game
 *
 ******************************************************************************/

/*=============================================================================
=====                         SET OWN MODULE ID                           =====
=============================================================================*/

#ifndef _GAME_H_
#define _GAME_H_

/*=============================================================================
=====                              INCLUDES                               =====
=============================================================================*/

/*------  System interface includes  -------*/
#include <iostream>
#include <conio.h>          // getch()

/*------  Module includes  -------*/
#include "Dialog.hpp"

/*=============================================================================
=====                               CLASSES                               =====
=============================================================================*/

class Game : public Dialog
{
    public:
    /** Constructor / Destructor **/
                 Game();
        virtual ~Game();

    protected:

    private:
    /** Variables **/
        short   siWinner;

    /** Member functions / methods **/
        virtual void vInitGame();
        virtual void vGameLoop();

        virtual void vShow_GameState();
        virtual void vShow_WinnerInfo();
        virtual void vShow_TieGameInfo();
};

#endif // _GAME_H_
