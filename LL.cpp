
#include "LL.h"

namespace EuMax01
{

  LL::LL()
  {
    Next=0;
    data = 0;
  }
  
  void LL::addLL(LL * pItem)
  {
    if(!pItem)return;
    pItem->Next = this->Next;
    this->Next = pItem;
  }

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
