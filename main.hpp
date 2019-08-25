/******************************************************************************
 *
 *  @project Connect Four
 *
 *  @file    main.hpp
 *
 *  @date    2019-08-23
 *
 *  @author  Arthur Ackermann
 *
 *  @brief   Main module header
 *
 ******************************************************************************/

/*=============================================================================
=====                         SET OWN MODULE ID                           =====
=============================================================================*/

#ifndef _MAIN_H_
#define _MAIN_H_

/*=============================================================================
=====                              INCLUDES                               =====
=============================================================================*/

/*------  Module header includes  -------*/
#include "Game.hpp"

/*=============================================================================
=====                           MACROS / INLINES                          =====
=============================================================================*/

/***  Program version  ***/
#define  VERSION  "v0.1"

/***  Debug info for constructor/destructor calls  ***/
//#define DEBUG

#ifdef  DEBUG
        #define DEBUG_CONSTRUCTOR std::cout << "-> Constructor:  " << __PRETTY_FUNCTION__ << "\n"
        #define DEBUG_DESTRUCTOR  std::cout << "-> Constructor:  " << __PRETTY_FUNCTION__ << "\n"
#else
        #define DEBUG_CONSTRUCTOR
        #define DEBUG_DESTRUCTOR
#endif // DEBUG


/***  Halts program and prints "request for key  ***/
/***  press to continue" to first line           ***/
#define PAUSE  {COORD curpos_tmp;   \
                curpos_tmp = tCurPos_Get(); \
                vCurPos_Set({0, 0});  system("PAUSE"); \
                vCurPos_Set({0, 0});  std::cout << "                                              "; \
                vCurPos_Set(curpos_tmp);}


#endif // _MAIN_H_
