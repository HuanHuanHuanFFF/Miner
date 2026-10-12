define void @_RNvCsera0HrlzTQN_14r26_a_original9a_dp_pass(ptr noalias nofree noundef nonnull readonly captures(none) %s.0, i64 noundef range(i64 0, -9223372036854775808) %s.1, ptr noalias nofree noundef readonly align 8 captures(none) dereferenceable(24) %mp, ptr noalias nofree noundef readonly align 8 captures(none) dereferenceable(24) %mb, i64 noundef %p0, i64 noundef %pe, ptr noalias nofree noundef readonly align 4 captures(none) dereferenceable(1024) %lit, ptr noalias nofree noundef readonly align 4 captures(none) dereferenceable(2048) %lc, ptr noalias nofree noundef readonly align 4 captures(none) dereferenceable(128) %dc, ptr noalias nofree noundef readonly align 8 captures(none) dereferenceable(24) %cost, ptr noalias nofree noundef readonly align 8 captures(none) dereferenceable(24) %ch) unnamed_addr #0 !guid !2301 {
start:
  %0 = getelementptr inbounds nuw i8, ptr %cost, i64 16
  %cl = load i64, ptr %0, align 8, !noundef !149
  %_192 = icmp ult i64 %cl, 2305843009213693952
  tail call void @llvm.assume(i1 %_192)
  %_12 = icmp ult i64 %pe, %cl
  br i1 %_12, label %bb1, label %bb74

bb74:                                             ; preds = %_RNvCsera0HrlzTQN_14r26_a_original14a_store_choice.exit, %bb76, %bb3, %bb1, %start
  ret void

bb1:                                              ; preds = %start
  %1 = getelementptr inbounds nuw i8, ptr %mp, i64 16
  %_14 = load i64, ptr %1, align 8, !noundef !149
  %_193 = icmp ult i64 %_14, 2305843009213693952
  tail call void @llvm.assume(i1 %_193)
  %_13 = icmp samesign ult i64 %pe, %_14
  %_15 = icmp samesign ule i64 %pe, %s.1
  %or.cond = and i1 %_15, %_13
  br i1 %or.cond, label %bb3, label %bb74

bb3:                                              ; preds = %bb1
  %2 = getelementptr inbounds nuw i8, ptr %ch, i64 16
  %_18 = load i64, ptr %2, align 8, !noundef !149
  %_194 = icmp ult i64 %_18, 2305843009213693952
  tail call void @llvm.assume(i1 %_194)
  %_17.not = icmp samesign ugt i64 %pe, %_18
  br i1 %_17.not, label %bb74, label %bb76

bb76:                                             ; preds = %bb3
  %3 = getelementptr inbounds nuw i8, ptr %cost, i64 8
  %_199 = load ptr, ptr %3, align 8, !nonnull !149, !noundef !149
  %4 = shl nuw nsw i64 %pe, 2
  %scevgep = getelementptr nuw i8, ptr %_199, i64 %4
  %5 = xor i64 %pe, -1
  %6 = add nsw i64 %cl, %5
  %umin = tail call i64 @llvm.umin.i64(i64 %6, i64 258)
  %7 = shl nuw nsw i64 %umin, 2
  %8 = add nuw nsw i64 %7, 4
  tail call void @llvm.memset.p0.i64(ptr noundef nonnull align 4 dereferenceable(1) %scevgep, i8 0, i64 %8, i1 false)
  %9 = getelementptr inbounds nuw i8, ptr %mp, i64 8
  %_204 = load ptr, ptr %9, align 8, !nonnull !149, !noundef !149
  %_33134 = icmp ugt i64 %pe, %p0
  br i1 %_33134, label %bb12.lr.ph, label %bb74

bb12.lr.ph:                                       ; preds = %bb76
  %_30 = getelementptr inbounds nuw [4 x i8], ptr %_204, i64 %pe
  %_29 = load i32, ptr %_30, align 4, !noundef !149
  %10 = zext i32 %_29 to i64
  %11 = getelementptr inbounds nuw i8, ptr %cost, i64 8
  %_214 = load ptr, ptr %11, align 8, !nonnull !149
  %12 = getelementptr inbounds nuw i8, ptr %mb, i64 16
  %_59 = load i64, ptr %12, align 8
  %_216 = icmp ult i64 %_59, 2305843009213693952
  %13 = getelementptr inbounds nuw i8, ptr %mb, i64 8
  %_221 = load ptr, ptr %13, align 8, !nonnull !149
  %14 = getelementptr inbounds nuw i8, ptr %ch, i64 8
  %ch.val = load ptr, ptr %14, align 8
  %15 = trunc i64 %pe to i9
  %16 = add i64 %pe, 1
  %17 = add i64 %pe, 2
  %18 = add i9 %15, -3
  br label %bb12

