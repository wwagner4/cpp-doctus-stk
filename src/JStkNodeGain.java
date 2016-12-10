public class JStkNodeGain implements JStkNode {

	private int id;
	private double gain;

	public JStkNodeGain(int id, double gain) {
		this.id = id;
		this.gain = gain;
	}

	public int getId() {
		return id;
	}

	public double getGain() {
		return this.gain;
	}

	public int getNodeClassOrdinal() {
		return NodeClass.GAIN.ordinal();
	}
}