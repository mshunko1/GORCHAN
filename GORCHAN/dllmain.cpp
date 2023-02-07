// dllmain.cpp : Defines the entry point for the DLL application.


#ifndef LIB1_H_INCLUDED
#define LIB1_H_INCLUDED

#include "mind.h"
#include <iostream>
#include <thread>
int main()
{
   std::cout<<"Hi to all"<<std::endl;

   mind* _mind = nullptr;
   get_mind(&_mind);
   _mind->init();
   _mind->percive("a = a");
   std::this_thread::sleep_for(std::chrono::milliseconds(3000));
   _mind->percive("b = b");
   std::this_thread::sleep_for(std::chrono::milliseconds(3000));
   _mind->percive("c = c");
   std::this_thread::sleep_for(std::chrono::milliseconds(3000));
   _mind->percive("a = b");
   std::this_thread::sleep_for(std::chrono::milliseconds(3000));
   _mind->percive("b = c");


   std::this_thread::sleep_for(std::chrono::minutes(1000000000000));
   return 1;
}




#endif /* LIB1_H_INCLUDED */