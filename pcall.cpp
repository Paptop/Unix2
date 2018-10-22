#include "pcall.h"

#define DEBUG 0 

PCall::PCall()
{
  m_commands.insert({"ls",   PC::LS});
  m_commands.insert({"cat",  PC::CAT});
  m_commands.insert({"cd",   PC::CD});
  m_commands.insert({"sh",   PC::SH});
  m_commands.insert({"sort", PC::SORT});
  m_commands.insert({"grep", PC::GREP});
  m_commands.insert({"ps",   PC::PS});
  m_commands.insert({"vim",  PC::VIM});
  m_commands.insert({"pwd",  PC::PWD});
}

PCall::~PCall()
{
}


void PCall::ParseInput(std::string& str)
{
  Tokens tokens;
  char* input = strdup(str.c_str());
  char* token = nullptr;
  
  while( (token = strsep(&input," ")) != NULL)
  {
      tokens.push_back(token);
  }

#if DEBUG
  for(std::string& token : tokens)
  {
    std::cout <<"Tokens : " <<  token << " Str size : " << str.size() <<  std::endl;
  }
#endif
  CallProcess(tokens);
}

void PCall::CallProcess(Tokens& tokens)
{
  auto iter = m_commands.find(tokens[0]);  
  if(iter == m_commands.end())
  {
    std::cout << " No such command" << std::endl;
    return;
  }

  switch((*iter).second)
  {
    case PC::LS:
      {
        Ls(tokens);
      }
      break;
    case PC::CAT:
      {
        Cat(tokens);
      }
      break;
    case PC::CD:
      {
        Cd(tokens);
      }
      break;
    case PC::PS:
      {
        Ps(tokens);
      }
      break;
    case PC::VIM:
      {
        Vim(tokens);
      }
      break;
    case PC::GREP:
      {
        Grep(tokens);
      }
      break;
    case PC::PWD:
      {
        Pwd(tokens);
      }
      break;
    default:
      std::cout << " Command not implemented " << std::endl;
  }
}

void PCall::Ls(Tokens& tokens)
{
  const char* path = "/bin/ls"; 
  tokens[0] = "/bin/ls";

  int status;
  char* arg[tokens.size() + 1]; // +1 for NULL

  for(int i = 0 ; i < (int)tokens.size(); ++i)
  {
     arg[i] = strdup(tokens[i].c_str());
  }
  
  arg[tokens.size()] = NULL;

  if( fork() == 0)
  {
    execv(path, arg);
  }
  else
  {
    wait(&status);
  }
}

void PCall::Cat(Tokens& tokens)
{
  const char* path = "/bin/cat"; 
  tokens[0] = "/bin/cat";

  int status;
  char* arg[tokens.size() + 1]; // +1 for NULL

  for(int i = 0 ; i < (int)tokens.size(); ++i)
  {
     arg[i] = strdup(tokens[i].c_str());
  }
  
  arg[tokens.size()] = NULL;

  if( fork() == 0)
  {
    execv(path, arg);
  }
  else
  {
    wait(&status);
  }
}

void PCall::Ps(Tokens& tokens)
{
  const char* path = "/bin/ps"; 
  tokens[0] = "/bin/ps";

  int status;
  char* arg[tokens.size() + 1]; // +1 for NULL

  for(int i = 0 ; i < (int)tokens.size(); ++i)
  {
     arg[i] = strdup(tokens[i].c_str());
  }
  
  arg[tokens.size()] = NULL;

  if( fork() == 0)
  {
    execv(path, arg);
  }
  else
  {
    wait(&status);
  }
}

void PCall::Vim(Tokens& tokens)
{
  int status;
  const char* path = "/usr/bin/vim"; 
  tokens[0] = "/usr/bin/vim";

  char* arg[tokens.size() + 1]; // +1 for NULL

  for(int i = 0 ; i < (int)tokens.size(); ++i)
  {
     arg[i] = strdup(tokens[i].c_str());
  }
  
  arg[tokens.size()] = NULL;

  if( fork() == 0)
  {
    execv(path, arg);
  }
  else
  {
    wait(&status);
  }
}

void PCall::Grep(Tokens& tokens)
{
  int status;
  const char* path = "/bin/grep"; 
  tokens[0] = "/bin/grep";

  char* arg[tokens.size() + 1]; // +1 for NULL

  for(int i = 0 ; i < (int)tokens.size(); ++i)
  {
     arg[i] = strdup(tokens[i].c_str());
  }
  
  arg[tokens.size()] = NULL;

  if( fork() == 0)
  {
    execv(path, arg);
  }
  else
  {
    wait(&status);
  }
}

void PCall::Cd(Tokens& tokens)
{
  if(tokens.size() > 2 || tokens.size() < 1)
  {
    return;
  }

  int value = chdir(tokens[1].c_str());
  
  if(value < 0)
  {
    std::cout << "ijsh $ No such directory" << std::endl;
  }
}

void PCall::Pwd(Tokens& tokens)
{
  int status;
  const char* path = "/bin/pwd"; 
  tokens[0] = "/bin/pwd";

  char* arg[tokens.size() + 1]; // +1 for NULL

  for(int i = 0 ; i < (int)tokens.size(); ++i)
  {
     arg[i] = strdup(tokens[i].c_str());
  }
  
  arg[tokens.size()] = NULL;

  if( fork() == 0)
  {
    execv(path, arg);
  }
  else
  {
    wait(&status);
  }
}



