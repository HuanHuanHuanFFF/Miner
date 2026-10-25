# R14：ADD+MUL组合已进入256K，静态依赖裁剪请独立复核
时间：2026-10-25T01:08:10.987563+00:00
关联：005813实际ADD字节审查；R14不改截止时间
类型：协作请求 / 源码交付
摘要：f01-r14-dev-allword-combined1，393473afe5cbcd5a360a30eff7e6729f6f591a7a427aedd101ad6ef9c8bf9c7c，252500B，余3500B。真实public add=a234窄域整数路线，真实public mul=5556纯整数路线，SUM原样，BMM thin-cache+p8；完整gate/性能NOT_RUN。
容量路径：先精确复用已定义rounded/carry/mantissa/normal-round/rawdecode/ex/sign，合成277331B的draft（非候选）；三轮显式无引用plain theorem裁8794B，再移除含doc的未用round_normal_decode1320B；局部名字依赖图把四入口/四spec/eq/reference与注册属性、instance、structure等设根，保守解析namespace与suffix/dot后缀，找出41个不可达声明（含递归旧helper岛）14631B。全程保留每阶段源、切片和hash，不把静态图当Lean接受或动态等价证明。
结构实错已处理：共同raw_normal_decode移除后，复制的doc-comment原先悬在end前（分析稿保留）；新候选删去这段无归属的重复doc86B。没有删版权/作者信息，也没有改剩余运行体。
需要研究：下一自然检查点，独立核对graph裁剪是否漏了隐式/qualified依赖、四公开入口放置和共用片段名；优先找明确反例/缺引用，不另起运行体。可以检查development-local-dependency-graph1.json中41项及其source/removed精确坐标；若发现保守性问题，在astra-*记录，开发按新版本恢复原切片。尤其别只据“token出现一次”宣称编译通过。
证据：当前目录下development-compose-add-mul-draft.py、development-proof-fixedpoint-inventory.py、development-unreferenced-declarations-inventory.py、development-local-dependency-graph.py、development-build-allword-combined.py及各JSON。父源a234/d2b8原字节不变，new Kernel独立。
公开权限/CI：仍待人类新范围答复，没有push/dispatch；现有5个own运行全部终态收齐。计划1425012保留，后续新完整候选用另一个本地冻结请求。
结论状态：源码大小/派生字节VERIFIED，Lean正确性与真实性能UNKNOWN。
