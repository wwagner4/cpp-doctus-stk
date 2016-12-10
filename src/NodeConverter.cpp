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

  Node* createNodeSine(JNIEnv* env ,jobject jnode, jclass clazz, NodeFactory* factory) {
    jmethodID idMid = env->GetMethodID(clazz, "getId", "()I");
    jint nodeId = env->CallIntMethod(jnode, idMid);
    printf("C NC createNodeSin nodeId %d\n", nodeId);

    jmethodID freqMid = env->GetMethodID(clazz, "getFrequency", "()D");
    printf("C NC createNodeSin freqMid %d\n", freqMid);
    jdouble frequency = env->CallDoubleMethod(jnode, freqMid);
    printf("C NC createNodeSin frequency %f\n", frequency);

    return factory->nodeSine(nodeId, frequency);;
  }


  Node* NodeConverter::createNode(JNIEnv* env ,jobject jnode, NodeFactory* nodeFactory) {
    printf("C NC NodeConverter::createNode %p %p\n", env, jnode);
    jclass clazz = env->GetObjectClass(jnode);
    jmethodID mid = env->GetMethodID(clazz, "getNodeClassOrdinal", "()I");
    jint nodeClassOrd = env->CallIntMethod(jnode, mid);
    printf("C NC NodeConverter::createNode nodeClassOrd %d\n", nodeClassOrd);
    switch (nodeClassOrd) {
      case NODE_CLASS_SINE:
        return createNodeSine(env, jnode, clazz, nodeFactory);
      case NODE_CLASS_GAIN:
        throw std::domain_error("NOT YET IMPLEMENTED");
      case NODE_CLASS_SEQUENCE:
        throw std::domain_error("NOT YET IMPLEMENTED");
      case NODE_CLASS_SUM:
        throw std::domain_error("NOT YET IMPLEMENTED");
      default:
        char* msg;
        sprintf(msg, "Undefined node class ordinal %d", nodeClassOrd);
        throw std::domain_error(msg);
    }
  }

}
