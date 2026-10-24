# Panel4Tail 未接入证明诊断

源SHA `f767631343de86faebe2296cad41aae60d0e2ae57eb3b5748d3308f8389f915b`，238494 B。精确9a229218 B后直接追加9276 B原草稿1afa；父本实际入口及四spec全文保持原字节。panel4-tail.lean是原草稿的精确本地副本。

仅STATEMENT_DIAGNOSTIC。新增namespace测试局部尾数组准备、逐k读取平移、dot10/runDot等价和尾组/行/批次Prefix证明。没有Panel4机器循环投影/Projects实装、没有新generalPanel入口，也不验收新矩阵性能。原9a和R11草稿均保留原字节。

build.py默认dryrun，--write拒绝覆盖，--verify重建核对；完整逆账本恢复9a，原版policy和声明检查通过。所有新Lean/内核/公理/checksum/fullgate初始为NOT_RUN；由Root独占CI，真实错误最多在后续新proof修订中修复，不改冻结源。