bb12:                                             ; preds = %bb12.lr.ph, %_RNvCsera0HrlzTQN_14r26_a_original14a_store_choice.exit
  %indvar175 = phi i64 [ 0, %bb12.lr.ph ], [ %indvar.next176, %_RNvCsera0HrlzTQN_14r26_a_original14a_store_choice.exit ]
  %indvar = phi i9 [ 0, %bb12.lr.ph ], [ %indvar.next, %_RNvCsera0HrlzTQN_14r26_a_original14a_store_choice.exit ]
  %i.sroa.0.0138 = phi i64 [ %pe, %bb12.lr.ph ], [ %19, %_RNvCsera0HrlzTQN_14r26_a_original14a_store_choice.exit ]
  %e.sroa.0.0137 = phi i64 [ %10, %bb12.lr.ph ], [ %j0, %_RNvCsera0HrlzTQN_14r26_a_original14a_store_choice.exit ]
  %xl.sroa.0.0136 = phi i64 [ 0, %bb12.lr.ph ], [ %xl.sroa.0.1, %_RNvCsera0HrlzTQN_14r26_a_original14a_store_choice.exit ]
  %xd.sroa.0.0135 = phi i64 [ 0, %bb12.lr.ph ], [ %xd.sroa.0.1, %_RNvCsera0HrlzTQN_14r26_a_original14a_store_choice.exit ]
  %reass.sub.neg = sub i64 %pe, %indvar175
  %19 = add nsw i64 %i.sroa.0.0138, -1
  %_210 = icmp ult i64 %19, %_14
  br i1 %_210, label %bb77, label %panic5

bb77:                                             ; preds = %bb12
  %_37 = getelementptr inbounds nuw [4 x i8], ptr %_204, i64 %19
  %_36 = load i32, ptr %_37, align 4, !noundef !149
  %j0 = zext i32 %_36 to i64
  %_215 = icmp samesign ult i64 %i.sroa.0.0138, %cl
  br i1 %_215, label %bb78, label %panic6

panic5:                                           ; preds = %bb12
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %19, i64 noundef %_14, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_dc0f0c2638b46b144204a9d85f95981f) #29
  unreachable

bb78:                                             ; preds = %bb77
  %_40 = getelementptr inbounds nuw [4 x i8], ptr %_214, i64 %i.sroa.0.0138
  %nxt = load i32, ptr %_40, align 4, !noundef !149
  %bias = sub i32 1048576, %nxt
  %_50 = icmp ult i64 %19, %s.1
  br i1 %_50, label %bb13, label %panic7

panic6:                                           ; preds = %bb77
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %i.sroa.0.0138, i64 noundef %cl, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_19c67fa86284eca1bd1317a90cd36415) #29
  unreachable

bb13:                                             ; preds = %bb78
  %20 = getelementptr inbounds nuw i8, ptr %s.0, i64 %19
  %_48 = load i8, ptr %20, align 1, !noundef !149
  %_47 = zext i8 %_48 to i64
  %21 = getelementptr inbounds nuw [4 x i8], ptr %lit, i64 %_47
  %_46 = load i32, ptr %21, align 4, !noundef !149
  %_45 = shl i32 %_46, 9
  %22 = add i32 %_45, 536870912
  %23 = add nuw nsw i64 %i.sroa.0.0138, 1
  tail call void @llvm.assume(i1 %_216)
  %e.sroa.0.1 = tail call i64 @llvm.umin.i64(i64 %e.sroa.0.0137, i64 %_59)
  %_60119 = icmp samesign ugt i64 %e.sroa.0.1, %j0
  br i1 %_60119, label %bb79.preheader, label %bb39

