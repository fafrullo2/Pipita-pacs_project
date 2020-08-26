#include "game_field.h"
#include <math.h>
#include <iostream>

bool game_field::check_ghost_impact(float delta_x_center, float  delta_x_lenght, float delta_y_lenght ){
    std::pair<float, float> old_sx_rotated, old_dx_rotated ,new_sx_rotated, new_dx_rotated, old_ball_rotated, new_ball_rotated;
    float alpha_old, alpha_new;
    
    alpha_old=-asin((2*play_bar.y()) /  sqrt(pow(2*play_bar.y(),2)+pow(2*play_bar.x(),2) ));
    alpha_new=-asin((2*(play_bar.y()+delta_y_lenght)) /  sqrt(pow(2*(play_bar.y()),2)+pow(2*play_bar.x(),2) ));
    
    old_sx_rotated.first= rotate_x(bar_coords.first-play_bar.x() , bar_coords.first-play_bar.y() , alpha_old);
    old_sx_rotated.second= rotate_y(bar_coords.first-play_bar.x() , bar_coords.first-play_bar.y() , alpha_old);
    old_dx_rotated.first= rotate_x(bar_coords.first+play_bar.x() , bar_coords.first+play_bar.y() , alpha_old);
    old_dx_rotated.second= rotate_y(bar_coords.first+play_bar.x() , bar_coords.first+play_bar.y() , alpha_old);
    
    new_sx_rotated.first= rotate_x(bar_coords.first-play_bar.x() +delta_x_center +delta_x_lenght , bar_coords.first-play_bar.y()+delta_y_lenght , alpha_new);
    new_sx_rotated.second= rotate_y(bar_coords.first-play_bar.x() +delta_x_center +delta_x_lenght, bar_coords.first-play_bar.y() +delta_y_lenght, alpha_new);
    new_dx_rotated.first= rotate_x(bar_coords.first+play_bar.x() +delta_x_center +delta_x_lenght, bar_coords.first+play_bar.y() +delta_y_lenght, alpha_new);
    new_dx_rotated.second= rotate_y(bar_coords.first+play_bar.x() +delta_x_center +delta_x_lenght, bar_coords.first+play_bar.y() +delta_y_lenght, alpha_new);

    old_ball_rotated.first=rotate_x(ball_coords.first, ball_coords.second, alpha_old);
    old_ball_rotated.second=rotate_y(ball_coords.first, ball_coords.second, alpha_old);
    
    new_ball_rotated.first=rotate_x(ball_coords.first+play_ball.vel_x(), ball_coords.second+play_ball.vel_y(), alpha_new);
    new_ball_rotated.second=rotate_y(ball_coords.first+play_ball.vel_x(), ball_coords.second+play_ball.vel_y(), alpha_new);

    if(! ( old_ball_rotated.first>=old_sx_rotated.first && old_ball_rotated.first<=old_dx_rotated.first && new_ball_rotated.first>=new_sx_rotated.first && new_ball_rotated.first<=new_dx_rotated.first   ) )
        return false;
    bool old_above, new_above;
    old_above=old_ball_rotated.second>=old_sx_rotated.second;
    new_above=new_ball_rotated.second>=new_sx_rotated.second;
    if((old_above && new_above) || (!old_above && !new_above))
        return false;
    return true;
}

game_field::~game_field(){
    for (int x=0; x<10; x++){
        for (int y=0; y<4; y++){
            delete wall[x][y];
        }
    }
    hittable_bricks.clear();
    delete paint;
}

float game_field::rotate_x(float x_comp, float y_comp, float alpha){
    return x_comp*cos(alpha)-y_comp*sin(alpha);
}

float game_field::rotate_y(float x_comp, float y_comp, float alpha){
    return x_comp*sin(alpha)+y_comp*cos(alpha);
}

