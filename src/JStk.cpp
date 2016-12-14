#include "JStk.h"
#include "jni.h"

#include <cstdio>
#include <list>
#include <map>
#include <string>
#include <random>
#include <unistd.h>

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

  public:
    int id;
    bool running = true;
    Node* node;

    Graph(int id, Node* node) {
      this->id = id;
      this->node = node;
    }

    ~Graph() {
      running = false;
      delete this->node;
    }

};

/**
 * Holds graphs
 */
class GraphManager {
  
  private:
    std::map<int, Graph*>* graphs = nullptr;
    RtWvOut* dac = nullptr;
    int tickCnt = 0;

  public:
    bool started = false;

    GraphManager() {
      this->graphs = new std::map<int, Graph*>();
      this->dac = new RtWvOut(2);

    }

    ~GraphManager() {
      delete this->dac;
      delete this->graphs;
    }

    void add(int id, Graph* graph) {
      printf("C GraphManager add %d %p\n", id, graph);
      std::pair<std::map<int, Graph*>::iterator,bool> ret;
      printf("C GraphManager add created ret\n");
      ret = graphs->insert (std::pair<int, Graph*>(id, graph));
      printf("C GraphManager add inserted\n");
      if (ret.second==false) {
        delete graph;
        throw std::domain_error("Graph with the given id already existed");
      } 
    }
    
    Graph* remove(int id) {
      printf("C GraphManager remove %d\n", id);
      std::map<int, Graph*>::iterator it;
      it = graphs->find(id);
      printf("C GraphManager remove found iterator %p\n", &it);
      if (it != graphs->end()) {
        graphs->erase(it);
        printf("C GraphManager remove erased\n");
        return it->second;
      } else {
        throw std::domain_error("No graph with the given id existed");
      }
    }

    void tick() {
      tickCnt++;
      StkFloat v = 0.0;
      typedef std::map<int, Graph*>::iterator it_type;
      int i = 0;
      for(it_type iterator = graphs->begin(); iterator != graphs->end(); iterator++) {
    	  Graph* g = iterator->second;
    	  if (g->running) {
    		  i++;
        	  v += iterator->second->node->tick();
    	  }
      }
      dac->tick(v);
    }

    bool hasRunningGraphs() {
    	return graphs->size() > 0;
    }
};


NodeFactory factory;
NodeConverter conv;
GraphManager* graphManager = nullptr;

JNIEXPORT void JNICALL Java_JStk_start
	(JNIEnv *, jobject) {
	printf("C start\n");
	graphManager = new GraphManager();
	printf("C created GraphManager\n");
	graphManager->started = true;
	while(graphManager->started) {
		graphManager->tick();
	}
	printf("C start ended\n");
}

JNIEXPORT void JNICALL Java_JStk_stop
  (JNIEnv *, jobject) {
	printf("C stop\n");
	while(graphManager->hasRunningGraphs()) {
		  usleep(100000);
	}
	usleep(100000);
	graphManager->started = false;
	printf("C stop graphManager started = false\n");
	delete graphManager;
	printf("C stop graphManager deleted\n");
}

JNIEXPORT void JNICALL Java_JStk_addGraph
    (JNIEnv* env , jobject, jint graphId, jobject jgraph) {
  try {
    printf("C addGraph %d %p\n", graphId, jgraph);
    Stk::showWarnings(true);

    Node* node = conv.createNode(env, jgraph, &factory);
    printf("C addGraph created node\n");
    Graph* graph = new Graph(graphId, node);
    printf("C addGraph created graph\n");
    graphManager->add(graphId, graph);
    printf("C addGraph added graph %d\n", graphId);

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
    Graph* graph = graphManager->remove(graphId);
    printf("C removeGraph found graph to remove %d %p\n", graphId, graph);
    graph->running = false;
    printf("C removeGraph set running to false %d\n", graphId);
    //delete graph;
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

