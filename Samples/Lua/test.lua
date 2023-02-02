local magic = magic_bean_open();

magic_bean_process_enumerate(
	magic,
	function(processId, processName)
		print("Process ID: " .. processId .. ", Name: " .. processName);
	end
);

local process = magic_bean_process_open_by_name(magic, "wow.exe");

if not magic_bean_is_null(process) then
	magic_bean_thread_enumerate(
		process,
		function(processThreadId)
			print("Thread ID: " .. processThreadId);
		end
	);

	magic_bean_window_enumerate(
		process,
		function(processWindowName, processWindowIndex)
			print("Window Name: " .. processWindowName .. ", Index: " .. processWindowIndex);
		end
	);

	local playerGUID = magic_bean_process_memory_read_uint64(process, 0x00CA1238);

	if playerGUID ~= 0 then
		local realmName  = magic_bean_process_memory_read_string(process, 0x00C79B9E, 32);
		local playerName = magic_bean_process_memory_read_string(process, 0x00C79D18, 16);

		print(playerName .. ":" .. string.format("%x", playerGUID) .. " @ " .. realmName);
	end

	magic_bean_process_close(process);
end

magic_bean_close(magic);
