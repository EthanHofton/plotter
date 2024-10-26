#include <plotter/plotter.hpp>

namespace plt {

plotter::plotter(const std::string& t_title, const std::string& t_x_label, const std::string& t_y_label) :
    m_title(t_title),
    m_x_label(t_x_label),
    m_y_label(t_y_label) {}

void plotter::set_x_label(const std::string& t_x_label) { m_x_label = t_x_label; }
void plotter::set_y_label(const std::string& t_y_label) { m_y_label = t_y_label; }
void plotter::set_title(const std::string& t_title) { m_title = t_title; }
void plotter::add_line(const line& t_line) { m_lines.push_back(t_line); }
void plotter::add_line(line t_line, const std::string& t_line_label) { t_line.set_line_label(t_line_label); m_lines.push_back(t_line); }
void plotter::set_filename(const std::string& t_filename) { m_filename = t_filename; }
void plotter::set_x_range(const std::string& t_x_range) { m_x_range = t_x_range; }
void plotter::set_y_range(const std::string& t_y_range) { m_y_range = t_y_range; }
void plotter::interactive() { m_interactive = true; }

void plotter::draw() {
    if (m_lines.empty()) {
        throw std::invalid_argument("Lines required before draw");
    }

    if (m_filename.has_value()) {
        m_gp << "set terminal png\n";
        m_gp << "set output '" << m_filename.value() << "'\n";
    }

    m_gp << "set xlabel '" << m_x_label << "'\n";
    m_gp << "set ylabel '" << m_y_label << "'\n";
    m_gp << "set title '" << m_title << "'\n";

    if (m_x_range.has_value()) {
        m_gp << "set xrange" << m_x_range.value();
    }

    if (m_y_range.has_value()) {
        m_gp << "set yrange" << m_y_range.value();
    }

    for (auto& line : m_lines) {
        line.create_style(m_gp);
    }

    m_gp << "plot ";
    int i = 0;
    for (auto& line : m_lines) {
        if (i > 0) { m_gp << ", "; }
        line.draw(m_gp);
        i++;
    }
    m_gp << '\n';

    for (auto& line : m_lines) {
        line.send_data(m_gp);
    }

    // redraw in interactive mode
    if (m_interactive && m_filename.has_value()) {
        // Reset output to show in a window
        m_gp << "unset output\n";
        // Use Gnuplot's interactive terminal
        m_gp << "set terminal qt\n";
        m_gp << "replot\n";
    }
}

}