bb79.preheader:                                   ; preds = %bb13
  %24 = add i64 %reass.sub.neg, 509
  %25 = trunc i64 %24 to i9
  br label %bb79

panic7:                                           ; preds = %bb78
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %19, i64 noundef %s.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_ca46e1b1bfeb2b3ad3d0527f2a76cb9d) #29
  unreachable

bb39:                                             ; preds = %bb32, %bb13
  %pd.sroa.0.0.lcssa = phi i64 [ 0, %bb13 ], [ %pd.sroa.0.1, %bb32 ]
  %prev.sroa.0.0.lcssa = phi i64 [ %23, %bb13 ], [ %prev.sroa.0.1, %bb32 ]
  %bd.sroa.0.0.lcssa = phi i32 [ 0, %bb13 ], [ %spec.select87, %bb32 ]
  %best.sroa.0.0.lcssa = phi i32 [ %22, %bb13 ], [ %spec.select88, %bb32 ]
  %_126 = add nsw i64 %xl.sroa.0.0136, 1
  %._126 = tail call i64 @llvm.umin.i64(i64 %_126, i64 258)
  %_129 = icmp ult i64 %xl.sroa.0.0136, 3
  %26 = add nsw i64 %xd.sroa.0.0135, -1
  %27 = icmp uge i64 %26, %19
  %or.cond84 = select i1 %_129, i1 true, i1 %27
  br i1 %or.cond84, label %bb68, label %bb45

bb68:                                             ; preds = %bb48, %bb45, %bb39
  %28 = sub nsw i64 %prev.sroa.0.0.lcssa, %19
  br label %bb69

bb45:                                             ; preds = %bb39
  %_136 = add nuw nsw i64 %19, %._126
  %_135 = icmp ugt i64 %_136, %prev.sroa.0.0.lcssa
  br i1 %_135, label %bb47, label %bb68

bb47:                                             ; preds = %bb45
  %_145 = sub nsw i64 %19, %xd.sroa.0.0135
  %_148 = icmp ult i64 %_145, %s.1
  br i1 %_148, label %bb48, label %panic10

bb48:                                             ; preds = %bb47
  %29 = getelementptr inbounds nuw i8, ptr %s.0, i64 %_145
  %_144 = load i8, ptr %29, align 1, !noundef !149
  %_140 = icmp eq i8 %_48, %_144
  br i1 %_140, label %bb49, label %bb68

panic10:                                          ; preds = %bb47
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_145, i64 noundef %s.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_fc650c7e3ae0d766b2a9643cadc69347) #29
  unreachable

bb49:                                             ; preds = %bb48
  %30 = trunc nuw nsw i64 %xd.sroa.0.0135 to i32
  %x = add nsw i32 %30, -1
  %_233 = icmp ult i32 %x, 4
  br i1 %_233, label %bb50, label %bb83

bb69:                                             ; preds = %bb59, %bb68
  %bd.sroa.0.1 = phi i32 [ %spec.select, %bb59 ], [ %bd.sroa.0.0.lcssa, %bb68 ]
  %best.sroa.0.1 = phi i32 [ %spec.select85, %bb59 ], [ %best.sroa.0.0.lcssa, %bb68 ]
  %xd.sroa.0.1 = phi i64 [ %xd.sroa.0.0135, %bb59 ], [ %pd.sroa.0.0.lcssa, %bb68 ]
  %xl.sroa.0.1 = phi i64 [ %._126, %bb59 ], [ %28, %bb68 ]
  %_9.i = lshr i32 %best.sroa.0.1, 9
  %_8.i = add i32 %nxt, -1048576
  %value.i = add i32 %_8.i, %_9.i
  %_12.i = getelementptr inbounds nuw [4 x i8], ptr %_214, i64 %19
  store i32 %value.i, ptr %_12.i, align 4
  %_18.i = icmp samesign ult i64 %19, %_18
  br i1 %_18.i, label %bb11.i, label %_RNvCsera0HrlzTQN_14r26_a_original14a_store_choice.exit

