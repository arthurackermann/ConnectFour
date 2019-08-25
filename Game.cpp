/******************************************************************************
 *
 *  @project Connect Four
 *
 *  @file    Game.cpp
 *
 *  @date    2019-08-23
 *
 *  @author  Arthur Ackermann
 *
 *  @brief   Initiates the game, controls game flow
 *           and user interaction during the game
 *
 ******************************************************************************/

/*=============================================================================
=====                              INCLUDES                               =====
=============================================================================*/

/*------  Module includes  -------*/
#include "main.hpp"
#include "Game.hpp"

/*=============================================================================
=====                         FUNCTIONS / METHODS                         =====
=============================================================================*/

/******************************************************************************
 *  @function   Constructor of class Game
 *
 *  @brief      * Instantiates a Game object
 *              * Starts the game
 *  @param      -
 ******************************************************************************/


Game::Game()
{
    DEBUG_CONSTRUCTOR;

    vInitGame();
}


/******************************************************************************
 *  @function   Destructor of class Game
 *
 *  @brief      Destroys this Game object
 ******************************************************************************/

Game::~Game()
{
    DEBUG_DESTRUCTOR;
}


/******************************************************************************
 *  @function   vInitGame
 *
 *  @brief      * Sets initial default values
 *              * Prints screen elements (game board, menu, etc.)
 *              * Saves cursor position of each screen element
 *              * Starts menu and game loop
 *  @param      -
 *  @return     -
 ******************************************************************************/

void Game::vInitGame()
{
    system("CLS");

    // Reset first player
    if   ( siGet_StartPlayer() == PLAYER_1_ID )
         { vSet_StartPlayer (oPlayer_H, true  );
           vSet_StartPlayer (oPlayer_M, false ); }
    else { vSet_StartPlayer (oPlayer_H, false );
           vSet_StartPlayer (oPlayer_M, true  ); }

    siWinner = 0;       // Init / Reset winner state
    vClear_Board();     // Reset 2D vector (game board) to zero

    // Print screen elements and save cursor
    // position of each screen element
    vShow_Title();
    Pos_SlotSelect = tCurPos_Get();  vShow_SlotSelect(0, 0);
    Pos_Board      = tCurPos_Get();  vDraw_Board();
    Pos_GameInfo   = tCurPos_Get();  vShow_GameCfg();
    Pos_Menu       = tCurPos_Get();  vMenu_Main();

    vMenuLoop ();
    vGameLoop ();
}


/******************************************************************************
 *  @function   vGameLoop
 *
 *  @brief      Start of the game in a loop
 *              * For Human player reads keyboard interaction for slot selection
 *              * For Machine player generates a random slot
 *              * Checks for winner or tie game -> end of game
 *  @param      -
 *  @return     -
 ******************************************************************************/

void Game::vGameLoop()
{
    short key, slot, free_slots;
    short free_fields = siGet_FreeFields();

    vCurPos_Set (Pos_GameInfo);  vClear_Below (12, 45);

    vSet_SlotSelection(1);

    /******************************************************************
    *   Enter game loop until a player won or no moves left (tie game)
    *******************************************************************/
    while (siWinner == 0 && free_fields > 0)
    {
        /***  Human players move  ***/
        if (siGet_CurrentPlayer() == PLAYER_1_ID)
        {
            vCurPos_Set (Pos_SlotSelect);
            vShow_SlotSelect (siGet_SlotSelection(), COL_YELLOW);

            vShow_GameState();

            // Read keys for menu interaction
            key = oKey.iReadKeys ({KEY_LEFT, KEY_RIGHT, KEY_SPACE, KEY_a, KEY_A});

            switch (key)
            {
                case KEY_LEFT  :  vSlotSelect_LShift();  break;     // Move token one step left
                case KEY_RIGHT :  vSlotSelect_RShift();  break;     // Move token one step right

                                  // If token insertion was successful
                case KEY_SPACE :  if (bInsert_Token (PLAYER_1_ID, siGet_SlotSelection()))
                                  {
                                      vCurPos_Set (Pos_Board);
                                      vAnimate_TokenDrop (PLAYER_1_ID, siGet_SlotSelection());
                                      vToggle_CurrentPlayer();      // Switch human -> machine player
                                  }
                                  else BEEP_FULL_SLOT;  break;
                case KEY_a     :
                case KEY_A     :  vInitGame();          break;
                default        :  _Exit(1);
            }
        }
        /***  Machine players move  ***/
        else
        {
            vCurPos_Set (Pos_SlotSelect); vShow_SlotSelect(0, 0);
            vShow_GameState();

            // Check how many free slots left and
            // step out if board is full (no more possible moves)
            free_slots = siGet_FreeSlots();
            if (free_slots == 0) _Exit(1);

            // Generate a random slot for machine player move
            slot = oRandomNr.iRndNum (1, free_slots);
            slot = siGet_FreeSlotNr (slot);

            // Insert token in randomized slot
            bInsert_Token (PLAYER_2_ID, slot);

            // Show toke above randomized slot
            vCurPos_Set (Pos_SlotSelect);
            vShow_SlotSelect (slot, COL_RED);  Sleep(500);

            // Animate dropping of token in slot
            vCurPos_Set (Pos_Board);
            vAnimate_TokenDrop (PLAYER_2_ID, slot);

            // Switch machine -> human player
            vCurPos_Set (Pos_Board);
            vToggle_CurrentPlayer();
        }
        // Check if someone has won and ow many free slots left
        siWinner    = siCheck_WinState();
        free_fields = siGet_FreeFields();
    }

    vCurPos_Set (Pos_SlotSelect); vShow_SlotSelect(0, 0);   // Update slot selection line

    if   (siWinner > 0) vShow_WinnerInfo();     // Print winner information
    else                vShow_TieGameInfo();    // Print tie game information

    vInitGame();    // ReInit the game
}


