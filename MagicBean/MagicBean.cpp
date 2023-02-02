#include "MagicBean.h"

#include <AL/Common.hpp>

#include <AL/OS/Thread.hpp>
#include <AL/OS/System.hpp>
#include <AL/OS/Process.hpp>

#include <AL/Collections/Array.hpp>
#include <AL/Collections/LinkedList.hpp>

struct _MagicBean
{
	AL::Collections::LinkedList<MagicBeanProcess*> Processes;
};

struct _MagicBeanThread
{
	uint32_t          ID;
#if defined(AL_PLATFORM_LINUX)

#elif defined(AL_PLATFORM_WINDOWS)
	HANDLE            hThread;
#endif
	MagicBeanProcess* lpProcess;
};

struct _MagicBeanLibrary
{
	AL::OS::ProcessLibrary Base;
	MagicBeanProcess*      lpProcess;
};

struct _MagicBeanWindow
{
#if defined(AL_PLATFORM_LINUX)

#elif defined(AL_PLATFORM_WINDOWS)
	HWND              hWND;
#endif
	MagicBeanProcess* lpProcess;
};

struct _MagicBeanProcess
{
	AL::OS::Process                                Base;
	AL::OS::ProcessMemory                          Memory;
	MagicBean*                                     lpMagic;
	AL::Collections::LinkedList<MagicBeanThread*>  Threads;
	AL::Collections::LinkedList<MagicBeanWindow*>  Windows;
	AL::Collections::LinkedList<MagicBeanLibrary*> Libraries;
};

MagicBean*        magic_bean_open()
{
	auto magic = new MagicBean
	{
	};

	return magic;
}
void              magic_bean_close(MagicBean* magic)
{
	if (magic != nullptr)
	{
		for (auto it = magic->Processes.begin(); it != magic->Processes.end(); )
			magic_bean_process_close(*(it++));

		delete magic;
	}
}

bool              magic_bean_thread_enumerate(MagicBeanProcess* process, magic_bean_thread_enumerate_callback callback, void* lpParam)
{
	if (process == nullptr)
	{

		return false;
	}

#if defined(AL_PLATFORM_LINUX)
	// TODO: implement
	return false;
#elif defined(AL_PLATFORM_WINDOWS)
	HANDLE hSnapshot;
	
	if ((hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, static_cast<DWORD>(process->Base.GetId()))) == INVALID_HANDLE_VALUE)
	{

		return false;
	}

	THREADENTRY32 entry;
	entry.dwSize = sizeof(THREADENTRY32);

	if (Thread32First(hSnapshot, &entry))
	{
		MagicBeanThreadInformation information;

		do
		{
			information.ID = entry.th32ThreadID;

			if (!callback(&information, lpParam))
			{

				break;
			}
		} while (Thread32Next(hSnapshot, &entry));
	}

	CloseHandle(hSnapshot);
#endif

	return true;
}
MagicBeanThread*  magic_bean_thread_create(MagicBeanProcess* process, uint64_t address, uint64_t lpParam)
{
	if (process == nullptr)
	{

		return nullptr;
	}

	auto thread = new MagicBeanThread
	{
		.lpProcess = process
	};

#if defined(AL_PLATFORM_LINUX)
	delete thread; // TODO: implement
	return nullptr;
#elif defined(AL_PLATFORM_WINDOWS)
	DWORD threadID;

	if ((thread->hThread = CreateRemoteThread(process->Base.GetHandle(), nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(address), reinterpret_cast<LPVOID>(lpParam), 0, &threadID)) == NULL)
	{
		delete thread;

		return nullptr;
	}

	thread->ID = threadID;
#endif

	process->Threads.PushBack(
		thread
	);

	return thread;
}
MagicBeanThread*  magic_bean_thread_open_by_id(MagicBeanProcess* process, uint32_t id)
{
	if (process == nullptr)
	{

		return nullptr;
	}

	auto thread = new MagicBeanThread
	{
		.ID        = id,
		.lpProcess = process
	};

#if defined(AL_PLATFORM_LINUX)
	delete thread; // TODO: implement
	return nullptr;
#elif defined(AL_PLATFORM_WINDOWS)
	if ((thread->hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, static_cast<DWORD>(id))) == NULL)
	{
		delete thread;

		return nullptr;
	}
