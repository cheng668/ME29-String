#pragma once
/*引用计数基类，《MORE EFFECTIVE C++》 P195 */
class RCObject
{
public:
	RCObject();
	RCObject(const RCObject& rhs);
	RCObject& operator =(const RCObject& rhs);
	//纯虚构函数，此类只为基类
	virtual ~RCObject() = 0;
	void addReference();
	void removeReference();
	void markUnshareable();
	bool isShareable() const;
	bool isShared() const;
private:
	int refCount;
	/*可共享标志，防止出现先创建指针再赋值的情况：
	String s1 = "Hello" ;
	char *p = &s1[1] ;
	String s2 = s1 ;
	可共享：true  */
	bool shareable;
};

