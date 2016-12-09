#include "SineWave.h"
#include "RtWvOut.h"
#include <map>
#include <list>

#ifndef _Included_Node
#define _Included_Node

#define VALUE_TYPE_FREQUENCY 0
#define VALUE_TYPE_GAIN 1

namespace jstk {

  class Node {

  public:
    virtual stk::StkFloat tick() = 0;
    virtual void keyOn() = 0;
    virtual void keyOff() = 0;
    virtual void setValue(int valueType, stk::StkFloat value) = 0;
    virtual int getId() = 0;
    virtual ~Node() {};

  private:
    int id;

  };

  class NodeFactory {

  private:
    std::map<int, Node*> nodeMap;

  public:
    Node* nodeSine(int id, stk::StkFloat frequency);
    Node* nodeGain(int id, stk::StkFloat gain);
    Node* nodeSequence(int id, std::list<Node*> nodes);
    Node* nodeSum(int id, std::list<Node*> nodes);

    Node* findNode(int id);
  };
}
#endif