#endif

	process->Threads.PushBack(
		thread
	);

	return thread;
}
void              magic_bean_thread_close(MagicBeanThread* thread)
{
	if (thread != nullptr)
	{
		thread->lpProcess->Threads.Remove(
			thread
		);

#if defined(AL_PLATFORM_LINUX)
		// TODO: implement
#elif defined(AL_PLATFORM_WINDOWS)
		CloseHandle(thread->hThread);
#endif

		delete thread;
	}
}
bool              magic_bean_thread_resume(MagicBeanThread* thread)
{
	if (thread == nullptr)
	{

		return false;
	}

#if defined(AL_PLATFORM_LINUX)
	// TODO: implement
	return false;
#elif defined(AL_PLATFORM_WINDOWS)
	if (ResumeThread(thread->hThread) == DWORD(-1))
	{

		return false;
	}
#endif

	return true;
}
bool              magic_bean_thread_suspend(MagicBeanThread* thread)
{
	if (thread == nullptr)
	{

		return false;
	}

#if defined(AL_PLATFORM_LINUX)
	// TODO: implement
	return false;
#elif defined(AL_PLATFORM_WINDOWS)
	if (SuspendThread(thread->hThread) == DWORD(-1))
	{

		return false;
	}
#endif

	return true;
}
bool              magic_bean_thread_terminate(MagicBeanThread* thread, uint32_t exitCode)
{
	if (thread == nullptr)
	{

		return false;
	}

#if defined(AL_PLATFORM_LINUX)
	// TODO: implement
	return false;
#elif defined(AL_PLATFORM_WINDOWS)
	if (TerminateThread(thread->hThread, static_cast<DWORD>(exitCode)) == 0)
	{

		return false;
	}
#endif

	return true;
}
bool              magic_bean_thread_get_exit_code(MagicBeanThread* thread, uint32_t* lpValue)
{
	if (thread == nullptr)
	{

		return false;
	}

#if defined(AL_PLATFORM_LINUX)
	// TODO: implement
	return false;
#elif defined(AL_PLATFORM_WINDOWS)
	DWORD exitCode;

	if (!GetExitCodeThread(thread->hThread, &exitCode))
	{

		return false;
	}

	*lpValue = exitCode;
#endif

	return true;
}
bool              magic_bean_thread_wait_for_exit(MagicBeanThread* thread, uint32_t* lpExitCode)
{
	if (thread == nullptr)
	{

		return false;
	}

#if defined(AL_PLATFORM_LINUX)
	// TODO: implement
	return false;
#elif defined(AL_PLATFORM_WINDOWS)
	if (WaitForSingleObject(thread->hThread, INFINITE) != WAIT_OBJECT_0)
	{

		return false;
	}
#endif

	if ((lpExitCode != nullptr) && !magic_bean_thread_get_exit_code(thread, lpExitCode))
	{

		return false;
	}

	return true;
}

bool              magic_bean_window_enumerate(MagicBeanProcess* process, magic_bean_window_enumerate_callback callback, void* lpParam);
MagicBeanWindow*  magic_bean_window_open_by_name(MagicBeanProcess* process, const char* name);
MagicBeanWindow*  magic_bean_window_open_by_index(MagicBeanProcess* process, size_t index);
void              magic_bean_window_close(MagicBeanWindow* window)
{
	if (window != nullptr)
	{
		window->lpProcess->Windows.Remove(
			window
		);

		delete window;
	}
}
const char*       magic_bean_window_get_name(MagicBeanWindow* window)
{
	if (window == nullptr)
	{

		return nullptr;
	}

	static AL::String lastWindowTitle;

#if defined(SAL_PLATFORM_LINUX)
	// TODO: implement
	return nullptr;
#elif defined(AL_PLATFORM_WINDOWS)
	int windowTitleLength;

	if ((windowTitleLength = GetWindowTextLengthA(window->hWND)) == 0)
	{
		if (GetLastError() != ERROR_SUCCESS)
		{

			return nullptr;
		}
	}

	AL::Collections::Array<AL::String::Char> windowTitleBuffer(
		static_cast<size_t>(windowTitleLength)
	);

	if ((windowTitleLength = GetWindowTextA(window->hWND, &windowTitleBuffer[0], windowTitleLength)) == 0)
	{
		if (GetLastError() != ERROR_SUCCESS)
		{

			return nullptr;
		}
	}

	lastWindowTitle.Assign(
		&windowTitleBuffer[0],
		static_cast<size_t>(windowTitleLength)
	);
#endif

	return lastWindowTitle.GetCString();
}
bool              magic_bean_window_set_name(MagicBeanWindow* window, const char* value)
{
	if (window == nullptr)
	{

		return false;
	}

#if defined(SAL_PLATFORM_LINUX)
	// TODO: implement
	return false;
#elif defined(AL_PLATFORM_WINDOWS)
	if (!SetWindowTextA(window->hWND, value))
	{

		return false;
	}
#endif

	return true;
}

