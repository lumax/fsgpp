namespace EuMax01
{

#ifndef __FSGLL_H__
#define __FSGLL_H__
/*

 */


  class LL
  {
  public:
    LL();
    ~LL();
    LL * Next;
    unsigned int counter;
    void addLL(LL * pItem);
    void removeSingleLL(LL * pItem);
    //LL* removeLL(LL * pItem2Remove);
  };
  
#endif /*__FGSLL_H__*/
  
}
