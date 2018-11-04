#include <bits/stdc++.h>

using namespace std;

long int nearestnice(double a) {
    if (a < 10) {
        return floor(a);
    }
    else if (a >= 10 && a < 100) {
        if ((int)a%5 == 0)
            return (int)a;
        return ((int)a/5)*5;
    }
    else if (a >= 100 && a < 250) {
        if ((int)a%25 == 0)
            return (int)a;
        return ((int)a/25)*25;
    }
    else if (a >= 250 && a < 1000) {
        if ((int)a%50 == 0)
            return (int)a;
        return ((int)a/50)*50;
    }
    return 1000*nearestnice(a/1000);
}

int main() {
    int b = 2000; // total prize pool; input
    int e = 6; // 2*entry fee; input
    int n = 50; // number of entrants to win a non zero amount; input
    int p0 = 300; // payout to tournament winner; input
    // 0.05*b <= p0 <= 0.5*b; p0 == 0.15*b is standard
    // typically n == 0.25*total entrants
    
    int p[n]; // prize at place i is P[i]
    
    double diff = 10.0;
    double eps = pow(10.0, -8);
    double a = 0.0;
    double c = 20.0;
    double alpha = (a+c)/2;
    double s = 0.0;
    while(abs(diff) >= eps) {
        s = 0.0;
        for(unsigned i = 0; i < n; ++i) {
            s += (p0 - e)/(double)pow(i+1, alpha);
        }
        diff = b - n*e -s;
        if (diff > 0) {
            c = alpha;
            alpha = (a+c)/2;
        }
        else if (diff < 0) {
            a = alpha;
            alpha = (a+c)/2;
        }
        else {
            break;
        }
    }

    cout << "alpha = " << alpha << endl;

    double pi[n];
    double sanity = 0;
    cout << "pi: \n";
    for(unsigned i = 0; i < n; ++i) {
        pi[i] = (double)e + (p0 - e)/(double)pow(i+1, alpha);
        cout << pi[i] << " ";
        sanity += pi[i];
    }
    cout << "\n";
    cout << "|sum(pi) - b| = " << abs(b - sanity) << endl;


    double l = 0.0;
    p[0] = pi[0];

    cout << "p: \n";
    for(unsigned i = 0; i < n; ++i) {
        p[i] = nearestnice(pi[i]);
        l += pi[i] - nearestnice(pi[i]);
        cout << p[i] << " ";
    }

    int r = 0;
    for(unsigned i = 0; i < n; ++i) {
        if (i == 0 || i == n-1) {
            ++r;
            continue;
        }
        if (p[i] != p[i-1]){
            ++r;
        }
    }

    cout << "\nleftover = " << l << endl;

    int bs[r];
    for(unsigned i = 0; i < r; ++i) {
        if (i < 4){
            bs[i] = 1;
        }
        else {
            bs[i] = -1;
        }
    }

    a = 1.0;
    c = 20.0;
    double beta = (a + c)/2;
    diff = 10.0;
    while (abs(diff) >= eps) {
        s = 0.0;
        for(unsigned i = 0; i < r-4; ++i) {
            s += pow(beta, i+1);
        }
        diff = n - 4 - s;
        if (diff > 0) {
            a = beta;
            beta = (a+c)/2;
        }
        else if (diff < 0) {
            c = beta;
            beta = (a+c)/2;
        }
        else {
            break;
        }
    }
    cout << "beta = " << beta << endl;

    if (n == 5)
        bs[4] = 1;

    int tot = 4;
    int t = -1;
    for(unsigned i = 4; i < r; ++i) {
        bs[i] = ceil(beta*bs[i-1]);
        tot += bs[i];
        if (ceil(beta*beta*bs[i])+ceil(beta*bs[i])+tot > n && ceil(beta*bs[i])+tot <= n){
            t = i+2;
            ++i;
            bs[i] = n - tot;
            break;
        }
    }

    cout << "bucket sizes: \n";
    for(unsigned i = 0; i < t; ++i) {
        cout << bs[i] << " ";
    }
    cout << "\n";
    
    // int in = 0;
    // int out = 0;
    // while(in < n) {
    //     while(out < t) {
    //         while(in < in + bs[out]) {
                
    //         }
    //     }
    // }
    
    return 0;
}
