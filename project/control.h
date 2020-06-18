#ifndef CONTROL_H
#define CONTROL_H
class control{
    private:
        message_manager message_queue;
        message_manager* model_msg_queue;

    public:
        void control_thread();
};


#endif /* CONTROL_H */

