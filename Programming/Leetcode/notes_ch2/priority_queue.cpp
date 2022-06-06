#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class PriorityQueue
{
private:
    T*  pq;
    int N;

public:
    PriorityQueue(int);
    ~PriorityQueue();

    T Front();
    void Push(T);
    void Pop();
    void check();

private:
    void swim(int);
    void sink(int);

    int parent(int);
    int left(int);
    int right(int);

    bool less(int, int);
    void exchange(int, int);
};

template <typename T>
PriorityQueue<T>::PriorityQueue(int n)
{
    this->pq = new T[n + 1];
    this->N = 0;
}

template <typename T>
PriorityQueue<T>::~PriorityQueue()
{
    delete this->pq;
}

template <typename T>
T PriorityQueue<T>::Front()
{
    return this->pq[1];
}

template <typename T>
void PriorityQueue<T>::Push(T t)
{
    this->N ++;
    this->pq[N] = t;
    swim(this->N);
}

template <typename T>
void PriorityQueue<T>::Pop()
{
    exchange(1, this->N);
    this->N --;
    sink(1);
}

template <typename T>
void PriorityQueue<T>::swim(int k)
{   
    while(k > 1 && less(parent(k), k))
    {
        exchange(parent(k), k);
        k = parent(k);
    }
}

template <typename T>
void PriorityQueue<T>::sink(int k)
{
    // cout<<"Left:"<<left(k)<<' '<<this->pq[left(k)]<<endl;
    while(left(k) <= this->N)
    {
        T larger = left(k);
        // cout<<"Right:"<<right(k)<<' '<<this->pq[right(k)]<<endl;
        if(right(k) <= this->N && less(larger, right(k)))
        {
            // cout<<"Right:"<<right(k)<<endl;
            larger = right(k);
        }
        if(less(larger, k))
        {
            this->check();
            // cout<<"Break:"<<larger<<' '<<k<<endl;
            break;
        }
        exchange(k, larger);
        k = larger;

        // cout<<"Sink:"<<this->pq[larger]<<endl;
    }
}

template <typename T>
int PriorityQueue<T>::left(int root)
{
    return root << 1;
}

template <typename T>
int PriorityQueue<T>::right(int root)
{
    return (root << 1) + 1;
}

template <typename T>
int PriorityQueue<T>::parent(int root)
{
    return root >> 1;
}

template <typename T>
bool PriorityQueue<T>::less(int i, int j)
{
    return this->pq[i] < this->pq[j];
}

template <typename T>
void PriorityQueue<T>::exchange(int i, int j)
{
    T temp = this->pq[i];
    this->pq[i] = this->pq[j];
    this->pq[j] = temp;
}

template <typename T>
void PriorityQueue<T>::check()
{
    cout<<"Length: "<<this->N<<": ";
    for(int i=1; i<=this->N; i ++)
    {
        cout<<this->pq[i]<<' ';
    }
    cout<<endl;
}

int main(int argc, char const *argv[])
{
    PriorityQueue<int> PQ(10);

    for(int i=1; i<=10; i += 2)
    {
        PQ.Push(i);
        PQ.check();
    }

    for(int i=1; i<=3; i ++)
    {
        // cout<<"Before:";
        // PQ.check();
        cout<<PQ.Front()<<' ';
        PQ.Pop();
        // cout<<"After:";
        PQ.check();
        // cout<<endl;
    }

    for(int i=2; i<=10; i += 2)
    {
        PQ.Push(i);
        PQ.check();
    }

    for(int i=1; i <= 7; i ++)
    {
        // cout<<"Before:";
        // PQ.check();
        cout<<PQ.Front()<<' ';
        PQ.Pop();
        // cout<<"After:";
        PQ.check();
        // cout<<endl;
    }

    return 0;
}
