public class JStk {

  static {
    System.loadLibrary("JStk");
  }

  public native int addGraph(int graphId, JStkNode graph);

  public static void main(String... args) {
    System.out.println("J addNode ->");
    int re = new JStk().addGraph(0, createTestGraph());
    System.out.println("J addNode <- " + re);
  }

  static JStkNode createTestGraph() {
    JStkNodeSine n = new JStkNodeSine(0);
    return n;
  }

}
