#ifndef IQUEUE
#define IQUEUE

#include <mutex>

namespace __base {
template<typename T>
struct _Base_NODE
{
    T _value;
    _Base_NODE<T> *_next;
};
}

template<typename T>
struct IQueue
{
    typedef __base::_Base_NODE<T> _NODE;
    _NODE *_header;
    _NODE *_tail;
    std::mutex *_headLock = new std::mutex;
    std::mutex *_tailLock = new std::mutex;
    IQueue()
    {
        inital();
    }

    void inital()
    {
        _header = new _NODE;
        _tail = new _NODE;
        _NODE *node ;
        node = new _NODE;
        node->_next = NULL;
        _header  =    _tail = node;
    }

    bool enqueue(T &value)
    {
        _NODE *  node = new(std::nothrow) _NODE();
        node->_next = NULL;
        node->_value = value;
		_tailLock->lock();
        _tail->_next = node;
        _tail = node;
        _tailLock->unlock();
        return true;
    }

    bool enqueue(T &&value)
    {
        _NODE *  node = new _NODE;
        node->_next = NULL;
        node->_value = value;
        _tailLock->lock();
        _tail->_next = node;
        _tail = node;
        _tailLock->unlock();
        return true;
    }

    bool dequeue(T *pValue)
    {
        if(this->isEmpty())
            return false;
        _NODE *  node;
        _NODE *  newHeader;
        _headLock->lock();
        node = _header;
        newHeader = node->_next;
        *pValue =  newHeader->_value;
        _header =  newHeader;
        delete node;
        _headLock->unlock();
        return true;
    }
    bool isEmpty()
    {
        return (_header->_next)==nullptr?true:false;
    }
    void clear()
    {
        inital();
    }
    int size()
    {
        //效率明显降低
        int s = 0;
        if(!isEmpty())
        {
            _NODE *  node = _header;
            while (node->_next!=NULL) {
                s++;
                node = node->_next;
            }
        }
        return s;
    }
};

#endif // IQUEUE

