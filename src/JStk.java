import java.util.concurrent.*;

public class JStk {

  static {
    System.loadLibrary("JStk");
  }

  public native void addGraph(int graphId, JStkNode graph);
  public native void removeGraph(int graphId);
  public native void setValue(int graphId, int nodeId, int typeOrdinal, double value);

  /**
   * creates an object for executing the native calls
   * native calls asynchron.
   */
  public static IJStk create() {
    return new IJStk() {
      ExecutorService pool = Executors.newCachedThreadPool();
      JStk jStk = new JStk();
      public void addGraph(int graphId, JStkNode graph) {
        pool.execute(() -> jStk.addGraph(graphId, graph));
      }
      public void removeGraph(int graphId) {
        pool.execute(() -> jStk.removeGraph(graphId));
      }
      public void setValue(int graphId, int nodeId, int typeOrdinal, double value) {
          pool.execute(() -> jStk.setValue(graphId, nodeId, typeOrdinal, value));
      }
      public void shutdown() {
        pool.shutdown();
      }
    };
  }

  public static void main(String... args) {
    IJStk jStk = create();
    JStkNode g = createTestGraph();
    System.out.println("J addGraph ->");
    jStk.addGraph(0, g);
    jStk.setValue(0, 0, ValueType.FREQUENCY.ordinal(), 333);
    System.out.println("J addGraph <- ");
    pause(500);
    System.out.println("J removeGraph -> ");
    jStk.removeGraph(0);
    System.out.println("J removeGraph <- ");
    jStk.shutdown();
  }

  static JStkNode createTestGraph() {
    JStkNodeSine n = new JStkNodeSine(0);
    return n;
  }

  static void pause(int ms) {
    try {
      Thread.sleep(ms);
    } catch (InterruptedException ex) {
      // Nothing to do here
    }
  }

}
