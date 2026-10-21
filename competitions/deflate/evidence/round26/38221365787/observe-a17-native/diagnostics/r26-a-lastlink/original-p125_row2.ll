define internal fastcc noundef range(i64 0, 2305843009213693952) i64 @_RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row2(ptr noalias nofree noundef nonnull readonly captures(address, read_provenance) %input.0, ptr noalias nofree noundef nonnull align 4 captures(none) %out.0, i64 noundef range(i64 0, 2305843009213693952) %out.1) unnamed_addr #0 !guid !1557 {
bb5.i.preheader:
  %prev.i = alloca [131072 x i8], align 4
  %head.i = alloca [262144 x i8], align 4
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1558)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1561)
  call void @llvm.lifetime.start.p0(ptr nonnull %head.i), !noalias !1563
  call void @llvm.memset.p0.i64(ptr noundef nonnull align 4 dereferenceable(262144) %head.i, i8 0, i64 262144, i1 false), !noalias !1563
  call void @llvm.lifetime.start.p0(ptr nonnull %prev.i), !noalias !1563
  call void @llvm.memset.p0.i64(ptr noundef nonnull align 4 dereferenceable(131072) %prev.i, i8 0, i64 131072, i1 false), !noalias !1563
  br label %bb5.i

bb178.i:                                          ; preds = %bb174.i
  %p.sroa.0.4.i.lcssa = phi i64 [ %p.sroa.0.4.i, %bb174.i ]
  %nt.sroa.0.4.i.lcssa = phi i64 [ %nt.sroa.0.4.i, %bb174.i ]
  call void @llvm.lifetime.end.p0(ptr nonnull %prev.i), !noalias !1563
  call void @llvm.lifetime.end.p0(ptr nonnull %head.i), !noalias !1563
  %_237.i3250 = icmp ult i64 %p.sroa.0.4.i.lcssa, 500000
  br i1 %_237.i3250, label %bb1.i336.preheader, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse8u118_runKj10000_Kj8000_Kmffffffff_Kj4_Kj6_Kj20_Kj5_Kjf4240_Kj40_Kj1_Kj10_KB18_Kl40_KB1C_EB4_.exit

bb1.i336.preheader:                               ; preds = %bb178.i
  %umax = tail call i64 @llvm.umax.i64(i64 %nt.sroa.0.4.i.lcssa, i64 %out.1)
  %0 = sub i64 %umax, %nt.sroa.0.4.i.lcssa
  %1 = sub nuw nsw i64 499999, %p.sroa.0.4.i.lcssa
  %2 = call i64 @llvm.umin.i64(i64 %0, i64 %1)
  %min.iters.check310 = icmp samesign ult i64 %2, 8
  br i1 %min.iters.check310, label %bb1.i336.preheader336, label %vector.ph311

bb1.i336.preheader336:                            ; preds = %vector.body314, %bb1.i336.preheader
  %nt.sroa.0.2.i3252.ph = phi i64 [ %nt.sroa.0.4.i.lcssa, %bb1.i336.preheader ], [ %6, %vector.body314 ]
  %p.sroa.0.2.i3251.ph = phi i64 [ %p.sroa.0.4.i.lcssa, %bb1.i336.preheader ], [ %7, %vector.body314 ]
  br label %bb1.i336

vector.ph311:                                     ; preds = %bb1.i336.preheader
  %3 = add nuw nsw i64 %2, 1
  %n.mod.vf312 = and i64 %3, 7
  %4 = icmp eq i64 %n.mod.vf312, 0
  %5 = select i1 %4, i64 8, i64 %n.mod.vf312
  %n.vec313 = sub nuw nsw i64 %3, %5
  %6 = add i64 %nt.sroa.0.4.i.lcssa, %n.vec313
  %7 = add nuw nsw i64 %p.sroa.0.4.i.lcssa, %n.vec313
  %8 = getelementptr i8, ptr %input.0, i64 %p.sroa.0.4.i.lcssa
  %9 = getelementptr [4 x i8], ptr %out.0, i64 %nt.sroa.0.4.i.lcssa
  br label %vector.body314

vector.body314:                                   ; preds = %vector.body314, %vector.ph311
  %index315 = phi i64 [ 0, %vector.ph311 ], [ %index.next318, %vector.body314 ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1564)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1567)
  %10 = getelementptr i8, ptr %8, i64 %index315
  %11 = getelementptr inbounds nuw i8, ptr %10, i64 4
  %wide.load316 = load <4 x i8>, ptr %10, align 1, !alias.scope !1564, !noalias !1567
  %wide.load317 = load <4 x i8>, ptr %11, align 1, !alias.scope !1564, !noalias !1567
  %12 = getelementptr [4 x i8], ptr %9, i64 %index315
  %13 = zext <4 x i8> %wide.load316 to <4 x i32>
  %14 = zext <4 x i8> %wide.load317 to <4 x i32>
  %15 = getelementptr inbounds nuw i8, ptr %12, i64 16
  store <4 x i32> %13, ptr %12, align 4, !alias.scope !1567, !noalias !1564
  store <4 x i32> %14, ptr %15, align 4, !alias.scope !1567, !noalias !1564
  %index.next318 = add nuw i64 %index315, 8
  %16 = icmp eq i64 %index.next318, %n.vec313
  br i1 %16, label %bb1.i336.preheader336, label %vector.body314, !llvm.loop !1569

bb5.i:                                            ; preds = %bb5.i.preheader, %bb174.i
  %nt.sroa.0.1.i3247 = phi i64 [ %nt.sroa.0.4.i, %bb174.i ], [ 0, %bb5.i.preheader ]
  %miss.sroa.0.0.i3246 = phi i64 [ %miss.sroa.0.1.i, %bb174.i ], [ 0, %bb5.i.preheader ]
  %fuel.sroa.0.0.i3245 = phi i64 [ %_15.0.i, %bb174.i ], [ 500016, %bb5.i.preheader ]
  %p.sroa.0.1.i3244 = phi i64 [ %p.sroa.0.4.i, %bb174.i ], [ 0, %bb5.i.preheader ]
  %ins.sroa.0.0.i3243 = phi i64 [ %ins.sroa.0.3.i, %bb174.i ], [ 0, %bb5.i.preheader ]
  %p.sroa.0.1.i3244.fr = freeze i64 %p.sroa.0.1.i3244
  %_15.0.i = add nsw i64 %fuel.sroa.0.0.i3245, -1
  %_16.i3153 = icmp ult i64 %ins.sroa.0.0.i3243, %p.sroa.0.1.i3244.fr
  br i1 %_16.i3153, label %bb8.i, label %bb11.i

bb1.i336:                                         ; preds = %bb1.i336.preheader336, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit342
  %nt.sroa.0.2.i3252 = phi i64 [ %_10.0.i341, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit342 ], [ %nt.sroa.0.2.i3252.ph, %bb1.i336.preheader336 ]
  %p.sroa.0.2.i3251 = phi i64 [ %_241.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit342 ], [ %p.sroa.0.2.i3251.ph, %bb1.i336.preheader336 ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1564)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1567)
  %exitcond3446.not = icmp eq i64 %nt.sroa.0.2.i3252, %umax
  br i1 %exitcond3446.not, label %panic1.i338, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit342

panic1.i338:                                      ; preds = %bb1.i336
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %umax, i64 noundef range(i64 0, 2305843009213693952) %out.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_f5cc78c6143d87a95e73f58df7e9bb32) #13, !noalias !1570
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit342: ; preds = %bb1.i336
  %17 = getelementptr inbounds nuw i8, ptr %input.0, i64 %p.sroa.0.2.i3251
  %_5.i340 = load i8, ptr %17, align 1, !alias.scope !1564, !noalias !1567, !noundef !136
  %18 = getelementptr inbounds nuw [4 x i8], ptr %out.0, i64 %nt.sroa.0.2.i3252
  %19 = zext i8 %_5.i340 to i32
  store i32 %19, ptr %18, align 4, !alias.scope !1567, !noalias !1564
  %_10.0.i341 = add i64 %nt.sroa.0.2.i3252, 1
  %_241.0.i = add nuw nsw i64 %p.sroa.0.2.i3251, 1
  %exitcond3447.not = icmp eq i64 %_241.0.i, 500000
  br i1 %exitcond3447.not, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse8u118_runKj10000_Kj8000_Kmffffffff_Kj4_Kj6_Kj20_Kj5_Kjf4240_Kj40_Kj1_Kj10_KB18_Kl40_KB1C_EB4_.exit, label %bb1.i336, !llvm.loop !1571

bb11.i:                                           ; preds = %bb8.i, %bb5.i
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1572)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1575)
  %20 = getelementptr inbounds nuw i8, ptr %input.0, i64 %p.sroa.0.1.i3244.fr
  %21 = load <4 x i8>, ptr %20, align 1, !alias.scope !1577, !noalias !1580
  %22 = bitcast <4 x i8> %21 to i32
  %23 = call i32 @llvm.bswap.i32(i32 %22)
  %24 = zext i32 %23 to i64
  %25 = mul i64 %24, -7046029254386353131
  %26 = lshr i64 %25, 48
  %27 = getelementptr inbounds nuw [4 x i8], ptr %head.i, i64 %26
  %old.i190.i = load i32, ptr %27, align 4, !alias.scope !1572, !noalias !1581, !noundef !136
  %_16.i191.i = and i64 %p.sroa.0.1.i3244.fr, 32767
  %28 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_16.i191.i
  store i32 %old.i190.i, ptr %28, align 4, !alias.scope !1575, !noalias !1583
  %29 = trunc i64 %p.sroa.0.1.i3244.fr to i32
  store i32 %29, ptr %27, align 4, !alias.scope !1572, !noalias !1581
  %_0.i192.i = zext i32 %old.i190.i to i64
  %_29.0.i = add nuw nsw i64 %p.sroa.0.1.i3244.fr, 1
  %_13.0.i20 = sub i64 500000, %p.sroa.0.1.i3244.fr
  %spec.store.select3.i21 = tail call i64 @llvm.umin.i64(i64 %_13.0.i20, i64 258)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1584)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1587)
  %spec.store.select.i27 = tail call i64 @llvm.umin.i64(i64 %_13.0.i20, i64 64)
  %30 = and i64 %spec.store.select3.i21, 504
  %31 = extractelement <4 x i8> %21, i64 3
  %_26.i2423157.not = icmp eq i64 %30, %spec.store.select3.i21
  br label %bb11.i29

bb11.i29:                                         ; preds = %bb37.i, %bb11.i
  %start1.sroa.0.0.i3164 = phi i64 [ %_0.i192.i, %bb11.i ], [ %nx.i, %bb37.i ]
  %have.sroa.0.0.i3163 = phi i64 [ 3, %bb11.i ], [ %have.sroa.0.2.i, %bb37.i ]
  %depth.sroa.0.0.i3162 = phi i64 [ 6, %bb11.i ], [ %_66.0.i, %bb37.i ]
  %bd.sroa.0.0.i3161 = phi i64 [ 0, %bb11.i ], [ %bd.sroa.0.2.i, %bb37.i ]
  %pb.sroa.0.1.i3160 = phi i8 [ %31, %bb11.i ], [ %pb.sroa.0.3.i, %bb37.i ]
  %d.i = sub nsw i64 %p.sroa.0.1.i3244.fr, %start1.sroa.0.0.i3164
  %_29.i = add nsw i64 %d.i, -1
  %_28.i = icmp ult i64 %_29.i, 32768
  br i1 %_28.i, label %bb13.i, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit

bb13.i:                                           ; preds = %bb11.i29
  %_34.0.i = add nuw nsw i64 %start1.sroa.0.0.i3164, %have.sroa.0.0.i3163
  %_30.i = icmp ult i64 %_34.0.i, 500000
  br i1 %_30.i, label %bb16.i31, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit

bb16.i31:                                         ; preds = %bb13.i
  %32 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_34.0.i
  %_36.i = load i8, ptr %32, align 1, !alias.scope !1584, !noalias !1587, !noundef !136
  %_35.i32 = icmp eq i8 %_36.i, %pb.sroa.0.1.i3160
  br i1 %_35.i32, label %bb2.i266, label %bb37.i

bb2.i266:                                         ; preds = %bb16.i31, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit
  %k.sroa.0.0.i2373156 = phi i64 [ %_10.0.i267, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit ], [ 0, %bb16.i31 ]
  %_10.0.i267 = add nuw nsw i64 %k.sroa.0.0.i2373156, 8
  %_7.not.i270 = icmp samesign ugt i64 %_10.0.i267, %spec.store.select3.i21
  br i1 %_7.not.i270, label %bb17.i238, label %bb4.i271

bb4.i271:                                         ; preds = %bb2.i266
  %_15.0.i272 = add nuw nsw i64 %k.sroa.0.0.i2373156, %start1.sroa.0.0.i3164
  %33 = icmp samesign ugt i64 %_15.0.i272, 499992
  br i1 %33, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit688, label %bb2.i624

bb17.i238:                                        ; preds = %bb2.i266
  br i1 %_26.i2423157.not, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit292, label %bb21.i248

bb2.i624:                                         ; preds = %bb4.i271
  %34 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_15.0.i272
  %_15.i628 = load i8, ptr %34, align 1, !alias.scope !1589, !noalias !1587, !noundef !136
  %_14.i629 = zext i8 %_15.i628 to i64
  %_13.i630 = shl nuw i64 %_14.i629, 56
  %35 = getelementptr inbounds nuw i8, ptr %34, i64 1
  %_19.i635 = load i8, ptr %35, align 1, !alias.scope !1589, !noalias !1587, !noundef !136
  %_18.i636 = zext i8 %_19.i635 to i64
  %_17.i637 = shl nuw nsw i64 %_18.i636, 48
  %_12.i638 = or disjoint i64 %_17.i637, %_13.i630
  %36 = getelementptr inbounds nuw i8, ptr %34, i64 2
  %_25.i643 = load i8, ptr %36, align 1, !alias.scope !1589, !noalias !1587, !noundef !136
  %_24.i644 = zext i8 %_25.i643 to i64
  %_23.i645 = shl nuw nsw i64 %_24.i644, 40
  %_11.i646 = or disjoint i64 %_12.i638, %_23.i645
  %37 = getelementptr inbounds nuw i8, ptr %34, i64 3
  %_31.i651 = load i8, ptr %37, align 1, !alias.scope !1589, !noalias !1587, !noundef !136
  %_30.i652 = zext i8 %_31.i651 to i64
  %_29.i653 = shl nuw nsw i64 %_30.i652, 32
  %_10.i654 = or disjoint i64 %_11.i646, %_29.i653
  %38 = getelementptr inbounds nuw i8, ptr %34, i64 4
  %_37.i659 = load i8, ptr %38, align 1, !alias.scope !1589, !noalias !1587, !noundef !136
  %_36.i660 = zext i8 %_37.i659 to i64
  %_35.i661 = shl nuw nsw i64 %_36.i660, 24
  %_9.i662 = or disjoint i64 %_10.i654, %_35.i661
  %39 = getelementptr inbounds nuw i8, ptr %34, i64 5
  %_43.i667 = load i8, ptr %39, align 1, !alias.scope !1589, !noalias !1587, !noundef !136
  %_42.i668 = zext i8 %_43.i667 to i64
  %_41.i669 = shl nuw nsw i64 %_42.i668, 16
  %_8.i670 = or disjoint i64 %_9.i662, %_41.i669
  %40 = getelementptr inbounds nuw i8, ptr %34, i64 6
  %_49.i675 = load i8, ptr %40, align 1, !alias.scope !1589, !noalias !1587, !noundef !136
  %_48.i676 = zext i8 %_49.i675 to i64
  %_47.i677 = shl nuw nsw i64 %_48.i676, 8
  %_7.i678 = or i64 %_8.i670, %_47.i677
  %41 = getelementptr inbounds nuw i8, ptr %34, i64 7
  %_54.i683 = load i8, ptr %41, align 1, !alias.scope !1589, !noalias !1587, !noundef !136
  %_53.i684 = zext i8 %_54.i683 to i64
  %42 = or i64 %_7.i678, %_53.i684
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit688

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit688: ; preds = %bb4.i271, %bb2.i624
  %_0.sroa.0.0.i686 = phi i64 [ %42, %bb2.i624 ], [ 0, %bb4.i271 ]
  %_19.0.i276 = add nuw i64 %k.sroa.0.0.i2373156, %p.sroa.0.1.i3244.fr
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1592)
  %_5.1.i = icmp ugt i64 %_19.0.i276, -9
  br i1 %_5.1.i, label %panic.i619, label %bb1.i575

bb1.i575:                                         ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit688
  %43 = icmp ugt i64 %_19.0.i276, 499992
  br i1 %43, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit, label %bb2.i578

panic.i619:                                       ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit688
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_c9d76a7bf6f333d6169298e9d093a546) #13, !noalias !1595
  unreachable

