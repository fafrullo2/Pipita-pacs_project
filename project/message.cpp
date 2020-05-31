#include "message.h"

void message::copy(message msg){
    ID=msg.get_ID();
    type=msg.get_type();
    int n=msg.get_size();
    for (int i=0; i<n; i++)
        params.push_back(msg.get_param(i));
}

