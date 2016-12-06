public class DoctusStkJni {

  static {
    System.loadLibrary("DoctusStkJni");
  }

  public native void addNode();

  public static void main(String... args) {
    System.out.println("J addNode ->");
    new DoctusStkJni().addNode();
    System.out.println("J addNode <-");
  }

}