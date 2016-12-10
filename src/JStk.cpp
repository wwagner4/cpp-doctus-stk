#include "JStk.h"
#include "jni.h"

#include <cstdio>
#include <list>
#include <map>
#include <random>

#include "Node.hpp"
#include "NodeConverter.hpp"
#include "SineWave.h"
#include "RtWvOut.h"

using namespace stk;
using namespace jstk;

/**
 * Holds all resources necessary for executing a graph
 */
class Graph {
  private:
    Node* node;
    RtWvOut* dac;

  public:

    int id;
    bool running = true;

    Graph(int id, Node* node) {
      this->id = id;
      this->node = node;
      this->dac = new RtWvOut(2);
    }

    ~Graph() {
      running = false;
      delete this->node;
      delete this->dac;
    }

    void tick() {
      stk::StkFloat v = node->tick();
      dac->tick(v);
    }
};

NodeFactory factory;
NodeConverter conv;
std::map<int, Graph*> graphs;

/**
 * Utillity function for accessing 'map'
 */
void addToGraphs(int id, Graph* graph) {
  std::pair<std::map<int, Graph*>::iterator,bool> ret;
  ret = graphs.insert (std::pair<int, Graph*>(id, graph));
  if (ret.second==false) {
    delete graph;
    char* msg;
    sprintf(msg, "ERROR: A graph with id %d already exists", id);
    throw std::domain_error(msg);
  } else {
    printf("C addToGraphs %d\n", id);
  }
}

/**
 * Utillity function for accessing 'map'
 */
Graph* removeFromGraphs(int id) {
  std::map<int, Graph*>::iterator it;
  it = graphs.find(id);
  if (it != graphs.end()) {
    graphs.erase(it);
    printf("C removeFromGraphs %d\n", id);
    return it->second;
  } else {
    char* msg;
    sprintf(msg, "No graph with id %d existed", id);
    throw std::domain_error(msg);
  }
}

JNIEXPORT void JNICALL Java_JStk_addGraph
    (JNIEnv* env , jobject, jint graphId, jobject jgraph) {
  try {
    printf("C addGraph %d %p\n", graphId, jgraph);
    Stk::showWarnings(true);

    Node* node = conv.createNode(env, jgraph, &factory);
    Graph* graph = new Graph(graphId, node);
    addToGraphs(graphId, graph);

    while(graph->running) {
      graph->tick();
    }
  } catch(std::exception& e) {
    printf("ERROR: %s in 'Java_JStk_addGraph'\n", e.what());
    exit(-1);
  } catch (...) {
    printf("ERROR: An unknown exception occurred in 'Java_JStk_addGraph'\n");
    exit(-2);
  }
}

JNIEXPORT void JNICALL Java_JStk_removeGraph
  (JNIEnv *, jobject, jint graphId) {
  try {
    printf("C removeGraph %d\n", graphId);
    Graph* graph = removeFromGraphs(graphId);
    graph->running = false;
    delete graph;
  } catch(std::exception& e) {
    printf("ERROR: %s in 'Java_JStk_removeGraph'\n'", e.what());
    exit(-1);
  } catch (...) {
    printf("ERROR: An unknown exception occurred in 'Java_JStk_addGraph'\n");
    exit(-2);
  }
}
JNIEXPORT void JNICALL Java_JStk_setValue
  (JNIEnv* env, jobject thisObj, jint graphId, jint nodeId, jint valueTypeOrdinal, jdouble value) {
  try {
    printf("C Java_JStk_setValue %d %d %d %f\n", graphId, nodeId, valueTypeOrdinal, value);
  } catch(std::exception& e) {
    printf("ERROR: %s in 'Java_JStk_setValue'\n'", e.what());
    exit(-1);
  } catch (...) {
    printf("ERROR: An unknown exception occurred in 'Java_JStk_setValue'\n");
    exit(-2);
  }
}

