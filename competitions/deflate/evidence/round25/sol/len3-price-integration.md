# R25 len3 原码价观察器入口

冻结脚本：`scripts/research-round25-len3-price.py`，SHA-256 `d8253104ad7bd1f0cab87bf8ba21912ec06324bb395b9bb00ef06ac72ee302ee`。本地只执行 Python 文本/哈希/AST/计数 schema 检查；Rust 编译、完整原 token/output/decode 检查均尚未执行。无候选、token 改写、阈值或新路由。

共享 native 路由调用惯例为 **`main()` / 子进程运行本脚本**；不是 `main(root,out)`。环境同旧 observer：`ROUND4_SPEC`、`ROUND4_SPEC_DIR=evidence/round25`、`DEFLATE_ROOT`、`RUNNER_TEMP`、GitHub run/SHA/OS 元数据。预检可调用导入模块的 `preflight(spec)`，或者本地 CLI `--preflight`。

必要批次字段：`r25_len3_price=true`、`native_only=true`、`native_encoder=false`，`gate_candidates=[]`、`extract_candidates=[]`。按 round4 的既有 mandatory controls 保留 probe3/fast3/public432；另外真实 control entries 必须为 combo/public578/public584，名称、目录、双文件 SHA 与脚本 `SOURCES` 完全一致，全部 `control=true`。本脚本不会编辑共享 native/preflight 入口、workflow 或批次 JSON。

**早期预检不依赖本机 `ROOT/sources`。** 它硬检 Git 内的三份 frozen 源、三份原回执与同输入身份、route 插桩可逆性、计数 schema；只有本机阅读副本实际存在时才检查规范化 codec 文本。不在 runner 早期预检生成 native codec，不因缺少阅读副本报错。已经用精确路径的 `Path.is_file=False` 模拟缺失，并与正常预检逐源比对一致。

`main()` 在 prepare 以后只用 `DEFLATE_ROOT/validator/measure/src/{deflate.rs,token.rs}`，必须严格等于 Linux 原字节 SHA `172c240014f65d5e2762c1287e4982dd1cd426f2999f74e17011e05f2dc5fdec` / `8bf5d962324b3a0890f3c75f713198be086c4b0659797c24b8b976978cea4917`。价格 appendix 从实际原 `write_block` 复制完整 table prep，再比固定 SHA `52789ab5a4533ecf3c412002e70e55b447f840e4c5be9a3f1ce78256ed6c5d82`；不放宽 main 的真实身份检查。原 codec/token 与 repo 原来源文件只读。

观察范围和验收：

- 三份 parser 对 28 个固定输入各完整解析一次 frozen、一次 observed。Observed 只在原 p125/p135 row 入口加原子计数；没有额外分类扫描。两者逐 token 相同、独立 Rust 解码相同才继续。顶层没有 row 调用时记 `fallback_without_top_row`；复合 row11/13 不猜内部分支引擎。
- 原 trusted encoder 与只追加观察函数的临时副本 encode 字节必须相同。所有84组实际 token/output/input SHA、长度、token数与冻结 native/原协议回执对齐，再独立 zlib decode。
- 原 block 边界使用固定16384 tokens。Huffman 表构造复制原逻辑，stored/fixed/dynamic 选择保留原条件。Stored 不含 match；该类型仍被单列，避免将它报告成 fixed/dynamic。
- 每个原块、文件、原 source:row 分组及来源总计，记录257项计数：完整 token/覆盖、len3已知/缺失 literal码价、胜负/相等次数、正负 bits差，以及30距离码的同类分项。分组附原 row body 与其 SHA。缺失码价属于 UNKNOWN，不参与已知正负 bits差；len3已知亏损覆盖是该计数×3。
- 原块码价仅用于观察，不能解释为改变 token 后仍保持的最终字节收益；模型 header、block split、频率、类型会随改写改变。没有实际 token 改写，更没有新 parser 或性能结论。

运行上限：一次 Rust compile 300s，一次完整 untimed run 240s；共享 job 总预算由 root 按12公共runner分钟控制。没有 asm/profile/正式 gate 扩张。

runner 输出目录：`$RUNNER_TEMP/round4-receipts/r25-len3-price/`；核心 `counts.json`，另有 compile/run日志、原表准备appendix、实际 route observer源与完整 harness。开始与异常状态会保存 `STARTED` / `FAILED_OR_INCOMPLETE`；**只有84组token/output归档绑定、双实现对照、独立decode和计数一致性全通过才输出 `VERIFIED_UNTIMED_ORIGINAL_TOKEN_OUTPUT_ROUTE_AND_LEN3_PRICE_OBSERVER`**。临时 token/deflate spool 留在 runner build 目录，不改原语料。

已执行本地证据：`len3-price-preflight.json`；额外 AST、20个LP常量定义/引用、占位符、错误 native_encoder batch拒绝、sources缺失早期预检模拟均通过。它们不能替代 Rust 编译或原生验收。当前等待 root 唯一授权 dispatch，后续实现仍需按实际结果另行决定。
