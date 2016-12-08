import java.util.concurrent.*;

public class JStk {

  static {
    System.loadLibrary("JStk");
  }

  public native void addGraph(int graphId, JStkNode graph);
  public native void removeGraph(int graphId);

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
    System.out.println("J addGraph <- ");
    pause(1500);
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