bb2.i578:                                         ; preds = %bb1.i575
  %44 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_19.0.i276
  %_15.i582 = load i8, ptr %44, align 1, !alias.scope !1592, !noalias !1587, !noundef !136
  %_14.i583 = zext i8 %_15.i582 to i64
  %_13.i584 = shl nuw i64 %_14.i583, 56
  %45 = getelementptr inbounds nuw i8, ptr %44, i64 1
  %_19.i587 = load i8, ptr %45, align 1, !alias.scope !1592, !noalias !1587, !noundef !136
  %_18.i588 = zext i8 %_19.i587 to i64
  %_17.i = shl nuw nsw i64 %_18.i588, 48
  %_12.i589 = or disjoint i64 %_17.i, %_13.i584
  %46 = getelementptr inbounds nuw i8, ptr %44, i64 2
  %_25.i593 = load i8, ptr %46, align 1, !alias.scope !1592, !noalias !1587, !noundef !136
  %_24.i594 = zext i8 %_25.i593 to i64
  %_23.i = shl nuw nsw i64 %_24.i594, 40
  %_11.i595 = or disjoint i64 %_12.i589, %_23.i
  %47 = getelementptr inbounds nuw i8, ptr %44, i64 3
  %_31.i = load i8, ptr %47, align 1, !alias.scope !1592, !noalias !1587, !noundef !136
  %_30.i599 = zext i8 %_31.i to i64
  %_29.i600 = shl nuw nsw i64 %_30.i599, 32
  %_10.i601 = or disjoint i64 %_11.i595, %_29.i600
  %48 = getelementptr inbounds nuw i8, ptr %44, i64 4
  %_37.i = load i8, ptr %48, align 1, !alias.scope !1592, !noalias !1587, !noundef !136
  %_36.i603 = zext i8 %_37.i to i64
  %_35.i604 = shl nuw nsw i64 %_36.i603, 24
  %_9.i605 = or disjoint i64 %_10.i601, %_35.i604
  %49 = getelementptr inbounds nuw i8, ptr %44, i64 5
  %_43.i = load i8, ptr %49, align 1, !alias.scope !1592, !noalias !1587, !noundef !136
  %_42.i = zext i8 %_43.i to i64
  %_41.i608 = shl nuw nsw i64 %_42.i, 16
  %_8.i609 = or disjoint i64 %_9.i605, %_41.i608
  %50 = getelementptr inbounds nuw i8, ptr %44, i64 6
  %_49.i612 = load i8, ptr %50, align 1, !alias.scope !1592, !noalias !1587, !noundef !136
  %_48.i = zext i8 %_49.i612 to i64
  %_47.i = shl nuw nsw i64 %_48.i, 8
  %_7.i613 = or i64 %_8.i609, %_47.i
  %51 = getelementptr inbounds nuw i8, ptr %44, i64 7
  %_54.i = load i8, ptr %51, align 1, !alias.scope !1592, !noalias !1587, !noundef !136
  %_53.i = zext i8 %_54.i to i64
  %52 = or i64 %_7.i613, %_53.i
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit: ; preds = %bb1.i575, %bb2.i578
  %_0.sroa.0.0.i618 = phi i64 [ %52, %bb2.i578 ], [ 0, %bb1.i575 ]
  %53 = icmp eq i64 %_0.sroa.0.0.i686, %_0.sroa.0.0.i618
  br i1 %53, label %bb2.i266, label %bb17.i238.thread

bb17.i238.thread:                                 ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit
  %_0.sroa.0.0.i618.lcssa = phi i64 [ %_0.sroa.0.0.i618, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit ]
  %_0.sroa.0.0.i686.lcssa340 = phi i64 [ %_0.sroa.0.0.i686, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit ]
  %k.sroa.0.0.i2373156.lcssa339 = phi i64 [ %k.sroa.0.0.i2373156, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit ]
  %x.i281 = xor i64 %_0.sroa.0.0.i618.lcssa, %_0.sroa.0.0.i686.lcssa340
  %54 = tail call range(i64 0, 65) i64 @llvm.ctlz.i64(i64 %x.i281, i1 true)
  %_2220.i282 = lshr i64 %54, 3
  %_24.0.i283 = or disjoint i64 %_2220.i282, %k.sroa.0.0.i2373156.lcssa339
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit292

bb21.i248:                                        ; preds = %bb17.i238, %bb24.i258
  %k.sroa.0.2.i2413159 = phi i64 [ %k.sroa.0.3.i263, %bb24.i258 ], [ %30, %bb17.i238 ]
  %_32.0.i246 = add nuw nsw i64 %k.sroa.0.2.i2413159, %start1.sroa.0.0.i3164
  %_34.i249 = icmp samesign ult i64 %_32.0.i246, 500000
  br i1 %_34.i249, label %bb22.i251, label %panic6.i250

bb22.i251:                                        ; preds = %bb21.i248
  %55 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_32.0.i246
  %_29.i252 = load i8, ptr %55, align 1, !alias.scope !1596, !noalias !1587, !noundef !136
  %_38.0.i253 = add i64 %k.sroa.0.2.i2413159, %p.sroa.0.1.i3244.fr
  %_38.1.i254 = icmp ult i64 %_38.0.i253, %p.sroa.0.1.i3244.fr
  br i1 %_38.1.i254, label %panic7.i264, label %bb23.i255

panic6.i250:                                      ; preds = %bb21.i248
  %_32.0.i246.lcssa341 = phi i64 [ %_32.0.i246, %bb21.i248 ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_32.0.i246.lcssa341, i64 noundef range(i64 0, -9223372036854775808) 500000, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_88632784907d7d84d4dbb3c61bd04ae5) #13, !noalias !1587
  unreachable

bb23.i255:                                        ; preds = %bb22.i251
  %_39.i256 = icmp ult i64 %_38.0.i253, 500000
  br i1 %_39.i256, label %bb24.i258, label %panic8.i257

panic7.i264:                                      ; preds = %bb22.i251
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_747cf99f751d00e13712f3b323161078) #13, !noalias !1587
  unreachable

bb24.i258:                                        ; preds = %bb23.i255
  %56 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_38.0.i253
  %_35.i259 = load i8, ptr %56, align 1, !alias.scope !1596, !noalias !1587, !noundef !136
  %_28.i260 = icmp eq i8 %_29.i252, %_35.i259
  %_40.0.i261 = zext i1 %_28.i260 to i64
  %k.sroa.0.3.i263 = add nuw nsw i64 %k.sroa.0.2.i2413159, %_40.0.i261
  %_26.i242 = icmp samesign ult i64 %k.sroa.0.3.i263, %spec.store.select3.i21
  %or.cond.i243 = select i1 %_28.i260, i1 %_26.i242, i1 false
  br i1 %or.cond.i243, label %bb21.i248, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit292

panic8.i257:                                      ; preds = %bb23.i255
  %_38.0.i253.lcssa345 = phi i64 [ %_38.0.i253, %bb23.i255 ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_38.0.i253.lcssa345, i64 noundef range(i64 0, -9223372036854775808) 500000, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_45688f0cd226461942a9ccd1c478fc80) #13, !noalias !1587
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit292: ; preds = %bb24.i258, %bb17.i238.thread, %bb17.i238
  %k.sroa.0.2.i241.lcssa = phi i64 [ %30, %bb17.i238 ], [ %_24.0.i283, %bb17.i238.thread ], [ %k.sroa.0.3.i263, %bb24.i258 ]
  %_46.i = icmp ugt i64 %k.sroa.0.2.i241.lcssa, %have.sroa.0.0.i3163
  br i1 %_46.i, label %bb19.i, label %bb37.i

bb19.i:                                           ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit292
  %_51.not.i = icmp ult i64 %k.sroa.0.2.i241.lcssa, %spec.store.select.i27
  br i1 %_51.not.i, label %bb26.i, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit

bb26.i:                                           ; preds = %bb19.i
  %_55.0.i = add i64 %k.sroa.0.2.i241.lcssa, %p.sroa.0.1.i3244.fr
  %_55.1.i = icmp ult i64 %_55.0.i, %p.sroa.0.1.i3244.fr
  br i1 %_55.1.i, label %panic7.i, label %bb27.i

bb27.i:                                           ; preds = %bb26.i
  %_53.not.i = icmp ult i64 %_55.0.i, 500000
  br i1 %_53.not.i, label %bb31.i, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit

panic7.i:                                         ; preds = %bb26.i
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_15b4ce25bced7a5ce053340a71ef7d4e) #13, !noalias !1587
  unreachable

bb31.i:                                           ; preds = %bb27.i
  %57 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_55.0.i
  %58 = load i8, ptr %57, align 1, !alias.scope !1584, !noalias !1587, !noundef !136
  br label %bb37.i

bb37.i:                                           ; preds = %bb31.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit292, %bb16.i31
  %pb.sroa.0.3.i = phi i8 [ %pb.sroa.0.1.i3160, %bb16.i31 ], [ %pb.sroa.0.1.i3160, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit292 ], [ %58, %bb31.i ]
  %bd.sroa.0.2.i = phi i64 [ %bd.sroa.0.0.i3161, %bb16.i31 ], [ %bd.sroa.0.0.i3161, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit292 ], [ %d.i, %bb31.i ]
  %have.sroa.0.2.i = phi i64 [ %have.sroa.0.0.i3163, %bb16.i31 ], [ %have.sroa.0.0.i3163, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit292 ], [ %k.sroa.0.2.i241.lcssa, %bb31.i ]
  %_60.i33 = and i64 %start1.sroa.0.0.i3164, 32767
  %59 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_60.i33
  %_59.i = load i32, ptr %59, align 4, !alias.scope !1587, !noalias !1584, !noundef !136
  %nx.i = zext i32 %_59.i to i64
  %_64.i = icmp samesign ule i64 %start1.sroa.0.0.i3164, %nx.i
  %_66.0.i = add nsw i64 %depth.sroa.0.0.i3162, -1
  %_24.not.i = icmp eq i64 %_66.0.i, 0
  %or.cond = select i1 %_64.i, i1 true, i1 %_24.not.i
  br i1 %or.cond, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit, label %bb11.i29

_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit: ; preds = %bb19.i, %bb27.i, %bb37.i, %bb13.i, %bb11.i29
  %have.sroa.0.1.i3456 = phi i64 [ %have.sroa.0.0.i3163, %bb11.i29 ], [ %have.sroa.0.2.i, %bb37.i ], [ %have.sroa.0.0.i3163, %bb13.i ], [ %k.sroa.0.2.i241.lcssa, %bb27.i ], [ %k.sroa.0.2.i241.lcssa, %bb19.i ]
  %bd.sroa.0.1.i3455 = phi i64 [ %bd.sroa.0.0.i3161, %bb11.i29 ], [ %bd.sroa.0.2.i, %bb37.i ], [ %bd.sroa.0.0.i3161, %bb13.i ], [ %d.i, %bb27.i ], [ %d.i, %bb19.i ]
  %.not = icmp eq i64 %bd.sroa.0.1.i3455, 0
  br i1 %.not, label %bb154.i, label %bb16.i.preheader

bb16.i.preheader:                                 ; preds = %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit
  %_39.i3201 = icmp ult i64 %have.sroa.0.1.i3456, 32
  br i1 %_39.i3201, label %bb18.i, label %bb63.i

bb8.i:                                            ; preds = %bb5.i, %bb8.i
  %ins.sroa.0.1.i3154 = phi i64 [ %_23.0.i, %bb8.i ], [ %ins.sroa.0.0.i3243, %bb5.i ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1599)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1602)
  %60 = getelementptr inbounds nuw i8, ptr %input.0, i64 %ins.sroa.0.1.i3154
  %61 = load i32, ptr %60, align 1
  %62 = call i32 @llvm.bswap.i32(i32 %61)
  %63 = zext i32 %62 to i64
  %64 = mul i64 %63, -7046029254386353131
  %65 = lshr i64 %64, 48
  %66 = getelementptr inbounds nuw [4 x i8], ptr %head.i, i64 %65
  %old.i.i = load i32, ptr %66, align 4, !alias.scope !1599, !noalias !1604, !noundef !136
  %_16.i.i = and i64 %ins.sroa.0.1.i3154, 32767
  %67 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_16.i.i
  store i32 %old.i.i, ptr %67, align 4, !alias.scope !1602, !noalias !1606
  %68 = trunc i64 %ins.sroa.0.1.i3154 to i32
  store i32 %68, ptr %66, align 4, !alias.scope !1599, !noalias !1604
  %_23.0.i = add nuw nsw i64 %ins.sroa.0.1.i3154, 1
  %exitcond.not = icmp eq i64 %_23.0.i, %p.sroa.0.1.i3244.fr
  br i1 %exitcond.not, label %bb11.i, label %bb8.i

bb154.i:                                          ; preds = %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1607)
  %_9.i328 = icmp ult i64 %nt.sroa.0.1.i3247, %out.1
  br i1 %_9.i328, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit333, label %panic1.i329

panic1.i329:                                      ; preds = %bb154.i
  %nt.sroa.0.1.i3247.lcssa427 = phi i64 [ %nt.sroa.0.1.i3247, %bb154.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %nt.sroa.0.1.i3247.lcssa427, i64 noundef range(i64 0, 2305843009213693952) %out.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_f5cc78c6143d87a95e73f58df7e9bb32) #13, !noalias !1610
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit333: ; preds = %bb154.i
  %69 = getelementptr inbounds nuw [4 x i8], ptr %out.0, i64 %nt.sroa.0.1.i3247
  %70 = extractelement <4 x i8> %21, i64 0
  %71 = zext i8 %70 to i32
  store i32 %71, ptr %69, align 4, !alias.scope !1607, !noalias !1612
  %_219.0.i = add i64 %miss.sroa.0.0.i3246, 1
  %_219.1.i = icmp eq i64 %miss.sroa.0.0.i3246, -1
  br i1 %_219.1.i, label %panic5.i, label %bb157.i

bb157.i:                                          ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit333
  %72 = lshr i64 %_219.0.i, 5
  %nt.sroa.0.3.i3166 = add nuw nsw i64 %nt.sroa.0.1.i3247, 1
  %_225.i3167 = icmp ne i64 %72, 0
  %_227.i3168 = icmp ult i64 %p.sroa.0.1.i3244.fr, 499991
  %or.cond45.i3169 = and i1 %_225.i3167, %_227.i3168
  br i1 %or.cond45.i3169, label %bb164.i.preheader, label %bb170.i

bb164.i.preheader:                                ; preds = %bb157.i
  %spec.store.select.i = tail call i64 @llvm.umin.i64(i64 %72, i64 1000000)
  %73 = add nsw i64 %spec.store.select.i, -1
  %74 = sub nuw nsw i64 499990, %p.sroa.0.1.i3244.fr
  %umin = call i64 @llvm.umin.i64(i64 %73, i64 %74)
  %75 = freeze i64 %umin
  %76 = xor i64 %nt.sroa.0.1.i3247, -1
  %77 = add nsw i64 %out.1, %76
  %umin305 = call i64 @llvm.umin.i64(i64 %75, i64 %77)
  %78 = add i64 %umin305, 1
  %min.iters.check = icmp ult i64 %78, 9
  br i1 %min.iters.check, label %bb164.i.preheader337, label %vector.ph

bb164.i.preheader337:                             ; preds = %vector.body, %bb164.i.preheader
  %nt.sroa.0.3.i3172.ph = phi i64 [ %nt.sroa.0.3.i3166, %bb164.i.preheader ], [ %81, %vector.body ]
  %p.sroa.0.3.i3171.ph = phi i64 [ %_29.0.i, %bb164.i.preheader ], [ %82, %vector.body ]
  %step.sroa.0.0.i3170.ph = phi i64 [ %spec.store.select.i, %bb164.i.preheader ], [ %83, %vector.body ]
  br label %bb164.i

vector.ph:                                        ; preds = %bb164.i.preheader
  %n.mod.vf = and i64 %78, 7
  %79 = icmp eq i64 %n.mod.vf, 0
  %80 = select i1 %79, i64 8, i64 %n.mod.vf
  %n.vec = sub nuw i64 %78, %80
  %81 = add i64 %nt.sroa.0.3.i3166, %n.vec
  %82 = add i64 %_29.0.i, %n.vec
  %83 = sub i64 %spec.store.select.i, %n.vec
  %84 = getelementptr i8, ptr %input.0, i64 %_29.0.i
  %85 = getelementptr [4 x i8], ptr %out.0, i64 %nt.sroa.0.3.i3166
  br label %vector.body

vector.body:                                      ; preds = %vector.body, %vector.ph
  %index = phi i64 [ 0, %vector.ph ], [ %index.next, %vector.body ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1613)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1616)
  %86 = getelementptr i8, ptr %84, i64 %index
  %87 = getelementptr inbounds nuw i8, ptr %86, i64 4
  %wide.load = load <4 x i8>, ptr %86, align 1, !alias.scope !1613, !noalias !1616
  %wide.load306 = load <4 x i8>, ptr %87, align 1, !alias.scope !1613, !noalias !1616
  %88 = getelementptr [4 x i8], ptr %85, i64 %index
  %89 = zext <4 x i8> %wide.load to <4 x i32>
  %90 = zext <4 x i8> %wide.load306 to <4 x i32>
  %91 = getelementptr inbounds nuw i8, ptr %88, i64 16
  store <4 x i32> %89, ptr %88, align 4, !alias.scope !1616, !noalias !1613
  store <4 x i32> %90, ptr %91, align 4, !alias.scope !1616, !noalias !1613
  %index.next = add nuw i64 %index, 8
  %92 = icmp eq i64 %index.next, %n.vec
  br i1 %92, label %bb164.i.preheader337, label %vector.body, !llvm.loop !1618

