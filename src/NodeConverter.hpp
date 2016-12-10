#include "jni.h"
#include "node.hpp"

#ifndef _Included_NodeConverter
#define _Included_NodeConverter

#define NODE_CLASS_SINE 0
#define NODE_CLASS_GAIN 1
#define NODE_CLASS_SEQUENCE 2
#define NODE_CLASS_SUM 3

namespace jstk {

  class NodeConverter {

  public:
    Node* createNode(JNIEnv* env ,jobject jgraph, NodeFactory* nodeFactory);
    Node* createNodeSine(JNIEnv* env ,jobject jnode, jclass clazz, NodeFactory* factory);
    Node* createNodeGain(JNIEnv* env ,jobject jnode, jclass clazz, NodeFactory* factory);
    Node* createNodeSequence(JNIEnv* env ,jobject jnode, jclass clazz, NodeFactory* factory);
    Node* createNodeSum(JNIEnv* env ,jobject jnode, jclass clazz, NodeFactory* factory);
    std::list<Node*>* createChildren(JNIEnv* env ,jobject nodeObj, jclass nodeClass, NodeFactory* factory);

  };

}
#endif
