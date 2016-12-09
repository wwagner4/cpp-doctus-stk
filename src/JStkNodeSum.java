import java.util.List;

public class JStkNodeSum implements JStkNode, JStkContainer {
  
  private int id;
  private List<JStkNode> children;
  
  public JStkNodeSum(int id, List<JStkNode> children) {
    this.id = id;
    this.children = children;
  }
  
  public int getId() {
    return id;
  } 
  
  public List<JStkNode> getChildren() {
    return this.children;
  }

  public int getNodeClassOrdinal() {
	  return NodeClass.SUM.ordinal();
  }

}