local magic = magic_bean_open();

print("magic_bean_open -> 0x" .. string.format("%x", magic_bean_to_number(magic)));

local magic_bean_process_enumerate_return_value = magic_bean_process_enumerate(
	magic,
	function(processId, processName)
		print("Process ID: " .. processId .. ", Name: " .. processName);

		local process = magic_bean_process_open_by_id(
			magic,
			processId
		);

		print("magic_bean_process_open_by_id -> 0x" .. string.format("%x", magic_bean_to_number(process)));

		if not magic_bean_is_null(process) then
			-- local magic_bean_thread_enumerate_return_value = magic_bean_thread_enumerate(
			-- 	process,
			-- 	function(processThreadId)
			-- 		print("Thread ID: " .. processThreadId);
			-- 	end
			-- );

			-- print("magic_bean_thread_enumerate -> " .. (magic_bean_thread_enumerate_return_value and "true" or "false"));

			-- local magic_bean_window_enumerate_return_value = magic_bean_window_enumerate(
			-- 	process,
			-- 	function(processWindowName, processWindowIndex)
			-- 		print("Window Name: " .. processWindowName .. ", Index: " .. processWindowIndex);
			-- 	end
			-- );

			-- print("magic_bean_window_enumerate -> " .. (magic_bean_window_enumerate_return_value and "true" or "false"));

			-- if processName == "wow.exe" then
			-- 	if magic_bean_process_memory_read_uint64(process, 0x00CA1238) ~= 0 then
			-- 		local realmName  = magic_bean_process_memory_read_string(process, 0x00C79B9E, 32);
			-- 		local playerName = magic_bean_process_memory_read_string(process, 0x00C79D18, 16);

			-- 		print(playerName .. " @ " .. realmName);
			-- 	end
			-- end

			magic_bean_process_close(process);
		end
	end
);

print("magic_bean_process_enumerate -> " .. (magic_bean_process_enumerate_return_value and "true" or "false"));

magic_bean_close(magic);