panic5.i:                                         ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit333
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_5047a97e092172d1cdcda63092b5e51f) #13
  unreachable

bb170.i:                                          ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit324, %bb157.i
  %p.sroa.0.3.i.lcssa = phi i64 [ %_29.0.i, %bb157.i ], [ %_231.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit324 ]
  %nt.sroa.0.3.i.lcssa = phi i64 [ %nt.sroa.0.3.i3166, %bb157.i ], [ %nt.sroa.0.3.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit324 ]
  %spec.select.i = tail call i64 @llvm.umax.i64(i64 %_29.0.i, i64 %p.sroa.0.3.i.lcssa)
  br label %bb174.i

bb164.i:                                          ; preds = %bb164.i.preheader337, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit324
  %nt.sroa.0.3.i3172 = phi i64 [ %nt.sroa.0.3.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit324 ], [ %nt.sroa.0.3.i3172.ph, %bb164.i.preheader337 ]
  %p.sroa.0.3.i3171 = phi i64 [ %_231.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit324 ], [ %p.sroa.0.3.i3171.ph, %bb164.i.preheader337 ]
  %step.sroa.0.0.i3170 = phi i64 [ %_232.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit324 ], [ %step.sroa.0.0.i3170.ph, %bb164.i.preheader337 ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1613)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1616)
  %exitcond3444.not = icmp eq i64 %nt.sroa.0.3.i3172, %out.1
  br i1 %exitcond3444.not, label %panic1.i320, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit324

panic1.i320:                                      ; preds = %bb164.i
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %out.1, i64 noundef range(i64 0, 2305843009213693952) %out.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_f5cc78c6143d87a95e73f58df7e9bb32) #13, !noalias !1619
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit324: ; preds = %bb164.i
  %93 = getelementptr inbounds nuw i8, ptr %input.0, i64 %p.sroa.0.3.i3171
  %_5.i322 = load i8, ptr %93, align 1, !alias.scope !1613, !noalias !1616, !noundef !136
  %94 = getelementptr inbounds nuw [4 x i8], ptr %out.0, i64 %nt.sroa.0.3.i3172
  %95 = zext i8 %_5.i322 to i32
  store i32 %95, ptr %94, align 4, !alias.scope !1616, !noalias !1613
  %_231.0.i = add nuw nsw i64 %p.sroa.0.3.i3171, 1
  %_232.0.i = add nsw i64 %step.sroa.0.0.i3170, -1
  %nt.sroa.0.3.i = add i64 %nt.sroa.0.3.i3172, 1
  %_225.i = icmp ne i64 %_232.0.i, 0
  %_227.i = icmp ult i64 %p.sroa.0.3.i3171, 499991
  %or.cond45.i = select i1 %_225.i, i1 %_227.i, i1 false
  br i1 %or.cond45.i, label %bb164.i, label %bb170.i, !llvm.loop !1620

bb174.i:                                          ; preds = %bb150.i, %bb170.i
  %ins.sroa.0.3.i = phi i64 [ %spec.select150.i, %bb150.i ], [ %spec.select.i, %bb170.i ]
  %p.sroa.0.4.i = phi i64 [ %_19.0.i347, %bb150.i ], [ %p.sroa.0.3.i.lcssa, %bb170.i ]
  %miss.sroa.0.1.i = phi i64 [ 0, %bb150.i ], [ %_219.0.i, %bb170.i ]
  %nt.sroa.0.4.i = phi i64 [ %_17.0.i, %bb150.i ], [ %nt.sroa.0.3.i.lcssa, %bb170.i ]
  %_11.i = icmp ult i64 %p.sroa.0.4.i, 499992
  %_13.i = icmp ne i64 %_15.0.i, 0
  %or.cond.i = select i1 %_11.i, i1 %_13.i, i1 false
  br i1 %or.cond.i, label %bb5.i, label %bb178.i

bb18.i:                                           ; preds = %bb16.i.preheader, %bb59.i
  %nt.sroa.0.5.i3206 = phi i64 [ %_10.0.i305, %bb59.i ], [ %nt.sroa.0.1.i3247, %bb16.i.preheader ]
  %l.sroa.0.0.i3205 = phi i64 [ %l.sroa.0.1.i, %bb59.i ], [ %have.sroa.0.1.i3456, %bb16.i.preheader ]
  %d.sroa.0.0.i3204 = phi i64 [ %d.sroa.0.1.i, %bb59.i ], [ %bd.sroa.0.1.i3455, %bb16.i.preheader ]
  %p.sroa.0.5.i3203 = phi i64 [ %p.sroa.0.6.i, %bb59.i ], [ %p.sroa.0.1.i3244.fr, %bb16.i.preheader ]
  %ins.sroa.0.4.i3202 = phi i64 [ %ins.sroa.0.5.i, %bb59.i ], [ %_29.0.i, %bb16.i.preheader ]
  %_44.0.i = add i64 %p.sroa.0.5.i3203, 1
  %_41.i = icmp ult i64 %p.sroa.0.5.i3203, 499991
  br i1 %_41.i, label %bb21.i, label %bb63.i

bb63.i:                                           ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit, %bb16.i123, %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit155, %bb13.i121, %bb11.i107, %bb35.i, %bb39.i, %bb48.i, %bb59.i, %bb18.i, %bb16.i.preheader
  %ins.sroa.0.4.i.lcssa = phi i64 [ %_29.0.i, %bb16.i.preheader ], [ %_80.0.i, %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit155 ], [ %_80.0.i, %bb13.i121 ], [ %_80.0.i, %bb11.i107 ], [ %ins.sroa.0.5.i, %bb59.i ], [ %_80.0.i, %bb39.i ], [ %_51.0.i, %bb35.i ], [ %_80.0.i, %bb48.i ], [ %ins.sroa.0.4.i3202, %bb18.i ], [ %_80.0.i, %bb16.i123 ], [ %_80.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit ]
  %p.sroa.0.5.i.lcssa = phi i64 [ %p.sroa.0.1.i3244.fr, %bb16.i.preheader ], [ %p.sroa.0.5.i3203, %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit155 ], [ %p.sroa.0.5.i3203, %bb13.i121 ], [ %p.sroa.0.5.i3203, %bb11.i107 ], [ %p.sroa.0.6.i, %bb59.i ], [ %p.sroa.0.5.i3203, %bb39.i ], [ 499990, %bb35.i ], [ %p.sroa.0.5.i3203, %bb48.i ], [ %p.sroa.0.5.i3203, %bb18.i ], [ %p.sroa.0.5.i3203, %bb16.i123 ], [ %p.sroa.0.5.i3203, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit ]
  %d.sroa.0.0.i.lcssa = phi i64 [ %bd.sroa.0.1.i3455, %bb16.i.preheader ], [ %d.sroa.0.0.i3204, %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit155 ], [ %d.sroa.0.0.i3204, %bb13.i121 ], [ %d.sroa.0.0.i3204, %bb11.i107 ], [ %d.sroa.0.1.i, %bb59.i ], [ %d.sroa.0.0.i3204, %bb39.i ], [ %d.sroa.0.0.i3204, %bb35.i ], [ %d.sroa.0.0.i3204, %bb48.i ], [ %d.sroa.0.0.i3204, %bb18.i ], [ %d.sroa.0.0.i3204, %bb16.i123 ], [ %d.sroa.0.0.i3204, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit ]
  %l.sroa.0.0.i.lcssa = phi i64 [ %have.sroa.0.1.i3456, %bb16.i.preheader ], [ %l.sroa.0.0.i3205, %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit155 ], [ %l.sroa.0.0.i3205, %bb13.i121 ], [ %l.sroa.0.0.i3205, %bb11.i107 ], [ %l.sroa.0.1.i, %bb59.i ], [ %l.sroa.0.0.i3205, %bb39.i ], [ %l.sroa.0.0.i3205, %bb35.i ], [ %l.sroa.0.0.i3205, %bb48.i ], [ %l.sroa.0.0.i3205, %bb18.i ], [ %l.sroa.0.0.i3205, %bb16.i123 ], [ %l.sroa.0.0.i3205, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit ]
  %nt.sroa.0.5.i.lcssa = phi i64 [ %nt.sroa.0.1.i3247, %bb16.i.preheader ], [ %nt.sroa.0.5.i3206, %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit155 ], [ %nt.sroa.0.5.i3206, %bb13.i121 ], [ %nt.sroa.0.5.i3206, %bb11.i107 ], [ %_10.0.i305, %bb59.i ], [ %nt.sroa.0.5.i3206, %bb39.i ], [ %nt.sroa.0.5.i3206, %bb35.i ], [ %nt.sroa.0.5.i3206, %bb48.i ], [ %nt.sroa.0.5.i3206, %bb18.i ], [ %nt.sroa.0.5.i3206, %bb16.i123 ], [ %nt.sroa.0.5.i3206, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit ]
  %96 = add i64 %nt.sroa.0.5.i.lcssa, -1
  %97 = icmp ult i64 %96, %out.1
  %_110.i3221 = icmp ult i64 %l.sroa.0.0.i.lcssa, 258
  %or.cond49.i3222 = select i1 %97, i1 %_110.i3221, i1 false
  %_112.i3223 = icmp ult i64 %d.sroa.0.0.i.lcssa, %p.sroa.0.5.i.lcssa
  %or.cond149.i3224 = and i1 %or.cond49.i3222, %_112.i3223
  br i1 %or.cond149.i3224, label %bb71.i, label %bb116.i

bb21.i:                                           ; preds = %bb18.i
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1621)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1624)
  %98 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_44.0.i
  %_11.i411 = load i8, ptr %98, align 1, !alias.scope !1626, !noalias !1629, !noundef !136
  %_10.i412 = zext i8 %_11.i411 to i64
  %_9.i413 = shl nuw nsw i64 %_10.i412, 24
  %99 = getelementptr inbounds nuw i8, ptr %input.0, i64 %p.sroa.0.5.i3203
  %100 = getelementptr inbounds nuw i8, ptr %99, i64 2
  %_15.i418 = load i8, ptr %100, align 1, !alias.scope !1626, !noalias !1629, !noundef !136
  %_14.i419 = zext i8 %_15.i418 to i64
  %_13.i420 = shl nuw nsw i64 %_14.i419, 16
  %_8.i421 = or disjoint i64 %_13.i420, %_9.i413
  %101 = getelementptr inbounds nuw i8, ptr %99, i64 3
  %_21.i426 = load i8, ptr %101, align 1, !alias.scope !1626, !noalias !1629, !noundef !136
  %_20.i427 = zext i8 %_21.i426 to i64
  %_19.i428 = shl nuw nsw i64 %_20.i427, 8
  %_7.i429 = or disjoint i64 %_8.i421, %_19.i428
  %102 = getelementptr inbounds nuw i8, ptr %99, i64 4
  %_26.i434 = load i8, ptr %102, align 1, !alias.scope !1626, !noalias !1629, !noundef !136
  %_25.i435 = zext i8 %_26.i434 to i64
  %103 = or disjoint i64 %_7.i429, %_25.i435
  %104 = mul i64 %103, -7046029254386353131
  %105 = lshr i64 %104, 48
  %106 = getelementptr inbounds nuw [4 x i8], ptr %head.i, i64 %105
  %old.i183.i = load i32, ptr %106, align 4, !alias.scope !1621, !noalias !1630, !noundef !136
  %_16.i184.i = and i64 %_44.0.i, 32767
  %107 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_16.i184.i
  store i32 %old.i183.i, ptr %107, align 4, !alias.scope !1624, !noalias !1632
  %108 = trunc nuw nsw i64 %_44.0.i to i32
  store i32 %108, ptr %106, align 4, !alias.scope !1621, !noalias !1630
  %_0.i185.i = zext i32 %old.i183.i to i64
  %_51.0.i = add nuw nsw i64 %p.sroa.0.5.i3203, 2
  %_56.0.i = add nsw i64 %l.sroa.0.0.i3205, -1
  %spec.select.i10 = tail call i64 @llvm.umax.i64(i64 %_56.0.i, i64 3)
  %_13.0.i11 = sub nuw nsw i64 499999, %p.sroa.0.5.i3203
  %spec.store.select3.i12 = tail call i64 @llvm.umin.i64(i64 %_13.0.i11, i64 258)
  %_19.0.i37 = add nuw nsw i64 %spec.select.i10, %_44.0.i
  %_16.i38 = icmp ult i64 %_19.0.i37, 500000
  br i1 %_16.i38, label %bb7.i92, label %bb11.i49

bb7.i92:                                          ; preds = %bb21.i
  %109 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_19.0.i37
  %110 = load i8, ptr %109, align 1, !alias.scope !1633, !noalias !1636, !noundef !136
  br label %bb11.i49

bb11.i49:                                         ; preds = %bb21.i, %bb7.i92
  %pb.sroa.0.0.i40 = phi i8 [ %110, %bb7.i92 ], [ 0, %bb21.i ]
  %d.i50 = sub nsw i64 %_44.0.i, %_0.i185.i
  %_29.i51 = add nsw i64 %d.i50, -1
  %_28.i52 = icmp ult i64 %_29.i51, 32768
  br i1 %_28.i52, label %bb13.i63, label %bb35.i

bb13.i63:                                         ; preds = %bb11.i49
  %_34.0.i61 = add nuw nsw i64 %spec.select.i10, %_0.i185.i
  %_30.i64 = icmp ult i64 %_34.0.i61, 500000
  br i1 %_30.i64, label %bb16.i65, label %bb35.i

bb16.i65:                                         ; preds = %bb13.i63
  %111 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_34.0.i61
  %_36.i66 = load i8, ptr %111, align 1, !alias.scope !1633, !noalias !1636, !noundef !136
  %_35.i67 = icmp eq i8 %_36.i66, %pb.sroa.0.0.i40
  br i1 %_35.i67, label %bb2.i208.preheader, label %bb35.i

bb2.i208.preheader:                               ; preds = %bb16.i65
  %112 = and i64 %spec.store.select3.i12, 504
  br label %bb2.i208

bb2.i208:                                         ; preds = %bb2.i208.preheader, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit757
  %k.sroa.0.0.i1793176 = phi i64 [ %_10.0.i209, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit757 ], [ 0, %bb2.i208.preheader ]
  %_10.0.i209 = add nuw nsw i64 %k.sroa.0.0.i1793176, 8
  %_7.not.i212 = icmp samesign ugt i64 %_10.0.i209, %spec.store.select3.i12
  br i1 %_7.not.i212, label %bb17.i180, label %bb4.i213

bb4.i213:                                         ; preds = %bb2.i208
  %_15.0.i214 = add nuw nsw i64 %k.sroa.0.0.i1793176, %_0.i185.i
  %113 = icmp samesign ugt i64 %_15.0.i214, 499992
  br i1 %113, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit826, label %bb2.i762

bb17.i180:                                        ; preds = %bb2.i208
  %_26.i1843177.not = icmp eq i64 %112, %spec.store.select3.i12
  br i1 %_26.i1843177.not, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit234, label %bb21.i190

