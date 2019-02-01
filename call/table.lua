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

print("数="..Stage.num)
print("test="..Stage.stages.test)
print("name="..Stage.stages[2].name)
print("etc="..Stage["etc"])

for i=1,3 do
	print(Stage.stages[i].name)
end
