#ifndef __PLT_LINE_HPP__
#define __PLT_LINE_HPP__

#include <vector>
#include <random>
#include <boost/tuple/tuple.hpp>
#include "gnuplot-iostream.h"
#include <functional>

namespace plt {

class line {
    friend class plotter;
public:

    enum LineType {
        SOLID = 1,    // Solid line (Gnuplot linetype 1)
        DASHED = 2,   // Dashed line (Gnuplot linetype 2)
        DOTTED = 3,   // Dotted line (Gnuplot linetype 3)
        DASH_DOT = 4  // Dash-dot line (Gnuplot linetype 4)
    };

    using point = boost::tuple<double, double>;
    static point make_point(double x, double y) { return boost::make_tuple(x, y); }

    line(const std::vector<point>& t_points = {},
        const std::string& t_color = line::random_color(),
        LineType t_type = LineType::SOLID,
        const std::string& t_width = "1.0");

    void set_points(const std::vector<point>& t_points);

    const std::vector<point>& get_points();
    std::vector<point> get_points() const;

    void set_line_type(LineType t_line_type);
    void set_line_width(const std::string& t_line_width);
    void set_line_color(const std::string& t_line_color);
    void set_line_label(const std::string& t_line_label);

    void points_from_f(std::function<double(double)> t_f, double x_start = 0.0, double x_end = 10.0, double inc = 0.1);

    static line default_from_func(std::function<double(double)> t_f, double x_start = 0.0, double x_end = 10.0, double inc = 0.1) {
        line l;
        l.points_from_f(t_f, x_start, x_end, inc);
        return l;
    }

    static std::string random_color() {
        static std::vector<std::string> colors = {"red", "blue", "orange", "black", "pink"};
        static std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<> dist(0, colors.size() - 1);
        return colors[dist(gen)];
    }

private:

    void draw(Gnuplot &gp);

    void send_data(Gnuplot &gp);

    void create_style(Gnuplot &gp);

    std::vector<boost::tuple<double, double>> m_points;
    std::string m_line_color = "red";
    LineType m_line_type = LineType::SOLID;
    std::string m_line_width = "1";
    std::string m_line_label = "";
    int m_line_style;
    static int s_style_index;
};

}

#endif