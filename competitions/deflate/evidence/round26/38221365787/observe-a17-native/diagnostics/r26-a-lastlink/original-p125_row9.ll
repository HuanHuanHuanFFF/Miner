define internal fastcc noundef i64 @_RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row9(ptr noalias nofree noundef nonnull readonly captures(address, read_provenance) %input.0, i64 noundef range(i64 0, -9223372036854775808) %input.1, ptr noalias nofree noundef nonnull align 4 captures(none) %out.0, i64 noundef range(i64 0, 2305843009213693952) %out.1) unnamed_addr #0 !guid !2597 {
start:
  %prev.i = alloca [131072 x i8], align 4
  %head.i = alloca [262144 x i8], align 4
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2598)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2601)
  %_4.i = icmp samesign ugt i64 %input.1, 16
  br i1 %_4.i, label %bb5.i.preheader, label %bb178.i

bb178.i:                                          ; preds = %bb177.i, %start
  %p.sroa.0.0.i = phi i64 [ %p.sroa.0.4.i.lcssa, %bb177.i ], [ 0, %start ]
  %nt.sroa.0.0.i = phi i64 [ %nt.sroa.0.4.i.lcssa, %bb177.i ], [ 0, %start ]
  %_237.i2234 = icmp ult i64 %p.sroa.0.0.i, %input.1
  br i1 %_237.i2234, label %bb1.i185.preheader, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse8u118_runKj10000_Kj8000_Kmffffffff_Kj4_Kjc_Kj40_Kj6_Kjf4240_Kj80_Kj1_Kj10_KB18_Kl40_Kj0_EB4_.exit

bb1.i185.preheader:                               ; preds = %bb178.i
  %umax = tail call i64 @llvm.umax.i64(i64 %nt.sroa.0.0.i, i64 %out.1)
  %0 = xor i64 %p.sroa.0.0.i, -1
  %1 = add nsw i64 %input.1, %0
  %2 = sub i64 %umax, %nt.sroa.0.0.i
  %3 = call i64 @llvm.umin.i64(i64 %1, i64 %2)
  %4 = add i64 %3, 1
  %min.iters.check2817 = icmp ult i64 %4, 9
  br i1 %min.iters.check2817, label %bb1.i185.preheader2839, label %vector.ph2818

bb1.i185.preheader2839:                           ; preds = %vector.body2821, %bb1.i185.preheader
  %nt.sroa.0.2.i2236.ph = phi i64 [ %nt.sroa.0.0.i, %bb1.i185.preheader ], [ %7, %vector.body2821 ]
  %p.sroa.0.2.i2235.ph = phi i64 [ %p.sroa.0.0.i, %bb1.i185.preheader ], [ %8, %vector.body2821 ]
  br label %bb1.i185

vector.ph2818:                                    ; preds = %bb1.i185.preheader
  %n.mod.vf2819 = and i64 %4, 7
  %5 = icmp eq i64 %n.mod.vf2819, 0
  %6 = select i1 %5, i64 8, i64 %n.mod.vf2819
  %n.vec2820 = sub nuw i64 %4, %6
  %7 = add i64 %nt.sroa.0.0.i, %n.vec2820
  %8 = add i64 %p.sroa.0.0.i, %n.vec2820
  %9 = getelementptr i8, ptr %input.0, i64 %p.sroa.0.0.i
  %10 = getelementptr [4 x i8], ptr %out.0, i64 %nt.sroa.0.0.i
  br label %vector.body2821

vector.body2821:                                  ; preds = %vector.body2821, %vector.ph2818
  %index2822 = phi i64 [ 0, %vector.ph2818 ], [ %index.next2825, %vector.body2821 ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2603)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2606)
  %11 = getelementptr i8, ptr %9, i64 %index2822
  %12 = getelementptr inbounds nuw i8, ptr %11, i64 4
  %wide.load2823 = load <4 x i8>, ptr %11, align 1, !alias.scope !2603, !noalias !2606
  %wide.load2824 = load <4 x i8>, ptr %12, align 1, !alias.scope !2603, !noalias !2606
  %13 = getelementptr [4 x i8], ptr %10, i64 %index2822
  %14 = zext <4 x i8> %wide.load2823 to <4 x i32>
  %15 = zext <4 x i8> %wide.load2824 to <4 x i32>
  %16 = getelementptr inbounds nuw i8, ptr %13, i64 16
  store <4 x i32> %14, ptr %13, align 4, !alias.scope !2606, !noalias !2603
  store <4 x i32> %15, ptr %16, align 4, !alias.scope !2606, !noalias !2603
  %index.next2825 = add nuw i64 %index2822, 8
  %17 = icmp eq i64 %index.next2825, %n.vec2820
  br i1 %17, label %bb1.i185.preheader2839, label %vector.body2821, !llvm.loop !2608

bb5.i.preheader:                                  ; preds = %start
  call void @llvm.lifetime.start.p0(ptr nonnull %head.i), !noalias !2609
  call void @llvm.memset.p0.i64(ptr noundef nonnull align 4 dereferenceable(262144) %head.i, i8 0, i64 262144, i1 false), !noalias !2609
  call void @llvm.lifetime.start.p0(ptr nonnull %prev.i), !noalias !2609
  call void @llvm.memset.p0.i64(ptr noundef nonnull align 4 dereferenceable(131072) %prev.i, i8 0, i64 131072, i1 false), !noalias !2609
  %_8.0.i = add nsw i64 %input.1, -8
  %18 = add nuw i64 %input.1, 16
  %19 = add nsw i64 %input.1, -10
  br label %bb5.i

bb177.i:                                          ; preds = %bb174.i
  %p.sroa.0.4.i.lcssa = phi i64 [ %p.sroa.0.4.i, %bb174.i ]
  %nt.sroa.0.4.i.lcssa = phi i64 [ %nt.sroa.0.4.i, %bb174.i ]
  call void @llvm.lifetime.end.p0(ptr nonnull %prev.i), !noalias !2609
  call void @llvm.lifetime.end.p0(ptr nonnull %head.i), !noalias !2609
  br label %bb178.i

bb5.i:                                            ; preds = %bb5.i.preheader, %bb174.i
  %nt.sroa.0.1.i2231 = phi i64 [ %nt.sroa.0.4.i, %bb174.i ], [ 0, %bb5.i.preheader ]
  %miss.sroa.0.0.i2230 = phi i64 [ %miss.sroa.0.1.i, %bb174.i ], [ 0, %bb5.i.preheader ]
  %fuel.sroa.0.0.i2229 = phi i64 [ %_15.0.i, %bb174.i ], [ %18, %bb5.i.preheader ]
  %p.sroa.0.1.i2228 = phi i64 [ %p.sroa.0.4.i, %bb174.i ], [ 0, %bb5.i.preheader ]
  %ins.sroa.0.0.i2227 = phi i64 [ %ins.sroa.0.3.i, %bb174.i ], [ 0, %bb5.i.preheader ]
  %p.sroa.0.1.i2228.fr = freeze i64 %p.sroa.0.1.i2228
  %_15.0.i = add i64 %fuel.sroa.0.0.i2229, -1
  %_16.i2150 = icmp ult i64 %ins.sroa.0.0.i2227, %p.sroa.0.1.i2228.fr
  br i1 %_16.i2150, label %bb8.i, label %bb11.i

bb1.i185:                                         ; preds = %bb1.i185.preheader2839, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit191
  %nt.sroa.0.2.i2236 = phi i64 [ %_10.0.i190, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit191 ], [ %nt.sroa.0.2.i2236.ph, %bb1.i185.preheader2839 ]
  %p.sroa.0.2.i2235 = phi i64 [ %_241.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit191 ], [ %p.sroa.0.2.i2235.ph, %bb1.i185.preheader2839 ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2603)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2606)
  %exitcond2383.not = icmp eq i64 %nt.sroa.0.2.i2236, %umax
  br i1 %exitcond2383.not, label %panic1.i187, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit191

panic1.i187:                                      ; preds = %bb1.i185
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %umax, i64 noundef range(i64 0, 2305843009213693952) %out.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_f5cc78c6143d87a95e73f58df7e9bb32) #13, !noalias !2610
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit191: ; preds = %bb1.i185
  %20 = getelementptr inbounds nuw i8, ptr %input.0, i64 %p.sroa.0.2.i2235
  %_5.i189 = load i8, ptr %20, align 1, !alias.scope !2603, !noalias !2606, !noundef !136
  %21 = getelementptr inbounds nuw [4 x i8], ptr %out.0, i64 %nt.sroa.0.2.i2236
  %22 = zext i8 %_5.i189 to i32
  store i32 %22, ptr %21, align 4, !alias.scope !2606, !noalias !2603
  %_10.0.i190 = add i64 %nt.sroa.0.2.i2236, 1
  %_241.0.i = add i64 %p.sroa.0.2.i2235, 1
  %exitcond2384.not = icmp eq i64 %_241.0.i, %input.1
  br i1 %exitcond2384.not, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse8u118_runKj10000_Kj8000_Kmffffffff_Kj4_Kjc_Kj40_Kj6_Kjf4240_Kj80_Kj1_Kj10_KB18_Kl40_Kj0_EB4_.exit, label %bb1.i185, !llvm.loop !2611

bb11.i:                                           ; preds = %bb8.i, %bb5.i
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2612)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2615)
  %23 = getelementptr inbounds nuw i8, ptr %input.0, i64 %p.sroa.0.1.i2228.fr
  %24 = load <4 x i8>, ptr %23, align 1, !alias.scope !2617, !noalias !2620
  %25 = bitcast <4 x i8> %24 to i32
  %26 = call i32 @llvm.bswap.i32(i32 %25)
  %27 = zext i32 %26 to i64
  %28 = mul i64 %27, -7046029254386353131
  %29 = lshr i64 %28, 48
  %30 = getelementptr inbounds nuw [4 x i8], ptr %head.i, i64 %29
  %old.i173.i = load i32, ptr %30, align 4, !alias.scope !2612, !noalias !2621, !noundef !136
  %_16.i174.i = and i64 %p.sroa.0.1.i2228.fr, 32767
  %31 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_16.i174.i
  store i32 %old.i173.i, ptr %31, align 4, !alias.scope !2615, !noalias !2623
  %32 = trunc i64 %p.sroa.0.1.i2228.fr to i32
  store i32 %32, ptr %30, align 4, !alias.scope !2612, !noalias !2621
  %_0.i175.i = zext i32 %old.i173.i to i64
  %_29.0.i = add i64 %p.sroa.0.1.i2228.fr, 1
  %_13.0.i9 = sub i64 %input.1, %p.sroa.0.1.i2228.fr
  %spec.store.select3.i10 = tail call i64 @llvm.umin.i64(i64 %_13.0.i9, i64 258)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2624)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2627)
  %spec.store.select.i16 = tail call i64 @llvm.umin.i64(i64 %_13.0.i9, i64 128)
  %33 = and i64 %spec.store.select3.i10, 504
  %34 = extractelement <4 x i8> %24, i64 3
  %_26.i1092154.not = icmp eq i64 %33, %spec.store.select3.i10
  br label %bb11.i18

bb11.i18:                                         ; preds = %bb37.i, %bb11.i
  %start1.sroa.0.0.i2161 = phi i64 [ %_0.i175.i, %bb11.i ], [ %nx.i, %bb37.i ]
  %have.sroa.0.0.i2160 = phi i64 [ 3, %bb11.i ], [ %have.sroa.0.2.i, %bb37.i ]
  %depth.sroa.0.0.i2159 = phi i64 [ 12, %bb11.i ], [ %_66.0.i, %bb37.i ]
  %bd.sroa.0.0.i2158 = phi i64 [ 0, %bb11.i ], [ %bd.sroa.0.2.i, %bb37.i ]
  %pb.sroa.0.1.i2157 = phi i8 [ %34, %bb11.i ], [ %pb.sroa.0.3.i, %bb37.i ]
  %d.i = sub nsw i64 %p.sroa.0.1.i2228.fr, %start1.sroa.0.0.i2161
  %_29.i = add nsw i64 %d.i, -1
  %_28.i = icmp ult i64 %_29.i, 32768
  br i1 %_28.i, label %bb13.i, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit

bb13.i:                                           ; preds = %bb11.i18
  %_34.0.i = add nuw nsw i64 %start1.sroa.0.0.i2161, %have.sroa.0.0.i2160
  %_30.i = icmp ult i64 %_34.0.i, %input.1
  br i1 %_30.i, label %bb16.i19, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit

bb16.i19:                                         ; preds = %bb13.i
  %35 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_34.0.i
  %_36.i = load i8, ptr %35, align 1, !alias.scope !2624, !noalias !2627, !noundef !136
  %_35.i20 = icmp eq i8 %_36.i, %pb.sroa.0.1.i2157
  br i1 %_35.i20, label %bb2.i133, label %bb37.i

bb2.i133:                                         ; preds = %bb16.i19, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit
  %k.sroa.0.0.i1042153 = phi i64 [ %_10.0.i134, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit ], [ 0, %bb16.i19 ]
  %_10.0.i134 = add nuw nsw i64 %k.sroa.0.0.i1042153, 8
  %_7.not.i137 = icmp samesign ugt i64 %_10.0.i134, %spec.store.select3.i10
  br i1 %_7.not.i137, label %bb17.i105, label %bb4.i138

bb4.i138:                                         ; preds = %bb2.i133
  %_15.0.i139 = add nuw nsw i64 %k.sroa.0.0.i1042153, %start1.sroa.0.0.i2161
  %_5.0.i436 = add nuw nsw i64 %_15.0.i139, 8
  %_3.not.i437 = icmp samesign ugt i64 %_5.0.i436, %input.1
  br i1 %_3.not.i437, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit502, label %bb2.i438

