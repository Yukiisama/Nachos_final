#ifdef CHANGED
#ifndef PAGEPROVIDER_H
#define PAGEPROVIDER_H
#include "bitmap.h"
class pageprovider : dontcopythis
{
public:
    pageprovider(int size);
    ~pageprovider();
    int  GetEmptyPage();
    void ReleasePage(int page);
    int  NumAvailPage();
private:
    BitMap * page_bitmap;
};

#endif // PAGEPROVIDER_H
#endif // CHANGED
