#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <fstream>
#include <set>
#include <map>
using namespace std;

class f{
public:
    bool operator()(int i){
        if(i % 2 == 0){
            return true;
        }
        return false;
    }
};




void printList(const list<int>& lst){
    list<int>::const_iterator cit;
    for(cit = lst.begin(); cit != lst.end(); cit++){
        cout << *cit << " ";
    }
    cout << endl;
}

void printList2(const list<int>& lst){
    for(int x : lst){
        cout << x << " ";
    }
    cout << endl;
}

void printListAuto(const list<int>& lst){
    for(auto iter = lst.begin(); iter != lst.end(); iter++){
        cout << *iter << " ";
    }
    cout << endl;
}

list<int>::const_iterator findItem(const list<int>& lst, int x){
    list<int>::const_iterator lit;
    for(lit = lst.begin();lit != lst.end(); lit++ ) {
        if(*lit == x){
            return lit;
        }
    }
    return lst.end();
}

bool IsEven(int i){
    if(i%2 == 0){
        return true;
    }
    return false;
}

list<int>::const_iterator listFind(const list<int>& lst, int x){
    list<int>::const_iterator cit;
    cout << "My Find Function" << endl;
    for(cit = lst.begin(); cit != lst.end(); cit++){
        if(*cit == x){
            return cit;
        }
    }
    return lst.end();
}
//auto findItem2(const list<int>& lst, int x){

template <typename T, typename U>
T listFind2(T start, T stop, U num) {
    for (T p = start; p != stop; ++p) {
        if (*p == num) {
            return p;
        }
    }
    return stop;
}


int main() {
    cout << "Task 1" << endl;
    vector<int> vec;

    cout << "Task 2" << endl;
    for(size_t i = 0; i < 10; i++){ vec.push_back(i); }
    for(int x : vec){ cout << x << " "; }
    cout << endl << endl;

    cout << "Task 3" << endl;
    list<int> lst (vec.begin(), vec.end());
    for(int x : lst){ cout << x << " ";}
    cout << endl << endl;

    cout << "Task 4" << endl;
    for(size_t i = 0; i < vec.size(); i++){
        if(i%2 == 0){
            cout << vec[i] << " ";
        }
    }
    cout << endl << endl;
    //Task 5
    //for(size_t i = 0; i < lst.size(); i++){
    //     if(i% 2 == 0){
    //      cout << lst[i] << " ";
    //     }
    //}

    cout << "Task 6" << endl;
    vector<int>::iterator vit;
    int i = 0;
    for(vit = vec.begin(); vit != vec.end(); vit++, i++){
        if(i % 2 == 0){
            cout << *vit << " ";
        }
    }
    cout << endl << endl;

    cout << "Task 7" << endl;
    list<int>::iterator lit;
    int x = 0;
    for(lit = lst.begin(); lit != lst.end(); lit++, x++){
        if(i % 2 == 0){
            cout << *lit << " ";
        }
    }
    cout << endl << endl;

    cout << "Task 8" << endl;
    lst.push_back(5);
    lst.sort();
    for(int x : lst){
        cout << x << " ";
    }
    cout << endl << endl;

    cout << "Task 9" << endl;
    printList(lst);
    cout << endl;

    cout << "Task 10" << endl;
    printList2(lst);
    cout << endl;

    cout << "Task 11" << endl;
    printListAuto(lst);
    cout << endl;

    cout << "Task 12" << endl;
    cout << *findItem(lst, 4);
    cout << endl;

    cout << "Task 13" << endl;
    cout << "Doesn't support" << endl << endl;

    cout << "Task 14" << endl;
    list<int>::iterator p = find(lst.begin(), lst.end(), 4);
    cout << *p << endl << endl;

    cout << "Task 15" << endl;
    list<int>::iterator pit = find_if(lst.begin(), lst.end(), IsEven);
    cout << *pit << endl << endl;

    cout << "Task 16" << endl;
    f eff;
    list<int>::iterator pitt = find_if(lst.begin(), lst.end(), eff);
    cout << *pit << endl << endl;

    cout << "Task 17" << endl;
    list<int>::iterator pittt = find_if(lst.begin(), lst.end(),[](int i){return i % 2 == 0;});
    cout << endl << endl;

    cout << "Task 18" << endl;
    int arr[8];
    copy(lst.begin(), lst.end(), arr);
    for(int x : arr){
        cout << x << " ";
    }
    cout << endl;
    cout << *find(arr, arr + 8, 3) << endl << endl;

    cout << "Task 19" << endl;
    cout << *listFind(lst, 4);

    cout << "Task 20" << endl;
    cout << *listFind2(lst.begin(), lst.end(), 4);
    cout << endl << endl;

    cout << "Task 21" << endl;
/*
    ifstream ifs("\\\\WILLIAMSPC\\Users\\William\\CLionProjects\\rec13\\pooh-nopunc.txt");
    if(!ifs){
        cout << "File couldn't be opened" << endl;
        exit(1);
    }
    vector<string> svec;
    string s;
    while(ifs >> s){
        if(find(svec.begin(), svec.end(), s) == svec.end()){
            svec.push_back(s);
        }
        else{
            continue;
        }
    }
    for(string x : svec){
        cout << x << " ";
    }
    cout << endl << endl;*/

    /*cout << "Task 22" << endl;
    ifstream ifs("\\\\WILLIAMSPC\\Users\\William\\CLionProjects\\rec13\\pooh-nopunc.txt");
    if(!ifs){
        cout << "File couldn't be opened" << endl;
        exit(1);
    }
    string s;
    set<string> sets;
    while(ifs >> s){
        sets.insert(s);
    }
    for(string x : sets){
        cout << x << " ";
    }
    cout << endl << endl;*/

    cout << "Task 23" << endl;
    ifstream ifs("\\\\WILLIAMSPC\\Users\\William\\CLionProjects\\rec13\\pooh-nopunc.txt");
    if(!ifs){
        cout << "File couldn't be opened" << endl;
        exit(1);
    }
    string s;
    map<string, vector<int>> wordMap;
    int position = 0;
    while(ifs >> s){
        wordMap[s].push_back(position);
        position++;
    }
    for(auto entry : wordMap){
        cout << entry.first << endl << "    ";
        for(size_t i = 0; i < entry.second.size(); i++){
            cout << entry.second[i] << " ";
        }
        cout << endl;
    }
};