bb11.i:                                           ; preds = %bb69
  %bl.i = and i32 %best.sroa.0.1, 511
  %_15.i = icmp samesign ugt i32 %bl.i, 2
  %_17.i = shl nsw i32 %bd.sroa.0.1, 9
  %_16.i = add i32 %_17.i, 512
  %31 = or disjoint i32 %_16.i, %bl.i
  %tok.sroa.0.0.i = select i1 %_15.i, i32 %31, i32 0
  call void @llvm.assume(i1 true) [ "nonnull"(ptr %ch.val) ]
  %_20.i = getelementptr inbounds nuw [4 x i8], ptr %ch.val, i64 %19
  store i32 %tok.sroa.0.0.i, ptr %_20.i, align 4
  br label %_RNvCsera0HrlzTQN_14r26_a_original14a_store_choice.exit

_RNvCsera0HrlzTQN_14r26_a_original14a_store_choice.exit: ; preds = %bb69, %bb11.i
  %_33 = icmp ugt i64 %19, %p0
  %indvar.next = add i9 %indvar, 1
  %indvar.next176 = add i64 %indvar175, 1
  br i1 %_33, label %bb12, label %bb74

bb83:                                             ; preds = %bb49
  %_235 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %x, i1 true)
  %_234 = shl nuw nsw i32 %_235, 1
  %_239 = sub nuw nsw i32 30, %_235
  %_238 = lshr i32 %x, %_239
  %_237 = and i32 %_238, 1
  %_234.masked = and i32 %_234, 30
  %32 = or disjoint i32 %_237, %_234.masked
  %33 = xor i32 %32, 30
  br label %bb50

bb50:                                             ; preds = %bb83, %bb49
  %_159.sroa.0.0 = phi i32 [ %33, %bb83 ], [ %x, %bb49 ]
  %_162 = icmp ult i64 %_136, %cl
  br i1 %_162, label %bb53.lr.ph, label %bb59

bb59:                                             ; preds = %bb53, %middle.block, %bb50
  %mbest1.sroa.0.0 = phi i32 [ -1, %bb50 ], [ %69, %middle.block ], [ %spec.select86, %bb53 ]
  %_186 = icmp ult i32 %mbest1.sroa.0.0, %best.sroa.0.0.lcssa
  %spec.select = select i1 %_186, i32 %x, i32 %bd.sroa.0.0.lcssa
  %spec.select85 = tail call i32 @llvm.umin.i32(i32 %mbest1.sroa.0.0, i32 %best.sroa.0.0.lcssa)
  br label %bb69

bb53.lr.ph:                                       ; preds = %bb50
  %_157 = zext nneg i32 %_159.sroa.0.0 to i64
  %34 = getelementptr inbounds nuw [4 x i8], ptr %dc, i64 %_157
  %_156 = load i32, ptr %34, align 4, !noundef !149
  %35 = add i64 %prev.sroa.0.0.lcssa, 1
  %_165 = sub nsw i64 %35, %19
  %36 = trunc i64 %_165 to i32
  %_173 = add i32 %_156, %bias
  %37 = tail call i64 @llvm.umax.i64(i64 %_136, i64 %35)
  %38 = sub i64 %37, %prev.sroa.0.0.lcssa
  %min.iters.check = icmp ult i64 %38, 8
  br i1 %min.iters.check, label %bb53.preheader, label %vector.scevcheck

vector.scevcheck:                                 ; preds = %bb53.lr.ph
  %umax = tail call i64 @llvm.umax.i64(i64 %_136, i64 %35)
  %39 = xor i64 %prev.sroa.0.0.lcssa, -1
  %40 = add i64 %umax, %39
  %41 = trunc i64 %prev.sroa.0.0.lcssa to i9
  %42 = trunc i64 %40 to i9
  %43 = add i9 %indvar, %41
  %44 = sub i9 %18, %43
  %45 = icmp ult i9 %44, %42
  %46 = icmp ugt i64 %40, 511
  %47 = or i1 %45, %46
  br i1 %47, label %bb53.preheader, label %vector.ph

vector.ph:                                        ; preds = %vector.scevcheck
  %n.vec = and i64 %38, -8
  %48 = add i64 %35, %n.vec
  %49 = trunc i64 %n.vec to i32
  %50 = add i32 %36, %49
  %broadcast.splatinsert = insertelement <4 x i32> poison, i32 %_173, i64 0
  %broadcast.splat = shufflevector <4 x i32> %broadcast.splatinsert, <4 x i32> poison, <4 x i32> zeroinitializer
  %broadcast.splatinsert167 = insertelement <4 x i32> poison, i32 %36, i64 0
  %broadcast.splat168 = shufflevector <4 x i32> %broadcast.splatinsert167, <4 x i32> poison, <4 x i32> zeroinitializer
  %induction = add <4 x i32> %broadcast.splat168, <i32 0, i32 1, i32 2, i32 3>
  %51 = getelementptr [4 x i8], ptr %_214, i64 %35
  br label %vector.body

