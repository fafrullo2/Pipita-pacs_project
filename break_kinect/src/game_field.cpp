#include "game_field.h"
#include <math.h>
#include <iostream>

bool game_field::check_ghost_impact(float delta_x_center, float  delta_x_lenght, float delta_y_lenght ){
    if(ball_coords.second>6)
        return false;
    std::pair<float, float>* line_old=nullptr, *line_new=nullptr;
    
    float old_min_y, old_max_y, new_min_y, new_max_y, old_min_x, old_max_x, new_min_x, new_max_x;
    
    if(play_bar.y()>=0){
        old_min_y=bar_coords.second-play_bar.y();
        old_max_y=bar_coords.second+play_bar.y();
        new_min_y=old_min_y-delta_y_lenght;
        new_max_y=old_max_y+delta_y_lenght;
    }
    else if(play_bar.y()<0){
        old_min_y=bar_coords.second+play_bar.y();
        old_max_y=bar_coords.second-play_bar.y();
        new_min_y=old_min_y+delta_y_lenght;
        new_max_y=old_max_y-delta_y_lenght;
    }
    if(old_min_y==old_max_y && new_min_y==new_max_y){
        return false;
    }
    
    old_min_x=bar_coords.first-play_bar.x();
    old_max_x=bar_coords.first+play_bar.x();
    new_min_x=old_min_x+delta_x_lenght+delta_x_center;
    new_max_x=old_max_x+delta_x_lenght+delta_x_center;
    line_old=cart->compute_line_equation(old_min_x, old_min_y, old_max_x, old_max_y);
    line_new=cart->compute_line_equation(new_min_x, new_min_y, new_max_x, new_max_y);
    float max_x, max_y, min_x, min_y;
    max_x=cart->max(old_max_x, new_max_x);
    max_y=cart->max(old_max_y, new_max_y);
    min_x=cart->min(old_min_x, new_min_x);
    min_y=cart->min(old_min_y, new_min_y);
    bool in_square=(ball_coords.first>=min_x && ball_coords.first<= max_x && ball_coords.second>=min_y && ball_coords.second<=max_y), result;
    result=(in_square && (cart->point_between_lines(ball_coords, line_old, line_new) || cart->point_between_lines(ball_coords, line_new, line_old)));
    delete line_old;
    delete line_new;
    return result;
}

game_field::~game_field(){
    for (int x=0; x<10; x++){
        for (int y=0; y<4; y++){
            delete wall[x][y];
        }
    }
    hittable_bricks.clear();
    delete paint;
    delete cart;
}



//checks if the update doesn't skip over the ball and if it is possible at all.
//if it is possible, applies changes
void game_field::check_bound_r(){
    if(bar_coords.first+play_bar.x()+0.075<=20){
        if(!check_ghost_impact(0.075,0,0))
            bar_coords.first+=0.075;
    }
}
//checks if the update doesn't skip over the ball and if it is possible at all.
//if it is possible, applies changes
void game_field::check_bound_l(){
    if(bar_coords.first-play_bar.x()-0.075>=0){
        if(!check_ghost_impact(-0.075,0,0))
            bar_coords.first-=0.075;
    }
}

