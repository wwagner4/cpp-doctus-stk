#include "SineWave.h"
#include "RtWvOut.h"
#include <map>

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
	virtual int getId() = 0;
	virtual ~Node() {
	}
	;
private:
	int id;

};

class NodeFactory {

private:
	std::map<int, Node*> nodeMap;

public:
	Node* nodeSine(int id, stk::StkFloat frequency);
	Node* nodeGain(int id, stk::StkFloat gain);
	Node* nodeSequence(int id, std::vector<Node*> nodes);
	Node* nodeSum(int id, std::vector<Node*> nodes);

	Node* findNode(int id);

};


}
