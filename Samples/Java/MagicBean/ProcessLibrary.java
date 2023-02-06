package MagicBean;

import java.io.Closeable;
import java.io.IOException;

public class ProcessLibrary implements Closeable {
	private Magic   magic;
	private Process process;
	private long    library;

	private ProcessLibrary(Magic magic, Process process, long library) {
		this.magic   = magic;
		this.process = process;
		this.library = library;
	}

	public static ProcessLibrary open(Process process, String name) throws Exception {
		long library;

		if ((library = JNI.magic_bean_process_library_open(process.getHandle(), name)) == 0)
			throw new Exception("magic_bean_process_library_open failed");

		return new ProcessLibrary(process.getMagic(), process, library);
	}

	public static ProcessLibrary loadFile(Process process, String path) throws Exception
	{
		long library;

		if ((library = JNI.magic_bean_process_library_load_file(process.getHandle(), path)) == 0)
			throw new Exception("magic_bean_process_library_load_file failed");

		return new ProcessLibrary(process.getMagic(), process, library);
	}
	public static ProcessLibrary loadBuffer(Process process, byte[] buffer) throws Exception
	{
		long library;

		if ((library = JNI.magic_bean_process_library_load_buffer(process.getHandle(), buffer)) == 0)
			throw new Exception("magic_bean_process_library_load_buffer failed");

		return new ProcessLibrary(process.getMagic(), process, library);
	}
	public static ProcessLibrary loadMemory(Process process, long address, long size) throws Exception
	{
		long library;

		if ((library = JNI.magic_bean_process_library_load_memory(process.getHandle(), address, size)) == 0)
			throw new Exception("magic_bean_process_library_load_memory failed");

		return new ProcessLibrary(process.getMagic(), process, library);
	}

	public Magic getMagic() {
		return magic;
	}

	public long getHandle() {
		return library;
	}

	public Process getProcess() {
		return process;
	}

	@Override
	public void close() throws IOException {
		if (library != 0) {
			JNI.magic_bean_process_library_close(getHandle());
			library = 0;
		}
	}

	public void unload() {
		JNI.magic_bean_process_library_unload(getHandle());
	}

	public long getExport(String name) {
		return JNI.magic_bean_process_library_get_export(getHandle(), name);
	}
}