bb2.i762:                                         ; preds = %bb4.i213
  %114 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_15.0.i214
  %_15.i766 = load i8, ptr %114, align 1, !alias.scope !1638, !noalias !1636, !noundef !136
  %_14.i767 = zext i8 %_15.i766 to i64
  %_13.i768 = shl nuw i64 %_14.i767, 56
  %115 = getelementptr inbounds nuw i8, ptr %114, i64 1
  %_19.i773 = load i8, ptr %115, align 1, !alias.scope !1638, !noalias !1636, !noundef !136
  %_18.i774 = zext i8 %_19.i773 to i64
  %_17.i775 = shl nuw nsw i64 %_18.i774, 48
  %_12.i776 = or disjoint i64 %_17.i775, %_13.i768
  %116 = getelementptr inbounds nuw i8, ptr %114, i64 2
  %_25.i781 = load i8, ptr %116, align 1, !alias.scope !1638, !noalias !1636, !noundef !136
  %_24.i782 = zext i8 %_25.i781 to i64
  %_23.i783 = shl nuw nsw i64 %_24.i782, 40
  %_11.i784 = or disjoint i64 %_12.i776, %_23.i783
  %117 = getelementptr inbounds nuw i8, ptr %114, i64 3
  %_31.i789 = load i8, ptr %117, align 1, !alias.scope !1638, !noalias !1636, !noundef !136
  %_30.i790 = zext i8 %_31.i789 to i64
  %_29.i791 = shl nuw nsw i64 %_30.i790, 32
  %_10.i792 = or disjoint i64 %_11.i784, %_29.i791
  %118 = getelementptr inbounds nuw i8, ptr %114, i64 4
  %_37.i797 = load i8, ptr %118, align 1, !alias.scope !1638, !noalias !1636, !noundef !136
  %_36.i798 = zext i8 %_37.i797 to i64
  %_35.i799 = shl nuw nsw i64 %_36.i798, 24
  %_9.i800 = or disjoint i64 %_10.i792, %_35.i799
  %119 = getelementptr inbounds nuw i8, ptr %114, i64 5
  %_43.i805 = load i8, ptr %119, align 1, !alias.scope !1638, !noalias !1636, !noundef !136
  %_42.i806 = zext i8 %_43.i805 to i64
  %_41.i807 = shl nuw nsw i64 %_42.i806, 16
  %_8.i808 = or disjoint i64 %_9.i800, %_41.i807
  %120 = getelementptr inbounds nuw i8, ptr %114, i64 6
  %_49.i813 = load i8, ptr %120, align 1, !alias.scope !1638, !noalias !1636, !noundef !136
  %_48.i814 = zext i8 %_49.i813 to i64
  %_47.i815 = shl nuw nsw i64 %_48.i814, 8
  %_7.i816 = or i64 %_8.i808, %_47.i815
  %121 = getelementptr inbounds nuw i8, ptr %114, i64 7
  %_54.i821 = load i8, ptr %121, align 1, !alias.scope !1638, !noalias !1636, !noundef !136
  %_53.i822 = zext i8 %_54.i821 to i64
  %122 = or i64 %_7.i816, %_53.i822
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit826

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit826: ; preds = %bb4.i213, %bb2.i762
  %_0.sroa.0.0.i824 = phi i64 [ %122, %bb2.i762 ], [ 0, %bb4.i213 ]
  %_19.0.i218 = add nuw i64 %k.sroa.0.0.i1793176, %_44.0.i
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1641)
  %_5.1.i689 = icmp ugt i64 %_19.0.i218, -9
  br i1 %_5.1.i689, label %panic.i756, label %bb1.i690

bb1.i690:                                         ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit826
  %123 = icmp ugt i64 %_19.0.i218, 499992
  br i1 %123, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit757, label %bb2.i693

panic.i756:                                       ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit826
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_c9d76a7bf6f333d6169298e9d093a546) #13, !noalias !1644
  unreachable

bb2.i693:                                         ; preds = %bb1.i690
  %124 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_19.0.i218
  %_15.i697 = load i8, ptr %124, align 1, !alias.scope !1641, !noalias !1636, !noundef !136
  %_14.i698 = zext i8 %_15.i697 to i64
  %_13.i699 = shl nuw i64 %_14.i698, 56
  %125 = getelementptr inbounds nuw i8, ptr %124, i64 1
  %_19.i704 = load i8, ptr %125, align 1, !alias.scope !1641, !noalias !1636, !noundef !136
  %_18.i705 = zext i8 %_19.i704 to i64
  %_17.i706 = shl nuw nsw i64 %_18.i705, 48
  %_12.i707 = or disjoint i64 %_17.i706, %_13.i699
  %126 = getelementptr inbounds nuw i8, ptr %124, i64 2
  %_25.i712 = load i8, ptr %126, align 1, !alias.scope !1641, !noalias !1636, !noundef !136
  %_24.i713 = zext i8 %_25.i712 to i64
  %_23.i714 = shl nuw nsw i64 %_24.i713, 40
  %_11.i715 = or disjoint i64 %_12.i707, %_23.i714
  %127 = getelementptr inbounds nuw i8, ptr %124, i64 3
  %_31.i720 = load i8, ptr %127, align 1, !alias.scope !1641, !noalias !1636, !noundef !136
  %_30.i721 = zext i8 %_31.i720 to i64
  %_29.i722 = shl nuw nsw i64 %_30.i721, 32
  %_10.i723 = or disjoint i64 %_11.i715, %_29.i722
  %128 = getelementptr inbounds nuw i8, ptr %124, i64 4
  %_37.i728 = load i8, ptr %128, align 1, !alias.scope !1641, !noalias !1636, !noundef !136
  %_36.i729 = zext i8 %_37.i728 to i64
  %_35.i730 = shl nuw nsw i64 %_36.i729, 24
  %_9.i731 = or disjoint i64 %_10.i723, %_35.i730
  %129 = getelementptr inbounds nuw i8, ptr %124, i64 5
  %_43.i736 = load i8, ptr %129, align 1, !alias.scope !1641, !noalias !1636, !noundef !136
  %_42.i737 = zext i8 %_43.i736 to i64
  %_41.i738 = shl nuw nsw i64 %_42.i737, 16
  %_8.i739 = or disjoint i64 %_9.i731, %_41.i738
  %130 = getelementptr inbounds nuw i8, ptr %124, i64 6
  %_49.i744 = load i8, ptr %130, align 1, !alias.scope !1641, !noalias !1636, !noundef !136
  %_48.i745 = zext i8 %_49.i744 to i64
  %_47.i746 = shl nuw nsw i64 %_48.i745, 8
  %_7.i747 = or i64 %_8.i739, %_47.i746
  %131 = getelementptr inbounds nuw i8, ptr %124, i64 7
  %_54.i752 = load i8, ptr %131, align 1, !alias.scope !1641, !noalias !1636, !noundef !136
  %_53.i753 = zext i8 %_54.i752 to i64
  %132 = or i64 %_7.i747, %_53.i753
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit757

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit757: ; preds = %bb1.i690, %bb2.i693
  %_0.sroa.0.0.i755 = phi i64 [ %132, %bb2.i693 ], [ 0, %bb1.i690 ]
  %133 = icmp eq i64 %_0.sroa.0.0.i824, %_0.sroa.0.0.i755
  br i1 %133, label %bb2.i208, label %bb17.i180.thread

bb17.i180.thread:                                 ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit757
  %_0.sroa.0.0.i755.lcssa = phi i64 [ %_0.sroa.0.0.i755, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit757 ]
  %_0.sroa.0.0.i824.lcssa349 = phi i64 [ %_0.sroa.0.0.i824, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit757 ]
  %k.sroa.0.0.i1793176.lcssa348 = phi i64 [ %k.sroa.0.0.i1793176, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit757 ]
  %x.i223 = xor i64 %_0.sroa.0.0.i755.lcssa, %_0.sroa.0.0.i824.lcssa349
  %134 = tail call range(i64 0, 65) i64 @llvm.ctlz.i64(i64 %x.i223, i1 true)
  %_2220.i224 = lshr i64 %134, 3
  %_24.0.i225 = or disjoint i64 %_2220.i224, %k.sroa.0.0.i1793176.lcssa348
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit234

bb21.i190:                                        ; preds = %bb17.i180, %bb24.i200
  %k.sroa.0.2.i1833179 = phi i64 [ %k.sroa.0.3.i205, %bb24.i200 ], [ %112, %bb17.i180 ]
  %_32.0.i188 = add nuw nsw i64 %k.sroa.0.2.i1833179, %_0.i185.i
  %_34.i191 = icmp samesign ult i64 %_32.0.i188, 500000
  br i1 %_34.i191, label %bb23.i197, label %panic6.i192

panic6.i192:                                      ; preds = %bb21.i190
  %_32.0.i188.lcssa = phi i64 [ %_32.0.i188, %bb21.i190 ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_32.0.i188.lcssa, i64 noundef range(i64 0, -9223372036854775808) 500000, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_88632784907d7d84d4dbb3c61bd04ae5) #13, !noalias !1636
  unreachable

bb23.i197:                                        ; preds = %bb21.i190
  %_38.0.i195 = add nuw nsw i64 %k.sroa.0.2.i1833179, %_44.0.i
  %_39.i198 = icmp ult i64 %_38.0.i195, 500000
  br i1 %_39.i198, label %bb24.i200, label %panic8.i199

bb24.i200:                                        ; preds = %bb23.i197
  %135 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_32.0.i188
  %_29.i194 = load i8, ptr %135, align 1, !alias.scope !1645, !noalias !1636, !noundef !136
  %136 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_38.0.i195
  %_35.i201 = load i8, ptr %136, align 1, !alias.scope !1645, !noalias !1636, !noundef !136
  %_28.i202 = icmp eq i8 %_29.i194, %_35.i201
  %_40.0.i203 = zext i1 %_28.i202 to i64
  %k.sroa.0.3.i205 = add nuw nsw i64 %k.sroa.0.2.i1833179, %_40.0.i203
  %_26.i184 = icmp samesign ult i64 %k.sroa.0.3.i205, %spec.store.select3.i12
  %or.cond.i185 = select i1 %_28.i202, i1 %_26.i184, i1 false
  br i1 %or.cond.i185, label %bb21.i190, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit234

panic8.i199:                                      ; preds = %bb23.i197
  %_38.0.i195.lcssa = phi i64 [ %_38.0.i195, %bb23.i197 ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_38.0.i195.lcssa, i64 noundef range(i64 0, -9223372036854775808) 500000, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_45688f0cd226461942a9ccd1c478fc80) #13, !noalias !1636
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit234: ; preds = %bb24.i200, %bb17.i180.thread, %bb17.i180
  %k.sroa.0.2.i183.lcssa = phi i64 [ %112, %bb17.i180 ], [ %_24.0.i225, %bb17.i180.thread ], [ %k.sroa.0.3.i205, %bb24.i200 ]
  %_46.i81 = icmp ugt i64 %k.sroa.0.2.i183.lcssa, %spec.select.i10
  br i1 %_46.i81, label %bb19.i82, label %bb35.i

bb19.i82:                                         ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit234
  %137 = add i64 %k.sroa.0.2.i183.lcssa, -11
  %or.cond.i981 = icmp ult i64 %137, 247
  br i1 %or.cond.i981, label %bb6.i1003, label %bb7.i982

bb7.i982:                                         ; preds = %bb6.i1003, %bb19.i82
  %c.sroa.0.0.i983 = phi i32 [ %140, %bb6.i1003 ], [ 168, %bb19.i82 ]
  %_17.i984 = icmp ugt i64 %d.i50, 4
  br i1 %_17.i984, label %bb12.i999, label %bb13.i985

bb6.i1003:                                        ; preds = %bb19.i82
  %138 = trunc nuw nsw i64 %k.sroa.0.2.i183.lcssa to i32
  %_11.i1004 = add nsw i32 %138, -3
  %_10.i1005 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_11.i1004, i1 false)
  %139 = shl nuw nsw i32 %_10.i1005, 4
  %140 = sub nuw nsw i32 632, %139
  br label %bb7.i982

bb13.i985:                                        ; preds = %bb12.i999, %bb7.i982
  %c.sroa.0.1.i986 = phi i32 [ %144, %bb12.i999 ], [ %c.sroa.0.0.i983, %bb7.i982 ]
  %_29.i987 = trunc i64 %k.sroa.0.2.i183.lcssa to i32
  %141 = add i32 %_29.i987, -33554432
  %_30.1.i988 = icmp ult i32 %141, -67108864
  br i1 %_30.1.i988, label %panic8.i995, label %bb14.i989

bb12.i999:                                        ; preds = %bb7.i982
  %142 = trunc nuw i64 %d.i50 to i32
  %_22.i997 = add nsw i32 %142, -1
  %_21.i1000 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_22.i997, i1 true)
  %143 = shl nuw nsw i32 %_21.i1000, 4
  %reass.sub = sub nsw i32 %c.sroa.0.0.i983, %143
  %144 = add nsw i32 %reass.sub, 480
  br label %bb13.i985

bb14.i989:                                        ; preds = %bb13.i985
  %_30.0.i990 = shl nsw i32 %_29.i987, 6
  %145 = tail call { i32, i1 } @llvm.ssub.with.overflow.i32(i32 %_30.0.i990, i32 %c.sroa.0.1.i986)
  %_31.1.i991 = extractvalue { i32, i1 } %145, 1
  br i1 %_31.1.i991, label %panic9.i994, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1006

panic8.i995:                                      ; preds = %bb13.i985
; call core::panicking::panic_const::panic_const_mul_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_mul_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_de42051d6ce5797cfcaece5556197823) #13, !noalias !1636
  unreachable

panic9.i994:                                      ; preds = %bb14.i989
; call core::panicking::panic_const::panic_const_sub_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_de42051d6ce5797cfcaece5556197823) #13, !noalias !1636
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1006: ; preds = %bb14.i989
  %_31.0.i993 = extractvalue { i32, i1 } %145, 0
  %_49.i = icmp sle i32 %_31.0.i993, -1000000
  %.not335 = icmp eq i64 %d.i50, 0
  %or.cond431 = or i1 %_49.i, %.not335
  br i1 %or.cond431, label %bb35.i, label %bb29.i

bb35.i:                                           ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit234, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1006, %bb16.i65, %bb13.i63, %bb11.i49, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1032
  %_70.i.not = icmp eq i64 %p.sroa.0.5.i3203, 499990
  br i1 %_70.i.not, label %bb63.i, label %bb39.i

bb29.i:                                           ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1006
  br i1 %or.cond.i981, label %bb6.i1055, label %bb7.i1034

bb7.i1034:                                        ; preds = %bb6.i1055, %bb29.i
  %c.sroa.0.0.i1035 = phi i32 [ %147, %bb6.i1055 ], [ 168, %bb29.i ]
  %_17.i1036 = icmp ugt i64 %d.i50, 4
  br i1 %_17.i1036, label %bb12.i1051, label %bb14.i1041

bb6.i1055:                                        ; preds = %bb29.i
  %_11.i1056 = add nsw i32 %_29.i987, -3
  %_10.i1057 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_11.i1056, i1 false)
  %146 = shl nuw nsw i32 %_10.i1057, 4
  %147 = sub nuw nsw i32 632, %146
  br label %bb7.i1034

bb12.i1051:                                       ; preds = %bb7.i1034
  %148 = trunc nuw i64 %d.i50 to i32
  %_22.i1049 = add nsw i32 %148, -1
  %_21.i1052 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_22.i1049, i1 true)
  %149 = shl nuw nsw i32 %_21.i1052, 4
  %reass.sub3255 = sub nsw i32 %c.sroa.0.0.i1035, %149
  %150 = add nsw i32 %reass.sub3255, 480
  br label %bb14.i1041

bb14.i1041:                                       ; preds = %bb7.i1034, %bb12.i1051
  %c.sroa.0.1.i1038 = phi i32 [ %150, %bb12.i1051 ], [ %c.sroa.0.0.i1035, %bb7.i1034 ]
  %151 = tail call { i32, i1 } @llvm.ssub.with.overflow.i32(i32 %_30.0.i990, i32 %c.sroa.0.1.i1038)
  %_31.1.i1043 = extractvalue { i32, i1 } %151, 1
  br i1 %_31.1.i1043, label %panic9.i1046, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1058

panic9.i1046:                                     ; preds = %bb14.i1041
; call core::panicking::panic_const::panic_const_sub_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_de42051d6ce5797cfcaece5556197823) #13
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1058: ; preds = %bb14.i1041
  %_31.0.i1045 = extractvalue { i32, i1 } %151, 0
  %152 = add nsw i64 %l.sroa.0.0.i3205, -11
  %or.cond.i1007 = icmp ult i64 %152, 247
  br i1 %or.cond.i1007, label %bb6.i1029, label %bb7.i1008

bb7.i1008:                                        ; preds = %bb6.i1029, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1058
  %c.sroa.0.0.i1009 = phi i32 [ %155, %bb6.i1029 ], [ 168, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1058 ]
  %_17.i1010 = icmp ugt i64 %d.sroa.0.0.i3204, 4
  br i1 %_17.i1010, label %bb8.i1022, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1032

bb6.i1029:                                        ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1058
  %153 = trunc nuw nsw i64 %l.sroa.0.0.i3205 to i32
  %_11.i1030 = add nsw i32 %153, -3
  %_10.i1031 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_11.i1030, i1 false)
  %154 = shl nuw nsw i32 %_10.i1031, 4
  %155 = sub nuw nsw i32 632, %154
  br label %bb7.i1008

bb8.i1022:                                        ; preds = %bb7.i1008
  %156 = trunc i64 %d.sroa.0.0.i3204 to i32
  %_22.i1023 = add i32 %156, -1
  %_25.1.i1024 = icmp ult i32 %_22.i1023, 2
  br i1 %_25.1.i1024, label %panic5.i1028, label %bb12.i1025

panic5.i1028:                                     ; preds = %bb8.i1022
; call core::panicking::panic_const::panic_const_sub_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_b85e9cb8887915fa95bd915ab181c13b) #13
  unreachable

bb12.i1025:                                       ; preds = %bb8.i1022
  %_21.i1026 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_22.i1023, i1 true)
  %157 = shl nuw nsw i32 %_21.i1026, 4
  %reass.sub3256 = sub nsw i32 %c.sroa.0.0.i1009, %157
  %158 = add nsw i32 %reass.sub3256, 480
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1032

