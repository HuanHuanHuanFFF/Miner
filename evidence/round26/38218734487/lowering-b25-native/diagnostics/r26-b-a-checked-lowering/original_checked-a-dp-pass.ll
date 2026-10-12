define internal fastcc void @_RNvNtCs2hd9JHJjR4I_9candidate5parse9a_dp_pass(ptr noalias nofree noundef nonnull readonly captures(none) %s.0, i64 noundef range(i64 1, 67108864) %s.1, ptr nofree readonly captures(none) %mp.8.val, i64 %mp.16.val, ptr nofree readonly captures(none) %mb.8.val, i64 %mb.16.val, i64 noundef %p0, i64 noundef %pe, ptr noalias nofree noundef nonnull readonly align 4 captures(none) dereferenceable(1024) %lit, ptr noalias nofree noundef nonnull readonly align 4 captures(none) dereferenceable(2048) %lc, ptr noalias nofree noundef nonnull readonly align 4 captures(none) dereferenceable(128) %dc, ptr nofree captures(none) %cost.8.val, i64 range(i64 1, 67108865) %cost.16.val, ptr nofree writeonly captures(none) %ch.8.val, i64 range(i64 1, 67108864) %ch.16.val) unnamed_addr #2 !guid !3107 {
start:
  %_12 = icmp ult i64 %pe, %cost.16.val
  br i1 %_12, label %bb1, label %bb94

bb94:                                             ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse14a_store_choice.exit, %bb96, %bb1, %start
  ret void

bb1:                                              ; preds = %start
  %_213 = icmp ult i64 %mp.16.val, 2305843009213693952
  tail call void @llvm.assume(i1 %_213)
  %_13 = icmp samesign uge i64 %pe, %mp.16.val
  %_15 = icmp samesign ugt i64 %pe, %s.1
  %or.cond.not147 = or i1 %_13, %_15
  %_17.not = icmp samesign ugt i64 %pe, %ch.16.val
  %or.cond144 = select i1 %or.cond.not147, i1 true, i1 %_17.not
  br i1 %or.cond144, label %bb94, label %bb96

bb96:                                             ; preds = %bb1
  call void @llvm.assume(i1 true) [ "nonnull"(ptr %cost.8.val) ]
  %0 = shl nuw nsw i64 %pe, 2
  %scevgep = getelementptr i8, ptr %cost.8.val, i64 %0
  %1 = xor i64 %pe, -1
  %2 = add nsw i64 %cost.16.val, %1
  %umin = tail call i64 @llvm.umin.i64(i64 %2, i64 258)
  %3 = shl nuw nsw i64 %umin, 2
  %4 = add nuw nsw i64 %3, 4
  tail call void @llvm.memset.p0.i64(ptr noundef nonnull align 4 dereferenceable(1) %scevgep, i8 0, i64 %4, i1 false)
  call void @llvm.assume(i1 true) [ "nonnull"(ptr %mp.8.val) ]
  %_3549 = icmp ugt i64 %pe, %p0
  br i1 %_3549, label %bb14.lr.ph, label %bb94

bb14.lr.ph:                                       ; preds = %bb96
  %_32 = getelementptr inbounds nuw [4 x i8], ptr %mp.8.val, i64 %pe
  %_31 = load i32, ptr %_32, align 4, !noundef !233
  %5 = zext i32 %_31 to i64
  %_236 = icmp ult i64 %mb.16.val, 2305843009213693952
  %6 = trunc i64 %pe to i9
  %7 = add nuw nsw i64 %pe, 1
  %8 = add nuw nsw i64 %pe, 2
  %9 = add i9 %6, -3
  br label %bb14

