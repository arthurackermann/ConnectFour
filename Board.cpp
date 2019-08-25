/******************************************************************************
 *
 *  @project Connect Four
 *
 *  @file    Board.cpp
 *
 *  @date    2019-08-23
 *
 *  @author  Arthur Ackermann
 *
 *  @brief   Game board interface
 *           Provides functionalities to handle the game board.
 *
 ******************************************************************************/

/*=============================================================================
=====                              INCLUDES                               =====
=============================================================================*/

/*------  Module includes  -------*/
#include "main.hpp"
#include "Board.hpp"

/*=============================================================================
=====                         FUNCTIONS / METHODS                         =====
=============================================================================*/

/******************************************************************************
 *  @function   Constructor of class Board
 *
 *  @brief      * Instantiates a Board object
 *              * Inits game board with default values
 *  @param      -
 ******************************************************************************/

Board::Board()
{
    DEBUG_CONSTRUCTOR;

    vSet_BoardSize (BOARD {BOARD_SLOTS, BOARD_LINES});

    siWinTokens     = WIN_TOKENS;
    siWinTokens_Max = std::min (tBoardSize.slot, tBoardSize.line);
    siSlotSelection = 0;
}


/******************************************************************************
 *  @function   Destructor of class Board
 *
 *  @brief      Destroys this Board object
 ******************************************************************************/

Board::~Board()
{
    DEBUG_DESTRUCTOR;
}


/******************************************************************************
 *  @function   siGet_WinTokens
 *
 *  @brief      Returns number of tokens to win (token chain length)
 *  @param      -
 *  @return     siWinTokens : Number of tokens to win
 ******************************************************************************/

short Board::siGet_WinTokens()
{
    return siWinTokens;
}


/******************************************************************************
 *  @function   siGet_WinTokens_Max
 *
 *  @brief      Returns number of maximum tokens to win (token chain length).
 *              This depends on shortest game board side length (slots or lines)
 *  @param      -
 *  @return     siWinTokens_Max : Number of maximum tokens to win
 ******************************************************************************/

short Board::siGet_WinTokens_Max()
{
    return siWinTokens_Max;
}


/******************************************************************************
 *  @function   siGet_Field
 *
 *  @brief      Returns value of a game board field element
 *
 *  @param      _FieldPos : Coordinate of field element as list {slot, line}
 *  @return     vecBoard  : Vector element value of requested field
 ******************************************************************************/

short Board::siGet_Field (BOARD _FieldPos)
{
    return vecBoard[_FieldPos.slot][_FieldPos.line];
}


/******************************************************************************
 *  @function   tGet_BoardSize
 *
 *  @brief      Returns current game board size / dimension.
 *  @param      -
 *  @return     tBoardSize : Game board size as list of {slots, lines)
 ******************************************************************************/

Board::BOARD Board::tGet_BoardSize()
{
    return tBoardSize;
}


/******************************************************************************
 *  @function   siGet_FreeSlots
 *
 *  @brief      Returns number of slots which are not complete filled with tokens.
 *  @param      -
 *  @return     slot_count : Number of free slots
 ******************************************************************************/

short Board::siGet_FreeSlots()
{
    short slot_count = 0;

    // Iterator for outer vector
    std::vector< std::vector<short> >::iterator slot;

    // Count free slots
    for (slot = vecBoard.begin(); slot != vecBoard.end(); slot++)
    {
        if (*slot->begin() == 0) slot_count++;
    }

    return slot_count;
}


/******************************************************************************
 *  @function   siGet_FreeSlotNr
 *
 *  @brief      Returns slot number of n-th free slot.
 *              Example:  If slot 1 and 3 are full the 3rd free slot is slot 5
 *  @param      -
 *  @return     slot_nr : Number of n-th free slot
 *
 *  @note       slot_nr == 0 means the game board is full of tokens
 *              and no more moves possible -> end of game
 ******************************************************************************/

short Board::siGet_FreeSlotNr (short nth_freeslot)
{
    short slot_nr = 0;

    // Iterator for outer vector
    std::vector< std::vector<short> >::iterator slot;

    // Search for n-th free slot
    for (slot = vecBoard.begin(), slot_nr = 1; slot != vecBoard.end(); slot++, slot_nr++)
    {
        if (*slot->begin() == 0) nth_freeslot--;
        if (nth_freeslot   == 0) return slot_nr;
    }
    return slot_nr;
}


