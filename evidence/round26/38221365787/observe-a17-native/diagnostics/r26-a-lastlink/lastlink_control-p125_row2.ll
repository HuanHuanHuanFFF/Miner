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
  %_237.i3275 = icmp ult i64 %p.sroa.0.4.i.lcssa, 500000
  br i1 %_237.i3275, label %bb1.i348.preheader, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse8u118_runKj10000_Kj8000_Kmffffffff_Kj4_Kj6_Kj20_Kj5_Kjf4240_Kj40_Kj1_Kj10_KB18_Kl40_KB1C_EB4_.exit

bb1.i348.preheader:                               ; preds = %bb178.i
  %umax = tail call i64 @llvm.umax.i64(i64 %nt.sroa.0.4.i.lcssa, i64 %out.1)
  %0 = sub i64 %umax, %nt.sroa.0.4.i.lcssa
  %1 = sub nuw nsw i64 499999, %p.sroa.0.4.i.lcssa
  %2 = call i64 @llvm.umin.i64(i64 %0, i64 %1)
  %min.iters.check298 = icmp samesign ult i64 %2, 8
  br i1 %min.iters.check298, label %bb1.i348.preheader322, label %vector.ph299

bb1.i348.preheader322:                            ; preds = %vector.body302, %bb1.i348.preheader
  %nt.sroa.0.2.i3277.ph = phi i64 [ %nt.sroa.0.4.i.lcssa, %bb1.i348.preheader ], [ %6, %vector.body302 ]
  %p.sroa.0.2.i3276.ph = phi i64 [ %p.sroa.0.4.i.lcssa, %bb1.i348.preheader ], [ %7, %vector.body302 ]
  br label %bb1.i348

vector.ph299:                                     ; preds = %bb1.i348.preheader
  %3 = add nuw nsw i64 %2, 1
  %n.mod.vf300 = and i64 %3, 7
  %4 = icmp eq i64 %n.mod.vf300, 0
  %5 = select i1 %4, i64 8, i64 %n.mod.vf300
  %n.vec301 = sub nuw nsw i64 %3, %5
  %6 = add i64 %nt.sroa.0.4.i.lcssa, %n.vec301
  %7 = add nuw nsw i64 %p.sroa.0.4.i.lcssa, %n.vec301
  %8 = getelementptr i8, ptr %input.0, i64 %p.sroa.0.4.i.lcssa
  %9 = getelementptr [4 x i8], ptr %out.0, i64 %nt.sroa.0.4.i.lcssa
  br label %vector.body302

vector.body302:                                   ; preds = %vector.body302, %vector.ph299
  %index303 = phi i64 [ 0, %vector.ph299 ], [ %index.next306, %vector.body302 ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1564)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1567)
  %10 = getelementptr i8, ptr %8, i64 %index303
  %11 = getelementptr inbounds nuw i8, ptr %10, i64 4
  %wide.load304 = load <4 x i8>, ptr %10, align 1, !alias.scope !1564, !noalias !1567
  %wide.load305 = load <4 x i8>, ptr %11, align 1, !alias.scope !1564, !noalias !1567
  %12 = getelementptr [4 x i8], ptr %9, i64 %index303
  %13 = zext <4 x i8> %wide.load304 to <4 x i32>
  %14 = zext <4 x i8> %wide.load305 to <4 x i32>
  %15 = getelementptr inbounds nuw i8, ptr %12, i64 16
  store <4 x i32> %13, ptr %12, align 4, !alias.scope !1567, !noalias !1564
  store <4 x i32> %14, ptr %15, align 4, !alias.scope !1567, !noalias !1564
  %index.next306 = add nuw i64 %index303, 8
  %16 = icmp eq i64 %index.next306, %n.vec301
  br i1 %16, label %bb1.i348.preheader322, label %vector.body302, !llvm.loop !1569

bb5.i:                                            ; preds = %bb5.i.preheader, %bb174.i
  %nt.sroa.0.1.i3272 = phi i64 [ %nt.sroa.0.4.i, %bb174.i ], [ 0, %bb5.i.preheader ]
  %miss.sroa.0.0.i3271 = phi i64 [ %miss.sroa.0.1.i, %bb174.i ], [ 0, %bb5.i.preheader ]
  %fuel.sroa.0.0.i3270 = phi i64 [ %_15.0.i, %bb174.i ], [ 500016, %bb5.i.preheader ]
  %p.sroa.0.1.i3269 = phi i64 [ %p.sroa.0.4.i, %bb174.i ], [ 0, %bb5.i.preheader ]
  %ins.sroa.0.0.i3268 = phi i64 [ %ins.sroa.0.3.i, %bb174.i ], [ 0, %bb5.i.preheader ]
  %p.sroa.0.1.i3269.fr = freeze i64 %p.sroa.0.1.i3269
  %_15.0.i = add nsw i64 %fuel.sroa.0.0.i3270, -1
  %_16.i3181 = icmp ult i64 %ins.sroa.0.0.i3268, %p.sroa.0.1.i3269.fr
  br i1 %_16.i3181, label %bb8.i, label %bb11.i

bb1.i348:                                         ; preds = %bb1.i348.preheader322, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit354
  %nt.sroa.0.2.i3277 = phi i64 [ %_10.0.i353, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit354 ], [ %nt.sroa.0.2.i3277.ph, %bb1.i348.preheader322 ]
  %p.sroa.0.2.i3276 = phi i64 [ %_241.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit354 ], [ %p.sroa.0.2.i3276.ph, %bb1.i348.preheader322 ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1564)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1567)
  %exitcond3471.not = icmp eq i64 %nt.sroa.0.2.i3277, %umax
  br i1 %exitcond3471.not, label %panic1.i350, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit354

panic1.i350:                                      ; preds = %bb1.i348
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %umax, i64 noundef range(i64 0, 2305843009213693952) %out.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_1e808d4a560d2bfb30193cdd1b6f1f95) #13, !noalias !1570
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit354: ; preds = %bb1.i348
  %17 = getelementptr inbounds nuw i8, ptr %input.0, i64 %p.sroa.0.2.i3276
  %_5.i352 = load i8, ptr %17, align 1, !alias.scope !1564, !noalias !1567, !noundef !136
  %18 = getelementptr inbounds nuw [4 x i8], ptr %out.0, i64 %nt.sroa.0.2.i3277
  %19 = zext i8 %_5.i352 to i32
  store i32 %19, ptr %18, align 4, !alias.scope !1567, !noalias !1564
  %_10.0.i353 = add i64 %nt.sroa.0.2.i3277, 1
  %_241.0.i = add nuw nsw i64 %p.sroa.0.2.i3276, 1
  %exitcond3472.not = icmp eq i64 %_241.0.i, 500000
  br i1 %exitcond3472.not, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse8u118_runKj10000_Kj8000_Kmffffffff_Kj4_Kj6_Kj20_Kj5_Kjf4240_Kj40_Kj1_Kj10_KB18_Kl40_KB1C_EB4_.exit, label %bb1.i348, !llvm.loop !1571

bb11.i:                                           ; preds = %bb8.i, %bb5.i
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1572)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1575)
  %20 = getelementptr inbounds nuw i8, ptr %input.0, i64 %p.sroa.0.1.i3269.fr
  %21 = load <4 x i8>, ptr %20, align 1, !alias.scope !1577, !noalias !1580
  %22 = bitcast <4 x i8> %21 to i32
  %23 = call i32 @llvm.bswap.i32(i32 %22)
  %24 = zext i32 %23 to i64
  %25 = mul i64 %24, -7046029254386353131
  %26 = lshr i64 %25, 48
  %27 = getelementptr inbounds nuw [4 x i8], ptr %head.i, i64 %26
  %old.i190.i = load i32, ptr %27, align 4, !alias.scope !1572, !noalias !1581, !noundef !136
  %_16.i191.i = and i64 %p.sroa.0.1.i3269.fr, 32767
  %28 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_16.i191.i
  store i32 %old.i190.i, ptr %28, align 4, !alias.scope !1575, !noalias !1583
  %29 = trunc i64 %p.sroa.0.1.i3269.fr to i32
  store i32 %29, ptr %27, align 4, !alias.scope !1572, !noalias !1581
  %_0.i192.i = zext i32 %old.i190.i to i64
  %_29.0.i = add nuw nsw i64 %p.sroa.0.1.i3269.fr, 1
  %_13.0.i20 = sub i64 500000, %p.sroa.0.1.i3269.fr
  %spec.store.select3.i21 = tail call i64 @llvm.umin.i64(i64 %_13.0.i20, i64 258)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1584)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1587)
  %spec.store.select.i27 = tail call i64 @llvm.umin.i64(i64 %_13.0.i20, i64 64)
  %30 = and i64 %spec.store.select3.i21, 504
  %31 = extractelement <4 x i8> %21, i64 3
  %_26.i2543185.not = icmp eq i64 %30, %spec.store.select3.i21
  br label %bb11.i29

bb11.i29:                                         ; preds = %bb39.i34, %bb11.i
  %start1.sroa.0.0.i3192 = phi i64 [ %_0.i192.i, %bb11.i ], [ %spec.select25.i, %bb39.i34 ]
  %have.sroa.0.0.i3191 = phi i64 [ 3, %bb11.i ], [ %have.sroa.0.2.i, %bb39.i34 ]
  %depth.sroa.0.0.i3190 = phi i64 [ 6, %bb11.i ], [ %_68.0.i, %bb39.i34 ]
  %bd.sroa.0.0.i3189 = phi i64 [ 0, %bb11.i ], [ %bd.sroa.0.2.i, %bb39.i34 ]
  %pb.sroa.0.1.i3188 = phi i8 [ %31, %bb11.i ], [ %pb.sroa.0.3.i, %bb39.i34 ]
  %d.i = sub nsw i64 %p.sroa.0.1.i3269.fr, %start1.sroa.0.0.i3192
  %_29.i = add nsw i64 %d.i, -1
  %_28.i = icmp ult i64 %_29.i, 32768
  br i1 %_28.i, label %bb13.i, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit

bb13.i:                                           ; preds = %bb11.i29
  %_34.0.i = add nuw nsw i64 %start1.sroa.0.0.i3192, %have.sroa.0.0.i3191
  %_30.i = icmp ult i64 %_34.0.i, 500000
  br i1 %_30.i, label %bb16.i31, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit

bb16.i31:                                         ; preds = %bb13.i
  %32 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_34.0.i
  %_36.i = load i8, ptr %32, align 1, !alias.scope !1584, !noalias !1587, !noundef !136
  %_35.i32 = icmp eq i8 %_36.i, %pb.sroa.0.1.i3188
  br i1 %_35.i32, label %bb2.i278, label %bb35.i33

bb2.i278:                                         ; preds = %bb16.i31, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit
  %k.sroa.0.0.i2493184 = phi i64 [ %_10.0.i279, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit ], [ 0, %bb16.i31 ]
  %_10.0.i279 = add nuw nsw i64 %k.sroa.0.0.i2493184, 8
  %_7.not.i282 = icmp samesign ugt i64 %_10.0.i279, %spec.store.select3.i21
  br i1 %_7.not.i282, label %bb17.i250, label %bb4.i283

bb4.i283:                                         ; preds = %bb2.i278
  %_15.0.i284 = add nuw nsw i64 %k.sroa.0.0.i2493184, %start1.sroa.0.0.i3192
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1589)
  %_5.1.i632 = icmp ugt i64 %_15.0.i284, -9
  br i1 %_5.1.i632, label %panic.i699, label %bb1.i633

bb17.i250:                                        ; preds = %bb2.i278
  br i1 %_26.i2543185.not, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit304, label %bb21.i260

bb1.i633:                                         ; preds = %bb4.i283
  %33 = icmp ugt i64 %_15.0.i284, 499992
  br i1 %33, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit700, label %bb2.i636

panic.i699:                                       ; preds = %bb4.i283
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_440babfea49fec204c4bfa4556bd23df) #13, !noalias !1592
  unreachable

bb2.i636:                                         ; preds = %bb1.i633
  %34 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_15.0.i284
  %_15.i640 = load i8, ptr %34, align 1, !alias.scope !1589, !noalias !1587, !noundef !136
  %_14.i641 = zext i8 %_15.i640 to i64
  %_13.i642 = shl nuw i64 %_14.i641, 56
  %35 = getelementptr inbounds nuw i8, ptr %34, i64 1
  %_19.i647 = load i8, ptr %35, align 1, !alias.scope !1589, !noalias !1587, !noundef !136
  %_18.i648 = zext i8 %_19.i647 to i64
  %_17.i649 = shl nuw nsw i64 %_18.i648, 48
  %_12.i650 = or disjoint i64 %_17.i649, %_13.i642
  %36 = getelementptr inbounds nuw i8, ptr %34, i64 2
  %_25.i655 = load i8, ptr %36, align 1, !alias.scope !1589, !noalias !1587, !noundef !136
  %_24.i656 = zext i8 %_25.i655 to i64
  %_23.i657 = shl nuw nsw i64 %_24.i656, 40
  %_11.i658 = or disjoint i64 %_12.i650, %_23.i657
  %37 = getelementptr inbounds nuw i8, ptr %34, i64 3
  %_31.i663 = load i8, ptr %37, align 1, !alias.scope !1589, !noalias !1587, !noundef !136
  %_30.i664 = zext i8 %_31.i663 to i64
  %_29.i665 = shl nuw nsw i64 %_30.i664, 32
  %_10.i666 = or disjoint i64 %_11.i658, %_29.i665
  %38 = getelementptr inbounds nuw i8, ptr %34, i64 4
  %_37.i671 = load i8, ptr %38, align 1, !alias.scope !1589, !noalias !1587, !noundef !136
  %_36.i672 = zext i8 %_37.i671 to i64
  %_35.i673 = shl nuw nsw i64 %_36.i672, 24
  %_9.i674 = or disjoint i64 %_10.i666, %_35.i673
  %39 = getelementptr inbounds nuw i8, ptr %34, i64 5
  %_43.i679 = load i8, ptr %39, align 1, !alias.scope !1589, !noalias !1587, !noundef !136
  %_42.i680 = zext i8 %_43.i679 to i64
  %_41.i681 = shl nuw nsw i64 %_42.i680, 16
  %_8.i682 = or disjoint i64 %_9.i674, %_41.i681
  %40 = getelementptr inbounds nuw i8, ptr %34, i64 6
  %_49.i687 = load i8, ptr %40, align 1, !alias.scope !1589, !noalias !1587, !noundef !136
  %_48.i688 = zext i8 %_49.i687 to i64
  %_47.i689 = shl nuw nsw i64 %_48.i688, 8
  %_7.i690 = or i64 %_8.i682, %_47.i689
  %41 = getelementptr inbounds nuw i8, ptr %34, i64 7
  %_54.i695 = load i8, ptr %41, align 1, !alias.scope !1589, !noalias !1587, !noundef !136
  %_53.i696 = zext i8 %_54.i695 to i64
  %42 = or i64 %_7.i690, %_53.i696
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit700

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit700: ; preds = %bb1.i633, %bb2.i636
  %_0.sroa.0.0.i698 = phi i64 [ %42, %bb2.i636 ], [ 0, %bb1.i633 ]
  %_19.0.i288 = add nuw i64 %k.sroa.0.0.i2493184, %p.sroa.0.1.i3269.fr
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1593)
  %_5.1.i = icmp ugt i64 %_19.0.i288, -9
  br i1 %_5.1.i, label %panic.i631, label %bb1.i587

bb1.i587:                                         ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit700
  %43 = icmp ugt i64 %_19.0.i288, 499992
  br i1 %43, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit, label %bb2.i590

panic.i631:                                       ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit700
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_440babfea49fec204c4bfa4556bd23df) #13, !noalias !1596
  unreachable

