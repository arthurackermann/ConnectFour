/******************************************************************************
 *
 *  @project Connect Four
 *
 *  @file    KeyHandler.cpp
 *
 *  @date    2019-08-23
 *
 *  @author  Arthur Ackermann
 *
 *  @brief   Keyboard interface
 *           Provides functionalities to catch user keyboard interaction
 *
 ******************************************************************************/

/*=============================================================================
=====                              INCLUDES                               =====
=============================================================================*/

/*------  Module includes  -------*/
#include "main.hpp"
#include "KeyHandler.hpp"

/*=============================================================================
=====                         FUNCTIONS / METHODS                         =====
=============================================================================*/

/******************************************************************************
 *  @function   Constructor of class KeyHandler
 *
 *  @brief      Instantiates a KeyHandler object
 *  @param      -
 ******************************************************************************/

KeyHandler::KeyHandler()
{
    DEBUG_CONSTRUCTOR;
}


/******************************************************************************
 *  @function   Destructor of class KeyHandler
 *
 *  @brief      Destroys this KeyHandler object
 ******************************************************************************/

KeyHandler::~KeyHandler()
{
    DEBUG_DESTRUCTOR;
}


/******************************************************************************
 *  @function   iReadKeys
 *
 *  @brief      Recognizes requested key presses
 *
 *  @param      key_list    : List of keys that have to be observed
 *  @return     key_pressed : Keycode of pressed key
 ******************************************************************************/

template <class T>      // Template for variable argument list
short KeyHandler::iReadKeys (std::initializer_list<T> key_list)
{
    bool key_ctrl_seq = false;
    bool stop_keyread = false;
    short key_pressed;

    while ( !stop_keyread )
    {
        // Flush keyboard input buffer
        FlushConsoleInputBuffer (GetStdHandle(STD_INPUT_HANDLE));

        short key_read = getch();   // Read key

        // Check for control key (like arrow keys) code sequence
        // In case set an offset to requested key
        if  (key_ctrl_seq) key_read += KEY_CTRL_OFFSET;

        if  (key_read == KEY_CTRL_SEQ)
             key_ctrl_seq = true;

        // Handle standard keys (non control keys)
        else
        {
            // Check if key list contains the pressed key
            for (auto key_request : key_list)
            {
                if (key_read == key_request)
                {
                    key_pressed  = key_read;
                    stop_keyread = true;
                    break;
                }
            }
            // If a key was pressed which is not in key list
            if (!stop_keyread) {BEEP_KEY;  key_ctrl_seq = false;}
        }
    }
    return key_pressed;
}
template short KeyHandler::iReadKeys (std::initializer_list<int>);
//template int KeyHandler::iReadKeys(std::initializer_list<const char*>);


/******************************************************************************
 *  @function   siGetNum
 *
 *  @brief      Recognizes numeric key presses
 *  @param      -
 *  @return     Keycode of pressed numeric key
 ******************************************************************************/

short KeyHandler::siGetNum()
{
    std::string input = "";             // Numeric string
    char chr;

    // Flush keyboard input buffer
    FlushConsoleInputBuffer (GetStdHandle(STD_INPUT_HANDLE));

    chr = getch();                      // Read key

    // Read characters until Enter or backspace key
    while (chr != '\r')
    {
        if (chr >= '0' && chr <= '9')   // Add only numbers.
        {
            std::cout << chr;
            input += chr;
        }
        else if (chr == 8)              // Backspace key
        {
            // Clear last character on screen
            oConsole.vCursor_Move (-1, 0); std::cout << " ";
            // Delete last character from input string
            oConsole.vCursor_Move (-1, 0); input.pop_back();
        }
        else BEEP_KEY;                  // Invalid key pressed

        chr = getch();                  // Read next character
    }
    return ( (short)std::atoi(input.c_str()) );
}

