#ifndef CAN_COMMAND_HPP
#define CAN_COMMAND_HPP


#define SUCCESS 1
#define FAIL  0
#define ERROR   -1

class CanCommand{

    private:
        int     result;

    public:
        CanCommand();
        CanCommand(const CanCommand& obj);
        CanCommand& operator=(const CanCommand& obj);
        ~CanCommand();
        void    Pass();
        int     Nick();
        int     User();
        void    Ping();
        void    Pong();

};

#endif