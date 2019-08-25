/******************************************************************************
 *
 *  @project Connect Four
 *
 *  @file    ConsoleControl.cpp
 *
 *  @date    2019-08-23
 *
 *  @author  Arthur Ackermann
 *
 *  @brief   Console interface
 *           Provides functionalities to control cursor position
 *           and colored console output
 *
 ******************************************************************************/

/*=============================================================================
=====                              INCLUDES                               =====
=============================================================================*/

/*------  Module includes  -------*/
#include "main.hpp"
#include "ConsoleControl.hpp"

/*=============================================================================
=====                         FUNCTIONS / METHODS                         =====
=============================================================================*/

/******************************************************************************
 *  @function   Constructor of class ConsoleControl
 *
 *  @brief      Instantiates a ConsoleControl object
 *  @param      -
 ******************************************************************************/

ConsoleControl::ConsoleControl()
{
    DEBUG_CONSTRUCTOR;
}


/******************************************************************************
 *  @function   Destructor of class ConsoleControl
 *
 *  @brief      Destroys this ConsoleControl object
 ******************************************************************************/

ConsoleControl::~ConsoleControl()
{
    DEBUG_DESTRUCTOR;
}


/******************************************************************************
 *  @function   tCurPos_Get
 *
 *  @brief      Returns current cursor position coordinate
 *  @param      -
 *  @return     csbi.dwCursorPosition : Cursor coordinate as list {x, y}
 ******************************************************************************/

COORD ConsoleControl::tCurPos_Get()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo (GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    return (csbi.dwCursorPosition);
}


/******************************************************************************
 *  @function   vCurPos_Set
 *
 *  @brief      Sets cursor to specified position (X-Y coordinate)
 *
 *  @param      pos : Cursor coordinate as list {x, y}
 *  @return     -
 ******************************************************************************/

void ConsoleControl::vCurPos_Set (COORD pos)
{
    SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


/******************************************************************************
 *  @function   vCursor_Move
 *
 *  @brief      Moves cursor in booth X-Y directions
 *
 *  @param      x : Steps in X direction
 *                  positive value -> to right / negative value -> to left
 *              y : Steps in Y direction
 *                  positive value -> down / negative value -> up
 *  @return     -
 ******************************************************************************/

void ConsoleControl::vCursor_Move (short x, short y)
{
    COORD cur_pos = tCurPos_Get();

    cur_pos.X += x;  cur_pos.Y += y;

    vCurPos_Set (cur_pos);
}


/******************************************************************************
 *  @function   vCursor_Visible
 *
 *  @brief      Hides cursor or makes him visible
 *
 *  @param      visible : true   makes cursor visible
 *                        false  hides cursor
 *  @return     -
 ******************************************************************************/

void ConsoleControl::vCursor_Visible (bool visible)
{
   CONSOLE_CURSOR_INFO cci;

   cci.dwSize   = 10;
   cci.bVisible = visible;  // Set cursor state visible or invisible

   SetConsoleCursorInfo (GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}


/******************************************************************************
 *  @function   vColor_Set
 *
 *  @brief      Sets console color for next console outputs
 *
 *  @param      color : Console color code
 *  @return     -
 ******************************************************************************/

void ConsoleControl::vColor_Set (short color)
{
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), color);
}


/******************************************************************************
 *  @function   vColor_Save
 *
 *  @brief      Saves current console color to global variable
 *  @param      -
 *  @return     -
 ******************************************************************************/

void ConsoleControl::vColor_Save()
{
    CONSOLE_SCREEN_BUFFER_INFO color;
    GetConsoleScreenBufferInfo (GetStdHandle(STD_OUTPUT_HANDLE), &color);

    console_color = color.wAttributes;
}


/******************************************************************************
 *  @function   vColor_Restore
 *
 *  @brief      Restores console color from global variable
 *  @param      -
 *  @return     -
 ******************************************************************************/

void ConsoleControl::vColor_Restore()
{
    vColor_Set (console_color);
}


/******************************************************************************
 *  @function   vPrintU
 *
 *  @brief      Prints strings as unicode which consists of wide characters
 *  @param      std::wstring str : String with support of special characters
 *  @return     -
 ******************************************************************************/

void ConsoleControl::vPrintU (const std::wstring str)
{
    const wchar_t* wstr = str.c_str();  // Convert string to wide char (unicode)

    WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), wstr, wcslen(wstr), NULL, NULL);
}
