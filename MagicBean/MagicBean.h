#ifndef _MAGIC_BEAN_H
#define _MAGIC_BEAN_H

#include <stdint.h>
#include <stdbool.h>

#if defined(__cplusplus)
extern "C" {
#endif

#if defined(MAGIC_BEAN_API)
	#if defined(WIN32) || defined(_WIN32)
		#define MAGIC_BEAN_EXPORT __declspec(dllexport)
	#else
		#define MAGIC_BEAN_EXPORT
	#endif
#else
	#if defined(WIN32) || defined(_WIN32)
		#define MAGIC_BEAN_EXPORT __declspec(dllimport)
	#else
		#define MAGIC_BEAN_EXPORT
	#endif
#endif

typedef struct _MagicBean        MagicBean;
typedef struct _MagicBeanThread  MagicBeanThread;
typedef struct _MagicBeanWindow  MagicBeanWindow;
typedef struct _MagicBeanLibrary MagicBeanLibrary;
typedef struct _MagicBeanProcess MagicBeanProcess;

typedef struct _MagicBeanThreadInformation
{
	uint32_t ID;
} MagicBeanThreadInformation;

typedef struct _MagicBeanWindowInformation
{
	const char* Name;
	size_t      Index;
} MagicBeanWindowInformation;

typedef struct _MagicBeanProcessInformation
{
	uint32_t    ID;
	const char* Name;
} MagicBeanProcessInformation;

typedef enum _MAGIC_BEAN_PROCESS_MEMORY_PROTECTION_TYPES : uint8_t
{
	MAGIC_BEAN_PROCESS_MEMORY_PROTECTION_TYPE_NONE,

	MAGIC_BEAN_PROCESS_MEMORY_PROTECTION_TYPE_READ,
	MAGIC_BEAN_PROCESS_MEMORY_PROTECTION_TYPE_READ_WRITE,

	MAGIC_BEAN_PROCESS_MEMORY_PROTECTION_TYPE_EXECUTE,
	MAGIC_BEAN_PROCESS_MEMORY_PROTECTION_TYPE_EXECUTE_READ,
	MAGIC_BEAN_PROCESS_MEMORY_PROTECTION_TYPE_EXECUTE_READ_WRITE
} MAGIC_BEAN_PROCESS_MEMORY_PROTECTION_TYPES;

// @return false to stop
typedef bool(*magic_bean_thread_enumerate_callback)(const MagicBeanThreadInformation* lpInformation, void* lpParam);
// @return false to stop
typedef bool(*magic_bean_window_enumerate_callback)(const MagicBeanWindowInformation* lpInformation, void* lpParam);
// @return false to stop
typedef bool(*magic_bean_process_enumerate_callback)(const MagicBeanProcessInformation* lpInformation, void* lpParam);

MAGIC_BEAN_EXPORT MagicBean*        magic_bean_open();
MAGIC_BEAN_EXPORT void              magic_bean_close(MagicBean* magic);

MAGIC_BEAN_EXPORT bool              magic_bean_thread_enumerate(MagicBeanProcess* process, magic_bean_thread_enumerate_callback callback, void* lpParam);
MAGIC_BEAN_EXPORT MagicBeanThread*  magic_bean_thread_create(MagicBeanProcess* process, uint64_t address, uint64_t lpParam);
MAGIC_BEAN_EXPORT MagicBeanThread*  magic_bean_thread_open_by_id(MagicBeanProcess* process, uint32_t id);
MAGIC_BEAN_EXPORT void              magic_bean_thread_close(MagicBeanThread* thread);
MAGIC_BEAN_EXPORT bool              magic_bean_thread_resume(MagicBeanThread* thread);
MAGIC_BEAN_EXPORT bool              magic_bean_thread_suspend(MagicBeanThread* thread);
MAGIC_BEAN_EXPORT bool              magic_bean_thread_terminate(MagicBeanThread* thread, uint32_t exitCode);
MAGIC_BEAN_EXPORT bool              magic_bean_thread_get_exit_code(MagicBeanThread* thread, uint32_t* lpValue);
MAGIC_BEAN_EXPORT bool              magic_bean_thread_wait_for_exit(MagicBeanThread* thread, uint32_t* lpExitCode);

MAGIC_BEAN_EXPORT bool              magic_bean_window_enumerate(MagicBeanProcess* process, magic_bean_window_enumerate_callback callback, void* lpParam);
MAGIC_BEAN_EXPORT MagicBeanWindow*  magic_bean_window_open_by_name(MagicBeanProcess* process, const char* name);
MAGIC_BEAN_EXPORT MagicBeanWindow*  magic_bean_window_open_by_index(MagicBeanProcess* process, size_t index);
MAGIC_BEAN_EXPORT void              magic_bean_window_close(MagicBeanWindow* window);
MAGIC_BEAN_EXPORT const char*       magic_bean_window_get_name(MagicBeanWindow* window);
MAGIC_BEAN_EXPORT bool              magic_bean_window_set_name(MagicBeanWindow* window, const char* value);

MAGIC_BEAN_EXPORT bool              magic_bean_process_enumerate(MagicBean* magic, magic_bean_process_enumerate_callback callback, void* lpParam);
MAGIC_BEAN_EXPORT MagicBeanProcess* magic_bean_process_open_by_id(MagicBean* magic, uint32_t id);
MAGIC_BEAN_EXPORT MagicBeanProcess* magic_bean_process_open_by_name(MagicBean* magic, const char* name);
MAGIC_BEAN_EXPORT void              magic_bean_process_close(MagicBeanProcess* process);
MAGIC_BEAN_EXPORT bool              magic_bean_process_resume(MagicBeanProcess* process);
MAGIC_BEAN_EXPORT bool              magic_bean_process_suspend(MagicBeanProcess* process);
MAGIC_BEAN_EXPORT bool              magic_bean_process_set_debugger_present(MagicBeanProcess* process, bool value);
MAGIC_BEAN_EXPORT bool              magic_bean_process_memory_read(MagicBeanProcess* process, uint64_t address, void* lpBuffer, uint64_t size);
MAGIC_BEAN_EXPORT bool              magic_bean_process_memory_read_int8(MagicBeanProcess* process, uint64_t address, int8_t* lpValue);
MAGIC_BEAN_EXPORT bool              magic_bean_process_memory_read_int16(MagicBeanProcess* process, uint64_t address, int16_t* lpValue);
MAGIC_BEAN_EXPORT bool              magic_bean_process_memory_read_int32(MagicBeanProcess* process, uint64_t address, int32_t* lpValue);
MAGIC_BEAN_EXPORT bool              magic_bean_process_memory_read_int64(MagicBeanProcess* process, uint64_t address, int64_t* lpValue);
MAGIC_BEAN_EXPORT bool              magic_bean_process_memory_read_uint8(MagicBeanProcess* process, uint64_t address, uint8_t* lpValue);
MAGIC_BEAN_EXPORT bool              magic_bean_process_memory_read_uint16(MagicBeanProcess* process, uint64_t address, uint16_t* lpValue);
MAGIC_BEAN_EXPORT bool              magic_bean_process_memory_read_uint32(MagicBeanProcess* process, uint64_t address, uint32_t* lpValue);
MAGIC_BEAN_EXPORT bool              magic_bean_process_memory_read_uint64(MagicBeanProcess* process, uint64_t address, uint64_t* lpValue);
MAGIC_BEAN_EXPORT bool              magic_bean_process_memory_read_float(MagicBeanProcess* process, uint64_t address, float* lpValue);
MAGIC_BEAN_EXPORT bool              magic_bean_process_memory_read_double(MagicBeanProcess* process, uint64_t address, double* lpValue);
MAGIC_BEAN_EXPORT ssize_t           magic_bean_process_memory_read_string(MagicBeanProcess* process, uint64_t address, char* lpValue, size_t maxLength);
MAGIC_BEAN_EXPORT bool              magic_bean_process_memory_write(MagicBeanProcess* process, uint64_t address, const void* lpBuffer, uint64_t size);
MAGIC_BEAN_EXPORT bool              magic_bean_process_memory_write_int8(MagicBeanProcess* process, uint64_t address, int8_t value);
MAGIC_BEAN_EXPORT bool              magic_bean_process_memory_write_int16(MagicBeanProcess* process, uint64_t address, int16_t value);
MAGIC_BEAN_EXPORT bool              magic_bean_process_memory_write_int32(MagicBeanProcess* process, uint64_t address, int32_t value);
MAGIC_BEAN_EXPORT bool              magic_bean_process_memory_write_int64(MagicBeanProcess* process, uint64_t address, int64_t value);
MAGIC_BEAN_EXPORT bool              magic_bean_process_memory_write_uint8(MagicBeanProcess* process, uint64_t address, uint8_t value);
MAGIC_BEAN_EXPORT bool              magic_bean_process_memory_write_uint16(MagicBeanProcess* process, uint64_t address, uint16_t value);
MAGIC_BEAN_EXPORT bool              magic_bean_process_memory_write_uint32(MagicBeanProcess* process, uint64_t address, uint32_t value);
MAGIC_BEAN_EXPORT bool              magic_bean_process_memory_write_uint64(MagicBeanProcess* process, uint64_t address, uint64_t value);
MAGIC_BEAN_EXPORT bool              magic_bean_process_memory_write_float(MagicBeanProcess* process, uint64_t address, float value);
MAGIC_BEAN_EXPORT bool              magic_bean_process_memory_write_double(MagicBeanProcess* process, uint64_t address, double value);
MAGIC_BEAN_EXPORT bool              magic_bean_process_memory_write_string(MagicBeanProcess* process, uint64_t address, const char* value);
MAGIC_BEAN_EXPORT uint64_t          magic_bean_process_memory_find(MagicBeanProcess* process, const char* mask, const uint8_t* pattern);
MAGIC_BEAN_EXPORT uint64_t          magic_bean_process_memory_find_at(MagicBeanProcess* process, const char* mask, const uint8_t* pattern, uint64_t address, uint64_t size);
MAGIC_BEAN_EXPORT uint64_t          magic_bean_process_memory_allocate(MagicBeanProcess* process, uint64_t size, MAGIC_BEAN_PROCESS_MEMORY_PROTECTION_TYPES type);
MAGIC_BEAN_EXPORT uint64_t          magic_bean_process_memory_allocate_at(MagicBeanProcess* process, uint64_t address, uint64_t size, MAGIC_BEAN_PROCESS_MEMORY_PROTECTION_TYPES type);
MAGIC_BEAN_EXPORT bool              magic_bean_process_memory_release(MagicBeanProcess* process, uint64_t address);
MAGIC_BEAN_EXPORT MagicBeanLibrary* magic_bean_process_library_open(MagicBeanProcess* process, const char* name);
MAGIC_BEAN_EXPORT void              magic_bean_process_library_close(MagicBeanLibrary* library);
MAGIC_BEAN_EXPORT MagicBeanLibrary* magic_bean_process_library_load_file(MagicBeanProcess* process, const char* path);
MAGIC_BEAN_EXPORT MagicBeanLibrary* magic_bean_process_library_load_buffer(MagicBeanProcess* process, const void* lpBuffer, uint64_t size);
MAGIC_BEAN_EXPORT MagicBeanLibrary* magic_bean_process_library_load_memory(MagicBeanProcess* process, uint64_t address, uint64_t size);
MAGIC_BEAN_EXPORT void              magic_bean_process_library_unload(MagicBeanLibrary* library);
MAGIC_BEAN_EXPORT uint64_t          magic_bean_process_library_get_export(MagicBeanLibrary* library, const char* name);

#if defined(__cplusplus)
}
#endif

#endif
