#include <iostream>
#include <string>
#include <vector>  
#include <fstream>
#include <chrono>

using namespace std;

vector<int> prefix_function(const string& s) {
    vector<int> pi(s.length(), 0);

    for (int i = 1; i < s.length(); i++) {
        int j = pi[i - 1];

        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }

        if (s[i] == s[j]) {
            pi[i] = j + 1;
        }
        else {
            pi[i] = j;
        }
    }

    return pi;
}

int main() {
    string t;
    ifstream f("input2.txt");
    string s((std::istreambuf_iterator<char>(f)), (std::istreambuf_iterator<char>()));
   
    cout << "Enter t:";
    cin >> t;
    
    auto start = std::chrono::steady_clock::now();
    vector<int> pi = prefix_function(t + '#' + s);

    int t_len = t.length();
    long counter = 0;
    for (int i = 0; i < s.length(); i++) {
        if (pi[t_len + 1 + i] == t_len) {
          //  cout << "s[" << i - t_len + 1 << ".." << i << "] = t" << endl;
            counter++;
        }
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    cout << counter << endl;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
}