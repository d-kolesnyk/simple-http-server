#include <iostream>

#include <string>
#include <vector>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <netinet/ip.h>

#include <string.h>

#include <arpa/inet.h>

#include <sys/eventfd.h>
#include <sys/epoll.h>

class Socket 
{
    private:
        int fd;
        sockaddr_in addr;

    public:
        Socket(std::string addr, uint16_t port) : fd(0)
        {
            this->fd = socket(AF_INET, SOCK_STREAM, 0);

            bzero((char *)&(this->addr), sizeof(this->addr));

            this->addr.sin_family = AF_INET;
            this->addr.sin_port = htons(port);
            this->addr.sin_addr.s_addr = inet_addr(addr.c_str());
        }

        ~Socket() 
        {

        }

        operator int()
        {
            return this->fd;
        };

        void listen()
        {
            int enable = 1;
            setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
            bind(this->fd, (sockaddr *)&addr, sizeof(addr));
            ::listen(this->fd, SOMAXCONN);
        }
};

//int main(int argc, char *argv[])
int main()
{
    Socket sc = Socket("127.0.0.2", 8000);
    sc.listen();

    struct epoll_event event_sck;
    event_sck.data.fd = int(sc);
    event_sck.events = EPOLLIN | EPOLLET;
    
    // Epoll
    int epoll_fd = epoll_create1(0);
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, int(sc), &event_sck);

    std::vector<epoll_event> events(64);
    
    while (1) 
    {
        // wait for something to do...
        int nfds = epoll_wait(epoll_fd, &events[0], 64, -1);
        
        // for each ready socket
        for(int i = 0; i < nfds; i++)
        {
            //int fd = events[i].data.fd;
            std::cout << "Boo!" << std::endl;
        }
    }
    return 0;
}