void game_field::check_bound_r(){
    if(bar_coords.first+play_bar.x()+0.075<=20){
        if(!check_ghost_impact(0.075,0,0))
            bar_coords.first+=0.075;
    }
}
void game_field::check_bound_l(){
    if(bar_coords.first-play_bar.x()-0.075>=0){
        if(!check_ghost_impact(-0.075,0,0))
            bar_coords.first-=0.075;
    }
}
void game_field::check_bound_u(){
    if(play_bar.y()+0.05>=2)
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
void game_field::check_bound_d(){
    if(play_bar.y()+0.05<=(-2))
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
        impact_brick(end_x, end_y);
    if((start_x!=ball_coords.first)||(start_y!=ball_coords.second))
        return;
    if(end_y<=6 || ball_coords.second<=6)
        bar_impact(end_x, end_y);
    if((start_x!=ball_coords.first)||(start_y!=ball_coords.second))
        return;
    border_impact(end_x, end_y);
    if((start_x!=ball_coords.first)||(start_y!=ball_coords.second))
        return;
    if(end_y<=0){
        live--;
        ball_coords.first=10;
        ball_coords.second=10;
        play_ball.vel_x(0.001);
        play_ball.vel_y(0.15);
        return;
    }
    ball_coords.first=end_x;
    ball_coords.second=end_y;
    return;
}
void game_field::bar_impact(float bx, float by){
    std::pair<float, float>* line_eq=compute_line_equation(ball_coords.first, ball_coords.second, bx, by );
    std::pair<float, float>* bar_eq=compute_line_equation(bar_coords.first-play_bar.x(), bar_coords.second-play_bar.y(), bar_coords.first+play_bar.x(), bar_coords.second+play_bar.y());
    float x_impact, y_impact;
    
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
    else{
        x_impact=(bar_eq->second-line_eq->second)/(line_eq->first- bar_eq->first);
        y_impact=x_impact*line_eq->first+line_eq->second;
    }
    if(!check_boundaries(bx, ball_coords.first, by, ball_coords.second, bar_coords.first-play_bar.x(), bar_coords.first+play_bar.x(), bar_coords.second-play_bar.y(), bar_coords.second+play_bar.y(), x_impact, y_impact)){
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
    bar_dim=compute_cartesian_distance(left_x, right_x, left_y, right_y);
	float  beta;
	
		//alpha=asin( sqrt( pow((compute_cartesian_distance(start_x, end_x, start_y, end_y)/(start_y-end_y) ), 2)));

	
	beta=-asin((right_y-left_y)/bar_dim);

    //Rotate ball point, impact point and ball speeds
    float x_impact_r=rotate_x(x_impact, y_impact, beta);
    float y_impact_r=rotate_y(x_impact, y_impact, beta);

    float x_ball_r=rotate_x(ball_coords.first, ball_coords.second, beta);
    float y_ball_r=rotate_y(ball_coords.first, ball_coords.second, beta);

    float x_vel_r=rotate_x(ball_coords.first+play_ball.vel_x(), ball_coords.second+play_ball.vel_y(), beta)-x_ball_r;
    float y_vel_r=rotate_y(ball_coords.first+play_ball.vel_x(), ball_coords.second+play_ball.vel_y(), beta)-y_ball_r;


    float new_vel_x=rotate_x(x_ball_r+x_vel_r, y_ball_r-y_vel_r, -beta)-ball_coords.first;
    float new_vel_y=rotate_y(x_ball_r+x_vel_r, y_ball_r-y_vel_r, -beta)-ball_coords.second;

    play_ball.vel_x(new_vel_x);
    play_ball.vel_y(new_vel_y);

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
    float currdist=compute_cartesian_distance(bx,by, ball_coords.first, ball_coords.second);
    float alpha= asin(abs(by-ball_coords.second)/currdist);
    std::pair<float, float> impact_points[4], candidate(-1, -1);
    std::pair<float, float>* line_eq=compute_line_equation(ball_coords.first, ball_coords.second, bx, by );
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

        
        actual_hits[0]=check_boundaries(bx, ball_coords.first, by, ball_coords.second, center_x-1, center_x+1, center_y-0.5, center_y-0.5, impact_points[0].first, impact_points[0].second);
        actual_hits[1]=check_boundaries(bx, ball_coords.first, by, ball_coords.second, center_x+1, center_x+1, center_y-0.5, center_y+0.5, impact_points[1].first, impact_points[1].second);
        actual_hits[2]=check_boundaries(bx, ball_coords.first, by, ball_coords.second, center_x-1, center_x+1, center_y+0.5, center_y+0.5, impact_points[2].first, impact_points[2].second);
        actual_hits[3]=check_boundaries(bx, ball_coords.first, by, ball_coords.second, center_x-1, center_x-1, center_y-0.5, center_y+0.5, impact_points[3].first, impact_points[3].second);

        distances[0]= compute_cartesian_distance(ball_coords.first, ball_coords.second, impact_points[0].first, impact_points[0].second);
        distances[1]= compute_cartesian_distance(ball_coords.first, ball_coords.second, impact_points[1].first, impact_points[1].second);
        distances[2]= compute_cartesian_distance(ball_coords.first, ball_coords.second, impact_points[2].first, impact_points[2].second);
        distances[3]= compute_cartesian_distance(ball_coords.first, ball_coords.second, impact_points[3].first, impact_points[3].second);

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
    if(candidate.first==-1)
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
    float distance=compute_cartesian_distance(ball_coords.first, ball_coords.second, bx, by)+play_ball.get_radius();
    std::pair<float, float>* line_eq=compute_line_equation(ball_coords.first, ball_coords.second, bx, by );
    float x_impact=-1, y_impact=-1;
    if(by>30-play_ball.get_radius()){
        y_impact=30-play_ball.get_radius();
        x_impact=(y_impact-line_eq->second)   / line_eq->first;
        distance=compute_cartesian_distance(ball_coords.first, ball_coords.second, x_impact, y_impact);
    }
    if(bx<=0+play_ball.get_radius()){
        float aux_dist=compute_cartesian_distance(ball_coords.first, ball_coords.second, 0+play_ball.get_radius(), (0+play_ball.get_radius())*line_eq->first + line_eq->second );
        if(aux_dist<distance){
            y_impact=(0+play_ball.get_radius())*line_eq->first + line_eq->second;
            x_impact=0+play_ball.get_radius();
        }
    }
    if(bx>=20-play_ball.get_radius()){
        float aux_dist=compute_cartesian_distance(ball_coords.first, ball_coords.second, 20-play_ball.get_radius(), (20-play_ball.get_radius())*line_eq->first + line_eq->second );
        
        if(aux_dist<distance){
        y_impact=(20-play_ball.get_radius())*line_eq->first + line_eq->second;
        x_impact=20-play_ball.get_radius();
        }
    }
    if(x_impact!=-1){
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


float game_field::compute_cartesian_distance(float ax, float ay, float bx, float by){
    return sqrt(pow((ax-bx),2)+pow((ay-by),2));
}

std::pair<float, float>* game_field::compute_line_equation(float ax, float ay, float bx, float by){
    float a, b;
    if(ax==bx)
        return new std::pair<float, float>(0, 0);
    if(ay==by)
        return new std::pair<float, float>(0, ay);
    a=(by-ay)/(bx-ax);
    b= ay-ax*a;
    return new std::pair<float, float>(a, b);
}

bool game_field::check_boundaries(float end_x_ball, float start_x_ball, float end_y_ball, float start_y_ball, float line_end_x, float line_start_x, float line_end_y, float line_start_y, float impact_x, float impact_y ){
	/*bool aux_x=false, aux_y=false;
	aux_x=( (impact_x>=start_x_ball && impact_x<=end_x_ball)|| (impact_x<=start_x_ball && impact_x>=end_x_ball) ) && ( (impact_x>=line_start_x && impact_x<=line_end_x)|| (impact_x<=line_start_x && impact_x>=line_end_x) )  ;
	if(!aux_x)
		return false;
	aux_y=( (impact_y>=start_y_ball && impact_y<=end_y_ball)|| (impact_y<=start_y_ball && impact_y>=end_y_ball) ) && ( (impact_y>=line_start_y && impact_y<=line_end_y)|| (impact_y<=line_start_y && impact_y>=line_end_y) )  ;
	return aux_x && aux_y;*/

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

void game_field::impact_point(float coeff_ball, float known_term_ball, float coeff_line, float known_term_line, std::pair<float, float>* result){


	if(coeff_ball==coeff_line ){
		result->first=-1;
		result->second=-1;
		return;
	}

	if(coeff_ball==0 && known_term_ball==0){
		result->first=ball_coords.first;
		result->second=result->first*coeff_line+known_term_line;
		return;
	}


	result->first=(known_term_line-known_term_ball)/(coeff_ball-coeff_line);
	result->second=coeff_ball*result->first +known_term_ball;

	return ;


}