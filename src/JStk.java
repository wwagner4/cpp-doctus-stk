public class JStk {

  static {
    System.loadLibrary("JStk");
  }

  public native void addGraph(int graphId, JStkNode graph);
  public native void removeGraph(int graphId);

  public static void main(String... args) {
    JStk jStk = new JStk();
    JStkNode g = createTestGraph();
    System.out.println("J addGraph ->");
    jStk.addGraph(0, g);
    System.out.println("J addGraph <- ");
    pause(1500);
    System.out.println("J removeGraph -> ");
    jStk.removeGraph(0);
    System.out.println("J removeGraph <- ");
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
