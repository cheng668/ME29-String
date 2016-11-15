#pragma once
/*smart pointers to RCObject*/
template<class T>
class RCPtr {
public:
	RCPtr(T* realPtr = 0);
	RCPtr(const RCPtr& rhs);
	~RCPtr();

	RCPtr& operator=(const RCPtr& rhs);
	T* operator->() const;
	T& operator&() const;
private:
	T* pointee;
	void init();
};
/*工具函数，用于判断共享开关是否打开，并增大计量数*/
template<class T>
void
RCPtr<T>::init()
{
	if (pointee == 0)
	{
		return;
	}
	if (!pointee->isShareable())
	{
		pointee = new T(*pointee);
	}
	pointee->addReference();
}
/*管理类RCObject继承类指针pointee的构造函数*/
template<class T>
RCPtr<T>::RCPtr(T* realPtr /* = 0 */) :pointee(realPtr)
{
	init();
}
/*拷贝赋值构造函数*/
template<class T>
RCPtr<T>::RCPtr(const RCPtr& rhs) :pointee(rhs.pointee)
{
	init();
}
/*析构函数，释放指针*/
template<class T>
RCPtr<T>::~RCPtr()
{
	if (pointee)
	{
		pointee->removeReference();
	}
}
/*拷贝赋值函数，减小原有指针对象的计量数，并重新拷贝赋值，或者通过init()拷贝构造新对象，最后增加计量数*/
template<class T>
RCPtr<T>&
RCPtr<T>::operator =(const RCPtr& rhs)
{
	if (pointee != rhs.pointee)
	{
		if (pointee)
		{
			pointee->removeReference();
		}
		pointee = rhs.pointee;//指针赋值，进行浅拷贝
		init();
		
	}
	return *this;
}
/*返回指针*/
template<class T>
T*
RCPtr<T>::operator ->() const
{
	return pointee;
}
/*返回引用*/
template<class T>
T&
RCPtr<T>::operator &() const
{
	return *pointee;
}
