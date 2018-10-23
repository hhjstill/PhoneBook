#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

//电话本设计
//主要功能增删查改
//信息结构体
struct TEL
{
	char* szName[12];
	char* szNum[12];
};
//全局数据
char* fmtstr = "%s";
char* fmtchar = "%c";
char* fmtdec = "%d";
char* fmtprtstr = "%s\n";
char* namestr = "请输入姓名:";
char* ntc1 = "查无此人!\n";
char* ntc2 = "请选择:";
char* ntc3 = "请输入新号码:";
char* ntc4 = "删除成功!\n";
char* ntc5 = "当前号码为:%s\n";
char* ntc6 = "当前电话本无数据...\n";
char* ntc7 = "请输入要添加的名字:";
char* ntc8 = "请输入要添加的号码:";

char* show = "--姓名-----电话-------\n";
char* showName = "%-10s";
char* showNum = "%-10s\n";
char* strError = "error input!\n";
char* ui = 
"请选择功能:\n\
1.新增\n\
2.查询\n\
3.修改\n\
4.删除\n\
5.显示全部\n\
0.退出\n";
const int nameLen = 12;
const int numLen = 12;
const int msgSize = 24;
TEL msg[100]{};
int curLen = 0;
int maxLen = 100;
int findNum = 0;
//功能::
//显示界面:
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
		//打印
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
//增
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
//删
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
		//找到此人,此时eax保存的是指向此人数据的指针
		mov ebx, curLen;
		cmp findNum, ebx;
		je e;
		//如果要删除的不是最后一个人
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
		//要删除的是最后一个人
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
//查

//改
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
		//输入新号码

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
	//1.显示界面
	_asm
	{
		mov eax, ui;
		push eax;
		call showUI;
		add esp, 4;
		//call getchar;
	}
	//2.接收用户输入

	_asm
	{
	start:
		push ntc2;
		call printf;
		add esp, 4;
		call userInput;
		
	}
	//3.分支执行操作
	_asm
	{
		//增加
		cmp eax, 1;
		jne n1;
		//相等则增加
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

		//输入姓名
		call scanf_s;
		add esp, 0x0c;
		

		push ntc8;
		call printf;
		add esp, 4;
		//输入号码
		lea edi, [ebp - 0x0c];
		push numLen;
		push edi;
		push fmtstr;
		call scanf_s;
		add esp, 0x0c;

		//调用增加号码方法
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
	n1://查询
		cmp eax, 2;
		jne n2;
		//find
		//输入要查找的姓名
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
		//调用查找方法
		push eax;
		push esi;
		call find;
		add esp, 8;
		jmp s;
	n2://修改
		cmp eax, 3;
		jne n3;
		//改
		push namestr;
		call printf;
		add esp, 4;
		lea esi, [ebp - 0x18];
		push nameLen;
		push esi;
		push fmtstr;

		//输入姓名
		call scanf_s;
		add esp, 0x0c;


		//调用修改方法
		push esi;
		lea ebx, [msg];
		push ebx;
		call modify;
		add esp, 0x8;
		
		jmp s;
	n3://删除
		cmp eax, 4;
		jne n4;
		//删
		
		push namestr;
		call printf;
		add esp, 4;
		lea esi, [ebp - 0x18];
		push nameLen;
		push esi;
		push fmtstr;
		//输入姓名
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
		//显示所有
		call showAll;
		jmp s;
	n5:
		cmp eax, 0;
		jne err;
		//退出
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
