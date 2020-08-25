#ifndef GAME_FIELD_H
#define GAME_FIELD_H
#include "game_elems.h"
#include "painter.h"
#include <vector>
#include <utility>
#include <cstdlib>

//20 x 30


class game_field{
    private:
        int live=3;
        int bricks=40;
        ball play_ball;
        std::pair<float, float> ball_coords;
        bar play_bar;
        std::pair<float, float> bar_coords;
        painter* paint;
        brick* wall[10][4];
        std::vector<std::pair<std::pair<float, float>, brick*>> hittable_bricks;
        void impact_brick(float bx, float by);
        std::pair<float, float>* compute_line_equation(float ax, float ay, float bx, float by);
        void border_impact(float bx, float by);
        void bar_impact(float bx, float by);
        std::pair<float,float>* compute_new_coords(std::pair<float, float> ball_coefficients, std::pair<float, float> line_coefficients, std::pair<float, float> start_point, std::pair<float, float> impact_point_coords );
        void impact_point(float coeff_ball, float known_term_ball, float coeff_line, float known_term_line, std::pair<float, float>* result);
        float compute_cartesian_distance(float ax, float ay, float bx, float by);
        bool check_boundaries(float end_x_ball, float start_x_ball, float end_y_ball, float start_y_ball, float line_end_x, float line_start_x, float line_end_y, float line_start_y, float impact_x, float impact_y );
        float rotate_x(float x_comp, float y_comp, float alpha);
        float rotate_y(float x_comp, float y_comp, float alpha);
        

    public:
        void draw();
        void init();
        void check_bound_r();
        void check_bound_l();
        void check_bound_u();
        void check_bound_d();
        int lives(){return live;}
        bool bricks_alive(){return bricks>0;}
        ~game_field();
        game_field(){
            for(int x=0; x< 10; x++){
                for(int y=0; y<4; y++){
                    wall[x][y]=new brick(rand() %4);
                    if(y==3){
                        hittable_bricks.push_back(std::pair<std::pair<float, float>, brick*>(std::pair<float, float>(x, y), wall[x][y]));
                        wall[x][y]->can_hit(true);
                    }
                }
            }
            play_ball=ball();
            play_bar=bar();
            ball_coords=std::pair<float, float>(10, 10);
            bar_coords=std::pair<float, float>(10, 4.25);
            paint=new painter();
        }
        void move_ball();
        void draw_setup(){
            paint->setup_draw();
        }
        void draw_endgame(){
            paint->endgame_draw();
        }
};

#endif