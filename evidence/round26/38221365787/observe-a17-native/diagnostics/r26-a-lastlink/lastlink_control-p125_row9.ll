define internal fastcc noundef i64 @_RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row9(ptr noalias nofree noundef nonnull readonly captures(address, read_provenance) %input.0, i64 noundef range(i64 0, -9223372036854775808) %input.1, ptr noalias nofree noundef nonnull align 4 captures(none) %out.0, i64 noundef range(i64 0, 2305843009213693952) %out.1) unnamed_addr #0 !guid !2598 {
start:
  %prev.i = alloca [131072 x i8], align 4
  %head.i = alloca [262144 x i8], align 4
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2599)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2602)
  %_4.i = icmp samesign ugt i64 %input.1, 16
  br i1 %_4.i, label %bb5.i.preheader, label %bb178.i

bb178.i:                                          ; preds = %bb177.i, %start
  %p.sroa.0.0.i = phi i64 [ %p.sroa.0.4.i.lcssa, %bb177.i ], [ 0, %start ]
  %nt.sroa.0.0.i = phi i64 [ %nt.sroa.0.4.i.lcssa, %bb177.i ], [ 0, %start ]
  %_237.i2247 = icmp ult i64 %p.sroa.0.0.i, %input.1
  br i1 %_237.i2247, label %bb1.i190.preheader, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse8u118_runKj10000_Kj8000_Kmffffffff_Kj4_Kjc_Kj40_Kj6_Kjf4240_Kj80_Kj1_Kj10_KB18_Kl40_Kj0_EB4_.exit

bb1.i190.preheader:                               ; preds = %bb178.i
  %umax = tail call i64 @llvm.umax.i64(i64 %nt.sroa.0.0.i, i64 %out.1)
  %0 = xor i64 %p.sroa.0.0.i, -1
  %1 = add nsw i64 %input.1, %0
  %2 = sub i64 %umax, %nt.sroa.0.0.i
  %3 = call i64 @llvm.umin.i64(i64 %1, i64 %2)
  %4 = add i64 %3, 1
  %min.iters.check2822 = icmp ult i64 %4, 9
  br i1 %min.iters.check2822, label %bb1.i190.preheader2843, label %vector.ph2823

bb1.i190.preheader2843:                           ; preds = %vector.body2826, %bb1.i190.preheader
  %nt.sroa.0.2.i2249.ph = phi i64 [ %nt.sroa.0.0.i, %bb1.i190.preheader ], [ %7, %vector.body2826 ]
  %p.sroa.0.2.i2248.ph = phi i64 [ %p.sroa.0.0.i, %bb1.i190.preheader ], [ %8, %vector.body2826 ]
  br label %bb1.i190

vector.ph2823:                                    ; preds = %bb1.i190.preheader
  %n.mod.vf2824 = and i64 %4, 7
  %5 = icmp eq i64 %n.mod.vf2824, 0
  %6 = select i1 %5, i64 8, i64 %n.mod.vf2824
  %n.vec2825 = sub nuw i64 %4, %6
  %7 = add i64 %nt.sroa.0.0.i, %n.vec2825
  %8 = add i64 %p.sroa.0.0.i, %n.vec2825
  %9 = getelementptr i8, ptr %input.0, i64 %p.sroa.0.0.i
  %10 = getelementptr [4 x i8], ptr %out.0, i64 %nt.sroa.0.0.i
  br label %vector.body2826

vector.body2826:                                  ; preds = %vector.body2826, %vector.ph2823
  %index2827 = phi i64 [ 0, %vector.ph2823 ], [ %index.next2830, %vector.body2826 ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2604)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2607)
  %11 = getelementptr i8, ptr %9, i64 %index2827
  %12 = getelementptr inbounds nuw i8, ptr %11, i64 4
  %wide.load2828 = load <4 x i8>, ptr %11, align 1, !alias.scope !2604, !noalias !2607
  %wide.load2829 = load <4 x i8>, ptr %12, align 1, !alias.scope !2604, !noalias !2607
  %13 = getelementptr [4 x i8], ptr %10, i64 %index2827
  %14 = zext <4 x i8> %wide.load2828 to <4 x i32>
  %15 = zext <4 x i8> %wide.load2829 to <4 x i32>
  %16 = getelementptr inbounds nuw i8, ptr %13, i64 16
  store <4 x i32> %14, ptr %13, align 4, !alias.scope !2607, !noalias !2604
  store <4 x i32> %15, ptr %16, align 4, !alias.scope !2607, !noalias !2604
  %index.next2830 = add nuw i64 %index2827, 8
  %17 = icmp eq i64 %index.next2830, %n.vec2825
  br i1 %17, label %bb1.i190.preheader2843, label %vector.body2826, !llvm.loop !2609

bb5.i.preheader:                                  ; preds = %start
  call void @llvm.lifetime.start.p0(ptr nonnull %head.i), !noalias !2610
  call void @llvm.memset.p0.i64(ptr noundef nonnull align 4 dereferenceable(262144) %head.i, i8 0, i64 262144, i1 false), !noalias !2610
  call void @llvm.lifetime.start.p0(ptr nonnull %prev.i), !noalias !2610
  call void @llvm.memset.p0.i64(ptr noundef nonnull align 4 dereferenceable(131072) %prev.i, i8 0, i64 131072, i1 false), !noalias !2610
  %_8.0.i = add nsw i64 %input.1, -8
  %18 = add nuw i64 %input.1, 16
  %19 = add nsw i64 %input.1, -10
  br label %bb5.i

bb177.i:                                          ; preds = %bb174.i
  %p.sroa.0.4.i.lcssa = phi i64 [ %p.sroa.0.4.i, %bb174.i ]
  %nt.sroa.0.4.i.lcssa = phi i64 [ %nt.sroa.0.4.i, %bb174.i ]
  call void @llvm.lifetime.end.p0(ptr nonnull %prev.i), !noalias !2610
  call void @llvm.lifetime.end.p0(ptr nonnull %head.i), !noalias !2610
  br label %bb178.i

bb5.i:                                            ; preds = %bb5.i.preheader, %bb174.i
  %nt.sroa.0.1.i2244 = phi i64 [ %nt.sroa.0.4.i, %bb174.i ], [ 0, %bb5.i.preheader ]
  %miss.sroa.0.0.i2243 = phi i64 [ %miss.sroa.0.1.i, %bb174.i ], [ 0, %bb5.i.preheader ]
  %fuel.sroa.0.0.i2242 = phi i64 [ %_15.0.i, %bb174.i ], [ %18, %bb5.i.preheader ]
  %p.sroa.0.1.i2241 = phi i64 [ %p.sroa.0.4.i, %bb174.i ], [ 0, %bb5.i.preheader ]
  %ins.sroa.0.0.i2240 = phi i64 [ %ins.sroa.0.3.i, %bb174.i ], [ 0, %bb5.i.preheader ]
  %p.sroa.0.1.i2241.fr = freeze i64 %p.sroa.0.1.i2241
  %_15.0.i = add i64 %fuel.sroa.0.0.i2242, -1
  %_16.i2165 = icmp ult i64 %ins.sroa.0.0.i2240, %p.sroa.0.1.i2241.fr
  br i1 %_16.i2165, label %bb8.i, label %bb11.i

bb1.i190:                                         ; preds = %bb1.i190.preheader2843, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit196
  %nt.sroa.0.2.i2249 = phi i64 [ %_10.0.i195, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit196 ], [ %nt.sroa.0.2.i2249.ph, %bb1.i190.preheader2843 ]
  %p.sroa.0.2.i2248 = phi i64 [ %_241.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit196 ], [ %p.sroa.0.2.i2248.ph, %bb1.i190.preheader2843 ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2604)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2607)
  %exitcond2396.not = icmp eq i64 %nt.sroa.0.2.i2249, %umax
  br i1 %exitcond2396.not, label %panic1.i192, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit196

panic1.i192:                                      ; preds = %bb1.i190
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %umax, i64 noundef range(i64 0, 2305843009213693952) %out.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_1e808d4a560d2bfb30193cdd1b6f1f95) #13, !noalias !2611
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit196: ; preds = %bb1.i190
  %20 = getelementptr inbounds nuw i8, ptr %input.0, i64 %p.sroa.0.2.i2248
  %_5.i194 = load i8, ptr %20, align 1, !alias.scope !2604, !noalias !2607, !noundef !136
  %21 = getelementptr inbounds nuw [4 x i8], ptr %out.0, i64 %nt.sroa.0.2.i2249
  %22 = zext i8 %_5.i194 to i32
  store i32 %22, ptr %21, align 4, !alias.scope !2607, !noalias !2604
  %_10.0.i195 = add i64 %nt.sroa.0.2.i2249, 1
  %_241.0.i = add i64 %p.sroa.0.2.i2248, 1
  %exitcond2397.not = icmp eq i64 %_241.0.i, %input.1
  br i1 %exitcond2397.not, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse8u118_runKj10000_Kj8000_Kmffffffff_Kj4_Kjc_Kj40_Kj6_Kjf4240_Kj80_Kj1_Kj10_KB18_Kl40_Kj0_EB4_.exit, label %bb1.i190, !llvm.loop !2612

bb11.i:                                           ; preds = %bb8.i, %bb5.i
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2613)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2616)
  %23 = getelementptr inbounds nuw i8, ptr %input.0, i64 %p.sroa.0.1.i2241.fr
  %24 = load <4 x i8>, ptr %23, align 1, !alias.scope !2618, !noalias !2621
  %25 = bitcast <4 x i8> %24 to i32
  %26 = call i32 @llvm.bswap.i32(i32 %25)
  %27 = zext i32 %26 to i64
  %28 = mul i64 %27, -7046029254386353131
  %29 = lshr i64 %28, 48
  %30 = getelementptr inbounds nuw [4 x i8], ptr %head.i, i64 %29
  %old.i173.i = load i32, ptr %30, align 4, !alias.scope !2613, !noalias !2622, !noundef !136
  %_16.i174.i = and i64 %p.sroa.0.1.i2241.fr, 32767
  %31 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_16.i174.i
  store i32 %old.i173.i, ptr %31, align 4, !alias.scope !2616, !noalias !2624
  %32 = trunc i64 %p.sroa.0.1.i2241.fr to i32
  store i32 %32, ptr %30, align 4, !alias.scope !2613, !noalias !2622
  %_0.i175.i = zext i32 %old.i173.i to i64
  %_29.0.i = add i64 %p.sroa.0.1.i2241.fr, 1
  %_13.0.i9 = sub i64 %input.1, %p.sroa.0.1.i2241.fr
  %spec.store.select3.i10 = tail call i64 @llvm.umin.i64(i64 %_13.0.i9, i64 258)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2625)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2628)
  %spec.store.select.i16 = tail call i64 @llvm.umin.i64(i64 %_13.0.i9, i64 128)
  %33 = and i64 %spec.store.select3.i10, 504
  %34 = extractelement <4 x i8> %24, i64 3
  %_26.i1142169.not = icmp eq i64 %33, %spec.store.select3.i10
  br label %bb11.i18

bb11.i18:                                         ; preds = %bb39.i, %bb11.i
  %start1.sroa.0.0.i2176 = phi i64 [ %_0.i175.i, %bb11.i ], [ %spec.select25.i, %bb39.i ]
  %have.sroa.0.0.i2175 = phi i64 [ 3, %bb11.i ], [ %have.sroa.0.2.i, %bb39.i ]
  %depth.sroa.0.0.i2174 = phi i64 [ 12, %bb11.i ], [ %_68.0.i, %bb39.i ]
  %bd.sroa.0.0.i2173 = phi i64 [ 0, %bb11.i ], [ %bd.sroa.0.2.i, %bb39.i ]
  %pb.sroa.0.1.i2172 = phi i8 [ %34, %bb11.i ], [ %pb.sroa.0.3.i, %bb39.i ]
  %d.i = sub nsw i64 %p.sroa.0.1.i2241.fr, %start1.sroa.0.0.i2176
  %_29.i = add nsw i64 %d.i, -1
  %_28.i = icmp ult i64 %_29.i, 32768
  br i1 %_28.i, label %bb13.i, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit

bb13.i:                                           ; preds = %bb11.i18
  %_34.0.i = add nuw nsw i64 %start1.sroa.0.0.i2176, %have.sroa.0.0.i2175
  %_30.i = icmp ult i64 %_34.0.i, %input.1
  br i1 %_30.i, label %bb16.i19, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit

bb16.i19:                                         ; preds = %bb13.i
  %35 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_34.0.i
  %_36.i = load i8, ptr %35, align 1, !alias.scope !2625, !noalias !2628, !noundef !136
  %_35.i20 = icmp eq i8 %_36.i, %pb.sroa.0.1.i2172
  br i1 %_35.i20, label %bb2.i138, label %bb35.i

bb2.i138:                                         ; preds = %bb16.i19, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit
  %k.sroa.0.0.i1092168 = phi i64 [ %_10.0.i139, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit ], [ 0, %bb16.i19 ]
  %_10.0.i139 = add nuw nsw i64 %k.sroa.0.0.i1092168, 8
  %_7.not.i142 = icmp samesign ugt i64 %_10.0.i139, %spec.store.select3.i10
  br i1 %_7.not.i142, label %bb17.i110, label %bb4.i143

bb4.i143:                                         ; preds = %bb2.i138
  %_15.0.i144 = add nuw nsw i64 %k.sroa.0.0.i1092168, %start1.sroa.0.0.i2176
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2630)
  %_5.1.i439 = icmp ugt i64 %_15.0.i144, -9
  br i1 %_5.1.i439, label %panic.i506, label %bb1.i440

bb17.i110:                                        ; preds = %bb2.i138
  br i1 %_26.i1142169.not, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit164, label %bb21.i120

bb1.i440:                                         ; preds = %bb4.i143
  %_5.0.i441 = add nuw nsw i64 %_15.0.i144, 8
  %_3.not.i442 = icmp ugt i64 %_5.0.i441, %input.1
  br i1 %_3.not.i442, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit507, label %bb2.i443

