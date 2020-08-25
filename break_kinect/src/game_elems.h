#ifndef BAR_H
#define BAR_H

class bar{
    private:
        float x_comp=5, y_comp=0;
    public:
        bar(){}
        float x(){return x_comp;}
        float y(){return y_comp;}

        void x(float val){x_comp=val;}
        void y(float val){y_comp=val;}
};

#endif


#ifndef BALL_H
#define BALL_H

class ball{
    private:
        float vel_x_value=0.001, vel_y_value=0.1, radius_of_ball=0.05;
    public:
        ball(){}
        float vel_x(){return vel_x_value;}
        float vel_y(){return vel_y_value;}
        float get_radius(){return radius_of_ball;}

        void vel_x(float val){ vel_x_value=val;}
        void vel_y(float val){vel_y_value=val;}
        void radius(float val){radius_of_ball=val;}

};

#endif

#ifndef BRICK_H
#define BRICK_H

class brick{
    private:
        int type=2;
        bool is_alive=true, hittable=false;
    public:
        brick(){}
        brick(int t){type=t;}
        void hit(){
            type--;
            if(type<=0){
                is_alive=false;
                hittable=false;
            }
        }


        bool get_alive(){return is_alive;}
        bool can_hit(){return hittable;}
        void can_hit(bool hit){hittable=hit;}
        int get_type(){return type;}

};


#endif