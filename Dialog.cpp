/******************************************************************************
 *
 *  @project Connect Four
 *
 *  @file    Dialog.cpp
 *
 *  @date    2019-08-23
 *
 *  @author  Arthur Ackermann
 *
 *  @brief   User interface
 *           Provides menu dialog and user interaction
 *
 ******************************************************************************/

/*=============================================================================
=====                              INCLUDES                               =====
=============================================================================*/

/*------  Module includes  -------*/
#include "main.hpp"
#include "Dialog.hpp"

/*=============================================================================
=====                         FUNCTIONS / METHODS                         =====
=============================================================================*/

/******************************************************************************
 *  @function   Constructor of class Dialog
 *
 *  @brief      * Instantiates a Dialog object
 *              * Inits start parameter
 *  @param      -
 ******************************************************************************/

Dialog::Dialog()
{
    DEBUG_CONSTRUCTOR;

    siStartPlayer = 0;

    // Set initial values for Player objects
    vSet_StartPlayer (oPlayer_H, true);     // First player
    vSet_StartPlayer (oPlayer_M, false);

    vCursor_Visible (false);
}

/******************************************************************************
 *  @function   Destructor of class Dialog
 *
 *  @brief      Destroys this Dialog object
 ******************************************************************************/

Dialog::~Dialog()
{
    DEBUG_DESTRUCTOR;
}


/******************************************************************************
 *  @function   vMenuLoop
 *
 *  @brief      Reads user key press within main menu and jumps to
 *              corresponding functions.
 *              Runs in a loop until a valid key press is recognized.
 *  @param      -
 *  @return     -
 ******************************************************************************/

void Dialog::vMenuLoop()
{
    short key;
    bool  run_game = false;

    while (!run_game)
    {
        // Read key presses
        key = oKey.iReadKeys( {KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_q, KEY_q} );

        switch (key)
        {
            case KEY_1:  run_game = true;       break;

            case KEY_2:  vToggle_CurrentPlayer();
                         siStartPlayer = siGet_CurrentPlayer();
                         vShow_GameCfg();       break;

            case KEY_3:  vMenu_BoardSize();     break;
            case KEY_4:  vMenu_WinTokens();     break;
            case KEY_5:  vRestore_Defaults();   break;

            case KEY_q:
            case KEY_Q:  _Exit(0);

            default:     _Exit(1);
        }
    }
}


/******************************************************************************
 *  @function   vShow_Title
 *
 *  @brief      Prints game title and program version
 *  @param      -
 *  @return     -
 ******************************************************************************/

void Dialog::vShow_Title()
{
    vPrintU (L"  ╔════════════════════╗       \n"
              "  ║ Connect Four " VERSION "  ║\n"
              "  ╚════════════════════╝       \n");
}


/******************************************************************************
 *  @function   vShow_GameCfg
 *
 *  @brief      Prints current configuration for the game, like
 *              game board size, start player and how many tokens to win
 *  @param      -
 *  @return     -
 ******************************************************************************/

void Dialog::vShow_GameCfg ()
{
    //INIT_CONSOLE_COLOR; COL_SAVE;
    vColor_Save();

    vCurPos_Set (Pos_GameInfo);

    std::cout << "  -------------------------------------------"  << std::endl;
    vClear_Below (3, 45);
    std::cout << "  "; vColor_Set(COL_YELLOW); std::cout << "  "; vColor_Restore();
    std::cout << " Payer 1 (Human)      ";
    if (oPlayer_H.bIs_CurrentPlayer()) std::cout <<  "-> FIRST PLAYER";
    std::cout << std::endl;

    std::cout << "  "; vColor_Set(COL_RED); std::cout << "  " ; vColor_Restore();
    std::cout << " Payer 2 (Computer)   ";
    if (oPlayer_M.bIs_CurrentPlayer()) std::cout <<  "-> FIRST PLAYER";
    std::cout << std::endl;

    std::cout << "     " << siGet_WinTokens() << " Tokens to win" << std::endl;;

    std::cout << "  -------------------------------------------\n"  << std::endl;
}


/******************************************************************************
 *  @function   vMenu_Main
 *
 *  @brief      Prints main menu
 *  @param      -
 *  @return     -
 ******************************************************************************/

