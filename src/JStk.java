import java.util.*;
import java.util.concurrent.*;

public class JStk {

	static ExecutorService pool = Executors.newCachedThreadPool();
	static Random ran = new Random();
	
	static {
		System.loadLibrary("JStk");
	}

	public native void start();

	public native void stop();

	public native void addGraph(int graphId, JStkNode graph);

	public native void removeGraph(int graphId);

	public native void setValue(int graphId, int nodeId, int typeOrdinal, double value);

	/**
	 * creates an object for executing the native calls native calls asynchron.
	 */
	public static IJStk create() {
		return new IJStk() {
			JStk jStk = new JStk();

			@Override
			public void start() {
				pool.execute(() -> jStk.start());
				pause(100); // Pause until the graph manager is instantiated
			}

			@Override
			public void stop() {
				pool.execute(() -> {
					jStk.stop();
					pool.shutdown();
				});
			}

			@Override
			public void addGraph(int graphId, JStkNode graph) {
				pool.execute(() -> jStk.addGraph(graphId, graph));
			}

			@Override
			public void removeGraph(int graphId) {
				pool.execute(() -> jStk.removeGraph(graphId));
			}

			@Override
			public void setValue(int graphId, int nodeId, int valueTypeOrdinal, double value) {
				pool.execute(() -> jStk.setValue(graphId, nodeId, valueTypeOrdinal, value));
			}


		};
	}

	public static void main(String... args) {
		IJStk jStk = create();
		System.out.println("J start -> ");
		jStk.start();
		System.out.println("J start <- ");
		for (int i=1; i<=50; i++) {
			final int j = i;
			pool.execute(() -> playNote(jStk, j, 100 + j * 7.0));
			pause(100);
		}
		System.out.println("J stop -> ");
		jStk.stop();
		System.out.println("J stop <- ");
	}

	static void playNote(IJStk jStk, int id, double freq) {
		JStkNode g = createTestGraph(freq);
		System.out.println("J addGraph ->");
		jStk.addGraph(id, g);
		System.out.println("J addGraph <- ");
		int dur = 20 + ran.nextInt(5000);
		pause(dur);
		System.out.println("J removeGraph -> ");
		jStk.removeGraph(id);
		System.out.println("J removeGraph <- ");
	}
	
	
	static JStkNode createTestGraph(double freq) {
		JStkNodeSine nsine = new JStkNodeSine(101, freq);
		JStkNodeGain ngain = new JStkNodeGain(102, 0.05);
		List<JStkNode> li = Arrays.asList(nsine, ngain);
		JStkNodeSequence nseq = new JStkNodeSequence(103, li);
		return nseq;
	}

	static void pause(int ms) {
		try {
			Thread.sleep(ms);
		} catch (InterruptedException ex) {
			// Nothing to do here
		}
	}

}
