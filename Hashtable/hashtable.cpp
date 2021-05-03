#include "hashtable.h"

#include <cmath>
#include <iostream>
#include <string>

using namespace std;

// probing can take values 0, 1, 2
// 0 means that your Hashtable must use linear probing,
// 1 means quadratic probing,
// and 2 means double hashing.
Hashtable::Hashtable(bool debug, unsigned probing)
        : size(0), capacity(11), probing(probing), debug(debug), capacity_index(0)
{
    // hashtable initially has 11 positions
    table = new pair<string, int>[11];
    empty = new bool[11];
    for (int i = 0; i < 11; i++)
        empty[i] = true;
    if (debug)
    {
        r[0] = 983132572;
        r[1] = 62337998;
        r[2] = 552714139;
        r[3] = 984953261;
        r[4] = 261934300;
    }
    else
    {
        r[0] = rand() % capacity;
        r[1] = rand() % capacity;
        r[2] = rand() % capacity;
        r[3] = rand() % capacity;
        r[4] = rand() % capacity;
    }
}

Hashtable::~Hashtable()
{
    delete[] table;
    delete[] empty;
}

void Hashtable::add(string k)
{
    // if loading factor >= 0.5, resize
    if ((double)size / capacity >= 0.5)
    {
        resize();
    }

    unsigned hash = this->hash(k);
    unsigned record = hash;
    for (int i = 0; i < capacity; i++)
    {
        if (empty[hash])
        {
            table[hash] = make_pair(k, 1);
            empty[hash] = false;
            size++;
            return;
        }
        if (table[hash].first == k)
        {
            table[hash].second++;
            return;
        }
        // use appropriate probing method
        if (probing == 0)
            hash = record + (i + 1) * 1;
        else if (probing == 1)
            hash = record + (i + 1) * (i + 1);
        else
            hash = record + (i + 1) * double_hashing(k);

        hash %= capacity;
    }
}

int Hashtable::count(std::string k) const
{
    unsigned hash = this->hash(k);
    unsigned record = hash;
    for (int i = 0; i < capacity; i++)
    {
        if (empty[hash])
            return 0;
        if (table[hash].first == k)
            return table[hash].second;

        // use appropriate probing method
        if (probing == 0)
            hash = record + (i + 1) * 1;
        else if (probing == 1)
            hash = record + (i + 1) * (i + 1);
        else
            hash = record + (i + 1) * double_hashing(k);
        hash %= capacity;
    }
    return 0;
}

void Hashtable::reportAll(std::ostream& out) const
{
    for (int i = 0; i < capacity; i++)
    {
        if (!empty[i])
            out << table[i].first << " " << table[i].second << endl;
    }
}

void Hashtable::resize()
{
    int prev_capacity = capacity;
    capacity = primes1[++capacity_index];

    pair<string, int>* table_temp = table;
    table = new pair<string, int>[capacity];

    bool* empty_temp = empty;
    empty = new bool[capacity];
    for (int i = 0; i < capacity; i++)
        empty[i] = true;

    // regenerate r1 to r5
    if (!debug)
    {
        r[0] = rand() % capacity;
        r[1] = rand() % capacity;
        r[2] = rand() % capacity;
        r[3] = rand() % capacity;
        r[4] = rand() % capacity;
    }
    // rehash all existing strings and their values
    for (int i = 0; i < prev_capacity; i++)
    {
        if (!empty_temp[i])
        {
            unsigned hash = this->hash(table_temp[i].first);
            unsigned record = hash;
            for (int j = 0; j < capacity; j++)
            {
                if (empty[hash])
                {
                    table[hash] = table_temp[i];
                    empty[hash] = false;
                    break;
                }
                // use appropriate probing method
                if (probing == 0)
                    hash = record + (j + 1) * 1;
                else if (probing == 1)
                    hash = record + (j + 1) * (j + 1);
                else
                    hash = record + (j + 1) * double_hashing(table_temp[i].first);
                hash %= capacity;
            }
        }
    }
    // deallocate previous data
    delete[] table_temp;
    delete[] empty_temp;
}

int Hashtable::hash(string k) const
{
    // initialize all positions to 0
    int w[5] = {0};
    int index = k.size() - 1;
    for (size_t i = 0; i < ((k.size() - 1) / 6 + 1); i++)
    {
        int hashed_value = 0;
        for (int j = 0; j < 6; j++)
        {
            if (index >= 0)
            {
                hashed_value += pow(26, j) * (k[index] - 'a');
                index--;
            }
            else
                break;
        }
        w[5 - 1 - i] = hashed_value;
        if (index < 0)
            break;
    }
    int hashed_index = ((long long)r[0] * w[0] + (long long)r[1] * w[1] + (long long)r[2] * w[2]
                        + (long long)r[3] * w[3] + (long long)r[4] * w[4])
                       % capacity;

    return hashed_index;
}

int Hashtable::double_hashing(string k) const
{
    int w[5] = {0};
    int index = k.size() - 1;
    for (size_t i = 0; i < ((k.size() - 1) / 6 + 1); i++)
    {
        int hashed_value = 0;
        for (int j = 0; j < 6; j++)
        {
            if (index >= 0)
            {
                hashed_value += pow(26, j) * (k[index] - 'a');
                index--;
            }
            else
                break;
        }
        w[i] = hashed_value;
        if (index < 0)
            break;
    }
    int p = primes2[capacity_index];
    int hashed_index = p - ((w[0] + w[1] + w[2] + w[3] + w[4]) % p);
    return hashed_index;
}
