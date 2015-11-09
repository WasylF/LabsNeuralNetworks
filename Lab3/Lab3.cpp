//solution by Wsl_F
#include <bits/stdc++.h>
#include "ReadBMP.cpp"

using namespace std;


typedef vector<int> vi;
typedef double dbl;
#define pb(x)  push_back(x)

class Nerual
{
private:
    int n;
    vector<dbl> w;
    const dbl MinW= -0.3;
    const dbl MaxW=  0.3;
    const dbl eps= 1e-6;
    double speed;
    dbl getRand(dbl minR, dbl maxR)
    {
        dbl r= rand();
        dbl length= maxR-minR;
        r/= RAND_MAX;
        r*= length;
        r+= minR;
        return r;
    }

public:
    void printW()
    {
        cout<<fixed;
        cout<<setprecision(2);
        for (int i= 0; i<=n; i++)
            cout<<w[i]<<" ";
        cout<<endl;
    }

    Nerual(int n0, double speed0)
    {
        n= n0;
        speed= speed0;
        w.clear();
        for (int i= 0; i<=n; i++)
            w.pb(getRand(MinW,MaxW));
    }

    bool learn(vi x, int y)
    {
        dbl s= 0;
        for (int i= 0; i<=n; i++)
            s+= w[i]*x[i];


        double dif= (y-s);
        if (fabs(dif) < eps) return true;
        dif/= n;
        for (int i= 0; i<=n; i++)
            w[i]+= speed*dif*x[i];
        return false;
    }

    int classify(vi x)
    {
        dbl s= 0;
        for (int i= 0; i<=n; i++)
            s+= w[i]*x[i];
        if (fabs(s)<eps*2) return 0;
        return 1;
    }
};


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout<<fixed;
    cout<<setprecision(9);

    return 0;
}