/******************************************************************************
 *  @function   siGet_FreeFields
 *
 *  @brief      Returns number of game board fields without a token.
 *  @param      -
 *  @return     free_fields : Number of game board fields without a token
 *
 *  @note       free_fields == 0 means the game board is full of tokens
 *              and no more moves possible -> end of game
 ******************************************************************************/

short Board::siGet_FreeFields()
{
    short free_fields = 0;

    std::vector< std::vector<short> >::iterator slot;   // Iterator for outer vector
    std::vector< short              >::iterator line;   // Iterator for inner vector

    // Count free fields  (means number of moves left)
    for (slot = vecBoard.begin(); slot != vecBoard.end(); slot++)
    {
        for (line = slot->begin(); line != slot->end(); line++)

        if (*line == 0) free_fields++;
    }
    return free_fields;
}


/******************************************************************************
 *  @function   siGet_SlotSelection
 *
 *  @brief      Returns the current slot selected by human player
 *  @param      -
 *  @return     siSlotSelection : Current slot number selected by human player
 ******************************************************************************/

short Board::siGet_SlotSelection()
{
    return siSlotSelection;
}


/******************************************************************************
 *  @function   vSet_WinTokens
 *
 *  @brief      Sets number of tokens to win (token chain length)
 *
 *  @param      vSet_WinTokens : Number of tokens to win
 *  @return     -
 ******************************************************************************/

void Board::vSet_WinTokens (short _siWinTokens)
{
    siWinTokens = _siWinTokens;
}


/******************************************************************************
 *  @function   vSet_BoardSize
 *
 *  @brief      Sets game board size / dimension.
 *
 *  @param      _aBoardSize : Game board size as list of {slots, lines)
 *  @return     -
 ******************************************************************************/

void Board::vSet_BoardSize (BOARD _aBoardSize)
{
    tBoardSize.slot = _aBoardSize.slot;
    tBoardSize.line = _aBoardSize.line;

    siWinTokens_Max = std::min (tBoardSize.slot, tBoardSize.line);

    // Set maximum number of tokens to win,
    // based of shortest game board side length
    if (siWinTokens_Max < siWinTokens)  siWinTokens = siWinTokens_Max;

    vInit_Board (tBoardSize);   // Recreate game board with new dimensions
}


/******************************************************************************
 *  @function   vSet_Field
 *
 *  @brief      Sets game board flied value.
 *
 *  @param      _aFieldPos : Coordinate of field element as list {slot, line}
 *              val        : Field value that has to be set
 *  @return     -
 ******************************************************************************/

void Board::vSet_Field (BOARD _aFieldPos, short val)
{
    vecBoard[_aFieldPos.slot][_aFieldPos.line] = val;
}


/******************************************************************************
 *  @function   vSet_SlotSelection
 *
 *  @brief      Sets the current slot selected by human player
 *
 *  @param      _siSlotSelection : Slot number selected by human player
 *  @return     -
 ******************************************************************************/

void Board::vSet_SlotSelection (short _siSlotSelection)
{
    siSlotSelection = _siSlotSelection;
}


/******************************************************************************
 *  @function   vInit_Board
 *
 *  @brief      Recreate game board 2D vector with new dimensions
 *
 *  @param      _BoardSize : Game board dimension as list {slots, lines}
 *  @return     -
 *  @note       Deletion of vector elements will be done by resize(0)
 *              function instead of clear() function.
 *              At program start an empty vector (without elements) will
 *              be declared. Usage of clear() function on an empty vector
 *              leads to an exception.
 ******************************************************************************/

void Board::vInit_Board (BOARD _BoardSize)
{
    // Delete all vector elements by resize to zero (better than clear() method)
    vecBoard.resize(0);

    // Initialize board with new dimension and zero values
    vecBoard.resize(_BoardSize.slot, std::vector<short>(_BoardSize.line, 0));
}


/******************************************************************************
 *  @function   vClear_Board
 *
 *  @brief      Initiates game board 2D vector elements with zero value
 *
 *  @param      -
 *  @return     -
 ******************************************************************************/

