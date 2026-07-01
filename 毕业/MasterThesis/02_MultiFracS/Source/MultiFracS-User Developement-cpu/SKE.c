#include "Real.h"  
#include "SKE.h"
#include <math.h>
#include <stdio.h>

#define Length(x1,y1,x2,y2) sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1))
#define V2DCro(s,x1,y1,x2,y2) {s=x1*y2-x2*y1;}
#define V2DNor(s,x1,y1) \
              {(s)=sqrt((x1)*(x1)+(y1)*(y1));   \
              if((s)> SmallPositiveNumber)(x1)=(x1)/(s);  \
              if((s)> SmallPositiveNumber)(y1)=(y1)/(s);  }

void SKE_2D(Real x[3], Real y[3], Real W)
{
    int i;
    Real a, b, c, m, n, p, q, s, t, l, xt[3], yt[3], xc[3], yc[3];
    Real x_tem[4];
    Real y_tem[4];

    for (i = 0; i < 3; i++)
    {
        x_tem[i] = x[i];
        y_tem[i] = y[i];
    }
    x_tem[3] = x[0];
    y_tem[3] = y[0];

    a = Length(x_tem[1], y_tem[1], x_tem[2], y_tem[2]);
    b = Length(x_tem[0], y_tem[0], x_tem[2], y_tem[2]);
    c = Length(x_tem[0], y_tem[0], x_tem[1], y_tem[1]);
    
    m = (a * x_tem[0] + b * x_tem[1] + c * x_tem[2]) / (a + b + c);
    n = (a * y_tem[0] + b * y_tem[1] + c * y_tem[2]) / (a + b + c);

    for (i = 0; i < 3; i++)
    {
        p = Length(x_tem[i], y_tem[i], x_tem[i + 1], y_tem[i + 1]);
        q = Length(x_tem[i], y_tem[i], m, n);
        xt[i] = m - x_tem[i];
        yt[i] = n - y_tem[i];
        xc[i] = x_tem[i + 1] - x_tem[i];
        yc[i] = y_tem[i + 1] - y_tem[i];
        V2DCro(s, xc[i], yc[i], xt[i], yt[i]);
        V2DNor(t, xt[i], yt[i]);

        if (s >  SmallPositiveNumber)
        {
            l = W * p * q / s;
            x[i] = x_tem[i] - xt[i] * l;
            y[i] = y_tem[i] - yt[i] * l;

        }
    }
}

void SKE_3D(Real x[4], Real y[4], Real z[4], Real W)
{
    if (fabs(W) < 1e-15) return;

    //求解坐标
    Real x_new[4], y_new[4], z_new[4];

    Real a1, a2, a3, a4, a5, a6;
    Real a, b, c, d, e, f;
    Real R, V;
    Real k;
    Real C0, C1, C2, C3;
    Real S0, S1, S2, S3;
    Real S;
    Real Px, Py, Pz;

    //棱长
    a1 = sqrt((x[0] - x[1]) * (x[0] - x[1]) + (y[0] - y[1]) * (y[0] - y[1]) + (z[0] - z[1]) * (z[0] - z[1]));
    a2 = sqrt((x[1] - x[2]) * (x[1] - x[2]) + (y[1] - y[2]) * (y[1] - y[2]) + (z[1] - z[2]) * (z[1] - z[2]));
    a3 = sqrt((x[2] - x[3]) * (x[2] - x[3]) + (y[2] - y[3]) * (y[2] - y[3]) + (z[2] - z[3]) * (z[2] - z[3]));
    a4 = sqrt((x[3] - x[0]) * (x[3] - x[0]) + (y[3] - y[0]) * (y[3] - y[0]) + (z[3] - z[0]) * (z[3] - z[0]));
    a5 = sqrt((x[2] - x[0]) * (x[2] - x[0]) + (y[2] - y[0]) * (y[2] - y[0]) + (z[2] - z[0]) * (z[2] - z[0]));
    a6 = sqrt((x[1] - x[3]) * (x[1] - x[3]) + (y[1] - y[3]) * (y[1] - y[3]) + (z[1] - z[3]) * (z[1] - z[3]));

    //棱长及对边平方

    a = a1 * a1;
    b = a5 * a5;
    c = a4 * a4;
    d = a3 * a3;
    e = a6 * a6;
    f = a2 * a2;

    //四面体面积

    V = sqrt(a * d * (b + c + e + f - a - d) + b * e * (a + c + d + f - b - e) + c * f * (a + b + d + e - c - f) - a * b * f - b * c * d - c * a * e - d * e * f) / 12;


    //顶点相对应的各个面半周长

    C0 = (a2 + a3 + a6) / 2;
    C1 = (a3 + a4 + a5) / 2;
    C2 = (a1 + a4 + a6) / 2;
    C3 = (a1 + a2 + a5) / 2;

    //顶点相对应的各个面面积

    S0 = sqrt(C0 * (C0 - a2) * (C0 - a3) * (C0 - a6));
    S1 = sqrt(C1 * (C1 - a3) * (C1 - a4) * (C1 - a5));
    S2 = sqrt(C2 * (C2 - a1) * (C2 - a4) * (C2 - a6));
    S3 = sqrt(C3 * (C3 - a1) * (C3 - a2) * (C3 - a5));

    //顶点相对应的各个面面积之和

    S = S0 + S1 + S2 + S3;

    //内切球半径

    R = (3 * V) / S;

    k = 1 + (W / (R));

    //四面体中心

    Px = (S0 * x[0] + S1 * x[1] + S2 * x[2] + S3 * x[3]) / S;
    Py = (S0 * y[0] + S1 * y[1] + S2 * y[2] + S3 * y[3]) / S;
    Pz = (S0 * z[0] + S1 * z[1] + S2 * z[2] + S3 * z[3]) / S;

    for (int i = 0; i < 4; i++)
    {
        x_new[i] = Px + k * (x[i] - Px);
        y_new[i] = Py + k * (y[i] - Py);
        z_new[i] = Pz + k * (z[i] - Pz);
    }


    //将新坐标赋给原有坐标

    for (int i = 0; i < 4; i++)
    {
        x[i] = x_new[i];
        y[i] = y_new[i];
        z[i] = z_new[i];
    }
}