#include "SineWave.h"
#include "RtWvOut.h"

namespace dstk {

enum ValueType {
	frequency, gain
};

class Node {

public:
	virtual stk::StkFloat tick() = 0;
	virtual void keyOn() = 0;
	virtual void keyOff() = 0;
	virtual void setValue(ValueType type, stk::StkFloat value) = 0;
	virtual ~Node() {
	}
	;

};

class NodeFactory {

public:
	Node* nodeSine(stk::StkFloat frequency);
	Node* nodeGain(stk::StkFloat gain);
	Node* nodeSequence(std::vector<Node*> nodes);
	Node* nodeSum(std::vector<Node*> nodes);
};

}