bb14:                                             ; preds = %bb14.lr.ph, %_RNvNtCs2hd9JHJjR4I_9candidate5parse14a_store_choice.exit
  %indvar108 = phi i64 [ 0, %bb14.lr.ph ], [ %indvar.next109, %_RNvNtCs2hd9JHJjR4I_9candidate5parse14a_store_choice.exit ]
  %indvar = phi i9 [ 0, %bb14.lr.ph ], [ %indvar.next, %_RNvNtCs2hd9JHJjR4I_9candidate5parse14a_store_choice.exit ]
  %i.sroa.0.053 = phi i64 [ %pe, %bb14.lr.ph ], [ %_37.0, %_RNvNtCs2hd9JHJjR4I_9candidate5parse14a_store_choice.exit ]
  %e.sroa.0.052 = phi i64 [ %5, %bb14.lr.ph ], [ %j0, %_RNvNtCs2hd9JHJjR4I_9candidate5parse14a_store_choice.exit ]
  %xl.sroa.0.051 = phi i64 [ 0, %bb14.lr.ph ], [ %xl.sroa.0.1, %_RNvNtCs2hd9JHJjR4I_9candidate5parse14a_store_choice.exit ]
  %xd.sroa.0.050 = phi i64 [ 0, %bb14.lr.ph ], [ %xd.sroa.0.1, %_RNvNtCs2hd9JHJjR4I_9candidate5parse14a_store_choice.exit ]
  %reass.sub.neg = sub i64 %pe, %indvar108
  %_37.0 = add nsw i64 %i.sroa.0.053, -1
  %_230 = icmp ult i64 %_37.0, %mp.16.val
  br i1 %_230, label %bb97, label %panic7

bb97:                                             ; preds = %bb14
  %_40 = getelementptr inbounds nuw [4 x i8], ptr %mp.8.val, i64 %_37.0
  %_39 = load i32, ptr %_40, align 4, !noundef !233
  %j0 = zext i32 %_39 to i64
  %_235 = icmp ult i64 %i.sroa.0.053, %cost.16.val
  br i1 %_235, label %bb98, label %panic9

panic7:                                           ; preds = %bb14
  %_37.0.lcssa = phi i64 [ %_37.0, %bb14 ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_37.0.lcssa, i64 noundef %mp.16.val, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_adca51cd0f56de19797d3a5f631d3ddd) #24
  unreachable

bb98:                                             ; preds = %bb97
  %_43 = getelementptr inbounds nuw [4 x i8], ptr %cost.8.val, i64 %i.sroa.0.053
  %nxt = load i32, ptr %_43, align 4, !noundef !233
  %bias = sub i32 1048576, %nxt
  %_54 = icmp ult i64 %_37.0, %s.1
  br i1 %_54, label %bb17, label %panic10

panic9:                                           ; preds = %bb97
  %i.sroa.0.053.lcssa157 = phi i64 [ %i.sroa.0.053, %bb97 ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %i.sroa.0.053.lcssa157, i64 noundef %cost.16.val, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_435c27114c72307c82cb1103ffa5b8de) #24
  unreachable

bb17:                                             ; preds = %bb98
  %10 = getelementptr inbounds nuw i8, ptr %s.0, i64 %_37.0
  %_52 = load i8, ptr %10, align 1, !noundef !233
  %_59.0 = add nuw nsw i64 %i.sroa.0.053, 1
  %_51 = zext i8 %_52 to i64
  %11 = getelementptr inbounds nuw [4 x i8], ptr %lit, i64 %_51
  %_50 = load i32, ptr %11, align 4, !noundef !233
  %_49 = shl i32 %_50, 9
  %12 = add i32 %_49, 536870912
  tail call void @llvm.assume(i1 %_236)
  %spec.select = tail call i64 @llvm.umin.i64(i64 %e.sroa.0.052, i64 %mb.16.val)
  %_6534 = icmp samesign ugt i64 %spec.select, %j0
  br i1 %_6534, label %bb99.lr.ph, label %bb51

panic10:                                          ; preds = %bb98
  %_37.0.lcssa153 = phi i64 [ %_37.0, %bb98 ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_37.0.lcssa153, i64 noundef %s.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_667468cd33cd001ba36f461d0afddb9d) #24
  unreachable

bb99.lr.ph:                                       ; preds = %bb17
  call void @llvm.assume(i1 true) [ "nonnull"(ptr %mb.8.val) ]
  %13 = add i64 %reass.sub.neg, 509
  %14 = trunc i64 %13 to i9
  br label %bb99

