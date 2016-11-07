#pragma once
#include <string>
#include "RCObject.h"
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
	struct StringValue:public RCObject {
		char* vdata;

		StringValue(const char* initValue);
		~StringValue();
	};
	StringValue* value;
};

