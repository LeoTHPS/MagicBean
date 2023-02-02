#include <jni.h>

#include <MagicBean/MagicBean.h>

#define jni_GetUTFString(__jni__, __managed__)                 __jni__->GetStringUTFChars(__managed__, nullptr)
#define jni_ReleaseUTFString(__jni__, __managed__, __native__) __jni__->ReleaseStringUTFChars(__managed__, __native__)

#define jni_GetByteArray(__jni__, __managed__)                 __jni__->GetByteArrayElements(__managed__, nullptr)
#define jni_ReleaseByteArray(__jni__, __managed__, __native__) __jni__->ReleaseByteArrayElements(__managed__, __native__, 0)

extern "C" JNIEXPORT jlong JNICALL    Java_MagicBean_magic_bean_open(JNIEnv* jni, jclass clazz)
{
	return reinterpret_cast<jlong>(magic_bean_open());
}
extern "C" JNIEXPORT void JNICALL     Java_MagicBean_magic_bean_close(JNIEnv* jni, jclass clazz, jlong magic)
{
	magic_bean_close(reinterpret_cast<MagicBean*>(magic));
}

extern "C" JNIEXPORT jboolean JNICALL Java_MagicBean_magic_bean_thread_enumerate(JNIEnv* jni, jclass clazz, jlong process, jobject callback)
{
	struct Context
	{
		JNIEnv* JNI;
		jobject Callback;
		jclass  C_MagicBean_ThreadInformation;
	} context;

	context.JNI                           = jni;
	context.Callback                      = callback;
	context.C_MagicBean_ThreadInformation = jni->FindClass("MagicBean$ThreadInformation");

	magic_bean_thread_enumerate_callback _callback = [](const MagicBeanThreadInformation* _lpInformation, void* _lpParam)->bool
	{
		auto lpContext = reinterpret_cast<const Context*>(
			_lpParam
		);

		auto threadInformation = lpContext->JNI->NewObject(
			lpContext->C_MagicBean_ThreadInformation,
			lpContext->JNI->GetMethodID(
				lpContext->C_MagicBean_ThreadInformation,
				"<init>",
				"(I;)V"
			),
			static_cast<jint>(_lpInformation->ID)
		);

		return lpContext->JNI->CallBooleanMethod(
			lpContext->Callback,
			lpContext->JNI->GetMethodID(lpContext->JNI->GetObjectClass(lpContext->Callback), "callback", "(LMagicBean$ThreadInformation;)Z"),
			threadInformation
		);
	};

	return magic_bean_thread_enumerate(reinterpret_cast<MagicBeanProcess*>(process), _callback, &context);
}
extern "C" JNIEXPORT jlong JNICALL    Java_MagicBean_magic_bean_thread_create(JNIEnv* jni, jclass clazz, jlong process, jlong address, jlong lpParam)
{
	return reinterpret_cast<jlong>(magic_bean_thread_create(reinterpret_cast<MagicBeanProcess*>(process), static_cast<uint64_t>(address), static_cast<uint64_t>(lpParam)));
}
extern "C" JNIEXPORT jlong JNICALL    Java_MagicBean_magic_bean_thread_open_by_id(JNIEnv* jni, jclass clazz, jlong process, jint id)
{
	return reinterpret_cast<jlong>(magic_bean_thread_open_by_id(reinterpret_cast<MagicBeanProcess*>(process), static_cast<uint32_t>(id)));
}
extern "C" JNIEXPORT void JNICALL     Java_MagicBean_magic_bean_thread_close(JNIEnv* jni, jclass clazz, jlong thread)
{
	magic_bean_thread_close(reinterpret_cast<MagicBeanThread*>(thread));
}
extern "C" JNIEXPORT jboolean JNICALL Java_MagicBean_magic_bean_thread_resume(JNIEnv* jni, jclass clazz, jlong thread)
{
	return magic_bean_thread_resume(reinterpret_cast<MagicBeanThread*>(thread));
}
extern "C" JNIEXPORT jboolean JNICALL Java_MagicBean_magic_bean_thread_suspend(JNIEnv* jni, jclass clazz, jlong thread)
{
	return magic_bean_thread_suspend(reinterpret_cast<MagicBeanThread*>(thread));
}
extern "C" JNIEXPORT jboolean JNICALL Java_MagicBean_magic_bean_thread_terminate(JNIEnv* jni, jclass clazz, jlong thread, jint exitCode)
{
	return magic_bean_thread_terminate(reinterpret_cast<MagicBeanThread*>(thread), static_cast<uint32_t>(exitCode));
}
extern "C" JNIEXPORT jboolean JNICALL Java_MagicBean_magic_bean_thread_get_exit_code(JNIEnv* jni, jclass clazz, jlong thread, jobject exitCode)
{
	uint32_t _exitCode;

	if (!magic_bean_thread_get_exit_code(reinterpret_cast<MagicBeanThread*>(thread), &_exitCode))
	{

		return false;
	}

	jni->SetIntField(
		exitCode,
		jni->GetFieldID(jni->GetObjectClass(exitCode), "value", "I"),
		static_cast<jint>(_exitCode)
	);

	return true;
}
extern "C" JNIEXPORT jboolean JNICALL Java_MagicBean_magic_bean_thread_wait_for_exit(JNIEnv* jni, jclass clazz, jlong thread, jobject exitCode)
{
	uint32_t _exitCode;

	if (!magic_bean_thread_wait_for_exit(reinterpret_cast<MagicBeanThread*>(thread), &_exitCode))
	{

		return false;
	}

	jni->SetIntField(
		exitCode,
		jni->GetFieldID(jni->GetObjectClass(exitCode), "value", "I"),
		static_cast<jint>(_exitCode)
	);

	return true;
}