bb51:                                             ; preds = %bb41, %bb17
  %pd.sroa.0.0.lcssa = phi i64 [ 0, %bb17 ], [ %pd.sroa.0.1, %bb41 ]
  %prev.sroa.0.0.lcssa = phi i64 [ %_59.0, %bb17 ], [ %prev.sroa.0.1, %bb41 ]
  %bd.sroa.0.0.lcssa = phi i32 [ 0, %bb17 ], [ %spec.select106, %bb41 ]
  %best.sroa.0.0.lcssa = phi i32 [ %12, %bb17 ], [ %spec.select107, %bb41 ]
  %15 = tail call i64 @llvm.umin.i64(i64 %xl.sroa.0.051, i64 257)
  %el.sroa.0.0 = add nuw nsw i64 %15, 1
  %_142 = icmp ult i64 %xl.sroa.0.051, 3
  %16 = add nsw i64 %xd.sroa.0.050, -1
  %17 = icmp uge i64 %16, %_37.0
  %or.cond102 = select i1 %_142, i1 true, i1 %17
  br i1 %or.cond102, label %bb87, label %bb58

bb87:                                             ; preds = %bb63, %bb58, %bb51
  %_209.1 = icmp ult i64 %prev.sroa.0.0.lcssa, %_37.0
  br i1 %_209.1, label %panic19, label %bb88

bb58:                                             ; preds = %bb51
  %_152.0 = add nuw nsw i64 %i.sroa.0.053, %15
  %_148 = icmp ugt i64 %_152.0, %prev.sroa.0.0.lcssa
  br i1 %_148, label %bb62, label %bb87

bb62:                                             ; preds = %bb58
  %_162.0 = sub nsw i64 %_37.0, %xd.sroa.0.050
  %_163 = icmp ult i64 %_162.0, %s.1
  br i1 %_163, label %bb63, label %panic18

bb63:                                             ; preds = %bb62
  %18 = getelementptr inbounds nuw i8, ptr %s.0, i64 %_162.0
  %_158 = load i8, ptr %18, align 1, !noundef !233
  %_154 = icmp eq i8 %_52, %_158
  br i1 %_154, label %bb66, label %bb87

panic18:                                          ; preds = %bb62
  %_162.0.lcssa = phi i64 [ %_162.0, %bb62 ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_162.0.lcssa, i64 noundef %s.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_17c6631b50621382366421f98c86995c) #24
  unreachable

bb88:                                             ; preds = %bb87
  %_209.0 = sub nuw nsw i64 %prev.sroa.0.0.lcssa, %_37.0
  br label %bb89

panic19:                                          ; preds = %bb87
; call core::panicking::panic_const::panic_const_sub_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_c7584029baf529d89ee19b9f222ce7d9) #24
  unreachable

bb89:                                             ; preds = %bb78, %bb88
  %bd.sroa.0.1 = phi i32 [ %spec.select103, %bb78 ], [ %bd.sroa.0.0.lcssa, %bb88 ]
  %best.sroa.0.1 = phi i32 [ %spec.select104, %bb78 ], [ %best.sroa.0.0.lcssa, %bb88 ]
  %xd.sroa.0.1 = phi i64 [ %xd.sroa.0.050, %bb78 ], [ %pd.sroa.0.0.lcssa, %bb88 ]
  %xl.sroa.0.1 = phi i64 [ %el.sroa.0.0, %bb78 ], [ %_209.0, %bb88 ]
  %_9.i = lshr i32 %best.sroa.0.1, 9
  %_8.i = add i32 %nxt, -1048576
  %value.i = add i32 %_8.i, %_9.i
  %_12.i = getelementptr inbounds nuw [4 x i8], ptr %cost.8.val, i64 %_37.0
  store i32 %value.i, ptr %_12.i, align 4
  %_18.i = icmp samesign ult i64 %_37.0, %ch.16.val
  br i1 %_18.i, label %bb11.i, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse14a_store_choice.exit

bb11.i:                                           ; preds = %bb89
  %bl.i = and i32 %best.sroa.0.1, 511
  %_15.i = icmp samesign ugt i32 %bl.i, 2
  %_17.i = shl nsw i32 %bd.sroa.0.1, 9
  %_16.i = add nsw i32 %_17.i, 512
  %19 = or disjoint i32 %_16.i, %bl.i
  %tok.sroa.0.0.i = select i1 %_15.i, i32 %19, i32 0
  call void @llvm.assume(i1 true) [ "nonnull"(ptr %ch.8.val) ]
  %_20.i = getelementptr inbounds nuw [4 x i8], ptr %ch.8.val, i64 %_37.0
  store i32 %tok.sroa.0.0.i, ptr %_20.i, align 4
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse14a_store_choice.exit

