-- AdvertCast, Piotr Rżysko, 30.12.2015

local advertcast_proto = Proto("advertcast", "AdvertCast Protocol")

function advertcast_proto.dissector(buffer, pinfo, tree)
	pinfo.cols.protocol = "ADVERTCAST"
	local subtree = tree:add(advertcast_proto, buffer(), "AdvertCast Protocol")

	local function get_next_arg(line)
		local f_space_index = string.find(line, " ")
		if f_space_index then
			return string.sub(line, 1, f_space_index - 1), string.sub(line, f_space_index + 1)
		end
		return line, nil
	end

	local function add_sub_arg(line, offset, name)
		arg, line = get_next_arg(line)
		subtree:add(buffer(offset + 1, arg:len()), name..arg)
		offset = offset + 1 + arg:len()
		return line, offset
	end	

	local get_next_line = buffer():string():gmatch('[^\n]+')

	while true do
		local line = get_next_line()
	
		if line == nil then
			return
		end

		local arg, line = get_next_arg(line)
		local offset = 0	
	
		if arg == nil then
			return
		end

		if arg == 'CONNECT' then
			subtree:add(buffer(offset, arg:len()), "Command: 'CONNECT'")

		elseif arg == 'CLIENT' then
			subtree:add(buffer(offset, arg:len()), "Command: 'CLIENT'")
			offset = offset + arg:len()	
	
			line, offset = add_sub_arg(line, offset, "Client id: ")
			line, offset = add_sub_arg(line, offset, "Multicast group address: ")
			line, offset = add_sub_arg(line, offset, "Multicast port: ")

		elseif arg == 'REPORT' then
			subtree:add(buffer(offset, arg:len()), "Command: 'REPORT'")	
			offset = offset + arg:len()

			line, offset = add_sub_arg(line, offset, "Client id: ")
			line, offset = add_sub_arg(line, offset, "Successes: ")
			line, offset = add_sub_arg(line, offset, "Errors: ")
			line, offset = add_sub_arg(line, offset, "In buffor: ")

		elseif arg == 'NAK' then
			subtree:add(buffer(offset, arg:len()), "Command: 'NAK'")
			offset = offset + arg:len()

			line, offset = add_sub_arg(line, offset, "Client id: ")
			line, offset = add_sub_arg(line, offset, "File id: ")
		else
			return
		end
	end
end

local tcp_table = DissectorTable.get("tcp.port")
tcp_table:add(5555, advertcast_proto)
