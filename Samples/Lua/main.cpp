#include <AL/Common.hpp>

#include <AL/Lua543/Lua.hpp>

#include <AL/OS/Console.hpp>

#include <MagicBean/MagicBean.h>

typedef bool(_magic_bean_process_enumerate_callback)(uint32_t id, const char* name);
typedef AL::Lua543::Function::LuaCallback<_magic_bean_process_enumerate_callback> _magic_bean_process_enumerate_callback_lua;

typedef bool(_magic_bean_window_enumerate_callback)(uint32_t index, const char* name);
typedef AL::Lua543::Function::LuaCallback<_magic_bean_window_enumerate_callback>  _magic_bean_window_enumerate_callback_lua;

typedef bool(_magic_bean_thread_enumerate_callback)(uint32_t id);
typedef AL::Lua543::Function::LuaCallback<_magic_bean_thread_enumerate_callback>  _magic_bean_thread_enumerate_callback_lua;

bool     _magic_bean_is_null(void* lpUserData)
{
	return lpUserData == nullptr;
}
bool     _magic_bean_is_not_null(void* lpUserData)
{
	return lpUserData != nullptr;
}
uint64_t _magic_bean_to_number(void* lpUserData)
{
	return reinterpret_cast<uint64_t>(lpUserData);
}

bool     _magic_bean_thread_enumerate(MagicBeanProcess* process, _magic_bean_thread_enumerate_callback_lua callback)
{
	magic_bean_thread_enumerate_callback _callback = [](const MagicBeanThreadInformation* _lpInformation, void* _lpParam)
	{
		return (*reinterpret_cast<const _magic_bean_thread_enumerate_callback_lua*>(_lpParam))(
			_lpInformation->ID
		);
	};

	return magic_bean_thread_enumerate(process, _callback, &callback);
}

bool     _magic_bean_window_enumerate(MagicBeanProcess* process, _magic_bean_process_enumerate_callback_lua callback)
{
	magic_bean_window_enumerate_callback _callback = [](const MagicBeanWindowInformation* _lpInformation, void* _lpParam)
	{
		return (*reinterpret_cast<const _magic_bean_window_enumerate_callback_lua*>(_lpParam))(
			static_cast<uint32_t>(_lpInformation->Index),
			_lpInformation->Name
		);
	};

	return magic_bean_window_enumerate(process, _callback, &callback);
}

bool     _magic_bean_process_enumerate(MagicBean* magic, _magic_bean_process_enumerate_callback_lua callback)
{
	magic_bean_process_enumerate_callback _callback = [](const MagicBeanProcessInformation* _lpInformation, void* _lpParam)
	{
		return (*reinterpret_cast<const _magic_bean_process_enumerate_callback_lua*>(_lpParam))(
			_lpInformation->ID,
			_lpInformation->Name
		);
	};

	return magic_bean_process_enumerate(magic, _callback, &callback);
}

AL::Collections::Tuple<bool, int8_t>        _magic_bean_process_memory_read_int8(MagicBeanProcess* process, uint64_t address)
{
	AL::Collections::Tuple<bool, int8_t> result;
	result.Set<0>(magic_bean_process_memory_read_int8(process, address, &result.Get<1>()));

	return result;
}
AL::Collections::Tuple<bool, int16_t>       _magic_bean_process_memory_read_int16(MagicBeanProcess* process, uint64_t address)
{
	AL::Collections::Tuple<bool, int16_t> result;
	result.Set<0>(magic_bean_process_memory_read_int16(process, address, &result.Get<1>()));

	return result;
}
AL::Collections::Tuple<bool, int32_t>       _magic_bean_process_memory_read_int32(MagicBeanProcess* process, uint64_t address)
{
	AL::Collections::Tuple<bool, int32_t> result;
	result.Set<0>(magic_bean_process_memory_read_int32(process, address, &result.Get<1>()));

	return result;
}
AL::Collections::Tuple<bool, int64_t>       _magic_bean_process_memory_read_int64(MagicBeanProcess* process, uint64_t address)
{
	AL::Collections::Tuple<bool, int64_t> result;
	result.Set<0>(magic_bean_process_memory_read_int64(process, address, &result.Get<1>()));

	return result;
}
AL::Collections::Tuple<bool, uint8_t>       _magic_bean_process_memory_read_uint8(MagicBeanProcess* process, uint64_t address)
{
	AL::Collections::Tuple<bool, uint8_t> result;
	result.Set<0>(magic_bean_process_memory_read_uint8(process, address, &result.Get<1>()));

	return result;
}
AL::Collections::Tuple<bool, uint16_t>      _magic_bean_process_memory_read_uint16(MagicBeanProcess* process, uint64_t address)
{
	AL::Collections::Tuple<bool, uint16_t> result;
	result.Set<0>(magic_bean_process_memory_read_uint16(process, address, &result.Get<1>()));

	return result;
}
AL::Collections::Tuple<bool, uint32_t>      _magic_bean_process_memory_read_uint32(MagicBeanProcess* process, uint64_t address)
{
	AL::Collections::Tuple<bool, uint32_t> result;
	result.Set<0>(magic_bean_process_memory_read_uint32(process, address, &result.Get<1>()));

	return result;
}
AL::Collections::Tuple<bool, uint64_t>      _magic_bean_process_memory_read_uint64(MagicBeanProcess* process, uint64_t address)
{
	AL::Collections::Tuple<bool, uint64_t> result;
	result.Set<0>(magic_bean_process_memory_read_uint64(process, address, &result.Get<1>()));

	return result;
}
AL::Collections::Tuple<bool, float>         _magic_bean_process_memory_read_float(MagicBeanProcess* process, uint64_t address)
{
	AL::Collections::Tuple<bool, float> result;
	result.Set<0>(magic_bean_process_memory_read_float(process, address, &result.Get<1>()));

	return result;
}
AL::Collections::Tuple<bool, double>        _magic_bean_process_memory_read_double(MagicBeanProcess* process, uint64_t address)
{
	AL::Collections::Tuple<bool, double> result;
	result.Set<0>(magic_bean_process_memory_read_double(process, address, &result.Get<1>()));

	return result;
}
AL::Collections::Tuple<ssize_t, AL::String> _magic_bean_process_memory_read_string(MagicBeanProcess* process, uint64_t address, size_t maxLength)
{
	AL::Collections::Array<AL::String::Char> buffer(maxLength);
	ssize_t                                  bufferSize;

	if ((bufferSize = magic_bean_process_memory_read_string(process, address, &buffer[0], maxLength)) == -1)
	{

		bufferSize = 0;
	}

	return AL::Collections::Tuple<ssize_t, AL::String>(
		AL::Move(bufferSize),
		AL::String(
			&buffer[0],
			static_cast<size_t>(bufferSize)
		)
	);
}

