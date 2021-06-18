#include <NTL/ZZ.h>
#include <vector>
#include <iostream>

using namespace std;
using namespace NTL;

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

class blumblumshubRNG
{
    public:
        ZZ seed;
        ZZ m;

        blumblumshubRNG(time_t initialSeed, ZZ uM):
            m(uM)
        {
            seed = (long)initialSeed;
            seed = moduloZZ(seed, m);
            while (mcdZZ(seed, m) != 1 && seed > 1)
            {
                seed = moduloZZ(seed + seed + 1, m);
            }
        }

        blumblumshubRNG(int bits)
        {
            //offset = (2 << (bits - 2));
            //m = (2 << (bits - 1)) - offset;
            //seed = (long)time(NULL);
            //seed = moduloZZ(seed, m);
            //cout << "offset: " << offset << endl;
            //cout << "m: " << m << endl;
            //cout << "seed: " << seed << endl;
        }

        ZZ next()
        {
            ZZ temp = moduloZZ(seed * seed, m);
            while (temp > 1)
            {
                temp = moduloZZ(temp * temp + 1, m);
            }
            seed = temp;
            return seed;
        }
};

int main()
{
    ZZ mSeed = conv<ZZ>("53419");
    blumblumshubRNG myObj(time(NULL), mSeed);
    for (int i = 0; i < 5; i++)
    {
        cout << myObj.next() << endl;
    }
}
