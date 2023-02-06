package MagicBean;

import java.io.Closeable;
import java.io.IOException;

public class Magic implements Closeable {
	private long magic;

	private Magic(long magic) {
		this.magic = magic;
	}

	public static Magic open() throws Exception {
		long magic;

		if ((magic = JNI.magic_bean_open()) == 0)
			throw new Exception("magic_bean_open failed");

		return new Magic(magic);
	}

	public long getHandle() {
		return magic;
	}

	@Override
	public void close() throws IOException {
		JNI.magic_bean_close(magic);
	}

	public long getTimeMS() {
		return JNI.magic_bean_get_time_ms(getHandle());
	}

	public long getTimeUS() {
		return JNI.magic_bean_get_time_ms(getHandle());
	}

	public long getTimestamp() {
		return JNI.magic_bean_get_timestamp(getHandle());
	}

	public int getCurrentThreadId() {
		return JNI.magic_bean_get_current_thread_id();
	}

	public int getCurrentProcessId() {
		return JNI.magic_bean_get_current_process_id();
	}
}
