#ifndef _H_SUPERVISION
#define _H_SUPERVISION

class Supervision
{
private:
  bool stop;
  
  void initThermometers();
  
public:
  Supervision();
  virtual ~Supervision();  
  
  void init();
};

#endif