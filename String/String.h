#pragma once
#include <string>
#include "RCObject.h"
#include "RCPtr.h"
/*引用计数类*/
class String
{
public:
	explicit String(const char* initValue = "");
	const char& operator[](int index) const;
	char& operator[](int index);
private:
	struct StringValue:public RCObject {
		char* vdata;
		StringValue(const StringValue& rhs);
		StringValue(const char* initValue);
		void init(const char* initValue);
		~StringValue();
	};
	RCPtr<StringValue> value;
};

