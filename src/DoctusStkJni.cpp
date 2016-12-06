#include "DoctusStkJni.h"
#include "jni.h"

#include <cstdio>
#include <list>
#include <random>

#include "Node.hpp"
#include "SineWave.h"
#include "RtWvOut.h"

using namespace stk;
using namespace dstk;

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
    dstk::Node* n = createSine(freq, gain);
    v.push_back(n);
    gain *= 0.9;
    freq *= 1.02;
  }
  return f.nodeSum(id++, v);
}

JNIEXPORT void JNICALL Java_DoctusStkJni_addNode(JNIEnv *, jobject) {
  Stk::showWarnings(true);

  dstk::Node* node = createNode();
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
  return;
}
