#include "MinHeap.h"
#include <assert.h>
#include <iostream>
#include <queue>
using namespace std;

void push_to_pq(int i, priority_queue<int>& pq) { pq.push(-i); }

int peek_from_pq(priority_queue<int>& pq) { return -pq.top(); }

void test()
{
    priority_queue<int> pq;
    MinHeap<int> mh2(2);
    MinHeap<int> mh3(3);
    MinHeap<int> mh4(4);

    push_to_pq(2, pq);
    mh2.add(2, 2);
    mh3.add(2, 2);
    mh4.add(2, 2);

    push_to_pq(3, pq);
    mh2.add(3, 3);
    mh3.add(3, 3);
    mh4.add(3, 3);

    push_to_pq(1, pq);
    mh2.add(1, 1);
    mh3.add(1, 1);
    mh4.add(1, 1);

    assert(peek_from_pq(pq) == mh2.peek());
    assert(peek_from_pq(pq) == mh3.peek());
    assert(peek_from_pq(pq) == mh4.peek());

    pq.pop();
    mh2.remove();
    mh3.remove();
    mh4.remove();

    push_to_pq(5, pq);
    mh2.add(5, 5);
    mh3.add(5, 5);
    mh4.add(5, 5);

    push_to_pq(6, pq);
    mh2.add(6, 6);
    mh3.add(6, 6);
    mh4.add(6, 6);

    assert(peek_from_pq(pq) == mh2.peek());
    assert(peek_from_pq(pq) == mh3.peek());
    assert(peek_from_pq(pq) == mh4.peek());

    push_to_pq(4, pq);
    mh2.add(4, 4);
    mh3.add(4, 4);
    mh4.add(4, 4);

    push_to_pq(0, pq);
    mh2.add(0, 0);
    mh3.add(0, 0);
    mh4.add(0, 0);

    assert(peek_from_pq(pq) == mh2.peek());
    assert(peek_from_pq(pq) == mh3.peek());
    assert(peek_from_pq(pq) == mh4.peek());

    cout << "ALL Test passed." << endl;
}

int main() { test(); }