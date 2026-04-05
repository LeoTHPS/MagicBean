#include "MagicBean.hpp"

#include <iostream>

#include <LuaCPP.hpp>

enum ERROR_CODE
{
	ERROR_CODE_NONE,
	ERROR_CODE_LUA_ERROR,
	ERROR_CODE_FILE_ERROR,
	ERROR_CODE_FILE_NOT_FOUND
};

#define lua_set_global(lua, value) \
	try \
	{ \
		lua.SetGlobal(#value, value); \
	} \
	catch (const std::exception& exception) \
	{ \
		std::cerr << "Error registering lua global: " << #value << std::endl; \
		std::cerr << exception.what() << std::endl; \
		\
		return ERROR_CODE_LUA_ERROR; \
	}

#define lua_set_global_function(lua, value) \
	try \
	{ \
		lua.SetGlobal<value>(#value); \
	} \
	catch (const std::exception& exception) \
	{ \
		std::cerr << "Error registering lua global function: " << #value << std::endl; \
		std::cerr << exception.what() << std::endl; \
		\
		return ERROR_CODE_LUA_ERROR; \
	}

#define lua_run_file(lua, path) \
	try \
	{ \
		if (!lua.RunFile(path)) \
		{ \
			std::cerr << "File not found: " << path << std::endl; \
			\
			return ERROR_CODE_FILE_NOT_FOUND; \
		} \
	} \
	catch (const std::exception& exception) \
	{ \
		std::cerr << "Error running file: " << path << std::endl; \
		std::cerr << exception.what() << std::endl; \
		\
		return ERROR_CODE_FILE_ERROR; \
	}

#define lua_load_library(lua, library) \
	try \
	{ \
		lua.LoadLibrary(library); \
	} \
	catch (const std::exception& exception) \
	{ \
		std::cerr << "Error loading lua library: " << #library << std::endl; \
		std::cerr << exception.what() << std::endl; \
		\
		return ERROR_CODE_LUA_ERROR; \
	}

int main(int argc, char* argv[])
{
	if (auto lua = LuaCPP())
	{
		lua.SetGlobal("MAGIC_BEAN_INFINITE", INFINITE);

		lua.SetGlobal("MAGIC_BEAN_PLATFORM_X86",    1);
		lua.SetGlobal("MAGIC_BEAN_PLATFORM_X86_64", 2);
		lua.SetGlobal("MAGIC_BEAN_PLATFORM_ARM",    3);
		lua.SetGlobal("MAGIC_BEAN_PLATFORM_ARM64",  4);

#if defined(_M_IX86)
		lua.SetGlobal("MAGIC_BEAN_PLATFORM", 1);
#elif defined(_M_X64) || defined(_M_AMD64)
		lua.SetGlobal("MAGIC_BEAN_PLATFORM", 2);
#elif defined(_M_ARM)
		lua.SetGlobal("MAGIC_BEAN_PLATFORM", 3);
#elif defined(_M_ARM64)
		lua.SetGlobal("MAGIC_BEAN_PLATFORM", 4);
#endif

		lua_set_global(lua, MAGIC_BEAN_KEY_A);
		lua_set_global(lua, MAGIC_BEAN_KEY_B);
		lua_set_global(lua, MAGIC_BEAN_KEY_C);
		lua_set_global(lua, MAGIC_BEAN_KEY_D);
		lua_set_global(lua, MAGIC_BEAN_KEY_E);
		lua_set_global(lua, MAGIC_BEAN_KEY_F);
		lua_set_global(lua, MAGIC_BEAN_KEY_G);
		lua_set_global(lua, MAGIC_BEAN_KEY_H);
		lua_set_global(lua, MAGIC_BEAN_KEY_I);
		lua_set_global(lua, MAGIC_BEAN_KEY_J);
		lua_set_global(lua, MAGIC_BEAN_KEY_K);
		lua_set_global(lua, MAGIC_BEAN_KEY_L);
		lua_set_global(lua, MAGIC_BEAN_KEY_M);
		lua_set_global(lua, MAGIC_BEAN_KEY_N);
		lua_set_global(lua, MAGIC_BEAN_KEY_O);
		lua_set_global(lua, MAGIC_BEAN_KEY_P);
		lua_set_global(lua, MAGIC_BEAN_KEY_Q);
		lua_set_global(lua, MAGIC_BEAN_KEY_R);
		lua_set_global(lua, MAGIC_BEAN_KEY_S);
		lua_set_global(lua, MAGIC_BEAN_KEY_T);
		lua_set_global(lua, MAGIC_BEAN_KEY_U);
		lua_set_global(lua, MAGIC_BEAN_KEY_V);
		lua_set_global(lua, MAGIC_BEAN_KEY_W);
		lua_set_global(lua, MAGIC_BEAN_KEY_X);
		lua_set_global(lua, MAGIC_BEAN_KEY_Y);
		lua_set_global(lua, MAGIC_BEAN_KEY_Z);
		lua_set_global(lua, MAGIC_BEAN_KEY_NUM_0);
		lua_set_global(lua, MAGIC_BEAN_KEY_NUM_1);
		lua_set_global(lua, MAGIC_BEAN_KEY_NUM_2);
		lua_set_global(lua, MAGIC_BEAN_KEY_NUM_3);
		lua_set_global(lua, MAGIC_BEAN_KEY_NUM_4);
		lua_set_global(lua, MAGIC_BEAN_KEY_NUM_5);
		lua_set_global(lua, MAGIC_BEAN_KEY_NUM_6);
		lua_set_global(lua, MAGIC_BEAN_KEY_NUM_7);
		lua_set_global(lua, MAGIC_BEAN_KEY_NUM_8);
		lua_set_global(lua, MAGIC_BEAN_KEY_NUM_9);
		lua_set_global(lua, MAGIC_BEAN_KEY_NUMPAD_0);
		lua_set_global(lua, MAGIC_BEAN_KEY_NUMPAD_1);
		lua_set_global(lua, MAGIC_BEAN_KEY_NUMPAD_2);
		lua_set_global(lua, MAGIC_BEAN_KEY_NUMPAD_3);
		lua_set_global(lua, MAGIC_BEAN_KEY_NUMPAD_4);
		lua_set_global(lua, MAGIC_BEAN_KEY_NUMPAD_5);
		lua_set_global(lua, MAGIC_BEAN_KEY_NUMPAD_6);
		lua_set_global(lua, MAGIC_BEAN_KEY_NUMPAD_7);
		lua_set_global(lua, MAGIC_BEAN_KEY_NUMPAD_8);
		lua_set_global(lua, MAGIC_BEAN_KEY_NUMPAD_9);
		lua_set_global(lua, MAGIC_BEAN_KEY_F1);
		lua_set_global(lua, MAGIC_BEAN_KEY_F2);
		lua_set_global(lua, MAGIC_BEAN_KEY_F3);
		lua_set_global(lua, MAGIC_BEAN_KEY_F4);
		lua_set_global(lua, MAGIC_BEAN_KEY_F5);
		lua_set_global(lua, MAGIC_BEAN_KEY_F6);
		lua_set_global(lua, MAGIC_BEAN_KEY_F7);
		lua_set_global(lua, MAGIC_BEAN_KEY_F8);
		lua_set_global(lua, MAGIC_BEAN_KEY_F9);
		lua_set_global(lua, MAGIC_BEAN_KEY_F10);
		lua_set_global(lua, MAGIC_BEAN_KEY_F11);
		lua_set_global(lua, MAGIC_BEAN_KEY_F12);
		lua_set_global(lua, MAGIC_BEAN_KEY_TILDE);
		lua_set_global(lua, MAGIC_BEAN_KEY_ALT);
		lua_set_global(lua, MAGIC_BEAN_KEY_LALT);
		lua_set_global(lua, MAGIC_BEAN_KEY_RALT);
		lua_set_global(lua, MAGIC_BEAN_KEY_CLEAR);
		lua_set_global(lua, MAGIC_BEAN_KEY_DELETE);
		lua_set_global(lua, MAGIC_BEAN_KEY_ENTER);
		lua_set_global(lua, MAGIC_BEAN_KEY_ESCAPE);
		lua_set_global(lua, MAGIC_BEAN_KEY_BACKSPACE);
		lua_set_global(lua, MAGIC_BEAN_KEY_CONTROL);
		lua_set_global(lua, MAGIC_BEAN_KEY_LCONTROL);
		lua_set_global(lua, MAGIC_BEAN_KEY_RCONTROL);
		lua_set_global(lua, MAGIC_BEAN_KEY_SHIFT);
		lua_set_global(lua, MAGIC_BEAN_KEY_LSHIFT);
		lua_set_global(lua, MAGIC_BEAN_KEY_RSHIFT);
		lua_set_global(lua, MAGIC_BEAN_KEY_SPACEBAR);
		lua_set_global(lua, MAGIC_BEAN_KEY_TAB);
		lua_set_global(lua, MAGIC_BEAN_KEY_UP);
		lua_set_global(lua, MAGIC_BEAN_KEY_DOWN);
		lua_set_global(lua, MAGIC_BEAN_KEY_LEFT);
		lua_set_global(lua, MAGIC_BEAN_KEY_RIGHT);

		lua_set_global(lua, MAGIC_BEAN_BUTTON_X1);
		lua_set_global(lua, MAGIC_BEAN_BUTTON_X2);
		lua_set_global(lua, MAGIC_BEAN_BUTTON_LEFT);
		lua_set_global(lua, MAGIC_BEAN_BUTTON_RIGHT);
		lua_set_global(lua, MAGIC_BEAN_BUTTON_MIDDLE);

		lua_set_global(lua, MAGIC_BEAN_KEY_STATE_UP);
		lua_set_global(lua, MAGIC_BEAN_KEY_STATE_DOWN);

		lua_set_global(lua, MAGIC_BEAN_BUTTON_STATE_UP);
		lua_set_global(lua, MAGIC_BEAN_BUTTON_STATE_DOWN);

		lua_set_global(lua, MAGIC_BEAN_MEMORY_PROTECTION_NO_ACCESS);
		lua_set_global(lua, MAGIC_BEAN_MEMORY_PROTECTION_READ);
		lua_set_global(lua, MAGIC_BEAN_MEMORY_PROTECTION_READ_WRITE);
		lua_set_global(lua, MAGIC_BEAN_MEMORY_PROTECTION_WRITE_COPY);
		lua_set_global(lua, MAGIC_BEAN_MEMORY_PROTECTION_EXECUTE);
		lua_set_global(lua, MAGIC_BEAN_MEMORY_PROTECTION_EXECUTE_READ);
		lua_set_global(lua, MAGIC_BEAN_MEMORY_PROTECTION_EXECUTE_READ_WRITE);
		lua_set_global(lua, MAGIC_BEAN_MEMORY_PROTECTION_EXECUTE_WRITE_COPY);

		lua_set_global_function(lua, magic_bean_init);
		lua_set_global_function(lua, magic_bean_deinit);
		lua_set_global_function(lua, magic_bean_get_time_ms);
		lua_set_global_function(lua, magic_bean_get_time_us);
		lua_set_global_function(lua, magic_bean_get_timestamp);
		lua_set_global_function(lua, magic_bean_get_key_state);
		lua_set_global_function(lua, magic_bean_get_button_state);
		lua_set_global_function(lua, magic_bean_sleep);
		lua_set_global_function(lua, magic_bean_open_process_by_id);
		lua_set_global_function(lua, magic_bean_open_process_by_name);
		lua_set_global_function(lua, magic_bean_start_process);
		lua_set_global_function(lua, magic_bean_close_process);
		lua_set_global_function(lua, magic_bean_get_module_export);
		lua_set_global_function(lua, magic_bean_enumerate_processes);

		lua_set_global_function(lua, magic_bean_thread_is_running);
		lua_set_global_function(lua, magic_bean_thread_get_id);
		lua_set_global_function(lua, magic_bean_thread_resume);
		lua_set_global_function(lua, magic_bean_thread_suspend);
		lua_set_global_function(lua, magic_bean_thread_terminate);
		lua_set_global_function(lua, magic_bean_thread_join);

		lua_set_global_function(lua, magic_bean_window_is_focus);
		lua_set_global_function(lua, magic_bean_window_get_title);
		lua_set_global_function(lua, magic_bean_window_send_key);
		lua_set_global_function(lua, magic_bean_window_send_button);
		lua_set_global_function(lua, magic_bean_window_send_string);
		lua_set_global_function(lua, magic_bean_window_set_title);

		lua_set_global_function(lua, magic_bean_process_is_32_bit);
		lua_set_global_function(lua, magic_bean_process_is_running);
		lua_set_global_function(lua, magic_bean_process_get_file_version);
		lua_set_global_function(lua, magic_bean_process_open_thread_by_id);
		lua_set_global_function(lua, magic_bean_process_start_thread);
		lua_set_global_function(lua, magic_bean_process_close_thread);
		lua_set_global_function(lua, magic_bean_process_open_window_by_index);
		lua_set_global_function(lua, magic_bean_process_open_window_by_title);
		lua_set_global_function(lua, magic_bean_process_close_window);
		lua_set_global_function(lua, magic_bean_process_resume);
		lua_set_global_function(lua, magic_bean_process_suspend);
		lua_set_global_function(lua, magic_bean_process_enumerate_threads);
		lua_set_global_function(lua, magic_bean_process_enumerate_windows);

		lua_set_global_function(lua, magic_bean_process_memory_find);
		lua_set_global_function(lua, magic_bean_process_memory_read);
		lua_set_global_function(lua, magic_bean_process_memory_read_int8);
		lua_set_global_function(lua, magic_bean_process_memory_read_int16);
		lua_set_global_function(lua, magic_bean_process_memory_read_int32);
		lua_set_global_function(lua, magic_bean_process_memory_read_int64);
		lua_set_global_function(lua, magic_bean_process_memory_read_uint8);
		lua_set_global_function(lua, magic_bean_process_memory_read_uint16);
		lua_set_global_function(lua, magic_bean_process_memory_read_uint32);
		lua_set_global_function(lua, magic_bean_process_memory_read_uint64);
		lua_set_global_function(lua, magic_bean_process_memory_read_float);
		lua_set_global_function(lua, magic_bean_process_memory_read_double);
		lua_set_global_function(lua, magic_bean_process_memory_read_string);
		lua_set_global_function(lua, magic_bean_process_memory_read_string_ex);
		lua_set_global_function(lua, magic_bean_process_memory_write);
		lua_set_global_function(lua, magic_bean_process_memory_write_int8);
		lua_set_global_function(lua, magic_bean_process_memory_write_int16);
		lua_set_global_function(lua, magic_bean_process_memory_write_int32);
		lua_set_global_function(lua, magic_bean_process_memory_write_int64);
		lua_set_global_function(lua, magic_bean_process_memory_write_uint8);
		lua_set_global_function(lua, magic_bean_process_memory_write_uint16);
		lua_set_global_function(lua, magic_bean_process_memory_write_uint32);
		lua_set_global_function(lua, magic_bean_process_memory_write_uint64);
		lua_set_global_function(lua, magic_bean_process_memory_write_float);
		lua_set_global_function(lua, magic_bean_process_memory_write_double);
		lua_set_global_function(lua, magic_bean_process_memory_write_string);
		lua_set_global_function(lua, magic_bean_process_memory_allocate);
		lua_set_global_function(lua, magic_bean_process_memory_allocate_at);
		lua_set_global_function(lua, magic_bean_process_memory_release);
		lua_set_global_function(lua, magic_bean_process_memory_set_protection);

		lua_load_library(lua, LuaCPP::Libraries::All);

		for (int i = 1; i < argc; ++i)
			lua_run_file(lua, argv[i]);
	}

	return ERROR_CODE_NONE;
}
