/******************************************************************************
 *
 *  @project Connect Four
 *
 *  @file    Player.cpp
 *
 *  @date    2019-08-23
 *
 *  @author  Arthur Ackermann
 *
 *  @brief   Player interface
 *           Provides functionalities to handle a player.
 *
 ******************************************************************************/

/*=============================================================================
=====                              INCLUDES                               =====
=============================================================================*/

/*------  Module includes  -------*/
#include "main.hpp"
#include "Player.hpp"

/*=============================================================================
=====                         FUNCTIONS / METHODS                         =====
=============================================================================*/

/******************************************************************************
 *  @function   Constructor of class Player
 *
 *  @brief      Instantiates a player object
 *  @param      -
 ******************************************************************************/

Player::Player()
{
    DEBUG_CONSTRUCTOR;
}

/******************************************************************************
 *  @function   Overloaded Constructor of class Player
 *
 *  @brief      * Instantiates a Player object
 *              * Sets initial values
 *
 *  @param      player_id    : ID of this player
 *              start_player : true if this player of the game; false if not
 ******************************************************************************/

Player::Player (short player_id, bool start_player)
{
    DEBUG_CONSTRUCTOR;

    vSet_CurrentPlayer(start_player);
}

/******************************************************************************
 *  @function   Destructor of class Player
 *
 *  @brief      Destroys this Player object
 ******************************************************************************/

Player::~Player()
{
    DEBUG_DESTRUCTOR;
}


/******************************************************************************
 *  @function   vSet_CurrentPlayer
 *
 *  @brief      Sets or clears player status as current player
 *
 *  @param      _bCurrentPlayer : true || false
 *  @return     -
 ******************************************************************************/

void Player::vSet_CurrentPlayer(bool _bCurrentPlayer)
{
    bCurrentPlayer = _bCurrentPlayer;
}


/******************************************************************************
 *  @function   bIs_CurrentPlayer
 *
 *  @brief      Returns information about player is current player or not
 *  @param      -
 *  @return     bCurrentPlayer : true   if player is current player during game
 *                               false  if player is not the current player
 ******************************************************************************/

bool Player::bIs_CurrentPlayer()
{
    return bCurrentPlayer;
}


/******************************************************************************
 *  @function   Constructor of nested class RandomNr
 *
 *  @brief      * Instantiates a RandomNr object
 *  @param      -
 ******************************************************************************/

Player::RandomNr::RandomNr ()
{
    DEBUG_CONSTRUCTOR;
}


/******************************************************************************
 *  @function   Destructor of nested class RandomNr
 *
 *  @brief      Destroys this RandomNr object
 ******************************************************************************/

Player::RandomNr::~RandomNr ()
{
    DEBUG_DESTRUCTOR;
}


/******************************************************************************
 *  @function   iRndNum
 *
 *  @brief      Generates a time based random number
 *
 *  @param      minval : Minimum value of generated random number
 *              maxval : Maximum value of generated random number
 *  @return     Integer random number within a range of minval...maxval
 ******************************************************************************/

int Player::RandomNr::iRndNum (int minval, int maxval)
{
    int rndval = 0;

    srand (time(NULL));
    rndval = rand();

    // Return ranged random value
    return rndval % maxval + minval;    // Value range: minval ... maxval
}
