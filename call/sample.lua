-- サンプル

Name = "てすと"
Value = 13

function mul(a, b)
	print("a=["..a.."] b=["..b.."]")
	innerCall()
	return a * b
end

function innerCall()
	print("<<<内部での関数呼び出し>>>")
end

-- 複数の戻り値を設定する場合
function calc(a, b, c)
	d = a + b + c
	e = a * b * c
	return d, e
end

-- C側の関数の引数を複数にしてテーブルを含めてみる
function callWithTable()
	fromLua({x=3,y=5}, 123, "abcdef")
end
