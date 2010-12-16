/*
Bastian Ruppert
*/


#include <poll.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>

#include "LL.h"

#include "Poll.h"

#include <iostream>

namespace EuMax01
{

  PollTimer::PollTimer(int ms,IPollTimerListener * lis)
  {
    this->timeout = ms;
    this->lis = lis;
  }

  PollSource::PollSource(IPollReadListener * lis)
  {
    //clear memory
    char * pv = (char*)this;
    for(unsigned int i=0; i<sizeof(PollSource);i++)
      {
	*pv = 0;
	pv++;
      }
    this->lis = lis;
  }
  
  PollReader::PollReader(IPollReadListener * lis):PollSource(lis)
  {
    
  }

  /*
   *Sets errno
   */
  /*  int PollReader::setReadSource(const char* path,void (*readFnk)(PollSource * s))
  {
    int fd = open(path, O_RDONLY);
    if(-1==fd)
      return -1;
    return setReadSource(fd,readFnk);
    }*/

  /*
   *Sets errno
   */
  int PollReader::setReadSource(int fd)
  {
    if(this->thePollfd.fd)
      return -2;
    
    this->thePollfd.fd = fd;
    this->thePollfd.events = POLLIN | POLLPRI;
    return 0;
  }

  PollManager::PollManager()
  {
      //clear memory
    char * pv = (char*)this;
    for(unsigned int i=0; i<sizeof(PollManager);i++)
      {
	*pv=0;
	pv++;
      }
    this->timeout = -1;
  }

  void PollManager::addSource(PollSource * ps)
  {
    pollSources.addLL(ps);
    AmountSources++;
    newPrecondition = true;
  }

  void PollManager::addTimer(PollTimer * pt)
  {
    timerTargets.addLL(pt);
    timeout = pt->timeout;
  }

  void PollManager::stopPolling()
  {
    this->polling = false;
  }

  int PollManager::call_poll()
  {
    static struct timeval last;
    struct timeval start;
    int ret = 0;
    int tmpi = 0;
    long mtime = 0;
    long seconds = 0;
    long useconds = 0;    
    struct pollfd fdinfo[AmountSources];
    PollSource* sources[AmountSources];
    PollSource* pTmp = (PollSource*)this->pollSources.Next;
    PollTimer* tmpTimer = (PollTimer*)this->timerTargets.Next;
 
    start.tv_sec = 0;
    start.tv_usec = 0;
    last.tv_sec = 0;
    last.tv_usec = 0;

    polling = true;

    if(gettimeofday(&start, NULL))
      return -1;
    
    last=start;

    while(polling)
      {
	if(newPrecondition)//new fdinfos only when necessary
	  {
	    while(pTmp)//prepare fdinfo array for poll()
	      {
		fdinfo[tmpi]=pTmp->thePollfd;
		sources[tmpi] = pTmp;
		pTmp = (PollSource*)pTmp->Next;
		tmpi++;
	      }
	    newPrecondition = false;
	  }
	//std::cout<<"---poll---"<<std::endl;
	ret = poll(fdinfo,AmountSources,timeout);
	if(ret<0)
	  {
	    return ret;
	  }
	
	if(gettimeofday(&start, NULL))
	  return -1;
	
	seconds  = start.tv_sec  - last.tv_sec;
	useconds = start.tv_usec - last.tv_usec;
	
	mtime = seconds * 1000000;
	
	if(0!=seconds)
	  {
	    mtime -=last.tv_usec; 
	    mtime +=start.tv_usec;
	  }
	else
	  {
	    mtime += start.tv_usec - last.tv_usec;
	  }
	last = start;

	//std::cout << "mtime: " << mtime << std::endl;
	
	if(tmpTimer)
	  {
	    tmpTimer->lis->pollTimerExpired(mtime);
	  }
	if(0<ret)
	  {
	    for(int i=0;i<AmountSources;i++)
	      { 
		//TODO POLLERR POLLHUB POLLNVAL
		//reading
		if(fdinfo[i].revents & (POLLIN | POLLPRI) )
		  {
		    sources[i]->lis->pollReadEvent(sources[i]);
		  }
	      }
	  }
      }//end while (polling)
    return 0;
  }

}//end namespace
