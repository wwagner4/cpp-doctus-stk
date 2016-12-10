#include "Node.hpp"
#include "NodeConverter.hpp"
#include "stdio.h"

using namespace stk;

namespace jstk {

  Node* NodeConverter::createNodeSine(JNIEnv* env ,jobject nodeObj, jclass nodeClass, NodeFactory* factory) {
    jmethodID idMid = env->GetMethodID(nodeClass, "getId", "()I");
    jint nodeId = env->CallIntMethod(nodeObj, idMid);

    jmethodID freqMid = env->GetMethodID(nodeClass, "getFrequency", "()D");
    jdouble frequency = env->CallDoubleMethod(nodeObj, freqMid);

    return factory->nodeSine(nodeId, frequency);
  }

  Node* NodeConverter::createNodeGain(JNIEnv* env ,jobject nodeObj, jclass nodeClass, NodeFactory* factory) {
    jmethodID idMid = env->GetMethodID(nodeClass, "getId", "()I");
    jint nodeId = env->CallIntMethod(nodeObj, idMid);

    jmethodID gainMid = env->GetMethodID(nodeClass, "getGain", "()D");
    jdouble gain = env->CallDoubleMethod(nodeObj, gainMid);

    return factory->nodeGain(nodeId, gain);
  }

  Node* NodeConverter::createNodeSequence(JNIEnv* env ,jobject nodeObj, jclass nodeClass, NodeFactory* factory) {
    jmethodID idMid = env->GetMethodID(nodeClass, "getId", "()I");
    jint nodeId = env->CallIntMethod(nodeObj, idMid);

    jmethodID getChildrenMid = env->GetMethodID(nodeClass, "getChildren", "()Ljava/util/List;");
    jobject lObj = env->CallObjectMethod(nodeObj, getChildrenMid);
    jclass lClass = env->GetObjectClass(lObj);

    jmethodID sizeMid = env->GetMethodID(lClass, "size", "()I");
    jmethodID getMid = env->GetMethodID(lClass, "get", "(I)Ljava/lang/Object;");

    jint size = env->CallIntMethod(lObj, sizeMid);
    std::list<Node*> v;
    for (int i=0; i<size; i++) {
      jobject eObj = env->CallObjectMethod(lObj, getMid, i);
      Node* n = this->createNode(env, eObj, factory);
      v.push_back(n);
    }  
    return factory->nodeSequence(nodeId, v);
  }

  Node* NodeConverter::createNodeSum(JNIEnv* env ,jobject nodeObj, jclass nodeClass, NodeFactory* factory) {
    jmethodID idMid = env->GetMethodID(nodeClass, "getId", "()I");
    jint nodeId = env->CallIntMethod(nodeObj, idMid);

    jmethodID getChildrenMid = env->GetMethodID(nodeClass, "getChildren", "()Ljava/util/List;");
    jobject lObj = env->CallObjectMethod(nodeObj, getChildrenMid);
    jclass lClass = env->GetObjectClass(lObj);

    jmethodID sizeMid = env->GetMethodID(lClass, "size", "()I");
    jmethodID getMid = env->GetMethodID(lClass, "get", "(I)Ljava/lang/Object;");

    jint size = env->CallIntMethod(lObj, sizeMid);
    std::list<Node*> v;
    for (int i=0; i<size; i++) {
      jobject eObj = env->CallObjectMethod(lObj, getMid, i);
      Node* n = this->createNode(env, eObj, factory);
      v.push_back(n);
    }  
    return factory->nodeSum(nodeId, v);
  }

  Node* NodeConverter::createNode(JNIEnv* env ,jobject nodeObj, NodeFactory* factory) {
    jclass nodeClass = env->GetObjectClass(nodeObj);
    jmethodID mid = env->GetMethodID(nodeClass, "getNodeClassOrdinal", "()I");
    jint nodeClassOrd = env->CallIntMethod(nodeObj, mid);
    switch (nodeClassOrd) {
      case NODE_CLASS_SINE:
        return this->createNodeSine(env, nodeObj, nodeClass, factory);
      case NODE_CLASS_GAIN:
        return this->createNodeGain(env, nodeObj, nodeClass, factory);
      case NODE_CLASS_SEQUENCE:
        return this->createNodeSequence(env, nodeObj, nodeClass, factory);
      case NODE_CLASS_SUM:
        return this->createNodeSum(env, nodeObj, nodeClass, factory);
      default:
        char* msg;
        sprintf(msg, "Undefined node class ordinal %d", nodeClassOrd);
        throw std::domain_error(msg);
    }
  }

}