void Board::vClear_Board()
{
    std::vector< std::vector<short> >::iterator slot;   // Iterator for outer vector
    std::vector< short              >::iterator line;   // Iterator for inner vector

    // Reset game board 2D vector to zero
    for (slot = vecBoard.begin(); slot != vecBoard.end(); slot++)
    {
        for (line = slot->begin(); line != slot->end(); line++)  *line = 0;
    }
}


/******************************************************************************
 *  @function   vDraw_Board
 *
 *  @brief      Prints game board
 *
 *  @param      -
 *  @return     -
 ******************************************************************************/

void Board::vDraw_Board()
{
    std::string sBoard_TopLine, sBoard_MidLine, sBoard_BotLine;


    /******************************************************************
    *   Create game board sketch
    *******************************************************************/
    // Left border
    sBoard_TopLine  = std::string(1,' ') + ' ' + char(218);
    sBoard_MidLine  = std::string(1,' ') + ' ' + char(195);
    sBoard_BotLine  = std::string(1,' ') + ' ' + char(192);

    // Lines between top and bottom lines
    for (int i=1; i < tBoardSize.slot; i++)
    {
        sBoard_TopLine  +=  std::string(1,char(196)) + char(196) + char(194); // Line at top
        sBoard_MidLine  +=  std::string(1,char(196)) + char(196) + char(197); // Lines between fields (horizontal)
        sBoard_BotLine  +=  std::string(1,char(196)) + char(196) + char(193); // Line at bottom
    }

    // Right border
    sBoard_TopLine  +=  std::string(1,char(196)) + char(196) + char(191);
    sBoard_MidLine  +=  std::string(1,char(196)) + char(196) + char(180);
    sBoard_BotLine  +=  std::string(1,char(196)) + char(196) + char(217);


    /******************************************************************
    *   Print game board sketch
    *******************************************************************/
    // Draw Game board topline
    std::cout << sBoard_TopLine  << std::endl;

    // Draw Game board lines between top and bottom
    for (short line=0; line < tBoardSize.line; line++)
    {
        line+1 < 10 ? std::cout << ' ' << line+1 : std::cout << line+1 ;

        std::cout << char(179);

        for (short slot=0; slot < tBoardSize.slot; slot++)
        {
            std::cout << "  "; std::cout << char(179);
        }
        std::cout << std::endl;

        if (line < tBoardSize.line-1)   {std::cout << sBoard_MidLine << std::endl;}
    }

    // Draw game board bottomline
    std::cout << sBoard_BotLine << std::endl;

    // Print game board slot and line numbering
    std::cout << "   ";
    for (int i=1; i <= tBoardSize.slot; i++)  i < 10 ? std::cout << i << "  " : std::cout << i << " " ;
    std::cout << std::endl << std::endl;
}


/******************************************************************************
 *  @function   vShow_SlotSelect
 *
 *  @brief      Prints slot selection line
 *
 *  @param      slot  : Slot number where token has to be shown above slot
 *              color : Token color
 *  @return     -
 ******************************************************************************/

void Board::vShow_SlotSelect (short slot, short color)
{
    // If no slot selection just clear the slot selection line
    if (slot == 0) {std::cout << "                         "
                                 "                         " <<
                    std::endl; return;}

    // Save current color and clear token
    vColor_Save(); std::cout << "  ";

    // Print token above slot with user depending color
    for (int i=1; i <= tBoardSize.slot; i++)
    {
        std::cout << " ";

        if (i == slot) {vColor_Set (color);  std::cout << "  ";}

        vColor_Restore();  std::cout << "  ";
    }
    std::cout << std::endl;
}


/******************************************************************************
 *  @function   vSlotSelect_LShift
 *
 *  @brief      Move token in slot selection one slot to the left. If last
 *              slot is reached token will be rolled over to first slot.
 *  @param      -
 ******************************************************************************/

void Board::vSlotSelect_LShift()
{
    siSlotSelection <= 1 ? siSlotSelection = tBoardSize.slot : siSlotSelection--;
}