_RNvNtCs2hd9JHJjR4I_9candidate5parse14a_store_choice.exit: ; preds = %bb89, %bb11.i
  %_35 = icmp ugt i64 %_37.0, %p0
  %indvar.next = add i9 %indvar, 1
  %indvar.next109 = add i64 %indvar108, 1
  br i1 %_35, label %bb14, label %bb94

bb66:                                             ; preds = %bb63
  %20 = trunc nuw nsw i64 %xd.sroa.0.050 to i32
  %x = add nsw i32 %20, -1
  %_253 = icmp ult i32 %x, 4
  br i1 %_253, label %bb67, label %bb103

bb103:                                            ; preds = %bb66
  %_255 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %x, i1 true)
  %_254 = shl nuw nsw i32 %_255, 1
  %_259 = sub nuw nsw i32 30, %_255
  %_258 = lshr i32 %x, %_259
  %_257 = and i32 %_258, 1
  %_254.masked = and i32 %_254, 30
  %21 = or disjoint i32 %_257, %_254.masked
  %22 = xor i32 %21, 30
  br label %bb67

bb67:                                             ; preds = %bb103, %bb66
  %_176.sroa.0.0 = phi i32 [ %22, %bb103 ], [ %x, %bb66 ]
  %_179 = icmp ult i64 %_152.0, %cost.16.val
  br i1 %_179, label %bb71.lr.ph, label %bb78

bb78:                                             ; preds = %bb71, %middle.block, %bb67
  %mbest1.sroa.0.0 = phi i32 [ -1, %bb67 ], [ %57, %middle.block ], [ %spec.select105, %bb71 ]
  %_205 = icmp ult i32 %mbest1.sroa.0.0, %best.sroa.0.0.lcssa
  %spec.select103 = select i1 %_205, i32 %x, i32 %bd.sroa.0.0.lcssa
  %spec.select104 = tail call i32 @llvm.umin.i32(i32 %mbest1.sroa.0.0, i32 %best.sroa.0.0.lcssa)
  br label %bb89

bb71.lr.ph:                                       ; preds = %bb67
  %_174 = zext nneg i32 %_176.sroa.0.0 to i64
  %23 = getelementptr inbounds nuw [4 x i8], ptr %dc, i64 %_174
  %_173 = load i32, ptr %23, align 4, !noundef !233
  %_181.0 = add nuw nsw i64 %prev.sroa.0.0.lcssa, 1
  %_183 = sub nsw i64 %_181.0, %_37.0
  %24 = trunc nsw i64 %_183 to i32
  %_191 = add i32 %_173, %bias
  %25 = call i64 @llvm.umax.i64(i64 %_152.0, i64 %_181.0)
  %26 = sub nsw i64 %25, %prev.sroa.0.0.lcssa
  %min.iters.check = icmp ult i64 %26, 8
  br i1 %min.iters.check, label %bb71.preheader, label %vector.scevcheck

vector.scevcheck:                                 ; preds = %bb71.lr.ph
  %umax = call i64 @llvm.umax.i64(i64 %_152.0, i64 %_181.0)
  %27 = xor i64 %prev.sroa.0.0.lcssa, -1
  %28 = add nsw i64 %umax, %27
  %29 = trunc i64 %prev.sroa.0.0.lcssa to i9
  %30 = trunc i64 %28 to i9
  %31 = add i9 %indvar, %29
  %32 = sub i9 %9, %31
  %33 = icmp ult i9 %32, %30
  %34 = icmp ugt i64 %28, 511
  %35 = or i1 %33, %34
  br i1 %35, label %bb71.preheader, label %vector.ph

vector.ph:                                        ; preds = %vector.scevcheck
  %n.vec = and i64 %26, -8
  %36 = add i64 %_181.0, %n.vec
  %37 = trunc i64 %n.vec to i32
  %38 = add i32 %24, %37
  %broadcast.splatinsert = insertelement <4 x i32> poison, i32 %_191, i64 0
  %broadcast.splat = shufflevector <4 x i32> %broadcast.splatinsert, <4 x i32> poison, <4 x i32> zeroinitializer
  %broadcast.splatinsert100 = insertelement <4 x i32> poison, i32 %24, i64 0
  %broadcast.splat101 = shufflevector <4 x i32> %broadcast.splatinsert100, <4 x i32> poison, <4 x i32> zeroinitializer
  %induction = add <4 x i32> %broadcast.splat101, <i32 0, i32 1, i32 2, i32 3>
  %39 = getelementptr [4 x i8], ptr %cost.8.val, i64 %_181.0
  br label %vector.body

