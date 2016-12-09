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
    Node* convert(JNIEnv* env ,jobject jgraph, NodeFactory* nodeFactory);

  };

}
#endif
