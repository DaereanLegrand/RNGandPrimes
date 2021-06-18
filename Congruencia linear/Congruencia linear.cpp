#include <iostream>
#include <cstdlib>
#include<time.h>
#include <vector>
#include <NTL/ZZ.h>
#include <Windows.h>
using namespace NTL;
using namespace std;

ZZ get_coordinate()
        {
            POINT P;
            GetCursorPos(&P);

            ZZ seed = conv<ZZ>(P.x * P.y);
            return seed;
        }


ZZ moduloZZ(ZZ a, ZZ b)
{
    ZZ r;
    r = a - b * (a / b);
    r = r + (r < 0) * b;
    return r;
}

ZZ mcdZZ(ZZ a, ZZ b)
{
    ZZ res = a - ((a / b) * b);
    while (res != 0)
    {
        a = b;
        b = res;
        res = a - ((a / b) * b);
        //cout << a << " = (" << a / b << ") * " << b << " + " << res << endl;
    }
    return b;
}

ZZ rtl(ZZ b, ZZ e)
{
    ZZ A = conv<ZZ>("1");
    ZZ S = b;

    while (e != 0)
    {
        if (moduloZZ(e,ZZ(2)) == 1)
        {
            A =A * S;
        }
        e = e >> 1;
        if (e != 0) S = S * S;
    }
    return A;
}

vector<ZZ>X;

ZZ CL(ZZ semilla, ZZ a , ZZ c , ZZ m ,ZZ bits){
    ZZ random; random=semilla*get_coordinate();
    ZZ x0;
    X.push_back(random);
    while (mcdZZ(c, m) != 1)
    {
        c++;
    }
    for (int i=1;20; i++){
    X.push_back(ZZ(0));
	X[i] = X[i-1] * a + c;
	//X[i] = X[i-1] * X[i-1];
	if (X[i] > m){
		X[i] = moduloZZ(X[i], m);
    }
    while(X[i]<m>>1){
        //cout<<"\nX[i]: "<<X[i];
        X[i]=X[i]<<1;
    }

    std::cout<<"\n NUMBER: "<<X[i];

    if (X[i]==x0){
        std::cout<<"\n       Periodo: "<<i-1;
        exit(0);
    }
    if (i==1){
        x0=X[i];
	}
    }
	return semilla;
}

Getrand(ZZ bits){
    ZZ a,c,m;
    a=rtl(ZZ(3),bits/2);
    m=rtl(ZZ(2),bits)-1;
    c=1;
    ZZ semilla=ZZ(time(NULL));
    CL(semilla,a,c,m,bits);
}

int main()
{
    Getrand(ZZ(8));
}
