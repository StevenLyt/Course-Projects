#include <vector>
template<class T>
class MinHeap
{
public:
    MinHeap(int d);
    /* Constructor that builds a d-ary Min Heap
       This should work for any d >= 2,
       but doesn't have to do anything for smaller d.*/

    ~MinHeap();

    void add(T item, int priority);
    /* adds the item to the heap, with the given priority. */

    const T& peek() const;
    /* returns the element with smallest priority.
       Break ties however you wish.
       Throws an exception if the heap is empty. */

    void remove();
    /* removes the element with smallest priority.
       Break ties however you wish.
       Throws an exception if the heap is empty. */

    bool isEmpty();
    /* returns true iff there are no elements on the heap. */
private:
    // whatever you need to naturally store things.
    // You may also add helper functions here.
    std::vector<T> T_container;
    std::vector<int> priority_container;
    int d;
    int size;

    int parent(int i) { return (i - 1) / d; }

    std::vector<int> children(int i)
    {
        std::vector<int> v;
        for (int j = 1; j <= d; j++)
        {
            v.push_back(i * d + j);
        }
        return v;
    }
};

template<class T>
MinHeap<T>::MinHeap(int d)
{
    if (d >= 2)
    {
        this->d = d;
        size = 0;
    }
}

template<class T>
MinHeap<T>::~MinHeap()
{
}

template<class T>
void MinHeap<T>::add(T item, int priority)
{
    T_container.push_back(item);
    priority_container.push_back(priority);
    size++;
    // trickle up
    int curr = size - 1;
    while (curr && priority_container[parent(curr)] > priority_container[curr])
    {
        std::swap(priority_container[parent(curr)], priority_container[curr]);
        std::swap(T_container[parent(curr)], T_container[curr]);
        curr = parent(curr);
    }
}

template<class T>
const T& MinHeap<T>::peek() const
{
    if (size == 0)
    {
        throw "The heap is empty.";
    }
    else
    {
        return T_container[0];
    }
}

template<class T>
void MinHeap<T>::remove()
{
    if (size == 0)
    {
        throw "The heap is empty.";
    }
    else
    {
        std::swap(priority_container[0], priority_container[size - 1]);
        std::swap(T_container[0], T_container[size - 1]);
        priority_container.pop_back();
        T_container.pop_back();
        size--;
        // trickle down
        int curr = 0;
        while (children(curr)[d - 1] < size && priority_container[curr] > priority_container[curr * d + 1])
        {
            // find min child
            std::vector<int> children = this->children(curr);
            int min_index = curr * d + 1;
            for (int i = 1; i < children.size(); i++)
            {
                if (priority_container[i] < priority_container[min_index])
                {
                    min_index = i;
                }
            }
            std::swap(priority_container[curr], priority_container[min_index]);
            std::swap(T_container[curr], T_container[min_index]);
            curr = min_index;
        }
    }
}

template<class T>
bool MinHeap<T>::isEmpty()
{
    return size == 0;
}