extern "C" JNIEXPORT jboolean JNICALL Java_MagicBean_magic_bean_window_enumerate(JNIEnv* jni, jclass clazz, jlong process, jobject callback)
{
	struct Context
	{
		JNIEnv* JNI;
		jobject Callback;
		jclass  C_MagicBean_WindowInformation;
	} context;

	context.JNI                           = jni;
	context.Callback                      = callback;
	context.C_MagicBean_WindowInformation = jni->FindClass("MagicBean$WindowInformation");

	magic_bean_window_enumerate_callback _callback = [](const MagicBeanWindowInformation* _lpInformation, void* _lpParam)->bool
	{
		auto lpContext = reinterpret_cast<const Context*>(
			_lpParam
		);

		auto windowInformation = lpContext->JNI->NewObject(
			lpContext->C_MagicBean_WindowInformation,
			lpContext->JNI->GetMethodID(
				lpContext->C_MagicBean_WindowInformation,
				"<init>",
				"(Ljava/lang/String;I)V"
			),
			lpContext->JNI->NewStringUTF(_lpInformation->Name),
			static_cast<jint>(_lpInformation->Index)
		);

		return lpContext->JNI->CallBooleanMethod(
			lpContext->Callback,
			lpContext->JNI->GetMethodID(lpContext->JNI->GetObjectClass(lpContext->Callback), "callback", "(LMagicBean$WindowInformation;)Z"),
			windowInformation
		);
	};

	return magic_bean_window_enumerate(reinterpret_cast<MagicBeanProcess*>(process), _callback, &context);
}
extern "C" JNIEXPORT jlong JNICALL    Java_MagicBean_magic_bean_window_open_by_name(JNIEnv* jni, jclass clazz, jlong process, jstring name)
{
	auto lpName = jni_GetUTFString(
		jni,
		name
	);

	auto value = magic_bean_window_open_by_name(
		reinterpret_cast<MagicBeanProcess*>(process),
		lpName
	);

	jni_ReleaseUTFString(
		jni,
		name,
		lpName
	);

	return reinterpret_cast<jlong>(
		value
	);
}
extern "C" JNIEXPORT jlong JNICALL    Java_MagicBean_magic_bean_window_open_by_index(JNIEnv* jni, jclass clazz, jlong process, jint index)
{
	return reinterpret_cast<jlong>(magic_bean_window_open_by_index(reinterpret_cast<MagicBeanProcess*>(process), static_cast<size_t>(index)));
}
extern "C" JNIEXPORT void JNICALL     Java_MagicBean_magic_bean_window_close(JNIEnv* jni, jclass clazz, jlong window)
{
	magic_bean_window_close(reinterpret_cast<MagicBeanWindow*>(window));
}

