

function say(word)
	print("Hello "..word)
end

-- 関数を変数に入れる
func = say

-- そのまま呼び出せる
func("World")
