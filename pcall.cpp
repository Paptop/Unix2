#include "pcall.h"

#include <stdio.h>

#define DEBUG 0  

PCall::PCall()
{
  m_paths.insert({"ls",   "/bin/ls"});
  m_paths.insert({"cat",  "/bin/cat"});
  m_paths.insert({"sh",   "/bin/sh"});
  m_paths.insert({"echo", "/bin/echo"});
  m_paths.insert({"grep", "/bin/grep"});
  m_paths.insert({"ps",   "/bin/ps"});
  m_paths.insert({"pwd",  "/bin/pwd"});
  m_paths.insert({"sleep","/bin/sleep"});
  m_paths.insert({"cd",   "cd"});
  m_paths.insert({"wc",   "/usr/bin/wc"});
  m_paths.insert({"sort", "/usr/bin/sort"});
  m_paths.insert({"vim",  "/usr/bin/vim"});
  m_paths.insert({"less",  "/usr/bin/less"});
  m_paths.insert({"tail",  "/usr/bin/less"});
  m_paths.insert({"head",  "/usr/bin/head"});
}

PCall::~PCall()
{
}

PCall::Tokens& PCall::GetTopCommand()
{
  return (*m_commands.begin()); 
}

PCall::Tokens& PCall::GetTailCommand()
{
  return (*std::next(m_commands.begin(),1)); 
}

void PCall::PopTopCommand()
{
  m_commands.pop_front(); 
}

void PCall::ParseInput(std::string& str)
{
  m_commands.clear();
  char* input = strdup(str.c_str());
  char* token = nullptr;
  
  std::vector<std::string> command;
  while( (token = strsep(&input," ")) != NULL)
  {
      if(strcmp(token,"|") == 0)
      {
        if(command.size() > 0 )
        {
            m_commands.push_back(command);
        }
        command.clear();
      }
      else
      {
        command.push_back(token);
      }
  }

  if(command.size() > 0)
  {
    m_commands.push_back(command);
  }

#if DEBUG
  int Commands = 0;
  for(std::vector<std::string>& vec : m_commands)
  {
    for(int i = 0; i < (int)vec.size() ; ++i)
    {
        std::cout << "Command "<< Commands <<  " Token " << vec[i] << std::endl;
    }
    
    Commands++;
  }
#endif

  if(m_commands.size() == 0)
  {
    return;
  }

  LoopPipe();
}

int PCall::CreateArguments(Tokens& topCommand, char **arg)
{
#if DEBUG
    static int call = 0;
    call++;
    for(std::string& tokens : topCommand)
    {
        std::cout << "Arguments for command : " << tokens << " call : " << call <<  std::endl;
    }
#endif
  auto iter = m_paths.find(topCommand[0]);
  if(iter == m_paths.end())
  {
      std::cout << "  No such command " << std::endl;
      return -1;
  }

  const char* path = iter->second.c_str();
  topCommand[0] = strdup(path);

  for(int i = 0 ; i < (int)topCommand.size(); ++i)
  {
     arg[i] = strdup(topCommand[i].c_str());
  }

  arg[topCommand.size()] = NULL;

  return 0;
}

void PCall::RunProc()
{
}

void PCall::LoopPipe()
{
  int p[2];
  pid_t pid;
  int fd_in = 0;

  while(m_commands.size() > 0)
  {
      pipe(p);
      
      Tokens& topCommand = GetTopCommand(); 
      char* arg[topCommand.size() + 1]; // +1 for NULL
      int id0 = CreateArguments(topCommand, arg);
      if(id0 < 0)
      {
        break;
      }

      if( (pid = fork()) == -1)
      {
          exit(EXIT_FAILURE);
      } 
      else if (pid == 0)
      {
          dup2(fd_in, 0);
          if(Peek())
          {
            dup2(p[1], 1);
          }
          close(p[0]);
          execv(arg[0], arg);
          exit(EXIT_FAILURE);
      }
      else
      {
          wait(NULL);
          close(p[1]);
          fd_in = p[0];
          PopTopCommand();
      }
  }

}


bool PCall::Peek()
{
  if (std::next(m_commands.begin(),1) == m_commands.end() )
  {
      return false;
  } 
  else
  {
      return true;
  }
}

void PCall::Cd()
{
  Tokens& topCommand = GetTopCommand();

  if(topCommand.size() < 1 || topCommand.size() > 2)
  {
     return;
  }
  
  int value = chdir(topCommand[1].c_str());
  
  if(value < 0)
  {
    std::cout << "ijsh $ No such directory" << std::endl;
  }
}


