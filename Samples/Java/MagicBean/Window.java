package MagicBean;

import java.io.Closeable;
import java.io.IOException;

public class Window implements Closeable {
	private Magic   magic;
	private Process process;
	private long    window;

	private Window(Magic magic, Process process, long window) {
		this.magic   = magic;
		this.process = process;
		this.window  = window;
	}

	public static Window openByName(Process process, String name) throws Exception
	{
		long window;

		if ((window = JNI.magic_bean_window_open_by_name(process.getHandle(), name)) == 0)
			throw new Exception("magic_bean_window_open_by_name failed");

		return new Window(process.getMagic(), process, window);
	}
	public static Window openByIndex(Process process, int index) throws Exception
	{
		long window;

		if ((window = JNI.magic_bean_window_open_by_index(process.getHandle(), index)) == 0)
			throw new Exception("magic_bean_window_open_by_index failed");

		return new Window(process.getMagic(), process, window);
	}

	public Magic getMagic() {
		return magic;
	}

	public long getHandle() {
		return window;
	}

	public Process getProcess() {
		return process;
	}

	@Override
	public void close() throws IOException {
		if (window != 0) {
			JNI.magic_bean_window_close(getHandle());
			window = 0;
		}
	}

	public boolean enumerate(JNI.WindowEnumerateCallback callback) {
		return JNI.magic_bean_window_enumerate(getHandle(), callback);
	}

	public String getName() {
		return JNI.magic_bean_window_get_name(getHandle());
	}

	public boolean setName(String value) {
		return JNI.magic_bean_window_set_name(getHandle(), value);
	}
}
