-- コルーチン

function flow()
	print("1")
	coroutine.yield("World")
	print("2")
	coroutine.yield("Hello")
	print("3")
	coroutine.yield("Good morning")
end