//checks if the update doesn't skip over the ball and if it is possible at all.
//if it is possible, applies changes
void game_field::check_bound_u(){
    if(play_bar.y()+0.05>=1)
        return;
    float new_x_coord=bar_coords.first;
    float new_x_comp=(sqrt( pow(play_bar.x(),2) -0.1* play_bar.y() - 0.0025));
    if(bar_coords.first-new_x_comp<0)
        new_x_coord=new_x_comp;
    if(bar_coords.first+new_x_comp>20)
        new_x_coord=20-new_x_comp;
    if(check_ghost_impact(bar_coords.first-new_x_coord,play_bar.x()-new_x_comp, 0.05 ))
        return;
    bar_coords.first=new_x_coord;
    play_bar.x(new_x_comp);
    play_bar.y(play_bar.y()+0.05);

}
//checks if the update doesn't skip over the ball and if it is possible at all.
//if it is possible, applies changes
void game_field::check_bound_d(){ 
    if(play_bar.y()-0.05<=(-1))   
        return;
    float new_x_coord=bar_coords.first;
    float new_x_comp=(sqrt( pow(play_bar.x(),2) +0.1* play_bar.y() - 0.0025));
    if(bar_coords.first-new_x_comp<0)
        new_x_coord=new_x_comp;
    if(bar_coords.first+new_x_comp>20)
        new_x_coord=20-new_x_comp;
    if(check_ghost_impact(bar_coords.first-new_x_coord,play_bar.x()-new_x_comp, -0.05 ))
        return;
    bar_coords.first=new_x_coord;
    play_bar.x(new_x_comp);
    play_bar.y(play_bar.y()-0.05);

   
}
        





void game_field::draw(){
    //paint->prepare_for_update();
    paint->draw_gamefield(live);
    paint->draw(&play_ball, ball_coords.first, ball_coords.second);
    paint->draw(&play_bar, bar_coords.first, bar_coords.second);
    for (int x=0; x<10; x++){
        for (int y=0; y<4; y++){
            //if (wall[x][y]->get_alive())
                paint->draw(wall[x][y], x, y);
        }
    }
    return;

}


void game_field::move_ball(){
    float end_x=play_ball.vel_x()+ball_coords.first, end_y=play_ball.vel_y()+ball_coords.second;
    float start_x=ball_coords.first, start_y=ball_coords.second;
    
    if(end_y>=26 || ball_coords.second>=26)
        impact_brick(end_x, end_y); //check if the ball impcats on bricks
    if((start_x!=ball_coords.first)||(start_y!=ball_coords.second))
        return;
    if(end_y<=6 || ball_coords.second<=6)
        bar_impact(end_x, end_y); //check if the ball impacts with the bar
    if((start_x!=ball_coords.first)||(start_y!=ball_coords.second))
        return;
    border_impact(end_x, end_y); //check if the ball bounces on the walls
    if((start_x!=ball_coords.first)||(start_y!=ball_coords.second))
        return;
    if(end_y<=0){ //life lost
        live--;
        ball_coords.first=10;
        ball_coords.second=10;
        play_ball.vel_x(0.001);
        play_ball.vel_y(0.15);
        return;
    }
    //no impacts
    ball_coords.first=end_x;
    ball_coords.second=end_y;
    return;
}
void game_field::bar_impact(float bx, float by){
    std::pair<float, float>* line_eq=cart->compute_line_equation(ball_coords.first, ball_coords.second, bx, by );
    std::pair<float, float>* bar_eq=cart->compute_line_equation(bar_coords.first-play_bar.x(), bar_coords.second-play_bar.y(), bar_coords.first+play_bar.x(), bar_coords.second+play_bar.y());
    float x_impact, y_impact;
    //impact point determination
    if(line_eq->first==0 && line_eq->second==0){
        if(bar_eq->first==0 && bar_eq->second==0){
            delete line_eq;
            delete bar_eq;
            return;
        }
        x_impact=ball_coords.first;
        y_impact=x_impact*bar_eq->first + line_eq->second;
    }
    
    else if(bar_eq->first==0 && bar_eq->second==0){
        x_impact=bar_coords.first;
        y_impact=x_impact*line_eq->first + line_eq->second;
    }
    else if(bar_eq->first==0){
        y_impact=bar_coords.second;
        x_impact=(y_impact-line_eq->second)/line_eq->first;
    }
    else{
        x_impact=(bar_eq->second-line_eq->second)/(line_eq->first- bar_eq->first);
        y_impact=x_impact*line_eq->first+line_eq->second;
    }
    if(!cart->check_boundaries(bx, ball_coords.first, by, ball_coords.second, bar_coords.first-play_bar.x(), bar_coords.first+play_bar.x(), bar_coords.second-play_bar.y(), bar_coords.second+play_bar.y(), x_impact, y_impact)){
        delete line_eq;
        delete bar_eq;
        return;
    }

    //new speeds computation    
    float bar_dim;
    float left_x= bar_coords.first-play_bar.x();
    float right_x= bar_coords.first+play_bar.x();
	float left_y= bar_coords.second-play_bar.y();
    float right_y= bar_coords.second+play_bar.y();
    bar_dim=cart->compute_cartesian_distance(left_x, right_x, left_y, right_y);
	float  beta;
	
	beta=-asin((right_y-left_y)/bar_dim);

    //Rotate ball point and ball speeds
   
    float x_ball_r=cart->rotate_x(ball_coords.first, ball_coords.second, beta);
    float y_ball_r=cart->rotate_y(ball_coords.first, ball_coords.second, beta);

    float x_vel_r=cart->rotate_x(ball_coords.first+play_ball.vel_x(), ball_coords.second+play_ball.vel_y(), beta)-x_ball_r;
    float y_vel_r=cart->rotate_y(ball_coords.first+play_ball.vel_x(), ball_coords.second+play_ball.vel_y(), beta)-y_ball_r;


    float new_vel_x=cart->rotate_x(x_ball_r+x_vel_r, y_ball_r-y_vel_r, -beta)-ball_coords.first;
    float new_vel_y=cart->rotate_y(x_ball_r+x_vel_r, y_ball_r-y_vel_r, -beta)-ball_coords.second;

    play_ball.vel_x(new_vel_x);
    play_ball.vel_y(new_vel_y);
    //compute new ball coordinates
    std::pair<float, float>* aux=compute_new_coords((*line_eq),(*bar_eq), ball_coords, std::pair<float, float>(x_impact, y_impact));
    ball_coords.first=aux->first;
    ball_coords.second=aux->second;
    delete line_eq;
    delete bar_eq;
    delete aux;
}


