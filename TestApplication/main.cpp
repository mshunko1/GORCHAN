#include <iostream>
#include "../GORCHAN/mind.h"

int main()
{
    std::cout<<"Waiting debbuger";
    int i = 0;
    std::cin>>i;
    mind* my_mind = nullptr;
	get_mind(&my_mind);
    
    std::cout<<"Waiting percive";
     std::cin>>i;
    my_mind->percive("Misha kuda ti speshish u tebya vagon vremeni");
}