vector.body:                                      ; preds = %vector.body, %vector.ph
  %index = phi i64 [ 0, %vector.ph ], [ %index.next, %vector.body ]
  %vec.phi = phi <4 x i32> [ splat (i32 -1), %vector.ph ], [ %54, %vector.body ]
  %vec.phi102 = phi <4 x i32> [ splat (i32 -1), %vector.ph ], [ %55, %vector.body ]
  %vec.ind = phi <4 x i32> [ %induction, %vector.ph ], [ %vec.ind.next, %vector.body ]
  %step.add = add <4 x i32> %vec.ind, splat (i32 4)
  %40 = add i64 %_183, %index
  %41 = and i64 %40, 511
  %42 = getelementptr [4 x i8], ptr %39, i64 %index
  %43 = getelementptr inbounds nuw i8, ptr %42, i64 16
  %wide.load = load <4 x i32>, ptr %42, align 4
  %wide.load103 = load <4 x i32>, ptr %43, align 4
  %44 = getelementptr inbounds nuw [4 x i8], ptr %lc, i64 %41
  %45 = getelementptr inbounds nuw i8, ptr %44, i64 16
  %wide.load104 = load <4 x i32>, ptr %44, align 4
  %wide.load105 = load <4 x i32>, ptr %45, align 4
  %46 = add <4 x i32> %broadcast.splat, %wide.load
  %47 = add <4 x i32> %broadcast.splat, %wide.load103
  %48 = add <4 x i32> %46, %wide.load104
  %49 = add <4 x i32> %47, %wide.load105
  %50 = shl <4 x i32> %48, splat (i32 9)
  %51 = shl <4 x i32> %49, splat (i32 9)
  %52 = or <4 x i32> %50, %vec.ind
  %53 = or <4 x i32> %51, %step.add
  %54 = call <4 x i32> @llvm.umin.v4i32(<4 x i32> %52, <4 x i32> %vec.phi)
  %55 = call <4 x i32> @llvm.umin.v4i32(<4 x i32> %53, <4 x i32> %vec.phi102)
  %index.next = add nuw i64 %index, 8
  %vec.ind.next = add <4 x i32> %vec.ind, splat (i32 8)
  %56 = icmp eq i64 %index.next, %n.vec
  br i1 %56, label %middle.block, label %vector.body, !llvm.loop !3108

middle.block:                                     ; preds = %vector.body
  %.lcssa151 = phi <4 x i32> [ %54, %vector.body ]
  %.lcssa150 = phi <4 x i32> [ %55, %vector.body ]
  %rdx.minmax = call <4 x i32> @llvm.umin.v4i32(<4 x i32> %.lcssa151, <4 x i32> %.lcssa150)
  %57 = call i32 @llvm.vector.reduce.umin.v4i32(<4 x i32> %rdx.minmax)
  %cmp.n = icmp eq i64 %26, %n.vec
  br i1 %cmp.n, label %bb78, label %bb71.preheader

bb71.preheader:                                   ; preds = %vector.scevcheck, %bb71.lr.ph, %middle.block
  %mbest1.sroa.0.147.ph = phi i32 [ -1, %vector.scevcheck ], [ -1, %bb71.lr.ph ], [ %57, %middle.block ]
  %at2.sroa.0.046.ph = phi i64 [ %_181.0, %vector.scevcheck ], [ %_181.0, %bb71.lr.ph ], [ %36, %middle.block ]
  %l3.sroa.0.045.ph = phi i32 [ %24, %vector.scevcheck ], [ %24, %bb71.lr.ph ], [ %38, %middle.block ]
  br label %bb71

