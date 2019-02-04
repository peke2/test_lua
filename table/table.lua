-- table

Stage = {
	num = 3,				-- テーブルの「プロパティ」的な扱いができる
	stages = {
		test = 12346,
		{
			name = "aaa",
		},
		{
			name = "bbb",
		},
		{
			name = "ccc",
		},
	},
	["etc"] = "その他",		-- 対象のテーブルの「キー」として登録
}


-- インデックスの指定が無ければ「1」から割り振られる
-- 割り振られたインデックスと同じ場合は、割り振られた方が優先
Table = {
	"Hello",
	[2] = "Yes",
	"World",
}


print("Table[2]="..Table[2])	-- Table[2]=World

-- print("数="..Stage.num)
-- print("test="..Stage.stages.test)
-- print("name="..Stage.stages[2].name)
-- print("etc="..Stage["etc"])

-- for i=1,3 do
-- 	print(Stage.stages[i].name)
-- end
