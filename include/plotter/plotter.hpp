#ifndef __PLOTTER_HPP__
#define __PLOTTER_HPP__

#include "line.hpp"
#include <memory>
#include <optional>

class plotter {
public:

    plotter(const std::string& t_title = "Plot", const std::string& t_x_label = "x", const std::string& t_y_label = "y");
    
    void set_x_label(const std::string& t_x_label);
    void set_y_label(const std::string& t_y_label);
    void set_title(const std::string& t_title);

    void set_filename(const std::string& t_filename);
    void set_x_range(const std::string& t_x_range);
    void set_y_range(const std::string& t_y_range);
    void interactive();

    void add_line(const line& t_line);
    void add_line(line t_line, const std::string& t_line_label);

    void draw();

private:

    std::string m_x_label;
    std::string m_y_label;
    std::string m_title;

    // optional
    std::optional<std::string> m_filename;
    std::optional<std::string> m_x_range;
    std::optional<std::string> m_y_range;
    
    // flags
    bool m_interactive = false;
    // bool m_show_legend = false;

    // Gnuplot
    Gnuplot m_gp;

    // data
    std::vector<line> m_lines;
};

#endif