# SoftFloat加法一手参考

固定John R. Hauser/UC Regents SoftFloat3 commit497c81c1；4原件14000B先下载E盘，再逐字节整理到本目录。原SHA/URL/时间见receipts.json，版权及BSD3全文保留；无ZIP下载或删除。

仅比较GRS、sticky及异号归一化机制；本提案另用UInt32数值舍入给leading/carry，未继承C性能或NaN/flags策略。研究与验收边界见../../astra-grs-add-paper.md；Lean/full gate/速度均待实测。
