namespace EuMax01
{

#ifndef __FSGLL_H__
#define __FSGLL_H__
/*

 */


  class LL_Item
  {
  public:
    LL_Item * Next;
    int data;
    void addLL(LL_Item * pItem);
  }
  typedef struct _T_fsgLL_Item
  {
    struct _T_fsgLL_Item * Next;
    //struct _T_fsgLL_Item * Prev;
    int data;
  }_TfsgLL,*_pTfsgLL;
#endif /*__FGSLL_H__*/
  
}
