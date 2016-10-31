#pragma once
#include <string>
/*���ü�����*/
class String
{
public:
	explicit String(const char* initValue = "");
	explicit String(const String& rhs);
	String& operator=(const String& rhs);
	const char& operator[](int index) const;
	char& operator[](int index);
	~String();

private:
	struct StringValue {
		int refCount;
		char* vdata;

		/*�ɹ����־����ֹ�����ȴ���ָ���ٸ�ֵ�������
		String s1 = "Hello" ;
		char *p = &s1[1] ;
		String s2 = s1 ; 
		�ɹ���true  */
		bool shareable; 


		StringValue(const char* initValue);
		~StringValue();
	};
	StringValue* value;
};

