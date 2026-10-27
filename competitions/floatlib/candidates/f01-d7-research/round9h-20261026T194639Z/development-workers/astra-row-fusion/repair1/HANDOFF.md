# 最小两桥修复，编译仍待验

`Kernel-core-repair1.lean`：249625B，SHA `118d8efc9e8c3d92189913c0aae3d66bca1394a677ec09957174c9d9e97eb1fc`，余6375B。八个新根仍见 `HelperAudit.lean.inc`；父方可继续加原四spec。只有 `pack_low`、`pack_high` 的证明体改变，运行体、公开入口、父本、其余证明均与冻结8ad原字节相同；正逆patch与校验见 `receipt.json`。

CI18 40440668379 原失败仅在两个桥：目标左边已化为 `R19Temporal.packet ...`，右边停在旧 `Vector.ofFn ... .get t`，其中 t 的长度写作 `Fin (blocks n)`。原日志 SHA `ffffa14c0da7dad1e2383633f9f2db595038b4827f0651915d84e5b64908dbf0`；原源/日志保留。其它新声明没有报错不能升级整份源码状态。

修复先以已经接受的 `R19Temporal.pack_get` 重写旧pack读取，再简化新pack及其lane投影；不再把两边同时展开交给ofFn匹配。它直接对应已打印的剩余目标，但本机未跑Lean，新源码 **NOT_RUN**，不能称修复成功。

窄域完整整合保持停止；6155B入口草稿不进入此次探针。D17及性能确认资料未读。D负责重派、完整原件回收、源码/两模块/公理及实际C判别。
