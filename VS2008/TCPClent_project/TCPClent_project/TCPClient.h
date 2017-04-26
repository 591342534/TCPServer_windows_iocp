#ifndef TCP_CIENT_H_
#define TCP_CIENT_H_

#include <deque>
#include <winsock2.h>



class TCPClient
{
public:
    TCPClient();
    ~TCPClient();
    int start(const char* ip, const unsigned short port);
    void stop();

protected:
    //ֻ�ܴ�recv_deque������
    //ֻ����send_dequeѹ����
    //�û����ж��������������recv_dequeȡ�����պõ����ݣ���Ҫ���͵����ݷ���send_deque
    //�û�ֻʹ������������Բ��ù�������ϸ��
    virtual void work(std::deque<char>& send_deque, std::deque<char>& recv_deque);

private:
    static unsigned long WINAPI thread_func(void*);
    int connect_to_server(const char* ip, const unsigned short port);
    int connect_retry(const SOCKET socket, const struct sockaddr* addr, const int alen, const int connect_cnt);
    int read_from_server();
    int write_to_server();


private:
    unsigned int m_port;
    char m_server_ip[16];
    bool m_run_flag;
    SOCKET m_socket;
    HANDLE m_thread_handle;
    bool m_write_event;
    std::deque<char> m_recv_queque;
    std::deque<char> m_send_queque;
};

#endif
