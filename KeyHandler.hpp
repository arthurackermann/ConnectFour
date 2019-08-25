/******************************************************************************
 *
 *  @project Connect Four
 *
 *  @file    KeyHandler.hpp
 *
 *  @date    2019-08-23
 *
 *  @author  Arthur Ackermann
 *
 *  @class   KeyHandler
 *
 ******************************************************************************/

/*=============================================================================
=====                         SET OWN MODULE ID                           =====
=============================================================================*/

#ifndef _KEYHANDLER_H_
#define _KEYHANDLER_H_

/*=============================================================================
=====                              INCLUDES                               =====
=============================================================================*/

/*------  System interface includes  -------*/
#include <iostream>
#include <conio.h>          // getch()

/*------  Module header includes  -------*/
#include "ConsoleControl.hpp"

/*=============================================================================
=====                           MACROS / INLINES                          =====
=============================================================================*/

/***  Keyboard key codes  ***/
#define KEY_CTRL_SEQ        224
#define KEY_CTRL_OFFSET     1000

#define KEY_LEFT            75 + KEY_CTRL_OFFSET
#define KEY_RIGHT           77 + KEY_CTRL_OFFSET
#define KEY_UP              72 + KEY_CTRL_OFFSET
#define KEY_DOWN            80 + KEY_CTRL_OFFSET

#define KEY_SPACE           32
#define KEY_1               49
#define KEY_2               50
#define KEY_3               51
#define KEY_4               52
#define KEY_5               53

#define KEY_A               65
#define KEY_a               97
#define KEY_Q               81
#define KEY_q               113

/***  Warning sounds  **/
#define BEEP_KEY            Beep(1000, 150)
#define BEEP_FULL_SLOT      Beep( 300, 50 )

/*=============================================================================
=====                               CLASSES                               =====
=============================================================================*/

class KeyHandler
{
    public:
    /** Constructor / Destructor **/
                 KeyHandler();
        virtual ~KeyHandler();

    /** Member functions / methods **/
        template <typename T>       // Template for variable argument list
        short iReadKeys (std::initializer_list<T> key_list);

    protected:
    /** Member functions / methods **/
        virtual short siGetNum ();  // Read numeric keys

    private:
        ConsoleControl oConsole;
};


#endif // _KEYHANDLER_H_
