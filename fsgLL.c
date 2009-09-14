
#include "fsgLL.h"

void fsgLLAdd(_pTfsgLL pTarget,_pTfsgLL pItem)
{
  if(!pTarget)return;
  if(!pItem)return;
  pItem->Next = pTarget->Next;
  pTarget->Next = pItem;
}

