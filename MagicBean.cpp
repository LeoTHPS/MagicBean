#include "MagicBean.hpp"

#include <tlhelp32.h>
#include <psapi.h>

#include <list>
#include <chrono>
#include <vector>
#include <filesystem>

enum MAGIC_BEAN_HOOK_TYPE
{
	MAGIC_BEAN_HOOK_TYPE_KEY,
	MAGIC_BEAN_HOOK_TYPE_BUTTON
};

struct magic_bean_timer
{
	int64_t start;
	double  frequency;
};

struct magic_bean
{
	magic_bean_timer               timer;
	std::list<magic_bean_hook*>    hooks;
	std::list<magic_bean_process*> processes;

	magic_bean();

	~magic_bean();
};
struct magic_bean_hook
{
	int type;

	union
	{
		struct
		{
			int                             value;
			magic_bean_on_key_state_changed callback;
		} key;

		struct
		{
			int                                value;
			magic_bean_on_button_state_changed callback;
		} button;
	};
};
struct magic_bean_thread
{
	uint32_t            id;
	HANDLE              handle;
	magic_bean_process* process;
};
struct magic_bean_window
{
	HWND                handle;
	magic_bean_process* process;
};
struct magic_bean_process
{
	uint32_t                      id;
	HANDLE                        handle;
	std::list<magic_bean_thread*> threads;
	std::list<magic_bean_window*> windows;
};

struct magic_bean_key_info
{
	int    key;
	WPARAM message_wparam;
};
struct magic_bean_key_state_info
{
	int    state;
	UINT   message;
	LPARAM message_lparam;
};

constexpr magic_bean_key_info MAGIC_BEAN_KEY_INFO[MAGIC_BEAN_KEY_COUNT] =
{
	{ MAGIC_BEAN_KEY_A,         0x41        },
	{ MAGIC_BEAN_KEY_B,         0x42        },
	{ MAGIC_BEAN_KEY_C,         0x43        },
	{ MAGIC_BEAN_KEY_D,         0x44        },
	{ MAGIC_BEAN_KEY_E,         0x45        },
	{ MAGIC_BEAN_KEY_F,         0x46        },
	{ MAGIC_BEAN_KEY_G,         0x47        },
	{ MAGIC_BEAN_KEY_H,         0x48        },
	{ MAGIC_BEAN_KEY_I,         0x49        },
	{ MAGIC_BEAN_KEY_J,         0x4A        },
	{ MAGIC_BEAN_KEY_K,         0x4B        },
	{ MAGIC_BEAN_KEY_L,         0x4C        },
	{ MAGIC_BEAN_KEY_M,         0x4D        },
	{ MAGIC_BEAN_KEY_N,         0x4E        },
	{ MAGIC_BEAN_KEY_O,         0x4F        },
	{ MAGIC_BEAN_KEY_P,         0x50        },
	{ MAGIC_BEAN_KEY_Q,         0x51        },
	{ MAGIC_BEAN_KEY_R,         0x52        },
	{ MAGIC_BEAN_KEY_S,         0x53        },
	{ MAGIC_BEAN_KEY_T,         0x54        },
	{ MAGIC_BEAN_KEY_U,         0x55        },
	{ MAGIC_BEAN_KEY_V,         0x56        },
	{ MAGIC_BEAN_KEY_W,         0x57        },
	{ MAGIC_BEAN_KEY_X,         0x58        },
	{ MAGIC_BEAN_KEY_Y,         0x59        },
	{ MAGIC_BEAN_KEY_Z,         0x5A        },
	{ MAGIC_BEAN_KEY_NUM_0,     0x30        },
	{ MAGIC_BEAN_KEY_NUM_1,     0x31        },
	{ MAGIC_BEAN_KEY_NUM_2,     0x32        },
	{ MAGIC_BEAN_KEY_NUM_3,     0x33        },
	{ MAGIC_BEAN_KEY_NUM_4,     0x34        },
	{ MAGIC_BEAN_KEY_NUM_5,     0x35        },
	{ MAGIC_BEAN_KEY_NUM_6,     0x36        },
	{ MAGIC_BEAN_KEY_NUM_7,     0x37        },
	{ MAGIC_BEAN_KEY_NUM_8,     0x38        },
	{ MAGIC_BEAN_KEY_NUM_9,     0x39        },
	{ MAGIC_BEAN_KEY_NUMPAD_0,  VK_NUMPAD0  },
	{ MAGIC_BEAN_KEY_NUMPAD_1,  VK_NUMPAD1  },
	{ MAGIC_BEAN_KEY_NUMPAD_2,  VK_NUMPAD2  },
	{ MAGIC_BEAN_KEY_NUMPAD_3,  VK_NUMPAD3  },
	{ MAGIC_BEAN_KEY_NUMPAD_4,  VK_NUMPAD4  },
	{ MAGIC_BEAN_KEY_NUMPAD_5,  VK_NUMPAD5  },
	{ MAGIC_BEAN_KEY_NUMPAD_6,  VK_NUMPAD6  },
	{ MAGIC_BEAN_KEY_NUMPAD_7,  VK_NUMPAD7  },
	{ MAGIC_BEAN_KEY_NUMPAD_8,  VK_NUMPAD8  },
	{ MAGIC_BEAN_KEY_NUMPAD_9,  VK_NUMPAD9  },
	{ MAGIC_BEAN_KEY_F1,        VK_F1       },
	{ MAGIC_BEAN_KEY_F2,        VK_F2       },
	{ MAGIC_BEAN_KEY_F3,        VK_F3       },
	{ MAGIC_BEAN_KEY_F4,        VK_F4       },
	{ MAGIC_BEAN_KEY_F5,        VK_F5       },
	{ MAGIC_BEAN_KEY_F6,        VK_F6       },
	{ MAGIC_BEAN_KEY_F7,        VK_F7       },
	{ MAGIC_BEAN_KEY_F8,        VK_F8       },
	{ MAGIC_BEAN_KEY_F9,        VK_F9       },
	{ MAGIC_BEAN_KEY_F10,       VK_F10      },
	{ MAGIC_BEAN_KEY_F11,       VK_F11      },
	{ MAGIC_BEAN_KEY_F12,       VK_F12      },
	{ MAGIC_BEAN_KEY_TILDE,     VK_OEM_3    },
	{ MAGIC_BEAN_KEY_ALT,       VK_MENU     },
	{ MAGIC_BEAN_KEY_LALT,      VK_LMENU    },
	{ MAGIC_BEAN_KEY_RALT,      VK_RMENU    },
	{ MAGIC_BEAN_KEY_CLEAR,     VK_CLEAR    },
	{ MAGIC_BEAN_KEY_DELETE,    VK_DELETE   },
	{ MAGIC_BEAN_KEY_ENTER,     VK_RETURN   },
	{ MAGIC_BEAN_KEY_ESCAPE,    VK_ESCAPE   },
	{ MAGIC_BEAN_KEY_BACKSPACE, VK_BACK     },
	{ MAGIC_BEAN_KEY_CONTROL,   VK_CONTROL  },
	{ MAGIC_BEAN_KEY_LCONTROL,  VK_LCONTROL },
	{ MAGIC_BEAN_KEY_RCONTROL,  VK_RCONTROL },
	{ MAGIC_BEAN_KEY_SHIFT,     VK_SHIFT    },
	{ MAGIC_BEAN_KEY_LSHIFT,    VK_LSHIFT   },
	{ MAGIC_BEAN_KEY_RSHIFT,    VK_RSHIFT   },
	{ MAGIC_BEAN_KEY_SPACEBAR,  VK_SPACE    },
	{ MAGIC_BEAN_KEY_TAB,       VK_TAB      },
	{ MAGIC_BEAN_KEY_UP,        VK_UP       },
	{ MAGIC_BEAN_KEY_DOWN,      VK_DOWN     },
	{ MAGIC_BEAN_KEY_LEFT,      VK_LEFT     },
	{ MAGIC_BEAN_KEY_RIGHT,     VK_RIGHT    }
};
template<size_t ... I>
constexpr bool static_assert_magic_bean_key_info(std::index_sequence<I ...>)
{
	return ((MAGIC_BEAN_KEY_INFO[I].key == I) && ...);
}
static_assert(static_assert_magic_bean_key_info(std::make_index_sequence<MAGIC_BEAN_KEY_COUNT> {}));