bb2.i590:                                         ; preds = %bb1.i587
  %44 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_19.0.i288
  %_15.i594 = load i8, ptr %44, align 1, !alias.scope !1593, !noalias !1587, !noundef !136
  %_14.i595 = zext i8 %_15.i594 to i64
  %_13.i596 = shl nuw i64 %_14.i595, 56
  %45 = getelementptr inbounds nuw i8, ptr %44, i64 1
  %_19.i599 = load i8, ptr %45, align 1, !alias.scope !1593, !noalias !1587, !noundef !136
  %_18.i600 = zext i8 %_19.i599 to i64
  %_17.i = shl nuw nsw i64 %_18.i600, 48
  %_12.i601 = or disjoint i64 %_17.i, %_13.i596
  %46 = getelementptr inbounds nuw i8, ptr %44, i64 2
  %_25.i605 = load i8, ptr %46, align 1, !alias.scope !1593, !noalias !1587, !noundef !136
  %_24.i606 = zext i8 %_25.i605 to i64
  %_23.i = shl nuw nsw i64 %_24.i606, 40
  %_11.i607 = or disjoint i64 %_12.i601, %_23.i
  %47 = getelementptr inbounds nuw i8, ptr %44, i64 3
  %_31.i = load i8, ptr %47, align 1, !alias.scope !1593, !noalias !1587, !noundef !136
  %_30.i611 = zext i8 %_31.i to i64
  %_29.i612 = shl nuw nsw i64 %_30.i611, 32
  %_10.i613 = or disjoint i64 %_11.i607, %_29.i612
  %48 = getelementptr inbounds nuw i8, ptr %44, i64 4
  %_37.i = load i8, ptr %48, align 1, !alias.scope !1593, !noalias !1587, !noundef !136
  %_36.i615 = zext i8 %_37.i to i64
  %_35.i616 = shl nuw nsw i64 %_36.i615, 24
  %_9.i617 = or disjoint i64 %_10.i613, %_35.i616
  %49 = getelementptr inbounds nuw i8, ptr %44, i64 5
  %_43.i = load i8, ptr %49, align 1, !alias.scope !1593, !noalias !1587, !noundef !136
  %_42.i = zext i8 %_43.i to i64
  %_41.i620 = shl nuw nsw i64 %_42.i, 16
  %_8.i621 = or disjoint i64 %_9.i617, %_41.i620
  %50 = getelementptr inbounds nuw i8, ptr %44, i64 6
  %_49.i624 = load i8, ptr %50, align 1, !alias.scope !1593, !noalias !1587, !noundef !136
  %_48.i = zext i8 %_49.i624 to i64
  %_47.i = shl nuw nsw i64 %_48.i, 8
  %_7.i625 = or i64 %_8.i621, %_47.i
  %51 = getelementptr inbounds nuw i8, ptr %44, i64 7
  %_54.i = load i8, ptr %51, align 1, !alias.scope !1593, !noalias !1587, !noundef !136
  %_53.i = zext i8 %_54.i to i64
  %52 = or i64 %_7.i625, %_53.i
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit: ; preds = %bb1.i587, %bb2.i590
  %_0.sroa.0.0.i630 = phi i64 [ %52, %bb2.i590 ], [ 0, %bb1.i587 ]
  %53 = icmp eq i64 %_0.sroa.0.0.i698, %_0.sroa.0.0.i630
  br i1 %53, label %bb2.i278, label %bb17.i250.thread

bb17.i250.thread:                                 ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit
  %_0.sroa.0.0.i630.lcssa = phi i64 [ %_0.sroa.0.0.i630, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit ]
  %_0.sroa.0.0.i698.lcssa327 = phi i64 [ %_0.sroa.0.0.i698, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit ]
  %k.sroa.0.0.i2493184.lcssa326 = phi i64 [ %k.sroa.0.0.i2493184, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit ]
  %x.i293 = xor i64 %_0.sroa.0.0.i630.lcssa, %_0.sroa.0.0.i698.lcssa327
  %54 = tail call range(i64 0, 65) i64 @llvm.ctlz.i64(i64 %x.i293, i1 true)
  %_2220.i294 = lshr i64 %54, 3
  %_24.0.i295 = or disjoint i64 %_2220.i294, %k.sroa.0.0.i2493184.lcssa326
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit304

bb21.i260:                                        ; preds = %bb17.i250, %bb24.i270
  %k.sroa.0.2.i2533187 = phi i64 [ %k.sroa.0.3.i275, %bb24.i270 ], [ %30, %bb17.i250 ]
  %_32.0.i258 = add nuw nsw i64 %k.sroa.0.2.i2533187, %start1.sroa.0.0.i3192
  %_34.i261 = icmp ult i64 %_32.0.i258, 500000
  br i1 %_34.i261, label %bb22.i263, label %panic6.i262

bb22.i263:                                        ; preds = %bb21.i260
  %55 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_32.0.i258
  %_29.i264 = load i8, ptr %55, align 1, !alias.scope !1597, !noalias !1587, !noundef !136
  %_38.0.i265 = add i64 %k.sroa.0.2.i2533187, %p.sroa.0.1.i3269.fr
  %_38.1.i266 = icmp ult i64 %_38.0.i265, %p.sroa.0.1.i3269.fr
  br i1 %_38.1.i266, label %panic7.i276, label %bb23.i267

panic6.i262:                                      ; preds = %bb21.i260
  %_32.0.i258.lcssa328 = phi i64 [ %_32.0.i258, %bb21.i260 ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_32.0.i258.lcssa328, i64 noundef range(i64 0, -9223372036854775808) 500000, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_d0bf91bac5912d1054a41f50a5372dd0) #13, !noalias !1587
  unreachable

bb23.i267:                                        ; preds = %bb22.i263
  %_39.i268 = icmp ult i64 %_38.0.i265, 500000
  br i1 %_39.i268, label %bb24.i270, label %panic8.i269

panic7.i276:                                      ; preds = %bb22.i263
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_e58248ce06d86db1620e3928ca18f57a) #13, !noalias !1587
  unreachable

bb24.i270:                                        ; preds = %bb23.i267
  %56 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_38.0.i265
  %_35.i271 = load i8, ptr %56, align 1, !alias.scope !1597, !noalias !1587, !noundef !136
  %_28.i272 = icmp eq i8 %_29.i264, %_35.i271
  %_40.0.i273 = zext i1 %_28.i272 to i64
  %k.sroa.0.3.i275 = add nuw nsw i64 %k.sroa.0.2.i2533187, %_40.0.i273
  %_26.i254 = icmp samesign ult i64 %k.sroa.0.3.i275, %spec.store.select3.i21
  %or.cond.i255 = select i1 %_28.i272, i1 %_26.i254, i1 false
  br i1 %or.cond.i255, label %bb21.i260, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit304

panic8.i269:                                      ; preds = %bb23.i267
  %_38.0.i265.lcssa332 = phi i64 [ %_38.0.i265, %bb23.i267 ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_38.0.i265.lcssa332, i64 noundef range(i64 0, -9223372036854775808) 500000, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_c7cb404ab9612aded1ce50ca918ced7b) #13, !noalias !1587
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit304: ; preds = %bb24.i270, %bb17.i250.thread, %bb17.i250
  %k.sroa.0.2.i253.lcssa = phi i64 [ %30, %bb17.i250 ], [ %_24.0.i295, %bb17.i250.thread ], [ %k.sroa.0.3.i275, %bb24.i270 ]
  %_46.i = icmp ugt i64 %k.sroa.0.2.i253.lcssa, %have.sroa.0.0.i3191
  br i1 %_46.i, label %bb19.i, label %bb35.i33

bb35.i33:                                         ; preds = %bb31.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit304, %bb16.i31
  %pb.sroa.0.3.i = phi i8 [ %pb.sroa.0.1.i3188, %bb16.i31 ], [ %pb.sroa.0.1.i3188, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit304 ], [ %58, %bb31.i ]
  %bd.sroa.0.2.i = phi i64 [ %bd.sroa.0.0.i3189, %bb16.i31 ], [ %bd.sroa.0.0.i3189, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit304 ], [ %d.i, %bb31.i ]
  %have.sroa.0.2.i = phi i64 [ %have.sroa.0.0.i3191, %bb16.i31 ], [ %have.sroa.0.0.i3191, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit304 ], [ %k.sroa.0.2.i253.lcssa, %bb31.i ]
  %_58.i = icmp eq i64 %depth.sroa.0.0.i3190, 1
  br i1 %_58.i, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit, label %bb39.i34

bb19.i:                                           ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit304
  %_51.not.i = icmp ult i64 %k.sroa.0.2.i253.lcssa, %spec.store.select.i27
  br i1 %_51.not.i, label %bb26.i, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit

bb26.i:                                           ; preds = %bb19.i
  %_55.0.i = add i64 %k.sroa.0.2.i253.lcssa, %p.sroa.0.1.i3269.fr
  %_55.1.i = icmp ult i64 %_55.0.i, %p.sroa.0.1.i3269.fr
  br i1 %_55.1.i, label %panic7.i, label %bb27.i

bb27.i:                                           ; preds = %bb26.i
  %_53.not.i = icmp ult i64 %_55.0.i, 500000
  br i1 %_53.not.i, label %bb31.i, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit

panic7.i:                                         ; preds = %bb26.i
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_f7734e5b3c0057e9bae084232237166a) #13, !noalias !1587
  unreachable

bb31.i:                                           ; preds = %bb27.i
  %57 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_55.0.i
  %58 = load i8, ptr %57, align 1, !alias.scope !1584, !noalias !1587, !noundef !136
  br label %bb35.i33

bb39.i34:                                         ; preds = %bb35.i33
  %_62.i35 = and i64 %start1.sroa.0.0.i3192, 32767
  %59 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_62.i35
  %_61.i = load i32, ptr %59, align 4, !alias.scope !1587, !noalias !1584, !noundef !136
  %nx.i = zext i32 %_61.i to i64
  %_66.i.not = icmp ugt i64 %start1.sroa.0.0.i3192, %nx.i
  %_68.0.i = add nsw i64 %depth.sroa.0.0.i3190, -1
  %spec.select25.i = tail call i64 @llvm.umin.i64(i64 %start1.sroa.0.0.i3192, i64 %nx.i)
  br i1 %_66.i.not, label %bb11.i29, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit

_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit: ; preds = %bb19.i, %bb27.i, %bb13.i, %bb35.i33, %bb39.i34, %bb11.i29
  %have.sroa.0.1.i3481 = phi i64 [ %have.sroa.0.0.i3191, %bb11.i29 ], [ %k.sroa.0.2.i253.lcssa, %bb19.i ], [ %k.sroa.0.2.i253.lcssa, %bb27.i ], [ %have.sroa.0.0.i3191, %bb13.i ], [ %have.sroa.0.2.i, %bb35.i33 ], [ %have.sroa.0.2.i, %bb39.i34 ]
  %bd.sroa.0.1.i3480 = phi i64 [ %bd.sroa.0.0.i3189, %bb11.i29 ], [ %d.i, %bb19.i ], [ %d.i, %bb27.i ], [ %bd.sroa.0.0.i3189, %bb13.i ], [ %bd.sroa.0.2.i, %bb35.i33 ], [ %bd.sroa.0.2.i, %bb39.i34 ]
  %.not = icmp eq i64 %bd.sroa.0.1.i3480, 0
  br i1 %.not, label %bb154.i, label %bb16.i.preheader

bb16.i.preheader:                                 ; preds = %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit
  %_39.i3226 = icmp ult i64 %have.sroa.0.1.i3481, 32
  br i1 %_39.i3226, label %bb18.i, label %bb63.i

bb8.i:                                            ; preds = %bb5.i, %bb8.i
  %ins.sroa.0.1.i3182 = phi i64 [ %_23.0.i, %bb8.i ], [ %ins.sroa.0.0.i3268, %bb5.i ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1600)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1603)
  %60 = getelementptr inbounds nuw i8, ptr %input.0, i64 %ins.sroa.0.1.i3182
  %61 = load i32, ptr %60, align 1
  %62 = call i32 @llvm.bswap.i32(i32 %61)
  %63 = zext i32 %62 to i64
  %64 = mul i64 %63, -7046029254386353131
  %65 = lshr i64 %64, 48
  %66 = getelementptr inbounds nuw [4 x i8], ptr %head.i, i64 %65
  %old.i.i = load i32, ptr %66, align 4, !alias.scope !1600, !noalias !1605, !noundef !136
  %_16.i.i = and i64 %ins.sroa.0.1.i3182, 32767
  %67 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_16.i.i
  store i32 %old.i.i, ptr %67, align 4, !alias.scope !1603, !noalias !1607
  %68 = trunc i64 %ins.sroa.0.1.i3182 to i32
  store i32 %68, ptr %66, align 4, !alias.scope !1600, !noalias !1605
  %_23.0.i = add nuw nsw i64 %ins.sroa.0.1.i3182, 1
  %exitcond.not = icmp eq i64 %_23.0.i, %p.sroa.0.1.i3269.fr
  br i1 %exitcond.not, label %bb11.i, label %bb8.i

bb154.i:                                          ; preds = %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1608)
  %_9.i340 = icmp ult i64 %nt.sroa.0.1.i3272, %out.1
  br i1 %_9.i340, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit345, label %panic1.i341

panic1.i341:                                      ; preds = %bb154.i
  %nt.sroa.0.1.i3272.lcssa422 = phi i64 [ %nt.sroa.0.1.i3272, %bb154.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %nt.sroa.0.1.i3272.lcssa422, i64 noundef range(i64 0, 2305843009213693952) %out.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_1e808d4a560d2bfb30193cdd1b6f1f95) #13, !noalias !1611
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit345: ; preds = %bb154.i
  %69 = getelementptr inbounds nuw [4 x i8], ptr %out.0, i64 %nt.sroa.0.1.i3272
  %70 = extractelement <4 x i8> %21, i64 0
  %71 = zext i8 %70 to i32
  store i32 %71, ptr %69, align 4, !alias.scope !1608, !noalias !1613
  %_219.0.i = add i64 %miss.sroa.0.0.i3271, 1
  %_219.1.i = icmp eq i64 %miss.sroa.0.0.i3271, -1
  br i1 %_219.1.i, label %panic5.i, label %bb157.i

bb157.i:                                          ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit345
  %72 = lshr i64 %_219.0.i, 5
  %nt.sroa.0.3.i3193 = add nuw nsw i64 %nt.sroa.0.1.i3272, 1
  %_225.i3194 = icmp ne i64 %72, 0
  %_227.i3195 = icmp ult i64 %p.sroa.0.1.i3269.fr, 499991
  %or.cond45.i3196 = and i1 %_225.i3194, %_227.i3195
  br i1 %or.cond45.i3196, label %bb164.i.preheader, label %bb170.i

bb164.i.preheader:                                ; preds = %bb157.i
  %spec.store.select.i = tail call i64 @llvm.umin.i64(i64 %72, i64 1000000)
  %73 = add nsw i64 %spec.store.select.i, -1
  %74 = sub nuw nsw i64 499990, %p.sroa.0.1.i3269.fr
  %umin = call i64 @llvm.umin.i64(i64 %73, i64 %74)
  %75 = freeze i64 %umin
  %76 = xor i64 %nt.sroa.0.1.i3272, -1
  %77 = add nsw i64 %out.1, %76
  %umin293 = call i64 @llvm.umin.i64(i64 %75, i64 %77)
  %78 = add i64 %umin293, 1
  %min.iters.check = icmp ult i64 %78, 9
  br i1 %min.iters.check, label %bb164.i.preheader323, label %vector.ph

bb164.i.preheader323:                             ; preds = %vector.body, %bb164.i.preheader
  %nt.sroa.0.3.i3199.ph = phi i64 [ %nt.sroa.0.3.i3193, %bb164.i.preheader ], [ %81, %vector.body ]
  %p.sroa.0.3.i3198.ph = phi i64 [ %_29.0.i, %bb164.i.preheader ], [ %82, %vector.body ]
  %step.sroa.0.0.i3197.ph = phi i64 [ %spec.store.select.i, %bb164.i.preheader ], [ %83, %vector.body ]
  br label %bb164.i

vector.ph:                                        ; preds = %bb164.i.preheader
  %n.mod.vf = and i64 %78, 7
  %79 = icmp eq i64 %n.mod.vf, 0
  %80 = select i1 %79, i64 8, i64 %n.mod.vf
  %n.vec = sub nuw i64 %78, %80
  %81 = add i64 %nt.sroa.0.3.i3193, %n.vec
  %82 = add i64 %_29.0.i, %n.vec
  %83 = sub i64 %spec.store.select.i, %n.vec
  %84 = getelementptr i8, ptr %input.0, i64 %_29.0.i
  %85 = getelementptr [4 x i8], ptr %out.0, i64 %nt.sroa.0.3.i3193
  br label %vector.body

vector.body:                                      ; preds = %vector.body, %vector.ph
  %index = phi i64 [ 0, %vector.ph ], [ %index.next, %vector.body ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1614)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1617)
  %86 = getelementptr i8, ptr %84, i64 %index
  %87 = getelementptr inbounds nuw i8, ptr %86, i64 4
  %wide.load = load <4 x i8>, ptr %86, align 1, !alias.scope !1614, !noalias !1617
  %wide.load294 = load <4 x i8>, ptr %87, align 1, !alias.scope !1614, !noalias !1617
  %88 = getelementptr [4 x i8], ptr %85, i64 %index
  %89 = zext <4 x i8> %wide.load to <4 x i32>
  %90 = zext <4 x i8> %wide.load294 to <4 x i32>
  %91 = getelementptr inbounds nuw i8, ptr %88, i64 16
  store <4 x i32> %89, ptr %88, align 4, !alias.scope !1617, !noalias !1614
  store <4 x i32> %90, ptr %91, align 4, !alias.scope !1617, !noalias !1614
  %index.next = add nuw i64 %index, 8
  %92 = icmp eq i64 %index.next, %n.vec
  br i1 %92, label %bb164.i.preheader323, label %vector.body, !llvm.loop !1619

panic5.i:                                         ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit345
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_3040782d029b4f1f28da9c0a2089856b) #13
  unreachable

