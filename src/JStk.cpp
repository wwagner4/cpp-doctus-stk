#include "JStk.h"
#include "jni.h"

#include <cstdio>
#include <list>
#include <random>

#include "Node.hpp"
#include "SineWave.h"
#include "RtWvOut.h"

using namespace stk;
using namespace jstk;

NodeFactory f;

int id = 0;

Node* createSine(StkFloat frequency, StkFloat gain) {
  Node* sine = f.nodeSine(id++, frequency);

  Node* gain_ = f.nodeGain(id++, gain);

  std::list<Node*> v;

  v.push_back(sine);
  v.push_back(gain_);

  Node* seq = f.nodeSequence(id++, v);

  return seq;
}

Node* createNode() {
  std::list<Node*> v;
  StkFloat freq = rand() % 400 + 200;
  StkFloat gain = 0.1;
  for (int i = 1; i <= 100; i++) {
    jstk::Node* n = createSine(freq, gain);
    v.push_back(n);
    gain *= 0.9;
    freq *= 1.02;
  }
  return f.nodeSum(id++, v);
}

JNIEXPORT void JNICALL Java_JStk_addGraph
    (JNIEnv *, jobject, jint graphId, jobject graph) {
  try {
    printf("C addGraph %d %p\n", graphId, graph);
    Stk::showWarnings(true);

    jstk::Node* node = createNode();
    node->keyOn();
    RtWvOut *dac = 0;
    dac = new RtWvOut(2);
    for (int f = 0; f < 100000; f++) {
      stk::StkFloat v = node->tick();
      dac->tick(v);
    }
    node->keyOff();
    delete node;
    delete dac;
  } catch (...) {
    printf("ERROR: An unknown exception occurred in 'Java_JStk_addGraph\n'");
  }
}

JNIEXPORT void JNICALL Java_JStk_removeGraph
  (JNIEnv *, jobject, jint graphId) {
  printf("C removeGraph %d\n", graphId);
}