bb71:                                             ; preds = %bb71.preheader, %bb71
  %mbest1.sroa.0.147 = phi i32 [ %spec.select105, %bb71 ], [ %mbest1.sroa.0.147.ph, %bb71.preheader ]
  %at2.sroa.0.046 = phi i64 [ %_203.0, %bb71 ], [ %at2.sroa.0.046.ph, %bb71.preheader ]
  %l3.sroa.0.045 = phi i32 [ %_204, %bb71 ], [ %l3.sroa.0.045.ph, %bb71.preheader ]
  %_197 = and i32 %l3.sroa.0.045, 511
  %_196 = zext nneg i32 %_197 to i64
  %_193 = getelementptr inbounds nuw [4 x i8], ptr %cost.8.val, i64 %at2.sroa.0.046
  %_192 = load i32, ptr %_193, align 4, !noundef !233
  %58 = getelementptr inbounds nuw [4 x i8], ptr %lc, i64 %_196
  %_195 = load i32, ptr %58, align 4, !noundef !233
  %base = add i32 %_191, %_192
  %_190 = add i32 %base, %_195
  %_189 = shl i32 %_190, 9
  %59 = or i32 %_189, %l3.sroa.0.045
  %spec.select105 = tail call i32 @llvm.umin.i32(i32 %59, i32 %mbest1.sroa.0.147)
  %_203.0 = add nuw nsw i64 %at2.sroa.0.046, 1
  %_204 = add i32 %l3.sroa.0.045, 1
  %_186.not.not = icmp ult i64 %at2.sroa.0.046, %_152.0
  br i1 %_186.not.not, label %bb71, label %bb78, !llvm.loop !3109

bb99:                                             ; preds = %bb99.lr.ph, %bb41
  %best.sroa.0.039 = phi i32 [ %12, %bb99.lr.ph ], [ %spec.select107, %bb41 ]
  %bd.sroa.0.038 = phi i32 [ 0, %bb99.lr.ph ], [ %spec.select106, %bb41 ]
  %prev.sroa.0.037 = phi i64 [ %_59.0, %bb99.lr.ph ], [ %prev.sroa.0.1, %bb41 ]
  %pd.sroa.0.036 = phi i64 [ 0, %bb99.lr.ph ], [ %pd.sroa.0.1, %bb41 ]
  %j.sroa.0.035 = phi i64 [ %j0, %bb99.lr.ph ], [ %_134.0, %bb41 ]
  %_69 = getelementptr inbounds nuw [4 x i8], ptr %mb.8.val, i64 %j.sroa.0.035
  %m = load i32, ptr %_69, align 4, !noundef !233
  %_76 = lshr i32 %m, 15
  %_75 = and i32 %_76, 255
  %_77.0 = add nuw nsw i32 %_75, 3
  %_73 = zext nneg i32 %_77.0 to i64
  %_78.0 = add nuw nsw i64 %_37.0, %_73
  %_83 = lshr i32 %m, 23
  %_82 = and i32 %_83, 31
  %_81 = zext nneg i32 %_82 to i64
  %60 = getelementptr inbounds nuw [4 x i8], ptr %dc, i64 %_81
  %_80 = load i32, ptr %60, align 4, !noundef !233
  %base31 = add i32 %_80, %bias
  %_86 = icmp ult i64 %_78.0, %cost.16.val
  br i1 %_86, label %bb28, label %bb41

bb41:                                             ; preds = %bb34, %middle.block132, %bb32, %bb30, %bb99
  %mbest.sroa.0.0 = phi i32 [ %105, %bb30 ], [ -1, %bb99 ], [ -1, %bb32 ], [ %101, %middle.block132 ], [ %spec.select108, %bb34 ]
  %_126 = icmp ult i32 %mbest.sroa.0.0, %best.sroa.0.039
  %61 = and i32 %m, 32767
  %spec.select106 = select i1 %_126, i32 %61, i32 %bd.sroa.0.038
  %spec.select107 = tail call i32 @llvm.umin.i32(i32 %mbest.sroa.0.0, i32 %best.sroa.0.039)
  %_129 = icmp ugt i64 %_78.0, %prev.sroa.0.037
  %_133.0 = add nuw nsw i32 %61, 1
  %62 = zext nneg i32 %_133.0 to i64
  %pd.sroa.0.1 = select i1 %_129, i64 %62, i64 %pd.sroa.0.036
  %prev.sroa.0.1 = tail call i64 @llvm.umax.i64(i64 %_78.0, i64 %prev.sroa.0.037)
  %_134.0 = add nuw nsw i64 %j.sroa.0.035, 1
  %exitcond.not = icmp eq i64 %_134.0, %spec.select
  br i1 %exitcond.not, label %bb51, label %bb99

bb28:                                             ; preds = %bb99
  %_87 = icmp slt i32 %m, 0
  br i1 %_87, label %bb30, label %bb32

