/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		PlumThread.h
* @brief	This Program is PlumThread DLL Project.
* @author	Alopex/Helium
* @version	v1.01a
* @date		2018-1-14	v1.00a	alopex	Create Project.
* @date		2018-7-20	v1.01a	alopex	Modify Call Mode.
*/
#pragma once

#ifndef __PLUMTHREAD_H_
#define __PLUMTHREAD_H_

//Include Plum Common Header File
#include "PlumCommon.h"

//Macro Definition
#ifdef PLUMTHREAD_EXPORTS
#define PLUMTHREAD_API	__declspec(dllexport)
#else
#define PLUMTHREAD_API	__declspec(dllimport)
#endif

#define PLUMTHREAD_CALLMODE	__stdcall

//Class Definition
//CPlumThreadBase基类
class PLUMTHREAD_API CPlumThreadBase
{
private:

public:
	CPlumThreadBase();													//构造
	virtual ~CPlumThreadBase();											//析构
	virtual void PLUMTHREAD_CALLMODE PlumThreadRun() = 0;				//纯虚函数
};

//CPlumThread派生类
class PLUMTHREAD_API CPlumThread :public CPlumThreadBase
{
private:
	HANDLE m_hThread;													//线程句柄
	DWORD m_dwThreadID;													//线程号
	volatile bool m_bThreadRun;											//线程运行
	CPlumThreadBase* m_pThreadBase;										//线程基类指针

private:
	static DWORD PLUMTHREAD_CALLMODE PlumThreadProc(LPVOID pThreadPara);//线程处理函数(静态)

public:
	CPlumThread();														//构造
	~CPlumThread();														//析构
	CPlumThread(CPlumThreadBase* pThreadBase);							//构造

	DWORD PLUMTHREAD_CALLMODE PlumThreadGetID() const;								//线程ID获取

	virtual bool PLUMTHREAD_CALLMODE PlumThreadInit(bool bSuspend = false);			//线程初始化(挂起:true)
	virtual void PLUMTHREAD_CALLMODE PlumThreadSetPriority(int nPriority);			//线程设置优先级(THREAD_PRIORITY_ABOVE_NORMAL)
	virtual void PLUMTHREAD_CALLMODE PlumThreadRun();								//线程运行(重写)
	virtual void PLUMTHREAD_CALLMODE PlumThreadJoin(int nTimeOut = -1);				//线程等待结束
	virtual void PLUMTHREAD_CALLMODE PlumThreadResume();							//线程恢复
	virtual void PLUMTHREAD_CALLMODE PlumThreadSuspend();							//线程挂起
	virtual bool PLUMTHREAD_CALLMODE PlumThreadTerminate(DWORD dwExitCode);			//线程终止
	virtual void PLUMTHREAD_CALLMODE PlumThreadExit();								//线程退出
};

#endif