bb170.i:                                          ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit336, %bb157.i
  %p.sroa.0.3.i.lcssa = phi i64 [ %_29.0.i, %bb157.i ], [ %_231.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit336 ]
  %nt.sroa.0.3.i.lcssa = phi i64 [ %nt.sroa.0.3.i3193, %bb157.i ], [ %nt.sroa.0.3.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit336 ]
  %spec.select.i = tail call i64 @llvm.umax.i64(i64 %_29.0.i, i64 %p.sroa.0.3.i.lcssa)
  br label %bb174.i

bb164.i:                                          ; preds = %bb164.i.preheader323, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit336
  %nt.sroa.0.3.i3199 = phi i64 [ %nt.sroa.0.3.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit336 ], [ %nt.sroa.0.3.i3199.ph, %bb164.i.preheader323 ]
  %p.sroa.0.3.i3198 = phi i64 [ %_231.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit336 ], [ %p.sroa.0.3.i3198.ph, %bb164.i.preheader323 ]
  %step.sroa.0.0.i3197 = phi i64 [ %_232.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit336 ], [ %step.sroa.0.0.i3197.ph, %bb164.i.preheader323 ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1614)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1617)
  %exitcond3469.not = icmp eq i64 %nt.sroa.0.3.i3199, %out.1
  br i1 %exitcond3469.not, label %panic1.i332, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit336

panic1.i332:                                      ; preds = %bb164.i
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %out.1, i64 noundef range(i64 0, 2305843009213693952) %out.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_1e808d4a560d2bfb30193cdd1b6f1f95) #13, !noalias !1620
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit336: ; preds = %bb164.i
  %93 = getelementptr inbounds nuw i8, ptr %input.0, i64 %p.sroa.0.3.i3198
  %_5.i334 = load i8, ptr %93, align 1, !alias.scope !1614, !noalias !1617, !noundef !136
  %94 = getelementptr inbounds nuw [4 x i8], ptr %out.0, i64 %nt.sroa.0.3.i3199
  %95 = zext i8 %_5.i334 to i32
  store i32 %95, ptr %94, align 4, !alias.scope !1617, !noalias !1614
  %_231.0.i = add nuw nsw i64 %p.sroa.0.3.i3198, 1
  %_232.0.i = add nsw i64 %step.sroa.0.0.i3197, -1
  %nt.sroa.0.3.i = add i64 %nt.sroa.0.3.i3199, 1
  %_225.i = icmp ne i64 %_232.0.i, 0
  %_227.i = icmp ult i64 %p.sroa.0.3.i3198, 499991
  %or.cond45.i = select i1 %_225.i, i1 %_227.i, i1 false
  br i1 %or.cond45.i, label %bb164.i, label %bb170.i, !llvm.loop !1621

bb174.i:                                          ; preds = %bb150.i, %bb170.i
  %ins.sroa.0.3.i = phi i64 [ %spec.select150.i, %bb150.i ], [ %spec.select.i, %bb170.i ]
  %p.sroa.0.4.i = phi i64 [ %_19.0.i359, %bb150.i ], [ %p.sroa.0.3.i.lcssa, %bb170.i ]
  %miss.sroa.0.1.i = phi i64 [ 0, %bb150.i ], [ %_219.0.i, %bb170.i ]
  %nt.sroa.0.4.i = phi i64 [ %_17.0.i, %bb150.i ], [ %nt.sroa.0.3.i.lcssa, %bb170.i ]
  %_11.i = icmp ult i64 %p.sroa.0.4.i, 499992
  %_13.i = icmp ne i64 %_15.0.i, 0
  %or.cond.i = select i1 %_11.i, i1 %_13.i, i1 false
  br i1 %or.cond.i, label %bb5.i, label %bb178.i

bb18.i:                                           ; preds = %bb16.i.preheader, %bb59.i
  %nt.sroa.0.5.i3231 = phi i64 [ %_10.0.i317, %bb59.i ], [ %nt.sroa.0.1.i3272, %bb16.i.preheader ]
  %l.sroa.0.0.i3230 = phi i64 [ %l.sroa.0.1.i, %bb59.i ], [ %have.sroa.0.1.i3481, %bb16.i.preheader ]
  %d.sroa.0.0.i3229 = phi i64 [ %d.sroa.0.1.i, %bb59.i ], [ %bd.sroa.0.1.i3480, %bb16.i.preheader ]
  %p.sroa.0.5.i3228 = phi i64 [ %p.sroa.0.6.i, %bb59.i ], [ %p.sroa.0.1.i3269.fr, %bb16.i.preheader ]
  %ins.sroa.0.4.i3227 = phi i64 [ %ins.sroa.0.5.i, %bb59.i ], [ %_29.0.i, %bb16.i.preheader ]
  %_44.0.i = add i64 %p.sroa.0.5.i3228, 1
  %_41.i = icmp ult i64 %_44.0.i, 499992
  br i1 %_41.i, label %bb21.i, label %bb63.i

bb63.i:                                           ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit, %bb16.i131, %bb13.i129, %bb9.i105, %bb35.i, %bb39.i, %bb48.i, %bb59.i, %bb18.i, %bb16.i.preheader
  %ins.sroa.0.4.i.lcssa = phi i64 [ %_29.0.i, %bb16.i.preheader ], [ %_80.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit ], [ %_80.0.i, %bb16.i131 ], [ %_80.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit ], [ %_80.0.i, %bb13.i129 ], [ %_80.0.i, %bb9.i105 ], [ %ins.sroa.0.5.i, %bb59.i ], [ %_80.0.i, %bb39.i ], [ %_51.0.i, %bb35.i ], [ %_80.0.i, %bb48.i ], [ %ins.sroa.0.4.i3227, %bb18.i ]
  %p.sroa.0.5.i.lcssa = phi i64 [ %p.sroa.0.1.i3269.fr, %bb16.i.preheader ], [ %p.sroa.0.5.i3228, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit ], [ %p.sroa.0.5.i3228, %bb16.i131 ], [ %p.sroa.0.5.i3228, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit ], [ %p.sroa.0.5.i3228, %bb13.i129 ], [ %p.sroa.0.5.i3228, %bb9.i105 ], [ %p.sroa.0.6.i, %bb59.i ], [ %p.sroa.0.5.i3228, %bb39.i ], [ %p.sroa.0.5.i3228, %bb35.i ], [ %p.sroa.0.5.i3228, %bb48.i ], [ %p.sroa.0.5.i3228, %bb18.i ]
  %d.sroa.0.0.i.lcssa = phi i64 [ %bd.sroa.0.1.i3480, %bb16.i.preheader ], [ %d.sroa.0.0.i3229, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit ], [ %d.sroa.0.0.i3229, %bb16.i131 ], [ %d.sroa.0.0.i3229, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit ], [ %d.sroa.0.0.i3229, %bb13.i129 ], [ %d.sroa.0.0.i3229, %bb9.i105 ], [ %d.sroa.0.1.i, %bb59.i ], [ %d.sroa.0.0.i3229, %bb39.i ], [ %d.sroa.0.0.i3229, %bb35.i ], [ %d.sroa.0.0.i3229, %bb48.i ], [ %d.sroa.0.0.i3229, %bb18.i ]
  %l.sroa.0.0.i.lcssa = phi i64 [ %have.sroa.0.1.i3481, %bb16.i.preheader ], [ %l.sroa.0.0.i3230, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit ], [ %l.sroa.0.0.i3230, %bb16.i131 ], [ %l.sroa.0.0.i3230, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit ], [ %l.sroa.0.0.i3230, %bb13.i129 ], [ %l.sroa.0.0.i3230, %bb9.i105 ], [ %l.sroa.0.1.i, %bb59.i ], [ %l.sroa.0.0.i3230, %bb39.i ], [ %l.sroa.0.0.i3230, %bb35.i ], [ %l.sroa.0.0.i3230, %bb48.i ], [ %l.sroa.0.0.i3230, %bb18.i ]
  %nt.sroa.0.5.i.lcssa = phi i64 [ %nt.sroa.0.1.i3272, %bb16.i.preheader ], [ %nt.sroa.0.5.i3231, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit ], [ %nt.sroa.0.5.i3231, %bb16.i131 ], [ %nt.sroa.0.5.i3231, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit ], [ %nt.sroa.0.5.i3231, %bb13.i129 ], [ %nt.sroa.0.5.i3231, %bb9.i105 ], [ %_10.0.i317, %bb59.i ], [ %nt.sroa.0.5.i3231, %bb39.i ], [ %nt.sroa.0.5.i3231, %bb35.i ], [ %nt.sroa.0.5.i3231, %bb48.i ], [ %nt.sroa.0.5.i3231, %bb18.i ]
  %96 = add i64 %nt.sroa.0.5.i.lcssa, -1
  %97 = icmp ult i64 %96, %out.1
  %_110.i3246 = icmp ult i64 %l.sroa.0.0.i.lcssa, 258
  %or.cond49.i3247 = select i1 %97, i1 %_110.i3246, i1 false
  %_112.i3248 = icmp ult i64 %d.sroa.0.0.i.lcssa, %p.sroa.0.5.i.lcssa
  %or.cond149.i3249 = and i1 %or.cond49.i3247, %_112.i3248
  br i1 %or.cond149.i3249, label %bb71.i, label %bb116.i

bb21.i:                                           ; preds = %bb18.i
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1622)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1625)
  %98 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_44.0.i
  %_11.i423 = load i8, ptr %98, align 1, !alias.scope !1627, !noalias !1630, !noundef !136
  %_10.i424 = zext i8 %_11.i423 to i64
  %_9.i425 = shl nuw nsw i64 %_10.i424, 24
  %99 = getelementptr inbounds nuw i8, ptr %input.0, i64 %p.sroa.0.5.i3228
  %100 = getelementptr inbounds nuw i8, ptr %99, i64 2
  %_15.i430 = load i8, ptr %100, align 1, !alias.scope !1627, !noalias !1630, !noundef !136
  %_14.i431 = zext i8 %_15.i430 to i64
  %_13.i432 = shl nuw nsw i64 %_14.i431, 16
  %_8.i433 = or disjoint i64 %_13.i432, %_9.i425
  %101 = getelementptr inbounds nuw i8, ptr %99, i64 3
  %_21.i438 = load i8, ptr %101, align 1, !alias.scope !1627, !noalias !1630, !noundef !136
  %_20.i439 = zext i8 %_21.i438 to i64
  %_19.i440 = shl nuw nsw i64 %_20.i439, 8
  %_7.i441 = or disjoint i64 %_8.i433, %_19.i440
  %102 = getelementptr inbounds nuw i8, ptr %99, i64 4
  %_26.i446 = load i8, ptr %102, align 1, !alias.scope !1627, !noalias !1630, !noundef !136
  %_25.i447 = zext i8 %_26.i446 to i64
  %103 = or disjoint i64 %_7.i441, %_25.i447
  %104 = mul i64 %103, -7046029254386353131
  %105 = lshr i64 %104, 48
  %106 = getelementptr inbounds nuw [4 x i8], ptr %head.i, i64 %105
  %old.i183.i = load i32, ptr %106, align 4, !alias.scope !1622, !noalias !1631, !noundef !136
  %_16.i184.i = and i64 %_44.0.i, 32767
  %107 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_16.i184.i
  store i32 %old.i183.i, ptr %107, align 4, !alias.scope !1625, !noalias !1633
  %108 = trunc nuw nsw i64 %_44.0.i to i32
  store i32 %108, ptr %106, align 4, !alias.scope !1622, !noalias !1631
  %_0.i185.i = zext i32 %old.i183.i to i64
  %_51.0.i = add i64 %p.sroa.0.5.i3228, 2
  %_56.0.i = add nsw i64 %l.sroa.0.0.i3230, -1
  %spec.select.i10 = tail call i64 @llvm.umax.i64(i64 %_56.0.i, i64 3)
  %_13.0.i11 = sub i64 499999, %p.sroa.0.5.i3228
  %spec.store.select3.i12 = tail call i64 @llvm.umin.i64(i64 %_13.0.i11, i64 258)
  %spec.store.select.i39 = tail call i64 @llvm.umin.i64(i64 %_13.0.i11, i64 64)
  %_19.0.i40 = add nuw nsw i64 %spec.select.i10, %_44.0.i
  %_16.i41 = icmp ult i64 %_19.0.i40, 500000
  br i1 %_16.i41, label %bb7.i100, label %bb9.i42

bb9.i42:                                          ; preds = %bb7.i100, %bb21.i
  %pb.sroa.0.0.i43 = phi i8 [ %110, %bb7.i100 ], [ 0, %bb21.i ]
  %d.i53 = sub nsw i64 %_44.0.i, %_0.i185.i
  %_29.i54 = add nsw i64 %d.i53, -1
  %_28.i55 = icmp ult i64 %_29.i54, 32768
  br i1 %_28.i55, label %bb13.i66, label %bb35.i

bb7.i100:                                         ; preds = %bb21.i
  %109 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_19.0.i40
  %110 = load i8, ptr %109, align 1, !alias.scope !1634, !noalias !1637, !noundef !136
  br label %bb9.i42

bb13.i66:                                         ; preds = %bb9.i42
  %_34.0.i64 = add nuw nsw i64 %spec.select.i10, %_0.i185.i
  %_30.i67 = icmp ult i64 %_34.0.i64, 500000
  br i1 %_30.i67, label %bb16.i68, label %bb35.i

bb48.i56:                                         ; preds = %bb50.i
  %.not1 = icmp eq i64 %d.i53, 0
  br i1 %.not1, label %bb35.i, label %bb29.i

bb16.i68:                                         ; preds = %bb13.i66
  %111 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_34.0.i64
  %_36.i69 = load i8, ptr %111, align 1, !alias.scope !1634, !noalias !1637, !noundef !136
  %_35.i70 = icmp eq i8 %_36.i69, %pb.sroa.0.0.i43
  br i1 %_35.i70, label %bb2.i220.preheader, label %bb35.i

bb2.i220.preheader:                               ; preds = %bb16.i68
  %112 = and i64 %spec.store.select3.i12, 504
  %_19.1.i231.not.not = icmp eq i64 %p.sroa.0.5.i3228, -1
  br label %bb2.i220

bb2.i220:                                         ; preds = %bb2.i220.preheader, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit769
  %k.sroa.0.0.i1913203 = phi i64 [ %_10.0.i221, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit769 ], [ 0, %bb2.i220.preheader ]
  %_10.0.i221 = add nuw nsw i64 %k.sroa.0.0.i1913203, 8
  %_7.not.i224 = icmp samesign ugt i64 %_10.0.i221, %spec.store.select3.i12
  br i1 %_7.not.i224, label %bb17.i192, label %bb4.i225

bb4.i225:                                         ; preds = %bb2.i220
  %_15.0.i226 = add nuw nsw i64 %k.sroa.0.0.i1913203, %_0.i185.i
  %113 = icmp samesign ugt i64 %_15.0.i226, 499992
  br i1 %113, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit838, label %bb2.i774

bb17.i192:                                        ; preds = %bb2.i220
  %_26.i1963204.not = icmp eq i64 %112, %spec.store.select3.i12
  br i1 %_26.i1963204.not, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit246, label %bb21.i202

bb2.i774:                                         ; preds = %bb4.i225
  %114 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_15.0.i226
  %_15.i778 = load i8, ptr %114, align 1, !alias.scope !1639, !noalias !1637, !noundef !136
  %_14.i779 = zext i8 %_15.i778 to i64
  %_13.i780 = shl nuw i64 %_14.i779, 56
  %115 = getelementptr inbounds nuw i8, ptr %114, i64 1
  %_19.i785 = load i8, ptr %115, align 1, !alias.scope !1639, !noalias !1637, !noundef !136
  %_18.i786 = zext i8 %_19.i785 to i64
  %_17.i787 = shl nuw nsw i64 %_18.i786, 48
  %_12.i788 = or disjoint i64 %_17.i787, %_13.i780
  %116 = getelementptr inbounds nuw i8, ptr %114, i64 2
  %_25.i793 = load i8, ptr %116, align 1, !alias.scope !1639, !noalias !1637, !noundef !136
  %_24.i794 = zext i8 %_25.i793 to i64
  %_23.i795 = shl nuw nsw i64 %_24.i794, 40
  %_11.i796 = or disjoint i64 %_12.i788, %_23.i795
  %117 = getelementptr inbounds nuw i8, ptr %114, i64 3
  %_31.i801 = load i8, ptr %117, align 1, !alias.scope !1639, !noalias !1637, !noundef !136
  %_30.i802 = zext i8 %_31.i801 to i64
  %_29.i803 = shl nuw nsw i64 %_30.i802, 32
  %_10.i804 = or disjoint i64 %_11.i796, %_29.i803
  %118 = getelementptr inbounds nuw i8, ptr %114, i64 4
  %_37.i809 = load i8, ptr %118, align 1, !alias.scope !1639, !noalias !1637, !noundef !136
  %_36.i810 = zext i8 %_37.i809 to i64
  %_35.i811 = shl nuw nsw i64 %_36.i810, 24
  %_9.i812 = or disjoint i64 %_10.i804, %_35.i811
  %119 = getelementptr inbounds nuw i8, ptr %114, i64 5
  %_43.i817 = load i8, ptr %119, align 1, !alias.scope !1639, !noalias !1637, !noundef !136
  %_42.i818 = zext i8 %_43.i817 to i64
  %_41.i819 = shl nuw nsw i64 %_42.i818, 16
  %_8.i820 = or disjoint i64 %_9.i812, %_41.i819
  %120 = getelementptr inbounds nuw i8, ptr %114, i64 6
  %_49.i825 = load i8, ptr %120, align 1, !alias.scope !1639, !noalias !1637, !noundef !136
  %_48.i826 = zext i8 %_49.i825 to i64
  %_47.i827 = shl nuw nsw i64 %_48.i826, 8
  %_7.i828 = or i64 %_8.i820, %_47.i827
  %121 = getelementptr inbounds nuw i8, ptr %114, i64 7
  %_54.i833 = load i8, ptr %121, align 1, !alias.scope !1639, !noalias !1637, !noundef !136
  %_53.i834 = zext i8 %_54.i833 to i64
  %122 = or i64 %_7.i828, %_53.i834
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit838

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit838: ; preds = %bb4.i225, %bb2.i774
  %_0.sroa.0.0.i836 = phi i64 [ %122, %bb2.i774 ], [ 0, %bb4.i225 ]
  %_19.0.i230 = add nuw i64 %k.sroa.0.0.i1913203, %_44.0.i
  br i1 %_19.1.i231.not.not, label %panic2.i243, label %bb7.i232

