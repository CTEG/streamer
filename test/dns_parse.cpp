#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#ifdef WIN32
#include <winsock2.h>
#pragma  comment(lib, "Ws2_32.lib")
#else
#include <sys/socket.h>
#include <netinet/in.h>
#endif



typedef struct _dns_struct {
    unsigned short id;      //ID:长度为16位，是一个用户发送查询的时候定义的随机数
    unsigned short flag;    //标志: QR(1),Opcode(4),AA(1),TC(1),RD(1),RA(1),Z(3),RCode(4)
    unsigned short ques;    //QDCount:长度16位，报文请求段中的问题记录数。
    unsigned short answ;    //ANCount:长度16位，报文回答段中的回答记录数。
    unsigned short auth;    //NSCOUNT :长度16位，报文授权段中的授权记录数。
    unsigned short addrrs;  //ARCOUNT :长度16位，报文附加段中的附加记录数。
} dns_struct;

typedef struct _dns_query_type {
    unsigned short type;
    unsigned short classtype;
} dns_query_type;

typedef struct _dns_response_type {
    unsigned short name;        //C0 0C 域名指针
    unsigned short type;        //查询类型
    unsigned short classtype;   //分类
} dns_response_type;



int make_dquery_domain(const char *src_domain, int src_len, char *dst_domain, int dst_len)
{
    char *dst = dst_domain;
    const char *ptr = src_domain;
    const char *domain = src_domain;
    int doffset = 0;
    int offset = 0;
    int strlength = 0;
    
    while(ptr && *ptr) {
        if(*ptr == '.') {
            *(dst + doffset) = strlength;
            doffset++;
            memcpy(dst + doffset, domain + offset - strlength, strlength);
            doffset += strlength;
            strlength = 0;
            ptr++;
            offset++;
        } else {
            strlength++;
            offset++;
            ptr++;
        }
    }
    
    if(strlength != 0) {
        *(dst + doffset) = strlength;
        doffset++;
        memcpy(dst + doffset, domain + offset - strlength, strlength);
        doffset += strlength;
        strlength = 0;
    }
    
    *(dst + doffset) = 0;
    
    return (doffset + 1);
}

int make_dns_query_packet(char *buff, int length, const char *domain, int dlen)
{
    char *ptr = NULL;
    int domainlength = 0;
    int packet_length = 0;
    dns_query_type *query_type_ptr = NULL;
    dns_struct *dns_pkt = (dns_struct *)buff;  //DNS请求Header
    
    dns_pkt->id = 120;  //ID
    dns_pkt->flag = 0x0001; //标志
    dns_pkt->ques = 0x0100; //QDCount,报文请求段中的问题记录数
    dns_pkt->answ = 0; //ANCount:长度16位，报文回答段中的回答记录数。
    dns_pkt->auth = 0;
    
    //DNS请求Question
    ptr = buff + 12;
    domainlength = make_dquery_domain(domain, dlen, ptr, length - 12); //QName：是你要查询的域名
    //DNS请求Question尾部
    query_type_ptr = (dns_query_type *)(ptr + domainlength);
    query_type_ptr->type = 0x0100; //QType：长度16位，表示查询类型
    query_type_ptr->classtype = 0x0100; //QClass:长度为16位，表示分类
    
    packet_length = 12 + domainlength + 4;
    
    buff[packet_length] = 0;
    
    return packet_length;
}

int parse_dns_response_packet(char *buff, int length, char *dstbuff, int dstlen)
{
    int dstoffset = 0;
    char *ptr;
    unsigned int addr = 0;
    int count = 0;
    unsigned int answ_number = 0;
    
    dns_query_type *t = NULL;
    
    dns_struct *dns_pkt = (dns_struct *)buff;
    answ_number = htons(dns_pkt->answ); //回复的IP个数
    
    ptr = buff + 12; //跳过头
    
    while(ptr && *ptr) {
        ptr++;
    }
    ptr++; //跳过Question.Qname
    
    t = (dns_query_type *)ptr; //查询类型
    ptr += 4; //跳过Question
    
    while(count < answ_number) {
        dns_response_type *res = NULL;
        res = (dns_response_type *)ptr; //Name+Type+Class
        ptr += 6;
        
        unsigned int ttl = 0;
        memcpy(&ttl, ptr, 4); //生存时间。4字节
        ptr += 4;
        
        unsigned short dlen = 0;
        memcpy(&dlen, ptr, 2); //资源的长度
        ptr += 2;
        
        if(res->type == 0x0100) {
            if(dstoffset < dstlen - 4) {
                memcpy(&dstbuff[dstoffset], ptr, 4); //IPv4 地址
                dstoffset += 4;
            } else {
                break;
            }
        }
        
        ptr += htons(dlen);
        count++;
    }
    
    return dstoffset;
}

int custom_gethostbyname(const char *domain, const char *nameserver)
{
    int ret;
    int sockfd;
    int sendlength = 0;
    unsigned int addr = 0;
    char sendbuff[1500] = {0};
    char recvbuff[1500] = {0};
    char addrbuff[1500] = {0};
    socklen_t addrlen = sizeof(struct sockaddr_in);
    struct sockaddr_in server; //服务端
    
    memset(&server, 0, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(53);
    server.sin_addr.s_addr = inet_addr(nameserver);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0) {
        printf("socket failed\n");
        return -1;
    }
    
    sendlength = make_dns_query_packet(sendbuff, 1500, domain, strlen(domain));
    
    //和服务器端进行通信,发送数据
    ret = sendto(sockfd, sendbuff, sendlength, 0, (struct sockaddr *)&server, sizeof(struct sockaddr));
    if(ret < 0) {
        printf("sendto failed\n");
        close(sockfd);
        return -1;
    }
    
    //和服务器端进行通信,接收数据
    ret = recvfrom(sockfd, recvbuff, 1500, 0, (struct sockaddr *)&server, &addrlen);
    if(ret < 0) {
        printf("recvfrom failed\n");
        close(sockfd);
        return -1;
    }
    
    addrlen = parse_dns_response_packet(recvbuff, ret, addrbuff, 1500);
    if(addrlen >= 4) {
        for(int i = 0; i < addrlen/4; i++) {
            memcpy(&addr, &addrbuff[i*4], 4);
            printf("address: %s\n", inet_ntoa(*(struct in_addr *)&addr));
        }
    }

    close(sockfd);
    
    return 0;
}

int main(int argc, char *argv[])
{
#ifdef _WINDOWS_
    WSADATA wsa; // 加载套接字库,初始化socket资源
    
    if (WSAStartup(MAKEWORD(1, 1), &wsa) != 0) {
        return 1;   // 代表失败
    }
#endif
    
    int ret = custom_gethostbyname("www.g.cn", "8.8.8.8");

#ifdef _WINDOWS_
    WSACleanup(); // 关闭加载的套接字库
#endif
    
    return 0;
}

