/*
Bastian Ruppert
*/


#include <poll.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "LL.h"

#include "Poll.h"

namespace EuMax01
{

  PollSource::PollSource(IPollListener * lis)
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
  
  PollReader::PollReader(IPollListener * lis):PollSource(lis)
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
  }

  void PollManager::addSource(PollSource * ps)
  {
    pollSources.addLL(ps);
    AmountSources++;
    newPrecondition = true;
  }

  void PollManager::stopPolling()
  {
    this->polling = false;
  }

  int PollManager::call_poll()
  {
    int ret = 0;
    int tmpi = 0;
    struct pollfd fdinfo[AmountSources];
    PollSource* sources[AmountSources];
    PollSource* pTmp = (PollSource*)this->pollSources.Next;
    
    polling = true;
    
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
	
	ret = poll(fdinfo,AmountSources,-1);
	  if(ret<0)
	    {
	      return ret;
	    }
	for(int i=0;i<AmountSources;i++)
	  { 
	    //reading
	    if(fdinfo[i].revents & (POLLIN | POLLPRI) )
	      {
		sources[i]->lis->pollEvent(sources[i]);
	      }
	  }
      }//end while (polling)
    return 0;
  }

}//end namespace
