
#include "LL.h"

namespace EuMax01
{

  void LL::addLL(LL * pItem)
  {
    if(!pItem)return;
    pItem->Next = this->Next;
    this->Next = pItem;
  }

}
