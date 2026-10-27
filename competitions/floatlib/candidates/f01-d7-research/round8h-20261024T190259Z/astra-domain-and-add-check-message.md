# R14研究交接：真实公开输入域诊断与近指数加法小差检查

时间：2026-10-24T21:45:33.304244+00:00
关联：20261024T213646346Z-r14-research-add-boundaries-and-mul-integration.md
类型：数学支持／机会诊断

乘法主线不变，proof1仍冻结等待实际编译。本次最小动作是核对“guard理论域较大，是否真落在公开负载”以及加法小差值是否会破坏一次转换归约；不增加运行候选或CI请求。

输入域：从原run40129155932的公开seed1425006抽样84个timed scalar case，每case256个分层抖动位置，共21504对。按固定官方BenchSuite.lean逐行翻译生成器（原件10064B及MIT许可证已保留，Git blob已核对），未与Lean产生的操作数交叉校验，属于来源模型诊断。乘法ML2048/2048和paired2048/2048命中主guard；dense1508/1536、sparse787/1536、specials1337/1536、subnormal262/1024、extremes0/1024。支持继续主域验收，同时必须测量回退类的额外guard成本。这些是未加权输入对计数，绝非收益或可省耗时。

加法支持：保守守卫a≥24、最大指数≤252、差≤7下，1792个边界／符号／随机样本同时匹配整数oracle、host正确舍入相加和“UInt32幅度一次转换＋raw平移”原型。115例幅度<2^23、24例精确抵消，明确覆盖当前乘法normal-form草稿不能直接处理的小h分支。a23抵消、d8整数回卷、E254溢出三个反例留存。无Lean或性能通过声明。

实际输入模型中，加法ML2031/2048命中对齐守卫，paired1790/2048。paired并不全是精确相反数：该draw的8个paired case只有1个relation2，其余有常量、近抵消、同号低位扰动和相差23个binade。因此不要仅凭paired分类名假定整个分类可零值快退。

需要开发侧：按原定编译和集成顺序推进，取用这些域条件与负面边界；公开mul接入后审计真实caller及原版full gate。辅助声明编译、有限模型和原版公开入口验收继续分列。

证据（未提交快照，采纳前核对）：
- D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/astra-public-input-domain.json；SHA-256 58127a8d670674d53e59a643ec285a7dc522839e61c1b0b8f36aae59faf99977
- D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/astra-official-bench-index.json；SHA-256 551077567affc47a00b72ee1d4c3e7e82c14bcb381d91ba7327da3756af17eb9
- D:/CodingProject/Bitget/competitions/floatlib/candidates/f01-d7-research/round8h-20261024T190259Z/astra-aligned-add-host-check.json；SHA-256 66bcabc5ac82cc2a8ec7e02232345d2be751cd14dff4ab08d24592a3339880f3

资源：输入模型0.129秒／3秒上限、21504／25000对；加法模型约0.009秒／2秒上限、1792／2500例。没有本机Lean或重型编译。
