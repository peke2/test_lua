-- 引数でテーブルを扱う

function sample(params)
	print("x="..params.pos.x)
	print("y="..params.pos.y)
	print("name="..params.name)

	params.count = params.count + 3

	return params
end

function withArray(array)
	print("引数のパラメータ数="..#array)

	print("++++ インデックスで参照")
	-- 直接参照
	for i=1, #array do
		print("["..i.."]="..array[i].name)
		i = i + 1
	end

	print("++++ 列挙")
	-- 要素列挙
	for k,v in pairs(array) do
		print("["..k.."]="..v.name)
	end
end

