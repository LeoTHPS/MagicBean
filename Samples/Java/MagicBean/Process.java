package MagicBean;

import java.io.Closeable;
import java.io.IOException;

public class Process implements Closeable {
	private Magic         magic;
	private long          process;
	private ProcessMemory processMemory;

	private Process(Magic magic, long process) {
		this.magic         = magic;
		this.process       = process;
		this.processMemory = new ProcessMemory(magic, this);
	}

	public static Process openById(Magic magic, int id) throws Exception {
		long process;

		if ((process = JNI.magic_bean_process_open_by_id(magic.getHandle(), id)) == 0)
			throw new Exception("magic_bean_process_open_by_id failed");

		return new Process(magic, process);
	}
	public static Process openByName(Magic magic, String name) throws Exception {
		long process;

		if ((process = JNI.magic_bean_process_open_by_name(magic.getHandle(), name)) == 0)
			throw new Exception("magic_bean_process_open_by_name failed");

		return new Process(magic, process);
	}

	public Magic getMagic() {
		return magic;
	}

	public long getHandle() {
		return process;
	}

	public ProcessMemory getMemory() {
		return processMemory;
	}

	@Override
	public void close() throws IOException {
		if (process != 0) {
			JNI.magic_bean_process_close(getHandle());
			process = 0;
			processMemory = null;
		}
	}

	public boolean isRunning() throws IOException {
		return JNI.magic_bean_process_is_running(getHandle());
	}
	public static boolean isRunning(Magic magic, int processId) throws IOException {
		return JNI.magic_bean_process_is_running_by_id(magic.getHandle(), processId);
	}

	public long getFileVersion() throws Exception {
		JNI.ProcessFileVersion fileVersion = new JNI.ProcessFileVersion();

		if (!JNI.magic_bean_process_get_file_version(getHandle(), fileVersion))
			throw new Exception("magic_bean_process_get_file_version failed");

		return fileVersion.value;
	}
	public static long getFileVersion(Magic magic, int processId) throws Exception {
		JNI.ProcessFileVersion fileVersion = new JNI.ProcessFileVersion();

		if (!JNI.magic_bean_process_get_file_version_by_id(magic.getHandle(), processId, fileVersion))
			throw new Exception("magic_bean_process_get_file_version_by_id failed");

		return fileVersion.value;
	}

	public static boolean enumerate(Magic magic, JNI.ProcessEnumerateCallback callback) {
		return JNI.magic_bean_process_enumerate(magic.getHandle(), callback);
	}

	public boolean resume() {
		return JNI.magic_bean_process_resume(getHandle());
	}

	public boolean suspend() {
		return JNI.magic_bean_process_suspend(getHandle());
	}

	public boolean isDebuggerPresent() {
		return JNI.magic_bean_process_is_debugger_present(getHandle());
	}

	public boolean setDebuggerPresent(boolean set) {
		return JNI.magic_bean_process_set_debugger_present(getHandle(), set);
	}
}