bool              magic_bean_process_enumerate(MagicBean* magic, magic_bean_process_enumerate_callback callback, void* lpParam);
MagicBeanProcess* magic_bean_process_open_by_id(MagicBean* magic, uint32_t id)
{
	if (magic == nullptr)
	{

		return nullptr;
	}

	auto process = new MagicBeanProcess
	{
		.lpMagic = magic
	};

	try
	{
		if (!AL::OS::Process::Open(process->Base, static_cast<AL::OS::ProcessId>(id)))
		{
			delete process;

			return nullptr;
		}
	}
	catch (const AL::Exception& exception)
	{
		delete process;

		return nullptr;
	}

	magic->Processes.PushBack(
		process
	);

	return process;
}
MagicBeanProcess* magic_bean_process_open_by_name(MagicBean* magic, const char* name)
{
	if (magic == nullptr)
	{

		return nullptr;
	}

	auto process = new MagicBeanProcess
	{
		.lpMagic = magic
	};

	try
	{
		if (!AL::OS::Process::Open(process->Base, name))
		{
			delete process;

			return nullptr;
		}
	}
	catch (const AL::Exception& exception)
	{
		delete process;

		return nullptr;
	}

	magic->Processes.PushBack(
		process
	);

	return process;
}
void              magic_bean_process_close(MagicBeanProcess* process)
{
	if (process != nullptr)
	{
		for (auto it = process->Threads.begin(); it != process->Threads.end(); )
			magic_bean_thread_close(*(it++));

		for (auto it = process->Windows.begin(); it != process->Windows.end(); )
			magic_bean_window_close(*(it++));

		for (auto it = process->Libraries.begin(); it != process->Libraries.end(); )
			magic_bean_process_library_close(*(it++));

		process->Memory.Close();

		process->lpMagic->Processes.Remove(
			process
		);

		delete process;
	}
}
bool              magic_bean_process_resume(MagicBeanProcess* process)
{
	magic_bean_thread_enumerate_callback callback = [](const MagicBeanThreadInformation* _lpInformation, void* _lpParam)
	{
		auto process = reinterpret_cast<MagicBeanProcess*>(
			_lpParam
		);

		if (auto thread = magic_bean_thread_open_by_id(process, _lpInformation->ID))
		{
			magic_bean_thread_resume(thread);
			magic_bean_thread_close(thread);
		}

		return true;
	};

	return magic_bean_thread_enumerate(process, callback, process);
}
bool              magic_bean_process_suspend(MagicBeanProcess* process)
{
	magic_bean_thread_enumerate_callback callback = [](const MagicBeanThreadInformation* _lpInformation, void* _lpParam)
	{
		auto process = reinterpret_cast<MagicBeanProcess*>(
			_lpParam
		);

		if (auto thread = magic_bean_thread_open_by_id(process, _lpInformation->ID))
		{
			magic_bean_thread_suspend(thread);
			magic_bean_thread_close(thread);
		}

		return true;
	};

	return magic_bean_thread_enumerate(process, callback, process);
}
bool              magic_bean_process_set_debugger_present(MagicBeanProcess* process, bool set)
{
	if (process == nullptr)
	{

		return false;
	}

	if (process->Base.IsCurrentProcess())
	{
#if defined(AL_PLATFORM_LINUX)
		// TODO: implement
		return false;
#elif defined(AL_PLATFORM_WINDOWS)
		AL::OS::SetDebuggerPresent(
			set
		);

		return true;
#endif
	}

#if defined(AL_X86)
	// TODO: implement
#elif defined(AL_X86_64)
	// TODO: implement
#endif

	return false;
}
bool              magic_bean_process_memory_read(MagicBeanProcess* process, uint64_t address, void* lpBuffer, uint64_t size)
{
	if (process == nullptr)
	{

		return false;
	}

	try
	{
		for (uint64_t totalBytesRead = 0, numberOfBytesRead, numberOfBytesRemaining = size; totalBytesRead < size; )
		{
			process->Memory.Read(
				static_cast<AL::OS::ProcessMemoryAddress>(address + totalBytesRead),
				&reinterpret_cast<uint8_t*>(lpBuffer)[totalBytesRead],
				static_cast<size_t>(numberOfBytesRead = ((numberOfBytesRemaining <= AL::Integer<size_t>::Maximum) ? numberOfBytesRemaining : AL::Integer<size_t>::Maximum))
			);

			totalBytesRead         += numberOfBytesRead;
			numberOfBytesRemaining -= numberOfBytesRead;
		}
	}
	catch (const AL::Exception& exception)
	{

		return false;
	}

	return true;
}
bool              magic_bean_process_memory_read_int8(MagicBeanProcess* process, uint64_t address, int8_t* lpValue)
{
	return magic_bean_process_memory_read(process, address, lpValue, sizeof(int8_t));
}
bool              magic_bean_process_memory_read_int16(MagicBeanProcess* process, uint64_t address, int16_t* lpValue)
{
	return magic_bean_process_memory_read(process, address, lpValue, sizeof(int16_t));
}
bool              magic_bean_process_memory_read_int32(MagicBeanProcess* process, uint64_t address, int32_t* lpValue)
{
	return magic_bean_process_memory_read(process, address, lpValue, sizeof(int32_t));
}
bool              magic_bean_process_memory_read_int64(MagicBeanProcess* process, uint64_t address, int64_t* lpValue)
{
	return magic_bean_process_memory_read(process, address, lpValue, sizeof(int64_t));
}
bool              magic_bean_process_memory_read_uint8(MagicBeanProcess* process, uint64_t address, uint8_t* lpValue)
{
	return magic_bean_process_memory_read(process, address, lpValue, sizeof(uint8_t));
}
bool              magic_bean_process_memory_read_uint16(MagicBeanProcess* process, uint64_t address, uint16_t* lpValue)
{
	return magic_bean_process_memory_read(process, address, lpValue, sizeof(uint16_t));
}
bool              magic_bean_process_memory_read_uint32(MagicBeanProcess* process, uint64_t address, uint32_t* lpValue)
{
	return magic_bean_process_memory_read(process, address, lpValue, sizeof(uint32_t));
}
bool              magic_bean_process_memory_read_uint64(MagicBeanProcess* process, uint64_t address, uint64_t* lpValue)
{
	return magic_bean_process_memory_read(process, address, lpValue, sizeof(uint64_t));
}
bool              magic_bean_process_memory_read_float(MagicBeanProcess* process, uint64_t address, float* lpValue)
{
	return magic_bean_process_memory_read(process, address, lpValue, sizeof(float));
}
bool              magic_bean_process_memory_read_double(MagicBeanProcess* process, uint64_t address, double* lpValue)
{
	return magic_bean_process_memory_read(process, address, lpValue, sizeof(double));
}
ssize_t           magic_bean_process_memory_read_string(MagicBeanProcess* process, uint64_t address, char* lpValue, size_t maxLength)
{
	if (process == nullptr)
	{

		return -1;
	}

	ssize_t length = 0;

	for (size_t i = 0; i < maxLength; ++i, ++lpValue, ++length)
	{
		if (!magic_bean_process_memory_read_uint8(process, address + i, reinterpret_cast<uint8_t*>(lpValue)))
		{

			return -1;
		}

		if (*lpValue == '\0')
		{

			break;
		}
	}

	return length;
}
bool              magic_bean_process_memory_write(MagicBeanProcess* process, uint64_t address, const void* lpBuffer, uint64_t size)
{
	if (process == nullptr)
	{

		return false;
	}

	try
	{
		for (uint64_t totalBytesWritten = 0, numberOfBytesWritten, numberOfBytesRemaining = size; totalBytesWritten < size; )
		{
			process->Memory.Write(
				static_cast<AL::OS::ProcessMemoryAddress>(address + totalBytesWritten),
				&reinterpret_cast<const uint8_t*>(lpBuffer)[totalBytesWritten],
				static_cast<size_t>(numberOfBytesWritten = ((numberOfBytesRemaining <= AL::Integer<size_t>::Maximum) ? numberOfBytesRemaining : AL::Integer<size_t>::Maximum))
			);

			totalBytesWritten      += numberOfBytesWritten;
			numberOfBytesRemaining -= numberOfBytesWritten;
		}
	}
	catch (const AL::Exception& exception)
	{

		return false;
	}

	return true;
}
bool              magic_bean_process_memory_write_int8(MagicBeanProcess* process, uint64_t address, int8_t value)
{
	return magic_bean_process_memory_write(process, address, &value, sizeof(int8_t));
}
bool              magic_bean_process_memory_write_int16(MagicBeanProcess* process, uint64_t address, int16_t value)
{
	return magic_bean_process_memory_write(process, address, &value, sizeof(int16_t));
}
bool              magic_bean_process_memory_write_int32(MagicBeanProcess* process, uint64_t address, int32_t value)
{
	return magic_bean_process_memory_write(process, address, &value, sizeof(int32_t));
}
bool              magic_bean_process_memory_write_int64(MagicBeanProcess* process, uint64_t address, int64_t value)
{
	return magic_bean_process_memory_write(process, address, &value, sizeof(int64_t));
}
bool              magic_bean_process_memory_write_uint8(MagicBeanProcess* process, uint64_t address, uint8_t value)
{
	return magic_bean_process_memory_write(process, address, &value, sizeof(uint8_t));
}
bool              magic_bean_process_memory_write_uint16(MagicBeanProcess* process, uint64_t address, uint16_t value)
{
	return magic_bean_process_memory_write(process, address, &value, sizeof(uint16_t));
}
bool              magic_bean_process_memory_write_uint32(MagicBeanProcess* process, uint64_t address, uint32_t value)
{
	return magic_bean_process_memory_write(process, address, &value, sizeof(uint32_t));
}
bool              magic_bean_process_memory_write_uint64(MagicBeanProcess* process, uint64_t address, uint64_t value)
{
	return magic_bean_process_memory_write(process, address, &value, sizeof(uint64_t));
}
bool              magic_bean_process_memory_write_float(MagicBeanProcess* process, uint64_t address, float value)
{
	return magic_bean_process_memory_write(process, address, &value, sizeof(float));
}
bool              magic_bean_process_memory_write_double(MagicBeanProcess* process, uint64_t address, double value)
{
	return magic_bean_process_memory_write(process, address, &value, sizeof(double));
}
bool              magic_bean_process_memory_write_string(MagicBeanProcess* process, uint64_t address, const char* value)
{
	return magic_bean_process_memory_write(process, address, value, AL::String::GetLength(value) + 1);
}
uint64_t          magic_bean_process_memory_find(MagicBeanProcess* process, const char* mask, const uint8_t* pattern);
uint64_t          magic_bean_process_memory_find_at(MagicBeanProcess* process, const char* mask, const uint8_t* pattern, uint64_t address, uint64_t size);
uint64_t          magic_bean_process_memory_allocate(MagicBeanProcess* process, uint64_t size, MAGIC_BEAN_PROCESS_MEMORY_PROTECTION_TYPES type)
{
	return magic_bean_process_memory_allocate_at(process, 0, size, type);
}
uint64_t          magic_bean_process_memory_allocate_at(MagicBeanProcess* process, uint64_t address, uint64_t size, MAGIC_BEAN_PROCESS_MEMORY_PROTECTION_TYPES type)
{
	if (process == nullptr)
	{

		return 0;
	}

	try
	{
		return process->Memory.Allocate(
			static_cast<AL::OS::ProcessMemoryAddress>(address),
			static_cast<AL::size_t>(size),
			[type]() -> AL::OS::ProcessMemoryProtectionTypes
			{
				switch (type)
				{
					case MAGIC_BEAN_PROCESS_MEMORY_PROTECTION_TYPE_NONE:               return AL::OS::ProcessMemoryProtectionTypes::None;
					case MAGIC_BEAN_PROCESS_MEMORY_PROTECTION_TYPE_READ:               return AL::OS::ProcessMemoryProtectionTypes::Read;
					case MAGIC_BEAN_PROCESS_MEMORY_PROTECTION_TYPE_READ_WRITE:         return AL::OS::ProcessMemoryProtectionTypes::ReadWrite;
					case MAGIC_BEAN_PROCESS_MEMORY_PROTECTION_TYPE_EXECUTE:            return AL::OS::ProcessMemoryProtectionTypes::Execute;
					case MAGIC_BEAN_PROCESS_MEMORY_PROTECTION_TYPE_EXECUTE_READ:       return AL::OS::ProcessMemoryProtectionTypes::ExecuteRead;
					case MAGIC_BEAN_PROCESS_MEMORY_PROTECTION_TYPE_EXECUTE_READ_WRITE: return AL::OS::ProcessMemoryProtectionTypes::ExecuteReadWrite;
				}

				return AL::OS::ProcessMemoryProtectionTypes::None;
			}()
		);
	}
	catch (const AL::Exception& exception)
	{

		return 0;
	}
}
bool              magic_bean_process_memory_release(MagicBeanProcess* process, uint64_t address);
MagicBeanLibrary* magic_bean_process_library_open(MagicBeanProcess* process, const char* name)
{
	if (process == nullptr)
	{

		return nullptr;
	}

	auto library = new MagicBeanLibrary
	{
		.lpProcess = process
	};

	try
	{
		if (!AL::OS::ProcessLibrary::Open(library->Base, process->Base, name))
		{
			delete library;

			return nullptr;
		}
	}
	catch (const AL::Exception& exception)
	{
		delete library;

		return nullptr;
	}

	return library;
}
void              magic_bean_process_library_close(MagicBeanLibrary* library)
{
	if (library != nullptr)
	{
		library->lpProcess->Libraries.Remove(
			library
		);

		delete library;
	}
}
MagicBeanLibrary* magic_bean_process_library_load_file(MagicBeanProcess* process, const char* path)
{
	if (process == nullptr)
	{

		return nullptr;
	}

	auto library = new MagicBeanLibrary
	{
		.lpProcess = process
	};

	try
	{
		if (!AL::OS::ProcessLibrary::Load(library->Base, process->Base, AL::FileSystem::Path(path)))
		{
			delete library;

			return nullptr;
		}
	}
	catch (const AL::Exception& exception)
	{
		delete library;

		return nullptr;
	}

	return library;
}
MagicBeanLibrary* magic_bean_process_library_load_buffer(MagicBeanProcess* process, const void* lpBuffer, uint64_t size);
MagicBeanLibrary* magic_bean_process_library_load_memory(MagicBeanProcess* process, uint64_t address, uint64_t size);
void              magic_bean_process_library_unload(MagicBeanLibrary* library)
{
	if (library != nullptr)
	{
		library->Base.Unload();
	}
}
uint64_t          magic_bean_process_library_get_export(MagicBeanLibrary* library, const char* name)
{
	if (library == nullptr)
	{

		return 0;
	}

	if (name == nullptr)
	{

		return 0;
	}

	uint8_t* value;

	try
	{
		if (!library->Base.GetExport(value, name))
		{

			return 0;
		}
	}
	catch (const AL::Exception& exception)
	{

		return 0;
	}

	return reinterpret_cast<uint64_t>(
		value
	);
}
