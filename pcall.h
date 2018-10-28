#pragma once

#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <list>

class PCall
{
public:
    PCall();
    ~PCall();
    void ParseInput(std::string& str); 

private:

public:
    typedef std::list<std::vector<std::string> > Commands;
    typedef std::vector<std::string>               Tokens;

    void RunProc();
    void LoopPipe();
    void ParseCommands(std::string& input);

    void Cd();

    Tokens& GetTailCommand();
    Tokens& GetTopCommand();
    void    PopTopCommand();
    bool Peek();

    int CreateArguments(Tokens& tokens, char **arg);


private:
    std::map<std::string, std::string> m_paths;
    Commands                           m_commands;
};