bb17.i105:                                        ; preds = %bb2.i133
  br i1 %_26.i1092154.not, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit159, label %bb21.i115

bb2.i438:                                         ; preds = %bb4.i138
  %36 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_15.0.i139
  %_15.i442 = load i8, ptr %36, align 1, !alias.scope !2629, !noalias !2627, !noundef !136
  %_14.i443 = zext i8 %_15.i442 to i64
  %_13.i444 = shl nuw i64 %_14.i443, 56
  %37 = getelementptr inbounds nuw i8, ptr %36, i64 1
  %_19.i449 = load i8, ptr %37, align 1, !alias.scope !2629, !noalias !2627, !noundef !136
  %_18.i450 = zext i8 %_19.i449 to i64
  %_17.i451 = shl nuw nsw i64 %_18.i450, 48
  %_12.i452 = or disjoint i64 %_17.i451, %_13.i444
  %38 = getelementptr inbounds nuw i8, ptr %36, i64 2
  %_25.i457 = load i8, ptr %38, align 1, !alias.scope !2629, !noalias !2627, !noundef !136
  %_24.i458 = zext i8 %_25.i457 to i64
  %_23.i459 = shl nuw nsw i64 %_24.i458, 40
  %_11.i460 = or disjoint i64 %_12.i452, %_23.i459
  %39 = getelementptr inbounds nuw i8, ptr %36, i64 3
  %_31.i465 = load i8, ptr %39, align 1, !alias.scope !2629, !noalias !2627, !noundef !136
  %_30.i466 = zext i8 %_31.i465 to i64
  %_29.i467 = shl nuw nsw i64 %_30.i466, 32
  %_10.i468 = or disjoint i64 %_11.i460, %_29.i467
  %40 = getelementptr inbounds nuw i8, ptr %36, i64 4
  %_37.i473 = load i8, ptr %40, align 1, !alias.scope !2629, !noalias !2627, !noundef !136
  %_36.i474 = zext i8 %_37.i473 to i64
  %_35.i475 = shl nuw nsw i64 %_36.i474, 24
  %_9.i476 = or disjoint i64 %_10.i468, %_35.i475
  %41 = getelementptr inbounds nuw i8, ptr %36, i64 5
  %_43.i481 = load i8, ptr %41, align 1, !alias.scope !2629, !noalias !2627, !noundef !136
  %_42.i482 = zext i8 %_43.i481 to i64
  %_41.i483 = shl nuw nsw i64 %_42.i482, 16
  %_8.i484 = or disjoint i64 %_9.i476, %_41.i483
  %42 = getelementptr inbounds nuw i8, ptr %36, i64 6
  %_49.i489 = load i8, ptr %42, align 1, !alias.scope !2629, !noalias !2627, !noundef !136
  %_48.i490 = zext i8 %_49.i489 to i64
  %_47.i491 = shl nuw nsw i64 %_48.i490, 8
  %_7.i492 = or i64 %_8.i484, %_47.i491
  %43 = getelementptr inbounds nuw i8, ptr %36, i64 7
  %_54.i497 = load i8, ptr %43, align 1, !alias.scope !2629, !noalias !2627, !noundef !136
  %_53.i498 = zext i8 %_54.i497 to i64
  %44 = or i64 %_7.i492, %_53.i498
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit502

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit502: ; preds = %bb4.i138, %bb2.i438
  %_0.sroa.0.0.i500 = phi i64 [ %44, %bb2.i438 ], [ 0, %bb4.i138 ]
  %_19.0.i143 = add nuw i64 %k.sroa.0.0.i1042153, %p.sroa.0.1.i2228.fr
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2632)
  %_5.1.i = icmp ugt i64 %_19.0.i143, -9
  br i1 %_5.1.i, label %panic.i433, label %bb1.i390

bb1.i390:                                         ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit502
  %_5.0.i391 = add nuw i64 %_19.0.i143, 8
  %_3.not.i392 = icmp ugt i64 %_5.0.i391, %input.1
  br i1 %_3.not.i392, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit, label %bb2.i393

panic.i433:                                       ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit502
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_c9d76a7bf6f333d6169298e9d093a546) #13, !noalias !2635
  unreachable

bb2.i393:                                         ; preds = %bb1.i390
  %45 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_19.0.i143
  %_15.i397 = load i8, ptr %45, align 1, !alias.scope !2632, !noalias !2627, !noundef !136
  %_14.i398 = zext i8 %_15.i397 to i64
  %_13.i399 = shl nuw i64 %_14.i398, 56
  %46 = getelementptr inbounds nuw i8, ptr %45, i64 1
  %_19.i402 = load i8, ptr %46, align 1, !alias.scope !2632, !noalias !2627, !noundef !136
  %_18.i403 = zext i8 %_19.i402 to i64
  %_17.i = shl nuw nsw i64 %_18.i403, 48
  %_12.i404 = or disjoint i64 %_17.i, %_13.i399
  %47 = getelementptr inbounds nuw i8, ptr %45, i64 2
  %_25.i408 = load i8, ptr %47, align 1, !alias.scope !2632, !noalias !2627, !noundef !136
  %_24.i409 = zext i8 %_25.i408 to i64
  %_23.i = shl nuw nsw i64 %_24.i409, 40
  %_11.i410 = or disjoint i64 %_12.i404, %_23.i
  %48 = getelementptr inbounds nuw i8, ptr %45, i64 3
  %_31.i = load i8, ptr %48, align 1, !alias.scope !2632, !noalias !2627, !noundef !136
  %_30.i414 = zext i8 %_31.i to i64
  %_29.i415 = shl nuw nsw i64 %_30.i414, 32
  %_10.i416 = or disjoint i64 %_11.i410, %_29.i415
  %49 = getelementptr inbounds nuw i8, ptr %45, i64 4
  %_37.i = load i8, ptr %49, align 1, !alias.scope !2632, !noalias !2627, !noundef !136
  %_36.i418 = zext i8 %_37.i to i64
  %_35.i419 = shl nuw nsw i64 %_36.i418, 24
  %_9.i420 = or disjoint i64 %_10.i416, %_35.i419
  %50 = getelementptr inbounds nuw i8, ptr %45, i64 5
  %_43.i = load i8, ptr %50, align 1, !alias.scope !2632, !noalias !2627, !noundef !136
  %_42.i = zext i8 %_43.i to i64
  %_41.i423 = shl nuw nsw i64 %_42.i, 16
  %_8.i424 = or disjoint i64 %_9.i420, %_41.i423
  %51 = getelementptr inbounds nuw i8, ptr %45, i64 6
  %_49.i427 = load i8, ptr %51, align 1, !alias.scope !2632, !noalias !2627, !noundef !136
  %_48.i = zext i8 %_49.i427 to i64
  %_47.i = shl nuw nsw i64 %_48.i, 8
  %_7.i428 = or i64 %_8.i424, %_47.i
  %52 = getelementptr inbounds nuw i8, ptr %45, i64 7
  %_54.i = load i8, ptr %52, align 1, !alias.scope !2632, !noalias !2627, !noundef !136
  %_53.i = zext i8 %_54.i to i64
  %53 = or i64 %_7.i428, %_53.i
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit: ; preds = %bb1.i390, %bb2.i393
  %_0.sroa.0.0.i432 = phi i64 [ %53, %bb2.i393 ], [ 0, %bb1.i390 ]
  %54 = icmp eq i64 %_0.sroa.0.0.i500, %_0.sroa.0.0.i432
  br i1 %54, label %bb2.i133, label %bb17.i105.thread

bb17.i105.thread:                                 ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit
  %_0.sroa.0.0.i432.lcssa = phi i64 [ %_0.sroa.0.0.i432, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit ]
  %_0.sroa.0.0.i500.lcssa2843 = phi i64 [ %_0.sroa.0.0.i500, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit ]
  %k.sroa.0.0.i1042153.lcssa2842 = phi i64 [ %k.sroa.0.0.i1042153, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit ]
  %x.i148 = xor i64 %_0.sroa.0.0.i432.lcssa, %_0.sroa.0.0.i500.lcssa2843
  %55 = tail call range(i64 0, 65) i64 @llvm.ctlz.i64(i64 %x.i148, i1 true)
  %_2220.i149 = lshr i64 %55, 3
  %_24.0.i150 = or disjoint i64 %_2220.i149, %k.sroa.0.0.i1042153.lcssa2842
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit159

bb21.i115:                                        ; preds = %bb17.i105, %bb24.i125
  %k.sroa.0.2.i1082156 = phi i64 [ %k.sroa.0.3.i130, %bb24.i125 ], [ %33, %bb17.i105 ]
  %_32.0.i113 = add nuw nsw i64 %k.sroa.0.2.i1082156, %start1.sroa.0.0.i2161
  %_34.i116 = icmp samesign ult i64 %_32.0.i113, %input.1
  br i1 %_34.i116, label %bb22.i118, label %panic6.i117

bb22.i118:                                        ; preds = %bb21.i115
  %56 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_32.0.i113
  %_29.i119 = load i8, ptr %56, align 1, !alias.scope !2636, !noalias !2627, !noundef !136
  %_38.0.i120 = add i64 %k.sroa.0.2.i1082156, %p.sroa.0.1.i2228.fr
  %_38.1.i121 = icmp ult i64 %_38.0.i120, %p.sroa.0.1.i2228.fr
  br i1 %_38.1.i121, label %panic7.i131, label %bb23.i122

panic6.i117:                                      ; preds = %bb21.i115
  %_32.0.i113.lcssa2844 = phi i64 [ %_32.0.i113, %bb21.i115 ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_32.0.i113.lcssa2844, i64 noundef range(i64 0, -9223372036854775808) %input.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_88632784907d7d84d4dbb3c61bd04ae5) #13, !noalias !2627
  unreachable

bb23.i122:                                        ; preds = %bb22.i118
  %_39.i123 = icmp ult i64 %_38.0.i120, %input.1
  br i1 %_39.i123, label %bb24.i125, label %panic8.i124

panic7.i131:                                      ; preds = %bb22.i118
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_747cf99f751d00e13712f3b323161078) #13, !noalias !2627
  unreachable

bb24.i125:                                        ; preds = %bb23.i122
  %57 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_38.0.i120
  %_35.i126 = load i8, ptr %57, align 1, !alias.scope !2636, !noalias !2627, !noundef !136
  %_28.i127 = icmp eq i8 %_29.i119, %_35.i126
  %_40.0.i128 = zext i1 %_28.i127 to i64
  %k.sroa.0.3.i130 = add nuw nsw i64 %k.sroa.0.2.i1082156, %_40.0.i128
  %_26.i109 = icmp samesign ult i64 %k.sroa.0.3.i130, %spec.store.select3.i10
  %or.cond.i110 = select i1 %_28.i127, i1 %_26.i109, i1 false
  br i1 %or.cond.i110, label %bb21.i115, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit159

panic8.i124:                                      ; preds = %bb23.i122
  %_38.0.i120.lcssa2848 = phi i64 [ %_38.0.i120, %bb23.i122 ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_38.0.i120.lcssa2848, i64 noundef range(i64 0, -9223372036854775808) %input.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_45688f0cd226461942a9ccd1c478fc80) #13, !noalias !2627
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit159: ; preds = %bb24.i125, %bb17.i105.thread, %bb17.i105
  %k.sroa.0.2.i108.lcssa = phi i64 [ %33, %bb17.i105 ], [ %_24.0.i150, %bb17.i105.thread ], [ %k.sroa.0.3.i130, %bb24.i125 ]
  %_46.i = icmp ugt i64 %k.sroa.0.2.i108.lcssa, %have.sroa.0.0.i2160
  br i1 %_46.i, label %bb19.i, label %bb37.i

bb19.i:                                           ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit159
  %_51.not.i = icmp ult i64 %k.sroa.0.2.i108.lcssa, %spec.store.select.i16
  br i1 %_51.not.i, label %bb26.i, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit

bb26.i:                                           ; preds = %bb19.i
  %_55.0.i = add i64 %k.sroa.0.2.i108.lcssa, %p.sroa.0.1.i2228.fr
  %_55.1.i = icmp ult i64 %_55.0.i, %p.sroa.0.1.i2228.fr
  br i1 %_55.1.i, label %panic7.i, label %bb27.i

bb27.i:                                           ; preds = %bb26.i
  %_53.not.i = icmp ult i64 %_55.0.i, %input.1
  br i1 %_53.not.i, label %bb31.i, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit

panic7.i:                                         ; preds = %bb26.i
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_15b4ce25bced7a5ce053340a71ef7d4e) #13, !noalias !2627
  unreachable

bb31.i:                                           ; preds = %bb27.i
  %58 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_55.0.i
  %59 = load i8, ptr %58, align 1, !alias.scope !2624, !noalias !2627, !noundef !136
  br label %bb37.i

bb37.i:                                           ; preds = %bb31.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit159, %bb16.i19
  %pb.sroa.0.3.i = phi i8 [ %pb.sroa.0.1.i2157, %bb16.i19 ], [ %pb.sroa.0.1.i2157, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit159 ], [ %59, %bb31.i ]
  %bd.sroa.0.2.i = phi i64 [ %bd.sroa.0.0.i2158, %bb16.i19 ], [ %bd.sroa.0.0.i2158, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit159 ], [ %d.i, %bb31.i ]
  %have.sroa.0.2.i = phi i64 [ %have.sroa.0.0.i2160, %bb16.i19 ], [ %have.sroa.0.0.i2160, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit159 ], [ %k.sroa.0.2.i108.lcssa, %bb31.i ]
  %_60.i21 = and i64 %start1.sroa.0.0.i2161, 32767
  %60 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_60.i21
  %_59.i = load i32, ptr %60, align 4, !alias.scope !2627, !noalias !2624, !noundef !136
  %nx.i = zext i32 %_59.i to i64
  %_64.i = icmp samesign ule i64 %start1.sroa.0.0.i2161, %nx.i
  %_66.0.i = add nsw i64 %depth.sroa.0.0.i2159, -1
  %_24.not.i = icmp eq i64 %_66.0.i, 0
  %or.cond = select i1 %_64.i, i1 true, i1 %_24.not.i
  br i1 %or.cond, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit, label %bb11.i18

