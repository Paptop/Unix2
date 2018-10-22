#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <unistd.h>
#include "pcall.h"

int main()
{
  PCall prcall;
  char currentDir[256]; 
  std::string input;

  getcwd(currentDir,sizeof(currentDir));
  std::cout << "ijsh: ";

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

  while(std::getline(std::cin,input))
  {

    if(input.size() > 0)
    {
      prcall.ParseInput(input);
    }

    std::cout << "ijsh: ";

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


  return 0;
}
