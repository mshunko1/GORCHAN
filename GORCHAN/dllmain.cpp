// dllmain.cpp : Defines the entry point for the DLL application.


#ifndef LIB1_H_INCLUDED
#define LIB1_H_INCLUDED

#include "mind.h"
#include <iostream>

int main()
{
   std::cout<<"Hi to all"<<std::endl;

   mind* _mind = nullptr;
   get_mind(&_mind);
   _mind->init();
   _mind->percive("a = a");
   return 1;
}




#endif /* LIB1_H_INCLUDED */