#include<windows.h>

#define NUM 300

LRESULT CALLBACK WndProc(HWND hwnd,UINT msg,WPARAM wp,LPARAM lp);

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	static int iArr[NUM][4];
	HDC hdc,hdcmem;
	int x1,x2,y1,y2;
	HWND hwnd;
	int cx,cy,i,j;
	HBITMAP hbm;

	hwnd=GetDesktopWindow();
	if(LockWindowUpdate(hwnd))
	{
		hdc=GetDCEx(hwnd,NULL,DCX_CACHE|DCX_LOCKWINDOWUPDATE);
		hdcmem=CreateCompatibleDC(hdc);
		cx=GetSystemMetrics(SM_CXSCREEN)/10;
		cy=GetSystemMetrics(SM_CYSCREEN)/10;
		hbm=CreateCompatibleBitmap(hdc,cx,cy);
		SelectObject(hdcmem,hbm);

		srand((int)GetCurrentTime());

		for(i=0;i<2;i++)
		 for(j=0;j<NUM;j++)
		 {
			 if(i==0)
			 {
				 iArr[j][0]=x1=cx*(rand()%10);
				 iArr[j][1]=y1=cy*(rand()%10);
				 iArr[j][2]=x2=cx*(rand()%10);
				 iArr[j][3]=y2=cy*(rand()%10);
			 }
			 else
			 {
                 x1=iArr[NUM-1-j][0];
				 y1=iArr[NUM-1-j][1];
				 x2=iArr[NUM-1-j][2];
				 y2=iArr[NUM-1-j][3];
			 }
			 BitBlt(hdcmem,0,0,cx,cy,hdc,x1,y1,SRCCOPY);
			 BitBlt(hdc,x1,y1,cx,cy,hdc,x2,y2,SRCCOPY);
			 BitBlt(hdc,x2,y2,cx,cy,hdcmem,0,0,SRCCOPY);

			 Sleep(10);
		 }
	}

	DeleteDC(hdcmem);
	ReleaseDC(hwnd,hdc);
	DeleteObject(hbm);

	LockWindowUpdate(NULL);

	return FALSE;
}
