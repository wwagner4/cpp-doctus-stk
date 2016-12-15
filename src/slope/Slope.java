package slope;

public class Slope {

	enum State {
		BEFORE_START, STARTED, STOPPED, AFTER_STOPPED
	}

	ISlope linear(double duration, double from, double to) {
		final double delta = (to - from) * ISlope.FRAME_RATE / duration;
		return new ISlope() {

			private State state = State.BEFORE_START;
			private double val = from;

			@Override
			public void start() {
				state = State.STARTED;
			}

			@Override
			public void stop() {
				if (state == State.STARTED) {
					state = State.STOPPED;
				}
			}

			@Override
			public double nextVal() {
				if (!finished()) {
					switch (state) {
					case BEFORE_START:
						return val;
					case STARTED:
						val += delta;
						return val;
					case STOPPED:
						return val;
					case AFTER_STOPPED:
						return val;
					default:
						throw new IllegalStateException("Unknown state: " + state);
					}
				} else {
					return val;
				}
			}

			@Override
			public boolean finished() {
				if (delta < 0) {
					return val <= to;
				} else {
					return val >= to;
				}
			}

		};
	}

}
