// PhantomEngineDLL.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "PhantomEngineDLL.h"


// ���ǵ���������һ��ʾ��
PHANTOMENGINEDLL_API int nPhantomEngineDLL=0;

// ���ǵ���������һ��ʾ����
PHANTOMENGINEDLL_API int fnPhantomEngineDLL(void)
{
    return 42;
}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� PhantomEngineDLL.h
CPhantomEngineDLL::CPhantomEngineDLL()
{
    return;
}
