#include "mind.h"
#include "GORCHAN.h"
mind::mind()
{

}

mind::~mind()
{

}

void get_mind(mind** lvalue)
{
    *lvalue = new GORCHAN();
}