_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit: ; preds = %bb19.i, %bb27.i, %bb37.i, %bb13.i, %bb11.i18
  %have.sroa.0.1.i2393 = phi i64 [ %have.sroa.0.0.i2160, %bb11.i18 ], [ %have.sroa.0.2.i, %bb37.i ], [ %have.sroa.0.0.i2160, %bb13.i ], [ %k.sroa.0.2.i108.lcssa, %bb27.i ], [ %k.sroa.0.2.i108.lcssa, %bb19.i ]
  %bd.sroa.0.1.i2392 = phi i64 [ %bd.sroa.0.0.i2158, %bb11.i18 ], [ %bd.sroa.0.2.i, %bb37.i ], [ %bd.sroa.0.0.i2158, %bb13.i ], [ %d.i, %bb27.i ], [ %d.i, %bb19.i ]
  %.not = icmp eq i64 %bd.sroa.0.1.i2392, 0
  br i1 %.not, label %bb154.i, label %bb16.i.preheader

bb16.i.preheader:                                 ; preds = %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit
  %_39.i2185 = icmp ult i64 %have.sroa.0.1.i2393, 64
  br i1 %_39.i2185, label %bb18.i.preheader, label %bb63.i

bb18.i.preheader:                                 ; preds = %bb16.i.preheader
  %61 = xor i64 %p.sroa.0.1.i2228.fr, -1
  %62 = add i64 %input.1, %61
  %umax2809 = call i64 @llvm.umax.i64(i64 %_8.0.i, i64 %_29.0.i)
  %umax2810 = call i64 @llvm.umax.i64(i64 %nt.sroa.0.1.i2231, i64 %out.1)
  br label %bb18.i

bb8.i:                                            ; preds = %bb5.i, %bb8.i
  %ins.sroa.0.1.i2151 = phi i64 [ %_23.0.i, %bb8.i ], [ %ins.sroa.0.0.i2227, %bb5.i ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2639)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2642)
  %63 = getelementptr inbounds nuw i8, ptr %input.0, i64 %ins.sroa.0.1.i2151
  %64 = load i32, ptr %63, align 1
  %65 = call i32 @llvm.bswap.i32(i32 %64)
  %66 = zext i32 %65 to i64
  %67 = mul i64 %66, -7046029254386353131
  %68 = lshr i64 %67, 48
  %69 = getelementptr inbounds nuw [4 x i8], ptr %head.i, i64 %68
  %old.i.i = load i32, ptr %69, align 4, !alias.scope !2639, !noalias !2644, !noundef !136
  %_16.i.i = and i64 %ins.sroa.0.1.i2151, 32767
  %70 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_16.i.i
  store i32 %old.i.i, ptr %70, align 4, !alias.scope !2642, !noalias !2646
  %71 = trunc i64 %ins.sroa.0.1.i2151 to i32
  store i32 %71, ptr %69, align 4, !alias.scope !2639, !noalias !2644
  %_23.0.i = add nuw nsw i64 %ins.sroa.0.1.i2151, 1
  %exitcond.not = icmp eq i64 %_23.0.i, %p.sroa.0.1.i2228.fr
  br i1 %exitcond.not, label %bb11.i, label %bb8.i

bb154.i:                                          ; preds = %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2647)
  %_9.i177 = icmp ult i64 %nt.sroa.0.1.i2231, %out.1
  br i1 %_9.i177, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit182, label %panic1.i178

panic1.i178:                                      ; preds = %bb154.i
  %nt.sroa.0.1.i2231.lcssa2915 = phi i64 [ %nt.sroa.0.1.i2231, %bb154.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %nt.sroa.0.1.i2231.lcssa2915, i64 noundef range(i64 0, 2305843009213693952) %out.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_f5cc78c6143d87a95e73f58df7e9bb32) #13, !noalias !2650
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit182: ; preds = %bb154.i
  %72 = getelementptr inbounds nuw [4 x i8], ptr %out.0, i64 %nt.sroa.0.1.i2231
  %73 = extractelement <4 x i8> %24, i64 0
  %74 = zext i8 %73 to i32
  store i32 %74, ptr %72, align 4, !alias.scope !2647, !noalias !2652
  %_219.0.i = add i64 %miss.sroa.0.0.i2230, 1
  %_219.1.i = icmp eq i64 %miss.sroa.0.0.i2230, -1
  br i1 %_219.1.i, label %panic5.i, label %bb157.i

bb157.i:                                          ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit182
  %75 = lshr i64 %_219.0.i, 6
  %nt.sroa.0.3.i2163 = add nuw nsw i64 %nt.sroa.0.1.i2231, 1
  %_225.i2164 = icmp ne i64 %75, 0
  %_227.i2165 = icmp ult i64 %_29.0.i, %_8.0.i
  %or.cond45.i2166 = select i1 %_225.i2164, i1 %_227.i2165, i1 false
  br i1 %or.cond45.i2166, label %bb164.i.preheader, label %bb170.i

bb164.i.preheader:                                ; preds = %bb157.i
  %spec.store.select.i = tail call i64 @llvm.umin.i64(i64 %75, i64 1000000)
  %76 = sub i64 %19, %p.sroa.0.1.i2228.fr
  %77 = add nsw i64 %spec.store.select.i, -1
  %umin2811 = call i64 @llvm.umin.i64(i64 %76, i64 %77)
  %78 = freeze i64 %umin2811
  %79 = xor i64 %nt.sroa.0.1.i2231, -1
  %80 = add nsw i64 %out.1, %79
  %umin2812 = call i64 @llvm.umin.i64(i64 %78, i64 %80)
  %81 = add i64 %umin2812, 1
  %min.iters.check = icmp ult i64 %81, 9
  br i1 %min.iters.check, label %bb164.i.preheader2840, label %vector.ph

bb164.i.preheader2840:                            ; preds = %vector.body, %bb164.i.preheader
  %nt.sroa.0.3.i2169.ph = phi i64 [ %nt.sroa.0.3.i2163, %bb164.i.preheader ], [ %84, %vector.body ]
  %p.sroa.0.3.i2168.ph = phi i64 [ %_29.0.i, %bb164.i.preheader ], [ %85, %vector.body ]
  %step.sroa.0.0.i2167.ph = phi i64 [ %spec.store.select.i, %bb164.i.preheader ], [ %86, %vector.body ]
  br label %bb164.i

vector.ph:                                        ; preds = %bb164.i.preheader
  %n.mod.vf = and i64 %81, 7
  %82 = icmp eq i64 %n.mod.vf, 0
  %83 = select i1 %82, i64 8, i64 %n.mod.vf
  %n.vec = sub nuw i64 %81, %83
  %84 = add i64 %nt.sroa.0.3.i2163, %n.vec
  %85 = add i64 %_29.0.i, %n.vec
  %86 = sub i64 %spec.store.select.i, %n.vec
  %87 = getelementptr i8, ptr %input.0, i64 %_29.0.i
  %88 = getelementptr [4 x i8], ptr %out.0, i64 %nt.sroa.0.3.i2163
  br label %vector.body

vector.body:                                      ; preds = %vector.body, %vector.ph
  %index = phi i64 [ 0, %vector.ph ], [ %index.next, %vector.body ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2653)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2656)
  %89 = getelementptr i8, ptr %87, i64 %index
  %90 = getelementptr inbounds nuw i8, ptr %89, i64 4
  %wide.load = load <4 x i8>, ptr %89, align 1, !alias.scope !2653, !noalias !2656
  %wide.load2813 = load <4 x i8>, ptr %90, align 1, !alias.scope !2653, !noalias !2656
  %91 = getelementptr [4 x i8], ptr %88, i64 %index
  %92 = zext <4 x i8> %wide.load to <4 x i32>
  %93 = zext <4 x i8> %wide.load2813 to <4 x i32>
  %94 = getelementptr inbounds nuw i8, ptr %91, i64 16
  store <4 x i32> %92, ptr %91, align 4, !alias.scope !2656, !noalias !2653
  store <4 x i32> %93, ptr %94, align 4, !alias.scope !2656, !noalias !2653
  %index.next = add nuw i64 %index, 8
  %95 = icmp eq i64 %index.next, %n.vec
  br i1 %95, label %bb164.i.preheader2840, label %vector.body, !llvm.loop !2658

panic5.i:                                         ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit182
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_5047a97e092172d1cdcda63092b5e51f) #13
  unreachable

bb170.i:                                          ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit173, %bb157.i
  %p.sroa.0.3.i.lcssa = phi i64 [ %_29.0.i, %bb157.i ], [ %_231.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit173 ]
  %nt.sroa.0.3.i.lcssa = phi i64 [ %nt.sroa.0.3.i2163, %bb157.i ], [ %nt.sroa.0.3.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit173 ]
  %spec.select.i = tail call i64 @llvm.umax.i64(i64 %_29.0.i, i64 %p.sroa.0.3.i.lcssa)
  br label %bb174.i

bb164.i:                                          ; preds = %bb164.i.preheader2840, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit173
  %nt.sroa.0.3.i2169 = phi i64 [ %nt.sroa.0.3.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit173 ], [ %nt.sroa.0.3.i2169.ph, %bb164.i.preheader2840 ]
  %p.sroa.0.3.i2168 = phi i64 [ %_231.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit173 ], [ %p.sroa.0.3.i2168.ph, %bb164.i.preheader2840 ]
  %step.sroa.0.0.i2167 = phi i64 [ %_232.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit173 ], [ %step.sroa.0.0.i2167.ph, %bb164.i.preheader2840 ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2653)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2656)
  %exitcond2381.not = icmp eq i64 %nt.sroa.0.3.i2169, %out.1
  br i1 %exitcond2381.not, label %panic1.i169, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit173

panic1.i169:                                      ; preds = %bb164.i
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %out.1, i64 noundef range(i64 0, 2305843009213693952) %out.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_f5cc78c6143d87a95e73f58df7e9bb32) #13, !noalias !2659
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit173: ; preds = %bb164.i
  %96 = getelementptr inbounds nuw i8, ptr %input.0, i64 %p.sroa.0.3.i2168
  %_5.i171 = load i8, ptr %96, align 1, !alias.scope !2653, !noalias !2656, !noundef !136
  %97 = getelementptr inbounds nuw [4 x i8], ptr %out.0, i64 %nt.sroa.0.3.i2169
  %98 = zext i8 %_5.i171 to i32
  store i32 %98, ptr %97, align 4, !alias.scope !2656, !noalias !2653
  %_231.0.i = add nuw nsw i64 %p.sroa.0.3.i2168, 1
  %_232.0.i = add nsw i64 %step.sroa.0.0.i2167, -1
  %nt.sroa.0.3.i = add i64 %nt.sroa.0.3.i2169, 1
  %_225.i = icmp ne i64 %_232.0.i, 0
  %_227.i = icmp ult i64 %_231.0.i, %_8.0.i
  %or.cond45.i = select i1 %_225.i, i1 %_227.i, i1 false
  br i1 %or.cond45.i, label %bb164.i, label %bb170.i, !llvm.loop !2660

bb174.i:                                          ; preds = %bb150.i, %bb170.i
  %ins.sroa.0.3.i = phi i64 [ %spec.select140.i, %bb150.i ], [ %spec.select.i, %bb170.i ]
  %p.sroa.0.4.i = phi i64 [ %_19.0.i196, %bb150.i ], [ %p.sroa.0.3.i.lcssa, %bb170.i ]
  %miss.sroa.0.1.i = phi i64 [ 0, %bb150.i ], [ %_219.0.i, %bb170.i ]
  %nt.sroa.0.4.i = phi i64 [ %_17.0.i, %bb150.i ], [ %nt.sroa.0.3.i.lcssa, %bb170.i ]
  %_11.i = icmp ult i64 %p.sroa.0.4.i, %_8.0.i
  %_13.i = icmp ne i64 %_15.0.i, 0
  %or.cond.i = select i1 %_11.i, i1 %_13.i, i1 false
  br i1 %or.cond.i, label %bb5.i, label %bb177.i

bb18.i:                                           ; preds = %bb18.i.preheader, %bb59.i
  %indvars.iv2807 = phi i64 [ %62, %bb18.i.preheader ], [ %indvars.iv.next2808, %bb59.i ]
  %indvars.iv = phi i64 [ %_29.0.i, %bb18.i.preheader ], [ %indvars.iv.next, %bb59.i ]
  %nt.sroa.0.5.i2190 = phi i64 [ %nt.sroa.0.1.i2231, %bb18.i.preheader ], [ %_10.0.i164, %bb59.i ]
  %l.sroa.0.0.i2189 = phi i64 [ %have.sroa.0.1.i2393, %bb18.i.preheader ], [ %k.sroa.0.2.i.lcssa, %bb59.i ]
  %d.sroa.0.0.i2188 = phi i64 [ %bd.sroa.0.1.i2392, %bb18.i.preheader ], [ %d.i37, %bb59.i ]
  %p.sroa.0.5.i2187 = phi i64 [ %p.sroa.0.1.i2228.fr, %bb18.i.preheader ], [ %_44.0.i, %bb59.i ]
  %_44.0.i = add i64 %p.sroa.0.5.i2187, 1
  %umin = call i64 @llvm.umin.i64(i64 %indvars.iv2807, i64 258)
  %99 = and i64 %umin, 504
  %_41.i = icmp ult i64 %_44.0.i, %_8.0.i
  br i1 %_41.i, label %bb21.i, label %bb63.i

