package slope;

@FunctionalInterface
public interface ISlopeFactory {
	
	ISlope slope(double duration, double from, double to);

}
