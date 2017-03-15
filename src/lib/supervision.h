#ifndef _H_SUPERVISION
#define _H_SUPERVISION

#include "configuration/configuration.h"
#include "../thermometer/thermometerstatistics.h"
#include <functional>

typedef std::function<void (void)> Callback;

class Supervision
{
private:
  bool m_stop;
  std::string m_stopReason;
  std::string m_conf;
  const int SUPERVISE_PERIOD_CHECK_MS = 100;
  std::vector<std::thread *> startedThreads;
  static std::vector<Callback> queue;
  ThermometerStatistics statistics;
  
  bool loadConfiguration();
  bool supervise();
  bool startInThread(const Callback& callback);
  void execute(const Callback& callback);
  
  void waitForThreads();
  void dumpRunningThreadsInfo();
  
public:
  Supervision();
  virtual ~Supervision();
  
  void setConfigurationFile(const std::string& conf);
  void init();
  void stop(const std::string &verbose);
  static bool enqueueNewThread(const Callback &callback);
};

#endif
