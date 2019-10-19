#include <thread>
#include "iqueue.h"
#include <QDateTime>
#include <QDebug>
#include <mutex>


#include <list>
#include <QList>
using namespace std;

IQueue<int> queue;
int cccc = 0;
void rr()
{
    static int cou = 0;
    while (1) {
            int *data = new int;

            bool kk = queue.dequeue(data);
            if(kk)
            {
//                qDebug()<<"read"<<queue.getSize()<<*data<<kk<<"\t";//<<QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz");;
            cou++;
                if(cou==500000)
                {
                    qDebug()<<*data;
                    break;
                }
            }
    }
}


void w()
{
    int k = 1000;
    for(int i = 0;i<500000;i++)
    {
        queue.enqueue(i);
    }
}


void m()
{
    QDateTime start = QDateTime::currentDateTime();
    thread s(rr);
    this_thread::sleep_for(chrono::milliseconds(1000));
    thread bb(w);

    bb.join();
    s.join();
    QDateTime end = QDateTime::currentDateTime();
    int result = end.toTime_t()-start.toTime_t();

    qDebug()<<result<<"result";
    qDebug()<<start.toString("yyyy-MM-dd HH:mm:ss.zzz");
    qDebug()<<end.toString("yyyy-MM-dd HH:mm:ss.zzz");
}

int main(int argc, char *argv[])
{
        m();
    qDebug()<<"ss";

    list<int> ll;
    ll.size();
    QList<QString> lll;
    lll.size();
    return 0;
}
