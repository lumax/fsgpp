
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

}
