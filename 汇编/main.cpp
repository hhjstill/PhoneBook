#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

//�绰�����
//��Ҫ������ɾ���
//��Ϣ�ṹ��
struct TEL
{
	char* szName[12];
	char* szNum[12];
};
//ȫ������
char* fmtstr = "%s";
char* fmtchar = "%c";
char* fmtdec = "%d";
char* fmtprtstr = "%s\n";
char* namestr = "����������:";
char* ntc1 = "���޴���!\n";
char* ntc2 = "��ѡ��:";
char* ntc3 = "�������º���:";
char* ntc4 = "ɾ���ɹ�!\n";
char* ntc5 = "��ǰ����Ϊ:%s\n";
char* ntc6 = "��ǰ�绰��������...\n";
char* ntc7 = "������Ҫ��ӵ�����:";
char* ntc8 = "������Ҫ��ӵĺ���:";

char* show = "--����-----�绰-------\n";
char* showName = "%-10s";
char* showNum = "%-10s\n";
char* strError = "error input!\n";
char* ui = 
"��ѡ����:\n\
1.����\n\
2.��ѯ\n\
3.�޸�\n\
4.ɾ��\n\
5.��ʾȫ��\n\
0.�˳�\n";
const int nameLen = 12;
const int numLen = 12;
const int msgSize = 24;
TEL msg[100]{};
int curLen = 0;
int maxLen = 100;
int findNum = 0;
//����::
//��ʾ����:
void showUI(char* p)
{
	_asm
	{
		push[ebp + 8];
		push fmtstr;
		call printf;
		add esp, 8
	}
}
int userInput()
{
	_asm 
	{
		lea eax, [ebp - 0x0c];
		push eax;
		push fmtdec;
		call scanf_s;
		add esp, 8;
		mov eax, [ebp - 0x0c];
	}
}
void showAll()
{
	
	_asm
	{
		mov ecx, curLen;
		TEST ecx, ecx;
		je nodata;

		push ecx;

		push show;
		call printf;
		add esp, 4;
		lea esi, [msg];
		
		pop ecx;
	s:
		//��ӡ
		push ecx;

		push esi;
		push showName;
		call printf;
		add esp, 8;
		add esi, nameLen;

		push esi;
		push showNum;
		call printf;
		add esp, 8;
		add esi, numLen;

		pop ecx;

		loop s;
		jmp end;
	nodata:
		push ntc6;
		call printf;
		add esp, 4;
	end:
	}
}
//��
void increase(char* p, char* name, char* num)
{
	_asm
	{
		mov edi, [ebp + 8];
		mov esi, [ebp + 0x0c];
		mov ecx, nameLen;
		rep movsb;
		mov ecx, numLen;
		mov esi, [ebp + 0x10];
		rep movsb;
		inc curLen;
	}
}
char* find(char* p, char* name)
{
	_asm
	{
		xor ebx, ebx;
		mov findNum, 0;
		mov eax, findNum;
		mov[ebp - 4], eax;
	s:
		inc[ebp - 4];
		mov esi, [ebp + 8];
		mov edi, [ebp + 0x0c];
		mov ecx, nameLen;

		mov eax, msgSize;
		mul ebx;

		add esi, eax;
		repe cmpsb;
		TEST ecx, ecx;
		je yes;
		inc ebx;
		cmp ebx, curLen;
		jge no;
		loop s;
	yes:
		mov eax, [ebp - 4];
		mov findNum, eax;
		mov esi, [ebp + 8];
		mov edx, findNum;
		dec edx;
		mov eax, msgSize;
		mul edx;
		add esi, eax;
		mov edi, esi;
		add esi, nameLen;
		push esi;
		push ntc5;
		call printf;
		add esp, 8;
		mov eax, edi;
		jmp end;
	no:
		push ntc1;
		call printf;
		add esp, 4;
		mov eax, 0;
	end:
	}
}
//ɾ
void del(char* p, char* name)
{
	_asm
	{
		mov esi, [ebp + 8];
		mov edi, [ebp + 0x0c];
		push edi;
		push esi;
		call find;
		add esp, 8;
		cmp eax, 0;
		je eend;
		//�ҵ�����,��ʱeax�������ָ��������ݵ�ָ��
		mov ebx, curLen;
		cmp findNum, ebx;
		je e;
		//���Ҫɾ���Ĳ������һ����
		mov edi, eax;
		mov esi, edi;
		add esi, msgSize;
		sub ebx, findNum;
		mov eax, msgSize;
		mul ebx;
		mov ecx, eax;
		rep movsb;
		mov ebx, curLen;
		dec ebx;
		mov ecx, msgSize;
		xor eax, eax;
		rep stosb;
		dec curLen;
		jmp end;
	e:
		//Ҫɾ���������һ����
		mov edi, eax;
		xor eax, eax;
		mov ecx, 6;
		rep stosd;
		dec curLen;
	end:
		push ntc4;
		call printf;
		add esp, 4;
	eend:
	}
}
//��

