
#include "LL.h"

namespace EuMax01
{

  LL::LL()
  {
    Next=0;
  }
  
  void LL::addLL(LL * pItem)
  {
    LL * pLast;
    if(!pItem)return;
    pLast = pItem;
    while(pLast->Next)
    {
      pLast = pLast->Next;
    }
    pLast->Next = this->Next;
    this->Next = pItem;
  }

  /*  void LL::removeSingleLL(LL * pItem)
  {
    LL * pPrev;
    if(!pItem)return;
    pPrev = this;
    while(pPrev->Next)
      {
	if(pPrev->Next == pItem)
	  {
	    pPrev->Next = pItem->Next;
	    return;
	  }
	pPrev = pPrev->Next;
      }
  }
  */
  /*
   * returns the seperated LL Pointer or 0 if LL not found
   *
   */
  /*LL* LL::removeLL(LL * pItem2Remove)
  {
    LL * tmp = this->Next;
    while(tmp)
      {
	if(tmp->Next==pItem2Remove)
	  {
	    tmp->Next=pItem2Remove->Next;
	    return pItem2Remove;
	  }
	tmp=tmp->Next;
      }
    return 0;
    }*/
}
