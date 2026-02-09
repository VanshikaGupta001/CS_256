#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>
#include <algorithm>

using namespace std;

long double evalTerm(string term, long double n) {
    long double val = 1.0;

    size_t numEnd = 0;
    if (isdigit(term[0])) {
        val *= stold(term, &numEnd);
    }

    size_t logPos = term.find("log");
    if (logPos != string::npos) {
        long double logPower = 1.0;
        size_t caretPos = term.find('^', logPos);
        size_t nPos = term.find('n', logPos); 
        if (caretPos != string::npos && caretPos < nPos) {
            logPower = stold(term.substr(caretPos + 1));
        }
        val *= pow(log2(n), logPower);
        
        if (nPos != string::npos) term[nPos] = ' '; 
    }

    size_t nPos = term.find('n');
    if (nPos != string::npos) {
        long double nPower = 1.0;
        // Check for exponent after n ( n^2)
        size_t caretPos = term.find('^', nPos);
        if (caretPos != string::npos) {
            nPower = stold(term.substr(caretPos + 1));
        }
        val *= pow(n, nPower);
    }

    return val;
}

long double evaluate(string s, long double n) {
    long double total = 0;
    string term;
    for (char &c : s) if (c == '+') c = ' '; 
    stringstream ss(s);
    while (ss >> term) {
        total += evalTerm(term, n);
    }
    return total;
}

int main() {
    string f_str, g_str;
    if (!getline(cin, f_str)) return 0;
    getline(cin, g_str);

    long double n1 = 1000.0;
    long double n2 = 100000000.0; 

    long double r1 = evaluate(f_str, n1) / evaluate(g_str, n1);
    long double r2 = evaluate(f_str, n2) / evaluate(g_str, n2);

    long double M = r2 / r1;

    bool is_BigO = false;
    bool is_Omega = false;

    
    if (M < 0.9) {
        is_BigO = true;
        is_Omega = false;
    } else if (M > 1.1) {
        is_BigO = false;
        is_Omega = true;
    } else {
        is_BigO = true;
        is_Omega = true;
    }
    
    if (r2 < 1e-9) { is_BigO = true; is_Omega = false; }
    if (r2 > 1e9)  { is_BigO = false; is_Omega = true; }

    cout << (is_BigO ? "YES" : "NO") << endl;
    cout << (is_Omega ? "YES" : "NO") << endl;
    cout << ((is_BigO && is_Omega) ? "YES" : "NO") << endl;

    return 0;
}