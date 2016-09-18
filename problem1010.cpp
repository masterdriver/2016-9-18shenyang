#include <cstdio>
#include <cmath>
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
long long int prime[1362205], v[21544350],q,p;
bool boolflag[21544349];


inline long long int pi(long long int n, long long int len)
{
     long long int i, l, h;
     i = lower_bound(prime, prime + len, n) - prime;
     return i;
}

inline long long int phi(long long int x, long long int a, long long int& m)
{    
     if (a == m) return (x / q) * p + v[x % q];
     else if (x < prime[a-1]) return 1;
     else return phi(x, a-1, m) - phi(x/prime[a-1], a-1, m);
}

long long int get(long long int n)
{
     q = p = 1;
     long long int j, m = 7;
     long long int len, len2, len3,flag,boolflaglength,countn,result,s;
     countn = result = s = 0;
     if(n < 10000) boolflaglength = 10002;
     else boolflaglength = (exp(2.0 / 3 * log(n)) + 1);
     flag = sqrt(boolflaglength);
     for (int i = 2; i < flag; i++)
     {
         if (boolflag[i]) continue; 
         for (j = 2 * i; j < boolflaglength; j += i) boolflag[j] = 1;
     }
     boolflag[0] = boolflag[1] = 1;
     for (int i = 0; i < boolflaglength; i++) if (!boolflag[i]) countn++;
     for (int i = 0, j = 0; i < boolflaglength; i++) if (!boolflag[i]) prime[j++] = i;
     if (n < 10000) return pi(n, countn);
     len = pi(exp(1.0/3*log(n)), countn);
     len2 = pi(sqrt(n), countn);
     len3 = pi(boolflaglength-1, countn);
     boolflaglength = boolflaglength - 2;
     flag = sqrt(n);
     for (int i = exp(1.0/3*log(n)); i <= flag; i++)
     {
         if(!boolflag[i])
         {
             while(i * boolflaglength > n)
             {
                 if (!boolflag[boolflaglength]) s++;
                 boolflaglength--;
             }
             result += s;
         }
     }
     result = (len2 - len) * len3 - result + (len * (len - 1) - len2 * (len2 - 1)) / 2;
     m = min(m, len);
     for (int i = 0; i < m; i++)
     {
         q *= prime[i];
         p *= prime[i] - 1;
     }    
     for (int i = 0; i < q; i++) v[i] = i;
     for (int i = 0; i < m; i++) for (j = q - 1; j >= 0; j--) v[j] -= v[j/prime[i]];
     result = phi(n, len, m) - result + len -1;
     return result;    
}

int main()
{    
     long long int n;
     while(~scanf("%lld", &n))
     {
         if(n == 2) printf("1\n");
         else printf("%lld\n", get(n));
     }
     return 0;
}

