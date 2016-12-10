public class JStkNodeSine implements JStkNode {

	private int id;
	private double frequency;

	public JStkNodeSine(int id, double frequency) {
		this.id = id;
		this.frequency = frequency;
	}

	public int getId() {
		return id;
	}

	public double getFrequency() {
		return frequency;
	}

	public int getNodeClassOrdinal() {
		return NodeClass.SINE.ordinal();
	}
}