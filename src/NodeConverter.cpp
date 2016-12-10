#include "Node.hpp"
#include "NodeConverter.hpp"
#include "stdio.h"

using namespace stk;

namespace jstk {

  Node* NodeConverter::createNodeSine(JNIEnv* env ,jobject jnode, jclass clazz, NodeFactory* factory) {
    jmethodID idMid = env->GetMethodID(clazz, "getId", "()I");
    jint nodeId = env->CallIntMethod(jnode, idMid);
    printf("C NC NodeConverter::createNodeSin nodeId %d\n", nodeId);

    jmethodID freqMid = env->GetMethodID(clazz, "getFrequency", "()D");
    jdouble frequency = env->CallDoubleMethod(jnode, freqMid);
    printf("C NC NodeConverter::createNodeSin frequency %f\n", frequency);

    return factory->nodeSine(nodeId, frequency);
  }

  Node* NodeConverter::createNodeGain(JNIEnv* env ,jobject jnode, jclass clazz, NodeFactory* factory) {
    jmethodID idMid = env->GetMethodID(clazz, "getId", "()I");
    jint nodeId = env->CallIntMethod(jnode, idMid);
    printf("C NC NodeConverter::createNodeGain nodeId %d\n", nodeId);

    jmethodID gainMid = env->GetMethodID(clazz, "getGain", "()D");
    jdouble gain = env->CallDoubleMethod(jnode, gainMid);
    printf("C NC NodeConverter::createNodeGain gain %f\n", gain);

    return factory->nodeGain(nodeId, gain);
  }

  Node* NodeConverter::createNodeSequence(JNIEnv* env ,jobject jnode, jclass clazz, NodeFactory* factory) {
    jmethodID idMid = env->GetMethodID(clazz, "getId", "()I");
    jint nodeId = env->CallIntMethod(jnode, idMid);
    printf("C NC NodeConverter::createNodeSeq nodeId %d\n", nodeId);

    jmethodID getChildrenMid = env->GetMethodID(clazz, "getChildren", "()Ljava/util/List;");
    printf("C NC NodeConverter::createNodeSeq getChildrenMid %d\n", getChildrenMid);
    jobject lObj = env->CallObjectMethod(jnode, getChildrenMid);
    printf("C NC NodeConverter::createNodeSeq lObj %p\n", lObj);
    jclass clazz1 = env->GetObjectClass(lObj);

    jmethodID sizeMid = env->GetMethodID(clazz1, "size", "()I");
    printf("C NC NodeConverter::createNodeSeq sizeMid %d\n", sizeMid);
    jmethodID getMid = env->GetMethodID(clazz1, "get", "(I)Ljava/lang/Object;");
    printf("C NC NodeConverter::createNodeSeq getMid %d\n", getMid);

    jint size = env->CallIntMethod(lObj, sizeMid);
    std::list<Node*> v;
    for (int i=0; i<size; i++) {
      jobject dObj = env->CallObjectMethod(lObj, getMid, i);
      printf("C NC NodeConverter::createNodeSeq dobj %p\n", dObj);
      Node* n = this->createNode(env, dObj, factory);
      v.push_back(n);
    }  
    return factory->nodeSequence(nodeId, v);

  }


  Node* NodeConverter::createNode(JNIEnv* env ,jobject jnode, NodeFactory* nodeFactory) {
    printf("C NC NodeConverter::createNode %p %p\n", env, jnode);
    jclass clazz = env->GetObjectClass(jnode);
    jmethodID mid = env->GetMethodID(clazz, "getNodeClassOrdinal", "()I");
    jint nodeClassOrd = env->CallIntMethod(jnode, mid);
    printf("C NC NodeConverter::createNode nodeClassOrd %d\n", nodeClassOrd);
    switch (nodeClassOrd) {
      case NODE_CLASS_SINE:
        return this->createNodeSine(env, jnode, clazz, nodeFactory);
      case NODE_CLASS_GAIN:
        return this->createNodeGain(env, jnode, clazz, nodeFactory);
      case NODE_CLASS_SEQUENCE:
        return this->createNodeSequence(env, jnode, clazz, nodeFactory);
      case NODE_CLASS_SUM:
        throw std::domain_error("NodeConverter::createNode - NODE_CLASS_SUM - NOT YET IMPLEMENTED ");
      default:
        char* msg;
        sprintf(msg, "Undefined node class ordinal %d", nodeClassOrd);
        throw std::domain_error(msg);
    }
  }

}
