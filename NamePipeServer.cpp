#include <Windows.h>
#include <iostream>
#include "ClassProject.h"

using namespace std;




//HANDLE h_Mypipe = NULL;

//����1������ܵ��������ʾ��ǰ������pipe��ʾ�ܵ�

//#define MY_NAMED_PIPE   L"\\\\.\\pipe\\Named_Pipe"
#define MY_NAMED_PIPE   "\\\\.\\pipe\\Named_Pipe"

int createNamedPipe() {
	if (!WaitNamedPipe(MY_NAMED_PIPE, NMPWAIT_USE_DEFAULT_WAIT))

	{

		cout << "No Named_Pipe Accessible..." << endl;

		return 1;

	}

	else

		cout << "Named_Pipe Accessible..." << endl;



	//����3����ָ�������ܵ�

	//����CreateFile��������򿪶����������ָ���ǹܵ���

	h_Mypipe = CreateFile(

		MY_NAMED_PIPE, //������򿪵Ķ���(�ܵ�)����

		//GENERIC_READ  | //����ķ��ʷ�ʽ��������

		GENERIC_WRITE, //����ķ��ʷ�ʽ��д����

		0, //�����Ƿ���0��ʾ������

		NULL, //ָ��һ��SECURITY_ATTRIBUTES�ṹ��ָ��

		OPEN_EXISTING, //����Ĵ�����ʽ��OPEN_EXISTING��ʾ�򿪶���(�ܵ�)

		FILE_ATTRIBUTE_NORMAL, //���ö�������Ժͱ�־

		NULL);

	if (h_Mypipe == INVALID_HANDLE_VALUE)

	{

		cout << "Open Named_Pipe Failed..." << endl;

		return 1;

	}



	DWORD wLen = 0;

	DWORD rLen = 0;

	char szBuffer[BUF_SIZE] = { 0 };
}

int main(int argc, char** argv)

{

	//����2�����������ܵ�

	h_Mypipe = CreateNamedPipe(

		MY_NAMED_PIPE, //Ϊ�����ܵ���������

		PIPE_ACCESS_DUPLEX, //�ܵ����ʷ�ʽ��PIPE_ACCESS_DUPLEXָ˫��ģʽ

		PIPE_TYPE_MESSAGE | //�����ܵ������д�뷽ʽ�������ݿ�ķ�ʽд��ܵ�

		PIPE_READMODE_MESSAGE | //�����ܵ�����Ķ�ȡ��ʽ�������ݿ�ķ�ʽ�ӹܵ���ȡ

		PIPE_WAIT, //�����ܵ�����ĵȴ���ʽ��������ʽ

		PIPE_UNLIMITED_INSTANCES, //�ܵ����ܴ��������ʵ��������1~255��

		0, //�ܵ������������������0��ʾĬ�ϴ�С

		0, //�ܵ������뻺����������0��ʾĬ�ϴ�С 1000, //�ܵ���Ĭ�ϵȴ���ʱ����λ����

		0, //Ĭ�ϳ�ʱֵ
		NULL); //�ܵ��İ�ȫ�ԣ�NULL��ʾwindows�ṩ��Ĭ�ϰ�ȫ



		//INVALID_HANDLE_VALUE��CreateNamedPipe����ֵ����ʾ����ʧ��

	if (h_Mypipe == INVALID_HANDLE_VALUE)

	{

		cout << "Create Named_Pipe Failed..." << endl;

		return 1;

	}



	//����3���ȴ��ͻ��˵�����

	if (!ConnectNamedPipe(h_Mypipe, NULL))

	{

		cout << "Connect Failed..." << endl;

		return 1;

	}

	else

		cout << "Connect Successed..." << endl;



	DWORD wLen = 0;

	DWORD rLen = 0;

	char szBuffer[BUF_SIZE] = { 0 };



	//����4����д�ܵ�

	while (1)

	{

		
		//��ȡ�ͻ�������

		if (!ReadFile(h_Mypipe, szBuffer, BUF_SIZE, &rLen, NULL))

			cout << "Read Failed..." << endl;

		else

			cout << "���������տͻ������ݣ�" << szBuffer << ", ��" << rLen << "byte" << endl;

	}



	//����5���رչܵ�

	DisconnectNamedPipe(h_Mypipe);

	CloseHandle(h_Mypipe);

	return 0;

}
