

#ifndef VIEW_H
#define VIEW_H

#include "message_manager.h"
class view{
private:
    message_manager message_queue;
    message_manager* control_messager;
    //drawing part
    //input management
public:
    void draw_thread();
    void input_thread();
};


#endif /* VIEW_H */