panic.i506:                                       ; preds = %bb4.i143
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_440babfea49fec204c4bfa4556bd23df) #13, !noalias !2633
  unreachable

bb2.i443:                                         ; preds = %bb1.i440
  %36 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_15.0.i144
  %_15.i447 = load i8, ptr %36, align 1, !alias.scope !2630, !noalias !2628, !noundef !136
  %_14.i448 = zext i8 %_15.i447 to i64
  %_13.i449 = shl nuw i64 %_14.i448, 56
  %37 = getelementptr inbounds nuw i8, ptr %36, i64 1
  %_19.i454 = load i8, ptr %37, align 1, !alias.scope !2630, !noalias !2628, !noundef !136
  %_18.i455 = zext i8 %_19.i454 to i64
  %_17.i456 = shl nuw nsw i64 %_18.i455, 48
  %_12.i457 = or disjoint i64 %_17.i456, %_13.i449
  %38 = getelementptr inbounds nuw i8, ptr %36, i64 2
  %_25.i462 = load i8, ptr %38, align 1, !alias.scope !2630, !noalias !2628, !noundef !136
  %_24.i463 = zext i8 %_25.i462 to i64
  %_23.i464 = shl nuw nsw i64 %_24.i463, 40
  %_11.i465 = or disjoint i64 %_12.i457, %_23.i464
  %39 = getelementptr inbounds nuw i8, ptr %36, i64 3
  %_31.i470 = load i8, ptr %39, align 1, !alias.scope !2630, !noalias !2628, !noundef !136
  %_30.i471 = zext i8 %_31.i470 to i64
  %_29.i472 = shl nuw nsw i64 %_30.i471, 32
  %_10.i473 = or disjoint i64 %_11.i465, %_29.i472
  %40 = getelementptr inbounds nuw i8, ptr %36, i64 4
  %_37.i478 = load i8, ptr %40, align 1, !alias.scope !2630, !noalias !2628, !noundef !136
  %_36.i479 = zext i8 %_37.i478 to i64
  %_35.i480 = shl nuw nsw i64 %_36.i479, 24
  %_9.i481 = or disjoint i64 %_10.i473, %_35.i480
  %41 = getelementptr inbounds nuw i8, ptr %36, i64 5
  %_43.i486 = load i8, ptr %41, align 1, !alias.scope !2630, !noalias !2628, !noundef !136
  %_42.i487 = zext i8 %_43.i486 to i64
  %_41.i488 = shl nuw nsw i64 %_42.i487, 16
  %_8.i489 = or disjoint i64 %_9.i481, %_41.i488
  %42 = getelementptr inbounds nuw i8, ptr %36, i64 6
  %_49.i494 = load i8, ptr %42, align 1, !alias.scope !2630, !noalias !2628, !noundef !136
  %_48.i495 = zext i8 %_49.i494 to i64
  %_47.i496 = shl nuw nsw i64 %_48.i495, 8
  %_7.i497 = or i64 %_8.i489, %_47.i496
  %43 = getelementptr inbounds nuw i8, ptr %36, i64 7
  %_54.i502 = load i8, ptr %43, align 1, !alias.scope !2630, !noalias !2628, !noundef !136
  %_53.i503 = zext i8 %_54.i502 to i64
  %44 = or i64 %_7.i497, %_53.i503
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit507

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit507: ; preds = %bb1.i440, %bb2.i443
  %_0.sroa.0.0.i505 = phi i64 [ %44, %bb2.i443 ], [ 0, %bb1.i440 ]
  %_19.0.i148 = add nuw i64 %k.sroa.0.0.i1092168, %p.sroa.0.1.i2241.fr
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2634)
  %_5.1.i = icmp ugt i64 %_19.0.i148, -9
  br i1 %_5.1.i, label %panic.i438, label %bb1.i395

bb1.i395:                                         ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit507
  %_5.0.i396 = add nuw i64 %_19.0.i148, 8
  %_3.not.i397 = icmp ugt i64 %_5.0.i396, %input.1
  br i1 %_3.not.i397, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit, label %bb2.i398

panic.i438:                                       ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit507
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_440babfea49fec204c4bfa4556bd23df) #13, !noalias !2637
  unreachable

bb2.i398:                                         ; preds = %bb1.i395
  %45 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_19.0.i148
  %_15.i402 = load i8, ptr %45, align 1, !alias.scope !2634, !noalias !2628, !noundef !136
  %_14.i403 = zext i8 %_15.i402 to i64
  %_13.i404 = shl nuw i64 %_14.i403, 56
  %46 = getelementptr inbounds nuw i8, ptr %45, i64 1
  %_19.i407 = load i8, ptr %46, align 1, !alias.scope !2634, !noalias !2628, !noundef !136
  %_18.i408 = zext i8 %_19.i407 to i64
  %_17.i = shl nuw nsw i64 %_18.i408, 48
  %_12.i409 = or disjoint i64 %_17.i, %_13.i404
  %47 = getelementptr inbounds nuw i8, ptr %45, i64 2
  %_25.i413 = load i8, ptr %47, align 1, !alias.scope !2634, !noalias !2628, !noundef !136
  %_24.i414 = zext i8 %_25.i413 to i64
  %_23.i = shl nuw nsw i64 %_24.i414, 40
  %_11.i415 = or disjoint i64 %_12.i409, %_23.i
  %48 = getelementptr inbounds nuw i8, ptr %45, i64 3
  %_31.i = load i8, ptr %48, align 1, !alias.scope !2634, !noalias !2628, !noundef !136
  %_30.i419 = zext i8 %_31.i to i64
  %_29.i420 = shl nuw nsw i64 %_30.i419, 32
  %_10.i421 = or disjoint i64 %_11.i415, %_29.i420
  %49 = getelementptr inbounds nuw i8, ptr %45, i64 4
  %_37.i = load i8, ptr %49, align 1, !alias.scope !2634, !noalias !2628, !noundef !136
  %_36.i423 = zext i8 %_37.i to i64
  %_35.i424 = shl nuw nsw i64 %_36.i423, 24
  %_9.i425 = or disjoint i64 %_10.i421, %_35.i424
  %50 = getelementptr inbounds nuw i8, ptr %45, i64 5
  %_43.i = load i8, ptr %50, align 1, !alias.scope !2634, !noalias !2628, !noundef !136
  %_42.i = zext i8 %_43.i to i64
  %_41.i428 = shl nuw nsw i64 %_42.i, 16
  %_8.i429 = or disjoint i64 %_9.i425, %_41.i428
  %51 = getelementptr inbounds nuw i8, ptr %45, i64 6
  %_49.i432 = load i8, ptr %51, align 1, !alias.scope !2634, !noalias !2628, !noundef !136
  %_48.i = zext i8 %_49.i432 to i64
  %_47.i = shl nuw nsw i64 %_48.i, 8
  %_7.i433 = or i64 %_8.i429, %_47.i
  %52 = getelementptr inbounds nuw i8, ptr %45, i64 7
  %_54.i = load i8, ptr %52, align 1, !alias.scope !2634, !noalias !2628, !noundef !136
  %_53.i = zext i8 %_54.i to i64
  %53 = or i64 %_7.i433, %_53.i
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit: ; preds = %bb1.i395, %bb2.i398
  %_0.sroa.0.0.i437 = phi i64 [ %53, %bb2.i398 ], [ 0, %bb1.i395 ]
  %54 = icmp eq i64 %_0.sroa.0.0.i505, %_0.sroa.0.0.i437
  br i1 %54, label %bb2.i138, label %bb17.i110.thread

bb17.i110.thread:                                 ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit
  %_0.sroa.0.0.i437.lcssa = phi i64 [ %_0.sroa.0.0.i437, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit ]
  %_0.sroa.0.0.i505.lcssa2848 = phi i64 [ %_0.sroa.0.0.i505, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit ]
  %k.sroa.0.0.i1092168.lcssa2847 = phi i64 [ %k.sroa.0.0.i1092168, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit ]
  %x.i153 = xor i64 %_0.sroa.0.0.i437.lcssa, %_0.sroa.0.0.i505.lcssa2848
  %55 = tail call range(i64 0, 65) i64 @llvm.ctlz.i64(i64 %x.i153, i1 true)
  %_2220.i154 = lshr i64 %55, 3
  %_24.0.i155 = or disjoint i64 %_2220.i154, %k.sroa.0.0.i1092168.lcssa2847
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit164

bb21.i120:                                        ; preds = %bb17.i110, %bb24.i130
  %k.sroa.0.2.i1132171 = phi i64 [ %k.sroa.0.3.i135, %bb24.i130 ], [ %33, %bb17.i110 ]
  %_32.0.i118 = add nuw nsw i64 %k.sroa.0.2.i1132171, %start1.sroa.0.0.i2176
  %_34.i121 = icmp ult i64 %_32.0.i118, %input.1
  br i1 %_34.i121, label %bb22.i123, label %panic6.i122

bb22.i123:                                        ; preds = %bb21.i120
  %56 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_32.0.i118
  %_29.i124 = load i8, ptr %56, align 1, !alias.scope !2638, !noalias !2628, !noundef !136
  %_38.0.i125 = add i64 %k.sroa.0.2.i1132171, %p.sroa.0.1.i2241.fr
  %_38.1.i126 = icmp ult i64 %_38.0.i125, %p.sroa.0.1.i2241.fr
  br i1 %_38.1.i126, label %panic7.i136, label %bb23.i127

panic6.i122:                                      ; preds = %bb21.i120
  %_32.0.i118.lcssa2849 = phi i64 [ %_32.0.i118, %bb21.i120 ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_32.0.i118.lcssa2849, i64 noundef range(i64 0, -9223372036854775808) %input.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_d0bf91bac5912d1054a41f50a5372dd0) #13, !noalias !2628
  unreachable

bb23.i127:                                        ; preds = %bb22.i123
  %_39.i128 = icmp ult i64 %_38.0.i125, %input.1
  br i1 %_39.i128, label %bb24.i130, label %panic8.i129

panic7.i136:                                      ; preds = %bb22.i123
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_e58248ce06d86db1620e3928ca18f57a) #13, !noalias !2628
  unreachable

bb24.i130:                                        ; preds = %bb23.i127
  %57 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_38.0.i125
  %_35.i131 = load i8, ptr %57, align 1, !alias.scope !2638, !noalias !2628, !noundef !136
  %_28.i132 = icmp eq i8 %_29.i124, %_35.i131
  %_40.0.i133 = zext i1 %_28.i132 to i64
  %k.sroa.0.3.i135 = add nuw nsw i64 %k.sroa.0.2.i1132171, %_40.0.i133
  %_26.i114 = icmp samesign ult i64 %k.sroa.0.3.i135, %spec.store.select3.i10
  %or.cond.i115 = select i1 %_28.i132, i1 %_26.i114, i1 false
  br i1 %or.cond.i115, label %bb21.i120, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit164

panic8.i129:                                      ; preds = %bb23.i127
  %_38.0.i125.lcssa2853 = phi i64 [ %_38.0.i125, %bb23.i127 ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_38.0.i125.lcssa2853, i64 noundef range(i64 0, -9223372036854775808) %input.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_c7cb404ab9612aded1ce50ca918ced7b) #13, !noalias !2628
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit164: ; preds = %bb24.i130, %bb17.i110.thread, %bb17.i110
  %k.sroa.0.2.i113.lcssa = phi i64 [ %33, %bb17.i110 ], [ %_24.0.i155, %bb17.i110.thread ], [ %k.sroa.0.3.i135, %bb24.i130 ]
  %_46.i = icmp ugt i64 %k.sroa.0.2.i113.lcssa, %have.sroa.0.0.i2175
  br i1 %_46.i, label %bb19.i, label %bb35.i

bb35.i:                                           ; preds = %bb31.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit164, %bb16.i19
  %pb.sroa.0.3.i = phi i8 [ %pb.sroa.0.1.i2172, %bb16.i19 ], [ %pb.sroa.0.1.i2172, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit164 ], [ %59, %bb31.i ]
  %bd.sroa.0.2.i = phi i64 [ %bd.sroa.0.0.i2173, %bb16.i19 ], [ %bd.sroa.0.0.i2173, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit164 ], [ %d.i, %bb31.i ]
  %have.sroa.0.2.i = phi i64 [ %have.sroa.0.0.i2175, %bb16.i19 ], [ %have.sroa.0.0.i2175, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit164 ], [ %k.sroa.0.2.i113.lcssa, %bb31.i ]
  %_58.i = icmp eq i64 %depth.sroa.0.0.i2174, 1
  br i1 %_58.i, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit, label %bb39.i

bb19.i:                                           ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit164
  %_51.not.i = icmp ult i64 %k.sroa.0.2.i113.lcssa, %spec.store.select.i16
  br i1 %_51.not.i, label %bb26.i, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit

bb26.i:                                           ; preds = %bb19.i
  %_55.0.i = add i64 %k.sroa.0.2.i113.lcssa, %p.sroa.0.1.i2241.fr
  %_55.1.i = icmp ult i64 %_55.0.i, %p.sroa.0.1.i2241.fr
  br i1 %_55.1.i, label %panic7.i, label %bb27.i

bb27.i:                                           ; preds = %bb26.i
  %_53.not.i = icmp ult i64 %_55.0.i, %input.1
  br i1 %_53.not.i, label %bb31.i, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit

panic7.i:                                         ; preds = %bb26.i
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_f7734e5b3c0057e9bae084232237166a) #13, !noalias !2628
  unreachable

bb31.i:                                           ; preds = %bb27.i
  %58 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_55.0.i
  %59 = load i8, ptr %58, align 1, !alias.scope !2625, !noalias !2628, !noundef !136
  br label %bb35.i