void game_field::impact_brick(float bx, float by){
    brick *curr=nullptr, *cand=nullptr;
    bool actual_hits[4], horiz=false;
    float center_x, center_y, distances[4];
    float currdist=cart->compute_cartesian_distance(bx,by, ball_coords.first, ball_coords.second);
    std::pair<float, float> impact_points[4], candidate(-1, -1);
    std::pair<float, float>* line_eq=cart->compute_line_equation(ball_coords.first, ball_coords.second, bx, by );
    
    //scan all the hittable bricks to find an impact point
    for (int i=0; i<int(hittable_bricks.size()); i++){
        center_x=hittable_bricks[i].first.first*2+1;
        center_y=30-(hittable_bricks[i].first.second+0.5);
        curr=hittable_bricks[i].second;
        impact_points[0].second=center_y-0.5;
        impact_points[0].first= (center_y-0.5-line_eq->second)/line_eq->first ;
        
        impact_points[1].first=center_x+1;
        impact_points[1].second=(center_x+1)*line_eq->first + line_eq->second; 
        
        impact_points[2].second=center_y+0.5;
        impact_points[2].first=(center_y+0.5-line_eq->second)/line_eq->first ;
        
        impact_points[3].first=center_x-1;
        impact_points[3].second=(center_x-1)*line_eq->first + line_eq->second;

        
        actual_hits[0]=cart->check_boundaries(bx, ball_coords.first, by, ball_coords.second, center_x-1, center_x+1, center_y-0.5, center_y-0.5, impact_points[0].first, impact_points[0].second);
        actual_hits[1]=cart->check_boundaries(bx, ball_coords.first, by, ball_coords.second, center_x+1, center_x+1, center_y-0.5, center_y+0.5, impact_points[1].first, impact_points[1].second);
        actual_hits[2]=cart->check_boundaries(bx, ball_coords.first, by, ball_coords.second, center_x-1, center_x+1, center_y+0.5, center_y+0.5, impact_points[2].first, impact_points[2].second);
        actual_hits[3]=cart->check_boundaries(bx, ball_coords.first, by, ball_coords.second, center_x-1, center_x-1, center_y-0.5, center_y+0.5, impact_points[3].first, impact_points[3].second);

        distances[0]= cart->compute_cartesian_distance(ball_coords.first, ball_coords.second, impact_points[0].first, impact_points[0].second);
        distances[1]= cart->compute_cartesian_distance(ball_coords.first, ball_coords.second, impact_points[1].first, impact_points[1].second);
        distances[2]= cart->compute_cartesian_distance(ball_coords.first, ball_coords.second, impact_points[2].first, impact_points[2].second);
        distances[3]= cart->compute_cartesian_distance(ball_coords.first, ball_coords.second, impact_points[3].first, impact_points[3].second);

        for(int j=0; j<4; j++){
            if(actual_hits[j]&&distances[j]<=currdist){
                currdist=distances[j];
                candidate.first=impact_points[j].first;
                candidate.second=impact_points[j].second;
                horiz=(j==0 || j==2);
                cand=curr;
            }
        }
    }
    if(candidate.first==-1) //no hit point found
        return;
    cand->hit();
    if(!cand->get_alive()){
        //update hittable brick structure
        bricks--;
        int i=0;
        for(int j=0; j<int(hittable_bricks.size()) && hittable_bricks[j].second!=cand; j++){i++;}
        for(int x=hittable_bricks[i].first.first-1;x<=hittable_bricks[i].first.first+1; x++){
            for(int y=hittable_bricks[i].first.second-1;y<=hittable_bricks[i].first.second+1; y++){
                if(x>=0 && x<10 && y>=0 && y<4){
                    if(!(wall[x][y]->can_hit()) && wall[x][y]->get_alive()){
                        wall[x][y]->can_hit(true); 
                        std::pair<float, float>brick_indexes(x, y);             
                        hittable_bricks.push_back(std::pair<std::pair<float, float>, brick* >(brick_indexes, wall[x][y]));
                    }
                }
            }
        }
        hittable_bricks.erase(hittable_bricks.begin()+i);
    }

    //new ball position & velocity

    if(horiz){
        play_ball.vel_y(-play_ball.vel_y());
        if (candidate.second>ball_coords.second)
            ball_coords.second=candidate.second-play_ball.get_radius();
        else
            ball_coords.second=candidate.second+play_ball.get_radius();
        ball_coords.first=candidate.first;
    }
    else{
        play_ball.vel_x(-play_ball.vel_x());
        if (candidate.first>ball_coords.first)
            ball_coords.first=candidate.first-play_ball.get_radius();
        else
            ball_coords.first=candidate.first+play_ball.get_radius();
        ball_coords.second=candidate.second;
    }

    return;
}


