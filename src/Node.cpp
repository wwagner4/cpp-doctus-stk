#include "Node.hpp"

namespace jstk {

  class NodeSine: public Node {
  
  private:
    stk::SineWave sineWave;
    int id;
  
  public:
  
    NodeSine(int id, stk::StkFloat frequency) {
      //printf("NodeSine\n");
      sineWave.setFrequency(frequency);
      this->id = id;
    }
    ~NodeSine() {
      //printf("~NodeSine\n");
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
    void setValue(int valueType, stk::StkFloat value) {
      switch (valueType) {
      case VALUE_TYPE_FREQUENCY:
        sineWave.setFrequency(value);
        break;
      default:
        printf("Could not set value for %d in NodeGain\n", valueType);
      }
    }
    int getId() {
      return this->id;
    }
  
  };
  
  class NodeGain: public Node {
  
  private:
    int id;
    stk::StkFloat gain_;
  
  public:
    NodeGain(int id, stk::StkFloat gain) {
      gain_ = gain;
      this->id = id;
      //printf("NodeSine\n");
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
    void setValue(int valueType, stk::StkFloat value) {
      switch (valueType) {
      case VALUE_TYPE_GAIN:
        gain_ = value;
        break;
      default:
        printf("Could not set value for %d in NodeGain\n", valueType);
      }
    }
    int getId() {
      return this->id;
    }
  
  };
  
  class NodeSequence: public Node {
  private:
    int id;
    std::list<Node*> nodes;
  
  public:
    NodeSequence(int id, std::list<Node*> nodes_) {
      this->id = id;
      for (Node* n : nodes)
        delete n;
      nodes = nodes_;
    }
    ~NodeSequence() {
      //printf("~NodeSequence\n");
      for (Node* n : nodes)
        delete n;
    }
    stk::StkFloat tick() {
      stk::StkFloat prod = 1.0;
      for (Node* n : nodes) {
        prod *= n->tick();
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
    void setValue(int valueType, stk::StkFloat value) {
      printf("Could not set value for %d in NodeSequence\n", valueType);
    }
    int getId() {
      return this->id;
    }
  
  };
  
  class NodeSum: public Node {
  
  private:
    int id;
    std::list<Node*> nodes;
  
  public:
  
    NodeSum(int id, std::list<Node*> nodes_) {
      this->id = id;
      //printf("NodeSum\n");
      for (Node* n : nodes)
        delete n;
      nodes = nodes_;
    }
    ~NodeSum() {
      printf("~NodeSum\n");
      for (Node* n : nodes)
        delete n;
    }
    stk::StkFloat tick() {
      stk::StkFloat sum = 0.0;
      for (Node* n : nodes) {
        sum += n->tick();
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
    void setValue(int valueType, stk::StkFloat value) {
      printf("Could not set value for %d in NodeSum\n", valueType);
    }
    int getId() {
      return this->id;
    }
  
  };

  Node* NodeFactory::nodeSine(int id, stk::StkFloat frequency) {
    Node* re = new NodeSine(id, frequency);
    return re;
  }
  Node* NodeFactory::nodeGain(int id, stk::StkFloat gain) {
    Node* re = new NodeGain(id, gain);
    return re;
  }
  Node* NodeFactory::nodeSequence(int id, std::list<Node*> nodes) {
    Node* re = new NodeSequence(id, nodes);
    return re;
  }
  Node* NodeFactory::nodeSum(int id, std::list<Node*> nodes) {
    Node* re = new NodeSum(id, nodes);
    return re;
  }
}

