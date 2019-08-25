/******************************************************************************
 *
 *  @project Connect Four
 *
 *  @file    Board.hpp
 *
 *  @date    2019-08-23
 *
 *  @author  Arthur Ackermann
 *
 *  @class   Board
 *
 ******************************************************************************/

/*=============================================================================
=====                         SET OWN MODULE ID                           =====
=============================================================================*/

#ifndef _BOARD_H_
#define _BOARD_H_

/*=============================================================================
=====                              INCLUDES                               =====
=============================================================================*/

/*------  System interface includes  -------*/
#include <iostream>
#include <vector>

/*------  Module header includes  -------*/
#include "ConsoleControl.hpp"

/*=============================================================================
=====                           MACROS / INLINES                          =====
=============================================================================*/

/***  Game board attributes ***/
#define BOARD_SLOTS       7
#define BOARD_LINES       6
#define WIN_TOKENS        4

#define BOARD_SLOTS_MIN   3
#define BOARD_SLOTS_MAX   15
#define BOARD_LINES_MIN   3
#define BOARD_LINES_MAX   15
#define WIN_TOKENS_MIN    3

/***  Game board field values  **/
#define FIELDVAL_EMPTY    0
#define FIELDVAL_HUMAN    1
#define FIELDVAL_MACHINE  2

/***  Player wining IDs  ***/
#define WON_HUMAN   FIELDVAL_HUMAN
#define WON_MACHINE FIELDVAL_MACHINE

/*=============================================================================
=====                               CLASSES                               =====
=============================================================================*/

class Board : public ConsoleControl
{
    public:
    /** Constructor / Destructor **/
                 Board();
        virtual ~Board();

    protected:
    /** Types / Structs **/
        typedef struct {short slot; short line;} BOARD;

    /** Getter / Setter **/
        virtual short   siGet_WinTokens     ();
        virtual short   siGet_WinTokens_Max ();
        virtual BOARD   tGet_BoardSize      ();
        virtual short   siGet_Field         (BOARD _FieldPos);
        virtual short   siGet_FreeSlots     ();
        virtual short   siGet_FreeSlotNr    (short nth_freeslot);
        virtual short   siGet_FreeFields    ();
        virtual short   siGet_SlotSelection ();

        virtual void    vSet_WinTokens      (short _siWinTokens);
        virtual void    vSet_BoardSize      (BOARD _aBoardSize);
        virtual void    vSet_Field          (BOARD _aFieldPos, short val);
        virtual void    vSet_SlotSelection  (short _siSlotSelection);

    /** Further Member functions / methods **/
        virtual void    vClear_Board        (); // Reset 2D vector (game board) to zero
        virtual void    vDraw_Board         ();
        virtual void    vShow_SlotSelect    (short slot, short color);

        virtual void    vSlotSelect_LShift  ();
        virtual void    vSlotSelect_RShift  ();
        virtual bool    bInsert_Token       (short player_id, short slot);
        virtual void    vAnimate_TokenDrop  (short player_id, short slot);
        virtual short   siCheck_WinState    ();

    private:
    /** Variables **/
        BOARD   tBoardSize;
        short   siSlotSelection;
        short   siWinTokens, siWinTokens_Max;

        std::vector< std::vector<short> > vecBoard;   // Game board

    /** Member functions / methods **/
        virtual void    vInit_Board         (BOARD _BoardSize);
};

#endif // _BOARD_H_