/******************************************************************************
 *  @function   vSlotSelect_RShift
 *
 *  @brief      Move token in slot selection one slot to the right. If first
 *              slot is reached token will be rolled over to last slot.
 *  @param      -
 ******************************************************************************/

void Board::vSlotSelect_RShift()
{
    siSlotSelection >= tBoardSize.slot  ?  siSlotSelection = 1 : siSlotSelection++;
}


/******************************************************************************
 *  @function   bInsert_Token
 *
 *  @brief      Set field element of game board 2D vector with player ID
 *              value in next free line of selected slot.
 *
 *  @param      player_id : ID value for which player the token has to be set.
 *  @return     bool      : true   if token insert successful
 *                        : false  if slot is full of tokens
 ******************************************************************************/

bool Board::bInsert_Token (short player_id, short slot)
{
    slot--;   // Remap slot number to vector index count

    // Search within slot for next free line from bottom to top
    for (short line = tBoardSize.line - 1; line >= 0; line--)
    {
        if   (siGet_Field ({slot, line}) == FIELDVAL_EMPTY)
        {
              vSet_Field ({slot, line}, player_id);  return true;
        }
    }
    return false;
}


/******************************************************************************
 *  @function   vAnimate_TokenDrop
 *
 *  @brief      Animates a falling token within a slot.
 *
 *  @param      player_id : ID value for which player the falling
 *                          token has to be animated.
 *  @return     -
 ******************************************************************************/

void Board::vAnimate_TokenDrop (short player_id, short slot)
{
    short color;
    char  board_line = char(196);

    vCursor_Visible (false);        // Hide cursor

    slot--;                         // Remap slot number to vector index count

    // Set token color depending on player
    if   (player_id == PLAYER_1_ID) color = COL_YELLOW;
    else                            color = COL_RED;

    vCursor_Move (3, 0);            // Place cursor with X-offset above first slot
    vCursor_Move (slot * 3, -1);    // Move cursor to above selected slot

    // Animated token fall
    for (short line = 0; line < tBoardSize.line; line++)
    {
        vCursor_Move ( 0, +1); vColor_Set(color); std::cout << "  ";       Sleep(14);
        vCursor_Move (-2, -1); vColor_Restore();  std::cout << "  ";       Sleep(22);
        vCursor_Move (-2, +2); vColor_Set(color); std::cout << "  ";       Sleep(14);
        vCursor_Move (-2, -1); vColor_Restore();  std::cout << board_line
                                                            << board_line; Sleep(22);
        vCursor_Move (-2, +1);

        if (siGet_Field ({slot, line}) != FIELDVAL_EMPTY) break;
    }
    vColor_Restore();               // Restore console color
}


/******************************************************************************
 *  @function   siCheck_WinState
 *
 *  @brief      Searches for token chain in game board 2D vector which
 *              reached the length of token to win.
 *
 *  @param      -
 *  @return     WON_HUMAN || WON_MACHINE : ID of player that won the game
 *              Zero if no player won, means no token chain had the winning length
 ******************************************************************************/