_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1032: ; preds = %bb12.i1025, %bb7.i1008
  %c.sroa.0.1.i1012 = phi i32 [ %158, %bb12.i1025 ], [ %c.sroa.0.0.i1009, %bb7.i1008 ]
  %_29.i1013 = trunc nuw nsw i64 %l.sroa.0.0.i3205 to i32
  %_30.0.i1016 = shl nuw nsw i32 %_29.i1013, 6
  %159 = sub nsw i32 %_30.0.i1016, %c.sroa.0.1.i1012
  %_62.i = icmp sgt i32 %_31.0.i1045, %159
  br i1 %_62.i, label %bb32.i, label %bb35.i

bb32.i:                                           ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1032
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1648)
  %_9.i = icmp ult i64 %nt.sroa.0.5.i3206, %out.1
  br i1 %_9.i, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit, label %panic1.i295

panic1.i295:                                      ; preds = %bb32.i
  %nt.sroa.0.5.i3206.lcssa366 = phi i64 [ %nt.sroa.0.5.i3206, %bb32.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %nt.sroa.0.5.i3206.lcssa366, i64 noundef range(i64 0, 2305843009213693952) %out.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_f5cc78c6143d87a95e73f58df7e9bb32) #13, !noalias !1651
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit: ; preds = %bb32.i
  %_5.i = load i8, ptr %99, align 1, !alias.scope !1648, !noalias !1653, !noundef !136
  br label %bb59.i

bb39.i:                                           ; preds = %bb35.i
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1654)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1657)
  %_9.i379 = shl nuw nsw i64 %_14.i419, 24
  %_13.i386 = shl nuw nsw i64 %_20.i427, 16
  %_8.i387 = or disjoint i64 %_13.i386, %_9.i379
  %_19.i394 = shl nuw nsw i64 %_25.i435, 8
  %_7.i395 = or disjoint i64 %_8.i387, %_19.i394
  %160 = getelementptr inbounds nuw i8, ptr %99, i64 5
  %_26.i400 = load i8, ptr %160, align 1, !alias.scope !1659, !noalias !1662, !noundef !136
  %_25.i401 = zext i8 %_26.i400 to i64
  %161 = or disjoint i64 %_7.i395, %_25.i401
  %162 = mul i64 %161, -7046029254386353131
  %163 = lshr i64 %162, 48
  %164 = getelementptr inbounds nuw [4 x i8], ptr %head.i, i64 %163
  %old.i176.i = load i32, ptr %164, align 4, !alias.scope !1654, !noalias !1663, !noundef !136
  %_16.i177.i = and i64 %_51.0.i, 32767
  %165 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_16.i177.i
  store i32 %old.i176.i, ptr %165, align 4, !alias.scope !1657, !noalias !1665
  %166 = trunc nuw nsw i64 %_51.0.i to i32
  store i32 %166, ptr %164, align 4, !alias.scope !1654, !noalias !1663
  %_0.i178.i = zext i32 %old.i176.i to i64
  %_80.0.i = add nuw nsw i64 %p.sroa.0.5.i3203, 3
  %_84.0.i = sub nuw nsw i64 499998, %p.sroa.0.5.i3203
  %_81.i = icmp ult i64 %_56.0.i, %_84.0.i
  br i1 %_81.i, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_findKj8000_EB4_.exit, label %bb63.i

_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_findKj8000_EB4_.exit: ; preds = %bb39.i
  %spec.store.select3.i = tail call i64 @llvm.umin.i64(i64 %_84.0.i, i64 258)
  %_19.0.i95 = add nuw nsw i64 %spec.select.i10, %_51.0.i
  %_16.i96 = icmp ult i64 %_19.0.i95, 500000
  br i1 %_16.i96, label %bb7.i154, label %bb11.i107

bb7.i154:                                         ; preds = %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_findKj8000_EB4_.exit
  %167 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_19.0.i95
  %168 = load i8, ptr %167, align 1, !alias.scope !1666, !noalias !1669, !noundef !136
  br label %bb11.i107

bb11.i107:                                        ; preds = %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_findKj8000_EB4_.exit, %bb7.i154
  %pb.sroa.0.0.i98 = phi i8 [ %168, %bb7.i154 ], [ 0, %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_findKj8000_EB4_.exit ]
  %d.i108 = sub nsw i64 %_51.0.i, %_0.i178.i
  %_29.i109 = add nsw i64 %d.i108, -1
  %_28.i110 = icmp ult i64 %_29.i109, 32768
  br i1 %_28.i110, label %bb13.i121, label %bb63.i

bb13.i121:                                        ; preds = %bb11.i107
  %_34.0.i119 = add nuw nsw i64 %spec.select.i10, %_0.i178.i
  %_30.i122 = icmp ult i64 %_34.0.i119, 500000
  br i1 %_30.i122, label %bb16.i123, label %bb63.i

bb16.i123:                                        ; preds = %bb13.i121
  %169 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_34.0.i119
  %_36.i124 = load i8, ptr %169, align 1, !alias.scope !1666, !noalias !1669, !noundef !136
  %_35.i125 = icmp eq i8 %_36.i124, %pb.sroa.0.0.i98
  br i1 %_35.i125, label %bb2.i.preheader, label %bb63.i

bb2.i.preheader:                                  ; preds = %bb16.i123
  %170 = and i64 %spec.store.select3.i, 504
  br label %bb2.i

bb2.i:                                            ; preds = %bb2.i.preheader, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit895
  %k.sroa.0.0.i3189 = phi i64 [ %_10.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit895 ], [ 0, %bb2.i.preheader ]
  %_10.0.i = add nuw nsw i64 %k.sroa.0.0.i3189, 8
  %_7.not.i = icmp samesign ugt i64 %_10.0.i, %spec.store.select3.i
  br i1 %_7.not.i, label %bb17.i157, label %bb4.i

bb4.i:                                            ; preds = %bb2.i
  %_15.0.i169 = add nuw nsw i64 %k.sroa.0.0.i3189, %_0.i178.i
  %171 = icmp samesign ugt i64 %_15.0.i169, 499992
  br i1 %171, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit964, label %bb2.i900

bb17.i157:                                        ; preds = %bb2.i
  %_26.i3190.not = icmp eq i64 %170, %spec.store.select3.i
  br i1 %_26.i3190.not, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit, label %bb21.i161

bb2.i900:                                         ; preds = %bb4.i
  %172 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_15.0.i169
  %_15.i904 = load i8, ptr %172, align 1, !alias.scope !1671, !noalias !1669, !noundef !136
  %_14.i905 = zext i8 %_15.i904 to i64
  %_13.i906 = shl nuw i64 %_14.i905, 56
  %173 = getelementptr inbounds nuw i8, ptr %172, i64 1
  %_19.i911 = load i8, ptr %173, align 1, !alias.scope !1671, !noalias !1669, !noundef !136
  %_18.i912 = zext i8 %_19.i911 to i64
  %_17.i913 = shl nuw nsw i64 %_18.i912, 48
  %_12.i914 = or disjoint i64 %_17.i913, %_13.i906
  %174 = getelementptr inbounds nuw i8, ptr %172, i64 2
  %_25.i919 = load i8, ptr %174, align 1, !alias.scope !1671, !noalias !1669, !noundef !136
  %_24.i920 = zext i8 %_25.i919 to i64
  %_23.i921 = shl nuw nsw i64 %_24.i920, 40
  %_11.i922 = or disjoint i64 %_12.i914, %_23.i921
  %175 = getelementptr inbounds nuw i8, ptr %172, i64 3
  %_31.i927 = load i8, ptr %175, align 1, !alias.scope !1671, !noalias !1669, !noundef !136
  %_30.i928 = zext i8 %_31.i927 to i64
  %_29.i929 = shl nuw nsw i64 %_30.i928, 32
  %_10.i930 = or disjoint i64 %_11.i922, %_29.i929
  %176 = getelementptr inbounds nuw i8, ptr %172, i64 4
  %_37.i935 = load i8, ptr %176, align 1, !alias.scope !1671, !noalias !1669, !noundef !136
  %_36.i936 = zext i8 %_37.i935 to i64
  %_35.i937 = shl nuw nsw i64 %_36.i936, 24
  %_9.i938 = or disjoint i64 %_10.i930, %_35.i937
  %177 = getelementptr inbounds nuw i8, ptr %172, i64 5
  %_43.i943 = load i8, ptr %177, align 1, !alias.scope !1671, !noalias !1669, !noundef !136
  %_42.i944 = zext i8 %_43.i943 to i64
  %_41.i945 = shl nuw nsw i64 %_42.i944, 16
  %_8.i946 = or disjoint i64 %_9.i938, %_41.i945
  %178 = getelementptr inbounds nuw i8, ptr %172, i64 6
  %_49.i951 = load i8, ptr %178, align 1, !alias.scope !1671, !noalias !1669, !noundef !136
  %_48.i952 = zext i8 %_49.i951 to i64
  %_47.i953 = shl nuw nsw i64 %_48.i952, 8
  %_7.i954 = or i64 %_8.i946, %_47.i953
  %179 = getelementptr inbounds nuw i8, ptr %172, i64 7
  %_54.i959 = load i8, ptr %179, align 1, !alias.scope !1671, !noalias !1669, !noundef !136
  %_53.i960 = zext i8 %_54.i959 to i64
  %180 = or i64 %_7.i954, %_53.i960
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit964

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit964: ; preds = %bb4.i, %bb2.i900
  %_0.sroa.0.0.i962 = phi i64 [ %180, %bb2.i900 ], [ 0, %bb4.i ]
  %_19.0.i171 = add nuw i64 %k.sroa.0.0.i3189, %_51.0.i
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1674)
  %_5.1.i827 = icmp ugt i64 %_19.0.i171, -9
  br i1 %_5.1.i827, label %panic.i894, label %bb1.i828

bb1.i828:                                         ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit964
  %_3.not.i830 = icmp ugt i64 %_19.0.i171, 499992
  br i1 %_3.not.i830, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit895, label %bb2.i831

panic.i894:                                       ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit964
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_c9d76a7bf6f333d6169298e9d093a546) #13, !noalias !1677
  unreachable

bb2.i831:                                         ; preds = %bb1.i828
  %181 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_19.0.i171
  %_15.i835 = load i8, ptr %181, align 1, !alias.scope !1674, !noalias !1669, !noundef !136
  %_14.i836 = zext i8 %_15.i835 to i64
  %_13.i837 = shl nuw i64 %_14.i836, 56
  %182 = getelementptr inbounds nuw i8, ptr %181, i64 1
  %_19.i842 = load i8, ptr %182, align 1, !alias.scope !1674, !noalias !1669, !noundef !136
  %_18.i843 = zext i8 %_19.i842 to i64
  %_17.i844 = shl nuw nsw i64 %_18.i843, 48
  %_12.i845 = or disjoint i64 %_17.i844, %_13.i837
  %183 = getelementptr inbounds nuw i8, ptr %181, i64 2
  %_25.i850 = load i8, ptr %183, align 1, !alias.scope !1674, !noalias !1669, !noundef !136
  %_24.i851 = zext i8 %_25.i850 to i64
  %_23.i852 = shl nuw nsw i64 %_24.i851, 40
  %_11.i853 = or disjoint i64 %_12.i845, %_23.i852
  %184 = getelementptr inbounds nuw i8, ptr %181, i64 3
  %_31.i858 = load i8, ptr %184, align 1, !alias.scope !1674, !noalias !1669, !noundef !136
  %_30.i859 = zext i8 %_31.i858 to i64
  %_29.i860 = shl nuw nsw i64 %_30.i859, 32
  %_10.i861 = or disjoint i64 %_11.i853, %_29.i860
  %185 = getelementptr inbounds nuw i8, ptr %181, i64 4
  %_37.i866 = load i8, ptr %185, align 1, !alias.scope !1674, !noalias !1669, !noundef !136
  %_36.i867 = zext i8 %_37.i866 to i64
  %_35.i868 = shl nuw nsw i64 %_36.i867, 24
  %_9.i869 = or disjoint i64 %_10.i861, %_35.i868
  %186 = getelementptr inbounds nuw i8, ptr %181, i64 5
  %_43.i874 = load i8, ptr %186, align 1, !alias.scope !1674, !noalias !1669, !noundef !136
  %_42.i875 = zext i8 %_43.i874 to i64
  %_41.i876 = shl nuw nsw i64 %_42.i875, 16
  %_8.i877 = or disjoint i64 %_9.i869, %_41.i876
  %187 = getelementptr inbounds nuw i8, ptr %181, i64 6
  %_49.i882 = load i8, ptr %187, align 1, !alias.scope !1674, !noalias !1669, !noundef !136
  %_48.i883 = zext i8 %_49.i882 to i64
  %_47.i884 = shl nuw nsw i64 %_48.i883, 8
  %_7.i885 = or i64 %_8.i877, %_47.i884
  %188 = getelementptr inbounds nuw i8, ptr %181, i64 7
  %_54.i890 = load i8, ptr %188, align 1, !alias.scope !1674, !noalias !1669, !noundef !136
  %_53.i891 = zext i8 %_54.i890 to i64
  %189 = or i64 %_7.i885, %_53.i891
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit895

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit895: ; preds = %bb1.i828, %bb2.i831
  %_0.sroa.0.0.i893 = phi i64 [ %189, %bb2.i831 ], [ 0, %bb1.i828 ]
  %190 = icmp eq i64 %_0.sroa.0.0.i962, %_0.sroa.0.0.i893
  br i1 %190, label %bb2.i, label %bb17.i157.thread

bb17.i157.thread:                                 ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit895
  %_0.sroa.0.0.i893.lcssa = phi i64 [ %_0.sroa.0.0.i893, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit895 ]
  %_0.sroa.0.0.i962.lcssa355 = phi i64 [ %_0.sroa.0.0.i962, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit895 ]
  %k.sroa.0.0.i3189.lcssa354 = phi i64 [ %k.sroa.0.0.i3189, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit895 ]
  %x.i = xor i64 %_0.sroa.0.0.i893.lcssa, %_0.sroa.0.0.i962.lcssa355
  %191 = tail call range(i64 0, 65) i64 @llvm.ctlz.i64(i64 %x.i, i1 true)
  %_2220.i = lshr i64 %191, 3
  %_24.0.i = or disjoint i64 %_2220.i, %k.sroa.0.0.i3189.lcssa354
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit

bb21.i161:                                        ; preds = %bb17.i157, %bb24.i
  %k.sroa.0.2.i3192 = phi i64 [ %k.sroa.0.3.i, %bb24.i ], [ %170, %bb17.i157 ]
  %_32.0.i = add nuw nsw i64 %k.sroa.0.2.i3192, %_0.i178.i
  %_34.i = icmp samesign ult i64 %_32.0.i, 500000
  br i1 %_34.i, label %bb23.i, label %panic6.i

panic6.i:                                         ; preds = %bb21.i161
  %_32.0.i.lcssa = phi i64 [ %_32.0.i, %bb21.i161 ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_32.0.i.lcssa, i64 noundef range(i64 0, -9223372036854775808) 500000, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_88632784907d7d84d4dbb3c61bd04ae5) #13, !noalias !1669
  unreachable

bb23.i:                                           ; preds = %bb21.i161
  %_38.0.i = add nuw nsw i64 %k.sroa.0.2.i3192, %_51.0.i
  %_39.i163 = icmp ult i64 %_38.0.i, 500000
  br i1 %_39.i163, label %bb24.i, label %panic8.i

bb24.i:                                           ; preds = %bb23.i
  %192 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_32.0.i
  %_29.i162 = load i8, ptr %192, align 1, !alias.scope !1678, !noalias !1669, !noundef !136
  %193 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_38.0.i
  %_35.i164 = load i8, ptr %193, align 1, !alias.scope !1678, !noalias !1669, !noundef !136
  %_28.i165 = icmp eq i8 %_29.i162, %_35.i164
  %_40.0.i = zext i1 %_28.i165 to i64
  %k.sroa.0.3.i = add nuw nsw i64 %k.sroa.0.2.i3192, %_40.0.i
  %_26.i = icmp samesign ult i64 %k.sroa.0.3.i, %spec.store.select3.i
  %or.cond.i159 = select i1 %_28.i165, i1 %_26.i, i1 false
  br i1 %or.cond.i159, label %bb21.i161, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit

panic8.i:                                         ; preds = %bb23.i
  %_38.0.i.lcssa = phi i64 [ %_38.0.i, %bb23.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_38.0.i.lcssa, i64 noundef range(i64 0, -9223372036854775808) 500000, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_45688f0cd226461942a9ccd1c478fc80) #13, !noalias !1669
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit: ; preds = %bb24.i, %bb17.i157.thread, %bb17.i157
  %k.sroa.0.2.i.lcssa = phi i64 [ %170, %bb17.i157 ], [ %_24.0.i, %bb17.i157.thread ], [ %k.sroa.0.3.i, %bb24.i ]
  %_46.i140 = icmp ugt i64 %k.sroa.0.2.i.lcssa, %spec.select.i10
  br i1 %_46.i140, label %bb19.i141, label %bb63.i

