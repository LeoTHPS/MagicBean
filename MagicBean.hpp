#pragma once
#include <tuple>
#include <string>
#include <cstdint>

#include <windows.h>

enum MAGIC_BEAN_KEY
{
	MAGIC_BEAN_KEY_A,
	MAGIC_BEAN_KEY_B,
	MAGIC_BEAN_KEY_C,
	MAGIC_BEAN_KEY_D,
	MAGIC_BEAN_KEY_E,
	MAGIC_BEAN_KEY_F,
	MAGIC_BEAN_KEY_G,
	MAGIC_BEAN_KEY_H,
	MAGIC_BEAN_KEY_I,
	MAGIC_BEAN_KEY_J,
	MAGIC_BEAN_KEY_K,
	MAGIC_BEAN_KEY_L,
	MAGIC_BEAN_KEY_M,
	MAGIC_BEAN_KEY_N,
	MAGIC_BEAN_KEY_O,
	MAGIC_BEAN_KEY_P,
	MAGIC_BEAN_KEY_Q,
	MAGIC_BEAN_KEY_R,
	MAGIC_BEAN_KEY_S,
	MAGIC_BEAN_KEY_T,
	MAGIC_BEAN_KEY_U,
	MAGIC_BEAN_KEY_V,
	MAGIC_BEAN_KEY_W,
	MAGIC_BEAN_KEY_X,
	MAGIC_BEAN_KEY_Y,
	MAGIC_BEAN_KEY_Z,

	MAGIC_BEAN_KEY_NUM_0,
	MAGIC_BEAN_KEY_NUM_1,
	MAGIC_BEAN_KEY_NUM_2,
	MAGIC_BEAN_KEY_NUM_3,
	MAGIC_BEAN_KEY_NUM_4,
	MAGIC_BEAN_KEY_NUM_5,
	MAGIC_BEAN_KEY_NUM_6,
	MAGIC_BEAN_KEY_NUM_7,
	MAGIC_BEAN_KEY_NUM_8,
	MAGIC_BEAN_KEY_NUM_9,

	MAGIC_BEAN_KEY_NUMPAD_0,
	MAGIC_BEAN_KEY_NUMPAD_1,
	MAGIC_BEAN_KEY_NUMPAD_2,
	MAGIC_BEAN_KEY_NUMPAD_3,
	MAGIC_BEAN_KEY_NUMPAD_4,
	MAGIC_BEAN_KEY_NUMPAD_5,
	MAGIC_BEAN_KEY_NUMPAD_6,
	MAGIC_BEAN_KEY_NUMPAD_7,
	MAGIC_BEAN_KEY_NUMPAD_8,
	MAGIC_BEAN_KEY_NUMPAD_9,

	MAGIC_BEAN_KEY_F1,
	MAGIC_BEAN_KEY_F2,
	MAGIC_BEAN_KEY_F3,
	MAGIC_BEAN_KEY_F4,
	MAGIC_BEAN_KEY_F5,
	MAGIC_BEAN_KEY_F6,
	MAGIC_BEAN_KEY_F7,
	MAGIC_BEAN_KEY_F8,
	MAGIC_BEAN_KEY_F9,
	MAGIC_BEAN_KEY_F10,
	MAGIC_BEAN_KEY_F11,
	MAGIC_BEAN_KEY_F12,

	MAGIC_BEAN_KEY_TILDE,

	MAGIC_BEAN_KEY_ALT,
	MAGIC_BEAN_KEY_LALT,
	MAGIC_BEAN_KEY_RALT,

	MAGIC_BEAN_KEY_CLEAR,
	MAGIC_BEAN_KEY_DELETE,
	MAGIC_BEAN_KEY_ENTER,
	MAGIC_BEAN_KEY_ESCAPE,
	MAGIC_BEAN_KEY_BACKSPACE,

	MAGIC_BEAN_KEY_CONTROL,
	MAGIC_BEAN_KEY_LCONTROL,
	MAGIC_BEAN_KEY_RCONTROL,

	MAGIC_BEAN_KEY_SHIFT,
	MAGIC_BEAN_KEY_LSHIFT,
	MAGIC_BEAN_KEY_RSHIFT,

	MAGIC_BEAN_KEY_SPACEBAR,
	MAGIC_BEAN_KEY_TAB,

	MAGIC_BEAN_KEY_UP,
	MAGIC_BEAN_KEY_DOWN,
	MAGIC_BEAN_KEY_LEFT,
	MAGIC_BEAN_KEY_RIGHT,

	MAGIC_BEAN_KEY_COUNT
};