vector.body:                                      ; preds = %vector.body, %vector.ph
  %index = phi i64 [ 0, %vector.ph ], [ %index.next, %vector.body ]
  %vec.phi = phi <4 x i32> [ splat (i32 -1), %vector.ph ], [ %66, %vector.body ]
  %vec.phi169 = phi <4 x i32> [ splat (i32 -1), %vector.ph ], [ %67, %vector.body ]
  %vec.ind = phi <4 x i32> [ %induction, %vector.ph ], [ %vec.ind.next, %vector.body ]
  %step.add = add <4 x i32> %vec.ind, splat (i32 4)
  %52 = add i64 %_165, %index
  %53 = and i64 %52, 511
  %54 = getelementptr [4 x i8], ptr %51, i64 %index
  %55 = getelementptr inbounds nuw i8, ptr %54, i64 16
  %wide.load = load <4 x i32>, ptr %54, align 4
  %wide.load170 = load <4 x i32>, ptr %55, align 4
  %56 = getelementptr inbounds nuw [4 x i8], ptr %lc, i64 %53
  %57 = getelementptr inbounds nuw i8, ptr %56, i64 16
  %wide.load171 = load <4 x i32>, ptr %56, align 4
  %wide.load172 = load <4 x i32>, ptr %57, align 4
  %58 = add <4 x i32> %broadcast.splat, %wide.load
  %59 = add <4 x i32> %broadcast.splat, %wide.load170
  %60 = add <4 x i32> %58, %wide.load171
  %61 = add <4 x i32> %59, %wide.load172
  %62 = shl <4 x i32> %60, splat (i32 9)
  %63 = shl <4 x i32> %61, splat (i32 9)
  %64 = or <4 x i32> %62, %vec.ind
  %65 = or <4 x i32> %63, %step.add
  %66 = tail call <4 x i32> @llvm.umin.v4i32(<4 x i32> %64, <4 x i32> %vec.phi)
  %67 = tail call <4 x i32> @llvm.umin.v4i32(<4 x i32> %65, <4 x i32> %vec.phi169)
  %index.next = add nuw i64 %index, 8
  %vec.ind.next = add <4 x i32> %vec.ind, splat (i32 8)
  %68 = icmp eq i64 %index.next, %n.vec
  br i1 %68, label %middle.block, label %vector.body, !llvm.loop !2302

middle.block:                                     ; preds = %vector.body
  %rdx.minmax = tail call <4 x i32> @llvm.umin.v4i32(<4 x i32> %66, <4 x i32> %67)
  %69 = tail call i32 @llvm.vector.reduce.umin.v4i32(<4 x i32> %rdx.minmax)
  %cmp.n = icmp eq i64 %38, %n.vec
  br i1 %cmp.n, label %bb59, label %bb53.preheader

bb53.preheader:                                   ; preds = %vector.scevcheck, %bb53.lr.ph, %middle.block
  %mbest1.sroa.0.1132.ph = phi i32 [ -1, %vector.scevcheck ], [ -1, %bb53.lr.ph ], [ %69, %middle.block ]
  %at2.sroa.0.0131.ph = phi i64 [ %35, %vector.scevcheck ], [ %35, %bb53.lr.ph ], [ %48, %middle.block ]
  %l3.sroa.0.0130.ph = phi i32 [ %36, %vector.scevcheck ], [ %36, %bb53.lr.ph ], [ %50, %middle.block ]
  br label %bb53