bb63.i:                                           ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit, %bb16.i52, %bb13.i50, %bb11.i36, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit682, %bb59.i, %bb18.i, %bb16.i.preheader
  %ins.sroa.0.4.i.lcssa = phi i64 [ %_29.0.i, %bb16.i.preheader ], [ %indvars.iv.next, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit ], [ %indvars.iv.next, %bb13.i50 ], [ %indvars.iv.next, %bb11.i36 ], [ %indvars.iv.next, %bb59.i ], [ %indvars.iv.next, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit682 ], [ %umax2809, %bb18.i ], [ %indvars.iv.next, %bb16.i52 ], [ %indvars.iv.next, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit ]
  %p.sroa.0.5.i.lcssa = phi i64 [ %p.sroa.0.1.i2228.fr, %bb16.i.preheader ], [ %p.sroa.0.5.i2187, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit ], [ %p.sroa.0.5.i2187, %bb13.i50 ], [ %p.sroa.0.5.i2187, %bb11.i36 ], [ %_44.0.i, %bb59.i ], [ %p.sroa.0.5.i2187, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit682 ], [ %p.sroa.0.5.i2187, %bb18.i ], [ %p.sroa.0.5.i2187, %bb16.i52 ], [ %p.sroa.0.5.i2187, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit ]
  %d.sroa.0.0.i.lcssa = phi i64 [ %bd.sroa.0.1.i2392, %bb16.i.preheader ], [ %d.sroa.0.0.i2188, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit ], [ %d.sroa.0.0.i2188, %bb13.i50 ], [ %d.sroa.0.0.i2188, %bb11.i36 ], [ %d.i37, %bb59.i ], [ %d.sroa.0.0.i2188, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit682 ], [ %d.sroa.0.0.i2188, %bb18.i ], [ %d.sroa.0.0.i2188, %bb16.i52 ], [ %d.sroa.0.0.i2188, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit ]
  %l.sroa.0.0.i.lcssa = phi i64 [ %have.sroa.0.1.i2393, %bb16.i.preheader ], [ %l.sroa.0.0.i2189, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit ], [ %l.sroa.0.0.i2189, %bb13.i50 ], [ %l.sroa.0.0.i2189, %bb11.i36 ], [ %k.sroa.0.2.i.lcssa, %bb59.i ], [ %l.sroa.0.0.i2189, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit682 ], [ %l.sroa.0.0.i2189, %bb18.i ], [ %l.sroa.0.0.i2189, %bb16.i52 ], [ %l.sroa.0.0.i2189, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit ]
  %nt.sroa.0.5.i.lcssa = phi i64 [ %nt.sroa.0.1.i2231, %bb16.i.preheader ], [ %nt.sroa.0.5.i2190, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit ], [ %nt.sroa.0.5.i2190, %bb13.i50 ], [ %nt.sroa.0.5.i2190, %bb11.i36 ], [ %_10.0.i164, %bb59.i ], [ %nt.sroa.0.5.i2190, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit682 ], [ %nt.sroa.0.5.i2190, %bb18.i ], [ %nt.sroa.0.5.i2190, %bb16.i52 ], [ %nt.sroa.0.5.i2190, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit ]
  %100 = add i64 %nt.sroa.0.5.i.lcssa, -1
  %101 = icmp ult i64 %100, %out.1
  %_110.i2205 = icmp ult i64 %l.sroa.0.0.i.lcssa, 258
  %or.cond49.i2206 = select i1 %101, i1 %_110.i2205, i1 false
  %_112.i2207 = icmp ult i64 %d.sroa.0.0.i.lcssa, %p.sroa.0.5.i.lcssa
  %or.cond139.i2208 = and i1 %or.cond49.i2206, %_112.i2207
  br i1 %or.cond139.i2208, label %bb71.i, label %bb116.i

bb21.i:                                           ; preds = %bb18.i
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2661)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2664)
  %102 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_44.0.i
  %103 = getelementptr inbounds nuw i8, ptr %input.0, i64 %p.sroa.0.5.i2187
  %104 = load i32, ptr %102, align 1
  %105 = call i32 @llvm.bswap.i32(i32 %104)
  %106 = zext i32 %105 to i64
  %107 = mul i64 %106, -7046029254386353131
  %108 = lshr i64 %107, 48
  %109 = getelementptr inbounds nuw [4 x i8], ptr %head.i, i64 %108
  %old.i166.i = load i32, ptr %109, align 4, !alias.scope !2661, !noalias !2666, !noundef !136
  %_16.i167.i = and i64 %_44.0.i, 32767
  %110 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_16.i167.i
  store i32 %old.i166.i, ptr %110, align 4, !alias.scope !2664, !noalias !2668
  %111 = trunc i64 %_44.0.i to i32
  store i32 %111, ptr %109, align 4, !alias.scope !2661, !noalias !2666
  %_0.i168.i = zext i32 %old.i166.i to i64
  %indvars.iv.next = add nuw i64 %indvars.iv, 1
  %_56.0.i = add nsw i64 %l.sroa.0.0.i2189, -1
  %spec.select.i3 = tail call i64 @llvm.umax.i64(i64 %_56.0.i, i64 3)
  %_13.0.i = sub nuw nsw i64 %input.1, %_44.0.i
  %spec.store.select3.i = tail call i64 @llvm.umin.i64(i64 %_13.0.i, i64 258)
  %_19.0.i24 = add nuw i64 %spec.select.i3, %_44.0.i
  %_16.i25 = icmp ult i64 %_19.0.i24, %input.1
  br i1 %_16.i25, label %bb7.i79, label %bb11.i36

bb7.i79:                                          ; preds = %bb21.i
  %112 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_19.0.i24
  %113 = load i8, ptr %112, align 1, !alias.scope !2669, !noalias !2672, !noundef !136
  br label %bb11.i36

bb11.i36:                                         ; preds = %bb21.i, %bb7.i79
  %pb.sroa.0.0.i27 = phi i8 [ %113, %bb7.i79 ], [ 0, %bb21.i ]
  %d.i37 = sub nsw i64 %_44.0.i, %_0.i168.i
  %_29.i38 = add nsw i64 %d.i37, -1
  %_28.i39 = icmp ult i64 %_29.i38, 32768
  br i1 %_28.i39, label %bb13.i50, label %bb63.i

bb13.i50:                                         ; preds = %bb11.i36
  %_34.0.i48 = add nuw nsw i64 %spec.select.i3, %_0.i168.i
  %_30.i51 = icmp ult i64 %_34.0.i48, %input.1
  br i1 %_30.i51, label %bb16.i52, label %bb63.i

bb16.i52:                                         ; preds = %bb13.i50
  %114 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_34.0.i48
  %_36.i53 = load i8, ptr %114, align 1, !alias.scope !2669, !noalias !2672, !noundef !136
  %_35.i54 = icmp eq i8 %_36.i53, %pb.sroa.0.0.i27
  br i1 %_35.i54, label %bb2.i.preheader, label %bb63.i

bb2.i.preheader:                                  ; preds = %bb16.i52
  %_19.1.i.not = icmp ugt i64 %indvars.iv, %p.sroa.0.5.i2187
  br label %bb2.i

bb2.i:                                            ; preds = %bb2.i.preheader, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit571
  %k.sroa.0.0.i2173 = phi i64 [ %_10.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit571 ], [ 0, %bb2.i.preheader ]
  %_10.0.i = add nuw nsw i64 %k.sroa.0.0.i2173, 8
  %_7.not.i = icmp samesign ugt i64 %_10.0.i, %spec.store.select3.i
  br i1 %_7.not.i, label %bb17.i82, label %bb4.i

bb4.i:                                            ; preds = %bb2.i
  %_15.0.i94 = add nuw nsw i64 %k.sroa.0.0.i2173, %_0.i168.i
  %_5.0.i574 = add nuw nsw i64 %_15.0.i94, 8
  %_3.not.i575 = icmp samesign ugt i64 %_5.0.i574, %input.1
  br i1 %_3.not.i575, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit640, label %bb2.i576

bb17.i82:                                         ; preds = %bb2.i
  %_26.i2174 = icmp samesign ult i64 %99, %spec.store.select3.i
  br i1 %_26.i2174, label %bb20.i, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit

bb2.i576:                                         ; preds = %bb4.i
  %115 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_15.0.i94
  %_15.i580 = load i8, ptr %115, align 1, !alias.scope !2674, !noalias !2672, !noundef !136
  %_14.i581 = zext i8 %_15.i580 to i64
  %_13.i582 = shl nuw i64 %_14.i581, 56
  %116 = getelementptr inbounds nuw i8, ptr %115, i64 1
  %_19.i587 = load i8, ptr %116, align 1, !alias.scope !2674, !noalias !2672, !noundef !136
  %_18.i588 = zext i8 %_19.i587 to i64
  %_17.i589 = shl nuw nsw i64 %_18.i588, 48
  %_12.i590 = or disjoint i64 %_17.i589, %_13.i582
  %117 = getelementptr inbounds nuw i8, ptr %115, i64 2
  %_25.i595 = load i8, ptr %117, align 1, !alias.scope !2674, !noalias !2672, !noundef !136
  %_24.i596 = zext i8 %_25.i595 to i64
  %_23.i597 = shl nuw nsw i64 %_24.i596, 40
  %_11.i598 = or disjoint i64 %_12.i590, %_23.i597
  %118 = getelementptr inbounds nuw i8, ptr %115, i64 3
  %_31.i603 = load i8, ptr %118, align 1, !alias.scope !2674, !noalias !2672, !noundef !136
  %_30.i604 = zext i8 %_31.i603 to i64
  %_29.i605 = shl nuw nsw i64 %_30.i604, 32
  %_10.i606 = or disjoint i64 %_11.i598, %_29.i605
  %119 = getelementptr inbounds nuw i8, ptr %115, i64 4
  %_37.i611 = load i8, ptr %119, align 1, !alias.scope !2674, !noalias !2672, !noundef !136
  %_36.i612 = zext i8 %_37.i611 to i64
  %_35.i613 = shl nuw nsw i64 %_36.i612, 24
  %_9.i614 = or disjoint i64 %_10.i606, %_35.i613
  %120 = getelementptr inbounds nuw i8, ptr %115, i64 5
  %_43.i619 = load i8, ptr %120, align 1, !alias.scope !2674, !noalias !2672, !noundef !136
  %_42.i620 = zext i8 %_43.i619 to i64
  %_41.i621 = shl nuw nsw i64 %_42.i620, 16
  %_8.i622 = or disjoint i64 %_9.i614, %_41.i621
  %121 = getelementptr inbounds nuw i8, ptr %115, i64 6
  %_49.i627 = load i8, ptr %121, align 1, !alias.scope !2674, !noalias !2672, !noundef !136
  %_48.i628 = zext i8 %_49.i627 to i64
  %_47.i629 = shl nuw nsw i64 %_48.i628, 8
  %_7.i630 = or i64 %_8.i622, %_47.i629
  %122 = getelementptr inbounds nuw i8, ptr %115, i64 7
  %_54.i635 = load i8, ptr %122, align 1, !alias.scope !2674, !noalias !2672, !noundef !136
  %_53.i636 = zext i8 %_54.i635 to i64
  %123 = or i64 %_7.i630, %_53.i636
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit640

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit640: ; preds = %bb4.i, %bb2.i576
  %_0.sroa.0.0.i638 = phi i64 [ %123, %bb2.i576 ], [ 0, %bb4.i ]
  %_19.0.i96 = add nuw i64 %k.sroa.0.0.i2173, %_44.0.i
  br i1 %_19.1.i.not, label %bb7.i97, label %panic2.i

bb7.i97:                                          ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit640
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2677)
  %_5.1.i503 = icmp ugt i64 %_19.0.i96, -9
  br i1 %_5.1.i503, label %panic.i570, label %bb1.i504

bb1.i504:                                         ; preds = %bb7.i97
  %_5.0.i505 = add nuw i64 %_19.0.i96, 8
  %_3.not.i506 = icmp ugt i64 %_5.0.i505, %input.1
  br i1 %_3.not.i506, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit571, label %bb2.i507

panic.i570:                                       ; preds = %bb7.i97
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_c9d76a7bf6f333d6169298e9d093a546) #13, !noalias !2680
  unreachable