bb39.i:                                           ; preds = %bb35.i
  %_62.i21 = and i64 %start1.sroa.0.0.i2176, 32767
  %60 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_62.i21
  %_61.i = load i32, ptr %60, align 4, !alias.scope !2628, !noalias !2625, !noundef !136
  %nx.i = zext i32 %_61.i to i64
  %_66.i.not = icmp ugt i64 %start1.sroa.0.0.i2176, %nx.i
  %_68.0.i = add nsw i64 %depth.sroa.0.0.i2174, -1
  %spec.select25.i = tail call i64 @llvm.umin.i64(i64 %start1.sroa.0.0.i2176, i64 %nx.i)
  br i1 %_66.i.not, label %bb11.i18, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit

_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit: ; preds = %bb19.i, %bb27.i, %bb13.i, %bb35.i, %bb39.i, %bb11.i18
  %have.sroa.0.1.i2406 = phi i64 [ %have.sroa.0.0.i2175, %bb11.i18 ], [ %k.sroa.0.2.i113.lcssa, %bb19.i ], [ %k.sroa.0.2.i113.lcssa, %bb27.i ], [ %have.sroa.0.0.i2175, %bb13.i ], [ %have.sroa.0.2.i, %bb35.i ], [ %have.sroa.0.2.i, %bb39.i ]
  %bd.sroa.0.1.i2405 = phi i64 [ %bd.sroa.0.0.i2173, %bb11.i18 ], [ %d.i, %bb19.i ], [ %d.i, %bb27.i ], [ %bd.sroa.0.0.i2173, %bb13.i ], [ %bd.sroa.0.2.i, %bb35.i ], [ %bd.sroa.0.2.i, %bb39.i ]
  %.not = icmp eq i64 %bd.sroa.0.1.i2405, 0
  br i1 %.not, label %bb154.i, label %bb16.i.preheader

bb16.i.preheader:                                 ; preds = %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit
  %_39.i2198 = icmp ult i64 %have.sroa.0.1.i2406, 64
  br i1 %_39.i2198, label %bb18.i.preheader, label %bb63.i

bb18.i.preheader:                                 ; preds = %bb16.i.preheader
  %61 = xor i64 %p.sroa.0.1.i2241.fr, -1
  %62 = add i64 %input.1, %61
  %umax2814 = call i64 @llvm.umax.i64(i64 %_8.0.i, i64 %_29.0.i)
  %umax2815 = call i64 @llvm.umax.i64(i64 %nt.sroa.0.1.i2244, i64 %out.1)
  br label %bb18.i

bb8.i:                                            ; preds = %bb5.i, %bb8.i
  %ins.sroa.0.1.i2166 = phi i64 [ %_23.0.i, %bb8.i ], [ %ins.sroa.0.0.i2240, %bb5.i ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2641)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2644)
  %63 = getelementptr inbounds nuw i8, ptr %input.0, i64 %ins.sroa.0.1.i2166
  %64 = load i32, ptr %63, align 1
  %65 = call i32 @llvm.bswap.i32(i32 %64)
  %66 = zext i32 %65 to i64
  %67 = mul i64 %66, -7046029254386353131
  %68 = lshr i64 %67, 48
  %69 = getelementptr inbounds nuw [4 x i8], ptr %head.i, i64 %68
  %old.i.i = load i32, ptr %69, align 4, !alias.scope !2641, !noalias !2646, !noundef !136
  %_16.i.i = and i64 %ins.sroa.0.1.i2166, 32767
  %70 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_16.i.i
  store i32 %old.i.i, ptr %70, align 4, !alias.scope !2644, !noalias !2648
  %71 = trunc i64 %ins.sroa.0.1.i2166 to i32
  store i32 %71, ptr %69, align 4, !alias.scope !2641, !noalias !2646
  %_23.0.i = add nuw nsw i64 %ins.sroa.0.1.i2166, 1
  %exitcond.not = icmp eq i64 %_23.0.i, %p.sroa.0.1.i2241.fr
  br i1 %exitcond.not, label %bb11.i, label %bb8.i

bb154.i:                                          ; preds = %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2649)
  %_9.i182 = icmp ult i64 %nt.sroa.0.1.i2244, %out.1
  br i1 %_9.i182, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit187, label %panic1.i183

panic1.i183:                                      ; preds = %bb154.i
  %nt.sroa.0.1.i2244.lcssa2922 = phi i64 [ %nt.sroa.0.1.i2244, %bb154.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %nt.sroa.0.1.i2244.lcssa2922, i64 noundef range(i64 0, 2305843009213693952) %out.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_1e808d4a560d2bfb30193cdd1b6f1f95) #13, !noalias !2652
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit187: ; preds = %bb154.i
  %72 = getelementptr inbounds nuw [4 x i8], ptr %out.0, i64 %nt.sroa.0.1.i2244
  %73 = extractelement <4 x i8> %24, i64 0
  %74 = zext i8 %73 to i32
  store i32 %74, ptr %72, align 4, !alias.scope !2649, !noalias !2654
  %_219.0.i = add i64 %miss.sroa.0.0.i2243, 1
  %_219.1.i = icmp eq i64 %miss.sroa.0.0.i2243, -1
  br i1 %_219.1.i, label %panic5.i, label %bb157.i

bb157.i:                                          ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit187
  %75 = lshr i64 %_219.0.i, 6
  %nt.sroa.0.3.i2177 = add nuw nsw i64 %nt.sroa.0.1.i2244, 1
  %_225.i2178 = icmp ne i64 %75, 0
  %_227.i2179 = icmp ult i64 %_29.0.i, %_8.0.i
  %or.cond45.i2180 = select i1 %_225.i2178, i1 %_227.i2179, i1 false
  br i1 %or.cond45.i2180, label %bb164.i.preheader, label %bb170.i

bb164.i.preheader:                                ; preds = %bb157.i
  %spec.store.select.i = tail call i64 @llvm.umin.i64(i64 %75, i64 1000000)
  %76 = sub i64 %19, %p.sroa.0.1.i2241.fr
  %77 = add nsw i64 %spec.store.select.i, -1
  %umin2816 = call i64 @llvm.umin.i64(i64 %76, i64 %77)
  %78 = freeze i64 %umin2816
  %79 = xor i64 %nt.sroa.0.1.i2244, -1
  %80 = add nsw i64 %out.1, %79
  %umin2817 = call i64 @llvm.umin.i64(i64 %78, i64 %80)
  %81 = add i64 %umin2817, 1
  %min.iters.check = icmp ult i64 %81, 9
  br i1 %min.iters.check, label %bb164.i.preheader2844, label %vector.ph

bb164.i.preheader2844:                            ; preds = %vector.body, %bb164.i.preheader
  %nt.sroa.0.3.i2183.ph = phi i64 [ %nt.sroa.0.3.i2177, %bb164.i.preheader ], [ %84, %vector.body ]
  %p.sroa.0.3.i2182.ph = phi i64 [ %_29.0.i, %bb164.i.preheader ], [ %85, %vector.body ]
  %step.sroa.0.0.i2181.ph = phi i64 [ %spec.store.select.i, %bb164.i.preheader ], [ %86, %vector.body ]
  br label %bb164.i

vector.ph:                                        ; preds = %bb164.i.preheader
  %n.mod.vf = and i64 %81, 7
  %82 = icmp eq i64 %n.mod.vf, 0
  %83 = select i1 %82, i64 8, i64 %n.mod.vf
  %n.vec = sub nuw i64 %81, %83
  %84 = add i64 %nt.sroa.0.3.i2177, %n.vec
  %85 = add i64 %_29.0.i, %n.vec
  %86 = sub i64 %spec.store.select.i, %n.vec
  %87 = getelementptr i8, ptr %input.0, i64 %_29.0.i
  %88 = getelementptr [4 x i8], ptr %out.0, i64 %nt.sroa.0.3.i2177
  br label %vector.body

vector.body:                                      ; preds = %vector.body, %vector.ph
  %index = phi i64 [ 0, %vector.ph ], [ %index.next, %vector.body ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2655)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2658)
  %89 = getelementptr i8, ptr %87, i64 %index
  %90 = getelementptr inbounds nuw i8, ptr %89, i64 4
  %wide.load = load <4 x i8>, ptr %89, align 1, !alias.scope !2655, !noalias !2658
  %wide.load2818 = load <4 x i8>, ptr %90, align 1, !alias.scope !2655, !noalias !2658
  %91 = getelementptr [4 x i8], ptr %88, i64 %index
  %92 = zext <4 x i8> %wide.load to <4 x i32>
  %93 = zext <4 x i8> %wide.load2818 to <4 x i32>
  %94 = getelementptr inbounds nuw i8, ptr %91, i64 16
  store <4 x i32> %92, ptr %91, align 4, !alias.scope !2658, !noalias !2655
  store <4 x i32> %93, ptr %94, align 4, !alias.scope !2658, !noalias !2655
  %index.next = add nuw i64 %index, 8
  %95 = icmp eq i64 %index.next, %n.vec
  br i1 %95, label %bb164.i.preheader2844, label %vector.body, !llvm.loop !2660

panic5.i:                                         ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit187
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_3040782d029b4f1f28da9c0a2089856b) #13
  unreachable

bb170.i:                                          ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit178, %bb157.i
  %p.sroa.0.3.i.lcssa = phi i64 [ %_29.0.i, %bb157.i ], [ %_231.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit178 ]
  %nt.sroa.0.3.i.lcssa = phi i64 [ %nt.sroa.0.3.i2177, %bb157.i ], [ %nt.sroa.0.3.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit178 ]
  %spec.select.i = tail call i64 @llvm.umax.i64(i64 %_29.0.i, i64 %p.sroa.0.3.i.lcssa)
  br label %bb174.i

bb164.i:                                          ; preds = %bb164.i.preheader2844, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit178
  %nt.sroa.0.3.i2183 = phi i64 [ %nt.sroa.0.3.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit178 ], [ %nt.sroa.0.3.i2183.ph, %bb164.i.preheader2844 ]
  %p.sroa.0.3.i2182 = phi i64 [ %_231.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit178 ], [ %p.sroa.0.3.i2182.ph, %bb164.i.preheader2844 ]
  %step.sroa.0.0.i2181 = phi i64 [ %_232.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit178 ], [ %step.sroa.0.0.i2181.ph, %bb164.i.preheader2844 ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2655)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2658)
  %exitcond2394.not = icmp eq i64 %nt.sroa.0.3.i2183, %out.1
  br i1 %exitcond2394.not, label %panic1.i174, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit178

panic1.i174:                                      ; preds = %bb164.i
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %out.1, i64 noundef range(i64 0, 2305843009213693952) %out.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_1e808d4a560d2bfb30193cdd1b6f1f95) #13, !noalias !2661
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit178: ; preds = %bb164.i
  %96 = getelementptr inbounds nuw i8, ptr %input.0, i64 %p.sroa.0.3.i2182
  %_5.i176 = load i8, ptr %96, align 1, !alias.scope !2655, !noalias !2658, !noundef !136
  %97 = getelementptr inbounds nuw [4 x i8], ptr %out.0, i64 %nt.sroa.0.3.i2183
  %98 = zext i8 %_5.i176 to i32
  store i32 %98, ptr %97, align 4, !alias.scope !2658, !noalias !2655
  %_231.0.i = add nuw nsw i64 %p.sroa.0.3.i2182, 1
  %_232.0.i = add nsw i64 %step.sroa.0.0.i2181, -1
  %nt.sroa.0.3.i = add i64 %nt.sroa.0.3.i2183, 1
  %_225.i = icmp ne i64 %_232.0.i, 0
  %_227.i = icmp ult i64 %_231.0.i, %_8.0.i
  %or.cond45.i = select i1 %_225.i, i1 %_227.i, i1 false
  br i1 %or.cond45.i, label %bb164.i, label %bb170.i, !llvm.loop !2662

bb174.i:                                          ; preds = %bb150.i, %bb170.i
  %ins.sroa.0.3.i = phi i64 [ %spec.select140.i, %bb150.i ], [ %spec.select.i, %bb170.i ]
  %p.sroa.0.4.i = phi i64 [ %_19.0.i201, %bb150.i ], [ %p.sroa.0.3.i.lcssa, %bb170.i ]
  %miss.sroa.0.1.i = phi i64 [ 0, %bb150.i ], [ %_219.0.i, %bb170.i ]
  %nt.sroa.0.4.i = phi i64 [ %_17.0.i, %bb150.i ], [ %nt.sroa.0.3.i.lcssa, %bb170.i ]
  %_11.i = icmp ult i64 %p.sroa.0.4.i, %_8.0.i
  %_13.i = icmp ne i64 %_15.0.i, 0
  %or.cond.i = select i1 %_11.i, i1 %_13.i, i1 false
  br i1 %or.cond.i, label %bb5.i, label %bb177.i

bb18.i:                                           ; preds = %bb18.i.preheader, %bb59.i
  %indvars.iv2812 = phi i64 [ %62, %bb18.i.preheader ], [ %indvars.iv.next2813, %bb59.i ]
  %indvars.iv = phi i64 [ %_29.0.i, %bb18.i.preheader ], [ %indvars.iv.next, %bb59.i ]
  %nt.sroa.0.5.i2203 = phi i64 [ %nt.sroa.0.1.i2244, %bb18.i.preheader ], [ %_10.0.i169, %bb59.i ]
  %l.sroa.0.0.i2202 = phi i64 [ %have.sroa.0.1.i2406, %bb18.i.preheader ], [ %k.sroa.0.2.i.lcssa, %bb59.i ]
  %d.sroa.0.0.i2201 = phi i64 [ %bd.sroa.0.1.i2405, %bb18.i.preheader ], [ %d.i38, %bb59.i ]
  %p.sroa.0.5.i2200 = phi i64 [ %p.sroa.0.1.i2241.fr, %bb18.i.preheader ], [ %_44.0.i, %bb59.i ]
  %_44.0.i = add i64 %p.sroa.0.5.i2200, 1
  %umin = call i64 @llvm.umin.i64(i64 %indvars.iv2812, i64 258)
  %99 = and i64 %umin, 504
  %_41.i = icmp ult i64 %_44.0.i, %_8.0.i
  br i1 %_41.i, label %bb21.i, label %bb63.i

