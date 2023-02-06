package MagicBean;

import java.io.Closeable;
import java.io.IOException;

public class Thread implements Closeable {
	private Magic   magic;
	private Process process;
	private long    thread;

	private Thread(Magic magic, Process process, long thread) {
		this.magic   = magic;
		this.process = process;
		this.thread  = thread;
	}

	public static Thread create(Process process, long address, long lpParam) throws Exception {
		long thread;

		if ((thread = JNI.magic_bean_thread_create(process.getHandle(), address, lpParam)) == 0)
			throw new Exception("magic_bean_thread_create failed");

		return new Thread(process.getMagic(), process, thread);
	}

	public static Thread openById(Process process, int id) throws Exception {
		long thread;

		if ((thread = JNI.magic_bean_thread_open_by_id(process.getHandle(), id)) == 0)
			throw new Exception("magic_bean_thread_open_by_id failed");

		return new Thread(process.getMagic(), process, thread);
	}

	public Magic getMagic() {
		return magic;
	}

	public long getHandle() {
		return thread;
	}

	public Process getProcess() {
		return process;
	}

	@Override
	public void close() throws IOException {
		if (thread != 0) {
			JNI.magic_bean_thread_close(getHandle());
			thread = 0;
		}
	}

	public boolean isRunning() {
		return JNI.magic_bean_thread_is_running(getHandle());
	}

	public static boolean isRunning(int threadId) {
		return JNI.magic_bean_thread_is_running(threadId);
	}

	public boolean enumerate(JNI.ThreadEnumerateCallback callback) {
		return JNI.magic_bean_thread_enumerate(getHandle(), callback);
	}

	public boolean resume() {
		return JNI.magic_bean_thread_resume(getHandle());
	}

	public boolean suspend() {
		return JNI.magic_bean_thread_suspend(getHandle());
	}

	public boolean terminate(int exitCode) {
		return JNI.magic_bean_thread_terminate(getHandle(), exitCode);
	}

	public int getExitCode() throws Exception {
		JNI.ThreadExitCode exitCode = new JNI.ThreadExitCode();

		if (!JNI.magic_bean_thread_get_exit_code(getHandle(), exitCode))
			throw new Exception("magic_bean_thread_get_exit_code failed");

		return exitCode.value;
	}

	public int waitForExit() throws Exception {
		JNI.ThreadExitCode exitCode = new JNI.ThreadExitCode();

		if (!JNI.magic_bean_thread_wait_for_exit(getHandle(), exitCode))
			throw new Exception("magic_bean_thread_wait_for_exit failed");

		return exitCode.value;
	}
}
