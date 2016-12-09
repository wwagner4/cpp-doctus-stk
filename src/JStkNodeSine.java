public class JStkNodeSine implements JStkNode {
  
  private int id;
  
  public JStkNodeSine(int id) {
    this.id = id;
  }
  
  public int getId() {
    return id;
  }

  public int getNodeClassOrdinal() {
	  return NodeClass.SINE.ordinal();
  }
}