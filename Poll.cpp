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

//#include <iostream>
#include <stdio.h>

namespace EuMax01
{

  PollTimer::PollTimer(unsigned int ms,IPollTimerListener * lis)
  {
    //clear memory
    char * pv = (char*)this;
    for(unsigned int i=0; i<sizeof(PollTimer);i++)
      {
	*pv = 0;
	pv++;
      }
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
    this->PollSourceID = 0;
  }

  void PollSource::setPollSourceID(char* id)
  {
    this->PollSourceID = id;
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
    //this->MaxPollSources=16;
    for(unsigned int i=0; i<sizeof(PollManager);i++)
      {
	*pv=0;
	pv++;
      }
    this->timeout = -1;
    this->MaxPollSources=16;
  }

  int PollManager::addSource(PollSource * ps)
  {
    if(AmountSources < this->MaxPollSources)
      {
	pollSources.addLL(ps);
	AmountSources++;
	newPrecondition = true;
	return 0;
      }
    return -1;
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

  int PollManager::timerHandling(PollTimer * tmpTimer)
  {
    unsigned int sec,i=0;
    if(gettimeofday(&timerStart, NULL))
      return -1;

    while(tmpTimer)
      {
	if(tmpTimer)
	  {
	    if(tmpTimer->nextTimeout.tv_sec<timerStart.tv_sec||\
	       (tmpTimer->nextTimeout.tv_sec==timerStart.tv_sec &&	\
		tmpTimer->nextTimeout.tv_usec<=timerStart.tv_usec) )
	      {
		//next Timeout
		if(tmpTimer->timeout)
		  sec = tmpTimer->timeout/1000;

		i = timerStart.tv_usec+tmpTimer->timeout*1000;
		if(i>=1000000)
		{
		  sec = i/1000000;
		  i=i-sec*1000000;
		}

		tmpTimer->nextTimeout.tv_sec = timerStart.tv_sec+sec;
		tmpTimer->nextTimeout.tv_usec = i;

		//exec Funktion
		tmpTimer->lis->pollTimerExpired(/*timediff*//*uptime*/0);
	      }
	  }
	tmpTimer = (PollTimer*)tmpTimer->Next;
      }
    return 0;
  }

  int PollManager::call_poll()
  {

    struct pollfd fdinfo[this->MaxPollSources];
    PollSource* sources[this->MaxPollSources];
    PollSource* pTmp = 0;
    PollTimer* tmpTimer = (PollTimer*)this->timerTargets.Next;  
    int ret = 0;
    int tmpi = 0;

    timerStart.tv_sec = 0;
    timerStart.tv_usec = 0;

    polling = true;

    if(gettimeofday(&timerStart, NULL))
      return -1;

    while(polling)
      {
	//std::cout<<"---poll---"<<std::endl;
	if(newPrecondition)//new fdinfos only when necessary
	  {
	    //pTmp = 0;
	    pTmp = (PollSource*)this->pollSources.Next;
	    tmpi = 0;
	    while(pTmp)//prepare fdinfo array for poll()
	      {
		sources[tmpi] = pTmp;
		fdinfo[tmpi]=pTmp->thePollfd;
		//fdinfo[tmpi].fd=pTmp->thePollfd.fd;
		//fdinfo[tmpi].events=pTmp->thePollfd.events;
		pTmp = (PollSource*)pTmp->Next;
		tmpi++;
	      }
	    tmpTimer = (PollTimer*)this->timerTargets.Next;
	    newPrecondition = false;
	  }

	ret = poll(fdinfo,AmountSources,/*timeout*/30);
	if(ret<0)
	  {
	    return ret;
	  }

	//std::cout << "mtime: " << mtime << std::endl;

	if(tmpTimer)
	  {
	    if(timerHandling(tmpTimer))
	      return -2;	    
	  }
	if(0<ret)
	  {
	    for(unsigned int i=0;i<AmountSources;i++)
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
