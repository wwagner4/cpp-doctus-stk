#include "Node.hpp"
#include "NodeConverter.hpp"
#include "stdio.h"

using namespace stk;

namespace jstk {

  int id = 0;

  Node* createSine(StkFloat frequency, StkFloat gain, NodeFactory* f) {
    Node* sine = f->nodeSine(id++, frequency);

    Node* gain_ = f->nodeGain(id++, gain);

    std::list<Node*> v;

    v.push_back(sine);
    v.push_back(gain_);

    Node* seq = f->nodeSequence(id++, v);

    return seq;
  }

  Node* createNode(NodeFactory* factory) {
    return createSine(500, 1.0, factory);
  }


  Node* NodeConverter::convert(JNIEnv* env ,jobject jnode, NodeFactory* nodeFactory) {
    printf("C NodeConverter::convert %p %p\n", env, jnode);
    return createNode(nodeFactory);
  }

}
