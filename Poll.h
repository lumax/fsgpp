/*
Poll.h
Bastian Ruppert
*/
#include <poll.h>
namespace EuMax01
{

#ifndef __POLL_H__
#define __POLL_H__

  class IPollListener;

  class PollSource:public LL
  {
  public:
    PollSource(IPollListener * lis);
    struct pollfd thePollfd;
    IPollListener * lis;
  };

  class IPollListener
  {
  public:
    virtual ~IPollListener() {}
    virtual void (pollEvent)(PollSource * s) = 0;
  };   

  class PollReader:public PollSource
  {
  public:
    PollReader(IPollListener * lis);
    int setReadSource(int fd);
  };

  class PollManager
  {   
  public:
    PollManager();
    void addSource(PollSource * ps);
    void stopPolling();
    int call_poll();
  private:
    LL pollSources;
    int AmountSources;
    bool newPrecondition;
    bool polling;
  };

 
#endif /* __POLL_H__*/
}// end namespace 

