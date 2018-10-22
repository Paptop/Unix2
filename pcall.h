#pragma once

#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <map>

class PCall
{
public:

  enum PC 
  {
    LS = 0,
    CD,
    CAT,
    BASH,
    SH,
    SORT,
    GREP,
    PS,
    VIM,
    PWD,
    COUNT
  };

public:
    PCall();
    ~PCall();
    void ParseInput(std::string& str); 

private:
    typedef std::vector<std::string> Tokens;

    void CallProcess(Tokens& tokens);

    void Ls(Tokens& tokens);
    void Cd(Tokens& tokens);
    void Cat(Tokens& tokens);
    void Vim(Tokens& tokens);
    void Ps(Tokens& tokens);
    void Grep(Tokens& tokens);
    void Pwd(Tokens& tokens);

private:
    std::map<std::string, PC> m_commands;
};
