/******************************************************************************
 *
 *  @project Connect Four
 *
 *  @file    Player.hpp
 *
 *  @date    2019-08-23
 *
 *  @author  Arthur Ackermann
 *
 *  @class   Player
 *  @class   RandomNr : Nested class within class Player
 *
 ******************************************************************************/

/*=============================================================================
=====                         SET OWN MODULE ID                           =====
=============================================================================*/

#ifndef _PLAYER_H_
#define _PLAYER_H_

/*=============================================================================
=====                              INCLUDES                               =====
=============================================================================*/

/*------  System interface includes  -------*/
#include <iostream>
#include <time.h>       // time(NULL)

/*=============================================================================
=====                           MACROS / INLINES                          =====
=============================================================================*/

/***  Player IDs  ***/
#define PLAYER_1_ID     1
#define PLAYER_2_ID     2

/*=============================================================================
=====                               CLASSES                               =====
=============================================================================*/

class Player
{
    public:
    /** Variables **/
        //TODO: Schauen, warum bCurrentPlayer nicht protected geht
        bool bCurrentPlayer;

    /** Constructor / Destructor **/
                 Player ();
                 Player (short player_id, bool start_player);
        virtual ~Player ();

    /** Getter / Setter **/
        virtual void vSet_CurrentPlayer (bool _bCurrentPlayer);
        virtual bool bIs_CurrentPlayer  ();

    /** Nested class **/
        class RandomNr
        {
            public:
            /** Constructor / Destructor **/
                RandomNr();
                virtual ~RandomNr();

            /** Member functions / methods **/
                virtual int iRndNum (int minval, int maxval);

            protected:
            private:
        };

    protected:
    /** Objects **/
        RandomNr  oRandomNr;

    private:
};

#endif // _PLAYER_H_
