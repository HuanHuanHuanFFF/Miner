# compactScales成本复核：支持一次首完整D，收益UNKNOWN

UTC 2026-10-26 22:35:02接手，20分钟上限22:55:02；[checkpoint](checkpoint.md)在前10分钟落盘。只写本目录，无Git/CI/本地Lean，不读未来compact完整D/holdout。

**绑定已核：** 源`9c4e9505702231fdb93f47f8d767ba0b2b0c2ad7ec48d8894b5a53ba87657645`/229293 B，run40410895344/head d6b76ba0；88原件全部重哈希，当前源与原input逐字节相同。helper10根只含3允许公理、完整Submission/VerifyFull重放回执；raw末尾确为`true`和`512`。完整25轮gate和性能仍NOT_RUN，原manifest历史NOT_RUN不改写。

| 问题 | 核对结果 |
|---|---|
| 实际选中链 | MainFull的BENCH_PLAN分支把ADD closure lambda0、MUL closure lambda3交给Bench.Suite.run；对应实际statement-build object ASM已绑定 |
| FloatArray真实读取 | 两个fastOK输入各为`movsd [table+index*8+0x18]`→`cvtsd2ss`→原Float32乘/算术；是连续8B存储的索引读取，不是相邻索引向量化 |
| hot `.data`/重建 | MainFull.c没有data API；两条选中scalar体没有map/mk/check/once调用。Submission.c确有4个FloatArray proof splitter使用data，但各仅prototype+definition，没有选中链引用 |
| valid频率 | ADD每次运算1次；MUL native每次1次；LowScale `ex+ey<128`在ASM先分支，0次。不是每个operand再查一次 |
| fallback | valid=false的旧boxed table arm、fastOK=false的ofBits、结果NaN修复和LowScale路径全部保留；诊断eval为true并未把false arm静态删除 |
| 初始化 | C main先initialize_MainFull→initialize_Submission，后lean_run_main/bench。原boxed table、packed和valid在模块init赋值，带模块guard及once cell；非scalar首次调用时临时生成 |
| 512只做一次？ | **C语义上每个进程**构造512项、valid=true时检查512项；不是整个25轮gate只做一次。初始化函数ASM未捕获，实际native循环/检查次数UNKNOWN；true/512不能证明native恰好执行512次 |

成本边界：启动期map有widen及中间boxed Float64 array，随后float_array_mk；原boxed table仍persistent，packed也persistent，不能称更少总内存或初始化免费。启动先于Bench.Suite.run，缓存官方BenchSuite源码的计时器位于run内部，支持它在kernel ns计时之外；进程启动/分配仍属于总墙钟。未统计未来gate启动多少进程。

对照40395429076的index1源`9f7f96d7…`：ADD/nativeMul/mul Lean运行体与精确B2/622d逐字节相同；旧MainFull C保持两次boxed读取。旧ASM来自Submission.add/nativeMul，新ASM来自选中MainFull lambda0/lambda3，不能冒充同符号计时对照。编译均Lean4.34/293d5d0c、原clang -O3、ffp-contract=off。

**不是“少一层所以更快”：** 每次命中移除一个entry pointer依赖，但增加一次double→float窄化；每个native运算增加flag读取/判断/分支。PIC的flag地址读取+byte测试会抵消部分访存数量下降。例如所列双fastOK ADD直线路径各有8个访存读取，新路另有2个窄化，不能宣称总load更少。收益只能由正常完整D回答。

**给D的决定：** 成本前提未被推翻，值得精确9c4e源的一次首完整D作为表示路线判别；使用原25轮full gate、B2及现有41对照、无observer、原≤.97/正p05门槛。不得预排A/B或由静态指令推算收益；首D失败保留，不换seed恢复。没有建议修改源码/编译参数，也没有发CI。

[JSON](cost-review.json)含101份输入路径/大小/SHA、选中函数行号和分项VERIFIED/UNKNOWN边界；[摘录](selected-excerpts.txt)保留原C/ASM定位。C SHA为Submission `617f03df…`、MainFull `427ab174…`；新MainFull object SHA `4e07dc10…`只由原index作证，raw object本体未保留，不能说本次独立重哈希了object。**这些是diagnostic statement重放对象，绝不是清理后的timed gate对象。**

复验：`python -B competitions/floatlib/candidates/f01-d7-research/round9h-20261026T194639Z/development-workers/anchor-323/compact-scales-review/audit-compact-scales.py`。产物哈希见`MANIFEST.json`。