bb2.i507:                                         ; preds = %bb1.i504
  %124 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_19.0.i96
  %_15.i511 = load i8, ptr %124, align 1, !alias.scope !2677, !noalias !2672, !noundef !136
  %_14.i512 = zext i8 %_15.i511 to i64
  %_13.i513 = shl nuw i64 %_14.i512, 56
  %125 = getelementptr inbounds nuw i8, ptr %124, i64 1
  %_19.i518 = load i8, ptr %125, align 1, !alias.scope !2677, !noalias !2672, !noundef !136
  %_18.i519 = zext i8 %_19.i518 to i64
  %_17.i520 = shl nuw nsw i64 %_18.i519, 48
  %_12.i521 = or disjoint i64 %_17.i520, %_13.i513
  %126 = getelementptr inbounds nuw i8, ptr %124, i64 2
  %_25.i526 = load i8, ptr %126, align 1, !alias.scope !2677, !noalias !2672, !noundef !136
  %_24.i527 = zext i8 %_25.i526 to i64
  %_23.i528 = shl nuw nsw i64 %_24.i527, 40
  %_11.i529 = or disjoint i64 %_12.i521, %_23.i528
  %127 = getelementptr inbounds nuw i8, ptr %124, i64 3
  %_31.i534 = load i8, ptr %127, align 1, !alias.scope !2677, !noalias !2672, !noundef !136
  %_30.i535 = zext i8 %_31.i534 to i64
  %_29.i536 = shl nuw nsw i64 %_30.i535, 32
  %_10.i537 = or disjoint i64 %_11.i529, %_29.i536
  %128 = getelementptr inbounds nuw i8, ptr %124, i64 4
  %_37.i542 = load i8, ptr %128, align 1, !alias.scope !2677, !noalias !2672, !noundef !136
  %_36.i543 = zext i8 %_37.i542 to i64
  %_35.i544 = shl nuw nsw i64 %_36.i543, 24
  %_9.i545 = or disjoint i64 %_10.i537, %_35.i544
  %129 = getelementptr inbounds nuw i8, ptr %124, i64 5
  %_43.i550 = load i8, ptr %129, align 1, !alias.scope !2677, !noalias !2672, !noundef !136
  %_42.i551 = zext i8 %_43.i550 to i64
  %_41.i552 = shl nuw nsw i64 %_42.i551, 16
  %_8.i553 = or disjoint i64 %_9.i545, %_41.i552
  %130 = getelementptr inbounds nuw i8, ptr %124, i64 6
  %_49.i558 = load i8, ptr %130, align 1, !alias.scope !2677, !noalias !2672, !noundef !136
  %_48.i559 = zext i8 %_49.i558 to i64
  %_47.i560 = shl nuw nsw i64 %_48.i559, 8
  %_7.i561 = or i64 %_8.i553, %_47.i560
  %131 = getelementptr inbounds nuw i8, ptr %124, i64 7
  %_54.i566 = load i8, ptr %131, align 1, !alias.scope !2677, !noalias !2672, !noundef !136
  %_53.i567 = zext i8 %_54.i566 to i64
  %132 = or i64 %_7.i561, %_53.i567
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit571

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit571: ; preds = %bb1.i504, %bb2.i507
  %_0.sroa.0.0.i569 = phi i64 [ %132, %bb2.i507 ], [ 0, %bb1.i504 ]
  %133 = icmp eq i64 %_0.sroa.0.0.i638, %_0.sroa.0.0.i569
  br i1 %133, label %bb2.i, label %bb17.i82.thread

panic2.i:                                         ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit640
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_4b162fbcea1d677c71ea8df2a43606da) #13, !noalias !2672
  unreachable

bb17.i82.thread:                                  ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit571
  %_0.sroa.0.0.i569.lcssa = phi i64 [ %_0.sroa.0.0.i569, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit571 ]
  %_0.sroa.0.0.i638.lcssa2854 = phi i64 [ %_0.sroa.0.0.i638, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit571 ]
  %k.sroa.0.0.i2173.lcssa2852 = phi i64 [ %k.sroa.0.0.i2173, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit571 ]
  %x.i = xor i64 %_0.sroa.0.0.i569.lcssa, %_0.sroa.0.0.i638.lcssa2854
  %134 = tail call range(i64 0, 65) i64 @llvm.ctlz.i64(i64 %x.i, i1 true)
  %_2220.i = lshr i64 %134, 3
  %_24.0.i = or disjoint i64 %_2220.i, %k.sroa.0.0.i2173.lcssa2852
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit

bb20.i:                                           ; preds = %bb17.i82, %bb24.i
  %k.sroa.0.2.i2176 = phi i64 [ %k.sroa.0.3.i, %bb24.i ], [ %99, %bb17.i82 ]
  %_32.0.i = add i64 %k.sroa.0.2.i2176, %_0.i168.i
  %_32.1.i = icmp ult i64 %_32.0.i, %_0.i168.i
  br i1 %_32.1.i, label %panic5.i92, label %bb21.i86

bb21.i86:                                         ; preds = %bb20.i
  %_34.i = icmp ult i64 %_32.0.i, %input.1
  br i1 %_34.i, label %bb22.i, label %panic6.i

panic5.i92:                                       ; preds = %bb20.i
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_5a9bdb3e7c586b9d38e8a8e17b8c9181) #13, !noalias !2672
  unreachable

bb22.i:                                           ; preds = %bb21.i86
  %135 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_32.0.i
  %_29.i87 = load i8, ptr %135, align 1, !alias.scope !2681, !noalias !2672, !noundef !136
  %_38.0.i = add i64 %k.sroa.0.2.i2176, %_44.0.i
  %_38.1.i.not = icmp ugt i64 %_38.0.i, %p.sroa.0.5.i2187
  br i1 %_38.1.i.not, label %bb23.i, label %panic7.i91

panic6.i:                                         ; preds = %bb21.i86
  %_32.0.i.lcssa2855 = phi i64 [ %_32.0.i, %bb21.i86 ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_32.0.i.lcssa2855, i64 noundef range(i64 0, -9223372036854775808) %input.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_88632784907d7d84d4dbb3c61bd04ae5) #13, !noalias !2672
  unreachable

bb23.i:                                           ; preds = %bb22.i
  %_39.i88 = icmp ult i64 %_38.0.i, %input.1
  br i1 %_39.i88, label %bb24.i, label %panic8.i

panic7.i91:                                       ; preds = %bb22.i
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_747cf99f751d00e13712f3b323161078) #13, !noalias !2672
  unreachable

bb24.i:                                           ; preds = %bb23.i
  %136 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_38.0.i
  %_35.i89 = load i8, ptr %136, align 1, !alias.scope !2681, !noalias !2672, !noundef !136
  %_28.i90 = icmp eq i8 %_29.i87, %_35.i89
  %_40.0.i = zext i1 %_28.i90 to i64
  %k.sroa.0.3.i = add nuw i64 %k.sroa.0.2.i2176, %_40.0.i
  %_26.i = icmp ult i64 %k.sroa.0.3.i, %spec.store.select3.i
  %or.cond.i84 = select i1 %_28.i90, i1 %_26.i, i1 false
  br i1 %or.cond.i84, label %bb20.i, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit

panic8.i:                                         ; preds = %bb23.i
  %_38.0.i.lcssa2859 = phi i64 [ %_38.0.i, %bb23.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_38.0.i.lcssa2859, i64 noundef range(i64 0, -9223372036854775808) %input.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_45688f0cd226461942a9ccd1c478fc80) #13, !noalias !2672
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit: ; preds = %bb24.i, %bb17.i82.thread, %bb17.i82
  %k.sroa.0.2.i.lcssa = phi i64 [ %99, %bb17.i82 ], [ %_24.0.i, %bb17.i82.thread ], [ %k.sroa.0.3.i, %bb24.i ]
  %_46.i68 = icmp ugt i64 %k.sroa.0.2.i.lcssa, %spec.select.i3
  br i1 %_46.i68, label %bb19.i69, label %bb63.i

bb19.i69:                                         ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit
  %137 = add i64 %k.sroa.0.2.i.lcssa, -11
  %or.cond.i641 = icmp ult i64 %137, 247
  br i1 %or.cond.i641, label %bb6.i, label %bb7.i642

bb7.i642:                                         ; preds = %bb6.i, %bb19.i69
  %c.sroa.0.0.i = phi i32 [ %140, %bb6.i ], [ 168, %bb19.i69 ]
  %_17.i643 = icmp ugt i64 %d.i37, 4
  br i1 %_17.i643, label %bb12.i652, label %bb13.i644

bb6.i:                                            ; preds = %bb19.i69
  %138 = trunc nuw nsw i64 %k.sroa.0.2.i.lcssa to i32
  %_11.i655 = add nsw i32 %138, -3
  %_10.i656 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_11.i655, i1 false)
  %139 = shl nuw nsw i32 %_10.i656, 4
  %140 = sub nuw nsw i32 632, %139
  br label %bb7.i642

bb13.i644:                                        ; preds = %bb12.i652, %bb7.i642
  %c.sroa.0.1.i = phi i32 [ %144, %bb12.i652 ], [ %c.sroa.0.0.i, %bb7.i642 ]
  %_29.i645 = trunc i64 %k.sroa.0.2.i.lcssa to i32
  %141 = add i32 %_29.i645, -33554432
  %_30.1.i = icmp ult i32 %141, -67108864
  br i1 %_30.1.i, label %panic8.i649, label %bb14.i646

bb12.i652:                                        ; preds = %bb7.i642
  %142 = trunc nuw i64 %d.i37 to i32
  %_22.i651 = add nsw i32 %142, -1
  %_21.i653 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_22.i651, i1 true)
  %143 = shl nuw nsw i32 %_21.i653, 4
  %reass.sub = sub nsw i32 %c.sroa.0.0.i, %143
  %144 = add nsw i32 %reass.sub, 480
  br label %bb13.i644

bb14.i646:                                        ; preds = %bb13.i644
  %_30.0.i = shl nsw i32 %_29.i645, 6
  %145 = tail call { i32, i1 } @llvm.ssub.with.overflow.i32(i32 %_30.0.i, i32 %c.sroa.0.1.i)
  %_31.1.i = extractvalue { i32, i1 } %145, 1
  br i1 %_31.1.i, label %panic9.i648, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit

panic8.i649:                                      ; preds = %bb13.i644
; call core::panicking::panic_const::panic_const_mul_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_mul_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_de42051d6ce5797cfcaece5556197823) #13, !noalias !2672
  unreachable

panic9.i648:                                      ; preds = %bb14.i646
; call core::panicking::panic_const::panic_const_sub_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_de42051d6ce5797cfcaece5556197823) #13, !noalias !2672
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit: ; preds = %bb14.i646
  %_31.0.i = extractvalue { i32, i1 } %145, 0
  %_49.i = icmp sle i32 %_31.0.i, -1000000
  %.not2838 = icmp eq i64 %d.i37, 0
  %or.cond2919 = or i1 %_49.i, %.not2838
  br i1 %or.cond2919, label %bb63.i, label %bb29.i

bb29.i:                                           ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit
  br i1 %or.cond.i641, label %bb6.i705, label %bb7.i684

bb7.i684:                                         ; preds = %bb6.i705, %bb29.i
  %c.sroa.0.0.i685 = phi i32 [ %147, %bb6.i705 ], [ 168, %bb29.i ]
  %_17.i686 = icmp ugt i64 %d.i37, 4
  br i1 %_17.i686, label %bb12.i701, label %bb14.i691

bb6.i705:                                         ; preds = %bb29.i
  %_11.i706 = add nsw i32 %_29.i645, -3
  %_10.i707 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_11.i706, i1 false)
  %146 = shl nuw nsw i32 %_10.i707, 4
  %147 = sub nuw nsw i32 632, %146
  br label %bb7.i684

bb12.i701:                                        ; preds = %bb7.i684
  %148 = trunc nuw i64 %d.i37 to i32
  %_22.i699 = add nsw i32 %148, -1
  %_21.i702 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_22.i699, i1 true)
  %149 = shl nuw nsw i32 %_21.i702, 4
  %reass.sub2239 = sub nsw i32 %c.sroa.0.0.i685, %149
  %150 = add nsw i32 %reass.sub2239, 480
  br label %bb14.i691

bb14.i691:                                        ; preds = %bb7.i684, %bb12.i701
  %c.sroa.0.1.i688 = phi i32 [ %150, %bb12.i701 ], [ %c.sroa.0.0.i685, %bb7.i684 ]
  %151 = tail call { i32, i1 } @llvm.ssub.with.overflow.i32(i32 %_30.0.i, i32 %c.sroa.0.1.i688)
  %_31.1.i693 = extractvalue { i32, i1 } %151, 1
  br i1 %_31.1.i693, label %panic9.i696, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit708

panic9.i696:                                      ; preds = %bb14.i691
; call core::panicking::panic_const::panic_const_sub_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_de42051d6ce5797cfcaece5556197823) #13
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit708: ; preds = %bb14.i691
  %_31.0.i695 = extractvalue { i32, i1 } %151, 0
  %152 = add nsw i64 %l.sroa.0.0.i2189, -11
  %or.cond.i657 = icmp ult i64 %152, 247
  br i1 %or.cond.i657, label %bb6.i679, label %bb7.i658

bb7.i658:                                         ; preds = %bb6.i679, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit708
  %c.sroa.0.0.i659 = phi i32 [ %155, %bb6.i679 ], [ 168, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit708 ]
  %_17.i660 = icmp ugt i64 %d.sroa.0.0.i2188, 4
  br i1 %_17.i660, label %bb8.i672, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit682

bb6.i679:                                         ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit708
  %153 = trunc nuw nsw i64 %l.sroa.0.0.i2189 to i32
  %_11.i680 = add nsw i32 %153, -3
  %_10.i681 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_11.i680, i1 false)
  %154 = shl nuw nsw i32 %_10.i681, 4
  %155 = sub nuw nsw i32 632, %154
  br label %bb7.i658

bb8.i672:                                         ; preds = %bb7.i658
  %156 = trunc i64 %d.sroa.0.0.i2188 to i32
  %_22.i673 = add nsw i32 %156, -1
  %_25.1.i674 = icmp ult i32 %_22.i673, 2
  br i1 %_25.1.i674, label %panic5.i678, label %bb12.i675

panic5.i678:                                      ; preds = %bb8.i672
; call core::panicking::panic_const::panic_const_sub_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_b85e9cb8887915fa95bd915ab181c13b) #13
  unreachable

bb12.i675:                                        ; preds = %bb8.i672
  %_21.i676 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_22.i673, i1 true)
  %157 = shl nuw nsw i32 %_21.i676, 4
  %reass.sub2240 = sub nsw i32 %c.sroa.0.0.i659, %157
  %158 = add nsw i32 %reass.sub2240, 480
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit682

_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit682: ; preds = %bb12.i675, %bb7.i658
  %c.sroa.0.1.i662 = phi i32 [ %158, %bb12.i675 ], [ %c.sroa.0.0.i659, %bb7.i658 ]
  %_29.i663 = trunc nuw nsw i64 %l.sroa.0.0.i2189 to i32
  %_30.0.i666 = shl nuw nsw i32 %_29.i663, 6
  %159 = sub nsw i32 %_30.0.i666, %c.sroa.0.1.i662
  %_62.i = icmp sgt i32 %_31.0.i695, %159
  br i1 %_62.i, label %bb32.i, label %bb63.i

