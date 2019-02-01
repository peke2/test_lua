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
