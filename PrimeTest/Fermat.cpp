#include <iostream>
#include <vector>
#include <NTL/ZZ.h>
#include <stdlib.h>
#include <time.h>

using namespace NTL;
using namespace std;

int Contador_Bucles=0;


ZZ moduloZZ(ZZ a, ZZ b)
{
    ZZ r;
    r = a - b * (a / b);
    r = r + (r < 0) * b;
    return r;
}

ZZ mcd(ZZ x, ZZ y)
{
    ZZ modulo;
    while (y != 0)
    {
        Contador_Bucles++;
        cout<<Contador_Bucles<<endl;
        modulo = moduloZZ(x, y);
        x = y;
        y = modulo;
    }
    return x;
}


ZZ moduloZZ2(ZZ a)
{
    ZZ r = a - ((a >> 1) << 1);
    r = r + ((r < 0) << 1);
    return r;
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

bool fermat(ZZ x){
    ZZ res;
    ZZ y;
    ZZ gcd;
    
    if(x%2==0){
        return false;
    }
    srand(time(NULL));
    y=RandomBnd(x);
    //y=ZZ(2);
    gcd=mcd(x,y);
    while(gcd!=1){
        y=RandomBnd(x);
        //y=ZZ(2);
        gcd=mcd(x,y);
    }
    res=rtlexponentiation(y,(x-1),x);
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
    //a=RandomPrime_ZZ(16); b=RandomPrime_ZZ(16);
    a=conv<ZZ>("151897494693896507253296606496578359620613544562971368358552122300052224140919178200749008454085546903774958551817795230097071132086559612888699812383058893838987762249959515677765362813325730776287673095650841037108197881834273323847366551982901038731847303018508581353753447379136613287426764568933381241907")
    ;b=conv<ZZ>("171574259887820126257812684689167982377567729921638647986380956224401762771791201109904904426873413001162519190900495748252133769719896792738834852351399713104663244201816354990327671582290818033541005191485617389625244898889168943086464803070590975781562289463722568011310167552441470376094834848741995101347");
    //cout<<a<<endl;
    bool ftry=fermat(a);
    cout<<ftry;
    //ZZ number=rtlexponentiation(b,(a-1),a);
    //cout<<number;
    std::cout<<"\n Bucles: "<<Contador_Bucles;

}
