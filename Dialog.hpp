/******************************************************************************
 *
 *  @project Connect Four
 *
 *  @file    Dialog.hpp
 *
 *  @date    2019-08-23
 *
 *  @author  Arthur Ackermann
 *
 *  @class   Dialog
 *
 ******************************************************************************/

/*=============================================================================
=====                         SET OWN MODULE ID                           =====
=============================================================================*/

#ifndef _DIALOG_H_
#define _DIALOG_H_

/*=============================================================================
=====                              INCLUDES                               =====
=============================================================================*/

/*------  System interface includes  -------*/
#include <iostream>
#include <windows.h>    // Console color and cursor control

/*------  Module header includes  -------*/
#include "Board.hpp"
#include "Player.hpp"
#include "KeyHandler.hpp"

/*=============================================================================
=====                               CLASSES                               =====
=============================================================================*/

class Dialog : public Board, public Player, public KeyHandler
{
    public:
    /** Constructor / Destructor **/
                 Dialog();
        virtual ~Dialog();

    protected:
    /** Variables **/
        COORD   Pos_SlotSelect, Pos_Board, Pos_Menu, Pos_GameInfo;

    /** Objects **/
        Player      oPlayer_H;     // First player
        Player      oPlayer_M;
        KeyHandler  oKey;

    /** Getter / Setter **/
        virtual short   siGet_StartPlayer     ();
        virtual short   siGet_CurrentPlayer   ();
        virtual void    vSet_StartPlayer      (Player& obj, bool start_player);
        virtual void    vToggle_CurrentPlayer ();

        virtual void    vMenu_Main        ();

    /** Further Member functions / methods **/
        virtual void    vMenuLoop         ();
        virtual void    vShow_Title       ();
        virtual void    vShow_GameCfg     ();

        virtual void    vClear_Line       (int columns);
        virtual void    vClear_Lines      (int lines, int columns);
        virtual void    vClear_Below      (int lines, int columns);

    private:
    /** Variables **/
        short   siStartPlayer;

    /** Member functions / methods **/
        virtual void    vMenu_BoardSize   ();
        virtual void    vMenu_WinTokens   ();
        virtual void    vRestore_Defaults ();
        virtual void    vUpdate_Screen    ();
};

#endif // _DIALOG_H_