enum MAGIC_BEAN_BUTTON
{
	MAGIC_BEAN_BUTTON_X1,
	MAGIC_BEAN_BUTTON_X2,
	MAGIC_BEAN_BUTTON_LEFT,
	MAGIC_BEAN_BUTTON_RIGHT,
	MAGIC_BEAN_BUTTON_MIDDLE,

	MAGIC_BEAN_BUTTON_COUNT
};

enum MAGIC_BEAN_KEY_STATE
{
	MAGIC_BEAN_KEY_STATE_UP,
	MAGIC_BEAN_KEY_STATE_DOWN,

	MAGIC_BEAN_KEY_STATE_COUNT
};

enum MAGIC_BEAN_BUTTON_STATE
{
	MAGIC_BEAN_BUTTON_STATE_UP,
	MAGIC_BEAN_BUTTON_STATE_DOWN,

	MAGIC_BEAN_BUTTON_STATE_COUNT
};

enum MAGIC_BEAN_MEMORY_PROTECTION
{
	MAGIC_BEAN_MEMORY_PROTECTION_NO_ACCESS          = PAGE_NOACCESS,
	MAGIC_BEAN_MEMORY_PROTECTION_READ               = PAGE_READONLY,
	MAGIC_BEAN_MEMORY_PROTECTION_READ_WRITE         = PAGE_READWRITE,
	MAGIC_BEAN_MEMORY_PROTECTION_WRITE_COPY         = PAGE_WRITECOPY,
	MAGIC_BEAN_MEMORY_PROTECTION_EXECUTE            = PAGE_EXECUTE,
	MAGIC_BEAN_MEMORY_PROTECTION_EXECUTE_READ       = PAGE_EXECUTE_READ,
	MAGIC_BEAN_MEMORY_PROTECTION_EXECUTE_READ_WRITE = PAGE_EXECUTE_READWRITE,
	MAGIC_BEAN_MEMORY_PROTECTION_EXECUTE_WRITE_COPY = PAGE_EXECUTE_WRITECOPY
};

struct magic_bean;
struct magic_bean_hook;
struct magic_bean_thread;
struct magic_bean_window;
struct magic_bean_process;

typedef void(*magic_bean_on_key_state_changed)(magic_bean_hook* hook, int key, int state);
typedef void(*magic_bean_on_button_state_changed)(magic_bean_hook* hook, int button, int state);

typedef void(*magic_bean_enum_process_callback)(uint32_t id, std::string_view name);
typedef void(*magic_bean_process_enum_thread_callback)(magic_bean_process* process, uint32_t id);
typedef void(*magic_bean_process_enum_window_callback)(magic_bean_process* process, std::string_view title, uint32_t index);

uint64_t                      magic_bean_get_time_ms();
uint64_t                      magic_bean_get_time_us();
uint64_t                      magic_bean_get_timestamp();
void                          magic_bean_sleep(uint32_t ms);
magic_bean_process*           magic_bean_open_process_by_id(uint32_t id);
magic_bean_process*           magic_bean_open_process_by_name(std::string_view name);
magic_bean_process*           magic_bean_start_process(std::string_view path);
void                          magic_bean_close_process(magic_bean_process* process);
magic_bean_hook*              magic_bean_hook_key(int key, magic_bean_on_key_state_changed on_state_changed);
magic_bean_hook*              magic_bean_hook_button(int button, magic_bean_on_button_state_changed on_state_changed);
void                          magic_bean_unhook(magic_bean_hook* hook);
std::tuple<bool, uint64_t>    magic_bean_get_module_export(std::string_view module, std::string_view name);
bool                          magic_bean_enumerate_processes(magic_bean_enum_process_callback callback);

bool                          magic_bean_thread_is_running(magic_bean_thread* thread);
uint32_t                      magic_bean_thread_get_id(magic_bean_thread* thread);
bool                          magic_bean_thread_resume(magic_bean_thread* thread);
bool                          magic_bean_thread_suspend(magic_bean_thread* thread);
bool                          magic_bean_thread_terminate(magic_bean_thread* thread, uint32_t exit_code);
// @return 0 on error
// @return -1 on timeout
int                           magic_bean_thread_join(magic_bean_thread* thread, uint32_t timeout_ms);

bool                          magic_bean_window_is_focus(magic_bean_window* window);
std::string                   magic_bean_window_get_title(magic_bean_window* window);
bool                          magic_bean_window_send_key(magic_bean_window* window, int value, int state);
bool                          magic_bean_window_send_button(magic_bean_window* window, int value, int state);
bool                          magic_bean_window_send_string(magic_bean_window* window, std::string_view value);
bool                          magic_bean_window_set_title(magic_bean_window* window, std::string_view value);

