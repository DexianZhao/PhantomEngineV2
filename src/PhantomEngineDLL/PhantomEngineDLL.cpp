// PhantomEngineDLL.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "PhantomEngineDLL.h"


// 这是导出变量的一个示例
PHANTOMENGINEDLL_API int nPhantomEngineDLL=0;

// 这是导出函数的一个示例。
PHANTOMENGINEDLL_API int fnPhantomEngineDLL(void)
{
    return 42;
}

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 PhantomEngineDLL.h
CPhantomEngineDLL::CPhantomEngineDLL()
{
    return;
}
