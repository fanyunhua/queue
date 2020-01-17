/***
 * @author          :范玉华
 * @brief           :摘要
 * @version         :1.0
 * @date            :2019-11-18
 */
#ifndef IQUEUE
#define IQUEUE

#include <mutex>
namespace __base {
template<typename T>
struct _Base_NODE
{
    T _value;
    _Base_NODE<T> *_next;
    int _size;
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
        _size = 0;
    }

    bool enqueue(T &value)
    {
        _tailLock->lock();
        _NODE *  node = new(std::nothrow) _NODE();
        node->_next = NULL;
        node->_value = value;
        node->_size = _size++;
        std::cout<<_size<<std::endl;
        _tail->_next = node;
        _tail = node;
        _tailLock->unlock();
        return true;
    }

    bool enqueue(T &&value)
    {
        _tailLock->lock();
        _NODE *  node = new _NODE;
        node->_next = NULL;
        node->_value = value;
        node->_size = _size+=1;

        _tail->_next = node;
        _tail = node;
        _tailLock->unlock();
        return true;
    }

    bool dequeue(T *pValue)
    {
        _headLock->lock();
        if(this->isEmpty())
        {
            _headLock->unlock();
            return false;
        }
        _NODE *  node;
        _NODE *  newHeader;
        node = _header;
        newHeader = node->_next;
        _headNumber = newHeader->_size;

        *pValue =  newHeader->_value;
        _header =  newHeader;
        delete node;
        _headLock->unlock();
        return true;
    }
    bool isEmpty()
    {
        bool result =  (_header->_next)==nullptr?true:false;
        if(result)
            _size = 0;
        return result;
    }
    void clear()
    {
        inital();
    }

    int size()
    {
        int si = _size -_headNumber;
        si = si>=0?si:0;
        return si;
    }

private:
    int _size;
    int _headNumber;
};

#endif // IQUEUE
