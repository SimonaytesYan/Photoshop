#include "CutMullRom.h"

namespace sym_plugin
{
    const double kCatMullRomConst = 0.5;
    const double kCatMullRomStep  = 0.01;

    static double CalcNextT      (plugin::Vec2 p1, plugin::Vec2 p2, double t);
    static void   CutMullRom3Vert(plugin::RenderTargetI* target, plugin::Color color, double thickness,
                                plugin::Vec2 p0, plugin::Vec2 p1, plugin::Vec2 p2);
    static void   CutMullRom2Vert(plugin::RenderTargetI* target, plugin::Color color, double thickness,
                                plugin::Vec2 p0, plugin::Vec2 p1);
    static void   CutMullRom     (plugin::RenderTargetI* data, plugin::Color color, double thickness,
                                plugin::Vec2 p0, plugin::Vec2 p1, plugin::Vec2 p2, plugin::Vec2 p3);

    double CalcNextT(plugin::Vec2 p1, plugin::Vec2 p2, double t)
    {
        return pow((p2 - p1).Length(), kCatMullRomConst) + t;
    }

    double LinearInterpol(double a, double b, double t)
    {
        return a + t * (b - a);
    }

    void DrawPoint(plugin::RenderTargetI* target, plugin::Color color, 
                   double thickness, plugin::Vec2 point)
    {
        plugin::Color color_i = color;

        plugin::Vec2 gen_size(thickness, thickness);
        target->drawEllipse(point, gen_size, color_i);
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

            DrawPoint(target, color, thickness, b);
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
            DrawPoint(target, color, thickness, a);
        }
    }

    void CutMullRom(plugin::RenderTargetI* target, plugin::Color color, double thickness,
                    plugin::Vec2 p0, plugin::Vec2 p1, plugin::Vec2 p2, plugin::Vec2 p3)
    {
        double t0 = 0;
        double t1 = CalcNextT(p0, p1, t0);
        double t2 = CalcNextT(p1, p2, t1);
        double t3 = CalcNextT(p2, p3, t2);

        for (double it = 0; it <= 1; it += kCatMullRomStep)
        {
            double t = LinearInterpol(t1, t2, it);

            plugin::Vec2 a1 = (t1 - t) / (t1 - t0) * p0 + (t - t0) / (t1 - t0) * p1;
            plugin::Vec2 a2 = (t2 - t) / (t2 - t1) * p1 + (t - t1) / (t2 - t1) * p2;
            plugin::Vec2 a3 = (t3 - t) / (t3 - t2) * p2 + (t - t2) / (t3 - t2) * p3;

            plugin::Vec2 b1 = (t2 - t) / (t2 - t0) * a1 + (t - t0)/ (t2 - t0) * a2;
            plugin::Vec2 b2 = (t3 - t) / (t3 - t1) * a2 + (t - t1)/ (t3 - t1) * a3;

            plugin::Vec2 c  = (t2 - t) / (t2 - t1) * b1 + (t - t1) / (t2 - t1) * b2;

            DrawPoint(target, color, thickness, c);
        }
    }

    void DrawUsingCatMullRom_plugin(plugin::RenderTargetI* target, plugin::Color color,
                                    double thickness, List<plugin::Vec2> &vertexes)
    {
        int index = vertexes.Begin();
        plugin::Vec2 p0 = vertexes[index].val; 
        if (vertexes.size == 1)
        {
            DrawPoint(target, color, thickness, p0);
            return;
        }

        index = vertexes.Iterate(index);
        plugin::Vec2 p1 = vertexes[index].val;
        if (vertexes.size == 2)
        {
            CutMullRom2Vert(target, color, thickness, p0, p1);
            return;
        }

        index = vertexes.Iterate(index);
        plugin::Vec2 p2 = vertexes[index].val;
        if (vertexes.size == 3)
        {
            CutMullRom3Vert(target,  color, thickness, p0, p1, p2);
            CutMullRom3Vert(target, color, thickness, p2, p1, p0);
            return;
        }

        // Draw line between the first and the second points 
        CutMullRom3Vert(target, color, thickness, p2, p1, p0);

        index = vertexes.Iterate(index);
        plugin::Vec2 p3;

        for (index; index != -1; index = vertexes.Iterate(index))
        {
            p3 = vertexes[index].val;
            CutMullRom(target, color, thickness, p0, p1, p2, p3);
            
            p0 = p1;
            p1 = p2;
            p2 = p3;
        }

        // Draw line to the last point
        CutMullRom3Vert(target, color, thickness, p0, p1, p2);
    }
}