bool                          magic_bean_process_is_32_bit(magic_bean_process* process);
bool                          magic_bean_process_is_running(magic_bean_process* process);
uint32_t                      magic_bean_process_get_id(magic_bean_process* process);
uint64_t                      magic_bean_process_get_file_version(magic_bean_process* process);
magic_bean_thread*            magic_bean_process_open_thread_by_id(magic_bean_process* process, uint32_t id);
magic_bean_thread*            magic_bean_process_start_thread(magic_bean_process* process, uint64_t address, uint64_t param);
void                          magic_bean_process_close_thread(magic_bean_process* process, magic_bean_thread* thread);
magic_bean_window*            magic_bean_process_open_window_by_index(magic_bean_process* process, uint32_t index);
magic_bean_window*            magic_bean_process_open_window_by_title(magic_bean_process* process, std::string_view title);
void                          magic_bean_process_close_window(magic_bean_process* process, magic_bean_window* window);
bool                          magic_bean_process_resume(magic_bean_process* process);
bool                          magic_bean_process_suspend(magic_bean_process* process);
bool                          magic_bean_process_enumerate_threads(magic_bean_process* process, magic_bean_process_enum_thread_callback callback);
bool                          magic_bean_process_enumerate_windows(magic_bean_process* process, magic_bean_process_enum_window_callback callback);

std::tuple<bool, uint64_t>    magic_bean_process_memory_find(magic_bean_process* process, uint64_t address, uint64_t size, std::string_view pattern);
std::tuple<bool, std::string> magic_bean_process_memory_read(magic_bean_process* process, uint64_t address, uint64_t size);
std::tuple<bool, int8_t>      magic_bean_process_memory_read_int8(magic_bean_process* process, uint64_t address);
std::tuple<bool, int16_t>     magic_bean_process_memory_read_int16(magic_bean_process* process, uint64_t address);
std::tuple<bool, int32_t>     magic_bean_process_memory_read_int32(magic_bean_process* process, uint64_t address);
std::tuple<bool, int64_t>     magic_bean_process_memory_read_int64(magic_bean_process* process, uint64_t address);
std::tuple<bool, uint8_t>     magic_bean_process_memory_read_uint8(magic_bean_process* process, uint64_t address);
std::tuple<bool, uint16_t>    magic_bean_process_memory_read_uint16(magic_bean_process* process, uint64_t address);
std::tuple<bool, uint32_t>    magic_bean_process_memory_read_uint32(magic_bean_process* process, uint64_t address);
std::tuple<bool, std::string> magic_bean_process_memory_read_uint64(magic_bean_process* process, uint64_t address);
std::tuple<bool, float>       magic_bean_process_memory_read_float(magic_bean_process* process, uint64_t address);
std::tuple<bool, double>      magic_bean_process_memory_read_double(magic_bean_process* process, uint64_t address);
std::tuple<bool, std::string> magic_bean_process_memory_read_string(magic_bean_process* process, uint64_t address);
std::tuple<bool, std::string> magic_bean_process_memory_read_string_ex(magic_bean_process* process, uint64_t address, uint64_t length);
bool                          magic_bean_process_memory_write(magic_bean_process* process, uint64_t address, std::string_view value);
bool                          magic_bean_process_memory_write_int8(magic_bean_process* process, uint64_t address, int8_t value);
bool                          magic_bean_process_memory_write_int16(magic_bean_process* process, uint64_t address, int16_t value);
bool                          magic_bean_process_memory_write_int32(magic_bean_process* process, uint64_t address, int32_t value);
bool                          magic_bean_process_memory_write_int64(magic_bean_process* process, uint64_t address, int64_t value);
bool                          magic_bean_process_memory_write_uint8(magic_bean_process* process, uint64_t address, uint8_t value);
bool                          magic_bean_process_memory_write_uint16(magic_bean_process* process, uint64_t address, uint16_t value);
bool                          magic_bean_process_memory_write_uint32(magic_bean_process* process, uint64_t address, uint32_t value);
bool                          magic_bean_process_memory_write_uint64(magic_bean_process* process, uint64_t address, uint64_t value);
bool                          magic_bean_process_memory_write_float(magic_bean_process* process, uint64_t address, float value);
bool                          magic_bean_process_memory_write_double(magic_bean_process* process, uint64_t address, double value);
bool                          magic_bean_process_memory_write_string(magic_bean_process* process, uint64_t address, std::string_view value);
std::tuple<bool, uint64_t>    magic_bean_process_memory_allocate(magic_bean_process* process, uint64_t size, int protection);
bool                          magic_bean_process_memory_allocate_at(magic_bean_process* process, uint64_t address, uint64_t size, int protection);
bool                          magic_bean_process_memory_release(magic_bean_process* process, uint64_t address);
std::tuple<bool, int>         magic_bean_process_memory_set_protection(magic_bean_process* process, uint64_t address, uint64_t size, int protection);
