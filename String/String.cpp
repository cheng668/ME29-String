#include "String.h"

String::StringValue::StringValue(const char* initValue)
{
	init(initValue);
}

String::StringValue::StringValue(const StringValue& rhs)
{
	init(rhs.vdata);
}

void String::StringValue::init(const char* initValue)
{
	vdata = new char[strlen(initValue) + 1];
	strcpy_s(vdata, strlen(initValue) + 1, initValue);
}

String::StringValue::~StringValue()
{
	delete[] vdata;
}

const char& String::operator[](int index) const
{
	return value->vdata[index];
}

char& String::operator[](int index)
{
	if (value->isShared())
	{
		value->removeReference();
		value = new StringValue(value->vdata);
	}
	value->markUnshareable();  //可共享标志置false
	return value->vdata[index];
}