extern "C" JNIEXPORT jboolean JNICALL Java_MagicBean_magic_bean_process_enumerate(JNIEnv* jni, jclass clazz, jlong magic, jobject callback)
{
	struct Context
	{
		JNIEnv* JNI;
		jobject Callback;
		jclass  C_MagicBean_ProcessInformation;
	} context;

	context.JNI                            = jni;
	context.Callback                       = callback;
	context.C_MagicBean_ProcessInformation = jni->FindClass("MagicBean$ProcessInformation");

	magic_bean_process_enumerate_callback _callback = [](const MagicBeanProcessInformation* _lpInformation, void* _lpParam)->bool
	{
		auto lpContext = reinterpret_cast<const Context*>(
			_lpParam
		);

		auto processInformation = lpContext->JNI->NewObject(
			lpContext->C_MagicBean_ProcessInformation,
			lpContext->JNI->GetMethodID(
				lpContext->C_MagicBean_ProcessInformation,
				"<init>",
				"(ILjava/lang/String;)V"
			),
			static_cast<jint>(_lpInformation->ID),
			lpContext->JNI->NewStringUTF(_lpInformation->Name)
		);

		return lpContext->JNI->CallBooleanMethod(
			lpContext->Callback,
			lpContext->JNI->GetMethodID(lpContext->JNI->GetObjectClass(lpContext->Callback), "callback", "(LMagicBean$ProcessInformation;)Z"),
			processInformation
		);
	};

	return magic_bean_process_enumerate(reinterpret_cast<MagicBean*>(magic), _callback, &context);
}
extern "C" JNIEXPORT jlong JNICALL    Java_MagicBean_magic_bean_process_open_by_id(JNIEnv* jni, jclass clazz, jlong magic, jint id)
{
	return reinterpret_cast<jlong>(magic_bean_process_open_by_id(reinterpret_cast<MagicBean*>(magic), static_cast<uint32_t>(id)));
}
extern "C" JNIEXPORT jlong JNICALL    Java_MagicBean_magic_bean_process_open_by_name(JNIEnv* jni, jclass clazz, jlong magic, jstring name)
{
	auto lpName = jni_GetUTFString(
		jni,
		name
	);

	auto value = magic_bean_process_open_by_name(
		reinterpret_cast<MagicBean*>(magic),
		lpName
	);

	jni_ReleaseUTFString(
		jni,
		name,
		lpName
	);

	return reinterpret_cast<jlong>(
		value
	);
}
extern "C" JNIEXPORT void JNICALL     Java_MagicBean_magic_bean_process_close(JNIEnv* jni, jclass clazz, jlong process)
{
	magic_bean_process_close(reinterpret_cast<MagicBeanProcess*>(process));
}
extern "C" JNIEXPORT jboolean JNICALL Java_MagicBean_magic_bean_process_resume(JNIEnv* jni, jclass clazz, jlong process)
{
	return magic_bean_process_resume(reinterpret_cast<MagicBeanProcess*>(process));
}
extern "C" JNIEXPORT jboolean JNICALL Java_MagicBean_magic_bean_process_suspend(JNIEnv* jni, jclass clazz, jlong process)
{
	return magic_bean_process_suspend(reinterpret_cast<MagicBeanProcess*>(process));
}
extern "C" JNIEXPORT jboolean JNICALL Java_MagicBean_magic_bean_process_set_debugger_present(JNIEnv* jni, jclass clazz, jlong process, jboolean set)
{
	return magic_bean_process_set_debugger_present(reinterpret_cast<MagicBeanProcess*>(process), set);
}
extern "C" JNIEXPORT jboolean JNICALL Java_MagicBean_magic_bean_process_memory_read(JNIEnv* jni, jclass clazz, jlong process, jlong address, jbyteArray buffer, jint offset, jint size)
{
	auto lpBuffer = new jbyte[size];

	if (!magic_bean_process_memory_read(reinterpret_cast<MagicBeanProcess*>(process), static_cast<uint64_t>(address), lpBuffer, static_cast<uint64_t>(size)))
	{
		delete[] lpBuffer;

		return false;
	}

	jni->SetByteArrayRegion(
		buffer,
		static_cast<jsize>(offset),
		static_cast<jsize>(size),
		lpBuffer
	);

	delete[] lpBuffer;

	return true;
}
extern "C" JNIEXPORT jboolean JNICALL Java_MagicBean_magic_bean_process_memory_write(JNIEnv* jni, jclass clazz, jlong process, jlong address, jbyteArray buffer, jint offset, jint size)
{
	auto lpBuffer = jni_GetByteArray(
		jni,
		buffer
	);

	auto value = magic_bean_process_memory_write(
		reinterpret_cast<MagicBeanProcess*>(process),
		static_cast<uint64_t>(address),
		&lpBuffer[offset],
		static_cast<uint64_t>(size)
	);

	jni_ReleaseByteArray(
		jni,
		buffer,
		lpBuffer
	);

	return value;
}
extern "C" JNIEXPORT jlong JNICALL    Java_MagicBean_magic_bean_process_memory_find(JNIEnv* jni, jclass clazz, jlong process, jstring mask, jbyteArray pattern)
{
	auto lpMask = jni_GetUTFString(
		jni,
		mask
	);

	auto lpPattern = jni_GetByteArray(
		jni,
		pattern
	);

	auto value = magic_bean_process_memory_find(
		reinterpret_cast<MagicBeanProcess*>(process),
		lpMask,
		reinterpret_cast<const uint8_t*>(lpPattern)
	);

	jni_ReleaseByteArray(
		jni,
		pattern,
		lpPattern
	);

	jni_ReleaseUTFString(
		jni,
		mask,
		lpMask
	);

	return static_cast<jlong>(
		value
	);
}
extern "C" JNIEXPORT jlong JNICALL    Java_MagicBean_magic_bean_process_memory_find_at(JNIEnv* jni, jclass clazz, jlong process, jstring mask, jbyteArray pattern, jlong address, jlong size)
{
	auto lpMask = jni_GetUTFString(
		jni,
		mask
	);

	auto lpPattern = jni_GetByteArray(
		jni,
		pattern
	);

	auto value = magic_bean_process_memory_find_at(
		reinterpret_cast<MagicBeanProcess*>(process),
		lpMask,
		reinterpret_cast<const uint8_t*>(lpPattern),
		static_cast<uint64_t>(address),
		static_cast<uint64_t>(size)
	);

	jni_ReleaseByteArray(
		jni,
		pattern,
		lpPattern
	);

	jni_ReleaseUTFString(
		jni,
		mask,
		lpMask
	);

	return static_cast<jlong>(
		value
	);
}
extern "C" JNIEXPORT jlong JNICALL    Java_MagicBean_magic_bean_process_memory_allocate(JNIEnv* jni, jclass clazz, jlong process, jlong size)
{
	return static_cast<jlong>(magic_bean_process_memory_allocate(reinterpret_cast<MagicBeanProcess*>(process), static_cast<uint64_t>(size)));
}
extern "C" JNIEXPORT jlong JNICALL    Java_MagicBean_magic_bean_process_memory_allocate_at(JNIEnv* jni, jclass clazz, jlong process, jlong address, jlong size)
{
	return static_cast<jlong>(magic_bean_process_memory_allocate_at(reinterpret_cast<MagicBeanProcess*>(process), static_cast<uint64_t>(address), static_cast<uint64_t>(size)));
}
extern "C" JNIEXPORT jboolean JNICALL Java_MagicBean_magic_bean_process_memory_release(JNIEnv* jni, jclass clazz, jlong process, jlong address)
{
	return magic_bean_process_memory_release(reinterpret_cast<MagicBeanProcess*>(process), static_cast<uint64_t>(address));
}
extern "C" JNIEXPORT jlong JNICALL    Java_MagicBean_magic_bean_process_library_open(JNIEnv* jni, jclass clazz, jlong process, jstring name)
{
	auto lpName = jni_GetUTFString(
		jni,
		name
	);

	auto value = magic_bean_process_library_open(
		reinterpret_cast<MagicBeanProcess*>(process),
		lpName
	);

	jni_ReleaseUTFString(
		jni,
		name,
		lpName
	);

	return reinterpret_cast<jlong>(
		value
	);
}
extern "C" JNIEXPORT void JNICALL     Java_MagicBean_magic_bean_process_library_close(JNIEnv* jni, jclass clazz, jlong library)
{
	magic_bean_process_library_close(reinterpret_cast<MagicBeanLibrary*>(library));
}
extern "C" JNIEXPORT jlong JNICALL    Java_MagicBean_magic_bean_process_library_load_file(JNIEnv* jni, jclass clazz, jlong process, jstring path)
{
	auto lpPath = jni_GetUTFString(
		jni,
		path
	);

	auto value = magic_bean_process_library_load_file(
		reinterpret_cast<MagicBeanProcess*>(process),
		lpPath
	);

	jni_ReleaseUTFString(
		jni,
		path,
		lpPath
	);

	return reinterpret_cast<jlong>(
		value
	);
}
extern "C" JNIEXPORT jlong JNICALL    Java_MagicBean_magic_bean_process_library_load_buffer(JNIEnv* jni, jclass clazz, jlong process, jbyteArray buffer)
{
	auto lpBuffer = jni_GetByteArray(
		jni,
		buffer
	);

	auto value = magic_bean_process_library_load_buffer(
		reinterpret_cast<MagicBeanProcess*>(process),
		lpBuffer,
		static_cast<uint64_t>(jni->GetArrayLength(buffer))
	);

	jni_ReleaseByteArray(
		jni,
		buffer,
		lpBuffer
	);

	return reinterpret_cast<jlong>(
		value
	);
}
extern "C" JNIEXPORT jlong JNICALL    Java_MagicBean_magic_bean_process_library_load_memory(JNIEnv* jni, jclass clazz, jlong process, jlong address, jlong size)
{
	return reinterpret_cast<jlong>(magic_bean_process_library_load_memory(reinterpret_cast<MagicBeanProcess*>(process), static_cast<uint64_t>(address), static_cast<uint64_t>(size)));
}
extern "C" JNIEXPORT void JNICALL     Java_MagicBean_magic_bean_process_library_unload(JNIEnv* jni, jclass clazz, jlong library)
{
	magic_bean_process_library_unload(reinterpret_cast<MagicBeanLibrary*>(library));
}
extern "C" JNIEXPORT jlong JNICALL    Java_MagicBean_magic_bean_process_library_get_export(JNIEnv* jni, jclass clazz, jlong library, jstring name)
{
	auto lpName = jni_GetUTFString(
		jni,
		name
	);

	auto value = magic_bean_process_library_get_export(
		reinterpret_cast<MagicBeanLibrary*>(library),
		lpName
	);

	jni_ReleaseUTFString(
		jni,
		name,
		lpName
	);

	return static_cast<jlong>(
		value
	);
}