/******************************************************************************
 *  @function   vShow_GameState
 *
 *  @brief      Displays current game state during players move
 *  @param      -
 *  @return     -
 ******************************************************************************/

void Game::vShow_GameState()
{
    vCurPos_Set (Pos_GameInfo);

    /***  Human players move  ***/
    if (siGet_CurrentPlayer() == PLAYER_1_ID)
    {
        std::cout <<
        "  -------------------------------------------\n";
        std::cout << "  "; vColor_Set(COL_YELLOW); std::cout << "  "; vColor_Restore();
        std::cout <<
        " Player 1  (Human)                           \n"
        "                                             \n"
        "     Please select slot and drop token       \n"
        "  -------------------------------------------\n"
        "                                             \n"
        "  [ LEFT  ]   Move token to left             \n"
        "  [ RIGHT ]   Move token to right            \n"
        "  [ SPACE ]   Drop token                     \n"
        "  [ A     ]   Abort game                     \n"
        << std::endl;

        vClear_Below (3, 50);
    }
    /***  Machine players move  ***/
    else
    {
        std::cout <<
        "  -------------------------------------------\n";
        std::cout << "  "; vColor_Set(COL_RED); std::cout << "  "; vColor_Restore();
        std::cout <<
        " Player 2  (Computer)                        \n"
        "                                             \n"
        "     Calculating move...  Please wait        \n"
        "  -------------------------------------------\n"
        << std::endl;

        vClear_Below (5, 50);  Sleep(750);
    }
}


/******************************************************************************
 *  @function   vShow_WinnerInfo
 *
 *  @brief      Displays winner notification of human or machine player
 *  @param      -
 *  @return     -
 ******************************************************************************/

void Game::vShow_WinnerInfo()
{
    vCurPos_Set (Pos_GameInfo);  vClear_Below (8, 50);

    vColor_Save();

    vColor_Restore(); std::cout << "  "; vColor_Set(COL_GREY_BLUE);
    std::cout << "                                       " << std::endl;

    vColor_Restore(); std::cout << "  "; vColor_Set(COL_GREY_BLACK);
    std::cout << "  !!!  C O N R A T U L A T I O N  !!!  " << std::endl;

    vColor_Restore(); std::cout << "  "; vColor_Set(COL_GREY_BLUE);
    std::cout << "                                       " << std::endl;

    vColor_Restore(); std::cout << "  "; vColor_Set(COL_GREY_BLUE);
    if (siWinner == PLAYER_1_ID)
    std::cout << "     Player 1 (Human) won the game     " << std::endl;
    else
    std::cout << "   Player 2 (Computer)  won the game   " << std::endl;

    vColor_Restore(); std::cout << "  "; vColor_Set(COL_GREY_BLUE);
    std::cout << "                                       " << std::endl;

    vColor_Restore();  vClear_Below (5, 50);
    std::cout << "\n  Press a key to continue..."          << std::endl;

    getch();
}


/******************************************************************************
 *  @function   vShow_TieGameInfo
 *
 *  @brief      Displays notification if the game ends undecided
 *  @param      -
 *  @return     -
 ******************************************************************************/

void Game::vShow_TieGameInfo()
{
    vCurPos_Set (Pos_GameInfo);  vClear_Below (8, 50);

    vColor_Save();

    vColor_Restore(); std::cout << "  "; vColor_Set(COL_RED_WHITE);
    std::cout << "                                  " << std::endl;

    vColor_Restore(); std::cout << "  "; vColor_Set(COL_RED_WHITE);
    std::cout << "  !!!  Game ended undecided  !!!  " << std::endl;

    vColor_Restore(); std::cout << "  "; vColor_Set(COL_RED_WHITE);
    std::cout << "                                  " << std::endl;

    vColor_Restore(); std::cout << "  "; vColor_Set(COL_RED_WHITE);
    std::cout << "      No player won the game      " << std::endl;

    vColor_Restore(); std::cout << "  "; vColor_Set(COL_RED_WHITE);
    std::cout << "                                  " << std::endl;

    vColor_Restore();  vClear_Below (5, 50);
    std::cout << "\n  Press a key to continue..."          << std::endl;

    getch();
}
