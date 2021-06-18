#include <iostream>
#include <vector>
#include <NTL/ZZ.h>
#include <stdlib.h>
#include <time.h>

using namespace std;
using namespace NTL;

ZZ moduloZZ(ZZ a, ZZ b)
{
    ZZ r;
    r = a - b * (a / b);
    r = r + (r < 0) * b;
    return r;
}

ZZ moduloZZ2(ZZ a)
{
    ZZ r = a - ((a >> 1) << 1);
    r = r + ((r < 0) << 1);
    return r;
}


int Contador_Bucles=0;

ZZ mcd(ZZ x, ZZ y)
{
    ZZ modulo;
    while (y != 0)
    {
        Contador_Bucles++;
        modulo = moduloZZ(x, y);
        x = y;
        y = modulo;
    }
    return x;
}

ZZ rtlexponentiation(ZZ b, ZZ e, ZZ m)
{
    ZZ A = conv<ZZ>("1");
    ZZ S = b;

    while (e != 0)
    {
        Contador_Bucles++;
        if (moduloZZ2(e) == 1)
        {
            A = moduloZZ(A * S, m);
        }
        e = e >> 1;
        if (e != 0) S = moduloZZ(S * S,m);
    }
    return A;
}

ZZ phi(ZZ x) {
    ZZ i; ZZ counter; counter=0;
    for (i = 1; i < x ; i++) {
        Contador_Bucles++;
        if (mcd(i, x)==ZZ(1)) {
            counter++;
        }
    }
    return counter;
}

bool euler(ZZ x, ZZ y){
    ZZ res;
    ZZ gcd;

    srand(time(NULL));
    gcd=mcd(x,y);

    if(gcd!=1){
        return false;
    }

    ZZ prime=ZZ(phi(x));
    cout<<"phi: "<<prime<<endl;
    res=rtlexponentiation(y,prime,x);
    cout<<res<<endl;
    if(res==1){
        return true;
    }
    else{
        return false;
    }
}

int main()
{
    ZZ a, b;
    a=RandomPrime_ZZ(16); b=RandomPrime_ZZ(16);
    a=13;b=12;
    bool ftry=euler(b,a);
    cout<<ftry;
    //std::cout<<"\n Bucles: "<<Contador_Bucles;

}