bb63.i:                                           ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit, %bb16.i53, %bb48.i41, %bb13.i51, %bb9.i27, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit687, %bb59.i, %bb18.i, %bb16.i.preheader
  %ins.sroa.0.4.i.lcssa = phi i64 [ %_29.0.i, %bb16.i.preheader ], [ %indvars.iv.next, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit ], [ %indvars.iv.next, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit ], [ %indvars.iv.next, %bb16.i53 ], [ %indvars.iv.next, %bb48.i41 ], [ %indvars.iv.next, %bb13.i51 ], [ %indvars.iv.next, %bb9.i27 ], [ %indvars.iv.next, %bb59.i ], [ %indvars.iv.next, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit687 ], [ %umax2814, %bb18.i ]
  %p.sroa.0.5.i.lcssa = phi i64 [ %p.sroa.0.1.i2241.fr, %bb16.i.preheader ], [ %p.sroa.0.5.i2200, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit ], [ %p.sroa.0.5.i2200, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit ], [ %p.sroa.0.5.i2200, %bb16.i53 ], [ %p.sroa.0.5.i2200, %bb48.i41 ], [ %p.sroa.0.5.i2200, %bb13.i51 ], [ %p.sroa.0.5.i2200, %bb9.i27 ], [ %_44.0.i, %bb59.i ], [ %p.sroa.0.5.i2200, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit687 ], [ %p.sroa.0.5.i2200, %bb18.i ]
  %d.sroa.0.0.i.lcssa = phi i64 [ %bd.sroa.0.1.i2405, %bb16.i.preheader ], [ %d.sroa.0.0.i2201, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit ], [ %d.sroa.0.0.i2201, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit ], [ %d.sroa.0.0.i2201, %bb16.i53 ], [ %d.sroa.0.0.i2201, %bb48.i41 ], [ %d.sroa.0.0.i2201, %bb13.i51 ], [ %d.sroa.0.0.i2201, %bb9.i27 ], [ %d.i38, %bb59.i ], [ %d.sroa.0.0.i2201, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit687 ], [ %d.sroa.0.0.i2201, %bb18.i ]
  %l.sroa.0.0.i.lcssa = phi i64 [ %have.sroa.0.1.i2406, %bb16.i.preheader ], [ %l.sroa.0.0.i2202, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit ], [ %l.sroa.0.0.i2202, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit ], [ %l.sroa.0.0.i2202, %bb16.i53 ], [ %l.sroa.0.0.i2202, %bb48.i41 ], [ %l.sroa.0.0.i2202, %bb13.i51 ], [ %l.sroa.0.0.i2202, %bb9.i27 ], [ %k.sroa.0.2.i.lcssa, %bb59.i ], [ %l.sroa.0.0.i2202, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit687 ], [ %l.sroa.0.0.i2202, %bb18.i ]
  %nt.sroa.0.5.i.lcssa = phi i64 [ %nt.sroa.0.1.i2244, %bb16.i.preheader ], [ %nt.sroa.0.5.i2203, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit ], [ %nt.sroa.0.5.i2203, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit ], [ %nt.sroa.0.5.i2203, %bb16.i53 ], [ %nt.sroa.0.5.i2203, %bb48.i41 ], [ %nt.sroa.0.5.i2203, %bb13.i51 ], [ %nt.sroa.0.5.i2203, %bb9.i27 ], [ %_10.0.i169, %bb59.i ], [ %nt.sroa.0.5.i2203, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit687 ], [ %nt.sroa.0.5.i2203, %bb18.i ]
  %100 = add i64 %nt.sroa.0.5.i.lcssa, -1
  %101 = icmp ult i64 %100, %out.1
  %_110.i2218 = icmp ult i64 %l.sroa.0.0.i.lcssa, 258
  %or.cond49.i2219 = select i1 %101, i1 %_110.i2218, i1 false
  %_112.i2220 = icmp ult i64 %d.sroa.0.0.i.lcssa, %p.sroa.0.5.i.lcssa
  %or.cond139.i2221 = and i1 %or.cond49.i2219, %_112.i2220
  br i1 %or.cond139.i2221, label %bb71.i, label %bb116.i

bb21.i:                                           ; preds = %bb18.i
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2663)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2666)
  %102 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_44.0.i
  %103 = getelementptr inbounds nuw i8, ptr %input.0, i64 %p.sroa.0.5.i2200
  %104 = load i32, ptr %102, align 1
  %105 = call i32 @llvm.bswap.i32(i32 %104)
  %106 = zext i32 %105 to i64
  %107 = mul i64 %106, -7046029254386353131
  %108 = lshr i64 %107, 48
  %109 = getelementptr inbounds nuw [4 x i8], ptr %head.i, i64 %108
  %old.i166.i = load i32, ptr %109, align 4, !alias.scope !2663, !noalias !2668, !noundef !136
  %_16.i167.i = and i64 %_44.0.i, 32767
  %110 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_16.i167.i
  store i32 %old.i166.i, ptr %110, align 4, !alias.scope !2666, !noalias !2670
  %111 = trunc i64 %_44.0.i to i32
  store i32 %111, ptr %109, align 4, !alias.scope !2663, !noalias !2668
  %_0.i168.i = zext i32 %old.i166.i to i64
  %indvars.iv.next = add nuw i64 %indvars.iv, 1
  %_56.0.i = add nsw i64 %l.sroa.0.0.i2202, -1
  %spec.select.i3 = tail call i64 @llvm.umax.i64(i64 %_56.0.i, i64 3)
  %_13.0.i = sub nuw nsw i64 %input.1, %_44.0.i
  %spec.store.select3.i = tail call i64 @llvm.umin.i64(i64 %_13.0.i, i64 258)
  %spec.store.select.i24 = tail call i64 @llvm.umin.i64(i64 %_13.0.i, i64 128)
  %_19.0.i25 = add nuw i64 %spec.select.i3, %_44.0.i
  %_16.i26 = icmp ult i64 %_19.0.i25, %input.1
  br i1 %_16.i26, label %bb7.i84, label %bb9.i27

bb9.i27:                                          ; preds = %bb7.i84, %bb21.i
  %pb.sroa.0.0.i28 = phi i8 [ %113, %bb7.i84 ], [ 0, %bb21.i ]
  %d.i38 = sub nsw i64 %_44.0.i, %_0.i168.i
  %_29.i39 = add nsw i64 %d.i38, -1
  %_28.i40 = icmp ult i64 %_29.i39, 32768
  br i1 %_28.i40, label %bb13.i51, label %bb63.i

bb7.i84:                                          ; preds = %bb21.i
  %112 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_19.0.i25
  %113 = load i8, ptr %112, align 1, !alias.scope !2671, !noalias !2674, !noundef !136
  br label %bb9.i27

bb13.i51:                                         ; preds = %bb9.i27
  %_34.0.i49 = add nuw nsw i64 %spec.select.i3, %_0.i168.i
  %_30.i52 = icmp ult i64 %_34.0.i49, %input.1
  br i1 %_30.i52, label %bb16.i53, label %bb63.i

bb48.i41:                                         ; preds = %bb50.i
  %.not2593 = icmp eq i64 %d.i38, 0
  br i1 %.not2593, label %bb63.i, label %bb29.i

bb16.i53:                                         ; preds = %bb13.i51
  %114 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_34.0.i49
  %_36.i54 = load i8, ptr %114, align 1, !alias.scope !2671, !noalias !2674, !noundef !136
  %_35.i55 = icmp eq i8 %_36.i54, %pb.sroa.0.0.i28
  br i1 %_35.i55, label %bb2.i.preheader, label %bb63.i

bb2.i.preheader:                                  ; preds = %bb16.i53
  %_19.1.i.not = icmp ugt i64 %indvars.iv, %p.sroa.0.5.i2200
  br label %bb2.i

bb2.i:                                            ; preds = %bb2.i.preheader, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit576
  %k.sroa.0.0.i2187 = phi i64 [ %_10.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit576 ], [ 0, %bb2.i.preheader ]
  %_10.0.i = add nuw nsw i64 %k.sroa.0.0.i2187, 8
  %_7.not.i = icmp samesign ugt i64 %_10.0.i, %spec.store.select3.i
  br i1 %_7.not.i, label %bb17.i87, label %bb4.i

bb4.i:                                            ; preds = %bb2.i
  %_15.0.i99 = add nuw nsw i64 %k.sroa.0.0.i2187, %_0.i168.i
  %_5.0.i579 = add nuw nsw i64 %_15.0.i99, 8
  %_3.not.i580 = icmp samesign ugt i64 %_5.0.i579, %input.1
  br i1 %_3.not.i580, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit645, label %bb2.i581

bb17.i87:                                         ; preds = %bb2.i
  %_26.i2188 = icmp samesign ult i64 %99, %spec.store.select3.i
  br i1 %_26.i2188, label %bb20.i, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit

bb2.i581:                                         ; preds = %bb4.i
  %115 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_15.0.i99
  %_15.i585 = load i8, ptr %115, align 1, !alias.scope !2676, !noalias !2674, !noundef !136
  %_14.i586 = zext i8 %_15.i585 to i64
  %_13.i587 = shl nuw i64 %_14.i586, 56
  %116 = getelementptr inbounds nuw i8, ptr %115, i64 1
  %_19.i592 = load i8, ptr %116, align 1, !alias.scope !2676, !noalias !2674, !noundef !136
  %_18.i593 = zext i8 %_19.i592 to i64
  %_17.i594 = shl nuw nsw i64 %_18.i593, 48
  %_12.i595 = or disjoint i64 %_17.i594, %_13.i587
  %117 = getelementptr inbounds nuw i8, ptr %115, i64 2
  %_25.i600 = load i8, ptr %117, align 1, !alias.scope !2676, !noalias !2674, !noundef !136
  %_24.i601 = zext i8 %_25.i600 to i64
  %_23.i602 = shl nuw nsw i64 %_24.i601, 40
  %_11.i603 = or disjoint i64 %_12.i595, %_23.i602
  %118 = getelementptr inbounds nuw i8, ptr %115, i64 3
  %_31.i608 = load i8, ptr %118, align 1, !alias.scope !2676, !noalias !2674, !noundef !136
  %_30.i609 = zext i8 %_31.i608 to i64
  %_29.i610 = shl nuw nsw i64 %_30.i609, 32
  %_10.i611 = or disjoint i64 %_11.i603, %_29.i610
  %119 = getelementptr inbounds nuw i8, ptr %115, i64 4
  %_37.i616 = load i8, ptr %119, align 1, !alias.scope !2676, !noalias !2674, !noundef !136
  %_36.i617 = zext i8 %_37.i616 to i64
  %_35.i618 = shl nuw nsw i64 %_36.i617, 24
  %_9.i619 = or disjoint i64 %_10.i611, %_35.i618
  %120 = getelementptr inbounds nuw i8, ptr %115, i64 5
  %_43.i624 = load i8, ptr %120, align 1, !alias.scope !2676, !noalias !2674, !noundef !136
  %_42.i625 = zext i8 %_43.i624 to i64
  %_41.i626 = shl nuw nsw i64 %_42.i625, 16
  %_8.i627 = or disjoint i64 %_9.i619, %_41.i626
  %121 = getelementptr inbounds nuw i8, ptr %115, i64 6
  %_49.i632 = load i8, ptr %121, align 1, !alias.scope !2676, !noalias !2674, !noundef !136
  %_48.i633 = zext i8 %_49.i632 to i64
  %_47.i634 = shl nuw nsw i64 %_48.i633, 8
  %_7.i635 = or i64 %_8.i627, %_47.i634
  %122 = getelementptr inbounds nuw i8, ptr %115, i64 7
  %_54.i640 = load i8, ptr %122, align 1, !alias.scope !2676, !noalias !2674, !noundef !136
  %_53.i641 = zext i8 %_54.i640 to i64
  %123 = or i64 %_7.i635, %_53.i641
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit645

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit645: ; preds = %bb4.i, %bb2.i581
  %_0.sroa.0.0.i643 = phi i64 [ %123, %bb2.i581 ], [ 0, %bb4.i ]
  %_19.0.i101 = add nuw i64 %k.sroa.0.0.i2187, %_44.0.i
  br i1 %_19.1.i.not, label %bb7.i102, label %panic2.i

bb7.i102:                                         ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit645
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2679)
  %_5.1.i508 = icmp ugt i64 %_19.0.i101, -9
  br i1 %_5.1.i508, label %panic.i575, label %bb1.i509

bb1.i509:                                         ; preds = %bb7.i102
  %_5.0.i510 = add nuw i64 %_19.0.i101, 8
  %_3.not.i511 = icmp ugt i64 %_5.0.i510, %input.1
  br i1 %_3.not.i511, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit576, label %bb2.i512

panic.i575:                                       ; preds = %bb7.i102
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_440babfea49fec204c4bfa4556bd23df) #13, !noalias !2682
  unreachable