bb32.i:                                           ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit682
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2684)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2687)
  %exitcond.not2829 = icmp eq i64 %nt.sroa.0.5.i2190, %umax2810
  br i1 %exitcond.not2829, label %panic1.i162, label %bb59.i

panic1.i162:                                      ; preds = %bb32.i
  %nt.sroa.0.5.i2190.lcssa2871 = phi i64 [ %nt.sroa.0.5.i2190, %bb32.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %nt.sroa.0.5.i2190.lcssa2871, i64 noundef range(i64 0, 2305843009213693952) %out.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_f5cc78c6143d87a95e73f58df7e9bb32) #13, !noalias !2689
  unreachable

bb59.i:                                           ; preds = %bb32.i
  %_5.i = load i8, ptr %103, align 1, !alias.scope !2684, !noalias !2687, !noundef !136
  %160 = getelementptr inbounds nuw [4 x i8], ptr %out.0, i64 %nt.sroa.0.5.i2190
  %161 = zext i8 %_5.i to i32
  store i32 %161, ptr %160, align 4, !alias.scope !2687, !noalias !2684
  %_10.0.i164 = add i64 %nt.sroa.0.5.i2190, 1
  %_39.i = icmp ult i64 %k.sroa.0.2.i.lcssa, 64
  %indvars.iv.next2808 = add i64 %indvars.iv2807, -1
  br i1 %_39.i, label %bb18.i, label %bb63.i

bb116.i:                                          ; preds = %bb110.i, %bb63.i
  %p.sroa.0.7.i.lcssa = phi i64 [ %p.sroa.0.5.i.lcssa, %bb63.i ], [ %p.sroa.0.8.i, %bb110.i ]
  %l.sroa.0.2.i.lcssa = phi i64 [ %l.sroa.0.0.i.lcssa, %bb63.i ], [ %l.sroa.0.3.i, %bb110.i ]
  %nt.sroa.0.7.i.lcssa = phi i64 [ %nt.sroa.0.5.i.lcssa, %bb63.i ], [ %nt.sroa.0.8.i, %bb110.i ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2690)
  %_15.i = icmp samesign ult i64 %nt.sroa.0.7.i.lcssa, %out.1
  br i1 %_15.i, label %bb1.i193, label %panic.i192

bb1.i193:                                         ; preds = %bb116.i
  %162 = trunc i64 %l.sroa.0.2.i.lcssa to i32
  %163 = trunc i64 %d.sroa.0.0.i.lcssa to i32
  %_10.i = shl i32 %163, 8
  %_12.i194 = add i32 %_10.i, 16776957
  %_7.i195 = add i32 %_12.i194, %162
  %164 = getelementptr inbounds nuw [4 x i8], ptr %out.0, i64 %nt.sroa.0.7.i.lcssa
  store i32 %_7.i195, ptr %164, align 4, !alias.scope !2690
  %_19.0.i196 = add i64 %l.sroa.0.2.i.lcssa, %p.sroa.0.7.i.lcssa
  %_19.1.i197 = icmp ult i64 %_19.0.i196, %p.sroa.0.7.i.lcssa
  br i1 %_19.1.i197, label %panic2.i199, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse14u118_put_match.exit

panic.i192:                                       ; preds = %bb116.i
  %nt.sroa.0.7.i.lcssa.lcssa = phi i64 [ %nt.sroa.0.7.i.lcssa, %bb116.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef range(i64 0, 2305843009213693952) %nt.sroa.0.7.i.lcssa.lcssa, i64 noundef range(i64 0, 2305843009213693952) %out.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_771dc0d324c573869d9faceafd4f8e56) #13, !noalias !2690
  unreachable

panic2.i199:                                      ; preds = %bb1.i193
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_86c5a99bb83ebb25fc53357ef56f8fe2) #13, !noalias !2690
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse14u118_put_match.exit: ; preds = %bb1.i193
  %_17.0.i = add nuw nsw i64 %nt.sroa.0.7.i.lcssa, 1
  %_175.i = add nuw i64 %ins.sroa.0.4.i.lcssa, 16
  %spec.select138.i = tail call i64 @llvm.umin.i64(i64 %_19.0.i196, i64 %_175.i)
  %spec.store.select50.i = tail call i64 @llvm.umin.i64(i64 %spec.select138.i, i64 %_8.0.i)
  %_181.i2216 = icmp ult i64 %ins.sroa.0.4.i.lcssa, %spec.store.select50.i
  br i1 %_181.i2216, label %bb125.i, label %bb129.i

bb125.i:                                          ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse14u118_put_match.exit, %bb125.i
  %ins.sroa.0.5.i2217 = phi i64 [ %_188.0.i, %bb125.i ], [ %ins.sroa.0.4.i.lcssa, %_RNvNtCs2hd9JHJjR4I_9candidate5parse14u118_put_match.exit ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2693)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2696)
  %165 = getelementptr inbounds nuw i8, ptr %input.0, i64 %ins.sroa.0.5.i2217
  %166 = load i32, ptr %165, align 1
  %167 = call i32 @llvm.bswap.i32(i32 %166)
  %168 = zext i32 %167 to i64
  %169 = mul i64 %168, -7046029254386353131
  %170 = lshr i64 %169, 48
  %171 = getelementptr inbounds nuw [4 x i8], ptr %head.i, i64 %170
  %old.i145.i = load i32, ptr %171, align 4, !alias.scope !2693, !noalias !2698, !noundef !136
  %_16.i146.i = and i64 %ins.sroa.0.5.i2217, 32767
  %172 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_16.i146.i
  store i32 %old.i145.i, ptr %172, align 4, !alias.scope !2696, !noalias !2700
  %173 = trunc i64 %ins.sroa.0.5.i2217 to i32
  store i32 %173, ptr %171, align 4, !alias.scope !2693, !noalias !2698
  %_188.0.i = add nuw i64 %ins.sroa.0.5.i2217, 1
  %exitcond2382.not = icmp eq i64 %_188.0.i, %spec.store.select50.i
  br i1 %exitcond2382.not, label %bb129.i, label %bb125.i

bb129.i:                                          ; preds = %bb125.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse14u118_put_match.exit
  %ins.sroa.0.5.i.lcssa = phi i64 [ %ins.sroa.0.4.i.lcssa, %_RNvNtCs2hd9JHJjR4I_9candidate5parse14u118_put_match.exit ], [ %spec.store.select50.i, %bb125.i ]
  %e2.i = tail call i64 @llvm.usub.sat.i64(i64 %_19.0.i196, i64 8)
  %invariant.umin = tail call i64 @llvm.umin.i64(i64 %e2.i, i64 %_8.0.i)
  %or.cond51.i2219 = icmp ult i64 %ins.sroa.0.5.i.lcssa, %invariant.umin
  br i1 %or.cond51.i2219, label %bb132.i, label %bb138.i

bb132.i:                                          ; preds = %bb129.i, %bb132.i
  %ins.sroa.0.6.i2220 = phi i64 [ %_5.0.i288, %bb132.i ], [ %ins.sroa.0.5.i.lcssa, %bb129.i ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2701)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2704)
  %_5.0.i288 = add nuw i64 %ins.sroa.0.6.i2220, 4
  %174 = getelementptr inbounds nuw i8, ptr %input.0, i64 %ins.sroa.0.6.i2220
  %175 = load i32, ptr %174, align 1
  %176 = call i32 @llvm.bswap.i32(i32 %175)
  %177 = zext i32 %176 to i64
  %178 = mul i64 %177, -7046029254386353131
  %179 = lshr i64 %178, 48
  %180 = getelementptr inbounds nuw [4 x i8], ptr %head.i, i64 %179
  %old.i152.i = load i32, ptr %180, align 4, !alias.scope !2701, !noalias !2706, !noundef !136
  %_16.i153.i = and i64 %ins.sroa.0.6.i2220, 32767
  %181 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_16.i153.i
  store i32 %old.i152.i, ptr %181, align 4, !alias.scope !2704, !noalias !2708
  %182 = trunc i64 %ins.sroa.0.6.i2220 to i32
  store i32 %182, ptr %180, align 4, !alias.scope !2701, !noalias !2706
  %or.cond51.i = icmp ult i64 %_5.0.i288, %invariant.umin
  br i1 %or.cond51.i, label %bb132.i, label %bb138.i

bb138.i:                                          ; preds = %bb132.i, %bb129.i
  %ins.sroa.0.6.i.lcssa = phi i64 [ %ins.sroa.0.5.i.lcssa, %bb129.i ], [ %_5.0.i288, %bb132.i ]
  %_202.i = add i64 %ins.sroa.0.6.i.lcssa, 4
  %_201.i = icmp ult i64 %_202.i, %_19.0.i196
  br i1 %_201.i, label %bb139.i, label %bb142.i

bb139.i:                                          ; preds = %bb138.i
  %_204.1.i = icmp ult i64 %_19.0.i196, 4
  br i1 %_204.1.i, label %panic18.i, label %bb140.i

bb142.i:                                          ; preds = %bb140.i, %bb138.i
  %ins.sroa.0.7.i = phi i64 [ %_204.0.i, %bb140.i ], [ %ins.sroa.0.6.i.lcssa, %bb138.i ]
  %invariant.umin2222 = tail call i64 @llvm.umin.i64(i64 %_19.0.i196, i64 %_8.0.i)
  %or.cond52.i2223 = icmp ult i64 %ins.sroa.0.7.i, %invariant.umin2222
  br i1 %or.cond52.i2223, label %bb145.i, label %bb150.i

bb140.i:                                          ; preds = %bb139.i
  %_204.0.i = add i64 %_19.0.i196, -4
  br label %bb142.i

panic18.i:                                        ; preds = %bb139.i
; call core::panicking::panic_const::panic_const_sub_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_314029bb05064e5fe6e525f4ab2e737b) #13
  unreachable

bb150.i:                                          ; preds = %bb145.i, %bb142.i
  %ins.sroa.0.8.i.lcssa = phi i64 [ %ins.sroa.0.7.i, %bb142.i ], [ %_213.0.i, %bb145.i ]
  %spec.select140.i = tail call i64 @llvm.umax.i64(i64 %ins.sroa.0.8.i.lcssa, i64 %_19.0.i196)
  br label %bb174.i

bb145.i:                                          ; preds = %bb142.i, %bb145.i
  %ins.sroa.0.8.i2224 = phi i64 [ %_213.0.i, %bb145.i ], [ %ins.sroa.0.7.i, %bb142.i ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2709)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2712)
  %183 = getelementptr inbounds nuw i8, ptr %input.0, i64 %ins.sroa.0.8.i2224
  %184 = load i32, ptr %183, align 1
  %185 = call i32 @llvm.bswap.i32(i32 %184)
  %186 = zext i32 %185 to i64
  %187 = mul i64 %186, -7046029254386353131
  %188 = lshr i64 %187, 48
  %189 = getelementptr inbounds nuw [4 x i8], ptr %head.i, i64 %188
  %old.i159.i = load i32, ptr %189, align 4, !alias.scope !2709, !noalias !2714, !noundef !136
  %_16.i160.i = and i64 %ins.sroa.0.8.i2224, 32767
  %190 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_16.i160.i
  store i32 %old.i159.i, ptr %190, align 4, !alias.scope !2712, !noalias !2716
  %191 = trunc i64 %ins.sroa.0.8.i2224 to i32
  store i32 %191, ptr %189, align 4, !alias.scope !2709, !noalias !2714
  %_213.0.i = add nuw nsw i64 %ins.sroa.0.8.i2224, 1
  %or.cond52.i = icmp ult i64 %_213.0.i, %invariant.umin2222
  br i1 %or.cond52.i, label %bb145.i, label %bb150.i

bb71.i:                                           ; preds = %bb63.i, %bb110.i
  %192 = phi i64 [ %244, %bb110.i ], [ %100, %bb63.i ]
  %nt.sroa.0.7.i2212 = phi i64 [ %nt.sroa.0.8.i, %bb110.i ], [ %nt.sroa.0.5.i.lcssa, %bb63.i ]
  %l.sroa.0.2.i2211 = phi i64 [ %l.sroa.0.3.i, %bb110.i ], [ %l.sroa.0.0.i.lcssa, %bb63.i ]
  %back.sroa.0.0.i2210 = phi i64 [ %back.sroa.0.1.i, %bb110.i ], [ 0, %bb63.i ]
  %p.sroa.0.7.i2209 = phi i64 [ %p.sroa.0.8.i, %bb110.i ], [ %p.sroa.0.5.i.lcssa, %bb63.i ]
  %193 = getelementptr inbounds nuw [4 x i8], ptr %out.0, i64 %192
  %t.i = load i32, ptr %193, align 4, !alias.scope !2601, !noalias !2598, !noundef !136
  %_120.i = icmp ult i32 %t.i, 256
  br i1 %_120.i, label %bb72.i, label %bb84.i

bb84.i:                                           ; preds = %bb71.i
  %_139.i = icmp ugt i32 %t.i, 16777215
  br i1 %_139.i, label %bb87.i, label %bb110.i

bb72.i:                                           ; preds = %bb71.i
  %_125.0.i = add i64 %p.sroa.0.7.i2209, -1
  %_126.i = icmp ult i64 %_125.0.i, %input.1
  br i1 %_126.i, label %bb74.i, label %panic25.i

bb74.i:                                           ; preds = %bb72.i
  %_133.0.i = sub i64 %_125.0.i, %d.sroa.0.0.i.lcssa
  %_134.i = icmp ult i64 %_133.0.i, %input.1
  br i1 %_134.i, label %bb77.i, label %panic28.i

