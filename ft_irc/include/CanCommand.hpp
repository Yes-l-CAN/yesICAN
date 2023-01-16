#ifndef CAN_COMMAND_HPP
#define CAN_COMMAND_HPP


#define SUCCESS 1
#define FAIL  0
#define ERROR   -1

class CanCommand{

    private:
        int     result;
    
    protected:
		int		bufferSize = 300;
		char	buffer[bufferSize];
	public:

    public:
        CanCommand();
        // CanCommand(const CanCommand& obj);
        // CanCommand& operator=(const CanCommand& obj);
        ~CanCommand();

		void cRecv(int fd);
		void Client2ServSend(int fd);
        void Serv2ClientSend(int fd);

        void    Pass(std::vector<std::string> argv);
        int     Nick(std::vector<std::string> argv);
        int     User(std::vector<std::string> argv);
        void    Ping(std::vector<std::string> argv);
        //void    Pong(std::vector<std::string> argv);
        void    Join(std::vector<std::string> argv);
        void    Part(std::vector<std::string> argv);
        void    Kick(std::vector<std::string> argv);
        void    Notice(std::vector<std::string> argv);
        void    PrivateMSG(std::vector<std::string> argv);                 
        
        
        class recvException : public std::exception{
            virtual const char* what() const throw()
        };
};

#endif