void game_field::border_impact(float bx, float by){
    float distance=cart->compute_cartesian_distance(ball_coords.first, ball_coords.second, bx, by)+play_ball.get_radius();
    std::pair<float, float>* line_eq=cart->compute_line_equation(ball_coords.first, ball_coords.second, bx, by );
    float x_impact=-1, y_impact=-1;
    if(by>30-play_ball.get_radius()){ //impact on the top
        y_impact=30-play_ball.get_radius();
        x_impact=(y_impact-line_eq->second)   / line_eq->first;
        distance=cart->compute_cartesian_distance(ball_coords.first, ball_coords.second, x_impact, y_impact);
    }
    if(bx<=0+play_ball.get_radius()){ //impact on the left
        float aux_dist=cart->compute_cartesian_distance(ball_coords.first, ball_coords.second, 0+play_ball.get_radius(), (0+play_ball.get_radius())*line_eq->first + line_eq->second );
        if(aux_dist<distance){
            y_impact=(0+play_ball.get_radius())*line_eq->first + line_eq->second;
            x_impact=0+play_ball.get_radius();
        }
    }
    if(bx>=20-play_ball.get_radius()){ //impact on the right
        float aux_dist=cart->compute_cartesian_distance(ball_coords.first, ball_coords.second, 20-play_ball.get_radius(), (20-play_ball.get_radius())*line_eq->first + line_eq->second );
        
        if(aux_dist<distance){
        y_impact=(20-play_ball.get_radius())*line_eq->first + line_eq->second;
        x_impact=20-play_ball.get_radius();
        }
    }
    if(x_impact!=-1){ //has found an impact point
        if(x_impact!=0+play_ball.get_radius() && x_impact!=20-play_ball.get_radius())
            play_ball.vel_y(-play_ball.vel_y());
        else
            play_ball.vel_x(-play_ball.vel_x());
        ball_coords.first=x_impact;
        ball_coords.second=y_impact;
    }
    delete line_eq;
    return;
}