panic25.i:                                        ; preds = %bb72.i
  %_125.0.i.lcssa = phi i64 [ %_125.0.i, %bb72.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_125.0.i.lcssa, i64 noundef range(i64 0, -9223372036854775808) %input.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_a9b07c74cfde78097f4604099b753106) #13
  unreachable

bb77.i:                                           ; preds = %bb74.i
  %194 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_125.0.i
  %_122.i = load i8, ptr %194, align 1, !alias.scope !2598, !noalias !2601, !noundef !136
  %195 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_133.0.i
  %_127.i = load i8, ptr %195, align 1, !alias.scope !2598, !noalias !2601, !noundef !136
  %_121.i = icmp eq i8 %_122.i, %_127.i
  br i1 %_121.i, label %bb80.i, label %bb110.i

panic28.i:                                        ; preds = %bb74.i
  %_133.0.i.lcssa = phi i64 [ %_133.0.i, %bb74.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_133.0.i.lcssa, i64 noundef range(i64 0, -9223372036854775808) %input.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_cd6670e2db87759322e29f99bddfa067) #13
  unreachable

bb87.i:                                           ; preds = %bb84.i
  %_142.i = and i32 %t.i, 255
  %_145.0.i = add nuw nsw i32 %_142.i, 3
  %w.i = zext nneg i32 %_145.0.i to i64
  %_149.0.i = add nuw nsw i64 %l.sroa.0.2.i2211, %w.i
  %_146.i = icmp samesign ult i64 %_149.0.i, 259
  %_150.i = icmp uge i64 %p.sroa.0.7.i2209, %w.i
  %or.cond53.i = select i1 %_146.i, i1 %_150.i, i1 false
  br i1 %or.cond53.i, label %bb90.i, label %bb110.i

bb90.i:                                           ; preds = %bb87.i
  %_156.0.i = sub nuw i64 %p.sroa.0.7.i2209, %w.i
  %_152.not.i = icmp ugt i64 %d.sroa.0.0.i.lcssa, %_156.0.i
  br i1 %_152.not.i, label %bb110.i, label %bb95.i

bb95.i:                                           ; preds = %bb90.i
  %_163.0.i = sub nuw i64 %_156.0.i, %d.sroa.0.0.i.lcssa
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2717)
  %196 = and i64 %w.i, 504
  br label %bb2.i747

bb2.i747:                                         ; preds = %bb95.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i
  %k.sroa.0.0.i7102201 = phi i64 [ 0, %bb95.i ], [ %_11.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i ]
  %_11.0.i = add nuw nsw i64 %k.sroa.0.0.i7102201, 8
  %_8.not.i = icmp samesign ugt i64 %_11.0.i, %w.i
  br i1 %_8.not.i, label %bb15.i711, label %bb4.i749

bb4.i749:                                         ; preds = %bb2.i747
  %_16.0.i = add nuw i64 %k.sroa.0.0.i7102201, %_163.0.i
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2720)
  %_5.1.i172.i = icmp ugt i64 %_16.0.i, -9
  br i1 %_5.1.i172.i, label %panic.i238.i, label %bb1.i173.i

bb15.i711:                                        ; preds = %bb2.i747
  %_23.i712.not = icmp eq i64 %196, %w.i
  br i1 %_23.i712.not, label %bb101.i, label %bb18.i714

bb1.i173.i:                                       ; preds = %bb4.i749
  %_5.0.i174.i = add nuw i64 %_16.0.i, 8
  %_3.not.i175.i = icmp ugt i64 %_5.0.i174.i, %input.1
  br i1 %_3.not.i175.i, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit239.i, label %bb2.i176.i

panic.i238.i:                                     ; preds = %bb4.i749
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_c9d76a7bf6f333d6169298e9d093a546) #13, !noalias !2723
  unreachable

bb2.i176.i:                                       ; preds = %bb1.i173.i
  %197 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_16.0.i
  %_15.i180.i = load i8, ptr %197, align 1, !alias.scope !2723, !noundef !136
  %_14.i181.i = zext i8 %_15.i180.i to i64
  %_13.i182.i = shl nuw i64 %_14.i181.i, 56
  %198 = getelementptr inbounds nuw i8, ptr %197, i64 1
  %_19.i187.i = load i8, ptr %198, align 1, !alias.scope !2723, !noundef !136
  %_18.i188.i = zext i8 %_19.i187.i to i64
  %_17.i189.i = shl nuw nsw i64 %_18.i188.i, 48
  %_12.i190.i = or disjoint i64 %_17.i189.i, %_13.i182.i
  %199 = getelementptr inbounds nuw i8, ptr %197, i64 2
  %_25.i195.i = load i8, ptr %199, align 1, !alias.scope !2723, !noundef !136
  %_24.i196.i = zext i8 %_25.i195.i to i64
  %_23.i197.i = shl nuw nsw i64 %_24.i196.i, 40
  %_11.i198.i = or disjoint i64 %_12.i190.i, %_23.i197.i
  %200 = getelementptr inbounds nuw i8, ptr %197, i64 3
  %_31.i203.i = load i8, ptr %200, align 1, !alias.scope !2723, !noundef !136
  %_30.i204.i = zext i8 %_31.i203.i to i64
  %_29.i205.i = shl nuw nsw i64 %_30.i204.i, 32
  %_10.i206.i = or disjoint i64 %_11.i198.i, %_29.i205.i
  %201 = getelementptr inbounds nuw i8, ptr %197, i64 4
  %_37.i211.i = load i8, ptr %201, align 1, !alias.scope !2723, !noundef !136
  %_36.i212.i = zext i8 %_37.i211.i to i64
  %_35.i213.i = shl nuw nsw i64 %_36.i212.i, 24
  %_9.i214.i = or disjoint i64 %_10.i206.i, %_35.i213.i
  %202 = getelementptr inbounds nuw i8, ptr %197, i64 5
  %_43.i219.i = load i8, ptr %202, align 1, !alias.scope !2723, !noundef !136
  %_42.i220.i = zext i8 %_43.i219.i to i64
  %_41.i221.i = shl nuw nsw i64 %_42.i220.i, 16
  %_8.i222.i = or disjoint i64 %_9.i214.i, %_41.i221.i
  %203 = getelementptr inbounds nuw i8, ptr %197, i64 6
  %_49.i227.i = load i8, ptr %203, align 1, !alias.scope !2723, !noundef !136
  %_48.i228.i = zext i8 %_49.i227.i to i64
  %_47.i229.i = shl nuw nsw i64 %_48.i228.i, 8
  %_7.i230.i = or i64 %_8.i222.i, %_47.i229.i
  %204 = getelementptr inbounds nuw i8, ptr %197, i64 7
  %_54.i235.i = load i8, ptr %204, align 1, !alias.scope !2723, !noundef !136
  %_53.i236.i = zext i8 %_54.i235.i to i64
  %205 = or i64 %_7.i230.i, %_53.i236.i
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit239.i

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit239.i: ; preds = %bb2.i176.i, %bb1.i173.i
  %_0.sroa.0.0.i237.i = phi i64 [ %205, %bb2.i176.i ], [ 0, %bb1.i173.i ]
  %_20.0.i = add nuw i64 %k.sroa.0.0.i7102201, %_156.0.i
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2724)
  %_5.1.i104.i = icmp ugt i64 %_20.0.i, -9
  br i1 %_5.1.i104.i, label %panic.i170.i, label %bb1.i105.i

bb1.i105.i:                                       ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit239.i
  %_5.0.i106.i = add nuw i64 %_20.0.i, 8
  %_3.not.i107.i = icmp ugt i64 %_5.0.i106.i, %input.1
  br i1 %_3.not.i107.i, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i, label %bb2.i108.i

panic.i170.i:                                     ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit239.i
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_c9d76a7bf6f333d6169298e9d093a546) #13, !noalias !2727
  unreachable

bb2.i108.i:                                       ; preds = %bb1.i105.i
  %206 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_20.0.i
  %_15.i112.i = load i8, ptr %206, align 1, !alias.scope !2727, !noundef !136
  %_14.i113.i = zext i8 %_15.i112.i to i64
  %_13.i114.i = shl nuw i64 %_14.i113.i, 56
  %207 = getelementptr inbounds nuw i8, ptr %206, i64 1
  %_19.i119.i = load i8, ptr %207, align 1, !alias.scope !2727, !noundef !136
  %_18.i120.i = zext i8 %_19.i119.i to i64
  %_17.i121.i = shl nuw nsw i64 %_18.i120.i, 48
  %_12.i122.i = or disjoint i64 %_17.i121.i, %_13.i114.i
  %208 = getelementptr inbounds nuw i8, ptr %206, i64 2
  %_25.i127.i = load i8, ptr %208, align 1, !alias.scope !2727, !noundef !136
  %_24.i128.i = zext i8 %_25.i127.i to i64
  %_23.i129.i = shl nuw nsw i64 %_24.i128.i, 40
  %_11.i130.i = or disjoint i64 %_12.i122.i, %_23.i129.i
  %209 = getelementptr inbounds nuw i8, ptr %206, i64 3
  %_31.i135.i = load i8, ptr %209, align 1, !alias.scope !2727, !noundef !136
  %_30.i136.i = zext i8 %_31.i135.i to i64
  %_29.i137.i = shl nuw nsw i64 %_30.i136.i, 32
  %_10.i138.i = or disjoint i64 %_11.i130.i, %_29.i137.i
  %210 = getelementptr inbounds nuw i8, ptr %206, i64 4
  %_37.i143.i = load i8, ptr %210, align 1, !alias.scope !2727, !noundef !136
  %_36.i144.i = zext i8 %_37.i143.i to i64
  %_35.i145.i = shl nuw nsw i64 %_36.i144.i, 24
  %_9.i146.i = or disjoint i64 %_10.i138.i, %_35.i145.i
  %211 = getelementptr inbounds nuw i8, ptr %206, i64 5
  %_43.i151.i = load i8, ptr %211, align 1, !alias.scope !2727, !noundef !136
  %_42.i152.i = zext i8 %_43.i151.i to i64
  %_41.i153.i = shl nuw nsw i64 %_42.i152.i, 16
  %_8.i154.i = or disjoint i64 %_9.i146.i, %_41.i153.i
  %212 = getelementptr inbounds nuw i8, ptr %206, i64 6
  %_49.i159.i = load i8, ptr %212, align 1, !alias.scope !2727, !noundef !136
  %_48.i160.i = zext i8 %_49.i159.i to i64
  %_47.i161.i = shl nuw nsw i64 %_48.i160.i, 8
  %_7.i162.i = or i64 %_8.i154.i, %_47.i161.i
  %213 = getelementptr inbounds nuw i8, ptr %206, i64 7
  %_54.i167.i = load i8, ptr %213, align 1, !alias.scope !2727, !noundef !136
  %_53.i168.i = zext i8 %_54.i167.i to i64
  %214 = or i64 %_7.i162.i, %_53.i168.i
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i: ; preds = %bb2.i108.i, %bb1.i105.i
  %_0.sroa.0.0.i169.i = phi i64 [ %214, %bb2.i108.i ], [ 0, %bb1.i105.i ]
  %_12.i.not = icmp eq i64 %_0.sroa.0.0.i237.i, %_0.sroa.0.0.i169.i
  br i1 %_12.i.not, label %bb2.i747, label %bb110.i

bb18.i714:                                        ; preds = %bb15.i711
  %_29.0.i715 = add i64 %196, %_163.0.i
  %_29.1.i = icmp ult i64 %_29.0.i715, %_163.0.i
  br i1 %_29.1.i, label %panic4.i746, label %bb19.i716

bb19.i716:                                        ; preds = %bb18.i714
  %_30.1.i717 = icmp ugt i64 %_29.0.i715, -9
  br i1 %_30.1.i717, label %panic5.i745, label %bb20.i718

panic4.i746:                                      ; preds = %bb18.i714
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_d25cf0b69b2704dd91f9333d61493191) #13, !noalias !2717
  unreachable

bb20.i718:                                        ; preds = %bb19.i716
  %_30.0.i719 = add nuw i64 %_29.0.i715, 8
  %_25.not.i = icmp ugt i64 %_30.0.i719, %input.1
  br i1 %_25.not.i, label %bb40.i.preheader, label %bb21.i720

bb40.i.preheader:                                 ; preds = %bb23.i722, %bb20.i718
  br label %bb40.i

panic5.i745:                                      ; preds = %bb19.i716
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_d25cf0b69b2704dd91f9333d61493191) #13, !noalias !2717
  unreachable

bb21.i720:                                        ; preds = %bb20.i718
  %_35.0.i = add i64 %196, %_156.0.i
  %_35.1.i = icmp ult i64 %_35.0.i, %_156.0.i
  br i1 %_35.1.i, label %panic6.i744, label %bb22.i721

bb22.i721:                                        ; preds = %bb21.i720
  %_36.1.i = icmp ugt i64 %_35.0.i, -9
  br i1 %_36.1.i, label %panic7.i743, label %bb23.i722

panic6.i744:                                      ; preds = %bb21.i720
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_a53f101562b3ececed8f3c5b31e2988c) #13, !noalias !2717
  unreachable

bb23.i722:                                        ; preds = %bb22.i721
  %_36.0.i = add nuw i64 %_35.0.i, 8
  %_31.not.i = icmp ugt i64 %_36.0.i, %input.1
  br i1 %_31.not.i, label %bb40.i.preheader, label %bb30.i

panic7.i743:                                      ; preds = %bb22.i721
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_a53f101562b3ececed8f3c5b31e2988c) #13, !noalias !2717
  unreachable

bb40.i:                                           ; preds = %bb40.i.preheader, %bb44.i
  %k.sroa.0.2.i7362203 = phi i64 [ %k.sroa.0.3.i741, %bb44.i ], [ %196, %bb40.i.preheader ]
  %_62.0.i = add i64 %k.sroa.0.2.i7362203, %_163.0.i
  %_62.1.i = icmp ult i64 %_62.0.i, %_163.0.i
  br i1 %_62.1.i, label %panic8.i742, label %bb41.i

