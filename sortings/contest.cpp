#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct element {
    string key;
    string value;
};

vector<element> counting_sort (const vector<element>& vec, int pos) {
    vector<int> counts(10, 0);
    for (element elem : vec) {
        counts[stoi(&elem.key.at(pos))]++;
    }

    for (int i = 1; i < 10; ++i) {
        counts[i] += counts[i-1];
    }
    vector<element> result(vec.size());
    for (int i = vec.size()-1; i >= 0; --i) {
        result[--counts[stoi(&vec[i].key.at(pos))]] = vec[i];
    }
    return result;
}

vector<element> radix_sort (const vector<element>& vec) {
    vector<element> result = vec;
    result = counting_sort(result, 1);
    result = counting_sort(result, 0);
    result = counting_sort(result, 4);
    result = counting_sort(result, 3);

    result = counting_sort(result, 9);
    result = counting_sort(result, 8);
    result = counting_sort(result, 7);
    result = counting_sort(result, 6);
    return result;
}

int main() {
    string in;
    vector<element> vec = {};
    while (getline(cin, in)) {
        if (in.empty()) break;
        in += '\t';
        string key = "";
        string value = "";
        int i = 0;
        
        string dd = "";
        string mm = "";
        string yyyy = "";

        while (in[i] != '.') {
            dd += in[i];
            i++;
        } 
        if (dd.size() < 2) {
            dd = '0' + dd;
        }
        while (in[i] != '.') {
            mm += in[i];
            i++;
        }
        if (mm.size() < 2) {
            mm = '0' + mm;
        }
        while (in[i] != '\t') {
            yyyy += in[i];
            i++;
        }
        if (yyyy.size() == 1) {
            yyyy = '0' + yyyy;
        } else if (yyyy.size() == 2) {
            yyyy = "00" + yyyy;
        } else if (yyyy.size() == 3) {
            yyyy = "000" + yyyy;
        } 
        i++;
        while (in[i] != '\t') {
            value += in[i++];
        }
        element cur;
        cur.key = dd+'.'+mm+'.'+yyyy;
        cur.value = value;
        vec.insert(vec.end(), cur);
    }
    vector<element> res = radix_sort(vec);
    for (element elem : res) {
        cout << elem.key << '\t' << elem.value << "\n";
    }
}

