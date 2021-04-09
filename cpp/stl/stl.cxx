#include <memory>
#include <iostream>
#include <vector>
#include <exception>
#include <algorithm>
#include <numeric>
#include <list>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>


using namespace std;

template<class T>
void print(const T& list)
{
    for(const auto& e: list)
    {
        cout << e << " ";
    }
    cout << endl;
}

template<>
void print(const queue<int>& q)
{
    auto t = q;
    while(!t.empty())
    {
        cout << t.front() << " ";
        t.pop();
    }
    cout << endl;
}

template<>
void print(const map<string, int>& m)
{
    for(const auto& e: m)
    {
        cout <<"(" << e.first << ", " << e.second << ") ";
    }
    cout << endl;
}

template<>
void print(const multimap<string, int>& m)
{
    for(const auto& e: m)
    {
        cout <<"(" << e.first << ", " << e.second << ") ";
    }
    cout << endl;
}


template<class T>
void algorithms(const vector<T>& vec)
{
    cout << "Original: ";
    print(vec);
    
    vector<T> work(vec.size());
    copy_n(vec.begin(), vec.size(), work.begin());
    cout << "Copy: ";
    print(work);
    
    sort(work.begin(), work.end(), [](T x, T y) { return x>y;});
    cout << "Custom sorted: ";
    print(work);

    int val = 5;
    cout << "Searching " << val << endl;
    cout << "First sort vector: ";
    sort(work.begin(), work.end());
    print(work);
    auto result = binary_search(work.begin(), work.end(), val);
    cout << "Result: " << result << endl;
    
    cout << "Reversed: ";
    reverse(work.begin(), work.end());
    print(work);
    
    cout << "Max: " << *max_element(work.begin(), work.end()) << endl;
    cout << "Min: " << *min_element(work.begin(), work.end()) << endl;
    cout << "Sum: " << accumulate(work.begin(), work.end(), 0) << endl;
    cout << "Contains negative numbers: " << any_of(work.begin(), work.end(), [](int x) {return x<0;}) << endl;
    
    vector<int> temp(10);
    cout << "Temp capacity: " << temp.capacity() << ", Size: " << temp.size() << endl;
    cout << "Initial state: ";
    print(temp);
    iota(temp.begin(), temp.end(), 3);
    cout << "Iota: ";
    print(temp);
    
    partition(temp.begin(), temp.end(), [](int x) { return x%2; });
    cout << "Partitioned: ";
    print(temp);
}

void lists()
{
    list<int> l(10);
    iota(l.begin(), l.end(), 3);
    cout << "Doubly linked list: ";
    print(l);
    l.emplace(l.begin(), 666);
    l.pop_back();
    print(l);
    l.pop_front();
    print(l);
    l.reverse();
    print(l);
    l.sort();
    print(l);
    for(int i=0; i<20; i++)
    {
        l.push_back(i);
    }
    cout << "Added values: ";
    print(l);
    l.sort();
    l.unique();
    cout << "Unique: ";
    print(l);
    list<int> l2 {2,3, 45, 6, 8, 9, 33, 2};
    l2.sort();
    l.merge(l2);
    cout << "Merged: ";
    print(l);
}

void queues()
{
    queue<int> q;
    for(int i=0; i<10; i++)
    {
        q.push(i);
    }
    cout << "Queue: ";
    print(q);
    cout << "Check: ";
    print(q);
}

void sets()
{
    auto arr = {3, 5, 1, 5, 7, 2, 1, 5};
    set<int> s(arr);
    cout << "Set: ";
    print(s);
    cout << "Lower bound 4: " << *s.lower_bound(4) << endl;
    
    multiset<int> s2(arr);
    cout << "Multiset: ";
    print(s2);
    s2.erase(s2.find(5));
    print(s2);
    
    unordered_set<int> us(arr);
    cout << "Unordered set: ";
    print(us);
    
    unordered_multiset<int> us2(arr);
    cout << "Unordered multiset: ";
    print(us2);
    cout << "Number of 5s: " << us2.count(5) << endl;
}

void maps()
{
    map<string, int> m;
    m["a"] = 2;
    m["c"] = 23;
    m["xyz"] = 12;
    m["a"] = 666;
    
    cout << "Map: ";
    print(m);
    
    multimap<string, int> m2;
    m2.insert(pair<string, int>("a", 2));
    m2.insert(pair<string, int>("c", 4));
    m2.insert(pair<string, int>("xyz", 9));
    m2.insert(pair<string, int>("a", 666));

    cout << "Multimap: ";
    print(m2);
    
    cout << (*m2.find("a")).second << endl;
    
}

int main()
{
    vector<int> vec {12, 4, 2, 4, 13, 6, 7, 2, 5, 12, 4, 3, 0, 3, 1};
    algorithms(vec);
    
    lists();
    
    queues();
    
    sets();
    
    maps();
    
    return 0;
}