bb2.i512:                                         ; preds = %bb1.i509
  %124 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_19.0.i101
  %_15.i516 = load i8, ptr %124, align 1, !alias.scope !2679, !noalias !2674, !noundef !136
  %_14.i517 = zext i8 %_15.i516 to i64
  %_13.i518 = shl nuw i64 %_14.i517, 56
  %125 = getelementptr inbounds nuw i8, ptr %124, i64 1
  %_19.i523 = load i8, ptr %125, align 1, !alias.scope !2679, !noalias !2674, !noundef !136
  %_18.i524 = zext i8 %_19.i523 to i64
  %_17.i525 = shl nuw nsw i64 %_18.i524, 48
  %_12.i526 = or disjoint i64 %_17.i525, %_13.i518
  %126 = getelementptr inbounds nuw i8, ptr %124, i64 2
  %_25.i531 = load i8, ptr %126, align 1, !alias.scope !2679, !noalias !2674, !noundef !136
  %_24.i532 = zext i8 %_25.i531 to i64
  %_23.i533 = shl nuw nsw i64 %_24.i532, 40
  %_11.i534 = or disjoint i64 %_12.i526, %_23.i533
  %127 = getelementptr inbounds nuw i8, ptr %124, i64 3
  %_31.i539 = load i8, ptr %127, align 1, !alias.scope !2679, !noalias !2674, !noundef !136
  %_30.i540 = zext i8 %_31.i539 to i64
  %_29.i541 = shl nuw nsw i64 %_30.i540, 32
  %_10.i542 = or disjoint i64 %_11.i534, %_29.i541
  %128 = getelementptr inbounds nuw i8, ptr %124, i64 4
  %_37.i547 = load i8, ptr %128, align 1, !alias.scope !2679, !noalias !2674, !noundef !136
  %_36.i548 = zext i8 %_37.i547 to i64
  %_35.i549 = shl nuw nsw i64 %_36.i548, 24
  %_9.i550 = or disjoint i64 %_10.i542, %_35.i549
  %129 = getelementptr inbounds nuw i8, ptr %124, i64 5
  %_43.i555 = load i8, ptr %129, align 1, !alias.scope !2679, !noalias !2674, !noundef !136
  %_42.i556 = zext i8 %_43.i555 to i64
  %_41.i557 = shl nuw nsw i64 %_42.i556, 16
  %_8.i558 = or disjoint i64 %_9.i550, %_41.i557
  %130 = getelementptr inbounds nuw i8, ptr %124, i64 6
  %_49.i563 = load i8, ptr %130, align 1, !alias.scope !2679, !noalias !2674, !noundef !136
  %_48.i564 = zext i8 %_49.i563 to i64
  %_47.i565 = shl nuw nsw i64 %_48.i564, 8
  %_7.i566 = or i64 %_8.i558, %_47.i565
  %131 = getelementptr inbounds nuw i8, ptr %124, i64 7
  %_54.i571 = load i8, ptr %131, align 1, !alias.scope !2679, !noalias !2674, !noundef !136
  %_53.i572 = zext i8 %_54.i571 to i64
  %132 = or i64 %_7.i566, %_53.i572
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit576

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit576: ; preds = %bb1.i509, %bb2.i512
  %_0.sroa.0.0.i574 = phi i64 [ %132, %bb2.i512 ], [ 0, %bb1.i509 ]
  %133 = icmp eq i64 %_0.sroa.0.0.i643, %_0.sroa.0.0.i574
  br i1 %133, label %bb2.i, label %bb17.i87.thread

panic2.i:                                         ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit645
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_8dedf8bdbae2e7f670fff12535f0d90a) #13, !noalias !2674
  unreachable

bb17.i87.thread:                                  ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit576
  %_0.sroa.0.0.i574.lcssa = phi i64 [ %_0.sroa.0.0.i574, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit576 ]
  %_0.sroa.0.0.i643.lcssa2859 = phi i64 [ %_0.sroa.0.0.i643, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit576 ]
  %k.sroa.0.0.i2187.lcssa2857 = phi i64 [ %k.sroa.0.0.i2187, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit576 ]
  %x.i = xor i64 %_0.sroa.0.0.i574.lcssa, %_0.sroa.0.0.i643.lcssa2859
  %134 = tail call range(i64 0, 65) i64 @llvm.ctlz.i64(i64 %x.i, i1 true)
  %_2220.i = lshr i64 %134, 3
  %_24.0.i = or disjoint i64 %_2220.i, %k.sroa.0.0.i2187.lcssa2857
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit

bb20.i:                                           ; preds = %bb17.i87, %bb24.i
  %k.sroa.0.2.i2190 = phi i64 [ %k.sroa.0.3.i, %bb24.i ], [ %99, %bb17.i87 ]
  %_32.0.i = add i64 %k.sroa.0.2.i2190, %_0.i168.i
  %_32.1.i = icmp ult i64 %_32.0.i, %_0.i168.i
  br i1 %_32.1.i, label %panic5.i97, label %bb21.i91

bb21.i91:                                         ; preds = %bb20.i
  %_34.i = icmp ult i64 %_32.0.i, %input.1
  br i1 %_34.i, label %bb22.i, label %panic6.i

panic5.i97:                                       ; preds = %bb20.i
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_68f9c5f1b64c796baf34863c111ebbab) #13, !noalias !2674
  unreachable

bb22.i:                                           ; preds = %bb21.i91
  %135 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_32.0.i
  %_29.i92 = load i8, ptr %135, align 1, !alias.scope !2683, !noalias !2674, !noundef !136
  %_38.0.i = add i64 %k.sroa.0.2.i2190, %_44.0.i
  %_38.1.i.not = icmp ugt i64 %_38.0.i, %p.sroa.0.5.i2200
  br i1 %_38.1.i.not, label %bb23.i, label %panic7.i96

panic6.i:                                         ; preds = %bb21.i91
  %_32.0.i.lcssa2860 = phi i64 [ %_32.0.i, %bb21.i91 ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_32.0.i.lcssa2860, i64 noundef range(i64 0, -9223372036854775808) %input.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_d0bf91bac5912d1054a41f50a5372dd0) #13, !noalias !2674
  unreachable

bb23.i:                                           ; preds = %bb22.i
  %_39.i93 = icmp ult i64 %_38.0.i, %input.1
  br i1 %_39.i93, label %bb24.i, label %panic8.i

panic7.i96:                                       ; preds = %bb22.i
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_e58248ce06d86db1620e3928ca18f57a) #13, !noalias !2674
  unreachable

bb24.i:                                           ; preds = %bb23.i
  %136 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_38.0.i
  %_35.i94 = load i8, ptr %136, align 1, !alias.scope !2683, !noalias !2674, !noundef !136
  %_28.i95 = icmp eq i8 %_29.i92, %_35.i94
  %_40.0.i = zext i1 %_28.i95 to i64
  %k.sroa.0.3.i = add nuw i64 %k.sroa.0.2.i2190, %_40.0.i
  %_26.i = icmp ult i64 %k.sroa.0.3.i, %spec.store.select3.i
  %or.cond.i89 = select i1 %_28.i95, i1 %_26.i, i1 false
  br i1 %or.cond.i89, label %bb20.i, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit

panic8.i:                                         ; preds = %bb23.i
  %_38.0.i.lcssa2864 = phi i64 [ %_38.0.i, %bb23.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_38.0.i.lcssa2864, i64 noundef range(i64 0, -9223372036854775808) %input.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_c7cb404ab9612aded1ce50ca918ced7b) #13, !noalias !2674
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit: ; preds = %bb24.i, %bb17.i87.thread, %bb17.i87
  %k.sroa.0.2.i.lcssa = phi i64 [ %99, %bb17.i87 ], [ %_24.0.i, %bb17.i87.thread ], [ %k.sroa.0.3.i, %bb24.i ]
  %_46.i73 = icmp ugt i64 %k.sroa.0.2.i.lcssa, %spec.select.i3
  br i1 %_46.i73, label %bb19.i74, label %bb63.i

bb19.i74:                                         ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit
  %137 = add i64 %k.sroa.0.2.i.lcssa, -11
  %or.cond.i646 = icmp ult i64 %137, 247
  br i1 %or.cond.i646, label %bb6.i, label %bb7.i647

bb7.i647:                                         ; preds = %bb6.i, %bb19.i74
  %c.sroa.0.0.i = phi i32 [ %140, %bb6.i ], [ 168, %bb19.i74 ]
  %_17.i648 = icmp ugt i64 %d.i38, 4
  br i1 %_17.i648, label %bb12.i657, label %bb13.i649

bb6.i:                                            ; preds = %bb19.i74
  %138 = trunc nuw nsw i64 %k.sroa.0.2.i.lcssa to i32
  %_11.i660 = add nsw i32 %138, -3
  %_10.i661 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_11.i660, i1 false)
  %139 = shl nuw nsw i32 %_10.i661, 4
  %140 = sub nuw nsw i32 632, %139
  br label %bb7.i647

bb13.i649:                                        ; preds = %bb12.i657, %bb7.i647
  %c.sroa.0.1.i = phi i32 [ %144, %bb12.i657 ], [ %c.sroa.0.0.i, %bb7.i647 ]
  %_29.i650 = trunc i64 %k.sroa.0.2.i.lcssa to i32
  %141 = add i32 %_29.i650, -33554432
  %_30.1.i = icmp ult i32 %141, -67108864
  br i1 %_30.1.i, label %panic8.i654, label %bb14.i651

bb12.i657:                                        ; preds = %bb7.i647
  %142 = trunc nuw i64 %d.i38 to i32
  %_22.i656 = add nsw i32 %142, -1
  %_21.i658 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_22.i656, i1 true)
  %143 = shl nuw nsw i32 %_21.i658, 4
  %reass.sub = sub nsw i32 %c.sroa.0.0.i, %143
  %144 = add nsw i32 %reass.sub, 480
  br label %bb13.i649

bb14.i651:                                        ; preds = %bb13.i649
  %_30.0.i = shl nsw i32 %_29.i650, 6
  %145 = tail call { i32, i1 } @llvm.ssub.with.overflow.i32(i32 %_30.0.i, i32 %c.sroa.0.1.i)
  %_31.1.i = extractvalue { i32, i1 } %145, 1
  br i1 %_31.1.i, label %panic9.i653, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit

panic8.i654:                                      ; preds = %bb13.i649
; call core::panicking::panic_const::panic_const_mul_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_mul_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_5bf2e340c7b7e1a7a2cf8d7086d6ac68) #13, !noalias !2674
  unreachable

panic9.i653:                                      ; preds = %bb14.i651
; call core::panicking::panic_const::panic_const_sub_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_5bf2e340c7b7e1a7a2cf8d7086d6ac68) #13, !noalias !2674
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit: ; preds = %bb14.i651
  %_31.0.i = extractvalue { i32, i1 } %145, 0
  %_49.i = icmp sgt i32 %_31.0.i, -1000000
  br i1 %_49.i, label %bb50.i, label %bb63.i

bb50.i:                                           ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit
  %_51.not.i75 = icmp uge i64 %k.sroa.0.2.i.lcssa, %spec.store.select.i24
  %_55.0.i77 = add nuw i64 %k.sroa.0.2.i.lcssa, %_44.0.i
  %_55.1.i78.not = icmp ugt i64 %_55.0.i77, %p.sroa.0.5.i2200
  %or.cond2590 = select i1 %_51.not.i75, i1 true, i1 %_55.1.i78.not
  br i1 %or.cond2590, label %bb48.i41, label %panic7.i82

panic7.i82:                                       ; preds = %bb50.i
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_f7734e5b3c0057e9bae084232237166a) #13, !noalias !2674
  unreachable

bb29.i:                                           ; preds = %bb48.i41
  br i1 %or.cond.i646, label %bb6.i710, label %bb7.i689

bb7.i689:                                         ; preds = %bb6.i710, %bb29.i
  %c.sroa.0.0.i690 = phi i32 [ %147, %bb6.i710 ], [ 168, %bb29.i ]
  br i1 %_17.i648, label %bb12.i706, label %bb14.i696

bb6.i710:                                         ; preds = %bb29.i
  %_11.i711 = add nsw i32 %_29.i650, -3
  %_10.i712 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_11.i711, i1 false)
  %146 = shl nuw nsw i32 %_10.i712, 4
  %147 = sub nuw nsw i32 632, %146
  br label %bb7.i689

bb12.i706:                                        ; preds = %bb7.i689
  %148 = trunc nuw i64 %d.i38 to i32
  %_22.i704 = add nsw i32 %148, -1
  %_21.i707 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_22.i704, i1 true)
  %149 = shl nuw nsw i32 %_21.i707, 4
  %reass.sub2252 = sub nsw i32 %c.sroa.0.0.i690, %149
  %150 = add nsw i32 %reass.sub2252, 480
  br label %bb14.i696

bb14.i696:                                        ; preds = %bb7.i689, %bb12.i706
  %c.sroa.0.1.i693 = phi i32 [ %150, %bb12.i706 ], [ %c.sroa.0.0.i690, %bb7.i689 ]
  %151 = tail call { i32, i1 } @llvm.ssub.with.overflow.i32(i32 %_30.0.i, i32 %c.sroa.0.1.i693)
  %_31.1.i698 = extractvalue { i32, i1 } %151, 1
  br i1 %_31.1.i698, label %panic9.i701, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit713

panic9.i701:                                      ; preds = %bb14.i696
; call core::panicking::panic_const::panic_const_sub_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_5bf2e340c7b7e1a7a2cf8d7086d6ac68) #13
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit713: ; preds = %bb14.i696
  %_31.0.i700 = extractvalue { i32, i1 } %151, 0
  %152 = add nsw i64 %l.sroa.0.0.i2202, -11
  %or.cond.i662 = icmp ult i64 %152, 247
  br i1 %or.cond.i662, label %bb6.i684, label %bb7.i663

bb7.i663:                                         ; preds = %bb6.i684, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit713
  %c.sroa.0.0.i664 = phi i32 [ %155, %bb6.i684 ], [ 168, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit713 ]
  %_17.i665 = icmp ugt i64 %d.sroa.0.0.i2201, 4
  br i1 %_17.i665, label %bb8.i677, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit687

bb6.i684:                                         ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit713
  %153 = trunc nuw nsw i64 %l.sroa.0.0.i2202 to i32
  %_11.i685 = add nsw i32 %153, -3
  %_10.i686 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_11.i685, i1 false)
  %154 = shl nuw nsw i32 %_10.i686, 4
  %155 = sub nuw nsw i32 632, %154
  br label %bb7.i663

