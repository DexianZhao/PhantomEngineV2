#ifndef __PHANTOM_LANGUAGE_H__
#define	__PHANTOM_LANGUAGE_H__

#pragma once

#include "PhantomManager.h"
//ת���ɵ�ǰ��ָ���Ĺ�������
namespace Phantom{

	PHANTOM_API const char*		Lan(const char* szID, const char* szDefault);
	struct ConfigText
	{
		Name					id;
		Text					value;
		ConfigText(){}
		~ConfigText(){
			value.clear();
		}
	};

	class PHANTOM_API CLanguageFile
	{
	public:
		enum Language
		{
			Chiness = 0,//���ļ���
			English,//Ӣ��
			Korean,//����
			Japaness,//����
			ChinessFan,//����
		};
		CLanguageFile(void);
		~CLanguageFile(void);
		//
		inline	BOOL				IsChiness(){return (m_nLanguage == Chiness);}
		inline	BOOL				IsChinessFan(){return (m_nLanguage == ChinessFan);}
		inline	BOOL				IsEnglish(){return (m_nLanguage == English);}
		inline	BOOL				IsKorean(){return (m_nLanguage == Korean);}
		inline	BOOL				IsJapaness(){return (m_nLanguage == Japaness);}
		//
		const char*					GetText(const char* szID, const char* szDefaultValue);	//����һ��������Ϣ
#ifdef WIN32_OS
		VOID						SetText(const char* szID, const char* szDefaultValue);	//����һ��������Ϣ
		VOID						SaveToFile();							//����ļ�����
#endif
		VOID						LoadFromFile(const char* lanFile);							//��ȡ�ļ�
		VOID						Destroy();
		const char*					GetDlgFile(const char* szFile);
		const char*					GetPath(){return m_lan;}
		const char*					GetPath(int type);
		char						m_lan[32];
	protected:
		int							m_nLanguage;
		std::vector<ConfigText*>	m_texts;
		BOOL						m_added;
	};

	PHANTOM_API CLanguageFile*					GetLanguagePtr();

#ifdef WIN32_OS
	PHANTOM_API CLanguageFile*					GetLanguageDebug();
#endif

};


#endif