// @throw AL::Exception
void lua_init(AL::Lua543::State& lua)
{
	#define lua_init_RegisterGlobal(__lua__, __value__)                    lua.SetGlobal(#__value__, __value__)
	#define lua_init_RegisterGlobalAs(__lua__, __value__, __name__)        lua.SetGlobal(__name__, __value__)
	#define lua_init_RegisterGlobalFunction(__lua__, __func__)             lua.SetGlobalFunction<__func__>(#__func__)
	#define lua_init_RegisterGlobalFunctionAs(__lua__, __func__, __name__) lua.SetGlobalFunction<__func__>(__name__)

	lua.Create();

	luaL_openlibs(lua.GetHandle());

	lua_init_RegisterGlobal(lua, MAGIC_BEAN_PROCESS_MEMORY_PROTECTION_TYPE_NONE);
	lua_init_RegisterGlobal(lua, MAGIC_BEAN_PROCESS_MEMORY_PROTECTION_TYPE_READ);
	lua_init_RegisterGlobal(lua, MAGIC_BEAN_PROCESS_MEMORY_PROTECTION_TYPE_READ_WRITE);
	lua_init_RegisterGlobal(lua, MAGIC_BEAN_PROCESS_MEMORY_PROTECTION_TYPE_EXECUTE);
	lua_init_RegisterGlobal(lua, MAGIC_BEAN_PROCESS_MEMORY_PROTECTION_TYPE_EXECUTE_READ);
	lua_init_RegisterGlobal(lua, MAGIC_BEAN_PROCESS_MEMORY_PROTECTION_TYPE_EXECUTE_READ_WRITE);

	lua_init_RegisterGlobalFunction(lua, magic_bean_open);
	lua_init_RegisterGlobalFunction(lua, magic_bean_close);
	lua_init_RegisterGlobalFunction(lua, magic_bean_get_time_ms);
	lua_init_RegisterGlobalFunction(lua, magic_bean_get_time_us);
	lua_init_RegisterGlobalFunction(lua, magic_bean_get_timestamp);
	lua_init_RegisterGlobalFunction(lua, magic_bean_get_current_thread_id);
	lua_init_RegisterGlobalFunction(lua, magic_bean_get_current_process_id);
	lua_init_RegisterGlobalFunctionAs(lua, _magic_bean_is_null, "magic_bean_is_null");
	lua_init_RegisterGlobalFunctionAs(lua, _magic_bean_is_not_null, "magic_bean_is_not_null");
	lua_init_RegisterGlobalFunctionAs(lua, _magic_bean_to_number, "magic_bean_to_number");

	lua_init_RegisterGlobalFunctionAs(lua, _magic_bean_thread_enumerate, "magic_bean_thread_enumerate");
	lua_init_RegisterGlobalFunction(lua, magic_bean_thread_create);
	lua_init_RegisterGlobalFunction(lua, magic_bean_thread_open_by_id);
	lua_init_RegisterGlobalFunction(lua, magic_bean_thread_close);
	lua_init_RegisterGlobalFunction(lua, magic_bean_thread_resume);
	lua_init_RegisterGlobalFunction(lua, magic_bean_thread_suspend);
	lua_init_RegisterGlobalFunction(lua, magic_bean_thread_terminate);
	// lua_init_RegisterGlobalFunction(lua, magic_bean_thread_get_exit_code);
	// lua_init_RegisterGlobalFunction(lua, magic_bean_thread_wait_for_exit);

	lua_init_RegisterGlobalFunctionAs(lua, _magic_bean_window_enumerate, "magic_bean_window_enumerate");
	lua_init_RegisterGlobalFunction(lua, magic_bean_window_open_by_name);
	lua_init_RegisterGlobalFunction(lua, magic_bean_window_open_by_index);
	lua_init_RegisterGlobalFunction(lua, magic_bean_window_close);
	lua_init_RegisterGlobalFunction(lua, magic_bean_window_get_name);
	lua_init_RegisterGlobalFunction(lua, magic_bean_window_set_name);

	lua_init_RegisterGlobalFunctionAs(lua, _magic_bean_process_enumerate, "magic_bean_process_enumerate");
	lua_init_RegisterGlobalFunction(lua, magic_bean_process_open_by_id);
	lua_init_RegisterGlobalFunction(lua, magic_bean_process_open_by_name);
	lua_init_RegisterGlobalFunction(lua, magic_bean_process_close);
	lua_init_RegisterGlobalFunction(lua, magic_bean_process_resume);
	lua_init_RegisterGlobalFunction(lua, magic_bean_process_suspend);
	lua_init_RegisterGlobalFunction(lua, magic_bean_process_set_debugger_present);
	// lua_init_RegisterGlobalFunction(lua, magic_bean_process_memory_read);
	lua_init_RegisterGlobalFunctionAs(lua, _magic_bean_process_memory_read_int8,   "magic_bean_process_memory_read_int8");
	lua_init_RegisterGlobalFunctionAs(lua, _magic_bean_process_memory_read_int16,  "magic_bean_process_memory_read_int16");
	lua_init_RegisterGlobalFunctionAs(lua, _magic_bean_process_memory_read_int32,  "magic_bean_process_memory_read_int32");
	lua_init_RegisterGlobalFunctionAs(lua, _magic_bean_process_memory_read_int64,  "magic_bean_process_memory_read_int64");
	lua_init_RegisterGlobalFunctionAs(lua, _magic_bean_process_memory_read_uint8,  "magic_bean_process_memory_read_uint8");
	lua_init_RegisterGlobalFunctionAs(lua, _magic_bean_process_memory_read_uint16, "magic_bean_process_memory_read_uint16");
	lua_init_RegisterGlobalFunctionAs(lua, _magic_bean_process_memory_read_uint32, "magic_bean_process_memory_read_uint32");
	lua_init_RegisterGlobalFunctionAs(lua, _magic_bean_process_memory_read_uint64, "magic_bean_process_memory_read_uint64");
	lua_init_RegisterGlobalFunctionAs(lua, _magic_bean_process_memory_read_float,  "magic_bean_process_memory_read_float");
	lua_init_RegisterGlobalFunctionAs(lua, _magic_bean_process_memory_read_double, "magic_bean_process_memory_read_double");
	lua_init_RegisterGlobalFunctionAs(lua, _magic_bean_process_memory_read_string, "magic_bean_process_memory_read_string");
	// lua_init_RegisterGlobalFunction(lua, magic_bean_process_memory_write);
	lua_init_RegisterGlobalFunction(lua, magic_bean_process_memory_write_int8);
	lua_init_RegisterGlobalFunction(lua, magic_bean_process_memory_write_int16);
	lua_init_RegisterGlobalFunction(lua, magic_bean_process_memory_write_int32);
	lua_init_RegisterGlobalFunction(lua, magic_bean_process_memory_write_int64);
	lua_init_RegisterGlobalFunction(lua, magic_bean_process_memory_write_uint8);
	lua_init_RegisterGlobalFunction(lua, magic_bean_process_memory_write_uint16);
	lua_init_RegisterGlobalFunction(lua, magic_bean_process_memory_write_uint32);
	lua_init_RegisterGlobalFunction(lua, magic_bean_process_memory_write_uint64);
	lua_init_RegisterGlobalFunction(lua, magic_bean_process_memory_write_float);
	lua_init_RegisterGlobalFunction(lua, magic_bean_process_memory_write_double);
	lua_init_RegisterGlobalFunction(lua, magic_bean_process_memory_write_string);
	// lua_init_RegisterGlobalFunction(lua, magic_bean_process_memory_find);
	// lua_init_RegisterGlobalFunction(lua, magic_bean_process_memory_find_at);
	lua_init_RegisterGlobalFunction(lua, magic_bean_process_memory_allocate);
	lua_init_RegisterGlobalFunction(lua, magic_bean_process_memory_release);
	lua_init_RegisterGlobalFunction(lua, magic_bean_process_library_open);
	lua_init_RegisterGlobalFunction(lua, magic_bean_process_library_close);
	lua_init_RegisterGlobalFunction(lua, magic_bean_process_library_load_file);
	lua_init_RegisterGlobalFunction(lua, magic_bean_process_library_load_buffer);
	lua_init_RegisterGlobalFunction(lua, magic_bean_process_library_load_memory);
	lua_init_RegisterGlobalFunction(lua, magic_bean_process_library_unload);
	lua_init_RegisterGlobalFunction(lua, magic_bean_process_library_get_export);
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
