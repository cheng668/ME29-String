#include "RCObject.h"


/*refCount的创建者有责任为refCount设定适当的值*/
RCObject::RCObject():refCount(0),shareable(true)
{
}

RCObject::RCObject(const RCObject&):refCount(0),shareable(true)
{
}
//不可能赋值
RCObject& RCObject::operator=(const RCObject&) { return *this; }
//增加计量数
void RCObject::addReference()
{
	++refCount;
}
//关闭共享标志
void RCObject::markUnshareable()
{
	shareable = false;
}
//减小计量数，如果为0则删除对象
void RCObject::removeReference()
{
	if (--refCount == 0) delete this;
}
//返回共享标志
bool RCObject::isShareable() const
{
	return shareable;
}
//对象是否被共享，被共享则为true
bool RCObject::isShared() const
{
	return refCount > 1;
}

RCObject::~RCObject(){}