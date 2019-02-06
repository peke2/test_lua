-- luaスクリプト内でのコルーチン使用

function flow()
	coroutine.yield("World")
	coroutine.yield("Hello")
	coroutine.yield("Good morning")
end

-- 匿名関数でコルーチンを作成
-- co = coroutine.create(function()
-- 	flow()
-- end)

-- 関数を指定してコルーチンを作成
co = coroutine.create(flow)


while true do
	-- succeeded, word = coroutine.resume(co)
	-- if( succeeded == false ) then
	-- 	break
	-- end

	-- 終了判定は戻り値を見るしかない？
	print("status="..coroutine.status(co))
	succeeded, word = coroutine.resume(co)
	if( word == nil ) then
		break
	end

	print(word)
end

print("--------")

-- falseになった時点でコルーチンは死んでいる
-- 終了を判定するなら戻り値が「nil」かどうかを見る？
-- print(coroutine.resume(co))	-- true    World
-- print(coroutine.resume(co))	-- true    Hello
-- print(coroutine.resume(co))	-- true    Good morning
-- print(coroutine.resume(co))	-- true    (nil)
-- print(coroutine.resume(co))	-- false   cannot resume dead coroutine