bb53:                                             ; preds = %bb53.preheader, %bb53
  %mbest1.sroa.0.1132 = phi i32 [ %spec.select86, %bb53 ], [ %mbest1.sroa.0.1132.ph, %bb53.preheader ]
  %at2.sroa.0.0131 = phi i64 [ %72, %bb53 ], [ %at2.sroa.0.0131.ph, %bb53.preheader ]
  %l3.sroa.0.0130 = phi i32 [ %_185, %bb53 ], [ %l3.sroa.0.0130.ph, %bb53.preheader ]
  %_179 = and i32 %l3.sroa.0.0130, 511
  %_178 = zext nneg i32 %_179 to i64
  %_175 = getelementptr inbounds nuw [4 x i8], ptr %_214, i64 %at2.sroa.0.0131
  %_174 = load i32, ptr %_175, align 4, !noundef !149
  %70 = getelementptr inbounds nuw [4 x i8], ptr %lc, i64 %_178
  %_177 = load i32, ptr %70, align 4, !noundef !149
  %base = add i32 %_173, %_174
  %_172 = add i32 %base, %_177
  %_171 = shl i32 %_172, 9
  %71 = or i32 %_171, %l3.sroa.0.0130
  %spec.select86 = tail call i32 @llvm.umin.i32(i32 %71, i32 %mbest1.sroa.0.1132)
  %72 = add nuw nsw i64 %at2.sroa.0.0131, 1
  %_185 = add i32 %l3.sroa.0.0130, 1
  %_168.not.not = icmp ult i64 %at2.sroa.0.0131, %_136
  br i1 %_168.not.not, label %bb53, label %bb59, !llvm.loop !2303

bb79:                                             ; preds = %bb79.preheader, %bb32
  %best.sroa.0.0124 = phi i32 [ %spec.select88, %bb32 ], [ %22, %bb79.preheader ]
  %bd.sroa.0.0123 = phi i32 [ %spec.select87, %bb32 ], [ 0, %bb79.preheader ]
  %prev.sroa.0.0122 = phi i64 [ %prev.sroa.0.1, %bb32 ], [ %23, %bb79.preheader ]
  %pd.sroa.0.0121 = phi i64 [ %pd.sroa.0.1, %bb32 ], [ 0, %bb79.preheader ]
  %j.sroa.0.0120 = phi i64 [ %76, %bb32 ], [ %j0, %bb79.preheader ]
  %_64 = getelementptr inbounds nuw [4 x i8], ptr %_221, i64 %j.sroa.0.0120
  %m = load i32, ptr %_64, align 4, !noundef !149
  %_71 = lshr i32 %m, 15
  %_70 = and i32 %_71, 255
  %_69 = add nuw nsw i32 %_70, 3
  %_68 = zext nneg i32 %_69 to i64
  %stop15 = add nuw nsw i64 %19, %_68
  %_76 = lshr i32 %m, 23
  %_75 = and i32 %_76, 31
  %_74 = zext nneg i32 %_75 to i64
  %73 = getelementptr inbounds nuw [4 x i8], ptr %dc, i64 %_74
  %_73 = load i32, ptr %73, align 4, !noundef !149
  %base17 = add i32 %_73, %bias
  %_79 = icmp ult i64 %stop15, %cl
  br i1 %_79, label %bb21, label %bb32

bb32:                                             ; preds = %bb26, %middle.block199, %bb24, %bb23, %bb79
  %mbest.sroa.0.0 = phi i32 [ %121, %bb23 ], [ -1, %bb79 ], [ -1, %bb24 ], [ %116, %middle.block199 ], [ %spec.select89, %bb26 ]
  %_117 = icmp ult i32 %mbest.sroa.0.0, %best.sroa.0.0124
  %74 = and i32 %m, 32767
  %spec.select87 = select i1 %_117, i32 %74, i32 %bd.sroa.0.0123
  %spec.select88 = tail call i32 @llvm.umin.i32(i32 %mbest.sroa.0.0, i32 %best.sroa.0.0124)
  %_120 = icmp ugt i64 %stop15, %prev.sroa.0.0122
  %_122 = add nuw nsw i32 %74, 1
  %75 = zext nneg i32 %_122 to i64
  %pd.sroa.0.1 = select i1 %_120, i64 %75, i64 %pd.sroa.0.0121
  %prev.sroa.0.1 = tail call i64 @llvm.umax.i64(i64 %stop15, i64 %prev.sroa.0.0122)
  %76 = add nuw nsw i64 %j.sroa.0.0120, 1
  %exitcond.not = icmp eq i64 %76, %e.sroa.0.1
  br i1 %exitcond.not, label %bb39, label %bb79

