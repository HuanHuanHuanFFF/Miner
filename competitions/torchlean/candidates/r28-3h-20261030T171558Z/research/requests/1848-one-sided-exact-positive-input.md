# B/C独立后续桥：非负输入只偏移W，保住span15 unsigned64域
父sparse-input/ONE-SIDED-POSITIVE-DOT.md与one-sided-result.json完成：a_i>=0（必须实际finite/sign guard），Q=2^(24+sw)，v_i=b_i+Q，则body=Σa_i v_i−QΣa_i。只有一个pixel行和/一次终端修正，不要通用双边的weight行和+n偏移项。a<2^(24+sx)、v<2^(25+sw)，sx+sw<=15就保证p<2^64，保持B原single-product域；一般双偏移需要span<=14。
unsignedcarry必须用C版本，不能复用B sign-extension。父实际raw词counter：X447fffff/3c800001、W3cffffff/3c800001，sx15/sw0/xm=wm120，真实unsignedp18446742424442142720<2^64但>=2^63，错误signedcarry让4200003f变c1ffff82。2548组exactword数组核验、span16拒绝例已留；不是native/全12证明。
Q按输出weight范围准备，不能沿用固定2^31center；Wpos<2^31仍UInt32，X可直接smallNat无Z减法。ΣX在Bpixelprep一次缓存共享cout、末尾纠偏后原qCtx2同尺度bias和rawzero fallback。实际Mobilepw输入来自BNrelu，但kernel不得假设调用者，要guard；NaN/Inf/负非零/稀疏旧路径保留。
这可复用C product_unsigned64，取ex=23+sx、ew=24+sw；原affine_list取input offset0。只是同族精炼后的研究起点，**不修改冻结5ecf/c5、不新增CI或多个variant**。先等本轮成本信号；有新依据再投入producer/字节/全12，不把纸面减少指令当速度。