bb41.i:                                           ; preds = %bb40.i
  %_63.i = icmp ult i64 %_62.0.i, %input.1
  br i1 %_63.i, label %bb42.i, label %panic9.i737

panic8.i742:                                      ; preds = %bb40.i
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_fd52fb03143b3c2291092829f0723dc0) #13, !noalias !2717
  unreachable

bb42.i:                                           ; preds = %bb41.i
  %215 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_62.0.i
  %_59.i738 = load i8, ptr %215, align 1, !alias.scope !2717, !noundef !136
  %_67.0.i = add i64 %k.sroa.0.2.i7362203, %_156.0.i
  %_67.1.i = icmp ult i64 %_67.0.i, %_156.0.i
  br i1 %_67.1.i, label %panic10.i, label %bb43.i

panic9.i737:                                      ; preds = %bb41.i
  %_62.0.i.lcssa2872 = phi i64 [ %_62.0.i, %bb41.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_62.0.i.lcssa2872, i64 noundef range(i64 0, -9223372036854775808) %input.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_1256f16a95fac1466fa65d9b9a438ec4) #13, !noalias !2717
  unreachable

bb43.i:                                           ; preds = %bb42.i
  %_68.i = icmp ult i64 %_67.0.i, %input.1
  br i1 %_68.i, label %bb44.i, label %panic11.i739

panic10.i:                                        ; preds = %bb42.i
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_bfa6d05f2bf936d7b8c99dcdd4008e5c) #13, !noalias !2717
  unreachable

bb44.i:                                           ; preds = %bb43.i
  %216 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_67.0.i
  %_64.i740 = load i8, ptr %216, align 1, !alias.scope !2717, !noundef !136
  %_58.i = icmp eq i8 %_59.i738, %_64.i740
  %_69.0.i = zext i1 %_58.i to i64
  %k.sroa.0.3.i741 = add nuw nsw i64 %k.sroa.0.2.i7362203, %_69.0.i
  %_56.i = icmp samesign ult i64 %k.sroa.0.3.i741, %w.i
  %or.cond19.i = select i1 %_58.i, i1 %_56.i, i1 false
  br i1 %or.cond19.i, label %bb40.i, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit

panic11.i739:                                     ; preds = %bb43.i
  %_67.0.i.lcssa2876 = phi i64 [ %_67.0.i, %bb43.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_67.0.i.lcssa2876, i64 noundef range(i64 0, -9223372036854775808) %input.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_63961bfa935f7f5c38e726eb9c394484) #13, !noalias !2717
  unreachable

bb30.i:                                           ; preds = %bb23.i722
  %_51.0.i727 = shl nuw nsw i32 %_145.0.i, 3
  %217 = and i32 %_51.0.i727, 56
  %_54.i730.not = icmp eq i32 %217, 0
  br i1 %_54.i730.not, label %panic18.i731, label %bb32.i732

bb32.i732:                                        ; preds = %bb30.i
  %_53.0.i = sub nuw nsw i32 64, %217
  %218 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_35.0.i
  %219 = getelementptr inbounds nuw i8, ptr %218, i64 1
  %_19.i.i = load i8, ptr %219, align 1, !alias.scope !2728, !noundef !136
  %_18.i.i = zext i8 %_19.i.i to i64
  %_17.i.i = shl nuw nsw i64 %_18.i.i, 48
  %_15.i.i = load i8, ptr %218, align 1, !alias.scope !2728, !noundef !136
  %_14.i.i = zext i8 %_15.i.i to i64
  %_13.i.i = shl nuw i64 %_14.i.i, 56
  %_12.i.i724 = or disjoint i64 %_17.i.i, %_13.i.i
  %220 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_35.0.i
  %221 = getelementptr inbounds nuw i8, ptr %220, i64 2
  %_25.i.i = load i8, ptr %221, align 1, !alias.scope !2728, !noundef !136
  %_24.i.i = zext i8 %_25.i.i to i64
  %_23.i.i = shl nuw nsw i64 %_24.i.i, 40
  %_11.i.i725 = or disjoint i64 %_12.i.i724, %_23.i.i
  %222 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_35.0.i
  %223 = getelementptr inbounds nuw i8, ptr %222, i64 3
  %_31.i.i = load i8, ptr %223, align 1, !alias.scope !2728, !noundef !136
  %_30.i.i = zext i8 %_31.i.i to i64
  %_29.i.i = shl nuw nsw i64 %_30.i.i, 32
  %_10.i.i = or disjoint i64 %_11.i.i725, %_29.i.i
  %224 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_35.0.i
  %225 = getelementptr inbounds nuw i8, ptr %224, i64 4
  %_37.i.i = load i8, ptr %225, align 1, !alias.scope !2728, !noundef !136
  %_36.i.i = zext i8 %_37.i.i to i64
  %_35.i.i = shl nuw nsw i64 %_36.i.i, 24
  %_9.i.i = or disjoint i64 %_10.i.i, %_35.i.i
  %226 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_35.0.i
  %227 = getelementptr inbounds nuw i8, ptr %226, i64 5
  %_43.i.i = load i8, ptr %227, align 1, !alias.scope !2728, !noundef !136
  %_42.i.i = zext i8 %_43.i.i to i64
  %_41.i.i = shl nuw nsw i64 %_42.i.i, 16
  %_8.i.i = or disjoint i64 %_9.i.i, %_41.i.i
  %228 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_35.0.i
  %229 = getelementptr inbounds nuw i8, ptr %228, i64 6
  %_49.i.i = load i8, ptr %229, align 1, !alias.scope !2728, !noundef !136
  %_48.i.i = zext i8 %_49.i.i to i64
  %_47.i.i = shl nuw nsw i64 %_48.i.i, 8
  %_7.i.i = or i64 %_8.i.i, %_47.i.i
  %230 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_35.0.i
  %231 = getelementptr inbounds nuw i8, ptr %230, i64 7
  %_54.i.i = load i8, ptr %231, align 1, !alias.scope !2728, !noundef !136
  %_53.i.i = zext i8 %_54.i.i to i64
  %232 = or i64 %_7.i.i, %_53.i.i
  %233 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_29.0.i715
  %234 = getelementptr inbounds nuw i8, ptr %233, i64 1
  %_19.i51.i = load i8, ptr %234, align 1, !alias.scope !2731, !noundef !136
  %_18.i52.i = zext i8 %_19.i51.i to i64
  %_17.i53.i = shl nuw nsw i64 %_18.i52.i, 48
  %_15.i44.i = load i8, ptr %233, align 1, !alias.scope !2731, !noundef !136
  %_14.i45.i = zext i8 %_15.i44.i to i64
  %_13.i46.i = shl nuw i64 %_14.i45.i, 56
  %_12.i54.i = or disjoint i64 %_17.i53.i, %_13.i46.i
  %235 = getelementptr inbounds nuw i8, ptr %233, i64 2
  %_25.i59.i = load i8, ptr %235, align 1, !alias.scope !2731, !noundef !136
  %_24.i60.i = zext i8 %_25.i59.i to i64
  %_23.i61.i = shl nuw nsw i64 %_24.i60.i, 40
  %_11.i62.i = or disjoint i64 %_12.i54.i, %_23.i61.i
  %236 = getelementptr inbounds nuw i8, ptr %233, i64 3
  %_31.i67.i = load i8, ptr %236, align 1, !alias.scope !2731, !noundef !136
  %_30.i68.i = zext i8 %_31.i67.i to i64
  %_29.i69.i = shl nuw nsw i64 %_30.i68.i, 32
  %_10.i70.i = or disjoint i64 %_11.i62.i, %_29.i69.i
  %237 = getelementptr inbounds nuw i8, ptr %233, i64 4
  %_37.i75.i = load i8, ptr %237, align 1, !alias.scope !2731, !noundef !136
  %_36.i76.i = zext i8 %_37.i75.i to i64
  %_35.i77.i = shl nuw nsw i64 %_36.i76.i, 24
  %_9.i78.i = or disjoint i64 %_10.i70.i, %_35.i77.i
  %238 = getelementptr inbounds nuw i8, ptr %233, i64 5
  %_43.i83.i = load i8, ptr %238, align 1, !alias.scope !2731, !noundef !136
  %_42.i84.i = zext i8 %_43.i83.i to i64
  %_41.i85.i = shl nuw nsw i64 %_42.i84.i, 16
  %_8.i86.i = or disjoint i64 %_9.i78.i, %_41.i85.i
  %239 = getelementptr inbounds nuw i8, ptr %233, i64 6
  %_49.i91.i = load i8, ptr %239, align 1, !alias.scope !2731, !noundef !136
  %_48.i92.i = zext i8 %_49.i91.i to i64
  %_47.i93.i = shl nuw nsw i64 %_48.i92.i, 8
  %_7.i94.i = or i64 %_8.i86.i, %_47.i93.i
  %240 = getelementptr inbounds nuw i8, ptr %233, i64 7
  %_54.i99.i = load i8, ptr %240, align 1, !alias.scope !2731, !noundef !136
  %_53.i100.i = zext i8 %_54.i99.i to i64
  %241 = or i64 %_7.i94.i, %_53.i100.i
  %x.i726 = xor i64 %232, %241
  %242 = zext nneg i32 %_53.0.i to i64
  %_46.i733 = lshr i64 %x.i726, %242
  %243 = icmp eq i64 %_46.i733, 0
  br i1 %243, label %bb101.i, label %bb110.i

panic18.i731:                                     ; preds = %bb30.i
; call core::panicking::panic_const::panic_const_shr_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_shr_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_8bda8caf9703c723fc6d18cb0fd57c1f) #13, !noalias !2717
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit: ; preds = %bb44.i
  br i1 %_58.i, label %bb101.i, label %bb110.i

bb101.i:                                          ; preds = %bb32.i732, %bb15.i711, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit
  %_170.0.i = add nuw nsw i64 %back.sroa.0.0.i2210, 1
  br label %bb110.i

bb110.i:                                          ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i, %bb32.i732, %bb77.i, %bb80.i, %bb101.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit, %bb90.i, %bb87.i, %bb84.i
  %p.sroa.0.8.i = phi i64 [ %_125.0.i, %bb80.i ], [ %_156.0.i, %bb101.i ], [ %p.sroa.0.7.i2209, %bb84.i ], [ %p.sroa.0.7.i2209, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit ], [ %p.sroa.0.7.i2209, %bb90.i ], [ %p.sroa.0.7.i2209, %bb87.i ], [ %p.sroa.0.7.i2209, %bb77.i ], [ %p.sroa.0.7.i2209, %bb32.i732 ], [ %p.sroa.0.7.i2209, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i ]
  %back.sroa.0.1.i = phi i64 [ %_138.0.i, %bb80.i ], [ %_170.0.i, %bb101.i ], [ 16, %bb84.i ], [ 16, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit ], [ 16, %bb90.i ], [ 16, %bb87.i ], [ 16, %bb77.i ], [ 16, %bb32.i732 ], [ 16, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i ]
  %l.sroa.0.3.i = phi i64 [ %_137.0.i, %bb80.i ], [ %_149.0.i, %bb101.i ], [ %l.sroa.0.2.i2211, %bb84.i ], [ %l.sroa.0.2.i2211, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit ], [ %l.sroa.0.2.i2211, %bb90.i ], [ %l.sroa.0.2.i2211, %bb87.i ], [ %l.sroa.0.2.i2211, %bb77.i ], [ %l.sroa.0.2.i2211, %bb32.i732 ], [ %l.sroa.0.2.i2211, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i ]
  %nt.sroa.0.8.i = phi i64 [ %192, %bb80.i ], [ %192, %bb101.i ], [ %nt.sroa.0.7.i2212, %bb84.i ], [ %nt.sroa.0.7.i2212, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit ], [ %nt.sroa.0.7.i2212, %bb90.i ], [ %nt.sroa.0.7.i2212, %bb87.i ], [ %nt.sroa.0.7.i2212, %bb77.i ], [ %nt.sroa.0.7.i2212, %bb32.i732 ], [ %nt.sroa.0.7.i2212, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i ]
  %_103.i = icmp ult i64 %back.sroa.0.1.i, 16
  %244 = add i64 %nt.sroa.0.8.i, -1
  %245 = icmp ult i64 %244, %out.1
  %or.cond48.i = select i1 %_103.i, i1 %245, i1 false
  %_110.i = icmp ult i64 %l.sroa.0.3.i, 258
  %or.cond49.i = select i1 %or.cond48.i, i1 %_110.i, i1 false
  %_112.i = icmp ult i64 %d.sroa.0.0.i.lcssa, %p.sroa.0.8.i
  %or.cond139.i = select i1 %or.cond49.i, i1 %_112.i, i1 false
  br i1 %or.cond139.i, label %bb71.i, label %bb116.i

bb80.i:                                           ; preds = %bb77.i
  %_137.0.i = add nuw nsw i64 %l.sroa.0.2.i2211, 1
  %_138.0.i = add nuw nsw i64 %back.sroa.0.0.i2210, 1
  br label %bb110.i

_RINvNtCs2hd9JHJjR4I_9candidate5parse8u118_runKj10000_Kj8000_Kmffffffff_Kj4_Kjc_Kj40_Kj6_Kjf4240_Kj80_Kj1_Kj10_KB18_Kl40_Kj0_EB4_.exit: ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit191, %bb178.i
  %nt.sroa.0.2.i.lcssa = phi i64 [ %nt.sroa.0.0.i, %bb178.i ], [ %_10.0.i190, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit191 ]
  ret i64 %nt.sroa.0.2.i.lcssa
}