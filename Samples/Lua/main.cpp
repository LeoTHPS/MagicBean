#include <AL/Common.hpp>

#include <AL/Lua543/Lua.hpp>

#include <AL/OS/Console.hpp>

#include <MagicBean/MagicBean.h>

typedef bool(*_magic_bean_process_enumerate_callback)(uint32_t id, const char* name);

bool _magic_bean_process_enumerate(MagicBean* magic, _magic_bean_process_enumerate_callback callback)
{
	magic_bean_process_enumerate_callback _callback = [](const MagicBeanProcessInformation* _lpInformation, void* _lpParam)
	{
		return (*reinterpret_cast<_magic_bean_process_enumerate_callback*>(_lpParam))(
			_lpInformation->ID,
			_lpInformation->Name
		);
	};

	return magic_bean_process_enumerate(magic, _callback, &callback);
}

int8_t _magic_bean_process_memory_read_int8(MagicBeanProcess* process, uint64_t address)
{
	int8_t value;
	return magic_bean_process_memory_read_int8(process, address, &value) ? value : 0;
}
int16_t _magic_bean_process_memory_read_int16(MagicBeanProcess* process, uint64_t address)
{
	int16_t value;
	return magic_bean_process_memory_read_int16(process, address, &value) ? value : 0;
}
int32_t _magic_bean_process_memory_read_int32(MagicBeanProcess* process, uint64_t address)
{
	int32_t value;
	return magic_bean_process_memory_read_int32(process, address, &value) ? value : 0;
}
int64_t _magic_bean_process_memory_read_int64(MagicBeanProcess* process, uint64_t address)
{
	int64_t value;
	return magic_bean_process_memory_read_int64(process, address, &value) ? value : 0;
}
uint8_t _magic_bean_process_memory_read_uint8(MagicBeanProcess* process, uint64_t address)
{
	uint8_t value;
	return magic_bean_process_memory_read_uint8(process, address, &value) ? value : 0;
}
uint16_t _magic_bean_process_memory_read_uint16(MagicBeanProcess* process, uint64_t address)
{
	uint16_t value;
	return magic_bean_process_memory_read_uint16(process, address, &value) ? value : 0;
}
uint32_t _magic_bean_process_memory_read_uint32(MagicBeanProcess* process, uint64_t address)
{
	uint32_t value;
	return magic_bean_process_memory_read_uint32(process, address, &value) ? value : 0;
}
uint64_t _magic_bean_process_memory_read_uint64(MagicBeanProcess* process, uint64_t address)
{
	uint64_t value;
	return magic_bean_process_memory_read_uint64(process, address, &value) ? value : 0;
}
float _magic_bean_process_memory_read_float(MagicBeanProcess* process, uint64_t address)
{
	float value;
	return magic_bean_process_memory_read_float(process, address, &value) ? value : 0;
}
double _magic_bean_process_memory_read_double(MagicBeanProcess* process, uint64_t address)
{
	double value;
	return magic_bean_process_memory_read_double(process, address, &value) ? value : 0;
}

