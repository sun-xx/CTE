#ifndef QCALC_HPP_INCLUDED
#define QCALC_HPP_INCLUDED
#include<cmath>
float Qsqrt( float number )
{
    long i;
    float x2, y;
    const float threehalfs = 1.5F;
    x2 = number * 0.5F;
    y   = number;
    i   = * ( long * ) &y;   // evil floating point bit level hacking
    i   = 0x5f3759df - ( i >> 1 ); // what the fuck?
    y   = * ( float * ) &i;
    y   = y * ( threehalfs - ( x2 * y * y ) ); // 1st iteration
    y   = y * ( threehalfs - ( x2 * y * y ) ); // 2nd iteration, this can be removed
    return 1/y;
}

#define pi 3.141592654

float Qsin(float x)
{
    float val=0;
    if (x< -pi)
    {
        //cout<<int((-x-pi)/2*pi)<<" ";
        x+= 2*pi*int((-x-pi)/(2*pi)+1);
    }
    else if (x>  pi)
    {
        //cout<<int((x-pi)/(2*pi)+1)<<" ";
        x-= 2*pi*int((x-pi)/(2*pi)+1);
    }

    //cout<<x<<" ";
    //compute vale
    if (x< 0)
    {
        val= 1.27323954 * x+ .405284735 * x* x;

        if (val< 0)
            val= .225 * (val*-val- val) + val;
        else
            val= .225 * (val* val- val) + val;
    }
    else
    {
        val= 1.27323954 * x- 0.405284735 * x* x;

        if (val< 0)
            val= .225 * (val*-val- val) + val;
        else
            val= .225 * (val* val- val) + val;
    }

    return val;
}

float Qcos(float x)
{
    float val=0;
    x+= pi*0.5;
    if (x< -pi)
    {
        //cout<<int((-x-pi)/2*pi)<<" ";
        x+= 2*pi*int((-x-pi)/(2*pi)+1);
    }
    else if (x>  pi)
    {
        //cout<<int((x-pi)/(2*pi)+1)<<" ";
        x-= 2*pi*int((x-pi)/(2*pi)+1);
    }

    if (x< 0)
    {
        val= 1.27323954 * x+ 0.405284735 * x* x;

        if (val< 0)
            val= .225 * (val*-val- val) + val;
        else
            val= .225 * (val* val- val) + val;
    }
    else
    {
        val= 1.27323954 * x- 0.405284735 * x* x;

        if (val< 0)
            val= .225 * (val*-val- val) + val;
        else
            val= .225 * (val* val- val) + val;
    }
    return val;
}

int Qpow(int x,int n)
{
    if(n == 0) return 1;
    int t = 1;
    while(n != 0)
    {
        if(n & 1) t *= x;
        n >>= 1;
        x *= x;
    }
    return t;
}




#define ln10 2.30258509299404568401799145468
#define pi2 6.283185307179586476925286766559
// 1e-14
#define eps2 0.00000000000001
// 1e-28
#define eps1 (eps2 * eps2)

float negative_log(float q)
{
    // q in ( 0.01, 0.1 ]
    int p = 1;
    float r = q, s = q, n = q, q2 = q * q, q1 = q2 * q;
    for (p = 1; (n *= q1) > eps1; s += n, q1 *= q2)
        r += (p = !p) ? n : -n;
    float u = 1 - 2 * r, v = 1 + 2 * s, t = u / v;
    float a = 1, b = Qsqrt(1 - t * t * t * t);
    for (; a - b > eps2; b = Qsqrt(a * b), a = t) t = (a + b) / 2;
    return pi2 / (a + b) / v / v;
}

float Qloge(float x)
{
    if (x <= 0) return 0;
    if (x == 1) return 0;

    int k = 0;
    for (; x > 0.1; k++) x /= 10;
    for (; x <= 0.01; k--) x *= 10;
    return k * ln10 - negative_log(x);
}

float Qlog(float m,float N)
{
    return Qloge(N)/Qloge(m);
}
#endif // QCALC_HPP_INCLUDED
