#include "supervision.h"
#include "logger.h"

#include <thread>
#include <chrono>
#include <iostream>

std::vector<Callback> Supervision::queue;

Supervision::Supervision()
{
  stop = false;
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
  Configuration conf(m_conf);
  
  if(! conf.loadConfiguration(statistics))
  {
    errn << "Configuration load failed";
    return false;
  }
  
  return this->supervise();
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
  std::thread th = std::thread(&Supervision::execute, this, callback);
  th.detach();
  
  startedThreads.push_back(&th);
  dbg << "Starting new thread";
}

bool Supervision::supervise()
{
  info << "Configuration loaded from file: " << m_conf;
  info << "Go to supervise state";
  
  // Start collecting statistics 
  // 	will create some new threads etc
  statistics.startStatsColl();
  
  while(!stop)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(SUPERVISE_PERIOD_CHECK_MS));
    
    while(! queue.empty())
    {
      this->startInThread(queue.back());
      queue.pop_back();
    }
  }
  
  if(stop)
  {
    info << "Intentional stop, bye";
    return true; 
  }
  else
  {
    errn << "Some other type of stop, most probably failed";
    return false;
  }
}


void Supervision::execute(const Callback& callback)
{
  // just execute callback of the new thread
  // does not support any parameter passing
  callback();
}


