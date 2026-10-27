# ADD独立成本包：D3 carrier，尚未运行

候选`f01-r19-dev-add-cost1`；hook `development-add-cost-audit.py`；stage `add-cost-diagnostic`；输出`add-cost/`。D需接此精确hook名和600秒诊断入口。本任务未改全局allowlist、preparer、官方源、Git或CI。manifest SHA **ada78534accd40265ea375122e72969152af022ffa05c19fa1b671e72eed5ff6**，16个必要组件全部位于本目录并逐项绑定SHA/size。

当前Kernel逐字R的新**d3c550da…/228686B**，以原622d全文为前缀，public四项保持B2。按D后续指示由77377切换而来；原未冻结77377包的22文件快照及完整替换记录见carrier-switch.md。CI12/40430974047的source/Submission+VerifyFull replay/7root仅绑定parent77377；manifest及hook不把这次通过转移到D3。当前D3普通statement、整模块回放、七根、actual C/ASM/成本均NOT_RUN；guarded ADD全域正确性UNKNOWN。

复用已真跑通MUL包的准备、预算、计时和bounded工具，不造新benchmark。control的ADD wrapper调用原Submission.add；guarded的wrapper直接调用现有inline `Submission.R19GRS32Add.guardedAdd Submission.add`。MUL/SUM/BMM回调均为同一个原Submission接口。按D的arity补充要求，两个wrapper用noinline固定入口身份，variant在Suite之前只选择静态函数值；Suite仅调用一次，不把variant Bool放进scalar lambda。driver在任何timer前保存actual-new-main.c并核两者静态arity2、零captures，否则停止计时并保留partial。这个检查不代替完整caller C/ASM语义审查，也不保证control与原MainFull绝对机器码相同。

新目标明确为`R19AddCostMain` / `r19AddCost`，独立`lake -f work/R19AddCostLake.lean build r19AddCost`，原lakefile只读并逐字作为新配置前缀。当前benchFull字段只接受srcDir/root两项；额外traceFlags或其他target选项直接拒绝。实际compile/link/rsp比较只映射MainFull↔R19AddCostMain、benchFull↔r19AddCost路径；其余flags、顺序、依赖不变，旧MUL别名不被normalize。original BenchSuite/contracts/gate/pins/source/objects/binary与依赖前后SHA相同才继续。所有新foreign/Built目标必须仅属于本包两个stems；不扩OWN_STEMS，也不使新目标成为原gate可接纳物。

保持两份已见plan1927003/1927005原字节，每份control/guarded/guarded/control，共8进程；500000 pairs、inner3、156行/152timed、同seed四次checksum、原CPU/原benchmark memory与4GiB build scope全部沿用。保留每条原log、每case ns和全部慢样本。逐项/whole直接求和，只作同binary完整Suite诊断，不是25轮原score、原D、新runner确认或采用。原pass/checksum/drop引用边界不变；输入生成及input/pass closure最终释放仍在原timer外，不把所有物理free成本宣称已测。

请求outer600，注册时刻起唯一absolute deadline580，含原intake/policy/statement；build≤180、measure phase≤300、post tools≤32只是上限，每次再与overall remaining及20/52秒reserve取min。不抬资源、不重试超时，失败保留partial。真实g entry remaining单列记录，不能把旧MUL实际864秒剩余额度说成600已被实测；新包内部580 deadline照常强制，D须正确设置外层入口。

历史验核：CI12全部原件及CI13全部121原件SHA/size/集合一致；CI13实际caller字节、-f准备argv和真实三类flags比较均和继承模板一致。模板只作工程可运行性证据；其source7489与MUL成本不会作为当前ADD通过/速度证据。

本地24项纯Python接线检查PASS：完整fake driver/8ABBA、只让ADD变化的汇总、错误function alias、trace schema、额外traceFlags、arity3捕获、flags/依赖/原构建漂移、checksum/缺行、预算耗尽、hook注册/cleanup等。全部临时fixture已删除，未提交合成C/ASM/timer。final-verification.json核当前D3/16组件/hook/manifest/parent历史和旧快照。

实际CI后必须追真实Main选择的两个静态closure：control为原ADD实现，guarded在wrapper体内含D3 pre-guard/delta逻辑，不能调用diagnosticEntry；MUL/SUM/BMM引用相同；C/带relocation ASM检查真实spill/栈帧/foreigncall及冷fallback。只有此边界成立，原始8进程数据才可解释为ADD成本对照；不把结果升级为public ADD等价或正式分数。
