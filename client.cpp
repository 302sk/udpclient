//#include "stdafx.h"                     //Ԥ�軷��
#include <stdio.h>
#include "winsock2.h"                   //�������紦����ͷ�ļ�
#include "string.h"                     //�����ַ�������ͷ�ļ�
#pragma comment(lib,"Ws2.lib")       //������̬���ӿ�
 
//��ȡ�ǳƺ�����
void getname(char *name)                //�����ǳ�ָ��
{
    char yourname[40];                  //�����ǳƴ洢�ռ�
    gets(yourname);                     //��ȡ�ǳ�
    int i;
    for (i=0;i<40;i++)                   //���ǳƸ�ֵָ�������������
    {
        *name++=yourname[i];
    }
}
//������
int WINAPI
_tmain(int argc, char* argv[])
{
    WSADATA client;                     //����ṹ��
    WSAStartup(MAKEWORD(2,2),&client);  //��ʼ�����绷��
    SOCKET clientsocket=socket(AF_INET,SOCK_DGRAM,IPPROTO_IP);  //����socket�׽ӿ�
    SOCKADDR_IN server;                 //�����ַ�ṹ
    server.sin_family=AF_INET;          //�����ַ�ṹ����
    server.sin_port=htons(8000);        //�����ַ�ṹ�Ķ˿�
    server.sin_addr.s_addr=inet_addr("255.255.255.255");        //�����ַ�ṹ��IP
    BOOL bBroadcast=TRUE;               //���ù㲥��ѡ��
    setsockopt(clientsocket,SOL_SOCKET,SO_BROADCAST,(char*)&bBroadcast,sizeof(BOOL));       //����socket֧�ֹ㲥��
 
    char namebuf[40];                   //�������ֱ���Ŀռ�
    char buf[470]={0};                  //������Ϣ����Ŀռ�
    char message[512]={NULL};           //���÷��ͷ���������Ϣ�ı���ռ�
    char flag='n';
 
    do
    {
        printf("Please input your Nick Name:\n");        //�����ʾ��Ϣ
        getname(namebuf);                       //�����û��ǳ�
        printf("Your Nick Name is:%s\nAre you sure?Confirm press y, Change press n\n",namebuf);        //�����ʾ��Ϣ
        scanf("%s",&flag);
    } while (flag=='n'||flag=='N');
    printf("Your nick name is \" %s \" you can talk here\n",namebuf);
 
    strcpy(message,namebuf);            //����������Ϣ��������Ϣ�ռ�
    message[strlen(namebuf)]=':';       //������Ϣ������ŵ���Ϣ���Ϳռ�
 
    while(strcmp(buf,"bye"))            //ѭ������
    {
        gets(buf);                      //���뷢���û�Ҫ˵����Ϣ
        char messageto[512];            //������ʱ�û�����ռ�
        strcpy(messageto,message);      //���û�������Ϣ�ռ����ݱ��浽��ʱ�û�����ռ�
        strcat(messageto,buf);          //���û�Ҫ˵����Ϣ׷�ӵ���ʱ��Ϣ����ռ�ĩβ
        sendto(clientsocket,messageto,strlen(messageto),0,(SOCKADDR*)&server,sizeof(server));       //ͨ��socket������Ϣ
    }
    closesocket(clientsocket);          //�ر�socket
    WSACleanup();                       //�������绷��
    return 0;                           //����0
}
 