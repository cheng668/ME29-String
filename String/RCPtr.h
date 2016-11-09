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
/*���ߺ����������жϹ������Ƿ�򿪣������������*/
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
/*������RCObject�̳���ָ��pointee�Ĺ��캯��*/
template<class T>
RCPtr<T>::RCPtr(T* realPtr /* = 0 */) :pointee(realPtr)
{
	init();
}
/*������ֵ���캯��*/
template<class T>
RCPtr<T>::RCPtr(const RCPtr& rhs) :pointee(rhs.pointee)
{
	init();
}
/*�����������ͷ�ָ��*/
template<class T>
RCPtr<T>::~RCPtr()
{
	if (pointee)
	{
		pointee->removeReference();
	}
}
/*������ֵ��������Сԭ��ָ�����ļ������������¿�����ֵ������ͨ��init()���������¶���������Ӽ�����*/
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
		pointee = rhs.pointee;//����RCObject�̳������Ŀ�����ֵ�����������е���StringValue���Ĭ�Ͽ�����ֵ����������ǳ����
		init();
		
	}
	return *this;
}
/*����ָ��*/
template<class T>
T*
RCPtr<T>::operator ->() const
{
	return pointee;
}
/*��������*/
template<class T>
T&
RCPtr<T>::operator &() const
{
	return *pointee;
}