bb19.i141:                                        ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit
  %194 = add i64 %k.sroa.0.2.i.lcssa, -11
  %or.cond.i965 = icmp ult i64 %194, 247
  br i1 %or.cond.i965, label %bb6.i, label %bb7.i966

bb7.i966:                                         ; preds = %bb6.i, %bb19.i141
  %c.sroa.0.0.i = phi i32 [ %197, %bb6.i ], [ 168, %bb19.i141 ]
  %_17.i967 = icmp ugt i64 %d.i108, 4
  br i1 %_17.i967, label %bb12.i976, label %bb13.i968

bb6.i:                                            ; preds = %bb19.i141
  %195 = trunc nuw nsw i64 %k.sroa.0.2.i.lcssa to i32
  %_11.i979 = add nsw i32 %195, -3
  %_10.i980 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_11.i979, i1 false)
  %196 = shl nuw nsw i32 %_10.i980, 4
  %197 = sub nuw nsw i32 632, %196
  br label %bb7.i966

bb13.i968:                                        ; preds = %bb12.i976, %bb7.i966
  %c.sroa.0.1.i = phi i32 [ %201, %bb12.i976 ], [ %c.sroa.0.0.i, %bb7.i966 ]
  %_29.i969 = trunc i64 %k.sroa.0.2.i.lcssa to i32
  %198 = add i32 %_29.i969, -33554432
  %_30.1.i = icmp ult i32 %198, -67108864
  br i1 %_30.1.i, label %panic8.i973, label %bb14.i970

bb12.i976:                                        ; preds = %bb7.i966
  %199 = trunc nuw i64 %d.i108 to i32
  %_22.i975 = add nsw i32 %199, -1
  %_21.i977 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_22.i975, i1 true)
  %200 = shl nuw nsw i32 %_21.i977, 4
  %reass.sub3257 = sub nsw i32 %c.sroa.0.0.i, %200
  %201 = add nsw i32 %reass.sub3257, 480
  br label %bb13.i968

bb14.i970:                                        ; preds = %bb13.i968
  %_30.0.i = shl nsw i32 %_29.i969, 6
  %202 = tail call { i32, i1 } @llvm.ssub.with.overflow.i32(i32 %_30.0.i, i32 %c.sroa.0.1.i)
  %_31.1.i = extractvalue { i32, i1 } %202, 1
  br i1 %_31.1.i, label %panic9.i972, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit155

panic8.i973:                                      ; preds = %bb13.i968
; call core::panicking::panic_const::panic_const_mul_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_mul_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_de42051d6ce5797cfcaece5556197823) #13, !noalias !1669
  unreachable

panic9.i972:                                      ; preds = %bb14.i970
; call core::panicking::panic_const::panic_const_sub_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_de42051d6ce5797cfcaece5556197823) #13, !noalias !1669
  unreachable

_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit155: ; preds = %bb14.i970
  %_31.0.i = extractvalue { i32, i1 } %202, 0
  %_49.i143 = icmp sgt i32 %_31.0.i, -1000000
  %spec.select = select i1 %_49.i143, i64 %d.i108, i64 0
  %spec.select3704 = select i1 %_49.i143, i64 %k.sroa.0.2.i.lcssa, i64 %spec.select.i10
  %203 = freeze i64 %spec.select
  %204 = icmp ne i64 %203, 0
  %_87.i = icmp ugt i64 %spec.select3704, 3
  %or.cond3700 = and i1 %204, %_87.i
  br i1 %or.cond3700, label %bb45.i, label %bb63.i

bb45.i:                                           ; preds = %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit155
  %205 = add i64 %spec.select3704, -11
  %or.cond.i1085 = icmp ult i64 %205, 247
  br i1 %or.cond.i1085, label %bb6.i1107, label %bb7.i1086

bb7.i1086:                                        ; preds = %bb6.i1107, %bb45.i
  %c.sroa.0.0.i1087 = phi i32 [ %208, %bb6.i1107 ], [ 168, %bb45.i ]
  %_17.i1088 = icmp ugt i64 %203, 4
  br i1 %_17.i1088, label %bb12.i1103, label %bb13.i1089

bb6.i1107:                                        ; preds = %bb45.i
  %206 = trunc nuw nsw i64 %spec.select3704 to i32
  %_11.i1108 = add nsw i32 %206, -3
  %_10.i1109 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_11.i1108, i1 false)
  %207 = shl nuw nsw i32 %_10.i1109, 4
  %208 = sub nuw nsw i32 632, %207
  br label %bb7.i1086

bb13.i1089:                                       ; preds = %bb12.i1103, %bb7.i1086
  %c.sroa.0.1.i1090 = phi i32 [ %212, %bb12.i1103 ], [ %c.sroa.0.0.i1087, %bb7.i1086 ]
  %_29.i1091 = trunc i64 %spec.select3704 to i32
  %209 = add i32 %_29.i1091, -33554432
  %_30.1.i1092 = icmp ult i32 %209, -67108864
  br i1 %_30.1.i1092, label %panic8.i1099, label %bb14.i1093

bb12.i1103:                                       ; preds = %bb7.i1086
  %210 = trunc nuw i64 %203 to i32
  %_22.i1101 = add nsw i32 %210, -1
  %_21.i1104 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_22.i1101, i1 true)
  %211 = shl nuw nsw i32 %_21.i1104, 4
  %reass.sub3258 = sub nsw i32 %c.sroa.0.0.i1087, %211
  %212 = add nsw i32 %reass.sub3258, 480
  br label %bb13.i1089

bb14.i1093:                                       ; preds = %bb13.i1089
  %_30.0.i1094 = shl nsw i32 %_29.i1091, 6
  %213 = tail call { i32, i1 } @llvm.ssub.with.overflow.i32(i32 %_30.0.i1094, i32 %c.sroa.0.1.i1090)
  %_31.1.i1095 = extractvalue { i32, i1 } %213, 1
  br i1 %_31.1.i1095, label %panic9.i1098, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1110

panic8.i1099:                                     ; preds = %bb13.i1089
; call core::panicking::panic_const::panic_const_mul_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_mul_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_de42051d6ce5797cfcaece5556197823) #13
  unreachable

panic9.i1098:                                     ; preds = %bb14.i1093
; call core::panicking::panic_const::panic_const_sub_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_de42051d6ce5797cfcaece5556197823) #13
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1110: ; preds = %bb14.i1093
  %_31.0.i1097 = extractvalue { i32, i1 } %213, 0
  %214 = add nsw i64 %l.sroa.0.0.i3205, -11
  %or.cond.i1059 = icmp ult i64 %214, 247
  br i1 %or.cond.i1059, label %bb6.i1081, label %bb7.i1060

bb7.i1060:                                        ; preds = %bb6.i1081, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1110
  %c.sroa.0.0.i1061 = phi i32 [ %217, %bb6.i1081 ], [ 168, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1110 ]
  %_17.i1062 = icmp ugt i64 %d.sroa.0.0.i3204, 4
  br i1 %_17.i1062, label %bb8.i1074, label %bb48.i

bb6.i1081:                                        ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1110
  %215 = trunc nuw nsw i64 %l.sroa.0.0.i3205 to i32
  %_11.i1082 = add nsw i32 %215, -3
  %_10.i1083 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_11.i1082, i1 false)
  %216 = shl nuw nsw i32 %_10.i1083, 4
  %217 = sub nuw nsw i32 632, %216
  br label %bb7.i1060

bb8.i1074:                                        ; preds = %bb7.i1060
  %218 = trunc i64 %d.sroa.0.0.i3204 to i32
  %_22.i1075 = add i32 %218, -1
  %_25.1.i1076 = icmp ult i32 %_22.i1075, 2
  br i1 %_25.1.i1076, label %panic5.i1080, label %bb12.i1077

panic5.i1080:                                     ; preds = %bb8.i1074
; call core::panicking::panic_const::panic_const_sub_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_b85e9cb8887915fa95bd915ab181c13b) #13
  unreachable

bb12.i1077:                                       ; preds = %bb8.i1074
  %_21.i1078 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_22.i1075, i1 true)
  %219 = shl nuw nsw i32 %_21.i1078, 4
  %reass.sub3259 = sub nsw i32 %c.sroa.0.0.i1061, %219
  %220 = add nsw i32 %reass.sub3259, 480
  br label %bb48.i

bb48.i:                                           ; preds = %bb7.i1060, %bb12.i1077
  %c.sroa.0.1.i1064 = phi i32 [ %220, %bb12.i1077 ], [ %c.sroa.0.0.i1061, %bb7.i1060 ]
  %_29.i1065 = trunc nuw nsw i64 %l.sroa.0.0.i3205 to i32
  %_30.0.i1068 = shl nuw nsw i32 %_29.i1065, 6
  %221 = or disjoint i32 %_30.0.i1068, 40
  %222 = sub nsw i32 %221, %c.sroa.0.1.i1064
  %_89.i = icmp sgt i32 %_31.0.i1097, %222
  br i1 %_89.i, label %bb49.i, label %bb63.i

bb49.i:                                           ; preds = %bb48.i
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1681)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1684)
  %_9.i310 = icmp ult i64 %nt.sroa.0.5.i3206, %out.1
  br i1 %_9.i310, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit315, label %panic1.i311

panic1.i311:                                      ; preds = %bb49.i
  %nt.sroa.0.5.i3206.lcssa375 = phi i64 [ %nt.sroa.0.5.i3206, %bb49.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %nt.sroa.0.5.i3206.lcssa375, i64 noundef range(i64 0, 2305843009213693952) %out.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_f5cc78c6143d87a95e73f58df7e9bb32) #13, !noalias !1686
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit315: ; preds = %bb49.i
  %_5.i313 = load i8, ptr %99, align 1, !alias.scope !1681, !noalias !1684, !noundef !136
  %223 = getelementptr inbounds nuw [4 x i8], ptr %out.0, i64 %nt.sroa.0.5.i3206
  %224 = zext i8 %_5.i313 to i32
  store i32 %224, ptr %223, align 4, !alias.scope !1684, !noalias !1681
  %_10.0.i314 = add nuw nsw i64 %nt.sroa.0.5.i3206, 1
  %_9.i301 = icmp ult i64 %_10.0.i314, %out.1
  br i1 %_9.i301, label %bb59.i, label %panic1.i302

panic1.i302:                                      ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit315
  %_10.0.i314.lcssa = phi i64 [ %_10.0.i314, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit315 ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_10.0.i314.lcssa, i64 noundef range(i64 0, 2305843009213693952) %out.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_f5cc78c6143d87a95e73f58df7e9bb32) #13, !noalias !1687
  unreachable

bb59.i:                                           ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit315, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit
  %_10.0.i314.sink = phi i64 [ %nt.sroa.0.5.i3206, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit ], [ %_10.0.i314, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit315 ]
  %_11.i411.sink = phi i8 [ %_5.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit ], [ %_11.i411, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit315 ]
  %.sink = phi i64 [ 1, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit ], [ 2, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit315 ]
  %ins.sroa.0.5.i = phi i64 [ %_51.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit ], [ %_80.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit315 ]
  %p.sroa.0.6.i = phi i64 [ %_44.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit ], [ %_51.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit315 ]
  %d.sroa.0.1.i = phi i64 [ %d.i50, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit ], [ %203, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit315 ]
  %l.sroa.0.1.i = phi i64 [ %k.sroa.0.2.i183.lcssa, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit ], [ %spec.select3704, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit315 ]
  %225 = getelementptr inbounds nuw [4 x i8], ptr %out.0, i64 %_10.0.i314.sink
  %226 = zext i8 %_11.i411.sink to i32
  store i32 %226, ptr %225, align 4, !noalias !136
  %_10.0.i305 = add nuw nsw i64 %nt.sroa.0.5.i3206, %.sink
  %_39.i = icmp ult i64 %l.sroa.0.1.i, 32
  br i1 %_39.i, label %bb18.i, label %bb63.i

bb116.i:                                          ; preds = %bb110.i, %bb63.i
  %p.sroa.0.7.i.lcssa = phi i64 [ %p.sroa.0.5.i.lcssa, %bb63.i ], [ %p.sroa.0.8.i, %bb110.i ]
  %l.sroa.0.2.i.lcssa = phi i64 [ %l.sroa.0.0.i.lcssa, %bb63.i ], [ %l.sroa.0.3.i, %bb110.i ]
  %nt.sroa.0.7.i.lcssa = phi i64 [ %nt.sroa.0.5.i.lcssa, %bb63.i ], [ %nt.sroa.0.8.i, %bb110.i ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1691)
  %_15.i = icmp samesign ult i64 %nt.sroa.0.7.i.lcssa, %out.1
  br i1 %_15.i, label %bb1.i344, label %panic.i343

bb1.i344:                                         ; preds = %bb116.i
  %227 = trunc i64 %l.sroa.0.2.i.lcssa to i32
  %228 = trunc i64 %d.sroa.0.0.i.lcssa to i32
  %_10.i = shl i32 %228, 8
  %_12.i345 = add i32 %_10.i, 16776957
  %_7.i346 = add i32 %_12.i345, %227
  %229 = getelementptr inbounds nuw [4 x i8], ptr %out.0, i64 %nt.sroa.0.7.i.lcssa
  store i32 %_7.i346, ptr %229, align 4, !alias.scope !1691
  %_19.0.i347 = add i64 %l.sroa.0.2.i.lcssa, %p.sroa.0.7.i.lcssa
  %_19.1.i348 = icmp ult i64 %_19.0.i347, %p.sroa.0.7.i.lcssa
  br i1 %_19.1.i348, label %panic2.i350, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse14u118_put_match.exit

panic.i343:                                       ; preds = %bb116.i
  %nt.sroa.0.7.i.lcssa.lcssa = phi i64 [ %nt.sroa.0.7.i.lcssa, %bb116.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef range(i64 0, 2305843009213693952) %nt.sroa.0.7.i.lcssa.lcssa, i64 noundef range(i64 0, 2305843009213693952) %out.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_771dc0d324c573869d9faceafd4f8e56) #13, !noalias !1691
  unreachable

panic2.i350:                                      ; preds = %bb1.i344
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_86c5a99bb83ebb25fc53357ef56f8fe2) #13, !noalias !1691
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse14u118_put_match.exit: ; preds = %bb1.i344
  %_17.0.i = add nuw nsw i64 %nt.sroa.0.7.i.lcssa, 1
  %_175.i = add nuw i64 %ins.sroa.0.4.i.lcssa, 16
  %spec.select148.i = tail call i64 @llvm.umin.i64(i64 %_19.0.i347, i64 %_175.i)
  %spec.store.select50.i = tail call i64 @llvm.umin.i64(i64 %spec.select148.i, i64 499992)
  %_181.i3232 = icmp ult i64 %ins.sroa.0.4.i.lcssa, %spec.store.select50.i
  br i1 %_181.i3232, label %bb125.i, label %bb129.i

bb125.i:                                          ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse14u118_put_match.exit, %bb125.i
  %ins.sroa.0.6.i3233 = phi i64 [ %_188.0.i, %bb125.i ], [ %ins.sroa.0.4.i.lcssa, %_RNvNtCs2hd9JHJjR4I_9candidate5parse14u118_put_match.exit ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1694)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1697)
  %230 = getelementptr inbounds nuw i8, ptr %input.0, i64 %ins.sroa.0.6.i3233
  %231 = load i32, ptr %230, align 1
  %232 = call i32 @llvm.bswap.i32(i32 %231)
  %233 = zext i32 %232 to i64
  %234 = mul i64 %233, -7046029254386353131
  %235 = lshr i64 %234, 48
  %236 = getelementptr inbounds nuw [4 x i8], ptr %head.i, i64 %235
  %old.i155.i = load i32, ptr %236, align 4, !alias.scope !1694, !noalias !1699, !noundef !136
  %_16.i156.i = and i64 %ins.sroa.0.6.i3233, 32767
  %237 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_16.i156.i
  store i32 %old.i155.i, ptr %237, align 4, !alias.scope !1697, !noalias !1701
  %238 = trunc i64 %ins.sroa.0.6.i3233 to i32
  store i32 %238, ptr %236, align 4, !alias.scope !1694, !noalias !1699
  %_188.0.i = add nuw i64 %ins.sroa.0.6.i3233, 1
  %exitcond3445.not = icmp eq i64 %_188.0.i, %spec.store.select50.i
  br i1 %exitcond3445.not, label %bb129.i, label %bb125.i

bb129.i:                                          ; preds = %bb125.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse14u118_put_match.exit
  %ins.sroa.0.6.i.lcssa = phi i64 [ %ins.sroa.0.4.i.lcssa, %_RNvNtCs2hd9JHJjR4I_9candidate5parse14u118_put_match.exit ], [ %spec.store.select50.i, %bb125.i ]
  %e2.i = tail call i64 @llvm.usub.sat.i64(i64 %_19.0.i347, i64 8)
  %invariant.umin = tail call i64 @llvm.umin.i64(i64 %e2.i, i64 499992)
  %or.cond51.i3235 = icmp ult i64 %ins.sroa.0.6.i.lcssa, %invariant.umin
  br i1 %or.cond51.i3235, label %bb132.i, label %bb138.i