short Board::siCheck_WinState()
{
    short fieldval;
    short siTokenCnt_H, siTokenCnt_M;

    /******************************************************************
    *   Check horizontal lines
    *******************************************************************/
    for (short line=0; line < tBoardSize.line; line++)
    {
        siTokenCnt_H = 0; siTokenCnt_M = 0;     // Reset token counter

        for (short slot=0; slot < tBoardSize.slot; slot++)
        {
            fieldval = siGet_Field ({slot, line});

            // Detect a gap in token chain and reset token counter
            if (fieldval != FIELDVAL_HUMAN   && siTokenCnt_H > 0) siTokenCnt_H = 0;
            if (fieldval != FIELDVAL_MACHINE && siTokenCnt_M > 0) siTokenCnt_M = 0;

            // Increase token counter if token detected
            if (fieldval == FIELDVAL_HUMAN)   siTokenCnt_H++;
            if (fieldval == FIELDVAL_MACHINE) siTokenCnt_M++;

            // Check token chain length and return winner
            if (siTokenCnt_H == siWinTokens)  return WON_HUMAN;
            if (siTokenCnt_M == siWinTokens)  return WON_MACHINE;
        }
    }

    /******************************************************************
    *   Check vertical lines
    *******************************************************************/
    for (short slot=0; slot < tBoardSize.slot; slot++)
    {
        siTokenCnt_H = 0; siTokenCnt_M = 0;     // Reset token counter

        for (short line=0; line < tBoardSize.line; line++)
        {
            fieldval = siGet_Field ({slot, line});

            // Detect a gap in token chain and reset token counter
            if (fieldval != FIELDVAL_HUMAN   && siTokenCnt_H > 0) siTokenCnt_H = 0;
            if (fieldval != FIELDVAL_MACHINE && siTokenCnt_M > 0) siTokenCnt_M = 0;

            // Increase token counter if token detected
            if (fieldval == FIELDVAL_HUMAN)   siTokenCnt_H++;
            if (fieldval == FIELDVAL_MACHINE) siTokenCnt_M++;

            // Check token chain length and return winner
            if (siTokenCnt_H == siWinTokens)  return WON_HUMAN;
            if (siTokenCnt_M == siWinTokens)  return WON_MACHINE;
      }
    }

    /******************************************************************
    *   Check diagonal lines  (bottom left -> top right)
    *******************************************************************/
    short lines        = tBoardSize.slot + tBoardSize.line - 1;
    short x_startfield = 0;
    short y_startfield = tBoardSize.line - 1;
    short slot, line;

    for (int line_cnt=1; line_cnt <= lines; line_cnt++)
    {
        siTokenCnt_H = 0; siTokenCnt_M = 0;             // Reset token counter
        slot = x_startfield;  line = y_startfield;      // Set start coordinate of first diagonal line

        while (slot >= 0  &&  slot < tBoardSize.slot  &&
               line >= 0  &&  line < tBoardSize.line)
        {
            fieldval = siGet_Field ({slot, line});

            // Detect a gap in token chain and reset token counter
            if (fieldval != FIELDVAL_HUMAN   && siTokenCnt_H > 0) siTokenCnt_H = 0;
            if (fieldval != FIELDVAL_MACHINE && siTokenCnt_M > 0) siTokenCnt_M = 0;

            // Increase token counter if token detected
            if (fieldval == FIELDVAL_HUMAN)   siTokenCnt_H++;
            if (fieldval == FIELDVAL_MACHINE) siTokenCnt_M++;

            // Check token chain length and return winner
            if (siTokenCnt_H == siWinTokens)  return WON_HUMAN;
            if (siTokenCnt_M == siWinTokens)  return WON_MACHINE;

            slot++; line++;   // Increase to next field
        }
        // Set start coordinate of next diagonal line
        y_startfield > 0 ? y_startfield-- : x_startfield++;
    }

    /******************************************************************
    *   Check diagonal lines  (top left -> bottom right)
    *******************************************************************/
    // Set start coordinate of first diagonal line
    x_startfield = 0;  y_startfield = 0;

    for (int line_cnt=1; line_cnt <= lines; line_cnt++)
    {
        siTokenCnt_H = 0; siTokenCnt_M = 0;             // Reset token counter
        slot = x_startfield;  line = y_startfield;      // Set start coordinate of first diagonal line

        while (slot >= 0  &&  slot < tBoardSize.slot  &&
               line >= 0  &&  line < tBoardSize.line)
        {
            fieldval = siGet_Field ({slot, line});

            // Detect a gap in token chain and reset token counter
            if (fieldval != FIELDVAL_HUMAN   && siTokenCnt_H > 0) siTokenCnt_H = 0;
            if (fieldval != FIELDVAL_MACHINE && siTokenCnt_M > 0) siTokenCnt_M = 0;

            // Increase token counter if token detected
            if (fieldval == FIELDVAL_HUMAN)   siTokenCnt_H++;
            if (fieldval == FIELDVAL_MACHINE) siTokenCnt_M++;

            // Check token chain length and return winner
            if (siTokenCnt_H == siWinTokens)  return WON_HUMAN;
            if (siTokenCnt_M == siWinTokens)  return WON_MACHINE;

            slot--; line++;   // Increase to next field
        }
        // Set start coordinate of next diagonal line
        x_startfield < tBoardSize.slot - 1 ? x_startfield++ : y_startfield++;
    }

    return 0;
}

