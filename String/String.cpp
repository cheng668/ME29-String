#include "String.h"

String::StringValue::StringValue(const char* initValue)
{
	vdata = new char[strlen(initValue) + 1];
	strcpy(vdata, initValue);
	addReference();
}

String::StringValue::~StringValue() {
	delete[] vdata;
}

String::String(const char* initValue):value(new StringValue(initValue))
{
}

String::~String()
{
	value->removeReference();  //���ü���Ϊ0���ͷ��ڴ�
}

String::String(const String& rhs)
{
	if (value->isShareable())  //�����־Ϊtrue
	{
		value = rhs.value;
		value->addReference(); //�����ڴ棬ֻ����������
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

	value->removeReference(); //ԭ����ֵ��һ�����Ϊ0����ɾ���ڴ�	
		
	//ָ��ָ����ֵ������ֵ��һ
	if (rhs.value->isShareable())
	{
		value = rhs.value;
		value->addReference();
	}
	else
	{
		value = new StringValue(rhs.value->vdata);
	}

	return *this;
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
	value->markUnshareable();  //�ɹ����־��false
	return value->vdata[index];
}


