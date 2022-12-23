#define _CRT_SECURE_NO_WARNINGS
#include "GameInit.h"
#include <easyx.h>
#include <stdio.h>
#include "AI.h"

int Board[20][20];
//y0 = 1;per y = 4.3;y per xiangsu = 15.621;permission = +-1
const int Y[15] = {16,83,150,218,284,351,419,486,553,621,688,755,822,889,955};
//x0 = 1.7;per x = 4.1;x per xiangsu = 15.431;permission = +-1
const int X[15] = {27,90,153,216,279,343,406,469,532,596,659,722,786,849,911};

void GameInit(IMAGE board_img,int *round) {
	LOGFONT f;
	ExMessage mouse0;

	initgraph(1500,956, 0);//912 956
	
	setbkcolor(WHITE);
	cleardevice();

	gettextstyle(&f);						// ��ȡ��ǰ��������
	settextcolor(BLACK);					// ����������ɫ��ɫ
	f.lfHeight = 42;						// ��������߶�Ϊ 12
	_tcscpy(f.lfFaceName, _T("����"));		// ��������Ϊ�����塱(�߰汾 VC �Ƽ�ʹ�� _tcscpy_s ����)
	f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
	settextstyle(&f);						// ����������ʽ

	setfillcolor(0xCCCCCC);
	solidrectangle(600, 344, 900, 428);
	solidrectangle(600, 528, 900, 612);
	setfillcolor(BLACK);
	outtextxy(665, 365, _T("��������"));
	outtextxy(665, 549, _T("�������"));
	flushmessage();
	mouse0.lbutton = false;
	while (1) {
		while (mouse0.lbutton != true) {
			getmessage(&mouse0, EX_MOUSE);
		}
		mouse0.lbutton = false;
		if (mouse0.x > 600 && mouse0.x < 900) {
			if (mouse0.y > 344 && mouse0.y < 428) {
				*round = 0;//������
				break;
			}
			else if (mouse0.y > 528 && mouse0.y < 612) {
				*round = 1;//�����
				break;
			}
			else {
				continue;
			}
		}
	}
	flushmessage();
	putimage(0, 0,&board_img);
	
	for (int i = 0; i < 15; ++i) {
		for (int j = 0; j < 15; ++j) {
			Board[i][j] = 0;
		}
	}
}

void UserMouseJ(ExMessage mouse,int color,int *win) {
	int i = 0;
	int j = 0;
	int jump = 0;
	LOGFONT f;

	gettextstyle(&f);						// ��ȡ��ǰ��������
	settextcolor(BLACK);					// ����������ɫ��ɫ
	f.lfHeight = 24;						// ��������߶�Ϊ 12
	_tcscpy(f.lfFaceName, _T("����"));		// ��������Ϊ�����塱(�߰汾 VC �Ƽ�ʹ�� _tcscpy_s ����)
	f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
	settextstyle(&f);						// ����������ʽ


RENEW:
	outtextxy(913, 0, _T("��������"));
	while(mouse.lbutton != true){
		getmessage(&mouse, EX_MOUSE);
	}
	mouse.lbutton = false;
	for (i = 0; i < 15; ++i) {
		for (j = 0; j < 15; ++j) {
			if (mouse.x > X[i] - 16 && mouse.x < X[i] + 16) {
				if (mouse.y > Y[j] - 16 && mouse.y < Y[j] + 16 && Board[i][j] == 0) {
					if (color == 1) {
						setfillcolor(BLACK);
					}
					else {
						setfillcolor(WHITE);
					}
					solidcircle(X[i], Y[j], 28);
					Board[i][j] = color;
					flushmessage();
					jump = 1;
					break;
				}
			}
		}
		if (jump == 1) {
			jump = 0;
			clearrectangle(913, 0, 1500, 30);
			WinWinWin(win);
			tree* root = treerootbuild(i, j);
			tree * finder = root;
			treebuild(1, color, root, finder);
			free(root);
			break;
		}
		if (i == 14 && j == 15) {
			clearrectangle(913, 0, 1500, 30);
			goto RENEW;
		}
	}
}

void WinWinWin(int *win) {
	short judgeLb = 0, judgeWb = 0, judgeDb = 0;
	short judgeLa = 0, judgeWa = 0, judgeDa = 0;
	LOGFONT f;
	TCHAR bwin[] = _T("�����ʤ");
	TCHAR wwin[] = _T("�����ʤ");

	gettextstyle(&f);						// ��ȡ��ǰ��������
	settextcolor(RED);						// ����������ɫ��ɫ
	f.lfHeight = 54;						// ��������߶�Ϊ 12
	f.lfWeight = FW_BLACK;					// ���������ϸ
	_tcscpy(f.lfFaceName, _T("����"));		// ��������Ϊ�����塱(�߰汾 VC �Ƽ�ʹ�� _tcscpy_s ����)
	f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����
	settextstyle(&f);						// ����������ʽ
	for (int i = 0; i < 15; ++i) {
		for (int j = 0; j < 15; ++j) {
			//��ʼ��ʤ������
			judgeLb = (Board[i][j] == 1) && (Board[i+1][j] == 1) && (Board[i+2][j] == 1) && (Board[i+3][j] == 1) && (Board[i+4][j] == 1);
			judgeWb = (Board[i][j] == 1) && (Board[i][j+1] == 1) && (Board[i][j+2] == 1) && (Board[i][j+3] == 1) && (Board[i][j+4] == 1);
			judgeDb = (Board[i][j] == 1) && (Board[i+1][j+1] == 1) && (Board[i+2][j+2] == 1) && (Board[i+3][j+3] == 1) && (Board[i+4][j+4] == 1);
			judgeLa = (Board[i][j] == 2) && (Board[i+1][j] == 2) && (Board[i+2][j] == 2) && (Board[i+3][j] == 2) && (Board[i+4][j] == 2);
			judgeWa = (Board[i][j] == 2) && (Board[i][j+1] == 2) && (Board[i][j+2] == 2) && (Board[i][j+3] == 2) && (Board[i][j+4] == 2);
			judgeDa = (Board[i][j] == 2) && (Board[i+1][j+1] == 2) && (Board[i+2][j+2] == 2) && (Board[i+3][j+3] == 2) && (Board[i+4][j+4] == 2);

			if (judgeLb || judgeWb || judgeDb) {
				outtextxy(400, 420, bwin);
				*win = 1;
			}
			else if (judgeLa || judgeWa || judgeDa) {
				outtextxy(400, 420, wwin);
				*win = 1;
			}
		}
	}
}

void tempinit(void)
{
	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 20; ++j) {
			temp[i][j] = Board[i][j];
		}
	}
}
