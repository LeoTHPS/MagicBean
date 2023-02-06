package MagicBean;

import java.io.Closeable;
import java.io.IOException;

public class ProcessMemory implements Closeable {
	private Magic   magic;
	private Process process;

	public ProcessMemory(Magic magic, Process process) {
		this.magic   = magic;
		this.process = process;
	}

	public Magic getMagic() {
		return magic;
	}

	public long getHandle() {
		return getProcess().getHandle();
	}

	public Process getProcess() {
		return process;
	}

	@Override
	public void close() throws IOException {
	}

	public void read(long address, byte[] buffer, int offset, int size) throws Exception {
		if (!JNI.magic_bean_process_memory_read(getHandle(), address, buffer, offset, size))
			throw new Exception("magic_bean_process_memory_read failed");
	}
	public byte readInt8(long address) throws Exception {
		return JNI.magic_bean_process_memory_read_int8(getHandle(), address);
	}
	public short readInt16(long address) throws Exception {
		return JNI.magic_bean_process_memory_read_int16(getHandle(), address);
	}
	public int readInt32(long address) throws Exception {
		return JNI.magic_bean_process_memory_read_int32(getHandle(), address);
	}
	public long readInt64(long address) throws Exception {
		return JNI.magic_bean_process_memory_read_int64(getHandle(), address);
	}
	public byte readUInt8(long address) throws Exception {
		return JNI.magic_bean_process_memory_read_uint8(getHandle(), address);
	}
	public short readUInt16(long address) throws Exception {
		return JNI.magic_bean_process_memory_read_uint16(getHandle(), address);
	}
	public int readUInt32(long address) throws Exception {
		return JNI.magic_bean_process_memory_read_uint32(getHandle(), address);
	}
	public long readUInt64(long address) throws Exception {
		return JNI.magic_bean_process_memory_read_uint64(getHandle(), address);
	}
	public float readFloat(long address) throws Exception {
		return JNI.magic_bean_process_memory_read_float(getHandle(), address);
	}
	public double readDouble(long address) throws Exception {
		return JNI.magic_bean_process_memory_read_double(getHandle(), address);
	}
	public String readString(long address, int maxLength) throws Exception {
		return JNI.magic_bean_process_memory_read_string(getHandle(), address, maxLength);
	}

	public void write(long address, byte[] buffer, int offset, int size) throws Exception {
		if (!JNI.magic_bean_process_memory_write(getHandle(), address, buffer, offset, size))
			throw new Exception("magic_bean_process_memory_write");
	}
	public void writeInt8(long address, byte value) throws Exception {
		if (!JNI.magic_bean_process_memory_write_int8(getHandle(), address, value))
			throw new Exception("magic_bean_process_memory_write_int8");
	}
	public void writeInt16(long address, short value) throws Exception {
		if (!JNI.magic_bean_process_memory_write_int16(getHandle(), address, value))
			throw new Exception("magic_bean_process_memory_write_int16");
	}
	public void writeInt32(long address, int value) throws Exception {
		if (!JNI.magic_bean_process_memory_write_int32(getHandle(), address, value))
			throw new Exception("magic_bean_process_memory_write_int32");
	}
	public void writeInt64(long address, long value) throws Exception {
		if (!JNI.magic_bean_process_memory_write_int64(getHandle(), address, value))
			throw new Exception("magic_bean_process_memory_write_int64");
	}
	public void writeUInt8(long address, byte value) throws Exception {
		if (!JNI.magic_bean_process_memory_write_uint8(getHandle(), address, value))
			throw new Exception("magic_bean_process_memory_write_int8");
	}
	public void writeUInt16(long address, short value) throws Exception {
		if (!JNI.magic_bean_process_memory_write_uint16(getHandle(), address, value))
			throw new Exception("magic_bean_process_memory_write_int16");
	}
	public void writeUInt32(long address, int value) throws Exception {
		if (!JNI.magic_bean_process_memory_write_uint32(getHandle(), address, value))
			throw new Exception("magic_bean_process_memory_write_int32");
	}
	public void writeUInt64(long address, long value) throws Exception {
		if (!JNI.magic_bean_process_memory_write_uint64(getHandle(), address, value))
			throw new Exception("magic_bean_process_memory_write_uint64");
	}
	public void writeFloat(long address, float value) throws Exception {
		if (!JNI.magic_bean_process_memory_write_float(getHandle(), address, value))
			throw new Exception("magic_bean_process_memory_write_float");
	}
	public void writeDouble(long address, double value) throws Exception {
		if (!JNI.magic_bean_process_memory_write_double(getHandle(), address, value))
			throw new Exception("magic_bean_process_memory_write_double");
	}
	public void writeString(long address, String value) throws Exception {
		if (!JNI.magic_bean_process_memory_write_string(getHandle(), address, value))
			throw new Exception("magic_bean_process_memory_write_string");
	}

	public long find(String mask, byte[] pattern) throws Exception {
		long address;

		if ((address = JNI.magic_bean_process_memory_find(getHandle(), mask, pattern)) == 0)
			throw new Exception("magic_bean_process_memory_find failed");

		return address;
	}
	public long findAt(String mask, byte[] pattern, long address, long size) throws Exception {
		if ((address = JNI.magic_bean_process_memory_find_at(getHandle(), mask, pattern, address, size)) == 0)
			throw new Exception("magic_bean_process_memory_find_at failed");

		return address;
	}

	public long allocate(long size, byte type) throws Exception {
		long address;

		if ((address = JNI.magic_bean_process_memory_allocate(getHandle(), size, type)) == 0)
			throw new Exception("magic_bean_process_memory_allocate failed");

		return address;
	}
	public long allocateAt(long address, long size, byte type) throws Exception {
		if ((address = JNI.magic_bean_process_memory_allocate_at(getHandle(), address, size, type)) == 0)
			throw new Exception("magic_bean_process_memory_allocate_at failed");

		return address;
	}

	public boolean release(long address) {
		return JNI.magic_bean_process_memory_release(getHandle(), address);
	}
}
