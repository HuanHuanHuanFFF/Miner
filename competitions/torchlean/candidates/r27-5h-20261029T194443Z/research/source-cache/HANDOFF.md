# 已合法取得资料的CI输入（只供D选择）

21:51两个榜单metadata及sub27报告的单次GET均403，原始17B为`error code: 1010`，不重试或换UA；latest标UNKNOWN，19:49原件留历史。不是人机验证推断、不是算法失败。

此前19:49合法取得的12/e2c1f1f1和27/f92ee2c9仍在本地private，有明确原始HTTP200回执。`cached_sources.py`只是固定这两个digest的资料编码/接收器，不请求网络、不操作Git/CI/凭据。原文480165B→XZ74220B→98960ASCII字符；单workflow input不够，已按35000/35000/28960分3个private片段。pack/unpack逐字回放PASS，128MiB解码上限、600000B原文上限、无payload路径、先验双SHA后写cache。外部上传尚未执行。

D若现有连接具备权限，可按持续研究资料上传授权，将3片段经stdin设置为repo Actions受保护**技术数据**，不是钱包/登录密钥；只在解码step映射到3个同名env。运行本script `unpack --cache-dir <RUNNER_TEMP>/r27-source-input --receipt <reports>/input-hashes.json`，自有resolve先用exactSHA缓存，缺cache再按原逻辑处理。三part缺失时不要盲调用receiver导致整job失败；先记录missing并继续可运行项。所有source/cache位于reports、Git、依赖cache之外，WholeKernel/C/ASM不公开，原gate/bench/contracts保持字节。

private/parts内3文件及decoded roundtrip cache仅本地，勿暂存。GitHub文档说明repo数据可由文件经stdin设置、workflow通过secrets上下文/env读取，单项48KB；本片段<=35KB。解码后原文不自动受mask保护，禁止打印/上传全源。参考[官方文档](https://docs.github.com/en/actions/how-tos/write-workflows/choose-what-workflows-do/use-secrets)。

仅修一个已观测传输缺陷，不扩账户权限/加paid或private runner、不找用户重复授权；若现有权限不足就走不依赖Conjectures新HTTP的自有研究源。D统一外部操作，R没有写任何repo secret或派CI。精确路径/hash与最小动作见REQUEST.json；本轮截止00:44:43不变。
