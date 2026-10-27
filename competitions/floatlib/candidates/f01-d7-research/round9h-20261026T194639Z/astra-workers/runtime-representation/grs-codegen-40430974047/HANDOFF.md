# 7737成本决定：暂停大publicADD桥，保留唯一pre-guard再判别

2026-10-27 01:44Z；原7737未改。40430974047/f4211856 statement+两模块重放+7根PASS，但public MainFull逐字B2，未证明/计时新ADD。

- 完整diagnosticEntry接受非零路真1cast+1非尾toBits，无table/FPaddmul/Nat/heap；短gap两magnitude cmp/4cmov/2variable shift，postE和pack仍在。
- 实际6保存+24Bframe，两热栈写保留raw-v/abs-v供postE失败：18d、364；成功不读，失败3fc/400重载。同期B2选中ADD3保存+16Bframe，全tablehit零数据spill，codec为尾跳。zero省cast/call但仍6保存及一热栈写；postE miss会重复原B2计算。
- 表和低指数codec删除有潜力，静态证据不足判实测快慢。旧R16已一cast+toBits且ADD负1.8739，scalarASM缺失；不把死log2或C比较次数当收益。7737不直接启动昂贵public桥，时间UNKNOWN。
- 根新增唯一pre-guard机制见`../grs-pre-guard-frontier/HANDOFF.md`：以T硬界把postE判定前移，目标原输入在codec前死，只保留delta；只存成本备选，不排CI。下一必要C验此明确活跃变量/热spill假设后再谈完整路径计时。
- 详`REVIEW.md`及11个完整代表路径；audit SHA8f248d8acb44850b33f9f0ed5d2ce12f8162e0b3bc072073d210e92a43c36a12。C+ASM绑定实际对象，原ELF未提供；无relocation的尾跳不可跟到打印出的局部下一地址。无本机Lean/Git/CI，token/cacheUNKNOWN。
