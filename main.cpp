#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <unistd.h>
#include "pcall.h"

void PrintPathHead()
{
  char currentDir[256]; 

  if(getcwd(currentDir,sizeof(currentDir)))
  {
    std::string topFolder;
    for(int i = strlen(currentDir) ; i >= 0; i--)
    { 
       topFolder.append(1,currentDir[i]); 
       if(currentDir[i] == '/')
       {
          break;
       }
    }
    std::reverse(topFolder.begin(),topFolder.end());
    std::cout << "\033[1;31m" << topFolder << "\033[0m";
    std::cout << " $ ";
  }

}

int main()
{
  PCall prcall;
  std::string input;

  std::cout << "ijsh: ";
  PrintPathHead();

  while(std::getline(std::cin,input))
  {

    if(input.size() > 0)
    {
      prcall.ParseInput(input);
    }

    std::cout << "ijsh: ";
    PrintPathHead();
  }


  return 0;
}
