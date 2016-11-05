#include "Stk.h"

namespace dstk {

class Node {

public:

	virtual stk::StkFloat tick() = 0;
	virtual void keyOn() = 0;
	virtual void keyOff() = 0;
	virtual ~Node() {
	};

};
}
