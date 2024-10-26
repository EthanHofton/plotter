# Plotter

A simple wrapper for the GNUPlot-iostream interface

# Requirements

 1. Gnuplot (install MacOS: `brew install gnuplot`)
 2. Boost (install MacOS: `brew install boost`)
 3. C++ 20
 4. (Optional) CMake

# Usage

## Basic Usage

The wrapper can be used to easily graph multiple lines in the same plot. The first example is to create a new instance of the plotter:

```
plt::plotter p1;
```

Then, we can configure the plotter with the desired options:

```
p1.set_title("Example plot");
p1.set_x_label("X-axis");
p1.set_x_label("Y-axis);

// optional params
p1.set_x_range("0:100);
p1.set_y_range("0:200);
```

After that, we can add lines to the plotter. There are multiple ways to add new lines. The easiest is to add lines via a function:

```
double x2(double x) { return x * x; }
double x3(double x) { return x * x * x; }
double x4(double x) { return x * x * x * x; }

...

p1.add_line(line::default_from_func(x2));
// optional, add a line label:
p1.add_line(line::default_from_func(x3), "X^3);
// optional, specificy an xstart, xend and xstep:
p1.add_line(line::default_from_func(x4, -100, 100, 0.1), "X^4");
```

And finally, draw:

```
p1.draw();
```

## Output redirects

With gnuplot, you can save to a file, or open a window to view the graph. By default, the plotter will open the graph in a window. To specify an output file, do:

```
p1.set_filename("your_file.png");
```

If you want to save to file and also open a window:

```
p1.set_filename("your_file.png");
p1.interactive();
```

## Lines

To create custom lines you can provide a function to generate from or provide the points yourself. You can also customize the line styling:

```
// plt::line::point is a typename for boost::tuple<double, double>
std::vector<plt::line::point> points;
for (int i = 0; i < 100; i += 0.1) {
    // plt::line::make_point simply calls boost::make_tuple(x, y)
    points.push_back(plt::line::make_point(x, x*x));
}
plt::line l1;
l1.set_points(points);

// styling params
l1.set_line_style(plt::line::DASHED);
l1.set_line_color("red");
l1.set_line_width("2");
l1.set_line_label("l1");

// create line using points_from_f
plt::line l2;
// works nicley with lambda functions
l2.points_from_f([](double x) { return x*x; }, -10, 10, 0.01);

// create line using default_from_func
plt::line l3 = plt::line::default_from_func([](double x) {return x*x*x; });
```

## Build

1. Using g++ (not recommended)

```
g++ [your_file.cpp] --std=c++20 -I path/to/plotter/include -I path/to/boost/include -L path/to/plotter/bin/lib -L path/to/boost/lib -lplotter -boost_iostreams -lboost_system -lboost_filesystem
```

2. Using CMake (Fetch Content)

```
include(FetchContent)

FetchContent_Declare(
  plt
  GIT_REPOSITORY https://github.com/JuliaStrings/utf8proc.git
)
FetchContent_MakeAvailable(utf8proc)

...

target_link_libraries(your_app plt::plotter)
```



