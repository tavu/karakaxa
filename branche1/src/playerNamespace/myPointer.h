#ifndef MYPOINDER_H
#define MYPOINDER_H


template <typename T>


//this is a very sympli class for specific reazons
//it's much simplier than QsharedPointers and it can not replace them
class myPointer
{
//      T element;
public:
    inline myPointer(T *p)
            :used(0)
    {
        this->p=p;
    }
    int used;
    T *p;
};
#endif
