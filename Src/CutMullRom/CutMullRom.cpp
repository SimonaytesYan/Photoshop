#include "CutMullRom.h"

const double kCatMullRomConst = 0.5;
const double kCatMullRomStep  = 0.005;

static double CalcNextT      (plugin::Vec2 p1, plugin::Vec2 p2, double t);
static void   CutMullRom3Vert(plugin::RenderTargetI* target, plugin::Color color, double thickness,
                              plugin::Vec2 p0, plugin::Vec2 p1, plugin::Vec2 p2);
static void   CutMullRom2Vert(plugin::RenderTargetI* target, plugin::Color color, double thickness,
                              plugin::Vec2 p0, plugin::Vec2 p1);
static void   CutMullRom     (plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, plugin::Color color, double thickness,
                              plugin::Vec2 p0, plugin::Vec2 p1, plugin::Vec2 p2, plugin::Vec2 p3);

double CalcNextT(plugin::Vec2 p1, plugin::Vec2 p2, double t)
{
    return pow((p2 - p1).Length(), kCatMullRomConst) + t;
}

double LinearInterpol(double a, double b, double t)
{
    return a + t * (b - a);
}

void CutMullRom3Vert(plugin::RenderTargetI* target, plugin::Color color, double thickness,
                     plugin::Vec2 p0, plugin::Vec2 p1, plugin::Vec2 p2)
{
    double t0 = 0;
    double t1 = CalcNextT(p0, p1, t0);
    double t2 = CalcNextT(p1, p2, t1);

    for (double it = 0; it <= 1; it += kCatMullRomStep)
    {
        double t = LinearInterpol(t1, t2, it);

        plugin::Vec2 a1 = (t1 - t) / (t1 - t0) * p0 + (t - t0) / (t1 - t0) * p1;
        plugin::Vec2 a2 = (t2 - t) / (t2 - t1) * p1 + (t - t1) / (t2 - t1) * p2;

        plugin::Vec2 b = (t2 - t) / (t2 - t0) * a1 + (t - t0)/ (t2 - t0) * a2;

        target->drawEllipse(b, plugin::Vec2(thickness/2, thickness/2), color);
    }
}

void CutMullRom2Vert(plugin::RenderTargetI* target, plugin::Color color, double thickness,
                     plugin::Vec2 p0, plugin::Vec2 p1)
{
    double t0 = 0;
    double t1 = CalcNextT(p0, p1, t0);

    for (double it = 0; it <= 1; it += kCatMullRomStep)
    {
        double t = LinearInterpol(t0, t1, it);
        plugin::Vec2 a = (t1 - t) / (t1 - t0) * p0 + (t - t0) / (t1 - t0) * p1;
        target->drawEllipse(a, plugin::Vec2(thickness/2, thickness/2), color);
    }
}

void CutMullRom(plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, plugin::Color color, double thickness,
                plugin::Vec2 p0, plugin::Vec2 p1, plugin::Vec2 p2, plugin::Vec2 p3)
{
    double t0 = 0;
    double t1 = CalcNextT(p0, p1, t0);
    double t2 = CalcNextT(p1, p2, t1);
    double t3 = CalcNextT(p2, p3, t2);

    ((RenderTarget*)tmp)->clear(plugin::Color(0, 0, 0, 0));
    for (double it = 0; it <= 1; it += kCatMullRomStep)
    {
        double t = LinearInterpol(t1, t2, it);

        plugin::Vec2 a1 = (t1 - t) / (t1 - t0) * p0 + (t - t0) / (t1 - t0) * p1;
        plugin::Vec2 a2 = (t2 - t) / (t2 - t1) * p1 + (t - t1) / (t2 - t1) * p2;
        plugin::Vec2 a3 = (t3 - t) / (t3 - t2) * p2 + (t - t2) / (t3 - t2) * p3;

        plugin::Vec2 b1 = (t2 - t) / (t2 - t0) * a1 + (t - t0)/ (t2 - t0) * a2;
        plugin::Vec2 b2 = (t3 - t) / (t3 - t1) * a2 + (t - t1)/ (t3 - t1) * a3;

        plugin::Vec2 c  = (t2 - t) / (t2 - t1) * b1 + (t - t1) / (t2 - t1) * b2;

        data->drawEllipse(c, plugin::Vec2(thickness/2, thickness/2), color);
    }
    CutMullRom3Vert(tmp, color, thickness, p1, p2, p3);
}

void DrawUsingCatMullRom(plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, plugin::Color color,
                         double thickness, List<plugin::Vec2> &vertexes)
{
    int index = vertexes.Begin();
    plugin::Vec2 p0 = vertexes[index].val; 
    if (vertexes.size == 1)
    {
        data->drawEllipse(p0, plugin::Vec2(thickness/2, thickness/2), color);
        return;
    }

    index = vertexes.Iterate(index);
    plugin::Vec2 p1 = vertexes[index].val;
    if (vertexes.size == 2)
    {
        CutMullRom2Vert(tmp, color, thickness, p0, p1);
        return;
    }

    index = vertexes.Iterate(index);
    plugin::Vec2 p2 = vertexes[index].val;
    if (vertexes.size == 3)
    {
        ((RenderTarget*)tmp)->clear(plugin::Color(0, 0, 0, 0));
        CutMullRom3Vert(tmp,  color, thickness, p0, p1, p2);
        CutMullRom3Vert(data, color, thickness, p2, p1, p0);
        return;
    }

    index = vertexes.Iterate(index);
    plugin::Vec2 p3 = vertexes[index].val;
    CutMullRom(data, tmp, color, thickness, p0, p1, p2, p3);
}

void DrawTmpToData(plugin::RenderTargetI* data, plugin::RenderTargetI* tmp, plugin::Color color, double thickness,
                   List<plugin::Vec2> &vertexes)
{
    ((RenderTarget*)tmp)->clear(plugin::Color(0, 0, 0, 0));
    if (vertexes.size < 2)
        return;
    
    int index = vertexes.Begin();
    plugin::Vec2 p0 = vertexes[index].val;
    index = vertexes.Iterate(index);
    plugin::Vec2 p1 = vertexes[index].val;
    if (vertexes.size == 2)
    {
        CutMullRom2Vert(data, color, thickness, p0, p1);
        return;
    }

    index = vertexes.Iterate(index);
    plugin::Vec2 p2 = vertexes[index].val;
    if (vertexes.size == 3)
    {
        CutMullRom3Vert(data, color, thickness, p0, p1, p2);
        CutMullRom3Vert(data, color, thickness, p2, p1, p0);
        return;
    }

    index = vertexes.Iterate(index);
    plugin::Vec2 p3 = vertexes[index].val;
    CutMullRom3Vert(data,  color, thickness, p1, p2, p3);
}