constexpr magic_bean_key_state_info MAGIC_BEAN_KEY_STATE_INFO[MAGIC_BEAN_KEY_STATE_COUNT] =
{
	{ MAGIC_BEAN_KEY_STATE_UP,   WM_KEYUP,   (LPARAM)0xC0000001 },
	{ MAGIC_BEAN_KEY_STATE_DOWN, WM_KEYDOWN, (LPARAM)0x00000000 }
};
template<size_t ... I>
constexpr bool static_assert_magic_bean_key_state_info(std::index_sequence<I ...>)
{
	return ((MAGIC_BEAN_KEY_STATE_INFO[I].state == I) && ...);
}
static_assert(static_assert_magic_bean_key_state_info(std::make_index_sequence<MAGIC_BEAN_KEY_STATE_COUNT> {}));

magic_bean magic;

void                          magic_bean_timer_init(magic_bean_timer& timer)
{
	LARGE_INTEGER li;
	QueryPerformanceFrequency(&li);
	timer.frequency = 1000000000.0 / li.QuadPart;

	QueryPerformanceCounter(&li);
	timer.start = li.QuadPart;
}
uint64_t                      magic_bean_timer_get_elapsed_ms(magic_bean_timer& timer)
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);

	return ((li.QuadPart - timer.start) * timer.frequency) / 1000000;
}
uint64_t                      magic_bean_timer_get_elapsed_us(magic_bean_timer& timer)
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);

	return ((li.QuadPart - timer.start) * timer.frequency) / 1000;
}
void                          magic_bean_timer_reset(magic_bean_timer& timer)
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);

	timer.start = li.QuadPart;
}

