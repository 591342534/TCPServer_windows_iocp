#ifndef TCP_SERVER_H_
#define TCP_SERVER_H_
#include <deque>
#include <set>
#include <winsock2.h>
#include <Windows.h>
#include "thread_mutex_lock.h"


class TCPServer
{
public:
    typedef struct _SERVERTHREADPOOL
    {
        HANDLE thread_handle;

    } SERVER_THREAD_POOL, *P_SERVER_THREAD_POOL;

    typedef struct _PERIODATA
    {
        OVERLAPPED overlapped;
        WSABUF wsa_buf;
        char buf[1024];
        std::deque<char>* p_send_deque;
        std::deque<char>* p_recv_deque;
        int type; //0 ���� 1 ����

    } PERIODATA, *P_PERIODATA;

    TCPServer();
    ~TCPServer();

    int start(const char* ip, const int port, int thread_cnt);
    //XP�Լ�֮ǰ��ϵͳstop��Ҫ��WSASocket��socket���л��⴦��֮���ϵͳ����Ҫ
    int stop();

protected:
    //ֻ�ܴ�recv_deque������
    //ֻ����send_dequeѹ����
    //�û����ж��������������recv_dequeȡ�����պõ����ݣ���Ҫ���͵����ݷ���send_deque
    //�û�ֻʹ������������Բ��ù�������ϸ��
    virtual void work(std::deque<char>& send_deque, std::deque<char>& recv_deque);

private:
    int create_thread_pool(int thread_cnt);
    SOCKET get_listen_socket(const char* ip, const int port, const int backlog); //SOMAXCONN
    static unsigned long WINAPI client_thread(void*);
    static unsigned long WINAPI accept_thread(void*);
    void clear(SOCKET client_socket, P_PERIODATA p_per_io_data);
    P_SERVER_THREAD_POOL m_thread_pool;
    int m_thread_cnt;
    bool m_run_flag;
    HANDLE m_accept_thread_handle;
    SOCKET m_listen_socket;
    HANDLE m_completion_port;
    std::set<SOCKET> m_client_sockets;
    thread_mutex m_mutex;
};

#endif