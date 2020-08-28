#include "cartesian_operator.h"
#include <math.h>
//rotate the x coordinate according to the angle alpha
float cartesian_operator::rotate_x(float x_comp, float y_comp, float alpha){
    return x_comp*cos(alpha)-y_comp*sin(alpha);
}
//rotate the y coordinate according to the angle alpha
float cartesian_operator::rotate_y(float x_comp, float y_comp, float alpha){
    return x_comp*sin(alpha)+y_comp*cos(alpha);
}
//checks if the impact point is within the boundaries of two segments
bool cartesian_operator::check_boundaries(float end_x_ball, float start_x_ball, float end_y_ball, float start_y_ball, float line_end_x, float line_start_x, float line_end_y, float line_start_y, float impact_x, float impact_y ){
    float x_min, x_max, y_min, y_max, aux;
    if(start_x_ball>end_x_ball){
        aux=end_x_ball;
        end_x_ball=start_x_ball;
        start_x_ball=aux;
    }
    if(end_y_ball<start_y_ball){
        aux=end_y_ball;
        end_y_ball=start_y_ball;
        start_y_ball=aux;
    }

    if(line_end_x<line_start_x){
        aux=line_end_x;
        line_end_x=line_start_x;
        line_start_x=aux;
    }

    if(line_end_y<line_start_y){
        aux=line_end_y;
        line_end_y=line_start_y;
        line_start_y=aux;
    }

    if(line_start_x>start_x_ball)
        x_min=line_start_x;
    else
        x_min=start_x_ball;
    
    if(line_end_x>end_x_ball)
        x_max=end_x_ball;
    else
        x_max=line_end_x;

    if(line_start_y>start_y_ball)
        y_min=line_start_y;
    else
        y_min=start_y_ball;
    
    if(line_end_y>end_y_ball)
        y_max=end_y_ball;
    else
        y_max=line_end_y;
    return(impact_x>=x_min && impact_x<=x_max && impact_y>=y_min && impact_y<=y_max );
}

//returns true if a point is situated between two lines. Line one is the upper bound, line 2 is the lower bound
bool cartesian_operator::point_between_lines(std::pair<float, float> point, std::pair<float, float>* line_one, std::pair<float, float>* line_two){
    return(point.second<=point.first*line_one->first+ line_one->second && point.second>=point.first*line_two->first+line_two->second);
}
    float cartesian_operator::max(float a, float b){
        if(a>b)
            return a;
        return b;
    }
    float cartesian_operator::min(float a, float b){
        if(a<b)
            return a;
        return b;
    }