bb7.i232:                                         ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit838
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1642)
  %_5.1.i701 = icmp ugt i64 %_19.0.i230, -9
  br i1 %_5.1.i701, label %panic.i768, label %bb1.i702

bb1.i702:                                         ; preds = %bb7.i232
  %123 = icmp ugt i64 %_19.0.i230, 499992
  br i1 %123, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit769, label %bb2.i705

panic.i768:                                       ; preds = %bb7.i232
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_440babfea49fec204c4bfa4556bd23df) #13, !noalias !1645
  unreachable

bb2.i705:                                         ; preds = %bb1.i702
  %124 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_19.0.i230
  %_15.i709 = load i8, ptr %124, align 1, !alias.scope !1642, !noalias !1637, !noundef !136
  %_14.i710 = zext i8 %_15.i709 to i64
  %_13.i711 = shl nuw i64 %_14.i710, 56
  %125 = getelementptr inbounds nuw i8, ptr %124, i64 1
  %_19.i716 = load i8, ptr %125, align 1, !alias.scope !1642, !noalias !1637, !noundef !136
  %_18.i717 = zext i8 %_19.i716 to i64
  %_17.i718 = shl nuw nsw i64 %_18.i717, 48
  %_12.i719 = or disjoint i64 %_17.i718, %_13.i711
  %126 = getelementptr inbounds nuw i8, ptr %124, i64 2
  %_25.i724 = load i8, ptr %126, align 1, !alias.scope !1642, !noalias !1637, !noundef !136
  %_24.i725 = zext i8 %_25.i724 to i64
  %_23.i726 = shl nuw nsw i64 %_24.i725, 40
  %_11.i727 = or disjoint i64 %_12.i719, %_23.i726
  %127 = getelementptr inbounds nuw i8, ptr %124, i64 3
  %_31.i732 = load i8, ptr %127, align 1, !alias.scope !1642, !noalias !1637, !noundef !136
  %_30.i733 = zext i8 %_31.i732 to i64
  %_29.i734 = shl nuw nsw i64 %_30.i733, 32
  %_10.i735 = or disjoint i64 %_11.i727, %_29.i734
  %128 = getelementptr inbounds nuw i8, ptr %124, i64 4
  %_37.i740 = load i8, ptr %128, align 1, !alias.scope !1642, !noalias !1637, !noundef !136
  %_36.i741 = zext i8 %_37.i740 to i64
  %_35.i742 = shl nuw nsw i64 %_36.i741, 24
  %_9.i743 = or disjoint i64 %_10.i735, %_35.i742
  %129 = getelementptr inbounds nuw i8, ptr %124, i64 5
  %_43.i748 = load i8, ptr %129, align 1, !alias.scope !1642, !noalias !1637, !noundef !136
  %_42.i749 = zext i8 %_43.i748 to i64
  %_41.i750 = shl nuw nsw i64 %_42.i749, 16
  %_8.i751 = or disjoint i64 %_9.i743, %_41.i750
  %130 = getelementptr inbounds nuw i8, ptr %124, i64 6
  %_49.i756 = load i8, ptr %130, align 1, !alias.scope !1642, !noalias !1637, !noundef !136
  %_48.i757 = zext i8 %_49.i756 to i64
  %_47.i758 = shl nuw nsw i64 %_48.i757, 8
  %_7.i759 = or i64 %_8.i751, %_47.i758
  %131 = getelementptr inbounds nuw i8, ptr %124, i64 7
  %_54.i764 = load i8, ptr %131, align 1, !alias.scope !1642, !noalias !1637, !noundef !136
  %_53.i765 = zext i8 %_54.i764 to i64
  %132 = or i64 %_7.i759, %_53.i765
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit769

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit769: ; preds = %bb1.i702, %bb2.i705
  %_0.sroa.0.0.i767 = phi i64 [ %132, %bb2.i705 ], [ 0, %bb1.i702 ]
  %133 = icmp eq i64 %_0.sroa.0.0.i836, %_0.sroa.0.0.i767
  br i1 %133, label %bb2.i220, label %bb17.i192.thread

panic2.i243:                                      ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit838
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_8dedf8bdbae2e7f670fff12535f0d90a) #13, !noalias !1637
  unreachable

bb17.i192.thread:                                 ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit769
  %_0.sroa.0.0.i767.lcssa = phi i64 [ %_0.sroa.0.0.i767, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit769 ]
  %_0.sroa.0.0.i836.lcssa338 = phi i64 [ %_0.sroa.0.0.i836, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit769 ]
  %k.sroa.0.0.i1913203.lcssa336 = phi i64 [ %k.sroa.0.0.i1913203, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit769 ]
  %x.i235 = xor i64 %_0.sroa.0.0.i767.lcssa, %_0.sroa.0.0.i836.lcssa338
  %134 = tail call range(i64 0, 65) i64 @llvm.ctlz.i64(i64 %x.i235, i1 true)
  %_2220.i236 = lshr i64 %134, 3
  %_24.0.i237 = or disjoint i64 %_2220.i236, %k.sroa.0.0.i1913203.lcssa336
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit246

bb21.i202:                                        ; preds = %bb17.i192, %bb24.i212
  %k.sroa.0.2.i1953206 = phi i64 [ %k.sroa.0.3.i217, %bb24.i212 ], [ %112, %bb17.i192 ]
  %_32.0.i200 = add nuw nsw i64 %k.sroa.0.2.i1953206, %_0.i185.i
  %_34.i203 = icmp samesign ult i64 %_32.0.i200, 500000
  br i1 %_34.i203, label %bb22.i205, label %panic6.i204

bb22.i205:                                        ; preds = %bb21.i202
  %135 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_32.0.i200
  %_29.i206 = load i8, ptr %135, align 1, !alias.scope !1646, !noalias !1637, !noundef !136
  %_38.0.i207 = add nuw nsw i64 %k.sroa.0.2.i1953206, %_44.0.i
  %_38.1.i208.not = icmp ugt i64 %_38.0.i207, %p.sroa.0.5.i3228
  br i1 %_38.1.i208.not, label %bb23.i209, label %panic7.i218

panic6.i204:                                      ; preds = %bb21.i202
  %_32.0.i200.lcssa = phi i64 [ %_32.0.i200, %bb21.i202 ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_32.0.i200.lcssa, i64 noundef range(i64 0, -9223372036854775808) 500000, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_d0bf91bac5912d1054a41f50a5372dd0) #13, !noalias !1637
  unreachable

bb23.i209:                                        ; preds = %bb22.i205
  %_39.i210 = icmp ult i64 %_38.0.i207, 500000
  br i1 %_39.i210, label %bb24.i212, label %panic8.i211

panic7.i218:                                      ; preds = %bb22.i205
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_e58248ce06d86db1620e3928ca18f57a) #13, !noalias !1637
  unreachable

bb24.i212:                                        ; preds = %bb23.i209
  %136 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_38.0.i207
  %_35.i213 = load i8, ptr %136, align 1, !alias.scope !1646, !noalias !1637, !noundef !136
  %_28.i214 = icmp eq i8 %_29.i206, %_35.i213
  %_40.0.i215 = zext i1 %_28.i214 to i64
  %k.sroa.0.3.i217 = add nuw nsw i64 %k.sroa.0.2.i1953206, %_40.0.i215
  %_26.i196 = icmp samesign ult i64 %k.sroa.0.3.i217, %spec.store.select3.i12
  %or.cond.i197 = select i1 %_28.i214, i1 %_26.i196, i1 false
  br i1 %or.cond.i197, label %bb21.i202, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit246

panic8.i211:                                      ; preds = %bb23.i209
  %_38.0.i207.lcssa342 = phi i64 [ %_38.0.i207, %bb23.i209 ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_38.0.i207.lcssa342, i64 noundef range(i64 0, -9223372036854775808) 500000, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_c7cb404ab9612aded1ce50ca918ced7b) #13, !noalias !1637
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit246: ; preds = %bb24.i212, %bb17.i192.thread, %bb17.i192
  %k.sroa.0.2.i195.lcssa = phi i64 [ %112, %bb17.i192 ], [ %_24.0.i237, %bb17.i192.thread ], [ %k.sroa.0.3.i217, %bb24.i212 ]
  %_46.i88 = icmp ugt i64 %k.sroa.0.2.i195.lcssa, %spec.select.i10
  br i1 %_46.i88, label %bb19.i89, label %bb35.i

bb19.i89:                                         ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit246
  %137 = add i64 %k.sroa.0.2.i195.lcssa, -11
  %or.cond.i993 = icmp ult i64 %137, 247
  br i1 %or.cond.i993, label %bb6.i1015, label %bb7.i994

bb7.i994:                                         ; preds = %bb6.i1015, %bb19.i89
  %c.sroa.0.0.i995 = phi i32 [ %140, %bb6.i1015 ], [ 168, %bb19.i89 ]
  %_17.i996 = icmp ugt i64 %d.i53, 4
  br i1 %_17.i996, label %bb12.i1011, label %bb13.i997

bb6.i1015:                                        ; preds = %bb19.i89
  %138 = trunc nuw nsw i64 %k.sroa.0.2.i195.lcssa to i32
  %_11.i1016 = add nsw i32 %138, -3
  %_10.i1017 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_11.i1016, i1 false)
  %139 = shl nuw nsw i32 %_10.i1017, 4
  %140 = sub nuw nsw i32 632, %139
  br label %bb7.i994

bb13.i997:                                        ; preds = %bb12.i1011, %bb7.i994
  %c.sroa.0.1.i998 = phi i32 [ %144, %bb12.i1011 ], [ %c.sroa.0.0.i995, %bb7.i994 ]
  %_29.i999 = trunc i64 %k.sroa.0.2.i195.lcssa to i32
  %141 = add i32 %_29.i999, -33554432
  %_30.1.i1000 = icmp ult i32 %141, -67108864
  br i1 %_30.1.i1000, label %panic8.i1007, label %bb14.i1001

bb12.i1011:                                       ; preds = %bb7.i994
  %142 = trunc nuw i64 %d.i53 to i32
  %_22.i1009 = add nsw i32 %142, -1
  %_21.i1012 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_22.i1009, i1 true)
  %143 = shl nuw nsw i32 %_21.i1012, 4
  %reass.sub = sub nsw i32 %c.sroa.0.0.i995, %143
  %144 = add nsw i32 %reass.sub, 480
  br label %bb13.i997

bb14.i1001:                                       ; preds = %bb13.i997
  %_30.0.i1002 = shl nsw i32 %_29.i999, 6
  %145 = tail call { i32, i1 } @llvm.ssub.with.overflow.i32(i32 %_30.0.i1002, i32 %c.sroa.0.1.i998)
  %_31.1.i1003 = extractvalue { i32, i1 } %145, 1
  br i1 %_31.1.i1003, label %panic9.i1006, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1018

panic8.i1007:                                     ; preds = %bb13.i997
; call core::panicking::panic_const::panic_const_mul_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_mul_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_5bf2e340c7b7e1a7a2cf8d7086d6ac68) #13, !noalias !1637
  unreachable

panic9.i1006:                                     ; preds = %bb14.i1001
; call core::panicking::panic_const::panic_const_sub_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_5bf2e340c7b7e1a7a2cf8d7086d6ac68) #13, !noalias !1637
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1018: ; preds = %bb14.i1001
  %_31.0.i1005 = extractvalue { i32, i1 } %145, 0
  %_49.i = icmp sgt i32 %_31.0.i1005, -1000000
  br i1 %_49.i, label %bb50.i, label %bb35.i

bb50.i:                                           ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1018
  %_51.not.i90 = icmp uge i64 %k.sroa.0.2.i195.lcssa, %spec.store.select.i39
  %_55.0.i92 = add nuw i64 %k.sroa.0.2.i195.lcssa, %_44.0.i
  %_55.1.i93.not = icmp ugt i64 %_55.0.i92, %p.sroa.0.5.i3228
  %or.cond3738 = select i1 %_51.not.i90, i1 true, i1 %_55.1.i93.not
  br i1 %or.cond3738, label %bb48.i56, label %panic7.i97

panic7.i97:                                       ; preds = %bb50.i
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_f7734e5b3c0057e9bae084232237166a) #13, !noalias !1637
  unreachable

bb35.i:                                           ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit246, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1018, %bb16.i68, %bb48.i56, %bb13.i66, %bb9.i42, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1044
  %_70.i = icmp ult i64 %_51.0.i, 499992
  br i1 %_70.i, label %bb39.i, label %bb63.i

bb29.i:                                           ; preds = %bb48.i56
  br i1 %or.cond.i993, label %bb6.i1067, label %bb7.i1046

bb7.i1046:                                        ; preds = %bb6.i1067, %bb29.i
  %c.sroa.0.0.i1047 = phi i32 [ %147, %bb6.i1067 ], [ 168, %bb29.i ]
  br i1 %_17.i996, label %bb12.i1063, label %bb14.i1053

bb6.i1067:                                        ; preds = %bb29.i
  %_11.i1068 = add nsw i32 %_29.i999, -3
  %_10.i1069 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_11.i1068, i1 false)
  %146 = shl nuw nsw i32 %_10.i1069, 4
  %147 = sub nuw nsw i32 632, %146
  br label %bb7.i1046

bb12.i1063:                                       ; preds = %bb7.i1046
  %148 = trunc nuw i64 %d.i53 to i32
  %_22.i1061 = add nsw i32 %148, -1
  %_21.i1064 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_22.i1061, i1 true)
  %149 = shl nuw nsw i32 %_21.i1064, 4
  %reass.sub3280 = sub nsw i32 %c.sroa.0.0.i1047, %149
  %150 = add nsw i32 %reass.sub3280, 480
  br label %bb14.i1053

bb14.i1053:                                       ; preds = %bb7.i1046, %bb12.i1063
  %c.sroa.0.1.i1050 = phi i32 [ %150, %bb12.i1063 ], [ %c.sroa.0.0.i1047, %bb7.i1046 ]
  %151 = tail call { i32, i1 } @llvm.ssub.with.overflow.i32(i32 %_30.0.i1002, i32 %c.sroa.0.1.i1050)
  %_31.1.i1055 = extractvalue { i32, i1 } %151, 1
  br i1 %_31.1.i1055, label %panic9.i1058, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1070

panic9.i1058:                                     ; preds = %bb14.i1053
; call core::panicking::panic_const::panic_const_sub_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_5bf2e340c7b7e1a7a2cf8d7086d6ac68) #13
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1070: ; preds = %bb14.i1053
  %_31.0.i1057 = extractvalue { i32, i1 } %151, 0
  %152 = add nsw i64 %l.sroa.0.0.i3230, -11
  %or.cond.i1019 = icmp ult i64 %152, 247
  br i1 %or.cond.i1019, label %bb6.i1041, label %bb7.i1020

bb7.i1020:                                        ; preds = %bb6.i1041, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1070
  %c.sroa.0.0.i1021 = phi i32 [ %155, %bb6.i1041 ], [ 168, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1070 ]
  %_17.i1022 = icmp ugt i64 %d.sroa.0.0.i3229, 4
  br i1 %_17.i1022, label %bb8.i1034, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1044

bb6.i1041:                                        ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1070
  %153 = trunc nuw nsw i64 %l.sroa.0.0.i3230 to i32
  %_11.i1042 = add nsw i32 %153, -3
  %_10.i1043 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_11.i1042, i1 false)
  %154 = shl nuw nsw i32 %_10.i1043, 4
  %155 = sub nuw nsw i32 632, %154
  br label %bb7.i1020