void                          magic_bean_hook_deinit(magic_bean_hook* hook)
{
	delete hook;
}
void                          magic_bean_thread_deinit(magic_bean_thread* thread)
{
	CloseHandle(thread->handle);

	delete thread;
}
void                          magic_bean_window_deinit(magic_bean_window* window)
{
	delete window;
}
void                          magic_bean_process_deinit(magic_bean_process* process)
{
	process->threads.remove_if([](magic_bean_thread* thread) {
		magic_bean_thread_deinit(thread);

		return true;
	});

	process->windows.remove_if([](magic_bean_window* window) {
		magic_bean_window_deinit(window);

		return true;
	});

	CloseHandle(process->handle);

	delete process;
}

magic_bean::magic_bean()
{
	magic_bean_timer_init(timer);
}
magic_bean::~magic_bean()
{
	hooks.remove_if([](magic_bean_hook* hook) {
		magic_bean_hook_deinit(hook);

		return true;
	});

	processes.remove_if([](magic_bean_process* process) {
		magic_bean_process_deinit(process);

		return true;
	});
}

uint64_t                      magic_bean_get_time_ms()
{
	return magic_bean_timer_get_elapsed_ms(magic.timer);
}
uint64_t                      magic_bean_get_time_us()
{
	return magic_bean_timer_get_elapsed_us(magic.timer);
}
uint64_t                      magic_bean_get_timestamp()
{
	return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}
void                          magic_bean_sleep(uint32_t ms)
{
	Sleep((DWORD)ms);
}
magic_bean_process*           magic_bean_open_process_by_id(uint32_t id)
{
	HANDLE handle;

	if ((handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, (DWORD)id)) == NULL)
		return nullptr;

	auto process = new magic_bean_process
	{
		.id     = id,
		.handle = handle
	};

	magic.processes.push_back(process);

	return process;
}
magic_bean_process*           magic_bean_open_process_by_name(std::string_view name)
{
	HANDLE snapshot;

	if ((snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)) == INVALID_HANDLE_VALUE)
		return nullptr;

	PROCESSENTRY32 process = { .dwSize = sizeof(PROCESSENTRY32) };

	if (!Process32First(snapshot, &process))
	{
		CloseHandle(snapshot);

		return nullptr;
	}

	do
	{
		if (!stricmp(process.szExeFile, name.data()))
		{
			CloseHandle(snapshot);

			HANDLE handle;

			if ((handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, process.th32ProcessID)) == NULL)
				return nullptr;

			auto p = new magic_bean_process
			{
				.id     = process.th32ProcessID,
				.handle = handle
			};

			magic.processes.push_back(p);

			return p;
		}
	} while (Process32Next(snapshot, &process));

	if (GetLastError() != ERROR_NO_MORE_FILES)
	{
		CloseHandle(snapshot);

		return nullptr;
	}

	CloseHandle(snapshot);

	return nullptr;
}
magic_bean_process*           magic_bean_start_process(std::string_view path)
{
	STARTUPINFO         startup = { .cb = sizeof(STARTUPINFO) };
	PROCESS_INFORMATION information;

	auto working_directory = std::filesystem::path(path).parent_path().generic_string();

	if (!CreateProcessA(path.data(), NULL, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE | CREATE_NEW_PROCESS_GROUP, NULL, working_directory.c_str(), &startup, &information))
		return nullptr;

	auto process = new magic_bean_process
	{
		.id     = information.dwProcessId,
		.handle = information.hProcess
	};

	magic.processes.push_back(process);

	return process;
}
void                          magic_bean_close_process(magic_bean_process* process)
{
	if (!process)
		return;

	magic.processes.remove(process);

	magic_bean_process_deinit(process);
}
magic_bean_hook*              magic_bean_hook_key(int key, magic_bean_on_key_state_changed on_state_changed)
{
	if (!on_state_changed || (key >= MAGIC_BEAN_KEY_COUNT))
		return nullptr;

	// TODO: implement

	return nullptr;
}
magic_bean_hook*              magic_bean_hook_button(int button, magic_bean_on_button_state_changed on_state_changed)
{
	if (!on_state_changed || (button >= MAGIC_BEAN_BUTTON_COUNT))
		return nullptr;

	// TODO: implement

	return nullptr;
}
void                          magic_bean_unhook(magic_bean_hook* hook)
{
	if (!hook)
		return;

	magic.hooks.remove(hook);

	magic_bean_hook_deinit(hook);
}
std::tuple<bool, uint64_t>    magic_bean_get_module_export(std::string_view module, std::string_view name)
{
	std::tuple<bool, uint64_t> value(false, 0);

	if (auto handle = GetModuleHandleA(module.data()))
		if (auto function = GetProcAddress(handle, name.data()))
		{
			std::get<0>(value) = true;
			std::get<1>(value) = (uint64_t)function;
		}

	return value;
}
bool                          magic_bean_enumerate_processes(magic_bean_enum_process_callback callback)
{
	if (!callback)
		return false;

	HANDLE snapshot;

	if ((snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)) == INVALID_HANDLE_VALUE)
		return false;

	PROCESSENTRY32 process = { .dwSize = sizeof(PROCESSENTRY32) };

	if (!Process32First(snapshot, &process))
	{
		CloseHandle(snapshot);

		return false;
	}

	do
		callback(process.th32ProcessID, process.szExeFile);
	while (Process32Next(snapshot, &process));

	if (GetLastError() != ERROR_NO_MORE_FILES)
	{
		CloseHandle(snapshot);

		return false;
	}

	CloseHandle(snapshot);

	return true;
}