bb8.i677:                                         ; preds = %bb7.i663
  %156 = trunc i64 %d.sroa.0.0.i2201 to i32
  %_22.i678 = add i32 %156, -1
  %_25.1.i679 = icmp ult i32 %_22.i678, 2
  br i1 %_25.1.i679, label %panic5.i683, label %bb12.i680

panic5.i683:                                      ; preds = %bb8.i677
; call core::panicking::panic_const::panic_const_sub_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_9f4d1cf899b26bf5e0e440ccaea53f2f) #13
  unreachable

bb12.i680:                                        ; preds = %bb8.i677
  %_21.i681 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_22.i678, i1 true)
  %157 = shl nuw nsw i32 %_21.i681, 4
  %reass.sub2253 = sub nsw i32 %c.sroa.0.0.i664, %157
  %158 = add nsw i32 %reass.sub2253, 480
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit687

_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit687: ; preds = %bb12.i680, %bb7.i663
  %c.sroa.0.1.i667 = phi i32 [ %158, %bb12.i680 ], [ %c.sroa.0.0.i664, %bb7.i663 ]
  %_29.i668 = trunc nuw nsw i64 %l.sroa.0.0.i2202 to i32
  %_30.0.i671 = shl nuw nsw i32 %_29.i668, 6
  %159 = sub nsw i32 %_30.0.i671, %c.sroa.0.1.i667
  %_62.i = icmp sgt i32 %_31.0.i700, %159
  br i1 %_62.i, label %bb32.i, label %bb63.i

bb32.i:                                           ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit687
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2686)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2689)
  %exitcond.not2834 = icmp eq i64 %nt.sroa.0.5.i2203, %umax2815
  br i1 %exitcond.not2834, label %panic1.i167, label %bb59.i

panic1.i167:                                      ; preds = %bb32.i
  %nt.sroa.0.5.i2203.lcssa2877 = phi i64 [ %nt.sroa.0.5.i2203, %bb32.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %nt.sroa.0.5.i2203.lcssa2877, i64 noundef range(i64 0, 2305843009213693952) %out.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_1e808d4a560d2bfb30193cdd1b6f1f95) #13, !noalias !2691
  unreachable

bb59.i:                                           ; preds = %bb32.i
  %_5.i = load i8, ptr %103, align 1, !alias.scope !2686, !noalias !2689, !noundef !136
  %160 = getelementptr inbounds nuw [4 x i8], ptr %out.0, i64 %nt.sroa.0.5.i2203
  %161 = zext i8 %_5.i to i32
  store i32 %161, ptr %160, align 4, !alias.scope !2689, !noalias !2686
  %_10.0.i169 = add i64 %nt.sroa.0.5.i2203, 1
  %_39.i = icmp ult i64 %k.sroa.0.2.i.lcssa, 64
  %indvars.iv.next2813 = add i64 %indvars.iv2812, -1
  br i1 %_39.i, label %bb18.i, label %bb63.i

bb116.i:                                          ; preds = %bb110.i, %bb63.i
  %p.sroa.0.7.i.lcssa = phi i64 [ %p.sroa.0.5.i.lcssa, %bb63.i ], [ %p.sroa.0.8.i, %bb110.i ]
  %l.sroa.0.2.i.lcssa = phi i64 [ %l.sroa.0.0.i.lcssa, %bb63.i ], [ %l.sroa.0.3.i, %bb110.i ]
  %nt.sroa.0.7.i.lcssa = phi i64 [ %nt.sroa.0.5.i.lcssa, %bb63.i ], [ %nt.sroa.0.8.i, %bb110.i ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2692)
  %_15.i = icmp samesign ult i64 %nt.sroa.0.7.i.lcssa, %out.1
  br i1 %_15.i, label %bb1.i198, label %panic.i197

bb1.i198:                                         ; preds = %bb116.i
  %162 = trunc i64 %l.sroa.0.2.i.lcssa to i32
  %163 = trunc i64 %d.sroa.0.0.i.lcssa to i32
  %_10.i = shl i32 %163, 8
  %_12.i199 = add i32 %_10.i, 16776957
  %_7.i200 = add i32 %_12.i199, %162
  %164 = getelementptr inbounds nuw [4 x i8], ptr %out.0, i64 %nt.sroa.0.7.i.lcssa
  store i32 %_7.i200, ptr %164, align 4, !alias.scope !2692
  %_19.0.i201 = add i64 %l.sroa.0.2.i.lcssa, %p.sroa.0.7.i.lcssa
  %_19.1.i202 = icmp ult i64 %_19.0.i201, %p.sroa.0.7.i.lcssa
  br i1 %_19.1.i202, label %panic2.i204, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse14u118_put_match.exit

panic.i197:                                       ; preds = %bb116.i
  %nt.sroa.0.7.i.lcssa.lcssa = phi i64 [ %nt.sroa.0.7.i.lcssa, %bb116.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef range(i64 0, 2305843009213693952) %nt.sroa.0.7.i.lcssa.lcssa, i64 noundef range(i64 0, 2305843009213693952) %out.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_91bbba7d8bfca8a214cab7fb1cbd8ce3) #13, !noalias !2692
  unreachable

panic2.i204:                                      ; preds = %bb1.i198
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_8c0fdb4f326073e19a6b7eb9b54b4e01) #13, !noalias !2692
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse14u118_put_match.exit: ; preds = %bb1.i198
  %_17.0.i = add nuw nsw i64 %nt.sroa.0.7.i.lcssa, 1
  %_175.i = add nuw i64 %ins.sroa.0.4.i.lcssa, 16
  %spec.select138.i = tail call i64 @llvm.umin.i64(i64 %_19.0.i201, i64 %_175.i)
  %spec.store.select50.i = tail call i64 @llvm.umin.i64(i64 %spec.select138.i, i64 %_8.0.i)
  %_181.i2229 = icmp ult i64 %ins.sroa.0.4.i.lcssa, %spec.store.select50.i
  br i1 %_181.i2229, label %bb125.i, label %bb129.i

bb125.i:                                          ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse14u118_put_match.exit, %bb125.i
  %ins.sroa.0.5.i2230 = phi i64 [ %_188.0.i, %bb125.i ], [ %ins.sroa.0.4.i.lcssa, %_RNvNtCs2hd9JHJjR4I_9candidate5parse14u118_put_match.exit ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2695)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2698)
  %165 = getelementptr inbounds nuw i8, ptr %input.0, i64 %ins.sroa.0.5.i2230
  %166 = load i32, ptr %165, align 1
  %167 = call i32 @llvm.bswap.i32(i32 %166)
  %168 = zext i32 %167 to i64
  %169 = mul i64 %168, -7046029254386353131
  %170 = lshr i64 %169, 48
  %171 = getelementptr inbounds nuw [4 x i8], ptr %head.i, i64 %170
  %old.i145.i = load i32, ptr %171, align 4, !alias.scope !2695, !noalias !2700, !noundef !136
  %_16.i146.i = and i64 %ins.sroa.0.5.i2230, 32767
  %172 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_16.i146.i
  store i32 %old.i145.i, ptr %172, align 4, !alias.scope !2698, !noalias !2702
  %173 = trunc i64 %ins.sroa.0.5.i2230 to i32
  store i32 %173, ptr %171, align 4, !alias.scope !2695, !noalias !2700
  %_188.0.i = add nuw i64 %ins.sroa.0.5.i2230, 1
  %exitcond2395.not = icmp eq i64 %_188.0.i, %spec.store.select50.i
  br i1 %exitcond2395.not, label %bb129.i, label %bb125.i

bb129.i:                                          ; preds = %bb125.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse14u118_put_match.exit
  %ins.sroa.0.5.i.lcssa = phi i64 [ %ins.sroa.0.4.i.lcssa, %_RNvNtCs2hd9JHJjR4I_9candidate5parse14u118_put_match.exit ], [ %spec.store.select50.i, %bb125.i ]
  %e2.i = tail call i64 @llvm.usub.sat.i64(i64 %_19.0.i201, i64 8)
  %invariant.umin = tail call i64 @llvm.umin.i64(i64 %e2.i, i64 %_8.0.i)
  %or.cond51.i2232 = icmp ult i64 %ins.sroa.0.5.i.lcssa, %invariant.umin
  br i1 %or.cond51.i2232, label %bb132.i, label %bb138.i

bb132.i:                                          ; preds = %bb129.i, %bb132.i
  %ins.sroa.0.6.i2233 = phi i64 [ %_5.0.i293, %bb132.i ], [ %ins.sroa.0.5.i.lcssa, %bb129.i ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2703)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2706)
  %_5.0.i293 = add nuw i64 %ins.sroa.0.6.i2233, 4
  %174 = getelementptr inbounds nuw i8, ptr %input.0, i64 %ins.sroa.0.6.i2233
  %175 = load i32, ptr %174, align 1
  %176 = call i32 @llvm.bswap.i32(i32 %175)
  %177 = zext i32 %176 to i64
  %178 = mul i64 %177, -7046029254386353131
  %179 = lshr i64 %178, 48
  %180 = getelementptr inbounds nuw [4 x i8], ptr %head.i, i64 %179
  %old.i152.i = load i32, ptr %180, align 4, !alias.scope !2703, !noalias !2708, !noundef !136
  %_16.i153.i = and i64 %ins.sroa.0.6.i2233, 32767
  %181 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_16.i153.i
  store i32 %old.i152.i, ptr %181, align 4, !alias.scope !2706, !noalias !2710
  %182 = trunc i64 %ins.sroa.0.6.i2233 to i32
  store i32 %182, ptr %180, align 4, !alias.scope !2703, !noalias !2708
  %or.cond51.i = icmp ult i64 %_5.0.i293, %invariant.umin
  br i1 %or.cond51.i, label %bb132.i, label %bb138.i

bb138.i:                                          ; preds = %bb132.i, %bb129.i
  %ins.sroa.0.6.i.lcssa = phi i64 [ %ins.sroa.0.5.i.lcssa, %bb129.i ], [ %_5.0.i293, %bb132.i ]
  %_202.i = add i64 %ins.sroa.0.6.i.lcssa, 4
  %_201.i = icmp ult i64 %_202.i, %_19.0.i201
  br i1 %_201.i, label %bb139.i, label %bb142.i

bb139.i:                                          ; preds = %bb138.i
  %_204.1.i = icmp ult i64 %_19.0.i201, 4
  br i1 %_204.1.i, label %panic18.i, label %bb140.i

bb142.i:                                          ; preds = %bb140.i, %bb138.i
  %ins.sroa.0.7.i = phi i64 [ %_204.0.i, %bb140.i ], [ %ins.sroa.0.6.i.lcssa, %bb138.i ]
  %invariant.umin2235 = tail call i64 @llvm.umin.i64(i64 %_19.0.i201, i64 %_8.0.i)
  %or.cond52.i2236 = icmp ult i64 %ins.sroa.0.7.i, %invariant.umin2235
  br i1 %or.cond52.i2236, label %bb145.i, label %bb150.i

bb140.i:                                          ; preds = %bb139.i
  %_204.0.i = add i64 %_19.0.i201, -4
  br label %bb142.i

panic18.i:                                        ; preds = %bb139.i
; call core::panicking::panic_const::panic_const_sub_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_94a048f0c628dd665e0545a553ca9ebc) #13
  unreachable

bb150.i:                                          ; preds = %bb145.i, %bb142.i
  %ins.sroa.0.8.i.lcssa = phi i64 [ %ins.sroa.0.7.i, %bb142.i ], [ %_213.0.i, %bb145.i ]
  %spec.select140.i = tail call i64 @llvm.umax.i64(i64 %ins.sroa.0.8.i.lcssa, i64 %_19.0.i201)
  br label %bb174.i

bb145.i:                                          ; preds = %bb142.i, %bb145.i
  %ins.sroa.0.8.i2237 = phi i64 [ %_213.0.i, %bb145.i ], [ %ins.sroa.0.7.i, %bb142.i ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2711)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2714)
  %183 = getelementptr inbounds nuw i8, ptr %input.0, i64 %ins.sroa.0.8.i2237
  %184 = load i32, ptr %183, align 1
  %185 = call i32 @llvm.bswap.i32(i32 %184)
  %186 = zext i32 %185 to i64
  %187 = mul i64 %186, -7046029254386353131
  %188 = lshr i64 %187, 48
  %189 = getelementptr inbounds nuw [4 x i8], ptr %head.i, i64 %188
  %old.i159.i = load i32, ptr %189, align 4, !alias.scope !2711, !noalias !2716, !noundef !136
  %_16.i160.i = and i64 %ins.sroa.0.8.i2237, 32767
  %190 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_16.i160.i
  store i32 %old.i159.i, ptr %190, align 4, !alias.scope !2714, !noalias !2718
  %191 = trunc i64 %ins.sroa.0.8.i2237 to i32
  store i32 %191, ptr %189, align 4, !alias.scope !2711, !noalias !2716
  %_213.0.i = add nuw nsw i64 %ins.sroa.0.8.i2237, 1
  %or.cond52.i = icmp ult i64 %_213.0.i, %invariant.umin2235
  br i1 %or.cond52.i, label %bb145.i, label %bb150.i

bb71.i:                                           ; preds = %bb63.i, %bb110.i
  %192 = phi i64 [ %244, %bb110.i ], [ %100, %bb63.i ]
  %nt.sroa.0.7.i2225 = phi i64 [ %nt.sroa.0.8.i, %bb110.i ], [ %nt.sroa.0.5.i.lcssa, %bb63.i ]
  %l.sroa.0.2.i2224 = phi i64 [ %l.sroa.0.3.i, %bb110.i ], [ %l.sroa.0.0.i.lcssa, %bb63.i ]
  %back.sroa.0.0.i2223 = phi i64 [ %back.sroa.0.1.i, %bb110.i ], [ 0, %bb63.i ]
  %p.sroa.0.7.i2222 = phi i64 [ %p.sroa.0.8.i, %bb110.i ], [ %p.sroa.0.5.i.lcssa, %bb63.i ]
  %193 = getelementptr inbounds nuw [4 x i8], ptr %out.0, i64 %192
  %t.i = load i32, ptr %193, align 4, !alias.scope !2602, !noalias !2599, !noundef !136
  %_120.i = icmp ult i32 %t.i, 256
  br i1 %_120.i, label %bb72.i, label %bb84.i

