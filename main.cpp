#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include "pcall.h"

int main()
{
  PCall prcall;
  std::string input;

  std::cout << "ijsh $ ";

  while(std::getline(std::cin,input))
  {

    if(input.size() > 0)
    {
      prcall.ParseInput(input);
    }

    std::cout << "ijsh $ ";
  }


  return 0;
}
