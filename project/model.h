

#ifndef MODEL_H
#define MODEL_H

#include <string>
#include "message_manager.h"
#include "ball.h"
#include "brick.h"
#include "bar.h"
#include <map>
#include <utility>

class model{
private:
    int brick_count;
    int lives;
    ball ball_;
    bar bar_;
    std::map<float,std::pair<float, brick*>> bricks;
    message_manager message_queue;
    message_manager* view_msg_queue;
    void ball_control();
    void bar_update(message msg);
    void analyze_msg(message msg);
    //view message queue reference
    
public:
    
    void model_thread();
    void init(std::string input);
    
    
    
    
    
};


#endif /* MODEL_H */

