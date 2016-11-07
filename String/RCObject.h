#pragma once
/*���ü������࣬��MORE EFFECTIVE C++�� P195 */
class RCObject
{
public:
	RCObject();
	RCObject(const RCObject& rhs);
	RCObject& operator =(const RCObject& rhs);
	//���鹹����������ֻΪ����
	virtual ~RCObject() = 0;
	void addReference();
	void removeReference();
	void markUnshareable();
	bool isShareable() const;
	bool isShared() const;
private:
	int refCount;
	/*�ɹ����־����ֹ�����ȴ���ָ���ٸ�ֵ�������
	String s1 = "Hello" ;
	char *p = &s1[1] ;
	String s2 = s1 ;
	�ɹ���true  */
	bool shareable;
};

