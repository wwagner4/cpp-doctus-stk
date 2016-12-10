#include "Node.hpp"
#include "NodeConverter.hpp"
#include "stdio.h"

using namespace stk;

namespace jstk {

  Node* NodeConverter::createNodeSine(JNIEnv* env ,jobject jnode, jclass clazz, NodeFactory* factory) {
    jmethodID idMid = env->GetMethodID(clazz, "getId", "()I");
    jint nodeId = env->CallIntMethod(jnode, idMid);

    jmethodID freqMid = env->GetMethodID(clazz, "getFrequency", "()D");
    jdouble frequency = env->CallDoubleMethod(jnode, freqMid);

    return factory->nodeSine(nodeId, frequency);
  }

  Node* NodeConverter::createNodeGain(JNIEnv* env ,jobject jnode, jclass clazz, NodeFactory* factory) {
    jmethodID idMid = env->GetMethodID(clazz, "getId", "()I");
    jint nodeId = env->CallIntMethod(jnode, idMid);

    jmethodID gainMid = env->GetMethodID(clazz, "getGain", "()D");
    jdouble gain = env->CallDoubleMethod(jnode, gainMid);

    return factory->nodeGain(nodeId, gain);
  }

  Node* NodeConverter::createNodeSequence(JNIEnv* env ,jobject jnode, jclass clazz, NodeFactory* factory) {
    jmethodID idMid = env->GetMethodID(clazz, "getId", "()I");
    jint nodeId = env->CallIntMethod(jnode, idMid);

    jmethodID getChildrenMid = env->GetMethodID(clazz, "getChildren", "()Ljava/util/List;");
    jobject lObj = env->CallObjectMethod(jnode, getChildrenMid);
    jclass clazz1 = env->GetObjectClass(lObj);

    jmethodID sizeMid = env->GetMethodID(clazz1, "size", "()I");
    jmethodID getMid = env->GetMethodID(clazz1, "get", "(I)Ljava/lang/Object;");

    jint size = env->CallIntMethod(lObj, sizeMid);
    std::list<Node*> v;
    for (int i=0; i<size; i++) {
      jobject dObj = env->CallObjectMethod(lObj, getMid, i);
      Node* n = this->createNode(env, dObj, factory);
      v.push_back(n);
    }  
    return factory->nodeSequence(nodeId, v);

  }


  Node* NodeConverter::createNode(JNIEnv* env ,jobject nodeObj, NodeFactory* nodeFactory) {
    jclass clazz = env->GetObjectClass(nodeObj);
    jmethodID mid = env->GetMethodID(clazz, "getNodeClassOrdinal", "()I");
    jint nodeClassOrd = env->CallIntMethod(nodeObj, mid);
    switch (nodeClassOrd) {
      case NODE_CLASS_SINE:
        return this->createNodeSine(env, nodeObj, clazz, nodeFactory);
      case NODE_CLASS_GAIN:
        return this->createNodeGain(env, nodeObj, clazz, nodeFactory);
      case NODE_CLASS_SEQUENCE:
        return this->createNodeSequence(env, nodeObj, clazz, nodeFactory);
      case NODE_CLASS_SUM:
        throw std::domain_error("NodeConverter::createNode - NODE_CLASS_SUM - NOT YET IMPLEMENTED ");
      default:
        char* msg;
        sprintf(msg, "Undefined node class ordinal %d", nodeClassOrd);
        throw std::domain_error(msg);
    }
  }

}
