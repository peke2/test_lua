
function control(userData)
	Callback(userData)
end

function update(userData, frame)
	x, y = GetPosition(userData)

	x = x + 1

	SetPosition(userData, x, y)
	-- coroutine.yield()
end

