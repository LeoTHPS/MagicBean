local MagicBean = {};

function MagicBean.OpenProcess(processNameOrId)
	MagicBean.magic = magic_bean_open();

	if magic_bean_is_null(MagicBean.magic) then

		return false;
	end

	local processNameOrIdType = type(processNameOrId);

	if processNameOrIdType == 'string' then
		MagicBean.process = magic_bean_process_open_by_name(MagicBean.magic, processNameOrId);
	elseif processNameOrIdType == "number" then
		MagicBean.process = magic_bean_process_open_by_id(MagicBean.magic, processNameOrId);
	else
		magic_bean_close(MagicBean.magic);

		return false;
	end

	if magic_bean_is_null(MagicBean.process) then
		magic_bean_close(MagicBean.magic);

		return false;
	end

	return true;
end

function MagicBean.CloseProcess()
	magic_bean_close(MagicBean.process);
	magic_bean_close(MagicBean.magic);
end

function MagicBean.ReadInt8(address)
	local success, value = magic_bean_process_memory_read_int8(MagicBean.process, address);

	return success and value or 0;
end
function MagicBean.ReadInt16(address)
	local success, value = magic_bean_process_memory_read_int16(MagicBean.process, address);

	return success and value or 0;
end
function MagicBean.ReadInt32(address)
	local success, value = magic_bean_process_memory_read_int32(MagicBean.process, address);

	return success and value or 0;
end
function MagicBean.ReadInt64(address)
	local success, value = magic_bean_process_memory_read_int64(MagicBean.process, address);

	return success and value or 0;
end
function MagicBean.ReadUInt8(address)
	local success, value = magic_bean_process_memory_read_uint8(MagicBean.process, address);

	return success and value or 0;
end
function MagicBean.ReadUInt16(address)
	local success, value = magic_bean_process_memory_read_uint16(MagicBean.process, address);

	return success and value or 0;
end
function MagicBean.ReadUInt32(address)
	local success, value = magic_bean_process_memory_read_uint32(MagicBean.process, address);

	return success and value or 0;
end
function MagicBean.ReadUInt64(address)
	local success, value = magic_bean_process_memory_read_uint64(MagicBean.process, address);

	return success and value or 0;
end
function MagicBean.ReadFloat(address)
	local success, value = magic_bean_process_memory_read_float(MagicBean.process, address);

	return success and value or 0;
end
function MagicBean.ReadDouble(address)
	local success, value = magic_bean_process_memory_read_double(MagicBean.process, address);

	return success and value or 0;
end
function MagicBean.ReadString(address, maxLength)
	local success, value = magic_bean_process_memory_read_string(MagicBean.process, address, maxLength);

	return success and value or nil;
end

function MagicBean.WriteInt8(address, value)
	return magic_bean_process_memory_write_int8(MagicBean.process, address, value);
end
function MagicBean.WriteInt16(address, value)
	return magic_bean_process_memory_write_int16(MagicBean.process, address, value);
end
function MagicBean.WriteInt32(address, value)
	return magic_bean_process_memory_write_int32(MagicBean.process, address, value);
end
function MagicBean.WriteInt64(address, value)
	return magic_bean_process_memory_write_int64(MagicBean.process, address, value);
end
function MagicBean.WriteUInt8(address, value)
	return magic_bean_process_memory_write_uint8(MagicBean.process, address, value);
end
function MagicBean.WriteUInt16(address, value)
	return magic_bean_process_memory_write_uint16(MagicBean.process, address, value);
end
function MagicBean.WriteUInt32(address, value)
	return magic_bean_process_memory_write_uint32(MagicBean.process, address, value);
end
function MagicBean.WriteUInt64(address, value)
	return magic_bean_process_memory_write_uint64(MagicBean.process, address, value);
end
function MagicBean.WriteFloat(address, value)
	return magic_bean_process_memory_write_float(MagicBean.process, address, value);
end
function MagicBean.WriteDouble(address, value)
	return magic_bean_process_memory_write_double(MagicBean.process, address, value);
end
function MagicBean.WriteString(address, value)
	return magic_bean_process_memory_write_string(MagicBean.process, address, value);
end

if MagicBean.OpenProcess('wow.exe') then
	io.write("Enable console? y/n: ");
	local isConsoleEnabled = io.read("l") == "y";
	MagicBean.WriteUInt32(0x00CABCC4, isConsoleEnabled and 1 or 0);
	print("Console " .. (isConsoleEnabled and "enabled" or "disabled"));

	local playerGUID = MagicBean.ReadUInt64(0x00CA1238);

	if playerGUID ~= 0 then
		local realmName   = MagicBean.ReadString(0x00C79B9E, 32);
		local playerName  = MagicBean.ReadString(0x00C79D18, 16);
		local playerIsAfk = MagicBean.ReadUInt32(0x00BCEFEC);

		print(((playerIsAfk ~= 0) and "<away> " or "") .. playerName .. ":" .. string.format("%x", playerGUID) .. " @ " .. realmName);
	end

	MagicBean.CloseProcess();
end
