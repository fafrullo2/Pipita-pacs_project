//a simple threadsafe wrapper for std::queue

#ifndef MESSAGE_MANAGER_H
#define MESSAGE_MANAGER_H
#include "message.h"
#include <queue>
#include <mutex>
class message_manager{
protected:
    std::queue<message> message_queue;
    std::mutex mtx;
public:
    void push(message msg);
    message pop();
    bool is_empty();
};

#endif /* MESSAGE_MANAGER_H */

