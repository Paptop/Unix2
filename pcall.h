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

    void LoopPipe();
    void ParseCommands(std::string& input);
    void Cd();

    Tokens& GetTopCommand();
    Tokens& GetTailCommand();
    void    PopTopCommand();
    void    PopTailCommand();
    bool Peek();
    bool Peek(std::string value);

    int CreateArguments(Tokens& tokens, char **arg);


private:
    std::map<std::string, std::string> m_paths;
    Commands                           m_commands;
};