// @throw AL::Exception
void lua_init(AL::Lua543::State& lua)
{
	#define lua_init_RegisterGlobal(__lua__, __func__)             lua.SetGlobalFunction<__func__>(#__func__)
	#define lua_init_RegisterGlobalAs(__lua__, __func__, __name__) lua.SetGlobalFunction<__func__>(__name__)

	lua.Create();

	luaL_openlibs(lua.GetHandle());

	lua_init_RegisterGlobal(lua, magic_bean_open);
	lua_init_RegisterGlobal(lua, magic_bean_close);

	lua_init_RegisterGlobal(lua, magic_bean_thread_enumerate);
	lua_init_RegisterGlobal(lua, magic_bean_thread_create);
	lua_init_RegisterGlobal(lua, magic_bean_thread_open_by_id);
	lua_init_RegisterGlobal(lua, magic_bean_thread_close);
	lua_init_RegisterGlobal(lua, magic_bean_thread_resume);
	lua_init_RegisterGlobal(lua, magic_bean_thread_suspend);
	lua_init_RegisterGlobal(lua, magic_bean_thread_terminate);
	lua_init_RegisterGlobal(lua, magic_bean_thread_get_exit_code);
	lua_init_RegisterGlobal(lua, magic_bean_thread_wait_for_exit);

	lua_init_RegisterGlobal(lua, magic_bean_window_enumerate);
	lua_init_RegisterGlobal(lua, magic_bean_window_open_by_name);
	lua_init_RegisterGlobal(lua, magic_bean_window_open_by_index);
	lua_init_RegisterGlobal(lua, magic_bean_window_close);

	lua_init_RegisterGlobalAs(lua, _magic_bean_process_enumerate, "magic_bean_process_enumerate");
	lua_init_RegisterGlobal(lua, magic_bean_process_open_by_id);
	lua_init_RegisterGlobal(lua, magic_bean_process_open_by_name);
	lua_init_RegisterGlobal(lua, magic_bean_process_close);
	lua_init_RegisterGlobal(lua, magic_bean_process_resume);
	lua_init_RegisterGlobal(lua, magic_bean_process_suspend);
	lua_init_RegisterGlobal(lua, magic_bean_process_set_debugger_present);
	lua_init_RegisterGlobal(lua, magic_bean_process_memory_read);
	lua_init_RegisterGlobalAs(lua, _magic_bean_process_memory_read_int8,   "magic_bean_process_memory_read_int8");
	lua_init_RegisterGlobalAs(lua, _magic_bean_process_memory_read_int16,  "magic_bean_process_memory_read_int16");
	lua_init_RegisterGlobalAs(lua, _magic_bean_process_memory_read_int32,  "magic_bean_process_memory_read_int32");
	lua_init_RegisterGlobalAs(lua, _magic_bean_process_memory_read_int64,  "magic_bean_process_memory_read_int64");
	lua_init_RegisterGlobalAs(lua, _magic_bean_process_memory_read_uint8,  "magic_bean_process_memory_read_uint8");
	lua_init_RegisterGlobalAs(lua, _magic_bean_process_memory_read_uint16, "magic_bean_process_memory_read_uint16");
	lua_init_RegisterGlobalAs(lua, _magic_bean_process_memory_read_uint32, "magic_bean_process_memory_read_uint32");
	lua_init_RegisterGlobalAs(lua, _magic_bean_process_memory_read_uint64, "magic_bean_process_memory_read_uint64");
	lua_init_RegisterGlobalAs(lua, _magic_bean_process_memory_read_float,  "magic_bean_process_memory_read_float");
	lua_init_RegisterGlobalAs(lua, _magic_bean_process_memory_read_double, "magic_bean_process_memory_read_double");
	lua_init_RegisterGlobal(lua, magic_bean_process_memory_write);
	lua_init_RegisterGlobal(lua, magic_bean_process_memory_write_int8);
	lua_init_RegisterGlobal(lua, magic_bean_process_memory_write_int16);
	lua_init_RegisterGlobal(lua, magic_bean_process_memory_write_int32);
	lua_init_RegisterGlobal(lua, magic_bean_process_memory_write_int64);
	lua_init_RegisterGlobal(lua, magic_bean_process_memory_write_uint8);
	lua_init_RegisterGlobal(lua, magic_bean_process_memory_write_uint16);
	lua_init_RegisterGlobal(lua, magic_bean_process_memory_write_uint32);
	lua_init_RegisterGlobal(lua, magic_bean_process_memory_write_uint64);
	lua_init_RegisterGlobal(lua, magic_bean_process_memory_write_float);
	lua_init_RegisterGlobal(lua, magic_bean_process_memory_write_double);
	lua_init_RegisterGlobal(lua, magic_bean_process_memory_find);
	lua_init_RegisterGlobal(lua, magic_bean_process_memory_find_at);
	lua_init_RegisterGlobal(lua, magic_bean_process_memory_allocate);
	lua_init_RegisterGlobal(lua, magic_bean_process_memory_release);
	lua_init_RegisterGlobal(lua, magic_bean_process_library_open);
	lua_init_RegisterGlobal(lua, magic_bean_process_library_close);
	lua_init_RegisterGlobal(lua, magic_bean_process_library_load_file);
	lua_init_RegisterGlobal(lua, magic_bean_process_library_load_buffer);
	lua_init_RegisterGlobal(lua, magic_bean_process_library_load_memory);
	lua_init_RegisterGlobal(lua, magic_bean_process_library_unload);
	lua_init_RegisterGlobal(lua, magic_bean_process_library_get_export);
}

// @throw AL::Exception
void lua_run(AL::Lua543::State& lua, int argc, char* argv[])
{
	AL::OS::Console::WriteLine(
		LUA_COPYRIGHT
	);

	for (int i = 1; i < argc; ++i)
	{
		AL::FileSystem::Path path(
			argv[i]
		);

		lua.RunFile(
			path
		);
	}
}

int main(int argc, char* argv[])
{
	AL::Lua543::State lua;

	try
	{
		lua_init(
			lua
		);

		lua_run(
			lua,
			argc,
			argv
		);
	}
	catch (const AL::Exception& exception)
	{
		AL::OS::Console::WriteException(
			exception
		);
	}

	return 0;
}
