// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� PHANTOMENGINEDLL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// PHANTOMENGINEDLL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef PHANTOMENGINEDLL_EXPORTS
#define PHANTOMENGINEDLL_API __declspec(dllexport)
#else
#define PHANTOMENGINEDLL_API __declspec(dllimport)
#endif

// �����Ǵ� PhantomEngineDLL.dll ������
class PHANTOMENGINEDLL_API CPhantomEngineDLL {
public:
	CPhantomEngineDLL(void);
	// TODO:  �ڴ�������ķ�����
};

extern PHANTOMENGINEDLL_API int nPhantomEngineDLL;

PHANTOMENGINEDLL_API int fnPhantomEngineDLL(void);
