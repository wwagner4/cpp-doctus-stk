package slope;

import java.util.Optional;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.ScheduledFuture;
import java.util.concurrent.TimeUnit;

public class SlopeTryout {

	public static void main(String[] args) {
		ScheduledExecutorService es  = Executors.newScheduledThreadPool(20);
		
		TParam p = new TParam();
		ParamExec e = new ParamExec(p);
		
		ISlope s = new Slope().linear(0.1, 0, 100);
		e.runSlope(s, es);
		pause(50);
		s.start();
		pause(150);
		
		es.shutdown();
		
	}

	private static void pause(int milis) {
		try {
			Thread.sleep(milis);
		} catch (InterruptedException e) {
			// Nothing to do here
		}
	}

	static void linearSlopeValues() {
		{
			System.out.printf("-- Ascending slope in 20 steps\n");
			Slope s = new Slope();
			ISlope ls = s.linear(0.1, 10, 20);
			System.out.printf("BS %5.2f\n", ls.nextVal());
			System.out.printf("BS %5.2f\n", ls.nextVal());
			System.out.printf("BS %5.2f\n", ls.nextVal());
			System.out.printf("BS %5.2f\n", ls.nextVal());
			ls.start();
			System.out.printf("-- started\n");
			for (int i = 0; i < 18; i++) {
				ls.nextVal();
			}
			System.out.printf("S #19 %5.2f\n", ls.nextVal());
			System.out.printf("S #20 %5.2f\n", ls.nextVal());
			System.out.printf("S #21 %5.2f\n", ls.nextVal());
			System.out.printf("S #22 %5.2f\n", ls.nextVal());
		}
		{
			System.out.printf("-- Descending slope in 20 steps\n");
			Slope s = new Slope();
			ISlope ls = s.linear(0.1, 200, 0);
			System.out.printf("BS %5.2f\n", ls.nextVal());
			System.out.printf("BS %5.2f\n", ls.nextVal());
			System.out.printf("BS %5.2f\n", ls.nextVal());
			System.out.printf("BS %5.2f\n", ls.nextVal());
			ls.start();
			System.out.printf("-- started\n");
			for (int i = 0; i < 16; i++) {
				ls.nextVal();
			}
			System.out.printf("S #17 %5.2f\n", ls.nextVal());
			System.out.printf("S #18 %5.2f\n", ls.nextVal());
			System.out.printf("S #19 %5.2f\n", ls.nextVal());
			System.out.printf("S #20 %5.2f\n", ls.nextVal());
			System.out.printf("S #21 %5.2f\n", ls.nextVal());
			System.out.printf("S #22 %5.2f\n", ls.nextVal());
		}
		{
			System.out.printf("-- Ascending slope in less than one step\n");
			double fl = 1.0 / ISlope.FRAME_RATE;
			System.out.printf("-- FrameLength %5.2f seconds\n", fl);

			Slope s = new Slope();
			ISlope ls = s.linear(fl * 0.9, 10, 20);
			System.out.printf("BS %5.2f\n", ls.nextVal());
			System.out.printf("BS %5.2f\n", ls.nextVal());
			System.out.printf("BS %5.2f\n", ls.nextVal());
			System.out.printf("BS %5.2f\n", ls.nextVal());
			ls.start();
			System.out.printf("-- started\n");
			System.out.printf("S #1 %5.2f\n", ls.nextVal());
			System.out.printf("S #2 %5.2f\n", ls.nextVal());
			System.out.printf("S #3 %5.2f\n", ls.nextVal());
			System.out.printf("S #4 %5.2f\n", ls.nextVal());
		}
		{
			System.out.printf("-- Descending slope in less than one step\n");
			double fl = 1.0 / ISlope.FRAME_RATE;
			System.out.printf("-- FrameLength %5.2f seconds\n", fl);

			Slope s = new Slope();
			ISlope ls = s.linear(fl * 0.1, 100, -20);
			System.out.printf("BS %5.2f\n", ls.nextVal());
			System.out.printf("BS %5.2f\n", ls.nextVal());
			System.out.printf("BS %5.2f\n", ls.nextVal());
			System.out.printf("BS %5.2f\n", ls.nextVal());
			ls.start();
			System.out.printf("-- started\n");
			System.out.printf("S #1 %5.2f\n", ls.nextVal());
			System.out.printf("S #2 %5.2f\n", ls.nextVal());
			System.out.printf("S #3 %5.2f\n", ls.nextVal());
			System.out.printf("S #4 %5.2f\n", ls.nextVal());
		}
	}

}

class ParamExec {

	long periode = Double.valueOf(1000000.0 / ISlope.FRAME_RATE).longValue();

	private Param param;

	Optional<ScheduledFuture<?>> process = Optional.empty();

	public ParamExec(Param param) {
		this.param = param;
	}

	public void runSlope(ISlope slope, ScheduledExecutorService es) {

		Runnable run = new Runnable() {

			@Override
			public void run() {
				param.setValue(slope.nextVal());
			}

		};
		process = Optional.of(es.scheduleAtFixedRate(run, 0, periode, TimeUnit.MICROSECONDS));
	}

}

interface Param {

	void setValue(double v);

	double getValue();
}

class TParam implements Param {

	double v = 0.0;

	@Override
	public void setValue(double v) {
		System.out.printf("-> TParam setValue %.3f\n", v);
		this.v = v;
	}

	@Override
	public double getValue() {
		System.out.printf("<- TParam getValue %.3f\n", v);
		return v;
	}

}
