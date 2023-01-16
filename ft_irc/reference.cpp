#include "./include/CanServer.hpp"


void printPacket(unsigned char* packet, unsigned int packetSize);

int main()
{
    int serverSock_fd = -1;
    /* 	소켓 만드는데 사용
        int socket(int domain, int type, int protocol);
        domain : 통신영역, type: 프로토콜 타입, protocol: 어떤 프로토콜...? */
    serverSock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSock_fd < 0)
    {
        std::cerr << "can not create socket" << std::endl;
        return -1;
    }
    int option = true;
    std::cout << "sockopt " << setsockopt(serverSock_fd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option))
              << std::endl;

    /* socket의 통신 대상 지정을 위해 address 사용 -> struct ~*/
    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET; // 주소 체계를 구분하기 위한 변수 addr_in의 경우 항상 AF_INET
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY); // host IP 주소  -> gethostbyname() 통새서 직접 설정 가능
    servAddr.sin_port = htons(MPORT);             // 보트번호!

    /*
        socket() 함수로 생성한 소켓에 ip주소, 포트 번호=> 소켓 주소정보에 해당하는 정보 할당
        어떤 포트에 연결되었는지 (일단 소켓 열면 연 소켓을 현재 system 포트에 연결시캬줘야 함)
        int bind(int sockfd, struct sockaddr *my_addr, int addrlen);
        sockfd: socket() 함수로 얻은 소켓 fd
        my_addr: IP 주소에 관한 정보(ip주소, 포트번호)를 담고있는 sockaddr 구조체 포인터
        addrlen: sockaddr 구조체 크기
    */
    int res = bind(serverSock_fd, (struct sockaddr*)&servAddr, sizeof(servAddr));
    if (res < 0)
    {
        std::cerr << "bind error" << std::endl;
        return -1;
    }

    /*
        클라이언트의 연결이 가능할 수 있도록 만들어줌 (약간 대기열로 생각하면 될 듯..! 대기열이니까 FIFO)
        외부로부터의 반드시 처리해야하는 접속이 올 경우 >> listen() -> accept()
        int listen(int sockfd, int backlog);
        sockfd: 보통 소켓 fd
        backlog: 접속 대기 큐 최대 연결 가능 수 (외부 연결은 대기 큐에서 accept() 호출 때 까지 기다려야 함, 보통 20
       제한)
        ** listen() 전에 bind() 호출 (랜덤 지정 포트에서 접속할 순 없으니까...) **
    */
    if (listen(serverSock_fd, MAXFD) < 0)
    {
        std::cerr << "listen error" << std::endl;
        return -1;
    }

    std::cout << "listen" << MPORT << "port" << std::endl;

    fcntl(serverSock_fd, F_SETFL, O_NONBLOCK);

    /*
        fd_set : 소켓 fd를 그룹짓기 위해 사용 -> FD_ 로 시작하는 매크로 함수들은 다 ㅎㅐ당 구조체 사용
        FD_SETSIZE : fd 집합 크기 즉 해당 그룹에 포함 가능한 소켓의 최대 개수 의미
        fd_mask (= long int): fd_set으로 그룹지을 때 각 소켓 fd 값 직접저장 아니라 해당 값을 비트 단위로 저장
        NFDBITS: fd_mask 크기 * 8 => fd_mask 데이터 형의 비트 수
        copy 해서 사용하는 이유는 select 함수가 원본을 바꿔버리기 때문!

    */
    fd_set reads;
    fd_set cpy_reads;
    FD_ZERO(&reads); // ft_set으로 선언된 변수 초기화 할 때 사용 모든 비트값 0으로 초기화
    /*
        fd_socket 값을 fd_set으로 ㅅ선언된 변수에 추가할 때 사용
        fd_socket 에 저장된 정수값을 고유값으로 판단 -> fd_set 변수에 해당 값에 할당된 비트를 1로 켜줌
        결국 fd_set에서 열려있는(연결되어있는) fd에 대한 비트를 1로 켜줌
    */
    FD_SET(serverSock_fd, &reads);
    int maxFd = serverSock_fd;
    // struct timeval timeout;
    // timeout.tv_sec = 1;
    // timeout.tv_usec = 0;

    int                clientSock_fd = -1;
    struct sockaddr_in clientAddr;

    const int buffSize = MAXBUF;
    char      buffer[buffSize];

    while (1)
    {
        struct timeval timeout;
        timeout.tv_sec = 5;
        timeout.tv_usec = 500;
        // FD_ZERO(&reads);
        // FD_SET(serverSock_fd, &reads);
        // FD_SET(clientSock_fd, &reads);
        cpy_reads = reads;

        /*
            소켓들을 관찰하다 이벤트 발생하면
        */
        int ret;
        ret = select(MAXFD + 1, &cpy_reads, NULL, NULL, &timeout);

        if (ret < 0)
        {
            std::cerr << "select error" << std::endl;
            break;
        }
        else if (ret == 0)
        {
            // std::cout << "timeout?" << std::endl;
            continue;
        }
        std::cout << "pass select" << std::endl;

        /*
            Fd_set 변수에 특정 fd값이 설정되어있는지 확인할 때 사용
            ex) socket fd가 5인 경우 fd_set에 5에 해당하는 비트가 1이 되어잇는지 확인
            변화를
        */
        for (int i = 0; i < MAXFD + 1; i++)
        {
            if (FD_ISSET(i, &cpy_reads))
            {
                if (i == serverSock_fd)
                {
                    unsigned int size = sizeof(clientAddr);
                    /*
                        요청이 들어온 client에 대한 새로운 socket fd 만들어줌 -> 하나의 값으로 두 개의 socket fd 갖...?
                        원래거(fd)-> 기다리던 포트에서 계속 listen()
                        새거(fd) -> send() recv() 준비 되도록
                        int accept(int sockfd, void *addr, int *addrlen);
                        sockfd: listen() 하고 있는 소켓 기술자
                        addr: 로컨 struct sockaddr_in 포인터 (접속에 관한 정보 -> 어느 호스트에서 어느 포트이용 접속하려
                       하는지) addrlen: 해당 정수에 struct sockaddr_in 크기 미리 지정되어야

                    */
					try
					{
                    clientSock_fd = accept(serverSock_fd, (struct sockaddr*)&clientAddr, &size);
                    std::cout << "clientfd  ::: " << clientSock_fd << std::endl;

                    // for (i = 0; i < 10; i++)
                    // 	std::cout << "fd_set bits ::" <<  std::bitset<32>(reads.fds_bits[i]) << std::endl;

                    if (clientSock_fd < 0)
                    {
						throw
                    }

                    FD_SET(clientSock_fd, &reads);
					}
					catch(const std::exception& e)
					{
                        std::cerr << "invalid client socket" << std::endl;
                        std::cerr << "ClientSocket : " << clientSock_fd << std::endl;
                        continue;					}
				}

                    std::cout << "accept new client! " << std::endl;
                    std::cout << "ClientSocket : " << clientSock_fd << std::endl;
                }
                else
                {

                    //	do{
                    ret = recv(i, buffer, buffSize, 0);
                    if (ret < 0)
                    {
                        std::cerr << "couldn't recv client socket error: " << errno << ": " << std::strerror(errno)
                                  << std::endl;
                        FD_CLR(i, &reads);
                        close(i);
                        break;
                    }
                    else if (ret == 0)
                    {
                        std::cerr << "receive client socket closed " << std::endl;
                        FD_CLR(i, &reads);
                        close(i);
                        break;
                    }

                    std::cout << "receive message!!" << std::endl;
                    std::cout << "Client Socket : " << clientSock_fd << std::endl;
                    std::cout << "read: " << ret << std::endl;

                    for (int j = 4; j <= clientSock_fd; j++)
                        ret = send(j, buffer, ret, 0);
                    if (ret < 0)
                    {
                        std::cerr << "couldn't send socket error" << std::endl;
                        break;
                    }
                    std::cout << "send to client socket : " << clientSock_fd << std::endl;
                    std::cout << "write: " << ret << std::endl;

                    printPacket((unsigned char*)buffer, ret);
                }
            }
            //	}while (false);

            //	close (clientSock_fd);
            //		std::cout << "close client socket : " << clientSock_fd << std::endl;
        }
    }
    if (serverSock_fd != -1)
    {
        close(serverSock_fd);
    }

    return (0);
}