bb132.i:                                          ; preds = %bb129.i, %bb132.i
  %ins.sroa.0.7.i3236 = phi i64 [ %_5.0.i473, %bb132.i ], [ %ins.sroa.0.6.i.lcssa, %bb129.i ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1702)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1705)
  %_5.0.i473 = add nuw nsw i64 %ins.sroa.0.7.i3236, 4
  %239 = getelementptr inbounds nuw i8, ptr %input.0, i64 %ins.sroa.0.7.i3236
  %240 = load i32, ptr %239, align 1
  %241 = call i32 @llvm.bswap.i32(i32 %240)
  %242 = zext i32 %241 to i64
  %243 = mul i64 %242, -7046029254386353131
  %244 = lshr i64 %243, 48
  %245 = getelementptr inbounds nuw [4 x i8], ptr %head.i, i64 %244
  %old.i162.i = load i32, ptr %245, align 4, !alias.scope !1702, !noalias !1707, !noundef !136
  %_16.i163.i = and i64 %ins.sroa.0.7.i3236, 32767
  %246 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_16.i163.i
  store i32 %old.i162.i, ptr %246, align 4, !alias.scope !1705, !noalias !1709
  %247 = trunc i64 %ins.sroa.0.7.i3236 to i32
  store i32 %247, ptr %245, align 4, !alias.scope !1702, !noalias !1707
  %or.cond51.i = icmp ult i64 %_5.0.i473, %invariant.umin
  br i1 %or.cond51.i, label %bb132.i, label %bb138.i

bb138.i:                                          ; preds = %bb132.i, %bb129.i
  %ins.sroa.0.7.i.lcssa = phi i64 [ %ins.sroa.0.6.i.lcssa, %bb129.i ], [ %_5.0.i473, %bb132.i ]
  %_202.i = add i64 %ins.sroa.0.7.i.lcssa, 4
  %_201.i = icmp ult i64 %_202.i, %_19.0.i347
  br i1 %_201.i, label %bb139.i, label %bb142.i

bb139.i:                                          ; preds = %bb138.i
  %_204.1.i = icmp ult i64 %_19.0.i347, 4
  br i1 %_204.1.i, label %panic18.i, label %bb140.i

bb142.i:                                          ; preds = %bb140.i, %bb138.i
  %ins.sroa.0.8.i = phi i64 [ %_204.0.i, %bb140.i ], [ %ins.sroa.0.7.i.lcssa, %bb138.i ]
  %invariant.umin3238 = tail call i64 @llvm.umin.i64(i64 %_19.0.i347, i64 499992)
  %or.cond52.i3239 = icmp ult i64 %ins.sroa.0.8.i, %invariant.umin3238
  br i1 %or.cond52.i3239, label %bb145.i, label %bb150.i

bb140.i:                                          ; preds = %bb139.i
  %_204.0.i = add i64 %_19.0.i347, -4
  br label %bb142.i

panic18.i:                                        ; preds = %bb139.i
; call core::panicking::panic_const::panic_const_sub_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_314029bb05064e5fe6e525f4ab2e737b) #13
  unreachable

bb150.i:                                          ; preds = %bb145.i, %bb142.i
  %ins.sroa.0.9.i.lcssa = phi i64 [ %ins.sroa.0.8.i, %bb142.i ], [ %_213.0.i, %bb145.i ]
  %spec.select150.i = tail call i64 @llvm.umax.i64(i64 %ins.sroa.0.9.i.lcssa, i64 %_19.0.i347)
  br label %bb174.i

bb145.i:                                          ; preds = %bb142.i, %bb145.i
  %ins.sroa.0.9.i3240 = phi i64 [ %_213.0.i, %bb145.i ], [ %ins.sroa.0.8.i, %bb142.i ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1710)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1713)
  %248 = getelementptr inbounds nuw i8, ptr %input.0, i64 %ins.sroa.0.9.i3240
  %249 = load i32, ptr %248, align 1
  %250 = call i32 @llvm.bswap.i32(i32 %249)
  %251 = zext i32 %250 to i64
  %252 = mul i64 %251, -7046029254386353131
  %253 = lshr i64 %252, 48
  %254 = getelementptr inbounds nuw [4 x i8], ptr %head.i, i64 %253
  %old.i169.i = load i32, ptr %254, align 4, !alias.scope !1710, !noalias !1715, !noundef !136
  %_16.i170.i = and i64 %ins.sroa.0.9.i3240, 32767
  %255 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_16.i170.i
  store i32 %old.i169.i, ptr %255, align 4, !alias.scope !1713, !noalias !1717
  %256 = trunc i64 %ins.sroa.0.9.i3240 to i32
  store i32 %256, ptr %254, align 4, !alias.scope !1710, !noalias !1715
  %_213.0.i = add nuw nsw i64 %ins.sroa.0.9.i3240, 1
  %or.cond52.i = icmp ult i64 %_213.0.i, %invariant.umin3238
  br i1 %or.cond52.i, label %bb145.i, label %bb150.i

bb71.i:                                           ; preds = %bb63.i, %bb110.i
  %257 = phi i64 [ %305, %bb110.i ], [ %96, %bb63.i ]
  %nt.sroa.0.7.i3228 = phi i64 [ %nt.sroa.0.8.i, %bb110.i ], [ %nt.sroa.0.5.i.lcssa, %bb63.i ]
  %l.sroa.0.2.i3227 = phi i64 [ %l.sroa.0.3.i, %bb110.i ], [ %l.sroa.0.0.i.lcssa, %bb63.i ]
  %back.sroa.0.0.i3226 = phi i64 [ %back.sroa.0.1.i, %bb110.i ], [ 0, %bb63.i ]
  %p.sroa.0.7.i3225 = phi i64 [ %p.sroa.0.8.i, %bb110.i ], [ %p.sroa.0.5.i.lcssa, %bb63.i ]
  %258 = getelementptr inbounds nuw [4 x i8], ptr %out.0, i64 %257
  %t.i = load i32, ptr %258, align 4, !alias.scope !1561, !noalias !1558, !noundef !136
  %_120.i = icmp ult i32 %t.i, 256
  br i1 %_120.i, label %bb72.i, label %bb84.i

bb84.i:                                           ; preds = %bb71.i
  %_139.i = icmp ugt i32 %t.i, 16777215
  br i1 %_139.i, label %bb87.i, label %bb110.i

bb72.i:                                           ; preds = %bb71.i
  %_125.0.i = add i64 %p.sroa.0.7.i3225, -1
  %_126.i = icmp ult i64 %_125.0.i, 500000
  br i1 %_126.i, label %bb74.i, label %panic25.i

bb74.i:                                           ; preds = %bb72.i
  %_133.0.i = sub i64 %_125.0.i, %d.sroa.0.0.i.lcssa
  %_134.i = icmp ult i64 %_133.0.i, 500000
  br i1 %_134.i, label %bb77.i, label %panic28.i

panic25.i:                                        ; preds = %bb72.i
  %_125.0.i.lcssa = phi i64 [ %_125.0.i, %bb72.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_125.0.i.lcssa, i64 noundef range(i64 0, -9223372036854775808) 500000, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_a9b07c74cfde78097f4604099b753106) #13
  unreachable

bb77.i:                                           ; preds = %bb74.i
  %259 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_125.0.i
  %_122.i = load i8, ptr %259, align 1, !alias.scope !1558, !noalias !1561, !noundef !136
  %260 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_133.0.i
  %_127.i = load i8, ptr %260, align 1, !alias.scope !1558, !noalias !1561, !noundef !136
  %_121.i = icmp eq i8 %_122.i, %_127.i
  br i1 %_121.i, label %bb80.i, label %bb110.i

panic28.i:                                        ; preds = %bb74.i
  %_133.0.i.lcssa = phi i64 [ %_133.0.i, %bb74.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_133.0.i.lcssa, i64 noundef range(i64 0, -9223372036854775808) 500000, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_cd6670e2db87759322e29f99bddfa067) #13
  unreachable

bb87.i:                                           ; preds = %bb84.i
  %_142.i = and i32 %t.i, 255
  %_145.0.i = add nuw nsw i32 %_142.i, 3
  %w.i = zext nneg i32 %_145.0.i to i64
  %_149.0.i = add nuw nsw i64 %l.sroa.0.2.i3227, %w.i
  %_146.i = icmp samesign ult i64 %_149.0.i, 259
  %_150.i = icmp uge i64 %p.sroa.0.7.i3225, %w.i
  %or.cond53.i = select i1 %_146.i, i1 %_150.i, i1 false
  br i1 %or.cond53.i, label %bb90.i, label %bb110.i

bb90.i:                                           ; preds = %bb87.i
  %_156.0.i = sub nuw i64 %p.sroa.0.7.i3225, %w.i
  %_152.not.i = icmp ugt i64 %d.sroa.0.0.i.lcssa, %_156.0.i
  br i1 %_152.not.i, label %bb110.i, label %bb95.i

bb95.i:                                           ; preds = %bb90.i
  %_163.0.i = sub nuw i64 %_156.0.i, %d.sroa.0.0.i.lcssa
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1718)
  %261 = and i64 %w.i, 504
  br label %bb2.i1151

bb2.i1151:                                        ; preds = %bb95.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i
  %k.sroa.0.0.i11123217 = phi i64 [ 0, %bb95.i ], [ %_11.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i ]
  %_11.0.i = add nuw nsw i64 %k.sroa.0.0.i11123217, 8
  %_8.not.i = icmp samesign ugt i64 %_11.0.i, %w.i
  br i1 %_8.not.i, label %bb15.i1113, label %bb4.i1153

bb4.i1153:                                        ; preds = %bb2.i1151
  %_16.0.i = add nuw i64 %k.sroa.0.0.i11123217, %_163.0.i
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1721)
  %_5.1.i172.i = icmp ugt i64 %_16.0.i, -9
  br i1 %_5.1.i172.i, label %panic.i238.i, label %bb1.i173.i

bb15.i1113:                                       ; preds = %bb2.i1151
  %_23.i1114.not = icmp eq i64 %261, %w.i
  br i1 %_23.i1114.not, label %bb101.i, label %bb18.i1116

bb1.i173.i:                                       ; preds = %bb4.i1153
  %262 = icmp ugt i64 %_16.0.i, 499992
  br i1 %262, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit239.i, label %bb2.i176.i

panic.i238.i:                                     ; preds = %bb4.i1153
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_c9d76a7bf6f333d6169298e9d093a546) #13, !noalias !1724
  unreachable

bb2.i176.i:                                       ; preds = %bb1.i173.i
  %263 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_16.0.i
  %_15.i180.i = load i8, ptr %263, align 1, !alias.scope !1724, !noundef !136
  %_14.i181.i = zext i8 %_15.i180.i to i64
  %_13.i182.i = shl nuw i64 %_14.i181.i, 56
  %264 = getelementptr inbounds nuw i8, ptr %263, i64 1
  %_19.i187.i = load i8, ptr %264, align 1, !alias.scope !1724, !noundef !136
  %_18.i188.i = zext i8 %_19.i187.i to i64
  %_17.i189.i = shl nuw nsw i64 %_18.i188.i, 48
  %_12.i190.i = or disjoint i64 %_17.i189.i, %_13.i182.i
  %265 = getelementptr inbounds nuw i8, ptr %263, i64 2
  %_25.i195.i = load i8, ptr %265, align 1, !alias.scope !1724, !noundef !136
  %_24.i196.i = zext i8 %_25.i195.i to i64
  %_23.i197.i = shl nuw nsw i64 %_24.i196.i, 40
  %_11.i198.i = or disjoint i64 %_12.i190.i, %_23.i197.i
  %266 = getelementptr inbounds nuw i8, ptr %263, i64 3
  %_31.i203.i = load i8, ptr %266, align 1, !alias.scope !1724, !noundef !136
  %_30.i204.i = zext i8 %_31.i203.i to i64
  %_29.i205.i = shl nuw nsw i64 %_30.i204.i, 32
  %_10.i206.i = or disjoint i64 %_11.i198.i, %_29.i205.i
  %267 = getelementptr inbounds nuw i8, ptr %263, i64 4
  %_37.i211.i = load i8, ptr %267, align 1, !alias.scope !1724, !noundef !136
  %_36.i212.i = zext i8 %_37.i211.i to i64
  %_35.i213.i = shl nuw nsw i64 %_36.i212.i, 24
  %_9.i214.i = or disjoint i64 %_10.i206.i, %_35.i213.i
  %268 = getelementptr inbounds nuw i8, ptr %263, i64 5
  %_43.i219.i = load i8, ptr %268, align 1, !alias.scope !1724, !noundef !136
  %_42.i220.i = zext i8 %_43.i219.i to i64
  %_41.i221.i = shl nuw nsw i64 %_42.i220.i, 16
  %_8.i222.i = or disjoint i64 %_9.i214.i, %_41.i221.i
  %269 = getelementptr inbounds nuw i8, ptr %263, i64 6
  %_49.i227.i = load i8, ptr %269, align 1, !alias.scope !1724, !noundef !136
  %_48.i228.i = zext i8 %_49.i227.i to i64
  %_47.i229.i = shl nuw nsw i64 %_48.i228.i, 8
  %_7.i230.i = or i64 %_8.i222.i, %_47.i229.i
  %270 = getelementptr inbounds nuw i8, ptr %263, i64 7
  %_54.i235.i = load i8, ptr %270, align 1, !alias.scope !1724, !noundef !136
  %_53.i236.i = zext i8 %_54.i235.i to i64
  %271 = or i64 %_7.i230.i, %_53.i236.i
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit239.i

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit239.i: ; preds = %bb2.i176.i, %bb1.i173.i
  %_0.sroa.0.0.i237.i = phi i64 [ %271, %bb2.i176.i ], [ 0, %bb1.i173.i ]
  %_20.0.i = add nuw i64 %k.sroa.0.0.i11123217, %_156.0.i
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1725)
  %_5.1.i104.i = icmp ugt i64 %_20.0.i, -9
  br i1 %_5.1.i104.i, label %panic.i170.i, label %bb1.i105.i

bb1.i105.i:                                       ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit239.i
  %_3.not.i107.i = icmp ugt i64 %_20.0.i, 499992
  br i1 %_3.not.i107.i, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i, label %bb2.i108.i

panic.i170.i:                                     ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit239.i
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_c9d76a7bf6f333d6169298e9d093a546) #13, !noalias !1728
  unreachable

bb2.i108.i:                                       ; preds = %bb1.i105.i
  %272 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_20.0.i
  %_15.i112.i = load i8, ptr %272, align 1, !alias.scope !1728, !noundef !136
  %_14.i113.i = zext i8 %_15.i112.i to i64
  %_13.i114.i = shl nuw i64 %_14.i113.i, 56
  %273 = getelementptr inbounds nuw i8, ptr %272, i64 1
  %_19.i119.i = load i8, ptr %273, align 1, !alias.scope !1728, !noundef !136
  %_18.i120.i = zext i8 %_19.i119.i to i64
  %_17.i121.i = shl nuw nsw i64 %_18.i120.i, 48
  %_12.i122.i = or disjoint i64 %_17.i121.i, %_13.i114.i
  %274 = getelementptr inbounds nuw i8, ptr %272, i64 2
  %_25.i127.i = load i8, ptr %274, align 1, !alias.scope !1728, !noundef !136
  %_24.i128.i = zext i8 %_25.i127.i to i64
  %_23.i129.i = shl nuw nsw i64 %_24.i128.i, 40
  %_11.i130.i = or disjoint i64 %_12.i122.i, %_23.i129.i
  %275 = getelementptr inbounds nuw i8, ptr %272, i64 3
  %_31.i135.i = load i8, ptr %275, align 1, !alias.scope !1728, !noundef !136
  %_30.i136.i = zext i8 %_31.i135.i to i64
  %_29.i137.i = shl nuw nsw i64 %_30.i136.i, 32
  %_10.i138.i = or disjoint i64 %_11.i130.i, %_29.i137.i
  %276 = getelementptr inbounds nuw i8, ptr %272, i64 4
  %_37.i143.i = load i8, ptr %276, align 1, !alias.scope !1728, !noundef !136
  %_36.i144.i = zext i8 %_37.i143.i to i64
  %_35.i145.i = shl nuw nsw i64 %_36.i144.i, 24
  %_9.i146.i = or disjoint i64 %_10.i138.i, %_35.i145.i
  %277 = getelementptr inbounds nuw i8, ptr %272, i64 5
  %_43.i151.i = load i8, ptr %277, align 1, !alias.scope !1728, !noundef !136
  %_42.i152.i = zext i8 %_43.i151.i to i64
  %_41.i153.i = shl nuw nsw i64 %_42.i152.i, 16
  %_8.i154.i = or disjoint i64 %_9.i146.i, %_41.i153.i
  %278 = getelementptr inbounds nuw i8, ptr %272, i64 6
  %_49.i159.i = load i8, ptr %278, align 1, !alias.scope !1728, !noundef !136
  %_48.i160.i = zext i8 %_49.i159.i to i64
  %_47.i161.i = shl nuw nsw i64 %_48.i160.i, 8
  %_7.i162.i = or i64 %_8.i154.i, %_47.i161.i
  %279 = getelementptr inbounds nuw i8, ptr %272, i64 7
  %_54.i167.i = load i8, ptr %279, align 1, !alias.scope !1728, !noundef !136
  %_53.i168.i = zext i8 %_54.i167.i to i64
  %280 = or i64 %_7.i162.i, %_53.i168.i
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i: ; preds = %bb2.i108.i, %bb1.i105.i
  %_0.sroa.0.0.i169.i = phi i64 [ %280, %bb2.i108.i ], [ 0, %bb1.i105.i ]
  %_12.i.not = icmp eq i64 %_0.sroa.0.0.i237.i, %_0.sroa.0.0.i169.i
  br i1 %_12.i.not, label %bb2.i1151, label %bb110.i

