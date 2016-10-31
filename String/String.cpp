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
	if (--value->refCount == 0) delete value;  //���ü���Ϊ0���ͷ��ڴ�
}

String::String(const String& rhs)
{
	if (value->shareable)  //�����־Ϊtrue
	{
		value = rhs.value;
		++value->refCount; //�����ڴ棬ֻ����������
	}
	else
	{
		value = new StringValue(rhs.value->vdata);   //�����־Ϊfalse,���½�����
	}
}

String& String::operator=(const String& rhs)
{
	if (rhs.value == value)  //���Լ���ֵ�����Լ�
	{
		return *this;
	}

	if (--value->refCount == 0)  //ԭ����ֵ��һ�����Ϊ0����ɾ���ڴ�
	{
		delete value;
	}
	//ָ��ָ����ֵ������ֵ��һ
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
	value->shareable = false;  //�ɹ����־��false
	return value->vdata[index];
}