bb8.i1034:                                        ; preds = %bb7.i1020
  %156 = trunc i64 %d.sroa.0.0.i3229 to i32
  %_22.i1035 = add i32 %156, -1
  %_25.1.i1036 = icmp ult i32 %_22.i1035, 2
  br i1 %_25.1.i1036, label %panic5.i1040, label %bb12.i1037

panic5.i1040:                                     ; preds = %bb8.i1034
; call core::panicking::panic_const::panic_const_sub_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_9f4d1cf899b26bf5e0e440ccaea53f2f) #13
  unreachable

bb12.i1037:                                       ; preds = %bb8.i1034
  %_21.i1038 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_22.i1035, i1 true)
  %157 = shl nuw nsw i32 %_21.i1038, 4
  %reass.sub3281 = sub nsw i32 %c.sroa.0.0.i1021, %157
  %158 = add nsw i32 %reass.sub3281, 480
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1044

_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1044: ; preds = %bb12.i1037, %bb7.i1020
  %c.sroa.0.1.i1024 = phi i32 [ %158, %bb12.i1037 ], [ %c.sroa.0.0.i1021, %bb7.i1020 ]
  %_29.i1025 = trunc nuw nsw i64 %l.sroa.0.0.i3230 to i32
  %_30.0.i1028 = shl nuw nsw i32 %_29.i1025, 6
  %159 = sub nsw i32 %_30.0.i1028, %c.sroa.0.1.i1024
  %_62.i = icmp sgt i32 %_31.0.i1057, %159
  br i1 %_62.i, label %bb32.i, label %bb35.i

bb32.i:                                           ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1044
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1649)
  %_9.i = icmp ult i64 %nt.sroa.0.5.i3231, %out.1
  br i1 %_9.i, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit, label %panic1.i307

panic1.i307:                                      ; preds = %bb32.i
  %nt.sroa.0.5.i3231.lcssa360 = phi i64 [ %nt.sroa.0.5.i3231, %bb32.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %nt.sroa.0.5.i3231.lcssa360, i64 noundef range(i64 0, 2305843009213693952) %out.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_1e808d4a560d2bfb30193cdd1b6f1f95) #13, !noalias !1652
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit: ; preds = %bb32.i
  %_5.i = load i8, ptr %99, align 1, !alias.scope !1649, !noalias !1654, !noundef !136
  br label %bb59.i

bb39.i:                                           ; preds = %bb35.i
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1655)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1658)
  %_9.i391 = shl nuw nsw i64 %_14.i431, 24
  %_13.i398 = shl nuw nsw i64 %_20.i439, 16
  %_8.i399 = or disjoint i64 %_13.i398, %_9.i391
  %_19.i406 = shl nuw nsw i64 %_25.i447, 8
  %_7.i407 = or disjoint i64 %_8.i399, %_19.i406
  %160 = getelementptr inbounds nuw i8, ptr %99, i64 5
  %_26.i412 = load i8, ptr %160, align 1, !alias.scope !1660, !noalias !1663, !noundef !136
  %_25.i413 = zext i8 %_26.i412 to i64
  %161 = or disjoint i64 %_7.i407, %_25.i413
  %162 = mul i64 %161, -7046029254386353131
  %163 = lshr i64 %162, 48
  %164 = getelementptr inbounds nuw [4 x i8], ptr %head.i, i64 %163
  %old.i176.i = load i32, ptr %164, align 4, !alias.scope !1655, !noalias !1664, !noundef !136
  %_16.i177.i = and i64 %_51.0.i, 32767
  %165 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_16.i177.i
  store i32 %old.i176.i, ptr %165, align 4, !alias.scope !1658, !noalias !1666
  %166 = trunc nuw nsw i64 %_51.0.i to i32
  store i32 %166, ptr %164, align 4, !alias.scope !1655, !noalias !1664
  %_0.i178.i = zext i32 %old.i176.i to i64
  %_80.0.i = add nuw nsw i64 %p.sroa.0.5.i3228, 3
  %_84.0.i = sub i64 499998, %p.sroa.0.5.i3228
  %_81.i = icmp ult i64 %_56.0.i, %_84.0.i
  br i1 %_81.i, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_findKj8000_EB4_.exit, label %bb63.i

_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_findKj8000_EB4_.exit: ; preds = %bb39.i
  %spec.store.select3.i = tail call i64 @llvm.umin.i64(i64 %_84.0.i, i64 258)
  %_19.0.i103 = add nuw nsw i64 %spec.select.i10, %_51.0.i
  %_16.i104 = icmp ult i64 %_19.0.i103, 500000
  br i1 %_16.i104, label %bb7.i166, label %bb9.i105

bb9.i105:                                         ; preds = %bb7.i166, %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_findKj8000_EB4_.exit
  %pb.sroa.0.0.i106 = phi i8 [ %168, %bb7.i166 ], [ 0, %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_findKj8000_EB4_.exit ]
  %d.i116 = sub nsw i64 %_51.0.i, %_0.i178.i
  %_29.i117 = add nsw i64 %d.i116, -1
  %_28.i118 = icmp ult i64 %_29.i117, 32768
  br i1 %_28.i118, label %bb13.i129, label %bb63.i

bb7.i166:                                         ; preds = %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_findKj8000_EB4_.exit
  %167 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_19.0.i103
  %168 = load i8, ptr %167, align 1, !alias.scope !1667, !noalias !1670, !noundef !136
  br label %bb9.i105

bb13.i129:                                        ; preds = %bb9.i105
  %_34.0.i127 = add nuw nsw i64 %spec.select.i10, %_0.i178.i
  %_30.i130 = icmp ult i64 %_34.0.i127, 500000
  br i1 %_30.i130, label %bb16.i131, label %bb63.i

bb16.i131:                                        ; preds = %bb13.i129
  %169 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_34.0.i127
  %_36.i132 = load i8, ptr %169, align 1, !alias.scope !1667, !noalias !1670, !noundef !136
  %_35.i133 = icmp eq i8 %_36.i132, %pb.sroa.0.0.i106
  br i1 %_35.i133, label %bb2.i.preheader, label %bb63.i

bb2.i.preheader:                                  ; preds = %bb16.i131
  %170 = and i64 %spec.store.select3.i, 504
  br label %bb2.i

bb2.i:                                            ; preds = %bb2.i.preheader, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit907
  %k.sroa.0.0.i3215 = phi i64 [ %_10.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit907 ], [ 0, %bb2.i.preheader ]
  %_10.0.i = add nuw nsw i64 %k.sroa.0.0.i3215, 8
  %_7.not.i = icmp samesign ugt i64 %_10.0.i, %spec.store.select3.i
  br i1 %_7.not.i, label %bb17.i169, label %bb4.i

bb4.i:                                            ; preds = %bb2.i
  %_15.0.i181 = add nuw nsw i64 %k.sroa.0.0.i3215, %_0.i178.i
  %171 = icmp samesign ugt i64 %_15.0.i181, 499992
  br i1 %171, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit976, label %bb2.i912

bb17.i169:                                        ; preds = %bb2.i
  %_26.i3216.not = icmp eq i64 %170, %spec.store.select3.i
  br i1 %_26.i3216.not, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit, label %bb21.i173

bb2.i912:                                         ; preds = %bb4.i
  %172 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_15.0.i181
  %_15.i916 = load i8, ptr %172, align 1, !alias.scope !1672, !noalias !1670, !noundef !136
  %_14.i917 = zext i8 %_15.i916 to i64
  %_13.i918 = shl nuw i64 %_14.i917, 56
  %173 = getelementptr inbounds nuw i8, ptr %172, i64 1
  %_19.i923 = load i8, ptr %173, align 1, !alias.scope !1672, !noalias !1670, !noundef !136
  %_18.i924 = zext i8 %_19.i923 to i64
  %_17.i925 = shl nuw nsw i64 %_18.i924, 48
  %_12.i926 = or disjoint i64 %_17.i925, %_13.i918
  %174 = getelementptr inbounds nuw i8, ptr %172, i64 2
  %_25.i931 = load i8, ptr %174, align 1, !alias.scope !1672, !noalias !1670, !noundef !136
  %_24.i932 = zext i8 %_25.i931 to i64
  %_23.i933 = shl nuw nsw i64 %_24.i932, 40
  %_11.i934 = or disjoint i64 %_12.i926, %_23.i933
  %175 = getelementptr inbounds nuw i8, ptr %172, i64 3
  %_31.i939 = load i8, ptr %175, align 1, !alias.scope !1672, !noalias !1670, !noundef !136
  %_30.i940 = zext i8 %_31.i939 to i64
  %_29.i941 = shl nuw nsw i64 %_30.i940, 32
  %_10.i942 = or disjoint i64 %_11.i934, %_29.i941
  %176 = getelementptr inbounds nuw i8, ptr %172, i64 4
  %_37.i947 = load i8, ptr %176, align 1, !alias.scope !1672, !noalias !1670, !noundef !136
  %_36.i948 = zext i8 %_37.i947 to i64
  %_35.i949 = shl nuw nsw i64 %_36.i948, 24
  %_9.i950 = or disjoint i64 %_10.i942, %_35.i949
  %177 = getelementptr inbounds nuw i8, ptr %172, i64 5
  %_43.i955 = load i8, ptr %177, align 1, !alias.scope !1672, !noalias !1670, !noundef !136
  %_42.i956 = zext i8 %_43.i955 to i64
  %_41.i957 = shl nuw nsw i64 %_42.i956, 16
  %_8.i958 = or disjoint i64 %_9.i950, %_41.i957
  %178 = getelementptr inbounds nuw i8, ptr %172, i64 6
  %_49.i963 = load i8, ptr %178, align 1, !alias.scope !1672, !noalias !1670, !noundef !136
  %_48.i964 = zext i8 %_49.i963 to i64
  %_47.i965 = shl nuw nsw i64 %_48.i964, 8
  %_7.i966 = or i64 %_8.i958, %_47.i965
  %179 = getelementptr inbounds nuw i8, ptr %172, i64 7
  %_54.i971 = load i8, ptr %179, align 1, !alias.scope !1672, !noalias !1670, !noundef !136
  %_53.i972 = zext i8 %_54.i971 to i64
  %180 = or i64 %_7.i966, %_53.i972
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit976

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit976: ; preds = %bb4.i, %bb2.i912
  %_0.sroa.0.0.i974 = phi i64 [ %180, %bb2.i912 ], [ 0, %bb4.i ]
  %_19.0.i183 = add nuw i64 %k.sroa.0.0.i3215, %_51.0.i
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1675)
  %_5.1.i839 = icmp ugt i64 %_19.0.i183, -9
  br i1 %_5.1.i839, label %panic.i906, label %bb1.i840

bb1.i840:                                         ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit976
  %181 = icmp ugt i64 %_19.0.i183, 499992
  br i1 %181, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit907, label %bb2.i843

panic.i906:                                       ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit976
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_440babfea49fec204c4bfa4556bd23df) #13, !noalias !1678
  unreachable

bb2.i843:                                         ; preds = %bb1.i840
  %182 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_19.0.i183
  %_15.i847 = load i8, ptr %182, align 1, !alias.scope !1675, !noalias !1670, !noundef !136
  %_14.i848 = zext i8 %_15.i847 to i64
  %_13.i849 = shl nuw i64 %_14.i848, 56
  %183 = getelementptr inbounds nuw i8, ptr %182, i64 1
  %_19.i854 = load i8, ptr %183, align 1, !alias.scope !1675, !noalias !1670, !noundef !136
  %_18.i855 = zext i8 %_19.i854 to i64
  %_17.i856 = shl nuw nsw i64 %_18.i855, 48
  %_12.i857 = or disjoint i64 %_17.i856, %_13.i849
  %184 = getelementptr inbounds nuw i8, ptr %182, i64 2
  %_25.i862 = load i8, ptr %184, align 1, !alias.scope !1675, !noalias !1670, !noundef !136
  %_24.i863 = zext i8 %_25.i862 to i64
  %_23.i864 = shl nuw nsw i64 %_24.i863, 40
  %_11.i865 = or disjoint i64 %_12.i857, %_23.i864
  %185 = getelementptr inbounds nuw i8, ptr %182, i64 3
  %_31.i870 = load i8, ptr %185, align 1, !alias.scope !1675, !noalias !1670, !noundef !136
  %_30.i871 = zext i8 %_31.i870 to i64
  %_29.i872 = shl nuw nsw i64 %_30.i871, 32
  %_10.i873 = or disjoint i64 %_11.i865, %_29.i872
  %186 = getelementptr inbounds nuw i8, ptr %182, i64 4
  %_37.i878 = load i8, ptr %186, align 1, !alias.scope !1675, !noalias !1670, !noundef !136
  %_36.i879 = zext i8 %_37.i878 to i64
  %_35.i880 = shl nuw nsw i64 %_36.i879, 24
  %_9.i881 = or disjoint i64 %_10.i873, %_35.i880
  %187 = getelementptr inbounds nuw i8, ptr %182, i64 5
  %_43.i886 = load i8, ptr %187, align 1, !alias.scope !1675, !noalias !1670, !noundef !136
  %_42.i887 = zext i8 %_43.i886 to i64
  %_41.i888 = shl nuw nsw i64 %_42.i887, 16
  %_8.i889 = or disjoint i64 %_9.i881, %_41.i888
  %188 = getelementptr inbounds nuw i8, ptr %182, i64 6
  %_49.i894 = load i8, ptr %188, align 1, !alias.scope !1675, !noalias !1670, !noundef !136
  %_48.i895 = zext i8 %_49.i894 to i64
  %_47.i896 = shl nuw nsw i64 %_48.i895, 8
  %_7.i897 = or i64 %_8.i889, %_47.i896
  %189 = getelementptr inbounds nuw i8, ptr %182, i64 7
  %_54.i902 = load i8, ptr %189, align 1, !alias.scope !1675, !noalias !1670, !noundef !136
  %_53.i903 = zext i8 %_54.i902 to i64
  %190 = or i64 %_7.i897, %_53.i903
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit907

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit907: ; preds = %bb1.i840, %bb2.i843
  %_0.sroa.0.0.i905 = phi i64 [ %190, %bb2.i843 ], [ 0, %bb1.i840 ]
  %191 = icmp eq i64 %_0.sroa.0.0.i974, %_0.sroa.0.0.i905
  br i1 %191, label %bb2.i, label %bb17.i169.thread

bb17.i169.thread:                                 ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit907
  %_0.sroa.0.0.i905.lcssa = phi i64 [ %_0.sroa.0.0.i905, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit907 ]
  %_0.sroa.0.0.i974.lcssa346 = phi i64 [ %_0.sroa.0.0.i974, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit907 ]
  %k.sroa.0.0.i3215.lcssa345 = phi i64 [ %k.sroa.0.0.i3215, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit907 ]
  %x.i = xor i64 %_0.sroa.0.0.i905.lcssa, %_0.sroa.0.0.i974.lcssa346
  %192 = tail call range(i64 0, 65) i64 @llvm.ctlz.i64(i64 %x.i, i1 true)
  %_2220.i = lshr i64 %192, 3
  %_24.0.i = or disjoint i64 %_2220.i, %k.sroa.0.0.i3215.lcssa345
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit

bb21.i173:                                        ; preds = %bb17.i169, %bb24.i
  %k.sroa.0.2.i3218 = phi i64 [ %k.sroa.0.3.i, %bb24.i ], [ %170, %bb17.i169 ]
  %_32.0.i = add nuw nsw i64 %k.sroa.0.2.i3218, %_0.i178.i
  %_34.i = icmp samesign ult i64 %_32.0.i, 500000
  br i1 %_34.i, label %bb23.i, label %panic6.i

panic6.i:                                         ; preds = %bb21.i173
  %_32.0.i.lcssa = phi i64 [ %_32.0.i, %bb21.i173 ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_32.0.i.lcssa, i64 noundef range(i64 0, -9223372036854775808) 500000, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_d0bf91bac5912d1054a41f50a5372dd0) #13, !noalias !1670
  unreachable

bb23.i:                                           ; preds = %bb21.i173
  %_38.0.i = add nuw nsw i64 %k.sroa.0.2.i3218, %_51.0.i
  %_39.i175 = icmp ult i64 %_38.0.i, 500000
  br i1 %_39.i175, label %bb24.i, label %panic8.i

bb24.i:                                           ; preds = %bb23.i
  %193 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_32.0.i
  %_29.i174 = load i8, ptr %193, align 1, !alias.scope !1679, !noalias !1670, !noundef !136
  %194 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_38.0.i
  %_35.i176 = load i8, ptr %194, align 1, !alias.scope !1679, !noalias !1670, !noundef !136
  %_28.i177 = icmp eq i8 %_29.i174, %_35.i176
  %_40.0.i = zext i1 %_28.i177 to i64
  %k.sroa.0.3.i = add nuw nsw i64 %k.sroa.0.2.i3218, %_40.0.i
  %_26.i = icmp samesign ult i64 %k.sroa.0.3.i, %spec.store.select3.i
  %or.cond.i171 = select i1 %_28.i177, i1 %_26.i, i1 false
  br i1 %or.cond.i171, label %bb21.i173, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit

panic8.i:                                         ; preds = %bb23.i
  %_38.0.i.lcssa = phi i64 [ %_38.0.i, %bb23.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_38.0.i.lcssa, i64 noundef range(i64 0, -9223372036854775808) 500000, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_c7cb404ab9612aded1ce50ca918ced7b) #13, !noalias !1670
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit: ; preds = %bb24.i, %bb17.i169.thread, %bb17.i169
  %k.sroa.0.2.i.lcssa = phi i64 [ %170, %bb17.i169 ], [ %_24.0.i, %bb17.i169.thread ], [ %k.sroa.0.3.i, %bb24.i ]
  %_46.i151 = icmp ugt i64 %k.sroa.0.2.i.lcssa, %spec.select.i10
  br i1 %_46.i151, label %bb19.i152, label %bb63.i

bb19.i152:                                        ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit
  %195 = add i64 %k.sroa.0.2.i.lcssa, -11
  %or.cond.i977 = icmp ult i64 %195, 247
  br i1 %or.cond.i977, label %bb6.i, label %bb7.i978

bb7.i978:                                         ; preds = %bb6.i, %bb19.i152
  %c.sroa.0.0.i = phi i32 [ %198, %bb6.i ], [ 168, %bb19.i152 ]
  %_17.i979 = icmp ugt i64 %d.i116, 4
  br i1 %_17.i979, label %bb12.i988, label %bb13.i980

bb6.i:                                            ; preds = %bb19.i152
  %196 = trunc nuw nsw i64 %k.sroa.0.2.i.lcssa to i32
  %_11.i991 = add nsw i32 %196, -3
  %_10.i992 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_11.i991, i1 false)
  %197 = shl nuw nsw i32 %_10.i992, 4
  %198 = sub nuw nsw i32 632, %197
  br label %bb7.i978

bb13.i980:                                        ; preds = %bb12.i988, %bb7.i978
  %c.sroa.0.1.i = phi i32 [ %202, %bb12.i988 ], [ %c.sroa.0.0.i, %bb7.i978 ]
  %_29.i981 = trunc i64 %k.sroa.0.2.i.lcssa to i32
  %199 = add i32 %_29.i981, -33554432
  %_30.1.i = icmp ult i32 %199, -67108864
  br i1 %_30.1.i, label %panic8.i985, label %bb14.i982

bb12.i988:                                        ; preds = %bb7.i978
  %200 = trunc nuw i64 %d.i116 to i32
  %_22.i987 = add nsw i32 %200, -1
  %_21.i989 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_22.i987, i1 true)
  %201 = shl nuw nsw i32 %_21.i989, 4
  %reass.sub3282 = sub nsw i32 %c.sroa.0.0.i, %201
  %202 = add nsw i32 %reass.sub3282, 480
  br label %bb13.i980

bb14.i982:                                        ; preds = %bb13.i980
  %_30.0.i = shl nsw i32 %_29.i981, 6
  %203 = tail call { i32, i1 } @llvm.ssub.with.overflow.i32(i32 %_30.0.i, i32 %c.sroa.0.1.i)
  %_31.1.i = extractvalue { i32, i1 } %203, 1
  br i1 %_31.1.i, label %panic9.i984, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit

panic8.i985:                                      ; preds = %bb13.i980
; call core::panicking::panic_const::panic_const_mul_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_mul_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_5bf2e340c7b7e1a7a2cf8d7086d6ac68) #13, !noalias !1670
  unreachable

panic9.i984:                                      ; preds = %bb14.i982
; call core::panicking::panic_const::panic_const_sub_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_5bf2e340c7b7e1a7a2cf8d7086d6ac68) #13, !noalias !1670
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit: ; preds = %bb14.i982
  %_31.0.i = extractvalue { i32, i1 } %203, 0
  %_49.i154 = icmp slt i32 %_31.0.i, -999999
  %.not2 = icmp eq i64 %d.i116, 0
  %or.cond = or i1 %_49.i154, %.not2
  br i1 %or.cond, label %bb63.i, label %bb45.i

bb45.i:                                           ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit
  br i1 %or.cond.i977, label %bb6.i1119, label %bb7.i1098

bb7.i1098:                                        ; preds = %bb6.i1119, %bb45.i
  %c.sroa.0.0.i1099 = phi i32 [ %205, %bb6.i1119 ], [ 168, %bb45.i ]
  br i1 %_17.i979, label %bb12.i1115, label %bb14.i1105

bb6.i1119:                                        ; preds = %bb45.i
  %_11.i1120 = add nsw i32 %_29.i981, -3
  %_10.i1121 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_11.i1120, i1 false)
  %204 = shl nuw nsw i32 %_10.i1121, 4
  %205 = sub nuw nsw i32 632, %204
  br label %bb7.i1098

bb12.i1115:                                       ; preds = %bb7.i1098
  %206 = trunc nuw i64 %d.i116 to i32
  %_22.i1113 = add nsw i32 %206, -1
  %_21.i1116 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_22.i1113, i1 true)
  %207 = shl nuw nsw i32 %_21.i1116, 4
  %reass.sub3283 = sub nsw i32 %c.sroa.0.0.i1099, %207
  %208 = add nsw i32 %reass.sub3283, 480
  br label %bb14.i1105

bb14.i1105:                                       ; preds = %bb7.i1098, %bb12.i1115
  %c.sroa.0.1.i1102 = phi i32 [ %208, %bb12.i1115 ], [ %c.sroa.0.0.i1099, %bb7.i1098 ]
  %209 = tail call { i32, i1 } @llvm.ssub.with.overflow.i32(i32 %_30.0.i, i32 %c.sroa.0.1.i1102)
  %_31.1.i1107 = extractvalue { i32, i1 } %209, 1
  br i1 %_31.1.i1107, label %panic9.i1110, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1122

panic9.i1110:                                     ; preds = %bb14.i1105
; call core::panicking::panic_const::panic_const_sub_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_5bf2e340c7b7e1a7a2cf8d7086d6ac68) #13
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1122: ; preds = %bb14.i1105
  %_31.0.i1109 = extractvalue { i32, i1 } %209, 0
  %210 = add nsw i64 %l.sroa.0.0.i3230, -11
  %or.cond.i1071 = icmp ult i64 %210, 247
  br i1 %or.cond.i1071, label %bb6.i1093, label %bb7.i1072

bb7.i1072:                                        ; preds = %bb6.i1093, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1122
  %c.sroa.0.0.i1073 = phi i32 [ %213, %bb6.i1093 ], [ 168, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1122 ]
  %_17.i1074 = icmp ugt i64 %d.sroa.0.0.i3229, 4
  br i1 %_17.i1074, label %bb8.i1086, label %bb48.i

bb6.i1093:                                        ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1122
  %211 = trunc nuw nsw i64 %l.sroa.0.0.i3230 to i32
  %_11.i1094 = add nsw i32 %211, -3
  %_10.i1095 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_11.i1094, i1 false)
  %212 = shl nuw nsw i32 %_10.i1095, 4
  %213 = sub nuw nsw i32 632, %212
  br label %bb7.i1072

bb8.i1086:                                        ; preds = %bb7.i1072
  %214 = trunc i64 %d.sroa.0.0.i3229 to i32
  %_22.i1087 = add i32 %214, -1
  %_25.1.i1088 = icmp ult i32 %_22.i1087, 2
  br i1 %_25.1.i1088, label %panic5.i1092, label %bb12.i1089

panic5.i1092:                                     ; preds = %bb8.i1086
; call core::panicking::panic_const::panic_const_sub_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_9f4d1cf899b26bf5e0e440ccaea53f2f) #13
  unreachable

bb12.i1089:                                       ; preds = %bb8.i1086
  %_21.i1090 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_22.i1087, i1 true)
  %215 = shl nuw nsw i32 %_21.i1090, 4
  %reass.sub3284 = sub nsw i32 %c.sroa.0.0.i1073, %215
  %216 = add nsw i32 %reass.sub3284, 480
  br label %bb48.i

bb48.i:                                           ; preds = %bb7.i1072, %bb12.i1089
  %c.sroa.0.1.i1076 = phi i32 [ %216, %bb12.i1089 ], [ %c.sroa.0.0.i1073, %bb7.i1072 ]
  %_29.i1077 = trunc nuw nsw i64 %l.sroa.0.0.i3230 to i32
  %_30.0.i1080 = shl nuw nsw i32 %_29.i1077, 6
  %217 = or disjoint i32 %_30.0.i1080, 40
  %218 = sub nsw i32 %217, %c.sroa.0.1.i1076
  %_89.i = icmp sgt i32 %_31.0.i1109, %218
  br i1 %_89.i, label %bb49.i, label %bb63.i

bb49.i:                                           ; preds = %bb48.i
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1682)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1685)
  %_9.i322 = icmp ult i64 %nt.sroa.0.5.i3231, %out.1
  br i1 %_9.i322, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit327, label %panic1.i323

panic1.i323:                                      ; preds = %bb49.i
  %nt.sroa.0.5.i3231.lcssa368 = phi i64 [ %nt.sroa.0.5.i3231, %bb49.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %nt.sroa.0.5.i3231.lcssa368, i64 noundef range(i64 0, 2305843009213693952) %out.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_1e808d4a560d2bfb30193cdd1b6f1f95) #13, !noalias !1687
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit327: ; preds = %bb49.i
  %_5.i325 = load i8, ptr %99, align 1, !alias.scope !1682, !noalias !1685, !noundef !136
  %219 = getelementptr inbounds nuw [4 x i8], ptr %out.0, i64 %nt.sroa.0.5.i3231
  %220 = zext i8 %_5.i325 to i32
  store i32 %220, ptr %219, align 4, !alias.scope !1685, !noalias !1682
  %_10.0.i326 = add nuw nsw i64 %nt.sroa.0.5.i3231, 1
  %_9.i313 = icmp ult i64 %_10.0.i326, %out.1
  br i1 %_9.i313, label %bb59.i, label %panic1.i314

panic1.i314:                                      ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit327
  %_10.0.i326.lcssa = phi i64 [ %_10.0.i326, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit327 ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_10.0.i326.lcssa, i64 noundef range(i64 0, 2305843009213693952) %out.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_1e808d4a560d2bfb30193cdd1b6f1f95) #13, !noalias !1688
  unreachable

bb59.i:                                           ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit327, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit
  %_10.0.i326.sink = phi i64 [ %nt.sroa.0.5.i3231, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit ], [ %_10.0.i326, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit327 ]
  %_11.i423.sink = phi i8 [ %_5.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit ], [ %_11.i423, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit327 ]
  %.sink = phi i64 [ 1, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit ], [ 2, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit327 ]
  %ins.sroa.0.5.i = phi i64 [ %_51.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit ], [ %_80.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit327 ]
  %p.sroa.0.6.i = phi i64 [ %_44.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit ], [ %_51.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit327 ]
  %d.sroa.0.1.i = phi i64 [ %d.i53, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit ], [ %d.i116, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit327 ]
  %l.sroa.0.1.i = phi i64 [ %k.sroa.0.2.i195.lcssa, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit ], [ %k.sroa.0.2.i.lcssa, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit327 ]
  %221 = getelementptr inbounds nuw [4 x i8], ptr %out.0, i64 %_10.0.i326.sink
  %222 = zext i8 %_11.i423.sink to i32
  store i32 %222, ptr %221, align 4, !noalias !136
  %_10.0.i317 = add nuw nsw i64 %nt.sroa.0.5.i3231, %.sink
  %_39.i = icmp ult i64 %l.sroa.0.1.i, 32
  br i1 %_39.i, label %bb18.i, label %bb63.i

bb116.i:                                          ; preds = %bb110.i, %bb63.i
  %p.sroa.0.7.i.lcssa = phi i64 [ %p.sroa.0.5.i.lcssa, %bb63.i ], [ %p.sroa.0.8.i, %bb110.i ]
  %l.sroa.0.2.i.lcssa = phi i64 [ %l.sroa.0.0.i.lcssa, %bb63.i ], [ %l.sroa.0.3.i, %bb110.i ]
  %nt.sroa.0.7.i.lcssa = phi i64 [ %nt.sroa.0.5.i.lcssa, %bb63.i ], [ %nt.sroa.0.8.i, %bb110.i ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1692)
  %_15.i = icmp samesign ult i64 %nt.sroa.0.7.i.lcssa, %out.1
  br i1 %_15.i, label %bb1.i356, label %panic.i355

bb1.i356:                                         ; preds = %bb116.i
  %223 = trunc i64 %l.sroa.0.2.i.lcssa to i32
  %224 = trunc i64 %d.sroa.0.0.i.lcssa to i32
  %_10.i = shl i32 %224, 8
  %_12.i357 = add i32 %_10.i, 16776957
  %_7.i358 = add i32 %_12.i357, %223
  %225 = getelementptr inbounds nuw [4 x i8], ptr %out.0, i64 %nt.sroa.0.7.i.lcssa
  store i32 %_7.i358, ptr %225, align 4, !alias.scope !1692
  %_19.0.i359 = add i64 %l.sroa.0.2.i.lcssa, %p.sroa.0.7.i.lcssa
  %_19.1.i360 = icmp ult i64 %_19.0.i359, %p.sroa.0.7.i.lcssa
  br i1 %_19.1.i360, label %panic2.i362, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse14u118_put_match.exit

panic.i355:                                       ; preds = %bb116.i
  %nt.sroa.0.7.i.lcssa.lcssa = phi i64 [ %nt.sroa.0.7.i.lcssa, %bb116.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef range(i64 0, 2305843009213693952) %nt.sroa.0.7.i.lcssa.lcssa, i64 noundef range(i64 0, 2305843009213693952) %out.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_91bbba7d8bfca8a214cab7fb1cbd8ce3) #13, !noalias !1692
  unreachable

panic2.i362:                                      ; preds = %bb1.i356
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_8c0fdb4f326073e19a6b7eb9b54b4e01) #13, !noalias !1692
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse14u118_put_match.exit: ; preds = %bb1.i356
  %_17.0.i = add nuw nsw i64 %nt.sroa.0.7.i.lcssa, 1
  %_175.i = add nuw i64 %ins.sroa.0.4.i.lcssa, 16
  %spec.select148.i = tail call i64 @llvm.umin.i64(i64 %_19.0.i359, i64 %_175.i)
  %spec.store.select50.i = tail call i64 @llvm.umin.i64(i64 %spec.select148.i, i64 499992)
  %_181.i3257 = icmp ult i64 %ins.sroa.0.4.i.lcssa, %spec.store.select50.i
  br i1 %_181.i3257, label %bb125.i, label %bb129.i

bb125.i:                                          ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse14u118_put_match.exit, %bb125.i
  %ins.sroa.0.6.i3258 = phi i64 [ %_188.0.i, %bb125.i ], [ %ins.sroa.0.4.i.lcssa, %_RNvNtCs2hd9JHJjR4I_9candidate5parse14u118_put_match.exit ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1695)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1698)
  %226 = getelementptr inbounds nuw i8, ptr %input.0, i64 %ins.sroa.0.6.i3258
  %227 = load i32, ptr %226, align 1
  %228 = call i32 @llvm.bswap.i32(i32 %227)
  %229 = zext i32 %228 to i64
  %230 = mul i64 %229, -7046029254386353131
  %231 = lshr i64 %230, 48
  %232 = getelementptr inbounds nuw [4 x i8], ptr %head.i, i64 %231
  %old.i155.i = load i32, ptr %232, align 4, !alias.scope !1695, !noalias !1700, !noundef !136
  %_16.i156.i = and i64 %ins.sroa.0.6.i3258, 32767
  %233 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_16.i156.i
  store i32 %old.i155.i, ptr %233, align 4, !alias.scope !1698, !noalias !1702
  %234 = trunc i64 %ins.sroa.0.6.i3258 to i32
  store i32 %234, ptr %232, align 4, !alias.scope !1695, !noalias !1700
  %_188.0.i = add nuw i64 %ins.sroa.0.6.i3258, 1
  %exitcond3470.not = icmp eq i64 %_188.0.i, %spec.store.select50.i
  br i1 %exitcond3470.not, label %bb129.i, label %bb125.i

bb129.i:                                          ; preds = %bb125.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse14u118_put_match.exit
  %ins.sroa.0.6.i.lcssa = phi i64 [ %ins.sroa.0.4.i.lcssa, %_RNvNtCs2hd9JHJjR4I_9candidate5parse14u118_put_match.exit ], [ %spec.store.select50.i, %bb125.i ]
  %e2.i = tail call i64 @llvm.usub.sat.i64(i64 %_19.0.i359, i64 8)
  %invariant.umin = tail call i64 @llvm.umin.i64(i64 %e2.i, i64 499992)
  %or.cond51.i3260 = icmp ult i64 %ins.sroa.0.6.i.lcssa, %invariant.umin
  br i1 %or.cond51.i3260, label %bb132.i, label %bb138.i

