#include "CutMullRom.h"

namespace sym_plugin
{
    const double kCatMullRomConst = 1;
    const double kCatMullRomStep  = 0.007;

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

    bool DrawPoint(plugin::RenderTargetI* target, plugin::Color color, 
                   double thickness, plugin::Vec2 point, 
                   plugin::Vec2 graph_pos, plugin::Vec2 graph_size)
    {

        plugin::Vec2 gen_size(thickness, thickness);

        if (point.x < graph_pos.x || 
            point.y < graph_pos.y || 
            point.x > graph_pos.x + graph_size.x || 
            point.y > graph_pos.y + graph_size.y)
           return true;

        if (target != nullptr)
            target->drawEllipse(point, gen_size, color);
        return false;
    }

    bool CutMullRom3Vert(plugin::RenderTargetI* target, plugin::Color color, double thickness,
                         plugin::Vec2 p0, plugin::Vec2 p1, plugin::Vec2 p2, 
                         plugin::Vec2 graph_pos, plugin::Vec2 graph_size)
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

            if (DrawPoint(target, color, thickness, b, graph_pos, graph_size))
                return true;
        }

        return false;
    }

    bool CutMullRom2Vert(plugin::RenderTargetI* target, plugin::Color color, double thickness,
                         plugin::Vec2 p0, plugin::Vec2 p1, 
                         plugin::Vec2 graph_pos, plugin::Vec2 graph_size)
    {
        double t0 = 0;
        double t1 = CalcNextT(p0, p1, t0);

        for (double it = 0; it <= 1; it += kCatMullRomStep)
        {
            double t = LinearInterpol(t0, t1, it);
            plugin::Vec2 a = (t1 - t) / (t1 - t0) * p0 + (t - t0) / (t1 - t0) * p1;

            if (DrawPoint(target, color, thickness, a, graph_pos, graph_size))
                return true;
        }

        return false;
    }

    bool CutMullRom(plugin::RenderTargetI* target, plugin::Color color, double thickness,
                    plugin::Vec2 p0, plugin::Vec2 p1, plugin::Vec2 p2, plugin::Vec2 p3, 
                    plugin::Vec2 graph_pos, plugin::Vec2 graph_size)
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

            if (DrawPoint(target, color, thickness, c, graph_pos, graph_size))
                return true;
        }
        return false;
    }

    bool DrawUsingCatMullRom_plugin(plugin::RenderTargetI* target, plugin::Color color,
                                    double thickness, List<plugin::Vec2> &vertexes, 
                                    plugin::Vec2 graph_pos, plugin::Vec2 graph_size)
    {
        int index = vertexes.Begin();
        plugin::Vec2 p0 = vertexes[index].val; 
        if (vertexes.size == 1)
        {
            return DrawPoint(target, color, thickness, p0, graph_pos, graph_size);
        }

        index = vertexes.Iterate(index);
        plugin::Vec2 p1 = vertexes[index].val;
        if (vertexes.size == 2)
        {
            return CutMullRom2Vert(target, color, thickness, p0, p1, graph_pos, graph_size);
        }

        index = vertexes.Iterate(index);
        plugin::Vec2 p2 = vertexes[index].val;
        if (vertexes.size == 3)
        {
            if (CutMullRom3Vert(target,  color, thickness, p0, p1, p2, graph_pos, graph_size))
                return true;
            return CutMullRom3Vert(target, color, thickness, p2, p1, p0, graph_pos, graph_size);
        }

        // Draw line between the first and the second points 
        if (CutMullRom3Vert(target, color, thickness, p2, p1, p0, graph_pos, graph_size))
            return true;

        index = vertexes.Iterate(index);
        plugin::Vec2 p3;

        for (index; index != -1; index = vertexes.Iterate(index))
        {
            p3 = vertexes[index].val;
            if (CutMullRom(target, color, thickness, p0, p1, p2, p3, graph_pos, graph_size))
                return true;
            
            p0 = p1;
            p1 = p2;
            p2 = p3;
        }

        // Draw line to the last point
        if (CutMullRom3Vert(target, color, thickness, p0, p1, p2, graph_pos, graph_size))
            return true;

        return false;
    }
}
