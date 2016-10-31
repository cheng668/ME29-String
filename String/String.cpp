#include "String.h"

String::StringValue::StringValue(const char* initValue) :refCount(1), shareable(true)
{
	vdata = new char[strlen(initValue) + 1];
	strcpy(vdata, initValue);
}

String::StringValue::~StringValue() {
	delete[] vdata;
}

String::String(const char* initValue):value(new StringValue(initValue))
{
}

String::~String()
{
	if (--value->refCount == 0) delete value;  //引用计数为0才释放内存
}

String::String(const String& rhs)
{
	if (value->shareable)  //共享标志为true
	{
		value = rhs.value;
		++value->refCount; //共享内存，只增加引用数
	}
	else
	{
		value = new StringValue(rhs.value->vdata);   //共享标志为false,则新建对象
	}
}

String& String::operator=(const String& rhs)
{
	if (rhs.value == value)  //对自己赋值返回自己
	{
		return *this;
	}

	if (--value->refCount == 0)  //原计数值减一，如果为0，则删除内存
	{
		delete value;
	}
	//指针指向新值，计数值加一
	value = rhs.value;
	++value->refCount;
	return *this;
}

const char& String::operator[](int index) const
{
	return value->vdata[index];
}

char& String::operator[](int index)
{
	if (value->refCount > 1)
	{
		--value->refCount;
		value = new StringValue(value->vdata);
	}
	value->shareable = false;  //可共享标志置false
	return value->vdata[index];
}


