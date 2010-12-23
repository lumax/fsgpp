/*
Poll.h
Bastian Ruppert
*/
#include <poll.h>
namespace EuMax01
{

#ifndef __POLL_H__
#define __POLL_H__

  class IPollTimerListener
  {
   public:
    virtual ~IPollTimerListener() {}
    virtual void (pollTimerExpired)(long time) = 0;
  };
 
  class PollTimer:public LL
  {
  public:
    PollTimer(int ms,IPollTimerListener * lis);
    int timeout;
    unsigned long nextTimeout_us;
    IPollTimerListener * lis;
  private:
    
  };

  class IPollReadListener;

  class PollSource:public LL
  {
  public:
    PollSource(IPollReadListener * lis);
    struct pollfd thePollfd;
    IPollReadListener * lis;
  };
  
  class IPollReadListener
  {
  public:
    virtual ~IPollReadListener() {}
    virtual void (pollReadEvent)(PollSource * s) = 0;
  };
   

  class PollReader:public PollSource
  {
  public:
    PollReader(IPollReadListener * lis);
    int setReadSource(int fd);
  };

  class PollManager
  {   
  public:
    PollManager();
    void addSource(PollSource * ps);
    void addTimer(PollTimer * pt);
    
    void stopPolling();
    int call_poll();
  private:
    int timerHandling(PollTimer * tmpTimer);
    LL pollSources;
    LL timerTargets;
    int timeout;
    int AmountSources;
    bool newPrecondition;
    bool polling;
    struct timeval timerLast;
    struct timeval timerStart;
  };

 
#endif /* __POLL_H__*/
}// end namespace 

