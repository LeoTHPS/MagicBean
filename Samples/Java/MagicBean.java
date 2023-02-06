public class MagicBean {
	public class ThreadExitCode {
		public int value;
	}

	public class ThreadInformation {
		public int id;

		public ThreadInformation(int id) {
			this.id = id;
		}
	}

	public interface ThreadEnumerateCallback {
		boolean callback(ThreadInformation information);
	}

	public class WindowInformation {
		public String name;
		public int    index;

		public WindowInformation(String name, int index) {
			this.name  = name;
			this.index = index;
		}
	}

	public interface WindowEnumerateCallback {
		boolean callback(WindowInformation information);
	}

	public class ProcessInformation {
		public int    id;
		public String name;

		public ProcessInformation(int id, String name) {
			this.id   = id;
			this.name = name;
		}
	}

	public interface ProcessEnumerateCallback {
		boolean callback(ProcessInformation information);
	}

	public static final byte MEMORY_PROTECTION_TYPE_NONE               = 0;
	public static final byte MEMORY_PROTECTION_TYPE_READ               = 1;
	public static final byte MEMORY_PROTECTION_TYPE_READ_WRITE         = 2;
	public static final byte MEMORY_PROTECTION_TYPE_EXECUTE            = 3;
	public static final byte MEMORY_PROTECTION_TYPE_EXECUTE_READ       = 4;
	public static final byte MEMORY_PROTECTION_TYPE_EXECUTE_READ_WRITE = 5;

	public static native long    magic_bean_open();
	public static native void    magic_bean_close(long magic);
	public static native long    magic_bean_get_time_ms(long magic);
	public static native long    magic_bean_get_time_us(long magic);
	public static native long    magic_bean_get_timestamp(long magic);
	public static native int     magic_bean_get_current_thread_id();
	public static native int     magic_bean_get_current_process_id();

	public static native boolean magic_bean_thread_is_running(long thread);
	public static native boolean magic_bean_thread_is_running_by_id(long process, int id);
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
	public static native String  magic_bean_window_get_name(long window);
	public static native boolean magic_bean_window_set_name(long window, String value);

	public static native boolean magic_bean_process_is_running(long process);
	public static native boolean magic_bean_process_is_running_by_id(long magic, int id);
	public static native boolean magic_bean_process_enumerate(long magic, ProcessEnumerateCallback callback);
	public static native long    magic_bean_process_open_by_id(long magic, int id);
	public static native long    magic_bean_process_open_by_name(long magic, String name);
	public static native void    magic_bean_process_close(long process);
	public static native boolean magic_bean_process_resume(long process);
	public static native boolean magic_bean_process_suspend(long process);
	public static native boolean magic_bean_process_is_debugger_present(long process);
	public static native boolean magic_bean_process_set_debugger_present(long process, boolean set);
	public static native boolean magic_bean_process_memory_read(long process, long address, byte[] buffer, int offset, int size);
	public static native byte    magic_bean_process_memory_read_int8(long process, long address) throws Exception;
	public static native short   magic_bean_process_memory_read_int16(long process, long address) throws Exception;
	public static native int     magic_bean_process_memory_read_int32(long process, long address) throws Exception;
	public static native long    magic_bean_process_memory_read_int64(long process, long address) throws Exception;
	public static native byte    magic_bean_process_memory_read_uint8(long process, long address) throws Exception;
	public static native short   magic_bean_process_memory_read_uint16(long process, long address) throws Exception;
	public static native int     magic_bean_process_memory_read_uint32(long process, long address) throws Exception;
	public static native long    magic_bean_process_memory_read_uint64(long process, long address) throws Exception;
	public static native float   magic_bean_process_memory_read_float(long process, long address) throws Exception;
	public static native double  magic_bean_process_memory_read_double(long process, long address) throws Exception;
	public static native String  magic_bean_process_memory_read_string(long process, long address, int maxLength) throws Exception;
	public static native boolean magic_bean_process_memory_write(long process, long address, byte[] buffer, int offset, int size);
	public static native boolean magic_bean_process_memory_write_int8(long process, long address, byte value);
	public static native boolean magic_bean_process_memory_write_int16(long process, long address, short value);
	public static native boolean magic_bean_process_memory_write_int32(long process, long address, int value);
	public static native boolean magic_bean_process_memory_write_int64(long process, long address, long value);
	public static native boolean magic_bean_process_memory_write_uint8(long process, long address, byte value);
	public static native boolean magic_bean_process_memory_write_uint16(long process, long address, short value);
	public static native boolean magic_bean_process_memory_write_uint32(long process, long address, int value);
	public static native boolean magic_bean_process_memory_write_uint64(long process, long address, long value);
	public static native boolean magic_bean_process_memory_write_float(long process, long address, float value);
	public static native boolean magic_bean_process_memory_write_double(long process, long address, double value);
	public static native boolean magic_bean_process_memory_write_string(long process, long address, String value);
	public static native long    magic_bean_process_memory_find(long process, String mask, byte[] pattern);
	public static native long    magic_bean_process_memory_find_at(long process, String mask, byte[] pattern, long address, long size);
	public static native long    magic_bean_process_memory_allocate(long process, long size, byte type);
	public static native long    magic_bean_process_memory_allocate_at(long process, long address, long size, byte type);
	public static native boolean magic_bean_process_memory_release(long process, long address);
	public static native long    magic_bean_process_library_open(long process, String name);
	public static native void    magic_bean_process_library_close(long library);
	public static native long    magic_bean_process_library_load_file(long process, String path);
	public static native long    magic_bean_process_library_load_buffer(long process, byte[] buffer);
	public static native long    magic_bean_process_library_load_memory(long process, long address, long size);
	public static native void    magic_bean_process_library_unload(long library);
	public static native long    magic_bean_process_library_get_export(long library, String name);
}
