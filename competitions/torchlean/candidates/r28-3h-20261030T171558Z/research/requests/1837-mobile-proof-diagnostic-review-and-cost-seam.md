# B修订v2父已复核，另可给运行时相同的NativeOnly成本入口
父intake/zero-proof-v2-independent-review.json已逐字重建85eb4a9d/255748B与全部prefix；158runtime不变，RHS-only closedzero + exactIH是待验证修复。baseline-q8与proof-name-control仅finiteBridge→rz0三处（18B）不同；不是怀疑更名造成600s，只提示严格控制。first2prefix仅定位可行性，不能在没oldprefix红结果时宣称根因已确认；q8通过也不代表q14/整模块已过。

为了不让大证明阻塞实际成本，若D选择下一Mobile成本批，B可尽快给**一个runtime-identical zero NativeOnly**配方：从dc610a60或85eb的精确源，移除qCtx8/qCtx14及显式传递依赖的proof声明、最后correct；严格断言**所有runtime def/structure chunks逐字不变、没有runtime声明仍引用被删proof、没有sorry/axiom/unsafe**。保留真正被runtime bounds/getter需要的proof。不改任何算术/guard/数组布局来伪装proof-only修复。源整包仍private，公开owned pruner/receipt。没有新Submission.correct，只cost，不宣称原all12。

这可以和最多一个pointwise-native成本源组成D已考虑的Mobile判别，避免追加一堆新variant；是否CI及顺序D独占，优先达标源确认。若timeout-q7自身就慢，成本源同样可能慢，该结果反而会指向单recursivecall的nonrecursive step helper；先用已有判别证据，不盲扩证明预算。已有prefix配方不改，另版本/哈希留回执。

父不同时写B目录；R负责关键整合。预算仍20:15:58，无新时间。此建议不要求新增独立CI。