bb32:                                             ; preds = %bb28
  %_107.not30.not = icmp ult i64 %prev.sroa.0.037, %_78.0
  br i1 %_107.not30.not, label %bb34.preheader, label %bb41

bb34.preheader:                                   ; preds = %bb32
  %_102.0 = add nuw nsw i64 %prev.sroa.0.037, 1
  %_104 = sub nsw i64 %_102.0, %_37.0
  %63 = trunc nsw i64 %_104 to i32
  %64 = and i32 %_76, 255
  %65 = zext nneg i32 %64 to i64
  %66 = add nuw nsw i64 %8, %65
  %67 = add i64 %indvar108, %prev.sroa.0.037
  %68 = sub i64 %66, %67
  %min.iters.check111 = icmp ult i64 %68, 8
  br i1 %min.iters.check111, label %bb34.preheader148, label %vector.scevcheck107

vector.scevcheck107:                              ; preds = %bb34.preheader
  %69 = and i32 %_76, 255
  %70 = zext nneg i32 %69 to i64
  %71 = add nuw nsw i64 %7, %70
  %72 = add i64 %indvar108, %prev.sroa.0.037
  %73 = sub i64 %71, %72
  %74 = trunc i64 %prev.sroa.0.037 to i9
  %75 = trunc i64 %73 to i9
  %76 = sub i9 %14, %74
  %77 = icmp ult i9 %76, %75
  %78 = icmp ugt i64 %73, 511
  %79 = or i1 %77, %78
  br i1 %79, label %bb34.preheader148, label %vector.ph112

vector.ph112:                                     ; preds = %vector.scevcheck107
  %n.vec114 = and i64 %68, -8
  %80 = add i64 %_102.0, %n.vec114
  %81 = trunc i64 %n.vec114 to i32
  %82 = add i32 %63, %81
  %broadcast.splatinsert115 = insertelement <4 x i32> poison, i32 %base31, i64 0
  %broadcast.splat116 = shufflevector <4 x i32> %broadcast.splatinsert115, <4 x i32> poison, <4 x i32> zeroinitializer
  %broadcast.splatinsert117 = insertelement <4 x i32> poison, i32 %63, i64 0
  %broadcast.splat118 = shufflevector <4 x i32> %broadcast.splatinsert117, <4 x i32> poison, <4 x i32> zeroinitializer
  %induction119 = add <4 x i32> %broadcast.splat118, <i32 0, i32 1, i32 2, i32 3>
  %83 = getelementptr [4 x i8], ptr %cost.8.val, i64 %_102.0
  br label %vector.body120

vector.body120:                                   ; preds = %vector.body120, %vector.ph112
  %index121 = phi i64 [ 0, %vector.ph112 ], [ %index.next130, %vector.body120 ]
  %vec.phi122 = phi <4 x i32> [ splat (i32 -1), %vector.ph112 ], [ %98, %vector.body120 ]
  %vec.phi123 = phi <4 x i32> [ splat (i32 -1), %vector.ph112 ], [ %99, %vector.body120 ]
  %vec.ind124 = phi <4 x i32> [ %induction119, %vector.ph112 ], [ %vec.ind.next131, %vector.body120 ]
  %step.add125 = add <4 x i32> %vec.ind124, splat (i32 4)
  %84 = add i64 %_104, %index121
  %85 = and i64 %84, 511
  %86 = getelementptr [4 x i8], ptr %83, i64 %index121
  %87 = getelementptr inbounds nuw i8, ptr %86, i64 16
  %wide.load126 = load <4 x i32>, ptr %86, align 4
  %wide.load127 = load <4 x i32>, ptr %87, align 4
  %88 = getelementptr inbounds nuw [4 x i8], ptr %lc, i64 %85
  %89 = getelementptr inbounds nuw i8, ptr %88, i64 16
  %wide.load128 = load <4 x i32>, ptr %88, align 4
  %wide.load129 = load <4 x i32>, ptr %89, align 4
  %90 = add <4 x i32> %wide.load126, %broadcast.splat116
  %91 = add <4 x i32> %wide.load127, %broadcast.splat116
  %92 = add <4 x i32> %90, %wide.load128
  %93 = add <4 x i32> %91, %wide.load129
  %94 = shl <4 x i32> %92, splat (i32 9)
  %95 = shl <4 x i32> %93, splat (i32 9)
  %96 = or <4 x i32> %94, %vec.ind124
  %97 = or <4 x i32> %95, %step.add125
  %98 = call <4 x i32> @llvm.umin.v4i32(<4 x i32> %96, <4 x i32> %vec.phi122)
  %99 = call <4 x i32> @llvm.umin.v4i32(<4 x i32> %97, <4 x i32> %vec.phi123)
  %index.next130 = add nuw i64 %index121, 8
  %vec.ind.next131 = add <4 x i32> %vec.ind124, splat (i32 8)
  %100 = icmp eq i64 %index.next130, %n.vec114
  br i1 %100, label %middle.block132, label %vector.body120, !llvm.loop !3110

