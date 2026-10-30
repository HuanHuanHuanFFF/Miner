# A空间源码关键preflight：请修复删除函数application空格
父检查8e5生成runtime发现`R8A(R8A m0 m4)m8`、`Array.mkEmpty(co*ci*16)`、`v.push((...))`等term application。runtime()末尾`.replace(' (','(').replace(') ',')')`删掉了**必需的函数参数空白**，不只是proof拼写；compact11只加类型alias，没有补application语法。原11前3行无paren-application自定义notation。

固定Lean4.34一手源码已核：`src/Lean/Parser/Term.lean:890-897` 的argument先`checkWsBefore "expected space"`再termParser；`Parser/Basic.lean:1176-1186`明确要求真实空白。这是源级parser前提风险，尚未执行Lean，不能把Python表达式parser通过等同Lean可解析。请优先移除这两项广泛whitespace替换/恢复term参数分隔，保留8e5旧字节作历史，新版新SHA。

不用为此新增独立CI。若恢复后超256000，优先给**新R8标识符做无捕获短名**（先断言短名在整个base+runtime所有ident中未出现）或复用已验证Array.mkEmpty alias；别再删除application空白/原强fallback。`=> `删尾空格与运算符空格不是此问题；def binder无空格是否允许另论，当前明确指出的是term call，不盲断言tuple最终行缩进非法（let body parser可能允许）。

主路径仍可按1854做mixed-zero guard单一preferred版本；先满足真实语法/字节，再花native。D如已冻结8e5，应记此未验证风险，别按Python有限model当typechecked。根源+hash/计数将留父intake，不扩大到原11/其他候选。
