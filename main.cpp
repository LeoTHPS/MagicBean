#include "MagicBean.hpp"

#undef LoadLibrary

#include <iostream>

#include <LuaCPP.hpp>

#define lua_register_global(lua, value)          lua_register_global_ex(lua, #value, value)
#define lua_register_global_ex(lua, name, value) lua.SetGlobal<value>(name)

void lua_register_globals(LuaCPP& lua)
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

	lua_register_global(lua, MAGIC_BEAN_KEY_A);
	lua_register_global(lua, MAGIC_BEAN_KEY_B);
	lua_register_global(lua, MAGIC_BEAN_KEY_C);
	lua_register_global(lua, MAGIC_BEAN_KEY_D);
	lua_register_global(lua, MAGIC_BEAN_KEY_E);
	lua_register_global(lua, MAGIC_BEAN_KEY_F);
	lua_register_global(lua, MAGIC_BEAN_KEY_G);
	lua_register_global(lua, MAGIC_BEAN_KEY_H);
	lua_register_global(lua, MAGIC_BEAN_KEY_I);
	lua_register_global(lua, MAGIC_BEAN_KEY_J);
	lua_register_global(lua, MAGIC_BEAN_KEY_K);
	lua_register_global(lua, MAGIC_BEAN_KEY_L);
	lua_register_global(lua, MAGIC_BEAN_KEY_M);
	lua_register_global(lua, MAGIC_BEAN_KEY_N);
	lua_register_global(lua, MAGIC_BEAN_KEY_O);
	lua_register_global(lua, MAGIC_BEAN_KEY_P);
	lua_register_global(lua, MAGIC_BEAN_KEY_Q);
	lua_register_global(lua, MAGIC_BEAN_KEY_R);
	lua_register_global(lua, MAGIC_BEAN_KEY_S);
	lua_register_global(lua, MAGIC_BEAN_KEY_T);
	lua_register_global(lua, MAGIC_BEAN_KEY_U);
	lua_register_global(lua, MAGIC_BEAN_KEY_V);
	lua_register_global(lua, MAGIC_BEAN_KEY_W);
	lua_register_global(lua, MAGIC_BEAN_KEY_X);
	lua_register_global(lua, MAGIC_BEAN_KEY_Y);
	lua_register_global(lua, MAGIC_BEAN_KEY_Z);
	lua_register_global(lua, MAGIC_BEAN_KEY_NUM_0);
	lua_register_global(lua, MAGIC_BEAN_KEY_NUM_1);
	lua_register_global(lua, MAGIC_BEAN_KEY_NUM_2);
	lua_register_global(lua, MAGIC_BEAN_KEY_NUM_3);
	lua_register_global(lua, MAGIC_BEAN_KEY_NUM_4);
	lua_register_global(lua, MAGIC_BEAN_KEY_NUM_5);
	lua_register_global(lua, MAGIC_BEAN_KEY_NUM_6);
	lua_register_global(lua, MAGIC_BEAN_KEY_NUM_7);
	lua_register_global(lua, MAGIC_BEAN_KEY_NUM_8);
	lua_register_global(lua, MAGIC_BEAN_KEY_NUM_9);
	lua_register_global(lua, MAGIC_BEAN_KEY_NUMPAD_0);
	lua_register_global(lua, MAGIC_BEAN_KEY_NUMPAD_1);
	lua_register_global(lua, MAGIC_BEAN_KEY_NUMPAD_2);
	lua_register_global(lua, MAGIC_BEAN_KEY_NUMPAD_3);
	lua_register_global(lua, MAGIC_BEAN_KEY_NUMPAD_4);
	lua_register_global(lua, MAGIC_BEAN_KEY_NUMPAD_5);
	lua_register_global(lua, MAGIC_BEAN_KEY_NUMPAD_6);
	lua_register_global(lua, MAGIC_BEAN_KEY_NUMPAD_7);
	lua_register_global(lua, MAGIC_BEAN_KEY_NUMPAD_8);
	lua_register_global(lua, MAGIC_BEAN_KEY_NUMPAD_9);
	lua_register_global(lua, MAGIC_BEAN_KEY_F1);
	lua_register_global(lua, MAGIC_BEAN_KEY_F2);
	lua_register_global(lua, MAGIC_BEAN_KEY_F3);
	lua_register_global(lua, MAGIC_BEAN_KEY_F4);
	lua_register_global(lua, MAGIC_BEAN_KEY_F5);
	lua_register_global(lua, MAGIC_BEAN_KEY_F6);
	lua_register_global(lua, MAGIC_BEAN_KEY_F7);
	lua_register_global(lua, MAGIC_BEAN_KEY_F8);
	lua_register_global(lua, MAGIC_BEAN_KEY_F9);
	lua_register_global(lua, MAGIC_BEAN_KEY_F10);
	lua_register_global(lua, MAGIC_BEAN_KEY_F11);
	lua_register_global(lua, MAGIC_BEAN_KEY_F12);
	lua_register_global(lua, MAGIC_BEAN_KEY_TILDE);
	lua_register_global(lua, MAGIC_BEAN_KEY_ALT);
	lua_register_global(lua, MAGIC_BEAN_KEY_LALT);
	lua_register_global(lua, MAGIC_BEAN_KEY_RALT);
	lua_register_global(lua, MAGIC_BEAN_KEY_CLEAR);
	lua_register_global(lua, MAGIC_BEAN_KEY_DELETE);
	lua_register_global(lua, MAGIC_BEAN_KEY_ENTER);
	lua_register_global(lua, MAGIC_BEAN_KEY_ESCAPE);
	lua_register_global(lua, MAGIC_BEAN_KEY_BACKSPACE);
	lua_register_global(lua, MAGIC_BEAN_KEY_CONTROL);
	lua_register_global(lua, MAGIC_BEAN_KEY_LCONTROL);
	lua_register_global(lua, MAGIC_BEAN_KEY_RCONTROL);
	lua_register_global(lua, MAGIC_BEAN_KEY_SHIFT);
	lua_register_global(lua, MAGIC_BEAN_KEY_LSHIFT);
	lua_register_global(lua, MAGIC_BEAN_KEY_RSHIFT);
	lua_register_global(lua, MAGIC_BEAN_KEY_SPACEBAR);
	lua_register_global(lua, MAGIC_BEAN_KEY_TAB);
	lua_register_global(lua, MAGIC_BEAN_KEY_UP);
	lua_register_global(lua, MAGIC_BEAN_KEY_DOWN);
	lua_register_global(lua, MAGIC_BEAN_KEY_LEFT);
	lua_register_global(lua, MAGIC_BEAN_KEY_RIGHT);

	lua_register_global(lua, MAGIC_BEAN_BUTTON_X1);
	lua_register_global(lua, MAGIC_BEAN_BUTTON_X2);
	lua_register_global(lua, MAGIC_BEAN_BUTTON_LEFT);
	lua_register_global(lua, MAGIC_BEAN_BUTTON_RIGHT);
	lua_register_global(lua, MAGIC_BEAN_BUTTON_MIDDLE);

	lua_register_global(lua, MAGIC_BEAN_KEY_STATE_UP);
	lua_register_global(lua, MAGIC_BEAN_KEY_STATE_DOWN);

	lua_register_global(lua, MAGIC_BEAN_BUTTON_STATE_UP);
	lua_register_global(lua, MAGIC_BEAN_BUTTON_STATE_DOWN);

	lua_register_global(lua, MAGIC_BEAN_MEMORY_PROTECTION_NO_ACCESS);
	lua_register_global(lua, MAGIC_BEAN_MEMORY_PROTECTION_READ);
	lua_register_global(lua, MAGIC_BEAN_MEMORY_PROTECTION_READ_WRITE);
	lua_register_global(lua, MAGIC_BEAN_MEMORY_PROTECTION_WRITE_COPY);
	lua_register_global(lua, MAGIC_BEAN_MEMORY_PROTECTION_EXECUTE);
	lua_register_global(lua, MAGIC_BEAN_MEMORY_PROTECTION_EXECUTE_READ);
	lua_register_global(lua, MAGIC_BEAN_MEMORY_PROTECTION_EXECUTE_READ_WRITE);
	lua_register_global(lua, MAGIC_BEAN_MEMORY_PROTECTION_EXECUTE_WRITE_COPY);

	lua_register_global(lua, magic_bean_init);
	lua_register_global(lua, magic_bean_deinit);
	lua_register_global(lua, magic_bean_get_time_ms);
	lua_register_global(lua, magic_bean_get_time_us);
	lua_register_global(lua, magic_bean_get_timestamp);
	lua_register_global(lua, magic_bean_get_key_state);
	lua_register_global(lua, magic_bean_get_button_state);
	lua_register_global(lua, magic_bean_sleep);
	lua_register_global(lua, magic_bean_open_process_by_id);
	lua_register_global(lua, magic_bean_open_process_by_name);
	lua_register_global(lua, magic_bean_start_process);
	lua_register_global(lua, magic_bean_close_process);
	lua_register_global(lua, magic_bean_get_module_export);
	lua_register_global(lua, magic_bean_enumerate_processes);

	lua_register_global(lua, magic_bean_thread_is_running);
	lua_register_global(lua, magic_bean_thread_get_id);
	lua_register_global(lua, magic_bean_thread_resume);
	lua_register_global(lua, magic_bean_thread_suspend);
	lua_register_global(lua, magic_bean_thread_terminate);
	lua_register_global(lua, magic_bean_thread_join);

	lua_register_global(lua, magic_bean_window_is_focus);
	lua_register_global(lua, magic_bean_window_get_title);
	lua_register_global(lua, magic_bean_window_send_key);
	lua_register_global(lua, magic_bean_window_send_button);
	lua_register_global(lua, magic_bean_window_send_string);
	lua_register_global(lua, magic_bean_window_set_title);

	lua_register_global(lua, magic_bean_process_is_32_bit);
	lua_register_global(lua, magic_bean_process_is_running);
	lua_register_global(lua, magic_bean_process_get_file_version);
	lua_register_global(lua, magic_bean_process_open_thread_by_id);
	lua_register_global(lua, magic_bean_process_start_thread);
	lua_register_global(lua, magic_bean_process_close_thread);
	lua_register_global(lua, magic_bean_process_open_window_by_index);
	lua_register_global(lua, magic_bean_process_open_window_by_title);
	lua_register_global(lua, magic_bean_process_close_window);
	lua_register_global(lua, magic_bean_process_resume);
	lua_register_global(lua, magic_bean_process_suspend);
	lua_register_global(lua, magic_bean_process_enumerate_threads);
	lua_register_global(lua, magic_bean_process_enumerate_windows);

	lua_register_global(lua, magic_bean_process_memory_find);
	lua_register_global(lua, magic_bean_process_memory_read);
	lua_register_global(lua, magic_bean_process_memory_read_int8);
	lua_register_global(lua, magic_bean_process_memory_read_int16);
	lua_register_global(lua, magic_bean_process_memory_read_int32);
	lua_register_global(lua, magic_bean_process_memory_read_int64);
	lua_register_global(lua, magic_bean_process_memory_read_uint8);
	lua_register_global(lua, magic_bean_process_memory_read_uint16);
	lua_register_global(lua, magic_bean_process_memory_read_uint32);
	lua_register_global(lua, magic_bean_process_memory_read_uint64);
	lua_register_global(lua, magic_bean_process_memory_read_float);
	lua_register_global(lua, magic_bean_process_memory_read_double);
	lua_register_global(lua, magic_bean_process_memory_read_string);
	lua_register_global(lua, magic_bean_process_memory_read_string_ex);
	lua_register_global(lua, magic_bean_process_memory_write);
	lua_register_global(lua, magic_bean_process_memory_write_int8);
	lua_register_global(lua, magic_bean_process_memory_write_int16);
	lua_register_global(lua, magic_bean_process_memory_write_int32);
	lua_register_global(lua, magic_bean_process_memory_write_int64);
	lua_register_global(lua, magic_bean_process_memory_write_uint8);
	lua_register_global(lua, magic_bean_process_memory_write_uint16);
	lua_register_global(lua, magic_bean_process_memory_write_uint32);
	lua_register_global(lua, magic_bean_process_memory_write_uint64);
	lua_register_global(lua, magic_bean_process_memory_write_float);
	lua_register_global(lua, magic_bean_process_memory_write_double);
	lua_register_global(lua, magic_bean_process_memory_write_string);
	lua_register_global(lua, magic_bean_process_memory_allocate);
	lua_register_global(lua, magic_bean_process_memory_allocate_at);
	lua_register_global(lua, magic_bean_process_memory_release);
	lua_register_global(lua, magic_bean_process_memory_set_protection);
}

