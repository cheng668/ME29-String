#pragma once
#include <string>
/*引用计数类*/
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

		/*可共享标志，防止出现先创建指针再赋值的情况：
		String s1 = "Hello" ;
		char *p = &s1[1] ;
		String s2 = s1 ; 
		可共享：true  */
		bool shareable; 


		StringValue(const char* initValue);
		~StringValue();
	};
	StringValue* value;
};

