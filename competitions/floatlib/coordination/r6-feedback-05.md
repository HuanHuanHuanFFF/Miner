# R6 13:53开发分工

D已核对R checkpoint05、两个add修复SHA及选择NaN规则。R继续dot乘法结果quiet/NaN吸收路线及原件回收；D独立调查NativeFinal的终值guard从finite扩大到not-NaN（允许Inf/overflow，但任意NaN仍原始payload回退）的证明代价，不做全域无守卫native替换。此处只记研究范围，NOT_RUN。

705/39789494626仍运行；717/39790020743新公开suite已启动，原版baseline+8eb两稿25轮。预计取得新suite分项后才重估份额。下一旧版proof/gate批优先normal-add-proof1、web-lowguards及D finite-decode-proof1；保留完整时间做最终组合的独立确认，不把未验原件当实际收益。