void printPacket(unsigned char* packet, unsigned int packetSize)
{

    for (unsigned int i = 0; i < packetSize; i++)
    {
        if ((i % 0x10) == 0x00)
        {
            fprintf(stdout, "0x%04X: ", i);
            fprintf(stdout, "%02X ", packet[i]);
            continue;
        }

        fprintf(stdout, "%02X ", packet[i]);

        if (i == 0)
        {
            continue;
        }

        if ((i % 0x10) == 0x0F)
        {
            fprintf(stdout, "| ");
            for (unsigned int j = i - 0x0F; j < i; j++)
            {
                if (packet[j] >= 0x20 && packet[j] < 0x7F)
                {
                    fprintf(stdout, "%c", packet[j]);
                }
                else
                {
                    fprintf(stdout, ".");
                }

                if ((j % 0x08) == 0x07)
                {
                    fprintf(stdout, " ");
                }
            }
            fprintf(stdout, "\n");
            continue;
        }

        if ((i % 0x08) == 0x07)
        {
            fprintf(stdout, "  ");
            continue;
        }
    }

    int remain = packetSize % 0x10;
    if (remain != 0)
    {
        unsigned int space = (0x10 - remain) * 3;
        if (remain < 8)
        {
            space += 2;
        }
        for (; space > 0; space--)
        {
            fprintf(stdout, " ");
        }

        fprintf(stdout, "| ");
        for (int i = remain; i > 0; i--)
        {
            int j = packetSize - i;
            if (packet[j] >= 0x20 && packet[j] < 0x7F)
            {
                fprintf(stdout, "%c", packet[j]);
            }
            else
            {
                fprintf(stdout, ".");
            }

            if ((j % 0x08) == 0x07)
            {
                fprintf(stdout, " ");
            }
        }

        fprintf(stdout, "\n");
    }
    fprintf(stdout, "\n");
}