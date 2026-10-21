# A17：新公开658可达深链的末跳读取判别

公开658 Rust `1185749453a5abe100106f2e15082eca84521292b7233784a9c2f4562367f3ad`，来源与作者见`references/round26-public-658/source-receipt.json`。本次不使用整源相似函数数量来代表可达性；实际入口为`parse → bulk_parse → p125_row*`。

新可达条件：row9使用U118深度12/lazy64、INS16/stride4，在路由k9/12/17/19/20可达；row2使用depth6/lazy32/L2=1。它是完整链查找的贪心/惰性解析，不是A或D动态规划。相较641只在少数路径调用DX1，这个公开起点扩大了U118消费域；实际公共文件覆盖仍需原生记录。其正式质量改善不能归因于一个函数，也不代表公共逐文件收益或可支付位置。

代码缺口：`u118_walk`在合法候选后总是读`prev[c % W]`，即使本次k==1，或刚接受长度达到nice把k设成1，随后也只会退出；c不在返回best/d中。但LLVM可能已经消除末次无用读取，所以源级观察不足以支持候选或速度。

最小动作：只在临时runner用原官方候选shim和完整release设置（opt3、fat LTO、1 codegen-unit、overflow-checks=yes、panic=unwind、debug断言关闭）编译原658和一份scratch对照。对照只在k<=1时置0，否则保留原next load/递减；不写production candidate，不执行该对照parser。保存row2/row9、walk、bulk的原IR和汇编及精确源，人工定位原末跳是否还读。模板绑定B25已保存官方模板，并与本次runner原版字节规范化比较。

同一批首次用原encoder对658、641和514进行28文件输出/解码。未计时observer保658原token，记录walk深度、真实迭代、common调用、因长度stop和最后一次next link源级机会；与本批658原encoder输入/token身份相符。计数与机器码分别判断，不把源级计数当机器码执行次数。

决定：若原机器码已跳过末次读取，停止该方向。若仍读取且真实覆盖充分，再考虑一份实际同token候选与原协议整轴成本；静态指令减少或大量末跳均不是时间收益。若只有薄弱空间，保留658可达路径/质量资料后换路，不扫深度或nice。

成本上限：两份编译及observer编译/运行分别300秒，建议20分钟外层cap；实际预期分钟级，队列UNKNOWN。原官方源码/flags不修改；不声称生成库等同官方Cargo产物，完整gate与独立确认保持NOT_RUN。剩余开发窗口截止约UTC09:18:52，最后90分钟仍留确认与交付。
