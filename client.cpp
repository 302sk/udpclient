//#include "stdafx.h"                     //预设环境
#include <stdio.h>
#include "winsock2.h"                   //包含网络处理函数头文件
#include "string.h"                     //包含字符串函数头文件
#pragma comment(lib,"Ws2.lib")       //包含静态链接库
 
//获取昵称函数：
void getname(char *name)                //定义昵称指针
{
    char yourname[40];                  //定义昵称存储空间
    gets(yourname);                     //获取昵称
    int i;
    for (i=0;i<40;i++)                   //将昵称赋值指针变量给主函数
    {
        *name++=yourname[i];
    }
}
//主函数
int WINAPI
_tmain(int argc, char* argv[])
{
    WSADATA client;                     //定义结构体
    WSAStartup(MAKEWORD(2,2),&client);  //初始化网络环境
    SOCKET clientsocket=socket(AF_INET,SOCK_DGRAM,IPPROTO_IP);  //创建socket套接口
    SOCKADDR_IN server;                 //定义地址结构
    server.sin_family=AF_INET;          //定义地址结构类型
    server.sin_port=htons(8000);        //定义地址结构的端口
    server.sin_addr.s_addr=inet_addr("255.255.255.255");        //定义地址结构的IP
    BOOL bBroadcast=TRUE;               //设置广播包选项
    setsockopt(clientsocket,SOL_SOCKET,SO_BROADCAST,(char*)&bBroadcast,sizeof(BOOL));       //设置socket支持广播包
 
    char namebuf[40];                   //定义名字保存的空间
    char buf[470]={0};                  //定义信息保存的空间
    char message[512]={NULL};           //设置发送服务器的信息的保存空间
    char flag='n';
 
    do
    {
        printf("Please input your Nick Name:\n");        //输出显示信息
        getname(namebuf);                       //输入用户昵称
        printf("Your Nick Name is:%s\nAre you sure?Confirm press y, Change press n\n",namebuf);        //输出提示信息
        scanf("%s",&flag);
    } while (flag=='n'||flag=='N');
    printf("Your nick name is \" %s \" you can talk here\n",namebuf);
 
    strcpy(message,namebuf);            //拷贝姓名信息到发送信息空间
    message[strlen(namebuf)]=':';       //拷贝信息特殊符号到信息发送空间
 
    while(strcmp(buf,"bye"))            //循环函数
    {
        gets(buf);                      //输入发送用户要说的信息
        char messageto[512];            //定义临时用户保存空间
        strcpy(messageto,message);      //将用户发送信息空间内容保存到临时用户保存空间
        strcat(messageto,buf);          //将用户要说的信息追加到临时信息保存空间末尾
        sendto(clientsocket,messageto,strlen(messageto),0,(SOCKADDR*)&server,sizeof(server));       //通过socket发送信息
    }
    closesocket(clientsocket);          //关闭socket
    WSACleanup();                       //清理网络环境
    return 0;                           //返回0
}
 