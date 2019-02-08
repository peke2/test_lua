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


function macroTest(arg)
	for i=1,#arg.work do
		arg.work[i] = arg.work[i] + 1
	end
	return arg
end


function update(params)
	rad_old = ((params.count-1) % 360) /180.0 * math.pi
	rad_new = (params.count % 360) /180.0 * math.pi
	pos = params.pos
	pos.x = pos.x + 2
	--pos.y = pos.y + 1
	pos.y = pos.y + (math.cos(rad_new) - math.cos(rad_old))*32
	params.pos = pos

	return params
end


-- 計算の合計値が想定最大値になっているかの確認
-- params = {pos={}}
-- params.pos.x = 0
-- params.pos.y = 0
-- params.count = 0
-- 
-- prev_y = 0
-- total_y = 0
-- for i=0,90 do
-- 	params = update(params)
-- 	-- print("["..params.pos.x..","..params.pos.y.."]")
-- 	diff = params.pos.y - prev_y
-- 	prev_y = params.pos.y
-- 	total_y = total_y + diff
-- 	params.count = params.count + 1
-- end
-- 
-- print("Y合計"..total_y)
