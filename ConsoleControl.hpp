/******************************************************************************
 *
 *  @project Connect Four
 *
 *  @file    ConsoleControl.hpp
 *
 *  @date    2019-08-23
 *
 *  @author  Arthur Ackermann
 *
 *  @class   ConsoleControl
 *
 ******************************************************************************/

/*=============================================================================
=====                         SET OWN MODULE ID                           =====
=============================================================================*/

#ifndef _CONSOLECONTROL_H_
#define _CONSOLECONTROL_H_

/*=============================================================================
=====                              INCLUDES                               =====
=============================================================================*/

/*------  System interface includes  -------*/
#include <iostream>
#include <wincon.h>      // Console color and cursor control

/*=============================================================================
=====                           MACROS / INLINES                          =====
=============================================================================*/

/***  Console colors  ***/
#define COL_RED_WHITE     79
#define COL_GREY_BLACK    112
#define COL_GREY_BLUE     113
#define COL_RED           192
#define COL_YELLOW        224

/*=============================================================================
=====                               CLASSES                               =====
=============================================================================*/

class ConsoleControl
{
    public:
    /** Constructor / Destructor **/
                 ConsoleControl();
        virtual ~ConsoleControl();

                virtual void    vCursor_Move    (short x, short y);


    protected:
    /** Member functions / methods **/
        virtual COORD   tCurPos_Get     ();
        virtual void    vCurPos_Set     (COORD pos);

        virtual void    vCursor_Visible (bool  visible);

        virtual void    vColor_Set      (short color);
        virtual void    vColor_Save     ();
        virtual void    vColor_Restore  ();

        virtual void    vPrintU         (const std::wstring str);   // Print unicode

    private:
    /** Variables **/
        short console_color;
};

#endif // _CONSOLECONTROL_H_
