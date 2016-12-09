public class CodeGen {

	public static void main(String[] args) {
		writeDefs("VALUE_TYPE", ValueType.values());
		System.out.println();
		writeDefs("NODE_CLASS", NodeClass.values());
	}

	static void writeDefs(String prefix, Enum<?>[] vals) {
		for (Enum<?> c : vals) {
			String name = c.name();
			int ord = c.ordinal();
			System.out.println(String.format("#define %s_%s %d", prefix, name, ord));
		}
	}

}
