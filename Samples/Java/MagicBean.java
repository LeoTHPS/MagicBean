public class MagicBean {
	public class ThreadExitCode {
		public int value;
	}

	public class ThreadInformation {
		public int id;
	}

	public interface ThreadEnumerateCallback {
		boolean callback(ThreadInformation information);
	}

	public class WindowInformation {
		public String name;
		public int    index;
	}

	public interface WindowEnumerateCallback {
		boolean callback(WindowInformation information);
	}

	public class ProcessInformation {
		public int    id;
		public String name;
	}

	public interface ProcessEnumerateCallback {
		boolean callback(ProcessInformation information);
	}

	public static native long    magic_bean_open();
	public static native void    magic_bean_close(long magic);

	public static native boolean magic_bean_thread_enumerate(long process, ThreadEnumerateCallback callback);
	public static native long    magic_bean_thread_create(long process, long address, long lpParam);
	public static native long    magic_bean_thread_open_by_id(long process, int id);
	public static native void    magic_bean_thread_close(long thread);
	public static native boolean magic_bean_thread_resume(long thread);
	public static native boolean magic_bean_thread_suspend(long thread);
	public static native boolean magic_bean_thread_terminate(long thread, int exitCode);
	public static native boolean magic_bean_thread_get_exit_code(long thread, ThreadExitCode exitCode);
	public static native boolean magic_bean_thread_wait_for_exit(long thread, ThreadExitCode exitCode);

	public static native boolean magic_bean_window_enumerate(long process, WindowEnumerateCallback callback);
	public static native long    magic_bean_window_open_by_name(long process, String name);
	public static native long    magic_bean_window_open_by_index(long process, int index);
	public static native void    magic_bean_window_close(long window);

	public static native boolean magic_bean_process_enumerate(long magic, ProcessEnumerateCallback callback);
	public static native long    magic_bean_process_open_by_id(long magic, int id);
	public static native long    magic_bean_process_open_by_name(long magic, String name);
	public static native void    magic_bean_process_close(long process);
	public static native boolean magic_bean_process_resume(long process);
	public static native boolean magic_bean_process_suspend(long process);
	public static native boolean magic_bean_process_set_debugger_present(long process, boolean set);
	public static native boolean magic_bean_process_memory_read(long process, long address, byte[] buffer, int offset, int size);
	public static native boolean magic_bean_process_memory_write(long process, long address, byte[] buffer, int offset, int size);
	public static native long    magic_bean_process_memory_find(long process, String mask, byte[] pattern);
	public static native long    magic_bean_process_memory_find_at(long process, String mask, byte[] pattern, long address, long size);
	public static native long    magic_bean_process_memory_allocate(long process, long size);
	public static native long    magic_bean_process_memory_allocate_at(long process, long address, long size);
	public static native boolean magic_bean_process_memory_release(long process, long address);
	public static native long    magic_bean_process_library_open(long process, String name);
	public static native void    magic_bean_process_library_close(long library);
	public static native long    magic_bean_process_library_load_file(long process, String path);
	public static native long    magic_bean_process_library_load_buffer(long process, byte[] buffer);
	public static native long    magic_bean_process_library_load_memory(long process, long address, long size);
	public static native void    magic_bean_process_library_unload(long library);
	public static native long    magic_bean_process_library_get_export(long library, String name);
}
