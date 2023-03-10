local magic = magic_bean_open();

if magic_bean_is_not_null(magic) then
	local process = magic_bean_process_open_by_name(magic, 'wow.exe');

	if magic_bean_is_not_null(process) then
		magic_bean_window_enumerate(process, print);

		io.write("Enable console? y/n: ");
		local isConsoleEnabled = io.read("l") == "y";
		magic_bean_process_memory_write_uint32(process, 0x00CABCC4, isConsoleEnabled and 1 or 0);
		print("Console " .. (isConsoleEnabled and "enabled" or "disabled"));

		local _, playerGUID = magic_bean_process_memory_read_uint64(process, 0x00CA1238);

		if playerGUID ~= 0 then
			local _, realmName   = magic_bean_process_memory_read_string(process, 0x00C79B9E, 32);
			local _, playerName  = magic_bean_process_memory_read_string(process, 0x00C79D18, 16);
			local _, playerIsAfk = magic_bean_process_memory_read_uint32(process, 0x00BCEFEC);

			print(((playerIsAfk ~= 0) and "<away> " or "") .. playerName .. ":" .. string.format("%x", playerGUID) .. " @ " .. realmName);
		end

		magic_bean_process_close(process);
	end

	magic_bean_close(magic);
end
