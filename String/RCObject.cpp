#include "RCObject.h"


/*refCount�Ĵ�����������ΪrefCount�趨�ʵ���ֵ*/
RCObject::RCObject():refCount(0),shareable(true)
{
}

RCObject::RCObject(const RCObject&):refCount(0),shareable(true)
{
}
//�����ܸ�ֵ
RCObject& RCObject::operator=(const RCObject&) { return *this; }
//���Ӽ�����
void RCObject::addReference()
{
	++refCount;
}
//�رչ����־
void RCObject::markUnshareable()
{
	shareable = false;
}
//��С�����������Ϊ0��ɾ������
void RCObject::removeReference()
{
	if (--refCount == 0) delete this;
}
//���ع����־
bool RCObject::isShareable() const
{
	return shareable;
}
//�����Ƿ񱻹�����������Ϊtrue
bool RCObject::isShared() const
{
	return refCount > 1;
}

RCObject::~RCObject(){}