bool                          magic_bean_thread_is_running(magic_bean_thread* thread)
{
	if (!thread)
		return false;

	DWORD exit_code;

	if (GetExitCodeThread(thread->handle, &exit_code) != STILL_ACTIVE)
		return false;

	return true;
}
uint32_t                      magic_bean_thread_get_id(magic_bean_thread* thread)
{
	if (!thread)
		return 0;

	return thread->id;
}
bool                          magic_bean_thread_resume(magic_bean_thread* thread)
{
	if (!thread)
		return false;

	if (ResumeThread(thread->handle) == (DWORD)-1)
		return false;

	return true;
}
bool                          magic_bean_thread_suspend(magic_bean_thread* thread)
{
	if (!thread)
		return false;

	if (SuspendThread(thread->handle) == (DWORD)-1)
		return false;

	return true;
}
bool                          magic_bean_thread_terminate(magic_bean_thread* thread, uint32_t exit_code)
{
	if (!thread)
		return false;

	if (!TerminateThread(thread->handle, (DWORD)exit_code))
		return false;

	return true;
}
// @return 0 on error
// @return -1 on timeout
int                           magic_bean_thread_join(magic_bean_thread* thread, uint32_t timeout_ms)
{
	if (!thread)
		return 0;

	switch (WaitForSingleObject(thread->handle, (DWORD)timeout_ms))
	{
		case WAIT_FAILED:
			return 0;

		case WAIT_TIMEOUT:
			return -1;
	}

	return 1;
}

bool                          magic_bean_window_is_focus(magic_bean_window* window)
{
	if (!window)
		return false;

	return window->handle == GetForegroundWindow();
}
std::string                   magic_bean_window_get_title(magic_bean_window* window)
{
	std::string value;

	if (window)
		if (auto length = GetWindowTextLengthA(window->handle))
		{
			value.resize(length);

			if (!GetWindowTextA(window->handle, value.data(), length + 1) && GetLastError())
				value.clear();
		}

	return value;
}
bool                          magic_bean_window_send_key(magic_bean_window* window, int value, int state)
{
	if (!window || (value >= MAGIC_BEAN_KEY_COUNT) || (state >= MAGIC_BEAN_KEY_STATE_COUNT))
		return false;

	if (!PostMessageA(window->handle, MAGIC_BEAN_KEY_STATE_INFO[state].message, MAGIC_BEAN_KEY_INFO[value].message_wparam, MAGIC_BEAN_KEY_STATE_INFO[state].message_lparam))
		return false;

	return true;
}
bool                          magic_bean_window_send_button(magic_bean_window* window, int value, int state)
{
	if (!window || (value >= MAGIC_BEAN_BUTTON_COUNT) || (state >= MAGIC_BEAN_BUTTON_STATE_COUNT))
		return false;

	// TODO: implement

	return false;
}
bool                          magic_bean_window_send_string(magic_bean_window* window, std::string_view value)
{
	if (!window)
		return false;

	for (auto c : value)
		if (!PostMessageA(window->handle, WM_CHAR, (WPARAM)c, 0))
			return false;

	return true;
}
bool                          magic_bean_window_set_title(magic_bean_window* window, std::string_view value)
{
	if (!window)
		return false;

	if (!SetWindowTextA(window->handle, value.data()))
		return false;

	return true;
}