bb21:                                             ; preds = %bb79
  %_80 = icmp slt i32 %m, 0
  br i1 %_80, label %bb23, label %bb24

bb24:                                             ; preds = %bb21
  %_99.not115.not = icmp ult i64 %prev.sroa.0.0122, %stop15
  br i1 %_99.not115.not, label %bb26.preheader, label %bb32

bb26.preheader:                                   ; preds = %bb24
  %77 = add nuw nsw i64 %prev.sroa.0.0122, 1
  %_96 = sub nsw i64 %77, %19
  %78 = trunc i64 %_96 to i32
  %79 = and i32 %_71, 255
  %80 = zext nneg i32 %79 to i64
  %81 = add i64 %17, %80
  %82 = add i64 %indvar175, %prev.sroa.0.0122
  %83 = sub i64 %81, %82
  %min.iters.check178 = icmp ult i64 %83, 8
  br i1 %min.iters.check178, label %bb26.preheader206, label %vector.scevcheck174

vector.scevcheck174:                              ; preds = %bb26.preheader
  %84 = and i32 %_71, 255
  %85 = zext nneg i32 %84 to i64
  %86 = add i64 %16, %85
  %87 = add i64 %indvar175, %prev.sroa.0.0122
  %88 = sub i64 %86, %87
  %89 = trunc i64 %prev.sroa.0.0122 to i9
  %90 = trunc i64 %88 to i9
  %91 = sub i9 %25, %89
  %92 = icmp ult i9 %91, %90
  %93 = icmp ugt i64 %88, 511
  %94 = or i1 %92, %93
  br i1 %94, label %bb26.preheader206, label %vector.ph179

vector.ph179:                                     ; preds = %vector.scevcheck174
  %n.vec181 = and i64 %83, -8
  %95 = add i64 %77, %n.vec181
  %96 = trunc i64 %n.vec181 to i32
  %97 = add i32 %78, %96
  %broadcast.splatinsert182 = insertelement <4 x i32> poison, i32 %base17, i64 0
  %broadcast.splat183 = shufflevector <4 x i32> %broadcast.splatinsert182, <4 x i32> poison, <4 x i32> zeroinitializer
  %broadcast.splatinsert184 = insertelement <4 x i32> poison, i32 %78, i64 0
  %broadcast.splat185 = shufflevector <4 x i32> %broadcast.splatinsert184, <4 x i32> poison, <4 x i32> zeroinitializer
  %induction186 = add <4 x i32> %broadcast.splat185, <i32 0, i32 1, i32 2, i32 3>
  %98 = getelementptr [4 x i8], ptr %_214, i64 %77
  br label %vector.body187

vector.body187:                                   ; preds = %vector.body187, %vector.ph179
  %index188 = phi i64 [ 0, %vector.ph179 ], [ %index.next197, %vector.body187 ]
  %vec.phi189 = phi <4 x i32> [ splat (i32 -1), %vector.ph179 ], [ %113, %vector.body187 ]
  %vec.phi190 = phi <4 x i32> [ splat (i32 -1), %vector.ph179 ], [ %114, %vector.body187 ]
  %vec.ind191 = phi <4 x i32> [ %induction186, %vector.ph179 ], [ %vec.ind.next198, %vector.body187 ]
  %step.add192 = add <4 x i32> %vec.ind191, splat (i32 4)
  %99 = add i64 %_96, %index188
  %100 = and i64 %99, 511
  %101 = getelementptr [4 x i8], ptr %98, i64 %index188
  %102 = getelementptr inbounds nuw i8, ptr %101, i64 16
  %wide.load193 = load <4 x i32>, ptr %101, align 4
  %wide.load194 = load <4 x i32>, ptr %102, align 4
  %103 = getelementptr inbounds nuw [4 x i8], ptr %lc, i64 %100
  %104 = getelementptr inbounds nuw i8, ptr %103, i64 16
  %wide.load195 = load <4 x i32>, ptr %103, align 4
  %wide.load196 = load <4 x i32>, ptr %104, align 4
  %105 = add <4 x i32> %wide.load193, %broadcast.splat183
  %106 = add <4 x i32> %wide.load194, %broadcast.splat183
  %107 = add <4 x i32> %105, %wide.load195
  %108 = add <4 x i32> %106, %wide.load196
  %109 = shl <4 x i32> %107, splat (i32 9)
  %110 = shl <4 x i32> %108, splat (i32 9)
  %111 = or <4 x i32> %109, %vec.ind191
  %112 = or <4 x i32> %110, %step.add192
  %113 = tail call <4 x i32> @llvm.umin.v4i32(<4 x i32> %111, <4 x i32> %vec.phi189)
  %114 = tail call <4 x i32> @llvm.umin.v4i32(<4 x i32> %112, <4 x i32> %vec.phi190)
  %index.next197 = add nuw i64 %index188, 8
  %vec.ind.next198 = add <4 x i32> %vec.ind191, splat (i32 8)
  %115 = icmp eq i64 %index.next197, %n.vec181
  br i1 %115, label %middle.block199, label %vector.body187, !llvm.loop !2304

