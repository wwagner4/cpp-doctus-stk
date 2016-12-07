public class JStk {

  static {
    System.loadLibrary("JStk");
  }

  public native void addNode();

  public static void main(String... args) {
    System.out.println("J addNode ->");
    new JStk().addNode();
    System.out.println("J addNode <-");
  }

}