bool                          magic_bean_process_is_32_bit(magic_bean_process* process)
{
	if (!process)
		return false;

	BOOL is_wow_64;

	if (!IsWow64Process(process->handle, &is_wow_64))
		return false;

	return is_wow_64 != FALSE;
}
bool                          magic_bean_process_is_running(magic_bean_process* process)
{
	if (!process)
		return false;

	DWORD exit_code;

	if (!GetExitCodeProcess(process->handle, &exit_code))
		return false;

	return exit_code == STILL_ACTIVE;
}
uint32_t                      magic_bean_process_get_id(magic_bean_process* process)
{
	if (!process)
		return 0;

	return process->id;
}
uint64_t                      magic_bean_process_get_file_version(magic_bean_process* process)
{
	if (!process)
		return 0;

	char path[MAX_PATH + 1] = {};

	if (!GetModuleFileNameExA(process->handle, NULL, path, MAX_PATH))
		return 0;

	DWORD version_handle;
	DWORD version_info_size;

	if ((version_info_size = GetFileVersionInfoSizeA(path, &version_handle)) == 0)
		return 0;

	std::vector<uint8_t> version_info_buffer(version_info_size);

	if (!GetFileVersionInfoA(path, version_handle, version_info_size, version_info_buffer.data()))
		return 0;

	VS_FIXEDFILEINFO* version_info;
	UINT              version_info_length;

	if (!VerQueryValueA(version_info_buffer.data(), "\\", (LPVOID*)&version_info, &version_info_length))
		return 0;

	if (!version_info || (version_info_length != sizeof(VS_FIXEDFILEINFO)) || (version_info->dwSignature != 0xFEEF04BD))
		return 0;

	return ((uint64_t)(version_info->dwFileVersionMS) << 32) | (uint64_t)version_info->dwFileVersionLS;
}
magic_bean_thread*            magic_bean_process_open_thread_by_id(magic_bean_process* process, uint32_t id)
{
	if (!process)
		return nullptr;

	HANDLE handle;

	if ((handle = OpenThread(THREAD_ALL_ACCESS, FALSE, (DWORD)id)) == NULL)
		return nullptr;

	auto thread = new magic_bean_thread
	{
		.id      = id,
		.handle  = handle,
		.process = process
	};

	process->threads.push_back(thread);

	return thread;
}
magic_bean_thread*            magic_bean_process_start_thread(magic_bean_process* process, uint64_t address, uint64_t param)
{
	if (!process)
		return nullptr;

	DWORD  id;
	HANDLE handle;

	if (!(handle = CreateRemoteThread(process->handle, NULL, 0, (LPTHREAD_START_ROUTINE)address, (LPVOID)param, 0, &id)))
		return nullptr;

	auto thread = new magic_bean_thread
	{
		.id      = id,
		.handle  = handle,
		.process = process
	};

	process->threads.push_back(thread);

	return thread;
}
void                          magic_bean_process_close_thread(magic_bean_process* process, magic_bean_thread* thread)
{
	if (!process || !thread)
		return;

	process->threads.remove(thread);

	magic_bean_thread_deinit(thread);
}
struct                        magic_bean_process_open_window_by_index_context
{
	bool                error;
	HWND                handle;
	uint32_t            index[2];
	magic_bean_process* process;
};
BOOL CALLBACK                 magic_bean_process_open_window_by_index_callback(HWND handle, LPARAM param)
{
	DWORD pid;
	auto  context = (magic_bean_process_open_window_by_index_context*)param;

	if (!GetWindowThreadProcessId(handle, &pid))
	{
		context->error = true;

		return FALSE;
	}

	if (pid == context->process->id)
	{
		if (context->index[0]++ == context->index[1])
		{
			context->handle = handle;

			return FALSE;
		}
	}

	return TRUE;
}
magic_bean_window*            magic_bean_process_open_window_by_index(magic_bean_process* process, uint32_t index)
{
	if (!process)
		return nullptr;

	magic_bean_process_open_window_by_index_context context =
	{
		.error   = false,
		.handle  = NULL,
		.index   = { 1, index },
		.process = process
	};

	if ((!EnumWindows(&magic_bean_process_open_window_by_index_callback, (LPARAM)&context) && context.error) || !context.handle)
		return nullptr;

	auto window = new magic_bean_window
	{
		.handle  = context.handle,
		.process = process
	};

	process->windows.push_back(window);

	return window;
}
struct                        magic_bean_process_open_window_by_title_context
{
	bool                error;
	std::string_view*   title;
	HWND                handle;
	magic_bean_process* process;
};
BOOL CALLBACK                 magic_bean_process_open_window_by_title_callback(HWND handle, LPARAM param)
{
	DWORD pid;
	auto  context = (magic_bean_process_open_window_by_title_context*)param;

	if (!GetWindowThreadProcessId(handle, &pid))
	{
		context->error = true;

		return FALSE;
	}

	if (pid == context->process->id)
	{
		std::string title;

		if (auto length = GetWindowTextLengthA(handle))
		{
			if (length == context->title->length())
			{
				title.resize(length);

				if (!GetWindowTextA(handle, title.data(), length) && GetLastError())
				{
					context->error = true;

					return FALSE;
				}

				if (!title.compare(*context->title))
				{
					context->handle = handle;

					return FALSE;
				}
			}
		}
	}

	return TRUE;
}
magic_bean_window*            magic_bean_process_open_window_by_title(magic_bean_process* process, std::string_view title)
{
	if (!process)
		return nullptr;

	magic_bean_process_open_window_by_title_context context =
	{
		.error   = false,
		.title   = &title,
		.handle  = NULL,
		.process = process
	};

	if ((!EnumWindows(&magic_bean_process_open_window_by_index_callback, (LPARAM)&context) && context.error) || !context.handle)
		return nullptr;

	auto window = new magic_bean_window
	{
		.handle  = context.handle,
		.process = process
	};

	process->windows.push_back(window);

	return window;
}
void                          magic_bean_process_close_window(magic_bean_process* process, magic_bean_window* window)
{
	if (!process || !window)
		return;

	process->windows.remove(window);

	magic_bean_window_deinit(window);
}
bool                          magic_bean_process_resume(magic_bean_process* process)
{
	if (!process)
		return false;

	HANDLE snapshot;

	if ((snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, process->id)) == INVALID_HANDLE_VALUE)
		return false;

	THREADENTRY32 thread = { .dwSize = sizeof(THREADENTRY32) };

	if (!Thread32First(snapshot, &thread))
	{
		CloseHandle(snapshot);

		return false;
	}

	HANDLE            handle;
	std::list<HANDLE> threads;

	do
	{
		if ((handle = OpenThread(THREAD_SUSPEND_RESUME, FALSE, thread.th32ThreadID)) == NULL)
		{
			threads.remove_if([](HANDLE handle) {
				CloseHandle(handle);

				return true;
			});

			CloseHandle(snapshot);

			return false;
		}

		if (ResumeThread(handle) == (DWORD)-1)
		{
			threads.remove_if([](HANDLE handle) {
				CloseHandle(handle);

				return true;
			});

			CloseHandle(snapshot);

			return false;
		}

		threads.push_back(handle);
	}
	while (Thread32Next(snapshot, &thread));

	if (GetLastError() != ERROR_NO_MORE_FILES)
	{
		threads.remove_if([](HANDLE handle) {
			CloseHandle(handle);

			return true;
		});

		CloseHandle(snapshot);

		return false;
	}

	threads.remove_if([](HANDLE handle) {
		CloseHandle(handle);

		return true;
	});

	return true;
}
bool                          magic_bean_process_suspend(magic_bean_process* process)
{
	if (!process)
		return false;

	HANDLE snapshot;

	if ((snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, process->id)) == INVALID_HANDLE_VALUE)
		return false;

	THREADENTRY32 thread = { .dwSize = sizeof(THREADENTRY32) };

	if (!Thread32First(snapshot, &thread))
	{
		CloseHandle(snapshot);

		return false;
	}

	HANDLE            handle;
	std::list<HANDLE> threads;

	do
	{
		if ((handle = OpenThread(THREAD_SUSPEND_RESUME, FALSE, thread.th32ThreadID)) == NULL)
		{
			threads.remove_if([](HANDLE handle) {
				ResumeThread(handle);
				CloseHandle(handle);

				return true;
			});

			CloseHandle(snapshot);

			return false;
		}

		if (SuspendThread(handle) == (DWORD)-1)
		{
			threads.remove_if([](HANDLE handle) {
				ResumeThread(handle);
				CloseHandle(handle);

				return true;
			});

			CloseHandle(snapshot);

			return false;
		}

		threads.push_back(handle);
	}
	while (Thread32Next(snapshot, &thread));

	if (GetLastError() != ERROR_NO_MORE_FILES)
	{
		threads.remove_if([](HANDLE handle) {
			CloseHandle(handle);

			return true;
		});

		CloseHandle(snapshot);

		return false;
	}

	threads.remove_if([](HANDLE handle) {
		CloseHandle(handle);

		return true;
	});

	CloseHandle(snapshot);

	return true;
}
bool                          magic_bean_process_enumerate_threads(magic_bean_process* process, magic_bean_process_enum_thread_callback callback)
{
	if (!process || !callback)
		return false;

	HANDLE snapshot;

	if ((snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, process->id)) == INVALID_HANDLE_VALUE)
		return false;

	THREADENTRY32 thread = { .dwSize = sizeof(THREADENTRY32) };

	if (!Thread32First(snapshot, &thread))
	{
		CloseHandle(snapshot);

		return false;
	}

	do
		callback(process, thread.th32ThreadID);
	while (Thread32Next(snapshot, &thread));

	if (GetLastError() != ERROR_NO_MORE_FILES)
	{
		CloseHandle(snapshot);

		return false;
	}

	CloseHandle(snapshot);

	return true;
}
struct                        magic_bean_process_enumerate_windows_context
{
	bool                                    error;
	uint32_t                                index;
	magic_bean_process*                     process;
	magic_bean_process_enum_window_callback callback;
};
BOOL CALLBACK                 magic_bean_process_enumerate_windows_callback(HWND handle, LPARAM param)
{
	DWORD pid;
	auto  context = (magic_bean_process_enumerate_windows_context*)param;

	if (!GetWindowThreadProcessId(handle, &pid))
	{
		context->error = true;

		return FALSE;
	}

	if (pid == context->process->id)
	{
		std::string title;

		if (auto length = GetWindowTextLengthA(handle))
		{
			title.resize(length);

			if (!GetWindowTextA(handle, title.data(), length) && GetLastError())
			{
				context->error = true;

				return FALSE;
			}
		}

		context->callback(context->process, title, context->index++);
	}

	return TRUE;
}
bool                          magic_bean_process_enumerate_windows(magic_bean_process* process, magic_bean_process_enum_window_callback callback)
{
	if (!process || !callback)
		return false;

	magic_bean_process_enumerate_windows_context context =
	{
		.error    = false,
		.index    = 1,
		.process  = process,
		.callback = callback
	};

	if (!EnumWindows(&magic_bean_process_enumerate_windows_callback, (LPARAM)&context) && context.error)
		return false;

	return true;
}