bb18.i1116:                                       ; preds = %bb15.i1113
  %_29.0.i1117 = add i64 %261, %_163.0.i
  %_29.1.i = icmp ult i64 %_29.0.i1117, %_163.0.i
  br i1 %_29.1.i, label %panic4.i1150, label %bb19.i1118

bb19.i1118:                                       ; preds = %bb18.i1116
  %_30.1.i1119 = icmp ugt i64 %_29.0.i1117, -9
  br i1 %_30.1.i1119, label %panic5.i1149, label %bb20.i1120

panic4.i1150:                                     ; preds = %bb18.i1116
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_d25cf0b69b2704dd91f9333d61493191) #13, !noalias !1718
  unreachable

bb20.i1120:                                       ; preds = %bb19.i1118
  %281 = icmp ugt i64 %_29.0.i1117, 499992
  br i1 %281, label %bb40.i.preheader, label %bb21.i1122

bb40.i.preheader:                                 ; preds = %bb23.i1124, %bb20.i1120
  br label %bb40.i

panic5.i1149:                                     ; preds = %bb19.i1118
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_d25cf0b69b2704dd91f9333d61493191) #13, !noalias !1718
  unreachable

bb21.i1122:                                       ; preds = %bb20.i1120
  %_35.0.i = add i64 %261, %_156.0.i
  %_35.1.i = icmp ult i64 %_35.0.i, %_156.0.i
  br i1 %_35.1.i, label %panic6.i1148, label %bb22.i1123

bb22.i1123:                                       ; preds = %bb21.i1122
  %_36.1.i = icmp ugt i64 %_35.0.i, -9
  br i1 %_36.1.i, label %panic7.i1147, label %bb23.i1124

panic6.i1148:                                     ; preds = %bb21.i1122
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_a53f101562b3ececed8f3c5b31e2988c) #13, !noalias !1718
  unreachable

bb23.i1124:                                       ; preds = %bb22.i1123
  %_31.not.i = icmp ugt i64 %_35.0.i, 499992
  br i1 %_31.not.i, label %bb40.i.preheader, label %bb30.i

panic7.i1147:                                     ; preds = %bb22.i1123
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_a53f101562b3ececed8f3c5b31e2988c) #13, !noalias !1718
  unreachable

bb40.i:                                           ; preds = %bb40.i.preheader, %bb44.i
  %k.sroa.0.2.i11383219 = phi i64 [ %k.sroa.0.3.i1145, %bb44.i ], [ %261, %bb40.i.preheader ]
  %_62.0.i = add i64 %k.sroa.0.2.i11383219, %_163.0.i
  %_62.1.i = icmp ult i64 %_62.0.i, %_163.0.i
  br i1 %_62.1.i, label %panic8.i1146, label %bb41.i

bb41.i:                                           ; preds = %bb40.i
  %_63.i = icmp ult i64 %_62.0.i, 500000
  br i1 %_63.i, label %bb42.i1140, label %panic9.i1139

panic8.i1146:                                     ; preds = %bb40.i
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_fd52fb03143b3c2291092829f0723dc0) #13, !noalias !1718
  unreachable

bb42.i1140:                                       ; preds = %bb41.i
  %282 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_62.0.i
  %_59.i1141 = load i8, ptr %282, align 1, !alias.scope !1718, !noundef !136
  %_67.0.i = add i64 %k.sroa.0.2.i11383219, %_156.0.i
  %_67.1.i = icmp ult i64 %_67.0.i, %_156.0.i
  br i1 %_67.1.i, label %panic10.i, label %bb43.i1142

panic9.i1139:                                     ; preds = %bb41.i
  %_62.0.i.lcssa377 = phi i64 [ %_62.0.i, %bb41.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_62.0.i.lcssa377, i64 noundef range(i64 0, -9223372036854775808) 500000, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_1256f16a95fac1466fa65d9b9a438ec4) #13, !noalias !1718
  unreachable

bb43.i1142:                                       ; preds = %bb42.i1140
  %_68.i = icmp ult i64 %_67.0.i, 500000
  br i1 %_68.i, label %bb44.i, label %panic11.i1143

panic10.i:                                        ; preds = %bb42.i1140
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_bfa6d05f2bf936d7b8c99dcdd4008e5c) #13, !noalias !1718
  unreachable

bb44.i:                                           ; preds = %bb43.i1142
  %283 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_67.0.i
  %_64.i1144 = load i8, ptr %283, align 1, !alias.scope !1718, !noundef !136
  %_58.i = icmp eq i8 %_59.i1141, %_64.i1144
  %_69.0.i = zext i1 %_58.i to i64
  %k.sroa.0.3.i1145 = add nuw nsw i64 %k.sroa.0.2.i11383219, %_69.0.i
  %_56.i = icmp samesign ult i64 %k.sroa.0.3.i1145, %w.i
  %or.cond19.i = select i1 %_58.i, i1 %_56.i, i1 false
  br i1 %or.cond19.i, label %bb40.i, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit

panic11.i1143:                                    ; preds = %bb43.i1142
  %_67.0.i.lcssa381 = phi i64 [ %_67.0.i, %bb43.i1142 ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_67.0.i.lcssa381, i64 noundef range(i64 0, -9223372036854775808) 500000, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_63961bfa935f7f5c38e726eb9c394484) #13, !noalias !1718
  unreachable

bb30.i:                                           ; preds = %bb23.i1124
  %_51.0.i1129 = shl nuw nsw i32 %_145.0.i, 3
  %284 = and i32 %_51.0.i1129, 56
  %_54.i1132.not = icmp eq i32 %284, 0
  br i1 %_54.i1132.not, label %panic18.i1133, label %bb32.i1134

bb32.i1134:                                       ; preds = %bb30.i
  %_53.0.i = sub nuw nsw i32 64, %284
  %285 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_35.0.i
  %286 = getelementptr inbounds nuw i8, ptr %285, i64 1
  %_19.i.i = load i8, ptr %286, align 1, !alias.scope !1729, !noundef !136
  %_18.i.i = zext i8 %_19.i.i to i64
  %_17.i.i = shl nuw nsw i64 %_18.i.i, 48
  %_15.i.i = load i8, ptr %285, align 1, !alias.scope !1729, !noundef !136
  %_14.i.i = zext i8 %_15.i.i to i64
  %_13.i.i = shl nuw i64 %_14.i.i, 56
  %_12.i.i1126 = or disjoint i64 %_17.i.i, %_13.i.i
  %287 = getelementptr inbounds nuw i8, ptr %285, i64 2
  %_25.i.i = load i8, ptr %287, align 1, !alias.scope !1729, !noundef !136
  %_24.i.i = zext i8 %_25.i.i to i64
  %_23.i.i = shl nuw nsw i64 %_24.i.i, 40
  %_11.i.i1127 = or disjoint i64 %_12.i.i1126, %_23.i.i
  %288 = getelementptr inbounds nuw i8, ptr %285, i64 3
  %_31.i.i = load i8, ptr %288, align 1, !alias.scope !1729, !noundef !136
  %_30.i.i = zext i8 %_31.i.i to i64
  %_29.i.i = shl nuw nsw i64 %_30.i.i, 32
  %_10.i.i = or disjoint i64 %_11.i.i1127, %_29.i.i
  %289 = getelementptr inbounds nuw i8, ptr %285, i64 4
  %_37.i.i = load i8, ptr %289, align 1, !alias.scope !1729, !noundef !136
  %_36.i.i = zext i8 %_37.i.i to i64
  %_35.i.i = shl nuw nsw i64 %_36.i.i, 24
  %_9.i.i = or disjoint i64 %_10.i.i, %_35.i.i
  %290 = getelementptr inbounds nuw i8, ptr %285, i64 5
  %_43.i.i = load i8, ptr %290, align 1, !alias.scope !1729, !noundef !136
  %_42.i.i = zext i8 %_43.i.i to i64
  %_41.i.i = shl nuw nsw i64 %_42.i.i, 16
  %_8.i.i = or disjoint i64 %_9.i.i, %_41.i.i
  %291 = getelementptr inbounds nuw i8, ptr %285, i64 6
  %_49.i.i = load i8, ptr %291, align 1, !alias.scope !1729, !noundef !136
  %_48.i.i = zext i8 %_49.i.i to i64
  %_47.i.i = shl nuw nsw i64 %_48.i.i, 8
  %_7.i.i = or i64 %_8.i.i, %_47.i.i
  %292 = getelementptr inbounds nuw i8, ptr %285, i64 7
  %_54.i.i = load i8, ptr %292, align 1, !alias.scope !1729, !noundef !136
  %_53.i.i = zext i8 %_54.i.i to i64
  %293 = or i64 %_7.i.i, %_53.i.i
  %294 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_29.0.i1117
  %295 = getelementptr inbounds nuw i8, ptr %294, i64 1
  %_19.i51.i = load i8, ptr %295, align 1, !alias.scope !1732, !noundef !136
  %_18.i52.i = zext i8 %_19.i51.i to i64
  %_17.i53.i = shl nuw nsw i64 %_18.i52.i, 48
  %_15.i44.i = load i8, ptr %294, align 1, !alias.scope !1732, !noundef !136
  %_14.i45.i = zext i8 %_15.i44.i to i64
  %_13.i46.i = shl nuw i64 %_14.i45.i, 56
  %_12.i54.i = or disjoint i64 %_17.i53.i, %_13.i46.i
  %296 = getelementptr inbounds nuw i8, ptr %294, i64 2
  %_25.i59.i = load i8, ptr %296, align 1, !alias.scope !1732, !noundef !136
  %_24.i60.i = zext i8 %_25.i59.i to i64
  %_23.i61.i = shl nuw nsw i64 %_24.i60.i, 40
  %_11.i62.i = or disjoint i64 %_12.i54.i, %_23.i61.i
  %297 = getelementptr inbounds nuw i8, ptr %294, i64 3
  %_31.i67.i = load i8, ptr %297, align 1, !alias.scope !1732, !noundef !136
  %_30.i68.i = zext i8 %_31.i67.i to i64
  %_29.i69.i = shl nuw nsw i64 %_30.i68.i, 32
  %_10.i70.i = or disjoint i64 %_11.i62.i, %_29.i69.i
  %298 = getelementptr inbounds nuw i8, ptr %294, i64 4
  %_37.i75.i = load i8, ptr %298, align 1, !alias.scope !1732, !noundef !136
  %_36.i76.i = zext i8 %_37.i75.i to i64
  %_35.i77.i = shl nuw nsw i64 %_36.i76.i, 24
  %_9.i78.i = or disjoint i64 %_10.i70.i, %_35.i77.i
  %299 = getelementptr inbounds nuw i8, ptr %294, i64 5
  %_43.i83.i = load i8, ptr %299, align 1, !alias.scope !1732, !noundef !136
  %_42.i84.i = zext i8 %_43.i83.i to i64
  %_41.i85.i = shl nuw nsw i64 %_42.i84.i, 16
  %_8.i86.i = or disjoint i64 %_9.i78.i, %_41.i85.i
  %300 = getelementptr inbounds nuw i8, ptr %294, i64 6
  %_49.i91.i = load i8, ptr %300, align 1, !alias.scope !1732, !noundef !136
  %_48.i92.i = zext i8 %_49.i91.i to i64
  %_47.i93.i = shl nuw nsw i64 %_48.i92.i, 8
  %_7.i94.i = or i64 %_8.i86.i, %_47.i93.i
  %301 = getelementptr inbounds nuw i8, ptr %294, i64 7
  %_54.i99.i = load i8, ptr %301, align 1, !alias.scope !1732, !noundef !136
  %_53.i100.i = zext i8 %_54.i99.i to i64
  %302 = or i64 %_7.i94.i, %_53.i100.i
  %x.i1128 = xor i64 %293, %302
  %303 = zext nneg i32 %_53.0.i to i64
  %_46.i1135 = lshr i64 %x.i1128, %303
  %304 = icmp eq i64 %_46.i1135, 0
  br i1 %304, label %bb101.i, label %bb110.i

panic18.i1133:                                    ; preds = %bb30.i
; call core::panicking::panic_const::panic_const_shr_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_shr_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_8bda8caf9703c723fc6d18cb0fd57c1f) #13, !noalias !1718
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit: ; preds = %bb44.i
  br i1 %_58.i, label %bb101.i, label %bb110.i

bb101.i:                                          ; preds = %bb32.i1134, %bb15.i1113, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit
  %_170.0.i = add nuw nsw i64 %back.sroa.0.0.i3226, 1
  br label %bb110.i

bb110.i:                                          ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i, %bb32.i1134, %bb77.i, %bb80.i, %bb101.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit, %bb90.i, %bb87.i, %bb84.i
  %p.sroa.0.8.i = phi i64 [ %_125.0.i, %bb80.i ], [ %_156.0.i, %bb101.i ], [ %p.sroa.0.7.i3225, %bb84.i ], [ %p.sroa.0.7.i3225, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit ], [ %p.sroa.0.7.i3225, %bb90.i ], [ %p.sroa.0.7.i3225, %bb87.i ], [ %p.sroa.0.7.i3225, %bb77.i ], [ %p.sroa.0.7.i3225, %bb32.i1134 ], [ %p.sroa.0.7.i3225, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i ]
  %back.sroa.0.1.i = phi i64 [ %_138.0.i, %bb80.i ], [ %_170.0.i, %bb101.i ], [ 16, %bb84.i ], [ 16, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit ], [ 16, %bb90.i ], [ 16, %bb87.i ], [ 16, %bb77.i ], [ 16, %bb32.i1134 ], [ 16, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i ]
  %l.sroa.0.3.i = phi i64 [ %_137.0.i, %bb80.i ], [ %_149.0.i, %bb101.i ], [ %l.sroa.0.2.i3227, %bb84.i ], [ %l.sroa.0.2.i3227, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit ], [ %l.sroa.0.2.i3227, %bb90.i ], [ %l.sroa.0.2.i3227, %bb87.i ], [ %l.sroa.0.2.i3227, %bb77.i ], [ %l.sroa.0.2.i3227, %bb32.i1134 ], [ %l.sroa.0.2.i3227, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i ]
  %nt.sroa.0.8.i = phi i64 [ %257, %bb80.i ], [ %257, %bb101.i ], [ %nt.sroa.0.7.i3228, %bb84.i ], [ %nt.sroa.0.7.i3228, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit ], [ %nt.sroa.0.7.i3228, %bb90.i ], [ %nt.sroa.0.7.i3228, %bb87.i ], [ %nt.sroa.0.7.i3228, %bb77.i ], [ %nt.sroa.0.7.i3228, %bb32.i1134 ], [ %nt.sroa.0.7.i3228, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i ]
  %_103.i = icmp ult i64 %back.sroa.0.1.i, 16
  %305 = add i64 %nt.sroa.0.8.i, -1
  %306 = icmp ult i64 %305, %out.1
  %or.cond48.i = select i1 %_103.i, i1 %306, i1 false
  %_110.i = icmp ult i64 %l.sroa.0.3.i, 258
  %or.cond49.i = select i1 %or.cond48.i, i1 %_110.i, i1 false
  %_112.i = icmp ult i64 %d.sroa.0.0.i.lcssa, %p.sroa.0.8.i
  %or.cond149.i = select i1 %or.cond49.i, i1 %_112.i, i1 false
  br i1 %or.cond149.i, label %bb71.i, label %bb116.i

bb80.i:                                           ; preds = %bb77.i
  %_137.0.i = add nuw nsw i64 %l.sroa.0.2.i3227, 1
  %_138.0.i = add nuw nsw i64 %back.sroa.0.0.i3226, 1
  br label %bb110.i

_RINvNtCs2hd9JHJjR4I_9candidate5parse8u118_runKj10000_Kj8000_Kmffffffff_Kj4_Kj6_Kj20_Kj5_Kjf4240_Kj40_Kj1_Kj10_KB18_Kl40_KB1C_EB4_.exit: ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit342, %bb178.i
  %nt.sroa.0.2.i.lcssa = phi i64 [ %nt.sroa.0.4.i.lcssa, %bb178.i ], [ %_10.0.i341, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit342 ]
  ret i64 %nt.sroa.0.2.i.lcssa
}