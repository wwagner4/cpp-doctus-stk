#include "Node.hpp"

namespace dstk {

class NodeSine: public Node {

	stk::SineWave sineWave;

public:

	NodeSine(stk::StkFloat frequency) {
		printf("NodeSine\n");
		sineWave.setFrequency(frequency);
	}
	~NodeSine() {
		printf("~NodeSine\n");
	}
	stk::StkFloat tick() {
		stk::StkFloat v = sineWave.tick();
		return v;
	}
	void keyOn() {
		printf("keyOn\n");
		// Nothing to do
	}
	void keyOff() {
		printf("keyOff\n");
		// Nothing to do
	}
	void setValue(ValueType type, stk::StkFloat value) {
		switch (type) {
		case frequency:
			sineWave.setFrequency(value);
			break;
		default:
			printf("Could not set value for %d in NodeGain\n", type);
		}
	}

};

class NodeGain: public Node {

	stk::StkFloat gain_;

public:
	NodeGain(stk::StkFloat gain) {
		gain_ = gain;
		printf("NodeSine\n");
	}
	NodeGain() {
		gain_ = 1.0;
		printf("NodeSine\n");
	}
	stk::StkFloat tick() {
		return gain_;
	}
	void keyOn() {
		printf("keyOn\n");
		// Nothing to do
	}
	void keyOff() {
		printf("keyOff\n");
		// Nothing to do
	}
	void setValue(ValueType type, stk::StkFloat value) {
		switch (type) {
		case gain:
			gain_ = value;
			break;
		default:
			printf("Could not set value for %d in NodeGain\n", type);
		}
	}

};

class NodeSequence: public Node {

	std::vector<Node*> nodes;

public:
	NodeSequence() {
		printf("NodeSequence\n");
	}
	~NodeSequence() {
		printf("~NodeSequence\n");
		for (std::vector<Node*>::size_type i = 0; i != nodes.size(); i++) {
			delete nodes[i];
		}
	}
	stk::StkFloat tick() {
		stk::StkFloat prod = 1.0;
		for (std::vector<Node*>::size_type i = 0; i != nodes.size(); i++) {
			prod *= nodes[i]->tick();
		}
		return prod;
	}
	void keyOn() {
		printf("keyOn\n");
		// Nothing to do
	}
	void keyOff() {
		printf("keyOff\n");
		// Nothing to do
	}
	void addNode(Node* node) {
		printf("addNode\n");
		nodes.push_back(node);
	}
	void setValue(ValueType type, stk::StkFloat value) {
		printf("Could not set value for %d in NodeSequence\n", type);
	}

};

class NodeSum: public Node {

	std::vector<Node*> nodes;

public:

	NodeSum() {
		printf("NodeSum\n");
	}
	~NodeSum() {
		printf("~NodeSum\n");
		for (std::vector<Node*>::size_type i = 0; i != nodes.size(); i++) {
			delete nodes[i];
		}
	}
	stk::StkFloat tick() {
		stk::StkFloat sum = 0.0;
		for (std::vector<Node*>::size_type i = 0; i != nodes.size(); i++) {
			sum += nodes[i]->tick();
		}
		return sum;
	}
	void keyOn() {
		printf("keyOn\n");
		// Nothing to do
	}
	void keyOff() {
		printf("keyOff\n");
		// Nothing to do
	}
	void addNode(Node* node) {
		printf("addNode\n");
		nodes.push_back(node);
	}
	void setValue(ValueType type, stk::StkFloat value) {
		printf("Could not set value for %d in NodeSum\n", type);
	}

};

Node* NodeFactory::nodeSine(stk::StkFloat frequency) {
	return new NodeSine(frequency);
}
Node* NodeFactory::nodeGain(stk::StkFloat gain) {
	return new NodeGain(gain);
}
Node* NodeFactory::nodeSequence(std::vector<Node*> nodes) {
	NodeSequence* re = new NodeSequence();
	for (Node* node : nodes) {
		re->addNode(node);
	}
	return re;
}
Node* NodeFactory::nodeSum(std::vector<Node*> nodes) {
	NodeSum* re = new NodeSum();
	for (Node* node : nodes) {
		re->addNode(node);
	}
	return re;
}

}

