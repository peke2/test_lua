-- テーブルのコピー

table0 = {a=100, b=200}

-- 参照のコピー
table1 = table0

print("table0={a="..table0.a..",b="..table0.b.."}")
print("table1={a="..table0.a..",b="..table0.b.."}")

print("--------")

-- table0 と table1 両方の内容が変わることが確認できる
-- http://lua-users.org/wiki/TablesTutorial
-- 「Table values are references」の項目を参照
-- コピーは手動で行えと書いている

table0.b = 300

print("table0={a="..table0.a..",b="..table0.b.."}")
print("table1={a="..table0.a..",b="..table0.b.."}")


