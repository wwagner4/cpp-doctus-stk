public class JStkNodeGain implements JStkNode {
  
  private int id;
  
  public JStkNodeGain(int id) {
    this.id = id;
  }
  
  public int getId() {
    return id;
  }

  public int getNodeClassOrdinal() {
	  return NodeClass.GAIN.ordinal();
  }
}