void Dialog::vMenu_Main()
{
    vCurPos_Set (Pos_Menu);  vClear_Below(5, 40);

    std::cout <<
    "  [ 1 ]   Start game                     \n"
    "  [ 2 ]   Toggle start Player            \n"
    "  [ 3 ]   Change board size              \n"
    "  [ 4 ]   Change number of tokens to win \n"
    "  [ 5 ]   Restore defaults               \n\n"
    "  [ Q ]   Quit game                        "
    << std::endl;
}


/******************************************************************************
 *  @function   vMenu_BoardSize
 *
 *  @brief      User dialog to change the game board size.
 *              It will be asked for number of slots (X direction)
 *              and number of lines (Y direction)
 *  @param      -
 *  @return     -
 ******************************************************************************/

void Dialog::vMenu_BoardSize()
{
    short  slots, lines;
    COORD  cur_pos;
    bool   input_err = false;

    vCursor_Visible (true);         // Show cursor
    vCurPos_Set     (Pos_Menu);     // Set cursor to menu menu area
    vClear_Below    (8, 80);

    /***  Input number of game board slots (X direction)  ***/
    do
    {
        cur_pos = tCurPos_Get();    // Save cursor position
        std::cout << "  Define slots (Min: " << BOARD_SLOTS_MIN
                  << " / Max: "              << BOARD_SLOTS_MAX << "):  ";

        slots = siGetNum();  std::cout << std::endl;    // Input numeric value

        // Check if input value is in valid range
        if (slots < BOARD_SLOTS_MIN || slots > BOARD_SLOTS_MAX)
        {
            input_err = true;  BEEP_KEY;

            std::cout << "\n  !!! INVALID input... Please retry !!!" << std::endl;
            vCurPos_Set (cur_pos); vClear_Line(80);     // Restore cursor position
        }
        else input_err = false;

    } while(input_err);     // Repeat input if value is invalid

    vClear_Below (2, 80);

    /***  Input number of game board lines (Y direction)  ***/
    do
    {
        cur_pos = tCurPos_Get();    // Save cursor position
        std::cout << "  Define lines (Min: " << BOARD_LINES_MIN
                  << " / Max: "              << BOARD_LINES_MAX << "):  ";

        lines = siGetNum();  std::cout << std::endl;    // Input numeric value

        // Check if input value is in valid range
        if (lines < BOARD_LINES_MIN || lines > BOARD_LINES_MAX)
        {
            input_err = true;  BEEP_KEY;

            std::cout << "\n  !!! INVALID input... Please retry !!!" << std::endl;
            vCurPos_Set (cur_pos); vClear_Line(80);     // Restore cursor position
        }
        else input_err = false;

    } while(input_err);                 // Repeat input if value is invalid

    vCursor_Visible (false);            // Hide cursor

    vSet_BoardSize ({slots, lines});    // Sets game board size / dimension
    vUpdate_Screen();                   // Redraw complete screen
}


/******************************************************************************
 *  @function   vMenu_WinTokens
 *
 *  @brief      User dialog to change the number of tokens to win.
 *              Means the token chain length in horizontal, vertical
 *              and diagonal directions.
 *  @param      -
 *  @return     -
 ******************************************************************************/

void Dialog::vMenu_WinTokens()
{
    short  tokens;
    COORD  cur_pos;
    bool   input_err = false;

    vCursor_Visible (true);         // Show cursor
    vCurPos_Set     (Pos_Menu);     // Set cursor to menu menu area
    vClear_Below    (8, 80);

    /***  Input number of tokens to win (token chain length)  ***/
    do
    {
        cur_pos = tCurPos_Get();    // Save cursor position
        std::cout << "  Define number of tokens to win (Min: "
                  << WIN_TOKENS_MIN << " / Max: " << siGet_WinTokens_Max() << "):  ";

        tokens = siGetNum();  std::cout << std::endl;    // Input numeric value

        if (tokens < WIN_TOKENS_MIN || tokens > siGet_WinTokens_Max())
        {
            input_err = true;  BEEP_KEY;

            std::cout << "\n  !!! INVALID input... Please retry !!!" << std::endl;
            vCurPos_Set (cur_pos); vClear_Line(80);
        }
        else input_err = false;

    } while(input_err);         // Repeat input if value is invalid

    vCursor_Visible (false);    // Hide cursor

    vSet_WinTokens (tokens);    // Set new number of tokens to win
    vUpdate_Screen();           // Redraw complete screen
}


