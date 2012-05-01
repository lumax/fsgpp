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
    PollTimer(unsigned int ms,IPollTimerListener * lis);
    unsigned int timeout;
    struct timeval nextTimeout;
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
    bool CustomEventHandler;
    char * PollSourceID;

    void setPollSourceID(char * id);
    void setFD(struct pollfd fd);
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
    int setReadSource(int fd,char * id);
  };

  class PollManager
  {   
  public:
    PollManager();

    /*! \brief Ohne CustomEventHandler (CustmEventHandler = false):
     *         Es werden die Flags fdinfo[i].revents & (POLLIN | POLLPRI)
     *         ausgewertet.
     */
    int addSource(PollSource * ps);

    /*! \brief Mit dem CustomEventHandler muss sich selber um die
     *         Auswertung der revents Flags gekümmert werden.
     */
    int addSource(PollSource * ps,bool customEvtHandler);
    void addTimer(PollTimer * pt);
    
    void stopPolling();
    int call_poll();
  private:
    int timerHandling(PollTimer * tmpTimer);
    LL pollSources;
    LL timerTargets;
    int timeout;
    unsigned int AmountSources;
    bool newPrecondition;
    bool polling;
    struct timeval timerStart;
    unsigned int MaxPollSources;
  };

 
#endif /* __POLL_H__*/
}// end namespace 

