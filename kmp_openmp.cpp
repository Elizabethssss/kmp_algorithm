#include <iostream>
#include <string>
#include <vector>  
#include <fstream>
#include <chrono>
#include <omp.h>

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
    int filesCount;
    cout << "Enter t:";
    cin >> t;
    cout << "Enter number of files to process:";
    cin >> filesCount;
    long counter = 0;
    std::vector<std::string> filesList(filesCount);
    for (int i = 1; i <= filesCount; ++i)
    {
        ifstream f("input" + std::to_string(i) + ".txt");
        string s((std::istreambuf_iterator<char>(f)), (std::istreambuf_iterator<char>()));
        filesList.push_back(s);
    }

    std::chrono::duration<double> elapsed_seconds{};

    auto start = std::chrono::steady_clock::now();
#pragma omp parallel for default(none) shared(counter, t, filesList)
    
        for (int i = 0; i < filesList.size(); ++i)
        {
            vector<int> pi = prefix_function(t + '#' + filesList[i]);
            int t_len = t.length();
            for (int j = 0; j < filesList[i].length(); ++j)
            {
                if (pi[t_len + 1 + j] == t_len)
                {
                    //  cout << "s[" << i - t_len + 1 << ".." << i << "] = t" << endl;
                    counter++;
                }
            }
        }
    
    auto end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    cout << counter << endl;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
}