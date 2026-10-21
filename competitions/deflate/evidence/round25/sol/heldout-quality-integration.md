# R25 合成质量诊断入口

脚本 `scripts/research-round25-heldout-quality.py` 已冻结，SHA `3a26b6df478fbe3986a952bac3f45f41e9fdaf30f5c213abd294f8aae5ce7ed3`；生成器标记区 SHA `e3a29e3884f7f6091b71ce3f59c4c92f3333ed5f0780908cf7e35692ec8b078d`。本地仅做 Python/文本/生成/schema/input hash 检查，Rust、encoder/decode与任何质量输出尚未执行。

预声明先于任何生成/编码结果写入 `heldout-quality-predeclared.json`。最初24样本的长度12000/196608在静态检查中发现 end4均不覆盖：12000走row12，196608只fallback。root在任何生成结果前批准改为24主样本=三族×12000/400000×固定seed0–3，另保留每族seed0的196608作为3个inactive控制。这项失败的覆盖假设和修订原因保留，既有源码路由未改。

矩阵和全部27 input SHA 已冻结在 `heldout-quality-inputs.json`：主样本4,944,000 B，控制589,824 B，合计5,533,824 B。27 SHA各不相同；每family/seed长短来自同一个确定性unit stream，末端截断只丢不完整UTF8字节再以ASCII空格补齐。同stream/prefix相关性不作独立随机抽样解释。内容全部自写JSON配置样式、Markdown/日志、C样式模板，未读取官方tiny-config或任何输入语料、秘密、下载数据。

共享入口惯例：`main()` / 子进程本脚本；`preflight(spec)`只读取Git内冻结三份源、声明/输入manifest并复算轻量生成哈希，不读取`ROOT/sources`。本地CLI `--preflight`只首次创建输入哈希manifest；已有manifest必须逐字段相同，不能覆盖换样本。runtime `--generate <dir>`只在GitHub/Linux允许，生成目录由main指定到本次runner产物目录。

批次：`r25_heldout_quality=true`、`native_only=true`、`native_encoder=false`，gate/extract为空；三份control entries精确名为combo/end4/tiny-pc8，path/双SHA匹配脚本。root保留旧 mandatory controls并接共享native/preflight，本脚本没有编辑共享入口或workflow。

prepare后，main只从`DEFLATE_ROOT`读原encoder/token，严格绑定原字节SHA `172c240014f65d5e2762c1287e4982dd1cd426f2999f74e17011e05f2dc5fdec` / `8bf5d962324b3a0890f3c75f713198be086c4b0659797c24b8b976978cea4917`。encoder不插桩、不替换。三份parser各正常解析和只加原row/fallback入口计数的临时观察解析逐token一致；不是额外重跑分类。源插桩可逆恢复原字节，本地已检查。

运行阶段上限为生成60s、Rust compile300s、untimed run240s；root总公共runner上限12min保持不变。输入生成本身另有每例20000unit硬上限，矩阵/字节长度固定。无warmup、计时重复、CPU剖析或榜单计算。

输出目录 `$RUNNER_TEMP/round4-receipts/r25-heldout-quality/`：

- `quality.json` 包括完整81组（三源×27例）bytes/tokens/source/input/token/output SHA、实际row、各例相对combo得失与所有回退，24主/3inactive分列。
- 每份组件的`component_active_cases`另列：end4主400000的12例、tinyPC主12000的12例；不能将另一半同字节样本当经过改动机制的验证。这个标记表示进入改动所属row，不保证内部新guard在每例都产生新增offer。
- 实际路由必须为12000→row12、400000→row1、196608→fallback。控制token/output必须与combo相同；其他质量正负不作为失败，也不按结果改样本。
- 原输入`.utf8`与`input-manifest.json`、harness、临时route observer源、generate/compile/run日志保留。开始/失败也写状态与错误，不将缺失结果写零。

只有81组原encoder输出的native Rust decode、独立zlib decode、frozen/observed完整token身份、运行时重新生成的全部冻结input SHA、预声明route覆盖和源未修改全通过，才写 `VERIFIED_UNTIMED_27_SYNTHETIC_CASES_ORIGINAL_ENCODER_DECODE_AND_ROUTE_PARITY`。它是**自建固定合成域外诊断**，不是真实私有heldout/stage2、官方大小轴、收入、成功概率或独立原协议确认。

本地检查记录：`heldout-quality-preflight.json` 与 `heldout-quality-preflight-extra.json`。AST、UTF8/长度/27 distinct SHA、12个长短同流前缀、三源原row/fallback可逆插桩、错误flag拒绝，以及强禁止`ROOT/sources`读取的early-preflight模拟均通过；实际Rust/native仍NOT_RUN。