std::tuple<bool, uint64_t>    magic_bean_process_memory_find(magic_bean_process* process, uint64_t address, uint64_t size, std::string_view pattern)
{
	std::tuple<bool, uint64_t> value(false, 0);

	if (process && (pattern.length() <= size))
	{
		std::vector<uint8_t> buffer(size);

		if (ReadProcessMemory(process->handle, (LPCVOID)address, (LPVOID)buffer.data(), (SIZE_T)size, NULL))
			for (uint64_t i = 0; i < size; ++i)
			{
				bool is_match = true;

				for (uint64_t j = 0; j < pattern.length(); ++j)
					if ((pattern[j] != '?') && ((uint8_t)pattern[j] != buffer[i + j]))
					{
						is_match = false;

						break;
					}

				if (is_match)
				{
					std::get<0>(value) = true;
					std::get<1>(value) = address + i;

					break;
				}

				if ((i + pattern.length()) > size)
					break;
			}
	}

	return value;
}
bool                          magic_bean_process_memory_read(magic_bean_process* process, uint64_t address, void* value, uint64_t size)
{
	if (!process || !value)
		return false;

	if (size == 0)
		return true;

	if (!ReadProcessMemory(process->handle, (LPCVOID)address, (LPVOID)value, (SIZE_T)size, NULL))
		return false;

	return true;
}
std::tuple<bool, std::string> magic_bean_process_memory_read(magic_bean_process* process, uint64_t address, uint64_t size)
{
	std::tuple<bool, std::string> value(false, std::string(size, '\0'));

	std::get<0>(value) = magic_bean_process_memory_read(process, address, std::get<1>(value).data(), size);

	return value;
}
std::tuple<bool, int8_t>      magic_bean_process_memory_read_int8(magic_bean_process* process, uint64_t address)
{
	std::tuple<bool, int8_t> value;

	std::get<0>(value) = magic_bean_process_memory_read(process, address, &std::get<1>(value), sizeof(int8_t));

	return value;
}
std::tuple<bool, int16_t>     magic_bean_process_memory_read_int16(magic_bean_process* process, uint64_t address)
{
	std::tuple<bool, int16_t> value;

	std::get<0>(value) = magic_bean_process_memory_read(process, address, &std::get<1>(value), sizeof(int16_t));

	return value;
}
std::tuple<bool, int32_t>     magic_bean_process_memory_read_int32(magic_bean_process* process, uint64_t address)
{
	std::tuple<bool, int32_t> value;

	std::get<0>(value) = magic_bean_process_memory_read(process, address, &std::get<1>(value), sizeof(int32_t));

	return value;
}
std::tuple<bool, int64_t>     magic_bean_process_memory_read_int64(magic_bean_process* process, uint64_t address)
{
	std::tuple<bool, int64_t> value;

	std::get<0>(value) = magic_bean_process_memory_read(process, address, &std::get<1>(value), sizeof(int64_t));

	return value;
}
std::tuple<bool, uint8_t>     magic_bean_process_memory_read_uint8(magic_bean_process* process, uint64_t address)
{
	std::tuple<bool, uint8_t> value;

	std::get<0>(value) = magic_bean_process_memory_read(process, address, &std::get<1>(value), sizeof(uint8_t));

	return value;
}
std::tuple<bool, uint16_t>    magic_bean_process_memory_read_uint16(magic_bean_process* process, uint64_t address)
{
	std::tuple<bool, uint16_t> value;

	std::get<0>(value) = magic_bean_process_memory_read(process, address, &std::get<1>(value), sizeof(uint16_t));

	return value;
}
std::tuple<bool, uint32_t>    magic_bean_process_memory_read_uint32(magic_bean_process* process, uint64_t address)
{
	std::tuple<bool, uint32_t> value;

	std::get<0>(value) = magic_bean_process_memory_read(process, address, &std::get<1>(value), sizeof(uint32_t));

	return value;
}
std::tuple<bool, std::string> magic_bean_process_memory_read_uint64(magic_bean_process* process, uint64_t address)
{
	std::tuple<bool, std::string> value(false, "0x0");
	uint64_t                      number;

	if (std::get<0>(value) = magic_bean_process_memory_read(process, address, &number, sizeof(uint64_t)))
		if (number != 0)
		{
			auto length = snprintf(nullptr, 0, "0x%llX", number);

			std::get<1>(value).resize(length);
			snprintf(std::get<1>(value).data(), length + 1, "0x%llX", number);
		}

	return value;
}
std::tuple<bool, float>       magic_bean_process_memory_read_float(magic_bean_process* process, uint64_t address)
{
	std::tuple<bool, float> value;

	std::get<0>(value) = magic_bean_process_memory_read(process, address, &std::get<1>(value), sizeof(float));

	return value;
}
std::tuple<bool, double>      magic_bean_process_memory_read_double(magic_bean_process* process, uint64_t address)
{
	std::tuple<bool, double> value;

	std::get<0>(value) = magic_bean_process_memory_read(process, address, &std::get<1>(value), sizeof(double));

	return value;
}
std::tuple<bool, std::string> magic_bean_process_memory_read_string(magic_bean_process* process, uint64_t address)
{
	std::tuple<bool, std::string> value(false, std::string());

	if (process)
	{
		bool success = true;

		for (char c; success = ReadProcessMemory(process->handle, (LPCVOID)address, &c, sizeof(char), NULL); address += sizeof(char))
		{
			if (c == '\0')
				break;

			std::get<1>(value).push_back(c);
		}

		if (!(std::get<0>(value) = success))
			std::get<1>(value).clear();
	}

	return value;
}
std::tuple<bool, std::string> magic_bean_process_memory_read_string_ex(magic_bean_process* process, uint64_t address, uint64_t length)
{
	std::tuple<bool, std::string> value(false, std::string((size_t)length, '\0'));

	if (std::get<0>(value) = magic_bean_process_memory_read(process, address, std::get<1>(value).data(), length))
		if (size_t i; (i = std::get<1>(value).find('\0')) != std::string::npos)
			std::get<1>(value).erase(i);

	return value;
}
bool                          magic_bean_process_memory_write(magic_bean_process* process, uint64_t address, const void* value, size_t size)
{
	if (!process || !value)
		return false;

	if (size == 0)
		return true;

	if (!WriteProcessMemory(process->handle, (LPVOID)address, (LPCVOID)value, (SIZE_T)size, NULL))
		return false;

	return true;
}
bool                          magic_bean_process_memory_write(magic_bean_process* process, uint64_t address, std::string_view value)
{
	return magic_bean_process_memory_write(process, address, value.data(), value.length());
}
bool                          magic_bean_process_memory_write_int8(magic_bean_process* process, uint64_t address, int8_t value)
{
	return magic_bean_process_memory_write(process, address, &value, sizeof(int8_t));
}
bool                          magic_bean_process_memory_write_int16(magic_bean_process* process, uint64_t address, int16_t value)
{
	return magic_bean_process_memory_write(process, address, &value, sizeof(int16_t));
}
bool                          magic_bean_process_memory_write_int32(magic_bean_process* process, uint64_t address, int32_t value)
{
	return magic_bean_process_memory_write(process, address, &value, sizeof(int32_t));
}
bool                          magic_bean_process_memory_write_int64(magic_bean_process* process, uint64_t address, int64_t value)
{
	return magic_bean_process_memory_write(process, address, &value, sizeof(int64_t));
}
bool                          magic_bean_process_memory_write_uint8(magic_bean_process* process, uint64_t address, uint8_t value)
{
	return magic_bean_process_memory_write(process, address, &value, sizeof(uint8_t));
}
bool                          magic_bean_process_memory_write_uint16(magic_bean_process* process, uint64_t address, uint16_t value)
{
	return magic_bean_process_memory_write(process, address, &value, sizeof(uint16_t));
}
bool                          magic_bean_process_memory_write_uint32(magic_bean_process* process, uint64_t address, uint32_t value)
{
	return magic_bean_process_memory_write(process, address, &value, sizeof(uint32_t));
}
bool                          magic_bean_process_memory_write_uint64(magic_bean_process* process, uint64_t address, uint64_t value)
{
	return magic_bean_process_memory_write(process, address, &value, sizeof(uint64_t));
}
bool                          magic_bean_process_memory_write_float(magic_bean_process* process, uint64_t address, float value)
{
	return magic_bean_process_memory_write(process, address, &value, sizeof(float));
}
bool                          magic_bean_process_memory_write_double(magic_bean_process* process, uint64_t address, double value)
{
	return magic_bean_process_memory_write(process, address, &value, sizeof(double));
}
bool                          magic_bean_process_memory_write_string(magic_bean_process* process, uint64_t address, std::string_view value)
{
	static constexpr uint8_t END_OF_LINE = 0;

	if (!magic_bean_process_memory_write(process, address, value.data(), value.length()))
		return false;

	if (!magic_bean_process_memory_write(process, address + value.length(), &END_OF_LINE, sizeof(uint8_t)))
		return false;

	return true;
}
std::tuple<bool, uint64_t>    magic_bean_process_memory_allocate(magic_bean_process* process, uint64_t size, int protection)
{
	std::tuple<bool, uint64_t> value(false, 0);

	if (process)
		std::get<0>(value) = (std::get<1>(value) = (uint64_t)VirtualAllocEx(process->handle, NULL, (SIZE_T)size, MEM_COMMIT, (DWORD)protection)) != 0;

	return value;
}
bool                          magic_bean_process_memory_allocate_at(magic_bean_process* process, uint64_t address, uint64_t size, int protection)
{
	if (!process)
		return false;

	if (VirtualAllocEx(process->handle, (LPVOID)address, (SIZE_T)size, MEM_COMMIT, (DWORD)protection) == NULL)
		return false;

	return true;
}
bool                          magic_bean_process_memory_release(magic_bean_process* process, uint64_t address)
{
	if (!process)
		return false;

	if (!VirtualFreeEx(process->handle, (LPVOID)address, 0, MEM_RELEASE))
		return false;

	return true;
}
std::tuple<bool, int>         magic_bean_process_memory_set_protection(magic_bean_process* process, uint64_t address, uint64_t size, int protection)
{
	std::tuple<bool, int> value(false, 0);

	if (process)
	{
		DWORD protection_prev;

		if (std::get<0>(value) = VirtualProtectEx(process->handle, (LPVOID)address, (SIZE_T)size, (DWORD)protection, &protection_prev))
			std::get<1>(value) = (int)protection_prev;
	}

	return value;
}