bb132.i:                                          ; preds = %bb129.i, %bb132.i
  %ins.sroa.0.7.i3261 = phi i64 [ %_5.0.i485, %bb132.i ], [ %ins.sroa.0.6.i.lcssa, %bb129.i ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1703)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1706)
  %_5.0.i485 = add nuw nsw i64 %ins.sroa.0.7.i3261, 4
  %235 = getelementptr inbounds nuw i8, ptr %input.0, i64 %ins.sroa.0.7.i3261
  %236 = load i32, ptr %235, align 1
  %237 = call i32 @llvm.bswap.i32(i32 %236)
  %238 = zext i32 %237 to i64
  %239 = mul i64 %238, -7046029254386353131
  %240 = lshr i64 %239, 48
  %241 = getelementptr inbounds nuw [4 x i8], ptr %head.i, i64 %240
  %old.i162.i = load i32, ptr %241, align 4, !alias.scope !1703, !noalias !1708, !noundef !136
  %_16.i163.i = and i64 %ins.sroa.0.7.i3261, 32767
  %242 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_16.i163.i
  store i32 %old.i162.i, ptr %242, align 4, !alias.scope !1706, !noalias !1710
  %243 = trunc i64 %ins.sroa.0.7.i3261 to i32
  store i32 %243, ptr %241, align 4, !alias.scope !1703, !noalias !1708
  %or.cond51.i = icmp ult i64 %_5.0.i485, %invariant.umin
  br i1 %or.cond51.i, label %bb132.i, label %bb138.i

bb138.i:                                          ; preds = %bb132.i, %bb129.i
  %ins.sroa.0.7.i.lcssa = phi i64 [ %ins.sroa.0.6.i.lcssa, %bb129.i ], [ %_5.0.i485, %bb132.i ]
  %_202.i = add i64 %ins.sroa.0.7.i.lcssa, 4
  %_201.i = icmp ult i64 %_202.i, %_19.0.i359
  br i1 %_201.i, label %bb139.i, label %bb142.i

bb139.i:                                          ; preds = %bb138.i
  %_204.1.i = icmp ult i64 %_19.0.i359, 4
  br i1 %_204.1.i, label %panic18.i, label %bb140.i

bb142.i:                                          ; preds = %bb140.i, %bb138.i
  %ins.sroa.0.8.i = phi i64 [ %_204.0.i, %bb140.i ], [ %ins.sroa.0.7.i.lcssa, %bb138.i ]
  %invariant.umin3263 = tail call i64 @llvm.umin.i64(i64 %_19.0.i359, i64 499992)
  %or.cond52.i3264 = icmp ult i64 %ins.sroa.0.8.i, %invariant.umin3263
  br i1 %or.cond52.i3264, label %bb145.i, label %bb150.i

bb140.i:                                          ; preds = %bb139.i
  %_204.0.i = add i64 %_19.0.i359, -4
  br label %bb142.i

panic18.i:                                        ; preds = %bb139.i
; call core::panicking::panic_const::panic_const_sub_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_94a048f0c628dd665e0545a553ca9ebc) #13
  unreachable

bb150.i:                                          ; preds = %bb145.i, %bb142.i
  %ins.sroa.0.9.i.lcssa = phi i64 [ %ins.sroa.0.8.i, %bb142.i ], [ %_213.0.i, %bb145.i ]
  %spec.select150.i = tail call i64 @llvm.umax.i64(i64 %ins.sroa.0.9.i.lcssa, i64 %_19.0.i359)
  br label %bb174.i

bb145.i:                                          ; preds = %bb142.i, %bb145.i
  %ins.sroa.0.9.i3265 = phi i64 [ %_213.0.i, %bb145.i ], [ %ins.sroa.0.8.i, %bb142.i ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1711)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1714)
  %244 = getelementptr inbounds nuw i8, ptr %input.0, i64 %ins.sroa.0.9.i3265
  %245 = load i32, ptr %244, align 1
  %246 = call i32 @llvm.bswap.i32(i32 %245)
  %247 = zext i32 %246 to i64
  %248 = mul i64 %247, -7046029254386353131
  %249 = lshr i64 %248, 48
  %250 = getelementptr inbounds nuw [4 x i8], ptr %head.i, i64 %249
  %old.i169.i = load i32, ptr %250, align 4, !alias.scope !1711, !noalias !1716, !noundef !136
  %_16.i170.i = and i64 %ins.sroa.0.9.i3265, 32767
  %251 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_16.i170.i
  store i32 %old.i169.i, ptr %251, align 4, !alias.scope !1714, !noalias !1718
  %252 = trunc i64 %ins.sroa.0.9.i3265 to i32
  store i32 %252, ptr %250, align 4, !alias.scope !1711, !noalias !1716
  %_213.0.i = add nuw nsw i64 %ins.sroa.0.9.i3265, 1
  %or.cond52.i = icmp ult i64 %_213.0.i, %invariant.umin3263
  br i1 %or.cond52.i, label %bb145.i, label %bb150.i

bb71.i:                                           ; preds = %bb63.i, %bb110.i
  %253 = phi i64 [ %303, %bb110.i ], [ %96, %bb63.i ]
  %nt.sroa.0.7.i3253 = phi i64 [ %nt.sroa.0.8.i, %bb110.i ], [ %nt.sroa.0.5.i.lcssa, %bb63.i ]
  %l.sroa.0.2.i3252 = phi i64 [ %l.sroa.0.3.i, %bb110.i ], [ %l.sroa.0.0.i.lcssa, %bb63.i ]
  %back.sroa.0.0.i3251 = phi i64 [ %back.sroa.0.1.i, %bb110.i ], [ 0, %bb63.i ]
  %p.sroa.0.7.i3250 = phi i64 [ %p.sroa.0.8.i, %bb110.i ], [ %p.sroa.0.5.i.lcssa, %bb63.i ]
  %254 = getelementptr inbounds nuw [4 x i8], ptr %out.0, i64 %253
  %t.i = load i32, ptr %254, align 4, !alias.scope !1561, !noalias !1558, !noundef !136
  %_120.i = icmp ult i32 %t.i, 256
  br i1 %_120.i, label %bb72.i, label %bb84.i

bb84.i:                                           ; preds = %bb71.i
  %_139.i = icmp ugt i32 %t.i, 16777215
  br i1 %_139.i, label %bb87.i, label %bb110.i

bb72.i:                                           ; preds = %bb71.i
  %_125.0.i = add i64 %p.sroa.0.7.i3250, -1
  %_126.i = icmp ult i64 %_125.0.i, 500000
  br i1 %_126.i, label %bb74.i, label %panic25.i

bb74.i:                                           ; preds = %bb72.i
  %_133.0.i = sub i64 %_125.0.i, %d.sroa.0.0.i.lcssa
  %_134.i = icmp ult i64 %_133.0.i, 500000
  br i1 %_134.i, label %bb77.i, label %panic28.i

panic25.i:                                        ; preds = %bb72.i
  %_125.0.i.lcssa = phi i64 [ %_125.0.i, %bb72.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_125.0.i.lcssa, i64 noundef range(i64 0, -9223372036854775808) 500000, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_1cb241537ee4f281c00fcbb1bef48ab0) #13
  unreachable

bb77.i:                                           ; preds = %bb74.i
  %255 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_125.0.i
  %_122.i = load i8, ptr %255, align 1, !alias.scope !1558, !noalias !1561, !noundef !136
  %256 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_133.0.i
  %_127.i = load i8, ptr %256, align 1, !alias.scope !1558, !noalias !1561, !noundef !136
  %_121.i = icmp eq i8 %_122.i, %_127.i
  br i1 %_121.i, label %bb80.i, label %bb110.i

panic28.i:                                        ; preds = %bb74.i
  %_133.0.i.lcssa = phi i64 [ %_133.0.i, %bb74.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_133.0.i.lcssa, i64 noundef range(i64 0, -9223372036854775808) 500000, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_3d3fade205e2688424188b5bbd6c946c) #13
  unreachable

bb87.i:                                           ; preds = %bb84.i
  %_142.i = and i32 %t.i, 255
  %_145.0.i = add nuw nsw i32 %_142.i, 3
  %w.i = zext nneg i32 %_145.0.i to i64
  %_149.0.i = add nuw nsw i64 %l.sroa.0.2.i3252, %w.i
  %_146.i = icmp samesign ult i64 %_149.0.i, 259
  %_150.i = icmp uge i64 %p.sroa.0.7.i3250, %w.i
  %or.cond53.i = select i1 %_146.i, i1 %_150.i, i1 false
  br i1 %or.cond53.i, label %bb90.i, label %bb110.i

bb90.i:                                           ; preds = %bb87.i
  %_156.0.i = sub nuw i64 %p.sroa.0.7.i3250, %w.i
  %_152.not.i = icmp ugt i64 %d.sroa.0.0.i.lcssa, %_156.0.i
  br i1 %_152.not.i, label %bb110.i, label %bb95.i

bb95.i:                                           ; preds = %bb90.i
  %_163.0.i = sub nuw i64 %_156.0.i, %d.sroa.0.0.i.lcssa
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1719)
  %257 = and i64 %w.i, 504
  br label %bb2.i1162

bb2.i1162:                                        ; preds = %bb95.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i
  %k.sroa.0.0.i11243242 = phi i64 [ 0, %bb95.i ], [ %_11.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i ]
  %_11.0.i = add nuw nsw i64 %k.sroa.0.0.i11243242, 8
  %_8.not.i = icmp samesign ugt i64 %_11.0.i, %w.i
  br i1 %_8.not.i, label %bb15.i1125, label %bb4.i1164

bb4.i1164:                                        ; preds = %bb2.i1162
  %_16.0.i = add nuw i64 %k.sroa.0.0.i11243242, %_163.0.i
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1722)
  %_5.1.i172.i = icmp ugt i64 %_16.0.i, -9
  br i1 %_5.1.i172.i, label %panic.i238.i, label %bb1.i173.i

bb15.i1125:                                       ; preds = %bb2.i1162
  %_23.i1126.not = icmp eq i64 %257, %w.i
  br i1 %_23.i1126.not, label %bb101.i, label %bb18.i1128

bb1.i173.i:                                       ; preds = %bb4.i1164
  %258 = icmp ugt i64 %_16.0.i, 499992
  br i1 %258, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit239.i, label %bb2.i176.i

panic.i238.i:                                     ; preds = %bb4.i1164
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_440babfea49fec204c4bfa4556bd23df) #13, !noalias !1725
  unreachable

bb2.i176.i:                                       ; preds = %bb1.i173.i
  %259 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_16.0.i
  %_15.i180.i = load i8, ptr %259, align 1, !alias.scope !1725, !noundef !136
  %_14.i181.i = zext i8 %_15.i180.i to i64
  %_13.i182.i = shl nuw i64 %_14.i181.i, 56
  %260 = getelementptr inbounds nuw i8, ptr %259, i64 1
  %_19.i187.i = load i8, ptr %260, align 1, !alias.scope !1725, !noundef !136
  %_18.i188.i = zext i8 %_19.i187.i to i64
  %_17.i189.i = shl nuw nsw i64 %_18.i188.i, 48
  %_12.i190.i = or disjoint i64 %_17.i189.i, %_13.i182.i
  %261 = getelementptr inbounds nuw i8, ptr %259, i64 2
  %_25.i195.i = load i8, ptr %261, align 1, !alias.scope !1725, !noundef !136
  %_24.i196.i = zext i8 %_25.i195.i to i64
  %_23.i197.i = shl nuw nsw i64 %_24.i196.i, 40
  %_11.i198.i = or disjoint i64 %_12.i190.i, %_23.i197.i
  %262 = getelementptr inbounds nuw i8, ptr %259, i64 3
  %_31.i203.i = load i8, ptr %262, align 1, !alias.scope !1725, !noundef !136
  %_30.i204.i = zext i8 %_31.i203.i to i64
  %_29.i205.i = shl nuw nsw i64 %_30.i204.i, 32
  %_10.i206.i = or disjoint i64 %_11.i198.i, %_29.i205.i
  %263 = getelementptr inbounds nuw i8, ptr %259, i64 4
  %_37.i211.i = load i8, ptr %263, align 1, !alias.scope !1725, !noundef !136
  %_36.i212.i = zext i8 %_37.i211.i to i64
  %_35.i213.i = shl nuw nsw i64 %_36.i212.i, 24
  %_9.i214.i = or disjoint i64 %_10.i206.i, %_35.i213.i
  %264 = getelementptr inbounds nuw i8, ptr %259, i64 5
  %_43.i219.i = load i8, ptr %264, align 1, !alias.scope !1725, !noundef !136
  %_42.i220.i = zext i8 %_43.i219.i to i64
  %_41.i221.i = shl nuw nsw i64 %_42.i220.i, 16
  %_8.i222.i = or disjoint i64 %_9.i214.i, %_41.i221.i
  %265 = getelementptr inbounds nuw i8, ptr %259, i64 6
  %_49.i227.i = load i8, ptr %265, align 1, !alias.scope !1725, !noundef !136
  %_48.i228.i = zext i8 %_49.i227.i to i64
  %_47.i229.i = shl nuw nsw i64 %_48.i228.i, 8
  %_7.i230.i = or i64 %_8.i222.i, %_47.i229.i
  %266 = getelementptr inbounds nuw i8, ptr %259, i64 7
  %_54.i235.i = load i8, ptr %266, align 1, !alias.scope !1725, !noundef !136
  %_53.i236.i = zext i8 %_54.i235.i to i64
  %267 = or i64 %_7.i230.i, %_53.i236.i
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit239.i

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit239.i: ; preds = %bb2.i176.i, %bb1.i173.i
  %_0.sroa.0.0.i237.i = phi i64 [ %267, %bb2.i176.i ], [ 0, %bb1.i173.i ]
  %_20.0.i = add nuw i64 %k.sroa.0.0.i11243242, %_156.0.i
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1726)
  %_5.1.i104.i = icmp ugt i64 %_20.0.i, -9
  br i1 %_5.1.i104.i, label %panic.i170.i, label %bb1.i105.i

bb1.i105.i:                                       ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit239.i
  %268 = icmp ugt i64 %_20.0.i, 499992
  br i1 %268, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i, label %bb2.i108.i

panic.i170.i:                                     ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit239.i
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_440babfea49fec204c4bfa4556bd23df) #13, !noalias !1729
  unreachable

bb2.i108.i:                                       ; preds = %bb1.i105.i
  %269 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_20.0.i
  %_15.i112.i = load i8, ptr %269, align 1, !alias.scope !1729, !noundef !136
  %_14.i113.i = zext i8 %_15.i112.i to i64
  %_13.i114.i = shl nuw i64 %_14.i113.i, 56
  %270 = getelementptr inbounds nuw i8, ptr %269, i64 1
  %_19.i119.i = load i8, ptr %270, align 1, !alias.scope !1729, !noundef !136
  %_18.i120.i = zext i8 %_19.i119.i to i64
  %_17.i121.i = shl nuw nsw i64 %_18.i120.i, 48
  %_12.i122.i = or disjoint i64 %_17.i121.i, %_13.i114.i
  %271 = getelementptr inbounds nuw i8, ptr %269, i64 2
  %_25.i127.i = load i8, ptr %271, align 1, !alias.scope !1729, !noundef !136
  %_24.i128.i = zext i8 %_25.i127.i to i64
  %_23.i129.i = shl nuw nsw i64 %_24.i128.i, 40
  %_11.i130.i = or disjoint i64 %_12.i122.i, %_23.i129.i
  %272 = getelementptr inbounds nuw i8, ptr %269, i64 3
  %_31.i135.i = load i8, ptr %272, align 1, !alias.scope !1729, !noundef !136
  %_30.i136.i = zext i8 %_31.i135.i to i64
  %_29.i137.i = shl nuw nsw i64 %_30.i136.i, 32
  %_10.i138.i = or disjoint i64 %_11.i130.i, %_29.i137.i
  %273 = getelementptr inbounds nuw i8, ptr %269, i64 4
  %_37.i143.i = load i8, ptr %273, align 1, !alias.scope !1729, !noundef !136
  %_36.i144.i = zext i8 %_37.i143.i to i64
  %_35.i145.i = shl nuw nsw i64 %_36.i144.i, 24
  %_9.i146.i = or disjoint i64 %_10.i138.i, %_35.i145.i
  %274 = getelementptr inbounds nuw i8, ptr %269, i64 5
  %_43.i151.i = load i8, ptr %274, align 1, !alias.scope !1729, !noundef !136
  %_42.i152.i = zext i8 %_43.i151.i to i64
  %_41.i153.i = shl nuw nsw i64 %_42.i152.i, 16
  %_8.i154.i = or disjoint i64 %_9.i146.i, %_41.i153.i
  %275 = getelementptr inbounds nuw i8, ptr %269, i64 6
  %_49.i159.i = load i8, ptr %275, align 1, !alias.scope !1729, !noundef !136
  %_48.i160.i = zext i8 %_49.i159.i to i64
  %_47.i161.i = shl nuw nsw i64 %_48.i160.i, 8
  %_7.i162.i = or i64 %_8.i154.i, %_47.i161.i
  %276 = getelementptr inbounds nuw i8, ptr %269, i64 7
  %_54.i167.i = load i8, ptr %276, align 1, !alias.scope !1729, !noundef !136
  %_53.i168.i = zext i8 %_54.i167.i to i64
  %277 = or i64 %_7.i162.i, %_53.i168.i
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i: ; preds = %bb2.i108.i, %bb1.i105.i
  %_0.sroa.0.0.i169.i = phi i64 [ %277, %bb2.i108.i ], [ 0, %bb1.i105.i ]
  %_12.i.not = icmp eq i64 %_0.sroa.0.0.i237.i, %_0.sroa.0.0.i169.i
  br i1 %_12.i.not, label %bb2.i1162, label %bb110.i

