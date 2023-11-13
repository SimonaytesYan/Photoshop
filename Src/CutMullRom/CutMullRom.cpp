#include "CutMullRom.h"

const double kCatMullRomConst = 0.5;
const double kCatMullRomStep  = 0.005;

static double CalcNextT      (Vec2 p1, Vec2 p2, double t);
static void   CutMullRom3Vert(RenderTarget& target, Color color, double thickness,
                              Vec2 p0, Vec2 p1, Vec2 p2);
static void   CutMullRom2Vert(RenderTarget& target, Color color, double thickness,
                              Vec2 p0, Vec2 p1);
static void   CutMullRom     (RenderTarget& data, RenderTarget& tmp, Color color, double thickness,
                              Vec2 p0, Vec2 p1, Vec2 p2, Vec2 p3);

double CalcNextT(Vec2 p1, Vec2 p2, double t)
{
    return pow((p2 - p1).Length(), kCatMullRomConst) + t;
}

double LinearInterpol(double a, double b, double t)
{
    return a + t * (b - a);
}

void CutMullRom3Vert(RenderTarget& target, Color color, double thickness,
                     Vec2 p0, Vec2 p1, Vec2 p2)
{
    double t0 = 0;
    double t1 = CalcNextT(p0, p1, t0);
    double t2 = CalcNextT(p1, p2, t1);

    for (double it = 0; it <= 1; it += kCatMullRomStep)
    {
        double t = LinearInterpol(t1, t2, it);

        Vec2 a1 = (t1 - t) / (t1 - t0) * p0 + (t - t0) / (t1 - t0) * p1;
        Vec2 a2 = (t2 - t) / (t2 - t1) * p1 + (t - t1) / (t2 - t1) * p2;

        Vec2 b = (t2 - t) / (t2 - t0) * a1 + (t - t0)/ (t2 - t0) * a2;

        target.DrawCircle(b, thickness, color);
    }
}

void CutMullRom2Vert(RenderTarget& target, Color color, double thickness,
                     Vec2 p0, Vec2 p1)
{
    double t0 = 0;
    double t1 = CalcNextT(p0, p1, t0);

    for (double it = 0; it <= 1; it += kCatMullRomStep)
    {
        double t = LinearInterpol(t0, t1, it);
        Vec2 a = (t1 - t) / (t1 - t0) * p0 + (t - t0) / (t1 - t0) * p1;
        target.DrawCircle(a, thickness, color);
    }
}

void CutMullRom(RenderTarget& data, RenderTarget& tmp, Color color, double thickness,
                   Vec2 p0, Vec2 p1, Vec2 p2, Vec2 p3)
{
    double t0 = 0;
    double t1 = CalcNextT(p0, p1, t0);
    double t2 = CalcNextT(p1, p2, t1);
    double t3 = CalcNextT(p2, p3, t2);

    tmp.Clear(Color(0, 0, 0, 0));
    for (double it = 0; it <= 1; it += kCatMullRomStep)
    {
        double t = LinearInterpol(t1, t2, it);

        Vec2 a1 = (t1 - t) / (t1 - t0) * p0 + (t - t0) / (t1 - t0) * p1;
        Vec2 a2 = (t2 - t) / (t2 - t1) * p1 + (t - t1) / (t2 - t1) * p2;
        Vec2 a3 = (t3 - t) / (t3 - t2) * p2 + (t - t2) / (t3 - t2) * p3;

        Vec2 b1 = (t2 - t) / (t2 - t0) * a1 + (t - t0)/ (t2 - t0) * a2;
        Vec2 b2 = (t3 - t) / (t3 - t1) * a2 + (t - t1)/ (t3 - t1) * a3;

        Vec2 c  = (t2 - t) / (t2 - t1) * b1 + (t - t1) / (t2 - t1) * b2;
        data.DrawCircle(c, thickness, color);
    }
    CutMullRom3Vert(tmp, color, thickness, p1, p2, p3);
}

void DrawUsingCatMullRom(RenderTarget& data, RenderTarget& tmp, Color color,
                         double thickness, List<Vec2> &vertexes)
{
    int index = vertexes.Begin();
    Vec2 p0 = vertexes[index].val; 
    if (vertexes.size == 1)
    {
        data.DrawCircle(p0, thickness, color);
        return;
    }

    index = vertexes.Iterate(index);
    Vec2 p1 = vertexes[index].val;
    if (vertexes.size == 2)
    {
        CutMullRom2Vert(tmp, color, thickness, p0, p1);
        return;
    }

    index = vertexes.Iterate(index);
    Vec2 p2 = vertexes[index].val;
    if (vertexes.size == 3)
    {
        tmp.Clear(Color(0, 0, 0, 0));
        CutMullRom3Vert(tmp,  color, thickness, p0, p1, p2);
        CutMullRom3Vert(data, color, thickness, p2, p1, p0);
        return;
    }

    index = vertexes.Iterate(index);
    Vec2 p3 = vertexes[index].val;
    CutMullRom(data, tmp, color, thickness, p0, p1, p2, p3);
}

void DrawTmpToData(RenderTarget& data, RenderTarget& tmp, Color color, double thickness,
                   List<Vec2> &vertexes)
{
    tmp.Clear(Color(0, 0, 0, 0));
    if (vertexes.size < 2)
        return;
    
    int index = vertexes.Begin();
    Vec2 p0 = vertexes[index].val;
    index = vertexes.Iterate(index);
    Vec2 p1 = vertexes[index].val;
    if (vertexes.size == 2)
    {
        CutMullRom2Vert(data, color, thickness, p0, p1);
        return;
    }

    index = vertexes.Iterate(index);
    Vec2 p2 = vertexes[index].val;
    if (vertexes.size == 3)
    {
        CutMullRom3Vert(data, color, thickness, p0, p1, p2);
        CutMullRom3Vert(data, color, thickness, p2, p1, p0);
        return;
    }

    index = vertexes.Iterate(index);
    Vec2 p3 = vertexes[index].val;
    CutMullRom3Vert(data,  color, thickness, p1, p2, p3);
}