bool main_execute_files(LuaCPP& lua, int argc, char* argv[])
{
	for (int i = 1; i < argc; ++i)
		try
		{
			if (!lua.RunFile(argv[i]))
			{
				std::cerr << "File not found: " << argv[i] << std::endl;

				return false;
			}
		}
		catch (const std::exception& e)
		{
			std::cerr << "Error running file: " << argv[i] << std::endl;
			std::cerr << e.what() << std::endl;

			return false;
		}

	return true;
}
bool main_execute_stdin(LuaCPP& lua)
{
	std::cout << "Magic Bean" << std::endl;
	std::cout << LUA_COPYRIGHT << std::endl;

	std::string line;
	auto        get_next_line = [&line]()->bool
	{
		std::cout << "> ";

		// TODO: why is .operator bool() needed?
		return std::getline(std::cin, line).operator bool();
	};

	while (get_next_line())
	{
		try
		{
			lua.Run(line);
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << std::endl;

			return false;
		}
	}

	return true;
}

int main(int argc, char* argv[])
{
	if (auto lua = LuaCPP())
	{
		lua.LoadLibrary(LuaCPP::Libraries::All);

		lua_register_globals(lua);

		if (argc <= 1)
			main_execute_stdin(lua);
		else
			main_execute_files(lua, argc, argv);
	}

	return 0;
}
