#include "checkIntersection.h"

template <class T1, class T2> bool isIntersecting(T1& obj1, T2& obj2)
{
	return obj1.right() > obj2.left() && obj1.left() < obj2.right() && obj1.bottom() > obj2.top() && obj1.top() < obj2.bottom();
}