bb84.i:                                           ; preds = %bb71.i
  %_139.i = icmp ugt i32 %t.i, 16777215
  br i1 %_139.i, label %bb87.i, label %bb110.i

bb72.i:                                           ; preds = %bb71.i
  %_125.0.i = add i64 %p.sroa.0.7.i2222, -1
  %_126.i = icmp ult i64 %_125.0.i, %input.1
  br i1 %_126.i, label %bb74.i, label %panic25.i

bb74.i:                                           ; preds = %bb72.i
  %_133.0.i = sub i64 %_125.0.i, %d.sroa.0.0.i.lcssa
  %_134.i = icmp ult i64 %_133.0.i, %input.1
  br i1 %_134.i, label %bb77.i, label %panic28.i

panic25.i:                                        ; preds = %bb72.i
  %_125.0.i.lcssa = phi i64 [ %_125.0.i, %bb72.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_125.0.i.lcssa, i64 noundef range(i64 0, -9223372036854775808) %input.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_1cb241537ee4f281c00fcbb1bef48ab0) #13
  unreachable

bb77.i:                                           ; preds = %bb74.i
  %194 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_125.0.i
  %_122.i = load i8, ptr %194, align 1, !alias.scope !2599, !noalias !2602, !noundef !136
  %195 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_133.0.i
  %_127.i = load i8, ptr %195, align 1, !alias.scope !2599, !noalias !2602, !noundef !136
  %_121.i = icmp eq i8 %_122.i, %_127.i
  br i1 %_121.i, label %bb80.i, label %bb110.i

panic28.i:                                        ; preds = %bb74.i
  %_133.0.i.lcssa = phi i64 [ %_133.0.i, %bb74.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_133.0.i.lcssa, i64 noundef range(i64 0, -9223372036854775808) %input.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_3d3fade205e2688424188b5bbd6c946c) #13
  unreachable

bb87.i:                                           ; preds = %bb84.i
  %_142.i = and i32 %t.i, 255
  %_145.0.i = add nuw nsw i32 %_142.i, 3
  %w.i = zext nneg i32 %_145.0.i to i64
  %_149.0.i = add nuw nsw i64 %l.sroa.0.2.i2224, %w.i
  %_146.i = icmp samesign ult i64 %_149.0.i, 259
  %_150.i = icmp uge i64 %p.sroa.0.7.i2222, %w.i
  %or.cond53.i = select i1 %_146.i, i1 %_150.i, i1 false
  br i1 %or.cond53.i, label %bb90.i, label %bb110.i

bb90.i:                                           ; preds = %bb87.i
  %_156.0.i = sub nuw i64 %p.sroa.0.7.i2222, %w.i
  %_152.not.i = icmp ugt i64 %d.sroa.0.0.i.lcssa, %_156.0.i
  br i1 %_152.not.i, label %bb110.i, label %bb95.i

bb95.i:                                           ; preds = %bb90.i
  %_163.0.i = sub nuw i64 %_156.0.i, %d.sroa.0.0.i.lcssa
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2719)
  %196 = and i64 %w.i, 504
  br label %bb2.i751

bb2.i751:                                         ; preds = %bb95.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i
  %k.sroa.0.0.i7152214 = phi i64 [ 0, %bb95.i ], [ %_11.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i ]
  %_11.0.i = add nuw nsw i64 %k.sroa.0.0.i7152214, 8
  %_8.not.i = icmp samesign ugt i64 %_11.0.i, %w.i
  br i1 %_8.not.i, label %bb15.i716, label %bb4.i753

bb4.i753:                                         ; preds = %bb2.i751
  %_16.0.i = add nuw i64 %k.sroa.0.0.i7152214, %_163.0.i
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2722)
  %_5.1.i172.i = icmp ugt i64 %_16.0.i, -9
  br i1 %_5.1.i172.i, label %panic.i238.i, label %bb1.i173.i

bb15.i716:                                        ; preds = %bb2.i751
  %_23.i717.not = icmp eq i64 %196, %w.i
  br i1 %_23.i717.not, label %bb101.i, label %bb18.i719

bb1.i173.i:                                       ; preds = %bb4.i753
  %_5.0.i174.i = add nuw i64 %_16.0.i, 8
  %_3.not.i175.i = icmp ugt i64 %_5.0.i174.i, %input.1
  br i1 %_3.not.i175.i, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit239.i, label %bb2.i176.i

panic.i238.i:                                     ; preds = %bb4.i753
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_440babfea49fec204c4bfa4556bd23df) #13, !noalias !2725
  unreachable

bb2.i176.i:                                       ; preds = %bb1.i173.i
  %197 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_16.0.i
  %_15.i180.i = load i8, ptr %197, align 1, !alias.scope !2725, !noundef !136
  %_14.i181.i = zext i8 %_15.i180.i to i64
  %_13.i182.i = shl nuw i64 %_14.i181.i, 56
  %198 = getelementptr inbounds nuw i8, ptr %197, i64 1
  %_19.i187.i = load i8, ptr %198, align 1, !alias.scope !2725, !noundef !136
  %_18.i188.i = zext i8 %_19.i187.i to i64
  %_17.i189.i = shl nuw nsw i64 %_18.i188.i, 48
  %_12.i190.i = or disjoint i64 %_17.i189.i, %_13.i182.i
  %199 = getelementptr inbounds nuw i8, ptr %197, i64 2
  %_25.i195.i = load i8, ptr %199, align 1, !alias.scope !2725, !noundef !136
  %_24.i196.i = zext i8 %_25.i195.i to i64
  %_23.i197.i = shl nuw nsw i64 %_24.i196.i, 40
  %_11.i198.i = or disjoint i64 %_12.i190.i, %_23.i197.i
  %200 = getelementptr inbounds nuw i8, ptr %197, i64 3
  %_31.i203.i = load i8, ptr %200, align 1, !alias.scope !2725, !noundef !136
  %_30.i204.i = zext i8 %_31.i203.i to i64
  %_29.i205.i = shl nuw nsw i64 %_30.i204.i, 32
  %_10.i206.i = or disjoint i64 %_11.i198.i, %_29.i205.i
  %201 = getelementptr inbounds nuw i8, ptr %197, i64 4
  %_37.i211.i = load i8, ptr %201, align 1, !alias.scope !2725, !noundef !136
  %_36.i212.i = zext i8 %_37.i211.i to i64
  %_35.i213.i = shl nuw nsw i64 %_36.i212.i, 24
  %_9.i214.i = or disjoint i64 %_10.i206.i, %_35.i213.i
  %202 = getelementptr inbounds nuw i8, ptr %197, i64 5
  %_43.i219.i = load i8, ptr %202, align 1, !alias.scope !2725, !noundef !136
  %_42.i220.i = zext i8 %_43.i219.i to i64
  %_41.i221.i = shl nuw nsw i64 %_42.i220.i, 16
  %_8.i222.i = or disjoint i64 %_9.i214.i, %_41.i221.i
  %203 = getelementptr inbounds nuw i8, ptr %197, i64 6
  %_49.i227.i = load i8, ptr %203, align 1, !alias.scope !2725, !noundef !136
  %_48.i228.i = zext i8 %_49.i227.i to i64
  %_47.i229.i = shl nuw nsw i64 %_48.i228.i, 8
  %_7.i230.i = or i64 %_8.i222.i, %_47.i229.i
  %204 = getelementptr inbounds nuw i8, ptr %197, i64 7
  %_54.i235.i = load i8, ptr %204, align 1, !alias.scope !2725, !noundef !136
  %_53.i236.i = zext i8 %_54.i235.i to i64
  %205 = or i64 %_7.i230.i, %_53.i236.i
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit239.i

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit239.i: ; preds = %bb2.i176.i, %bb1.i173.i
  %_0.sroa.0.0.i237.i = phi i64 [ %205, %bb2.i176.i ], [ 0, %bb1.i173.i ]
  %_20.0.i = add nuw i64 %k.sroa.0.0.i7152214, %_156.0.i
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2726)
  %_5.1.i104.i = icmp ugt i64 %_20.0.i, -9
  br i1 %_5.1.i104.i, label %panic.i170.i, label %bb1.i105.i

bb1.i105.i:                                       ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit239.i
  %_5.0.i106.i = add nuw i64 %_20.0.i, 8
  %_3.not.i107.i = icmp ugt i64 %_5.0.i106.i, %input.1
  br i1 %_3.not.i107.i, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i, label %bb2.i108.i

panic.i170.i:                                     ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit239.i
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_440babfea49fec204c4bfa4556bd23df) #13, !noalias !2729
  unreachable

bb2.i108.i:                                       ; preds = %bb1.i105.i
  %206 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_20.0.i
  %_15.i112.i = load i8, ptr %206, align 1, !alias.scope !2729, !noundef !136
  %_14.i113.i = zext i8 %_15.i112.i to i64
  %_13.i114.i = shl nuw i64 %_14.i113.i, 56
  %207 = getelementptr inbounds nuw i8, ptr %206, i64 1
  %_19.i119.i = load i8, ptr %207, align 1, !alias.scope !2729, !noundef !136
  %_18.i120.i = zext i8 %_19.i119.i to i64
  %_17.i121.i = shl nuw nsw i64 %_18.i120.i, 48
  %_12.i122.i = or disjoint i64 %_17.i121.i, %_13.i114.i
  %208 = getelementptr inbounds nuw i8, ptr %206, i64 2
  %_25.i127.i = load i8, ptr %208, align 1, !alias.scope !2729, !noundef !136
  %_24.i128.i = zext i8 %_25.i127.i to i64
  %_23.i129.i = shl nuw nsw i64 %_24.i128.i, 40
  %_11.i130.i = or disjoint i64 %_12.i122.i, %_23.i129.i
  %209 = getelementptr inbounds nuw i8, ptr %206, i64 3
  %_31.i135.i = load i8, ptr %209, align 1, !alias.scope !2729, !noundef !136
  %_30.i136.i = zext i8 %_31.i135.i to i64
  %_29.i137.i = shl nuw nsw i64 %_30.i136.i, 32
  %_10.i138.i = or disjoint i64 %_11.i130.i, %_29.i137.i
  %210 = getelementptr inbounds nuw i8, ptr %206, i64 4
  %_37.i143.i = load i8, ptr %210, align 1, !alias.scope !2729, !noundef !136
  %_36.i144.i = zext i8 %_37.i143.i to i64
  %_35.i145.i = shl nuw nsw i64 %_36.i144.i, 24
  %_9.i146.i = or disjoint i64 %_10.i138.i, %_35.i145.i
  %211 = getelementptr inbounds nuw i8, ptr %206, i64 5
  %_43.i151.i = load i8, ptr %211, align 1, !alias.scope !2729, !noundef !136
  %_42.i152.i = zext i8 %_43.i151.i to i64
  %_41.i153.i = shl nuw nsw i64 %_42.i152.i, 16
  %_8.i154.i = or disjoint i64 %_9.i146.i, %_41.i153.i
  %212 = getelementptr inbounds nuw i8, ptr %206, i64 6
  %_49.i159.i = load i8, ptr %212, align 1, !alias.scope !2729, !noundef !136
  %_48.i160.i = zext i8 %_49.i159.i to i64
  %_47.i161.i = shl nuw nsw i64 %_48.i160.i, 8
  %_7.i162.i = or i64 %_8.i154.i, %_47.i161.i
  %213 = getelementptr inbounds nuw i8, ptr %206, i64 7
  %_54.i167.i = load i8, ptr %213, align 1, !alias.scope !2729, !noundef !136
  %_53.i168.i = zext i8 %_54.i167.i to i64
  %214 = or i64 %_7.i162.i, %_53.i168.i
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i: ; preds = %bb2.i108.i, %bb1.i105.i
  %_0.sroa.0.0.i169.i = phi i64 [ %214, %bb2.i108.i ], [ 0, %bb1.i105.i ]
  %_12.i.not = icmp eq i64 %_0.sroa.0.0.i237.i, %_0.sroa.0.0.i169.i
  br i1 %_12.i.not, label %bb2.i751, label %bb110.i

bb18.i719:                                        ; preds = %bb15.i716
  %_29.0.i720 = add i64 %196, %_163.0.i
  %_29.1.i = icmp ult i64 %_29.0.i720, %_163.0.i
  br i1 %_29.1.i, label %panic4.i750, label %bb19.i721

bb19.i721:                                        ; preds = %bb18.i719
  %_30.1.i722 = icmp ugt i64 %_29.0.i720, -9
  br i1 %_30.1.i722, label %panic5.i749, label %bb20.i723

panic4.i750:                                      ; preds = %bb18.i719
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_5988a9c474509aa3e7e55969f6ad663e) #13, !noalias !2719
  unreachable

bb20.i723:                                        ; preds = %bb19.i721
  %_30.0.i724 = add nuw i64 %_29.0.i720, 8
  %_25.not.i = icmp ugt i64 %_30.0.i724, %input.1
  br i1 %_25.not.i, label %bb40.i.preheader, label %bb21.i725

bb40.i.preheader:                                 ; preds = %bb23.i727, %bb20.i723
  br label %bb40.i

panic5.i749:                                      ; preds = %bb19.i721
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_5988a9c474509aa3e7e55969f6ad663e) #13, !noalias !2719
  unreachable

bb21.i725:                                        ; preds = %bb20.i723
  %_35.0.i = add i64 %196, %_156.0.i
  %_35.1.i = icmp ult i64 %_35.0.i, %_156.0.i
  br i1 %_35.1.i, label %panic6.i748, label %bb22.i726

bb22.i726:                                        ; preds = %bb21.i725
  %_36.1.i = icmp ugt i64 %_35.0.i, -9
  br i1 %_36.1.i, label %panic7.i747, label %bb23.i727

