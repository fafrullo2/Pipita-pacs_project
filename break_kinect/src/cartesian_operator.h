#ifndef CARTESIAN_OPERATOR_H
#define CARTESIAN_OPERATOR_H

#include <utility>

class cartesian_operator{
    public:
    float rotate_x(float x_comp, float y_comp, float alpha);
    float rotate_y(float x_comp, float y_comp, float alpha);
    float compute_cartesian_distance(float ax, float ay, float bx, float by);
    bool check_boundaries(float end_x_ball, float start_x_ball, float end_y_ball, float start_y_ball, float line_end_x, float line_start_x, float line_end_y, float line_start_y, float impact_x, float impact_y );
    std::pair<float, float>* compute_line_equation(float ax, float ay, float bx, float by);
    bool point_between_lines(std::pair<float, float> point, std::pair<float, float>* line_one, std::pair<float, float>* line_two);
    float max(float a, float b);
    float min(float a, float b);
};






#endif