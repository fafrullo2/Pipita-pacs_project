

#ifndef MESSAGE_H
#define MESSAGE_H
#include <vector>
class message{
private:
    int ID;
    int type;//(model update 1=position change, 2= length change, 3= angle change  ; 4= brick destruction, 5= end game)
    std::vector<float> params;
public:
    int get_ID(){return ID;}
    void set_ID(int id){ID=id;}
    
    int get_type(){return type;}
    void set_type(int t){type=t;}
    
    float get_param(int i){
        return params.at(i);
    }
    
    void add_param(float par){
        params.push_back(par);
    }
    int get_size(){
        return params.size();
    }
    
    void copy(message msg);
};


#endif /* MESSAGE_H */