/******************************************************************************
 *  @function   vRestore_Defaults
 *
 *  @brief      Restores all game parameter to default as on program start
 *  @param      -
 *  @return     -
 ******************************************************************************/

void Dialog::vRestore_Defaults()
{
    vSet_BoardSize ({BOARD_SLOTS, BOARD_LINES});
    vSet_WinTokens (WIN_TOKENS);

    vSet_StartPlayer (oPlayer_H, true);
    vSet_StartPlayer (oPlayer_M, false);

    vUpdate_Screen();
}


/******************************************************************************
 *  @function   vClear_Line
 *
 *  @brief      Clears the line of current cursor position and
 *              sets afterwards the cursor to beginning of line
 *
 *  @param      columns : number of columns that have to be cleared
 *  @return     -
 ******************************************************************************/

void Dialog::vClear_Line (int columns)
{
    vClear_Below (1, columns);
}


/******************************************************************************
 *  @function   vClear_Line
 *
 *  @brief      Clears a screen area.
 *              Cursor remains at and of cleared area.
 *
 *  @param      lines   : number of lines that have to be cleared
 *  @param      columns : number of columns that have to be cleared
 *  @return     -
 ******************************************************************************/

void Dialog::vClear_Lines (int lines, int columns)
{
    for (int y=1; y <= lines; y++)
    {
        for (int x=1; x <= columns; x++)  std::cout << " ";
        std::cout << std::endl;
    }
}


/******************************************************************************
 *  @function   vClear_Below
 *
 *  @brief      Clears a screen area.
 *              Afterwards cursor will bes set to beginning of clear area.
 *
 *  @param      lines   : number of lines that have to be cleared
 *  @param      columns : number of columns that have to be cleared
 *  @return     -
 ******************************************************************************/

void Dialog::vClear_Below (int lines, int columns)
{
    COORD pos;  pos = tCurPos_Get();

    vClear_Lines (lines, columns);
    vCurPos_Set (pos);
}


/******************************************************************************
 *  @function   vUpdate_Screen
 *
 *  @brief      Updates complete screen
 *              * Prints screen elements (slot selection line, game board,
 *                menu, game configuration info and main menu)
 *              * Saves cursor position of each screen element
 *  @param      -
 *  @return     -
 ******************************************************************************/

void Dialog::vUpdate_Screen()
{
    system("CLS");

    // Print screen elements and save cursor
    // position of each screen element
    vShow_Title();
    Pos_SlotSelect = tCurPos_Get(); vShow_SlotSelect (0, 0);
    Pos_Board      = tCurPos_Get(); vDraw_Board      ();
    Pos_GameInfo   = tCurPos_Get(); vShow_GameCfg    ();
    Pos_Menu       = tCurPos_Get(); vMenu_Main       ();
}


/******************************************************************************
 *  @function   vSet_StartPlayer
 *
 *  @brief      Sets the first player for the game
 *
 *  @param      obj          : Reference to player object
 *  @param      start_player : ID of first player
 *  @return     -
 ******************************************************************************/

void Dialog::vSet_StartPlayer (Player& obj, bool start_player)
{
    obj.bCurrentPlayer = start_player;
    siStartPlayer = siGet_CurrentPlayer();
}


/******************************************************************************
 *  @function   siGet_StartPlayer
 *
 *  @brief      Returns ID of first player of the game
 *  @param      -
 *  @return     siStartPlayer : ID of first player
 ******************************************************************************/

short Dialog::siGet_StartPlayer()
{
    return siStartPlayer;
}


/******************************************************************************
 *  @function   siGet_CurrentPlayer
 *
 *  @brief      Returns ID of current player
 *  @param      -
 *  @return     PLAYER_1_ID || PLAYER_2_ID : ID of current player
 ******************************************************************************/

short Dialog::siGet_CurrentPlayer()
{
    return (oPlayer_H.bIs_CurrentPlayer()) ? PLAYER_1_ID : PLAYER_2_ID;
}


/******************************************************************************
 *  @function   vToggle_CurrentPlayer
 *
 *  @brief      Switches active player state between booth player
 *  @param      -
 *  @return     -
 ******************************************************************************/

void Dialog::vToggle_CurrentPlayer()
{
    oPlayer_H.vSet_CurrentPlayer (  oPlayer_M.bIs_CurrentPlayer() );
    oPlayer_M.vSet_CurrentPlayer ( !oPlayer_M.bIs_CurrentPlayer() );
}