//��
void modify(char* p, char* name)
{
	_asm
	{
		mov edi, [ebp + 8];
		mov esi, [ebp + 0x0c];
		push esi;
		push edi;
		call find;
		add esp, 8;
		cmp eax, 0;
		je ed;
		mov edi, eax;

		push ntc3;
		call printf;
		add esp, 4;
		//�����º���

		lea esi, [ebp - 0x0c];
		push numLen;
		push esi;
		push fmtstr;
		call scanf_s;
		add esp, 0x0c;

		
		add edi, nameLen;
		mov ecx, numLen;
		rep movsb;
		
	ed:
		xor eax, eax;
	}
}
int main()
{
	//1.��ʾ����
	_asm
	{
		mov eax, ui;
		push eax;
		call showUI;
		add esp, 4;
		//call getchar;
	}
	//2.�����û�����

	_asm
	{
	start:
		push ntc2;
		call printf;
		add esp, 4;
		call userInput;
		
	}
	//3.��ִ֧�в���
	_asm
	{
		//����
		cmp eax, 1;
		jne n1;
		//���������
		//add..............
		mov eax, maxLen;
		cmp curLen, eax;
		je s;

		push ntc7;
		call printf;
		add esp, 4;

		lea esi, [ebp - 0x18];
		push nameLen;
		push esi;
		push fmtstr;

		//��������
		call scanf_s;
		add esp, 0x0c;
		

		push ntc8;
		call printf;
		add esp, 4;
		//�������
		lea edi, [ebp - 0x0c];
		push numLen;
		push edi;
		push fmtstr;
		call scanf_s;
		add esp, 0x0c;

		//�������Ӻ��뷽��
		push edi;
		push esi;
		lea ebx, [msg];
		mov eax, curLen;
		mul msgSize;
		lea esi, [eax + ebx];
		push esi;
		call increase;
		add esp, 0x0c;
		
		jmp s;
	n1://��ѯ
		cmp eax, 2;
		jne n2;
		//find
		//����Ҫ���ҵ�����
		push namestr;
		call printf;
		add esp, 4;
		push nameLen;
		lea eax, [ebp - 0x0c];
		push eax;
		push fmtstr;
		call scanf_s;
		add esp, 0x0c;
		lea eax, [ebp - 0x0c];
		lea esi, [msg];
		//���ò��ҷ���
		push eax;
		push esi;
		call find;
		add esp, 8;
		jmp s;
	n2://�޸�
		cmp eax, 3;
		jne n3;
		//��
		push namestr;
		call printf;
		add esp, 4;
		lea esi, [ebp - 0x18];
		push nameLen;
		push esi;
		push fmtstr;

		//��������
		call scanf_s;
		add esp, 0x0c;


		//�����޸ķ���
		push esi;
		lea ebx, [msg];
		push ebx;
		call modify;
		add esp, 0x8;
		
		jmp s;
	n3://ɾ��
		cmp eax, 4;
		jne n4;
		//ɾ
		
		push namestr;
		call printf;
		add esp, 4;
		lea esi, [ebp - 0x18];
		push nameLen;
		push esi;
		push fmtstr;
		//��������
		call scanf_s;
		add esp, 0x0c;
		push esi;
		lea edi, [msg];
		push edi;
		call del;
		add esp, 8;
		jmp s;
	n4:
		cmp eax, 5;
		jne n5;
		//��ʾ����
		call showAll;
		jmp s;
	n5:
		cmp eax, 0;
		jne err;
		//�˳�
		jmp ed;
	err:
	j:
		call getchar;
		cmp eax, 10;
		jne j;
		push strError;
		call printf;
		add esp, 4;
		jmp s;
	s:
		jmp start;
	ed:
		xor eax, eax;
	}
	return 0;
}