middle.block132:                                  ; preds = %vector.body120
  %.lcssa149 = phi <4 x i32> [ %98, %vector.body120 ]
  %.lcssa = phi <4 x i32> [ %99, %vector.body120 ]
  %rdx.minmax133 = call <4 x i32> @llvm.umin.v4i32(<4 x i32> %.lcssa149, <4 x i32> %.lcssa)
  %101 = call i32 @llvm.vector.reduce.umin.v4i32(<4 x i32> %rdx.minmax133)
  %cmp.n134 = icmp eq i64 %68, %n.vec114
  br i1 %cmp.n134, label %bb41, label %bb34.preheader148

bb34.preheader148:                                ; preds = %vector.scevcheck107, %bb34.preheader, %middle.block132
  %mbest.sroa.0.133.ph = phi i32 [ -1, %vector.scevcheck107 ], [ -1, %bb34.preheader ], [ %101, %middle.block132 ]
  %at.sroa.0.032.ph = phi i64 [ %_102.0, %vector.scevcheck107 ], [ %_102.0, %bb34.preheader ], [ %80, %middle.block132 ]
  %l.sroa.0.031.ph = phi i32 [ %63, %vector.scevcheck107 ], [ %63, %bb34.preheader ], [ %82, %middle.block132 ]
  br label %bb34

bb34:                                             ; preds = %bb34.preheader148, %bb34
  %mbest.sroa.0.133 = phi i32 [ %spec.select108, %bb34 ], [ %mbest.sroa.0.133.ph, %bb34.preheader148 ]
  %at.sroa.0.032 = phi i64 [ %_124.0, %bb34 ], [ %at.sroa.0.032.ph, %bb34.preheader148 ]
  %l.sroa.0.031 = phi i32 [ %_125, %bb34 ], [ %l.sroa.0.031.ph, %bb34.preheader148 ]
  %_118 = and i32 %l.sroa.0.031, 511
  %_117 = zext nneg i32 %_118 to i64
  %_114 = getelementptr inbounds nuw [4 x i8], ptr %cost.8.val, i64 %at.sroa.0.032
  %_113 = load i32, ptr %_114, align 4, !noundef !233
  %102 = getelementptr inbounds nuw [4 x i8], ptr %lc, i64 %_117
  %_116 = load i32, ptr %102, align 4, !noundef !233
  %_112 = add i32 %_113, %base31
  %_111 = add i32 %_112, %_116
  %_110 = shl i32 %_111, 9
  %103 = or i32 %_110, %l.sroa.0.031
  %spec.select108 = tail call i32 @llvm.umin.i32(i32 %103, i32 %mbest.sroa.0.133)
  %_124.0 = add nuw nsw i64 %at.sroa.0.032, 1
  %_125 = add i32 %l.sroa.0.031, 1
  %_107.not.not = icmp ult i64 %at.sroa.0.032, %_78.0
  br i1 %_107.not.not, label %bb34, label %bb41, !llvm.loop !3111

bb30:                                             ; preds = %bb28
  %_95 = getelementptr inbounds nuw [4 x i8], ptr %cost.8.val, i64 %_78.0
  %_94 = load i32, ptr %_95, align 4, !noundef !233
  %104 = getelementptr inbounds nuw [4 x i8], ptr %lc, i64 %_73
  %_96 = load i32, ptr %104, align 4, !noundef !233
  %_93 = add i32 %_94, %base31
  %_92 = add i32 %_93, %_96
  %_91 = shl i32 %_92, 9
  %105 = or disjoint i32 %_91, %_77.0
  br label %bb41
}
