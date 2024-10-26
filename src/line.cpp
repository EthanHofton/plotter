#include <plotter/line.hpp>

namespace plt {

line::line(const std::vector<point>& t_points, const std::string& t_color, LineType t_type, const std::string& t_width) :
        m_points(t_points),
        m_line_color(t_color),
        m_line_type(t_type),
        m_line_width(t_width),
        m_line_style(++s_style_index) {}

void line::set_points(const std::vector<point>& t_points) {
    m_points = t_points;
}

const std::vector<line::point>& line::get_points() { return m_points; }
    std::vector<line::point> line::get_points() const { return m_points; }

void line::set_line_type(LineType t_line_type) { m_line_type = t_line_type; }
void line::set_line_width(const std::string& t_line_width) { m_line_width = t_line_width; }
void line::set_line_color(const std::string& t_line_color) { m_line_color = t_line_color; }
void line::set_line_label(const std::string& t_line_label) { m_line_label = t_line_label; }

void line::points_from_f(std::function<double(double)> t_f, double x_start = 0.0, double x_end = 10.0, double inc = 0.1) {
    m_points.clear();
    for (double x = x_start; x < x_end; x += inc) {
        m_points.push_back(boost::make_tuple(x, t_f(x)));
    }
}

void line::draw(Gnuplot &gp) {
    gp << "'-' with lines linestyle " << m_line_style << " title '" << m_line_label << "'";
}

void line::send_data(Gnuplot &gp) {
    gp.send1d(m_points);
}

void line::create_style(Gnuplot &gp) {
    gp << "set style line " << m_line_style 
        << " linecolor rgb '" << m_line_color 
        << "' linewidth " << m_line_width 
        << " linetype " << static_cast<int>(m_line_type) << "\n";
}

}