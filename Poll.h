/*
Poll.h
Bastian Ruppert
*/
#include <poll.h>
namespace EuMax01
{

#ifndef __POLL_H__
#define __POLL_H__
  
  class PollSource:public LL
  {
  public:
    PollSource();
    struct pollfd thePollfd;
    void (*readFnk)(PollSource * s);
  };
  
  class PollReader:public PollSource
  {
    //    int setTimer(int ms, void (*timerExpired)());
  public:
    PollReader();
    //int setReadSource(const char* path,void (*rFnk)(PollSource * s));
    int setReadSource(int fd,void (*rFnk)(PollSource * s));
  };

  class PollManager
  {   
  public:
    PollManager();
    void addSource(PollSource * ps);
    void stopPolling();
    int call_poll();
  private:
    PollSource pollSources;
    int AmountSources;
    bool newPrecondition;
    bool polling;
  };

 
#endif /* __POLL_H__*/
}// end namespace 