panic6.i748:                                      ; preds = %bb21.i725
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_c2b01cdce33609a4161805adc289533f) #13, !noalias !2719
  unreachable

bb23.i727:                                        ; preds = %bb22.i726
  %_36.0.i = add nuw i64 %_35.0.i, 8
  %_31.not.i = icmp ugt i64 %_36.0.i, %input.1
  br i1 %_31.not.i, label %bb40.i.preheader, label %bb30.i

panic7.i747:                                      ; preds = %bb22.i726
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_c2b01cdce33609a4161805adc289533f) #13, !noalias !2719
  unreachable

bb40.i:                                           ; preds = %bb40.i.preheader, %bb44.i
  %k.sroa.0.2.i7412216 = phi i64 [ %k.sroa.0.3.i745, %bb44.i ], [ %196, %bb40.i.preheader ]
  %_62.0.i = add i64 %k.sroa.0.2.i7412216, %_163.0.i
  %_62.1.i = icmp ult i64 %_62.0.i, %_163.0.i
  br i1 %_62.1.i, label %panic8.i746, label %bb41.i

bb41.i:                                           ; preds = %bb40.i
  %_63.i = icmp ult i64 %_62.0.i, %input.1
  br i1 %_63.i, label %bb42.i, label %panic9.i742

panic8.i746:                                      ; preds = %bb40.i
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_ec9880852f5ad0b7f675c971d025b4ff) #13, !noalias !2719
  unreachable

bb42.i:                                           ; preds = %bb41.i
  %215 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_62.0.i
  %_59.i = load i8, ptr %215, align 1, !alias.scope !2719, !noundef !136
  %_67.0.i = add i64 %k.sroa.0.2.i7412216, %_156.0.i
  %_67.1.i = icmp ult i64 %_67.0.i, %_156.0.i
  br i1 %_67.1.i, label %panic10.i, label %bb43.i

panic9.i742:                                      ; preds = %bb41.i
  %_62.0.i.lcssa2878 = phi i64 [ %_62.0.i, %bb41.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_62.0.i.lcssa2878, i64 noundef range(i64 0, -9223372036854775808) %input.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_c867e779aaf632c8ba08807d62f697ee) #13, !noalias !2719
  unreachable

bb43.i:                                           ; preds = %bb42.i
  %_68.i = icmp ult i64 %_67.0.i, %input.1
  br i1 %_68.i, label %bb44.i, label %panic11.i743

panic10.i:                                        ; preds = %bb42.i
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_f89fc433b2ec5f525912d54366fd14b2) #13, !noalias !2719
  unreachable

bb44.i:                                           ; preds = %bb43.i
  %216 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_67.0.i
  %_64.i = load i8, ptr %216, align 1, !alias.scope !2719, !noundef !136
  %_58.i744 = icmp eq i8 %_59.i, %_64.i
  %_69.0.i = zext i1 %_58.i744 to i64
  %k.sroa.0.3.i745 = add nuw nsw i64 %k.sroa.0.2.i7412216, %_69.0.i
  %_56.i = icmp samesign ult i64 %k.sroa.0.3.i745, %w.i
  %or.cond19.i = select i1 %_58.i744, i1 %_56.i, i1 false
  br i1 %or.cond19.i, label %bb40.i, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit

panic11.i743:                                     ; preds = %bb43.i
  %_67.0.i.lcssa2882 = phi i64 [ %_67.0.i, %bb43.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_67.0.i.lcssa2882, i64 noundef range(i64 0, -9223372036854775808) %input.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_f7486e32a26ebd3f0532d14c194cbf09) #13, !noalias !2719
  unreachable

bb30.i:                                           ; preds = %bb23.i727
  %_51.0.i732 = shl nuw nsw i32 %_145.0.i, 3
  %217 = and i32 %_51.0.i732, 56
  %_54.i735.not = icmp eq i32 %217, 0
  br i1 %_54.i735.not, label %panic18.i736, label %bb32.i737

bb32.i737:                                        ; preds = %bb30.i
  %_53.0.i = sub nuw nsw i32 64, %217
  %218 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_35.0.i
  %219 = getelementptr inbounds nuw i8, ptr %218, i64 1
  %_19.i.i = load i8, ptr %219, align 1, !alias.scope !2730, !noundef !136
  %_18.i.i = zext i8 %_19.i.i to i64
  %_17.i.i = shl nuw nsw i64 %_18.i.i, 48
  %_15.i.i = load i8, ptr %218, align 1, !alias.scope !2730, !noundef !136
  %_14.i.i = zext i8 %_15.i.i to i64
  %_13.i.i = shl nuw i64 %_14.i.i, 56
  %_12.i.i729 = or disjoint i64 %_17.i.i, %_13.i.i
  %220 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_35.0.i
  %221 = getelementptr inbounds nuw i8, ptr %220, i64 2
  %_25.i.i = load i8, ptr %221, align 1, !alias.scope !2730, !noundef !136
  %_24.i.i = zext i8 %_25.i.i to i64
  %_23.i.i = shl nuw nsw i64 %_24.i.i, 40
  %_11.i.i730 = or disjoint i64 %_12.i.i729, %_23.i.i
  %222 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_35.0.i
  %223 = getelementptr inbounds nuw i8, ptr %222, i64 3
  %_31.i.i = load i8, ptr %223, align 1, !alias.scope !2730, !noundef !136
  %_30.i.i = zext i8 %_31.i.i to i64
  %_29.i.i = shl nuw nsw i64 %_30.i.i, 32
  %_10.i.i = or disjoint i64 %_11.i.i730, %_29.i.i
  %224 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_35.0.i
  %225 = getelementptr inbounds nuw i8, ptr %224, i64 4
  %_37.i.i = load i8, ptr %225, align 1, !alias.scope !2730, !noundef !136
  %_36.i.i = zext i8 %_37.i.i to i64
  %_35.i.i = shl nuw nsw i64 %_36.i.i, 24
  %_9.i.i = or disjoint i64 %_10.i.i, %_35.i.i
  %226 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_35.0.i
  %227 = getelementptr inbounds nuw i8, ptr %226, i64 5
  %_43.i.i = load i8, ptr %227, align 1, !alias.scope !2730, !noundef !136
  %_42.i.i = zext i8 %_43.i.i to i64
  %_41.i.i = shl nuw nsw i64 %_42.i.i, 16
  %_8.i.i = or disjoint i64 %_9.i.i, %_41.i.i
  %228 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_35.0.i
  %229 = getelementptr inbounds nuw i8, ptr %228, i64 6
  %_49.i.i = load i8, ptr %229, align 1, !alias.scope !2730, !noundef !136
  %_48.i.i = zext i8 %_49.i.i to i64
  %_47.i.i = shl nuw nsw i64 %_48.i.i, 8
  %_7.i.i = or i64 %_8.i.i, %_47.i.i
  %230 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_35.0.i
  %231 = getelementptr inbounds nuw i8, ptr %230, i64 7
  %_54.i.i = load i8, ptr %231, align 1, !alias.scope !2730, !noundef !136
  %_53.i.i = zext i8 %_54.i.i to i64
  %232 = or i64 %_7.i.i, %_53.i.i
  %233 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_29.0.i720
  %234 = getelementptr inbounds nuw i8, ptr %233, i64 1
  %_19.i51.i = load i8, ptr %234, align 1, !alias.scope !2733, !noundef !136
  %_18.i52.i = zext i8 %_19.i51.i to i64
  %_17.i53.i = shl nuw nsw i64 %_18.i52.i, 48
  %_15.i44.i = load i8, ptr %233, align 1, !alias.scope !2733, !noundef !136
  %_14.i45.i = zext i8 %_15.i44.i to i64
  %_13.i46.i = shl nuw i64 %_14.i45.i, 56
  %_12.i54.i = or disjoint i64 %_17.i53.i, %_13.i46.i
  %235 = getelementptr inbounds nuw i8, ptr %233, i64 2
  %_25.i59.i = load i8, ptr %235, align 1, !alias.scope !2733, !noundef !136
  %_24.i60.i = zext i8 %_25.i59.i to i64
  %_23.i61.i = shl nuw nsw i64 %_24.i60.i, 40
  %_11.i62.i = or disjoint i64 %_12.i54.i, %_23.i61.i
  %236 = getelementptr inbounds nuw i8, ptr %233, i64 3
  %_31.i67.i = load i8, ptr %236, align 1, !alias.scope !2733, !noundef !136
  %_30.i68.i = zext i8 %_31.i67.i to i64
  %_29.i69.i = shl nuw nsw i64 %_30.i68.i, 32
  %_10.i70.i = or disjoint i64 %_11.i62.i, %_29.i69.i
  %237 = getelementptr inbounds nuw i8, ptr %233, i64 4
  %_37.i75.i = load i8, ptr %237, align 1, !alias.scope !2733, !noundef !136
  %_36.i76.i = zext i8 %_37.i75.i to i64
  %_35.i77.i = shl nuw nsw i64 %_36.i76.i, 24
  %_9.i78.i = or disjoint i64 %_10.i70.i, %_35.i77.i
  %238 = getelementptr inbounds nuw i8, ptr %233, i64 5
  %_43.i83.i = load i8, ptr %238, align 1, !alias.scope !2733, !noundef !136
  %_42.i84.i = zext i8 %_43.i83.i to i64
  %_41.i85.i = shl nuw nsw i64 %_42.i84.i, 16
  %_8.i86.i = or disjoint i64 %_9.i78.i, %_41.i85.i
  %239 = getelementptr inbounds nuw i8, ptr %233, i64 6
  %_49.i91.i = load i8, ptr %239, align 1, !alias.scope !2733, !noundef !136
  %_48.i92.i = zext i8 %_49.i91.i to i64
  %_47.i93.i = shl nuw nsw i64 %_48.i92.i, 8
  %_7.i94.i = or i64 %_8.i86.i, %_47.i93.i
  %240 = getelementptr inbounds nuw i8, ptr %233, i64 7
  %_54.i99.i = load i8, ptr %240, align 1, !alias.scope !2733, !noundef !136
  %_53.i100.i = zext i8 %_54.i99.i to i64
  %241 = or i64 %_7.i94.i, %_53.i100.i
  %x.i731 = xor i64 %232, %241
  %242 = zext nneg i32 %_53.0.i to i64
  %_46.i738 = lshr i64 %x.i731, %242
  %243 = icmp eq i64 %_46.i738, 0
  br i1 %243, label %bb101.i, label %bb110.i

panic18.i736:                                     ; preds = %bb30.i
; call core::panicking::panic_const::panic_const_shr_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_shr_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_0471675f9abe1475b1e41b49769421c8) #13, !noalias !2719
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit: ; preds = %bb44.i
  br i1 %_58.i744, label %bb101.i, label %bb110.i

bb101.i:                                          ; preds = %bb32.i737, %bb15.i716, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit
  %_170.0.i = add nuw nsw i64 %back.sroa.0.0.i2223, 1
  br label %bb110.i

bb110.i:                                          ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i, %bb32.i737, %bb77.i, %bb80.i, %bb101.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit, %bb90.i, %bb87.i, %bb84.i
  %p.sroa.0.8.i = phi i64 [ %_125.0.i, %bb80.i ], [ %_156.0.i, %bb101.i ], [ %p.sroa.0.7.i2222, %bb84.i ], [ %p.sroa.0.7.i2222, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit ], [ %p.sroa.0.7.i2222, %bb90.i ], [ %p.sroa.0.7.i2222, %bb87.i ], [ %p.sroa.0.7.i2222, %bb77.i ], [ %p.sroa.0.7.i2222, %bb32.i737 ], [ %p.sroa.0.7.i2222, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i ]
  %back.sroa.0.1.i = phi i64 [ %_138.0.i, %bb80.i ], [ %_170.0.i, %bb101.i ], [ 16, %bb84.i ], [ 16, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit ], [ 16, %bb90.i ], [ 16, %bb87.i ], [ 16, %bb77.i ], [ 16, %bb32.i737 ], [ 16, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i ]
  %l.sroa.0.3.i = phi i64 [ %_137.0.i, %bb80.i ], [ %_149.0.i, %bb101.i ], [ %l.sroa.0.2.i2224, %bb84.i ], [ %l.sroa.0.2.i2224, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit ], [ %l.sroa.0.2.i2224, %bb90.i ], [ %l.sroa.0.2.i2224, %bb87.i ], [ %l.sroa.0.2.i2224, %bb77.i ], [ %l.sroa.0.2.i2224, %bb32.i737 ], [ %l.sroa.0.2.i2224, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i ]
  %nt.sroa.0.8.i = phi i64 [ %192, %bb80.i ], [ %192, %bb101.i ], [ %nt.sroa.0.7.i2225, %bb84.i ], [ %nt.sroa.0.7.i2225, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit ], [ %nt.sroa.0.7.i2225, %bb90.i ], [ %nt.sroa.0.7.i2225, %bb87.i ], [ %nt.sroa.0.7.i2225, %bb77.i ], [ %nt.sroa.0.7.i2225, %bb32.i737 ], [ %nt.sroa.0.7.i2225, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i ]
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
  %_137.0.i = add nuw nsw i64 %l.sroa.0.2.i2224, 1
  %_138.0.i = add nuw nsw i64 %back.sroa.0.0.i2223, 1
  br label %bb110.i

_RINvNtCs2hd9JHJjR4I_9candidate5parse8u118_runKj10000_Kj8000_Kmffffffff_Kj4_Kjc_Kj40_Kj6_Kjf4240_Kj80_Kj1_Kj10_KB18_Kl40_Kj0_EB4_.exit: ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit196, %bb178.i
  %nt.sroa.0.2.i.lcssa = phi i64 [ %nt.sroa.0.0.i, %bb178.i ], [ %_10.0.i195, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit196 ]
  ret i64 %nt.sroa.0.2.i.lcssa
}