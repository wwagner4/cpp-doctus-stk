#include <cstdio>
#include <vector>
#include <random>

#include "Node.hpp"
#include "SineWave.h"
#include "RtWvOut.h"

using namespace stk;

namespace dstk {

class NodeSine: public Node {

	stk::SineWave sineWave;

public:

	NodeSine() {
		printf("NodeSine\n");
		sineWave.setFrequency(440);
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
	void setFrequency(StkFloat frequency) {
		sineWave.setFrequency(frequency);
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
	void setGain(StkFloat gain) {
		gain_ = gain;
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

};

}

dstk::Node* createSine(StkFloat frequency, StkFloat gain) {
	dstk::NodeSine* sine = new dstk::NodeSine();
	sine->setFrequency(frequency);

	dstk::NodeGain* gain_ = new dstk::NodeGain(gain);

	dstk::NodeSequence* seq = new dstk::NodeSequence();
	seq->addNode(sine);
	seq->addNode(gain_);

	return seq;
}

dstk::Node* createNode() {
	dstk::NodeSum* sum = new dstk::NodeSum();
	StkFloat freq = rand() % 400 + 200;
	StkFloat gain = 0.01;
	for (int i=1; i <= 200; i++) {
		dstk::Node* n = createSine(freq, gain);
		sum->addNode(n);
		gain *= 0.9;
		freq *= 1.02;
	}
	return sum;
}

int main() {
	Stk::showWarnings(true);

	dstk::Node* node = createNode();
	node->keyOn();
	RtWvOut *dac = 0;
	dac = new RtWvOut(2);
	for (int f = 0; f < 200000; f++) {
		stk::StkFloat v = node->tick();
		dac->tick(v);
	}
	node->keyOff();
	delete node;
	delete dac;
	return 0;
}