std::pair<float,float>* game_field::compute_new_coords(std::pair<float, float> ball_coefficients, std::pair<float, float> line_coefficients, std::pair<float, float> start_point, std::pair<float, float> impact_point_coords ){
    std::pair<float, float>* result = new std::pair<float, float>(-1,-1);
	//case: vertical impact line
	if(line_coefficients.first==0 && line_coefficients.second==0){

		if(start_point.first<impact_point_coords.first)
			result->first=impact_point_coords.first-play_ball.get_radius();
		else
			result->first=impact_point_coords.first+play_ball.get_radius();
		result->second= ball_coefficients.first*result->first +ball_coefficients.second;
		return result;
	}

	//case:horizontal impact line
	else if(line_coefficients.first==0){
		if(start_point.second<impact_point_coords.second || impact_point_coords.second==100)
			result->second=impact_point_coords.second - play_ball.get_radius();
		else
			result->second=impact_point_coords.second+play_ball.get_radius();
		result->first=(result->second - ball_coefficients.second)/ball_coefficients.first;
		return result;
	}

	//case: generic impact


	//compute new known term
	float x=(-line_coefficients.second)/line_coefficients.first;
	float y=line_coefficients.first;
	float distance=sqrt(x*x + y*y);
	float alpha=asin(sqrt(pow((y/distance),2)));
	float new_constant=play_ball.get_radius()/sin((M_PI/2)-alpha);
	//determine wether up or down
	if(start_point.second< impact_point_coords.second)
		new_constant=-new_constant;
	//compute new ball coords
	std::pair<float, float>aux(0,0);
	float aux_4=line_coefficients.second+new_constant;
	impact_point(ball_coefficients.first, ball_coefficients.second, line_coefficients.first, aux_4, &aux);
	result->first=aux.first;
	result->second=aux.second;
	return result;
}

//computes the equation of the line deffined by two points
std::pair<float, float>* cartesian_operator::compute_line_equation(float ax, float ay, float bx, float by){
    float a, b;
    if(ax==bx)
        return new std::pair<float, float>(0, 0);
    if(ay==by)
        return new std::pair<float, float>(0, ay);
    a=(by-ay)/(bx-ax);
    b= ay-ax*a;
    return new std::pair<float, float>(a, b);
}
//computes the cartesian distance
float cartesian_operator::compute_cartesian_distance(float ax, float ay, float bx, float by){
    return sqrt(pow((ax-bx),2)+pow((ay-by),2));
}

void game_field::impact_point(float coeff_ball, float known_term_ball, float coeff_line, float known_term_line, std::pair<float, float>* result){


	if(coeff_ball==coeff_line ){ //parallel lines
		result->first=-1;
		result->second=-1;
		return;
	}

	if(coeff_ball==0 && known_term_ball==0){ // ball moves vertically
		result->first=ball_coords.first;
		result->second=result->first*coeff_line+known_term_line;
		return;
	}

    //general case
	result->first=(known_term_line-known_term_ball)/(coeff_ball-coeff_line);
	result->second=coeff_ball*result->first +known_term_ball;

	return ;


}