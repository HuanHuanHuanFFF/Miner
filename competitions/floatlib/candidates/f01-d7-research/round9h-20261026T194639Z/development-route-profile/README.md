# 可直接接入的statement-only路由诊断包

候选：`f01-r19-dev-route-profile1`，Kernel逐字为保留622d/226829B。manifest已绑定R19根`development-route-audit.py`及8个本目录运行组件；ci-diagnostics现有allowlist可导入该名字，无执行文件改动。

hook只追加`route-collection`，执行在原statement成功后；不调用kernel replay、axioms或score。source的既有完整gate证据不重放，这次结果始终`diagnostic_only=true/full_gate=false`。

运行组件：driver.py、RouteLabels.lean、legacy-whole-parser.py、parser-provenance.json、两份seen plan、request.json、request-original-240.json。hook按`Path(__file__).parent/development-route-profile`加载，先核manifest每项大小/SHA及request/plan/parser；不静默回退。旧R13 parser的HEAD Git blob `abc3d912dac66d1b2970ba1a7e5288a3d51446a4`和工作区字节均核对，其SHA256为`8726e1e5debcfc335a11585d2a432a74ef379727fa393c686abecf631fedd23e`，新包副本相同。

request采集cap从240降为60秒。原240配置以LF参考副本保存；原worker字节保持不变，其精确SHA及可恢复的base64字节保留在package-receipt.json。所有运行文本使用LF，避免Git文本规范化后哈希漂移。

内层ci-diagnostics默认120秒、外层nested statement180秒。hook读取本Linux进程age，将实际采集cap缩为`min(60,120-age-8)`，留8秒回执；余量不足则明确拒绝启动。driver从入口起计时，所有子调用都取remaining的较小值，结束前再次核deadline。超时保留已落盘progress、case rows和结果；TimeoutExpired提供的stdout保存为原始partial，缺失时明确标记不可用。外层硬杀只能保证此前已落盘文件，不宣称拿到未返回的stdout。

独立metadata进程和原benchFull timer保持既有设计：固定已见1927003/5，各两个原binary进程，raw case ns直接相加，不乘work/MAC。原binary/C/object前后身份检查保留。输出销毁范围仍等待实际BenchSuite C生命周期复核，采集成功不升级该声明。

`validation-receipt.json`记录语法、8组件、hook导入、唯一stage、4个错误manifest拒绝及预算边界检查。未调用stage callback、Lean或benchmark，运行仍NOT_RUN。原worker资料及官方执行文件未改；无Git写入、推送、CI或新增agent。由父会话独立检查后实际派发。