bb18.i1128:                                       ; preds = %bb15.i1125
  %_29.0.i1129 = add i64 %257, %_163.0.i
  %_29.1.i = icmp ult i64 %_29.0.i1129, %_163.0.i
  br i1 %_29.1.i, label %panic4.i1161, label %bb19.i1130

bb19.i1130:                                       ; preds = %bb18.i1128
  %_30.1.i1131 = icmp ugt i64 %_29.0.i1129, -9
  br i1 %_30.1.i1131, label %panic5.i1160, label %bb20.i1132

panic4.i1161:                                     ; preds = %bb18.i1128
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_5988a9c474509aa3e7e55969f6ad663e) #13, !noalias !1719
  unreachable

bb20.i1132:                                       ; preds = %bb19.i1130
  %278 = icmp ugt i64 %_29.0.i1129, 499992
  br i1 %278, label %bb40.i.preheader, label %bb21.i1134

bb40.i.preheader:                                 ; preds = %bb23.i1136, %bb20.i1132
  br label %bb40.i

panic5.i1160:                                     ; preds = %bb19.i1130
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_5988a9c474509aa3e7e55969f6ad663e) #13, !noalias !1719
  unreachable

bb21.i1134:                                       ; preds = %bb20.i1132
  %_35.0.i = add i64 %257, %_156.0.i
  %_35.1.i = icmp ult i64 %_35.0.i, %_156.0.i
  br i1 %_35.1.i, label %panic6.i1159, label %bb22.i1135

bb22.i1135:                                       ; preds = %bb21.i1134
  %_36.1.i = icmp ugt i64 %_35.0.i, -9
  br i1 %_36.1.i, label %panic7.i1158, label %bb23.i1136

panic6.i1159:                                     ; preds = %bb21.i1134
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_c2b01cdce33609a4161805adc289533f) #13, !noalias !1719
  unreachable

bb23.i1136:                                       ; preds = %bb22.i1135
  %279 = icmp ugt i64 %_35.0.i, 499992
  br i1 %279, label %bb40.i.preheader, label %bb30.i

panic7.i1158:                                     ; preds = %bb22.i1135
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_c2b01cdce33609a4161805adc289533f) #13, !noalias !1719
  unreachable

bb40.i:                                           ; preds = %bb40.i.preheader, %bb44.i
  %k.sroa.0.2.i11503244 = phi i64 [ %k.sroa.0.3.i1156, %bb44.i ], [ %257, %bb40.i.preheader ]
  %_62.0.i = add i64 %k.sroa.0.2.i11503244, %_163.0.i
  %_62.1.i = icmp ult i64 %_62.0.i, %_163.0.i
  br i1 %_62.1.i, label %panic8.i1157, label %bb41.i

bb41.i:                                           ; preds = %bb40.i
  %_63.i = icmp ult i64 %_62.0.i, 500000
  br i1 %_63.i, label %bb42.i1152, label %panic9.i1151

panic8.i1157:                                     ; preds = %bb40.i
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_ec9880852f5ad0b7f675c971d025b4ff) #13, !noalias !1719
  unreachable

bb42.i1152:                                       ; preds = %bb41.i
  %280 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_62.0.i
  %_59.i = load i8, ptr %280, align 1, !alias.scope !1719, !noundef !136
  %_67.0.i = add i64 %k.sroa.0.2.i11503244, %_156.0.i
  %_67.1.i = icmp ult i64 %_67.0.i, %_156.0.i
  br i1 %_67.1.i, label %panic10.i, label %bb43.i1153

panic9.i1151:                                     ; preds = %bb41.i
  %_62.0.i.lcssa370 = phi i64 [ %_62.0.i, %bb41.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_62.0.i.lcssa370, i64 noundef range(i64 0, -9223372036854775808) 500000, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_c867e779aaf632c8ba08807d62f697ee) #13, !noalias !1719
  unreachable

bb43.i1153:                                       ; preds = %bb42.i1152
  %_68.i = icmp ult i64 %_67.0.i, 500000
  br i1 %_68.i, label %bb44.i, label %panic11.i1154

panic10.i:                                        ; preds = %bb42.i1152
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_f89fc433b2ec5f525912d54366fd14b2) #13, !noalias !1719
  unreachable

bb44.i:                                           ; preds = %bb43.i1153
  %281 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_67.0.i
  %_64.i = load i8, ptr %281, align 1, !alias.scope !1719, !noundef !136
  %_58.i1155 = icmp eq i8 %_59.i, %_64.i
  %_69.0.i = zext i1 %_58.i1155 to i64
  %k.sroa.0.3.i1156 = add nuw nsw i64 %k.sroa.0.2.i11503244, %_69.0.i
  %_56.i = icmp samesign ult i64 %k.sroa.0.3.i1156, %w.i
  %or.cond19.i = select i1 %_58.i1155, i1 %_56.i, i1 false
  br i1 %or.cond19.i, label %bb40.i, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit

panic11.i1154:                                    ; preds = %bb43.i1153
  %_67.0.i.lcssa374 = phi i64 [ %_67.0.i, %bb43.i1153 ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_67.0.i.lcssa374, i64 noundef range(i64 0, -9223372036854775808) 500000, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_f7486e32a26ebd3f0532d14c194cbf09) #13, !noalias !1719
  unreachable

bb30.i:                                           ; preds = %bb23.i1136
  %_51.0.i1141 = shl nuw nsw i32 %_145.0.i, 3
  %282 = and i32 %_51.0.i1141, 56
  %_54.i1144.not = icmp eq i32 %282, 0
  br i1 %_54.i1144.not, label %panic18.i1145, label %bb32.i1146

bb32.i1146:                                       ; preds = %bb30.i
  %_53.0.i = sub nuw nsw i32 64, %282
  %283 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_35.0.i
  %284 = getelementptr inbounds nuw i8, ptr %283, i64 1
  %_19.i.i = load i8, ptr %284, align 1, !alias.scope !1730, !noundef !136
  %_18.i.i = zext i8 %_19.i.i to i64
  %_17.i.i = shl nuw nsw i64 %_18.i.i, 48
  %_15.i.i = load i8, ptr %283, align 1, !alias.scope !1730, !noundef !136
  %_14.i.i = zext i8 %_15.i.i to i64
  %_13.i.i = shl nuw i64 %_14.i.i, 56
  %_12.i.i1138 = or disjoint i64 %_17.i.i, %_13.i.i
  %285 = getelementptr inbounds nuw i8, ptr %283, i64 2
  %_25.i.i = load i8, ptr %285, align 1, !alias.scope !1730, !noundef !136
  %_24.i.i = zext i8 %_25.i.i to i64
  %_23.i.i = shl nuw nsw i64 %_24.i.i, 40
  %_11.i.i1139 = or disjoint i64 %_12.i.i1138, %_23.i.i
  %286 = getelementptr inbounds nuw i8, ptr %283, i64 3
  %_31.i.i = load i8, ptr %286, align 1, !alias.scope !1730, !noundef !136
  %_30.i.i = zext i8 %_31.i.i to i64
  %_29.i.i = shl nuw nsw i64 %_30.i.i, 32
  %_10.i.i = or disjoint i64 %_11.i.i1139, %_29.i.i
  %287 = getelementptr inbounds nuw i8, ptr %283, i64 4
  %_37.i.i = load i8, ptr %287, align 1, !alias.scope !1730, !noundef !136
  %_36.i.i = zext i8 %_37.i.i to i64
  %_35.i.i = shl nuw nsw i64 %_36.i.i, 24
  %_9.i.i = or disjoint i64 %_10.i.i, %_35.i.i
  %288 = getelementptr inbounds nuw i8, ptr %283, i64 5
  %_43.i.i = load i8, ptr %288, align 1, !alias.scope !1730, !noundef !136
  %_42.i.i = zext i8 %_43.i.i to i64
  %_41.i.i = shl nuw nsw i64 %_42.i.i, 16
  %_8.i.i = or disjoint i64 %_9.i.i, %_41.i.i
  %289 = getelementptr inbounds nuw i8, ptr %283, i64 6
  %_49.i.i = load i8, ptr %289, align 1, !alias.scope !1730, !noundef !136
  %_48.i.i = zext i8 %_49.i.i to i64
  %_47.i.i = shl nuw nsw i64 %_48.i.i, 8
  %_7.i.i = or i64 %_8.i.i, %_47.i.i
  %290 = getelementptr inbounds nuw i8, ptr %283, i64 7
  %_54.i.i = load i8, ptr %290, align 1, !alias.scope !1730, !noundef !136
  %_53.i.i = zext i8 %_54.i.i to i64
  %291 = or i64 %_7.i.i, %_53.i.i
  %292 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_29.0.i1129
  %293 = getelementptr inbounds nuw i8, ptr %292, i64 1
  %_19.i51.i = load i8, ptr %293, align 1, !alias.scope !1733, !noundef !136
  %_18.i52.i = zext i8 %_19.i51.i to i64
  %_17.i53.i = shl nuw nsw i64 %_18.i52.i, 48
  %_15.i44.i = load i8, ptr %292, align 1, !alias.scope !1733, !noundef !136
  %_14.i45.i = zext i8 %_15.i44.i to i64
  %_13.i46.i = shl nuw i64 %_14.i45.i, 56
  %_12.i54.i = or disjoint i64 %_17.i53.i, %_13.i46.i
  %294 = getelementptr inbounds nuw i8, ptr %292, i64 2
  %_25.i59.i = load i8, ptr %294, align 1, !alias.scope !1733, !noundef !136
  %_24.i60.i = zext i8 %_25.i59.i to i64
  %_23.i61.i = shl nuw nsw i64 %_24.i60.i, 40
  %_11.i62.i = or disjoint i64 %_12.i54.i, %_23.i61.i
  %295 = getelementptr inbounds nuw i8, ptr %292, i64 3
  %_31.i67.i = load i8, ptr %295, align 1, !alias.scope !1733, !noundef !136
  %_30.i68.i = zext i8 %_31.i67.i to i64
  %_29.i69.i = shl nuw nsw i64 %_30.i68.i, 32
  %_10.i70.i = or disjoint i64 %_11.i62.i, %_29.i69.i
  %296 = getelementptr inbounds nuw i8, ptr %292, i64 4
  %_37.i75.i = load i8, ptr %296, align 1, !alias.scope !1733, !noundef !136
  %_36.i76.i = zext i8 %_37.i75.i to i64
  %_35.i77.i = shl nuw nsw i64 %_36.i76.i, 24
  %_9.i78.i = or disjoint i64 %_10.i70.i, %_35.i77.i
  %297 = getelementptr inbounds nuw i8, ptr %292, i64 5
  %_43.i83.i = load i8, ptr %297, align 1, !alias.scope !1733, !noundef !136
  %_42.i84.i = zext i8 %_43.i83.i to i64
  %_41.i85.i = shl nuw nsw i64 %_42.i84.i, 16
  %_8.i86.i = or disjoint i64 %_9.i78.i, %_41.i85.i
  %298 = getelementptr inbounds nuw i8, ptr %292, i64 6
  %_49.i91.i = load i8, ptr %298, align 1, !alias.scope !1733, !noundef !136
  %_48.i92.i = zext i8 %_49.i91.i to i64
  %_47.i93.i = shl nuw nsw i64 %_48.i92.i, 8
  %_7.i94.i = or i64 %_8.i86.i, %_47.i93.i
  %299 = getelementptr inbounds nuw i8, ptr %292, i64 7
  %_54.i99.i = load i8, ptr %299, align 1, !alias.scope !1733, !noundef !136
  %_53.i100.i = zext i8 %_54.i99.i to i64
  %300 = or i64 %_7.i94.i, %_53.i100.i
  %x.i1140 = xor i64 %291, %300
  %301 = zext nneg i32 %_53.0.i to i64
  %_46.i1147 = lshr i64 %x.i1140, %301
  %302 = icmp eq i64 %_46.i1147, 0
  br i1 %302, label %bb101.i, label %bb110.i

panic18.i1145:                                    ; preds = %bb30.i
; call core::panicking::panic_const::panic_const_shr_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_shr_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_0471675f9abe1475b1e41b49769421c8) #13, !noalias !1719
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit: ; preds = %bb44.i
  br i1 %_58.i1155, label %bb101.i, label %bb110.i

bb101.i:                                          ; preds = %bb32.i1146, %bb15.i1125, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit
  %_170.0.i = add nuw nsw i64 %back.sroa.0.0.i3251, 1
  br label %bb110.i

bb110.i:                                          ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i, %bb32.i1146, %bb77.i, %bb80.i, %bb101.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit, %bb90.i, %bb87.i, %bb84.i
  %p.sroa.0.8.i = phi i64 [ %_125.0.i, %bb80.i ], [ %_156.0.i, %bb101.i ], [ %p.sroa.0.7.i3250, %bb84.i ], [ %p.sroa.0.7.i3250, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit ], [ %p.sroa.0.7.i3250, %bb90.i ], [ %p.sroa.0.7.i3250, %bb87.i ], [ %p.sroa.0.7.i3250, %bb77.i ], [ %p.sroa.0.7.i3250, %bb32.i1146 ], [ %p.sroa.0.7.i3250, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i ]
  %back.sroa.0.1.i = phi i64 [ %_138.0.i, %bb80.i ], [ %_170.0.i, %bb101.i ], [ 16, %bb84.i ], [ 16, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit ], [ 16, %bb90.i ], [ 16, %bb87.i ], [ 16, %bb77.i ], [ 16, %bb32.i1146 ], [ 16, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i ]
  %l.sroa.0.3.i = phi i64 [ %_137.0.i, %bb80.i ], [ %_149.0.i, %bb101.i ], [ %l.sroa.0.2.i3252, %bb84.i ], [ %l.sroa.0.2.i3252, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit ], [ %l.sroa.0.2.i3252, %bb90.i ], [ %l.sroa.0.2.i3252, %bb87.i ], [ %l.sroa.0.2.i3252, %bb77.i ], [ %l.sroa.0.2.i3252, %bb32.i1146 ], [ %l.sroa.0.2.i3252, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i ]
  %nt.sroa.0.8.i = phi i64 [ %253, %bb80.i ], [ %253, %bb101.i ], [ %nt.sroa.0.7.i3253, %bb84.i ], [ %nt.sroa.0.7.i3253, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit ], [ %nt.sroa.0.7.i3253, %bb90.i ], [ %nt.sroa.0.7.i3253, %bb87.i ], [ %nt.sroa.0.7.i3253, %bb77.i ], [ %nt.sroa.0.7.i3253, %bb32.i1146 ], [ %nt.sroa.0.7.i3253, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i ]
  %_103.i = icmp ult i64 %back.sroa.0.1.i, 16
  %303 = add i64 %nt.sroa.0.8.i, -1
  %304 = icmp ult i64 %303, %out.1
  %or.cond48.i = select i1 %_103.i, i1 %304, i1 false
  %_110.i = icmp ult i64 %l.sroa.0.3.i, 258
  %or.cond49.i = select i1 %or.cond48.i, i1 %_110.i, i1 false
  %_112.i = icmp ult i64 %d.sroa.0.0.i.lcssa, %p.sroa.0.8.i
  %or.cond149.i = select i1 %or.cond49.i, i1 %_112.i, i1 false
  br i1 %or.cond149.i, label %bb71.i, label %bb116.i

bb80.i:                                           ; preds = %bb77.i
  %_137.0.i = add nuw nsw i64 %l.sroa.0.2.i3252, 1
  %_138.0.i = add nuw nsw i64 %back.sroa.0.0.i3251, 1
  br label %bb110.i

_RINvNtCs2hd9JHJjR4I_9candidate5parse8u118_runKj10000_Kj8000_Kmffffffff_Kj4_Kj6_Kj20_Kj5_Kjf4240_Kj40_Kj1_Kj10_KB18_Kl40_KB1C_EB4_.exit: ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit354, %bb178.i
  %nt.sroa.0.2.i.lcssa = phi i64 [ %nt.sroa.0.4.i.lcssa, %bb178.i ], [ %_10.0.i353, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit354 ]
  ret i64 %nt.sroa.0.2.i.lcssa
}