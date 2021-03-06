#include "supervision.h"
#include "logger.h"
#include "../consts/threads.h"
#include "lib/database/database_factory.h"
#include "consts/databases.h"

#include <thread>
#include <chrono>
#include <iostream>
#include <unordered_map>

std::vector<Callback> Supervision::queue;

Supervision::Supervision()
{
  m_stop = false;
}

Supervision::~Supervision()
{

}

void Supervision::init()
{
  if(! this->loadConfiguration())
  {
    return;
  }
}

bool Supervision::loadConfiguration()
{
  if(m_conf.compare("") != 0)
  { 
    Configuration conf(m_conf);
    
    if(! conf.loadConfiguration(statistics))
    {
      errn << "Configuration load failed " << m_conf;
      return false;
    }
  }
  else
  {
    info << "Configuration is empty, please consider it";
  }
  
  return this->supervise();
}

bool Supervision::openDatabaseConnection()
{
  std::unordered_map<std::string, std::string> settings;
  
  settings.insert({SQLITE_DATABASE_PATH_ATTR, "TempController.sqlite3"});
  
  DatabaseFactory factory = DatabaseFactory::getInstance();
  // Temporary workaround ...
  factory.loadSettings(settings);
  
  return true;
}

void Supervision::setConfigurationFile(const std::string& conf)
{
  m_conf = conf;
}

bool Supervision::enqueueNewThread(const Callback &callback)
{
  queue.push_back(callback);
  return true;
}

bool Supervision::startInThread(const Callback& callback)
{
  std::thread *th = new std::thread(&Supervision::execute, this, callback);
  th->detach();
  
  startedThreads.push_back(th);
  
  return true;
}

void Supervision::stop(const string& verbose)
{
  this->m_stopReason = verbose;
  this->m_stop = true;
}

bool Supervision::supervise()
{
  info << "Configuration loaded from file: " << m_conf;
  info << "Go to supervise state";
  
  // Start collecting statistics 
  // 	will create some new threads etc
  statistics.startStatsColl();
  
  while(!m_stop)
  {    
    while(! queue.empty())
    {
      this->startInThread(queue.back());
      queue.pop_back();
    }
    
    std::this_thread::sleep_for(std::chrono::milliseconds(SUPERVISE_PERIOD_CHECK_MS));
  }
  
  warn << "Exiting application - will try to stop";
  
  statistics.stopStatsColl();
  this->waitForThreads();
  
  if(m_stop)
  {
    info << "Intentional stop, bye";
    info << "Stop reason: " <<  this->m_stopReason;
    return true; 
  }
  else
  {
    errn << "Some other type of stop, most probably failed";
    return false;
  }  
}

void Supervision::waitForThreads()
{
  vector<std::thread *>::iterator iterator;
  std::thread *runn;
  bool threadRunning = true;
  int stopCounter = 0;
  
  dbg << "Wait for threads to stop";
  
  while(threadRunning && 
    stopCounter < THREADS_CYCLES_WHILE_WAIT_TO_END)
  {
    threadRunning = false;
    
    //for(iterator = this->startedThreads.begin(); iterator != this->startedThreads.end(); iterator++)
    iterator = this->startedThreads.begin();
    while(iterator != this->startedThreads.end())
    {
      dbg << "Next iterator item";
      runn = *iterator;
      if(runn->joinable())
      {
	threadRunning = true;
	iterator++;
      }
      else
      {
	delete(runn);
	iterator = startedThreads.erase(iterator);
      }
    }
    
    std::this_thread::sleep_for(std::chrono::milliseconds(THREADS_SLEEP_WHILE_WAIT_TO_END_MS));
    stopCounter++;
  }
  
  if(threadRunning)
  {
    errn << "Not possible to stop all threads - will exit forcely";
    this->dumpRunningThreadsInfo();
  }
  
  info << "All threads stopped, can leave";
}

void Supervision::dumpRunningThreadsInfo()
{
  vector<std::thread *>::iterator iterator;
  std::thread *act;
  
  warn << "## Dumping running threads info ##";
  warn << "Thread ID \t\t joinable";
  for(iterator = this->startedThreads.begin(); iterator != this->startedThreads.end(); iterator++)
  {
    act = *iterator;
    warn << act->get_id() << "\t" << (act->joinable() == true ? "true" : "false");
  }
  warn << "###########################";
}

void Supervision::execute(const Callback& callback)
{
  // just execute callback of the new thread
  // does not support any parameter passing
  callback();
}