middle.block199:                                  ; preds = %vector.body187
  %rdx.minmax200 = tail call <4 x i32> @llvm.umin.v4i32(<4 x i32> %113, <4 x i32> %114)
  %116 = tail call i32 @llvm.vector.reduce.umin.v4i32(<4 x i32> %rdx.minmax200)
  %cmp.n201 = icmp eq i64 %83, %n.vec181
  br i1 %cmp.n201, label %bb32, label %bb26.preheader206

bb26.preheader206:                                ; preds = %vector.scevcheck174, %bb26.preheader, %middle.block199
  %mbest.sroa.0.1118.ph = phi i32 [ -1, %vector.scevcheck174 ], [ -1, %bb26.preheader ], [ %116, %middle.block199 ]
  %at.sroa.0.0117.ph = phi i64 [ %77, %vector.scevcheck174 ], [ %77, %bb26.preheader ], [ %95, %middle.block199 ]
  %l.sroa.0.0116.ph = phi i32 [ %78, %vector.scevcheck174 ], [ %78, %bb26.preheader ], [ %97, %middle.block199 ]
  br label %bb26

bb26:                                             ; preds = %bb26.preheader206, %bb26
  %mbest.sroa.0.1118 = phi i32 [ %spec.select89, %bb26 ], [ %mbest.sroa.0.1118.ph, %bb26.preheader206 ]
  %at.sroa.0.0117 = phi i64 [ %119, %bb26 ], [ %at.sroa.0.0117.ph, %bb26.preheader206 ]
  %l.sroa.0.0116 = phi i32 [ %_116, %bb26 ], [ %l.sroa.0.0116.ph, %bb26.preheader206 ]
  %_110 = and i32 %l.sroa.0.0116, 511
  %_109 = zext nneg i32 %_110 to i64
  %_106 = getelementptr inbounds nuw [4 x i8], ptr %_214, i64 %at.sroa.0.0117
  %_105 = load i32, ptr %_106, align 4, !noundef !149
  %117 = getelementptr inbounds nuw [4 x i8], ptr %lc, i64 %_109
  %_108 = load i32, ptr %117, align 4, !noundef !149
  %_104 = add i32 %_105, %base17
  %_103 = add i32 %_104, %_108
  %_102 = shl i32 %_103, 9
  %118 = or i32 %_102, %l.sroa.0.0116
  %spec.select89 = tail call i32 @llvm.umin.i32(i32 %118, i32 %mbest.sroa.0.1118)
  %119 = add nuw nsw i64 %at.sroa.0.0117, 1
  %_116 = add i32 %l.sroa.0.0116, 1
  %_99.not.not = icmp samesign ult i64 %at.sroa.0.0117, %stop15
  br i1 %_99.not.not, label %bb26, label %bb32, !llvm.loop !2305

bb23:                                             ; preds = %bb21
  %_88 = getelementptr inbounds nuw [4 x i8], ptr %_214, i64 %stop15
  %_87 = load i32, ptr %_88, align 4, !noundef !149
  %120 = getelementptr inbounds nuw [4 x i8], ptr %lc, i64 %_68
  %_89 = load i32, ptr %120, align 4, !noundef !149
  %_86 = add i32 %_87, %base17
  %_85 = add i32 %_86, %_89
  %_84 = shl i32 %_85, 9
  %121 = or disjoint i32 %_84, %_69
  br label %bb32
}
