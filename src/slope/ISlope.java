package slope;

public interface ISlope {
	
	public final int FRAME_RATE = 200;
	
	void start();

	void stop();

	double nextVal();
	
	boolean finished();
	
}
