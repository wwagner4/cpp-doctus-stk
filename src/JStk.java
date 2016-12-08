public class JStk {

  static {
    System.loadLibrary("JStk");
  }

  public native int addGraph();

  public static void main(String... args) {
    System.out.println("J addNode ->");
    int re = new JStk().addGraph();
    System.out.println("J addNode <- " + re);
  }

}
