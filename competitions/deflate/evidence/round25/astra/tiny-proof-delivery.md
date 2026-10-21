# tinyPC8 proof1 交付边界

新目录：`candidates/r25-astra-tiny-pc8-proof1`。

- Rust SHA-256：`5c20b99cf52ac8e2f047b4e2e83be974b1f9b1f21b23d54ccccb25c58b891f00`，与root候选逐字相同。
- Lean SHA-256：`3bd53694534c0114453a95c2f120d743fde3af233de88c00e1d5c30fe05ccdb8`，410,352B。
- 生成器：`scripts/build-round25-astra-tiny-proof.py`。
- 运行入口与原提取hash：`tiny-proof-entry.json`、`tiny-proof-build-audit.json`。

依据真实run38130286911提取：旧定义只变row12；新增14个tiny定义中，13个在函数名映射后与父版相同，唯一实质差异是record外层固定8次头部插入。生成器最初把模块末尾 `end slot` 误计入最后一个函数，实际差异仅为定义排序造成的footer归属；去掉独立模块结束行后再逐定义核对通过。这是分析器边界修正，不是改动Rust或放宽实际函数比较。

Lean新增9个局部定理。两个record循环、lazy循环和两个literal尾循环通过显式定义展开复用父版证明；record外层和主循环沿用已验收HeadBound/Dec模板。row12改接新的run1定理。原 `bulk_parse_spec`、`parse_spec`尾部逐字保留，没有新公理、sorry或admit，原运行时和证明限制未改变。

**已执行：** builder AST、证明文本构造、真实提取定义核对、精确Rust身份、最终双文件hash和限定diff检查。

**未执行：** 新Lean编译、原LZ77 obligation、公理白名单及公共roundtrip完整gate。本子线程没有本地Rust/Lean编译、CI派发、提交或推送。主线程负责原版完整gate；只有精确pair收到成功回执，才可将本状态改为已验收。
