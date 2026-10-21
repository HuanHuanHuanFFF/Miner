define internal fastcc noundef range(i64 0, 2305843009213693952) i64 @_RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row2(ptr noalias nofree noundef nonnull readonly captures(address, read_provenance) %input.0, ptr noalias nofree noundef nonnull align 4 captures(none) %out.0, i64 noundef range(i64 0, 2305843009213693952) %out.1) unnamed_addr #0 !guid !1556 {
bb5.i.preheader:
  %prev.i = alloca [131072 x i8], align 4
  %head.i = alloca [262144 x i8], align 4
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1557)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1560)
  call void @llvm.lifetime.start.p0(ptr nonnull %head.i), !noalias !1562
  call void @llvm.memset.p0.i64(ptr noundef nonnull align 4 dereferenceable(262144) %head.i, i8 0, i64 262144, i1 false), !noalias !1562
  call void @llvm.lifetime.start.p0(ptr nonnull %prev.i), !noalias !1562
  call void @llvm.memset.p0.i64(ptr noundef nonnull align 4 dereferenceable(131072) %prev.i, i8 0, i64 131072, i1 false), !noalias !1562
  br label %bb5.i

bb178.i:                                          ; preds = %bb174.i
  %p.sroa.0.4.i.lcssa = phi i64 [ %p.sroa.0.4.i, %bb174.i ]
  %nt.sroa.0.4.i.lcssa = phi i64 [ %nt.sroa.0.4.i, %bb174.i ]
  call void @llvm.lifetime.end.p0(ptr nonnull %prev.i), !noalias !1562
  call void @llvm.lifetime.end.p0(ptr nonnull %head.i), !noalias !1562
  %_237.i3161 = icmp ult i64 %p.sroa.0.4.i.lcssa, 500000
  br i1 %_237.i3161, label %bb1.i318.preheader, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse8u118_runKj10000_Kj8000_Kmffffffff_Kj4_Kj6_Kj20_Kj5_Kjf4240_Kj40_Kj1_Kj10_KB18_Kl40_KB1C_EB4_.exit

bb1.i318.preheader:                               ; preds = %bb178.i
  %umax = tail call i64 @llvm.umax.i64(i64 %nt.sroa.0.4.i.lcssa, i64 %out.1)
  %0 = sub i64 %umax, %nt.sroa.0.4.i.lcssa
  %1 = sub nuw nsw i64 499999, %p.sroa.0.4.i.lcssa
  %2 = call i64 @llvm.umin.i64(i64 %0, i64 %1)
  %min.iters.check272 = icmp samesign ult i64 %2, 8
  br i1 %min.iters.check272, label %bb1.i318.preheader298, label %vector.ph273

bb1.i318.preheader298:                            ; preds = %vector.body276, %bb1.i318.preheader
  %nt.sroa.0.2.i3163.ph = phi i64 [ %nt.sroa.0.4.i.lcssa, %bb1.i318.preheader ], [ %6, %vector.body276 ]
  %p.sroa.0.2.i3162.ph = phi i64 [ %p.sroa.0.4.i.lcssa, %bb1.i318.preheader ], [ %7, %vector.body276 ]
  br label %bb1.i318

vector.ph273:                                     ; preds = %bb1.i318.preheader
  %3 = add nuw nsw i64 %2, 1
  %n.mod.vf274 = and i64 %3, 7
  %4 = icmp eq i64 %n.mod.vf274, 0
  %5 = select i1 %4, i64 8, i64 %n.mod.vf274
  %n.vec275 = sub nuw nsw i64 %3, %5
  %6 = add i64 %nt.sroa.0.4.i.lcssa, %n.vec275
  %7 = add nuw nsw i64 %p.sroa.0.4.i.lcssa, %n.vec275
  %8 = getelementptr i8, ptr %input.0, i64 %p.sroa.0.4.i.lcssa
  %9 = getelementptr [4 x i8], ptr %out.0, i64 %nt.sroa.0.4.i.lcssa
  br label %vector.body276

vector.body276:                                   ; preds = %vector.body276, %vector.ph273
  %index277 = phi i64 [ 0, %vector.ph273 ], [ %index.next280, %vector.body276 ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1563)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1566)
  %10 = getelementptr i8, ptr %8, i64 %index277
  %11 = getelementptr inbounds nuw i8, ptr %10, i64 4
  %wide.load278 = load <4 x i8>, ptr %10, align 1, !alias.scope !1563, !noalias !1566
  %wide.load279 = load <4 x i8>, ptr %11, align 1, !alias.scope !1563, !noalias !1566
  %12 = getelementptr [4 x i8], ptr %9, i64 %index277
  %13 = zext <4 x i8> %wide.load278 to <4 x i32>
  %14 = zext <4 x i8> %wide.load279 to <4 x i32>
  %15 = getelementptr inbounds nuw i8, ptr %12, i64 16
  store <4 x i32> %13, ptr %12, align 4, !alias.scope !1566, !noalias !1563
  store <4 x i32> %14, ptr %15, align 4, !alias.scope !1566, !noalias !1563
  %index.next280 = add nuw i64 %index277, 8
  %16 = icmp eq i64 %index.next280, %n.vec275
  br i1 %16, label %bb1.i318.preheader298, label %vector.body276, !llvm.loop !1568

bb5.i:                                            ; preds = %bb5.i.preheader, %bb174.i
  %nt.sroa.0.1.i3158 = phi i64 [ %nt.sroa.0.4.i, %bb174.i ], [ 0, %bb5.i.preheader ]
  %miss.sroa.0.0.i3157 = phi i64 [ %miss.sroa.0.1.i, %bb174.i ], [ 0, %bb5.i.preheader ]
  %fuel.sroa.0.0.i3156 = phi i64 [ %_15.0.i, %bb174.i ], [ 500016, %bb5.i.preheader ]
  %p.sroa.0.1.i3155 = phi i64 [ %p.sroa.0.4.i, %bb174.i ], [ 0, %bb5.i.preheader ]
  %ins.sroa.0.0.i3154 = phi i64 [ %ins.sroa.0.3.i, %bb174.i ], [ 0, %bb5.i.preheader ]
  %p.sroa.0.1.i3155.fr = freeze i64 %p.sroa.0.1.i3155
  %_15.0.i = add nsw i64 %fuel.sroa.0.0.i3156, -1
  %_16.i3064 = icmp ult i64 %ins.sroa.0.0.i3154, %p.sroa.0.1.i3155.fr
  br i1 %_16.i3064, label %bb8.i, label %bb11.i

bb1.i318:                                         ; preds = %bb1.i318.preheader298, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit324
  %nt.sroa.0.2.i3163 = phi i64 [ %_10.0.i323, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit324 ], [ %nt.sroa.0.2.i3163.ph, %bb1.i318.preheader298 ]
  %p.sroa.0.2.i3162 = phi i64 [ %_241.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit324 ], [ %p.sroa.0.2.i3162.ph, %bb1.i318.preheader298 ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1563)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1566)
  %exitcond3347.not = icmp eq i64 %nt.sroa.0.2.i3163, %umax
  br i1 %exitcond3347.not, label %panic1.i320, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit324

panic1.i320:                                      ; preds = %bb1.i318
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %umax, i64 noundef range(i64 0, 2305843009213693952) %out.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_ce72d480401e07b7a290039044612259) #13, !noalias !1569
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit324: ; preds = %bb1.i318
  %17 = getelementptr inbounds nuw i8, ptr %input.0, i64 %p.sroa.0.2.i3162
  %_5.i322 = load i8, ptr %17, align 1, !alias.scope !1563, !noalias !1566, !noundef !135
  %18 = getelementptr inbounds nuw [4 x i8], ptr %out.0, i64 %nt.sroa.0.2.i3163
  %19 = zext i8 %_5.i322 to i32
  store i32 %19, ptr %18, align 4, !alias.scope !1566, !noalias !1563
  %_10.0.i323 = add i64 %nt.sroa.0.2.i3163, 1
  %_241.0.i = add nuw nsw i64 %p.sroa.0.2.i3162, 1
  %exitcond3348.not = icmp eq i64 %_241.0.i, 500000
  br i1 %exitcond3348.not, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse8u118_runKj10000_Kj8000_Kmffffffff_Kj4_Kj6_Kj20_Kj5_Kjf4240_Kj40_Kj1_Kj10_KB18_Kl40_KB1C_EB4_.exit, label %bb1.i318, !llvm.loop !1570

bb11.i:                                           ; preds = %bb8.i, %bb5.i
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1571)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1574)
  %20 = getelementptr inbounds nuw i8, ptr %input.0, i64 %p.sroa.0.1.i3155.fr
  %21 = load <4 x i8>, ptr %20, align 1, !alias.scope !1576, !noalias !1579
  %22 = bitcast <4 x i8> %21 to i32
  %23 = call i32 @llvm.bswap.i32(i32 %22)
  %24 = zext i32 %23 to i64
  %25 = mul i64 %24, -7046029254386353131
  %26 = lshr i64 %25, 48
  %27 = getelementptr inbounds nuw [4 x i8], ptr %head.i, i64 %26
  %old.i190.i = load i32, ptr %27, align 4, !alias.scope !1571, !noalias !1580, !noundef !135
  %_16.i191.i = and i64 %p.sroa.0.1.i3155.fr, 32767
  %28 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_16.i191.i
  store i32 %old.i190.i, ptr %28, align 4, !alias.scope !1574, !noalias !1582
  %29 = trunc i64 %p.sroa.0.1.i3155.fr to i32
  store i32 %29, ptr %27, align 4, !alias.scope !1571, !noalias !1580
  %_0.i192.i = zext i32 %old.i190.i to i64
  %_29.0.i = add nuw nsw i64 %p.sroa.0.1.i3155.fr, 1
  %_13.0.i20 = sub i64 500000, %p.sroa.0.1.i3155.fr
  %spec.store.select3.i21 = tail call i64 @llvm.umin.i64(i64 %_13.0.i20, i64 258)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1583)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1586)
  %spec.store.select.i27 = tail call i64 @llvm.umin.i64(i64 %_13.0.i20, i64 64)
  %30 = and i64 %spec.store.select3.i21, 504
  %31 = extractelement <4 x i8> %21, i64 3
  %_24.i2313068.not = icmp eq i64 %30, %spec.store.select3.i21
  br label %bb11.i29

bb11.i29:                                         ; preds = %bb37.i, %bb11.i
  %start1.sroa.0.0.i3075 = phi i64 [ %_0.i192.i, %bb11.i ], [ %nx.i, %bb37.i ]
  %have.sroa.0.0.i3074 = phi i64 [ 3, %bb11.i ], [ %have.sroa.0.2.i, %bb37.i ]
  %depth.sroa.0.0.i3073 = phi i64 [ 6, %bb11.i ], [ %_66.0.i, %bb37.i ]
  %bd.sroa.0.0.i3072 = phi i64 [ 0, %bb11.i ], [ %bd.sroa.0.2.i, %bb37.i ]
  %pb.sroa.0.1.i3071 = phi i8 [ %31, %bb11.i ], [ %pb.sroa.0.3.i, %bb37.i ]
  %d.i = sub nsw i64 %p.sroa.0.1.i3155.fr, %start1.sroa.0.0.i3075
  %_29.i = add nsw i64 %d.i, -1
  %_28.i = icmp ult i64 %_29.i, 32768
  br i1 %_28.i, label %bb13.i, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit

bb13.i:                                           ; preds = %bb11.i29
  %_34.0.i = add nuw nsw i64 %start1.sroa.0.0.i3075, %have.sroa.0.0.i3074
  %_30.i = icmp ult i64 %_34.0.i, 500000
  br i1 %_30.i, label %bb16.i31, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit

bb16.i31:                                         ; preds = %bb13.i
  %32 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_34.0.i
  %_36.i = load i8, ptr %32, align 1, !alias.scope !1583, !noalias !1586, !noundef !135
  %_35.i32 = icmp eq i8 %_36.i, %pb.sroa.0.1.i3071
  br i1 %_35.i32, label %bb2.i255, label %bb37.i

bb2.i255:                                         ; preds = %bb16.i31, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit
  %k.sroa.0.0.i2263067 = phi i64 [ %_10.0.i256, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit ], [ 0, %bb16.i31 ]
  %_10.0.i256 = add nuw nsw i64 %k.sroa.0.0.i2263067, 8
  %_7.not.i259 = icmp samesign ugt i64 %_10.0.i256, %spec.store.select3.i21
  br i1 %_7.not.i259, label %bb15.i227, label %bb4.i260

bb4.i260:                                         ; preds = %bb2.i255
  %_13.i261 = add nuw nsw i64 %k.sroa.0.0.i2263067, %start1.sroa.0.0.i3075
  %33 = icmp samesign ugt i64 %_13.i261, 499992
  br i1 %33, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit672, label %bb2.i608

bb2.i608:                                         ; preds = %bb4.i260
  %34 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_13.i261
  %_15.i612 = load i8, ptr %34, align 1, !alias.scope !1588, !noalias !1586, !noundef !135
  %_14.i613 = zext i8 %_15.i612 to i64
  %_13.i614 = shl nuw i64 %_14.i613, 56
  %35 = getelementptr inbounds nuw i8, ptr %34, i64 1
  %_19.i619 = load i8, ptr %35, align 1, !alias.scope !1588, !noalias !1586, !noundef !135
  %_18.i620 = zext i8 %_19.i619 to i64
  %_17.i621 = shl nuw nsw i64 %_18.i620, 48
  %_12.i622 = or disjoint i64 %_17.i621, %_13.i614
  %36 = getelementptr inbounds nuw i8, ptr %34, i64 2
  %_25.i627 = load i8, ptr %36, align 1, !alias.scope !1588, !noalias !1586, !noundef !135
  %_24.i628 = zext i8 %_25.i627 to i64
  %_23.i629 = shl nuw nsw i64 %_24.i628, 40
  %_11.i630 = or disjoint i64 %_12.i622, %_23.i629
  %37 = getelementptr inbounds nuw i8, ptr %34, i64 3
  %_31.i635 = load i8, ptr %37, align 1, !alias.scope !1588, !noalias !1586, !noundef !135
  %_30.i636 = zext i8 %_31.i635 to i64
  %_29.i637 = shl nuw nsw i64 %_30.i636, 32
  %_10.i638 = or disjoint i64 %_11.i630, %_29.i637
  %38 = getelementptr inbounds nuw i8, ptr %34, i64 4
  %_37.i643 = load i8, ptr %38, align 1, !alias.scope !1588, !noalias !1586, !noundef !135
  %_36.i644 = zext i8 %_37.i643 to i64
  %_35.i645 = shl nuw nsw i64 %_36.i644, 24
  %_9.i646 = or disjoint i64 %_10.i638, %_35.i645
  %39 = getelementptr inbounds nuw i8, ptr %34, i64 5
  %_43.i651 = load i8, ptr %39, align 1, !alias.scope !1588, !noalias !1586, !noundef !135
  %_42.i652 = zext i8 %_43.i651 to i64
  %_41.i653 = shl nuw nsw i64 %_42.i652, 16
  %_8.i654 = or disjoint i64 %_9.i646, %_41.i653
  %40 = getelementptr inbounds nuw i8, ptr %34, i64 6
  %_49.i659 = load i8, ptr %40, align 1, !alias.scope !1588, !noalias !1586, !noundef !135
  %_48.i660 = zext i8 %_49.i659 to i64
  %_47.i661 = shl nuw nsw i64 %_48.i660, 8
  %_7.i662 = or i64 %_8.i654, %_47.i661
  %41 = getelementptr inbounds nuw i8, ptr %34, i64 7
  %_54.i667 = load i8, ptr %41, align 1, !alias.scope !1588, !noalias !1586, !noundef !135
  %_53.i668 = zext i8 %_54.i667 to i64
  %42 = or i64 %_7.i662, %_53.i668
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit672

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit672: ; preds = %bb4.i260, %bb2.i608
  %_0.sroa.0.0.i670 = phi i64 [ %42, %bb2.i608 ], [ 0, %bb4.i260 ]
  %_16.i263 = add nuw i64 %k.sroa.0.0.i2263067, %p.sroa.0.1.i3155.fr
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1591)
  %_5.1.i = icmp ugt i64 %_16.i263, -9
  br i1 %_5.1.i, label %panic.i603, label %bb1.i559

bb1.i559:                                         ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit672
  %43 = icmp ugt i64 %_16.i263, 499992
  br i1 %43, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit, label %bb2.i562

panic.i603:                                       ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit672
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_bb314acf14069c2fbedf530b060ebd60) #13, !noalias !1594
  unreachable

bb2.i562:                                         ; preds = %bb1.i559
  %44 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_16.i263
  %_15.i566 = load i8, ptr %44, align 1, !alias.scope !1591, !noalias !1586, !noundef !135
  %_14.i567 = zext i8 %_15.i566 to i64
  %_13.i568 = shl nuw i64 %_14.i567, 56
  %45 = getelementptr inbounds nuw i8, ptr %44, i64 1
  %_19.i571 = load i8, ptr %45, align 1, !alias.scope !1591, !noalias !1586, !noundef !135
  %_18.i572 = zext i8 %_19.i571 to i64
  %_17.i = shl nuw nsw i64 %_18.i572, 48
  %_12.i573 = or disjoint i64 %_17.i, %_13.i568
  %46 = getelementptr inbounds nuw i8, ptr %44, i64 2
  %_25.i577 = load i8, ptr %46, align 1, !alias.scope !1591, !noalias !1586, !noundef !135
  %_24.i578 = zext i8 %_25.i577 to i64
  %_23.i = shl nuw nsw i64 %_24.i578, 40
  %_11.i579 = or disjoint i64 %_12.i573, %_23.i
  %47 = getelementptr inbounds nuw i8, ptr %44, i64 3
  %_31.i = load i8, ptr %47, align 1, !alias.scope !1591, !noalias !1586, !noundef !135
  %_30.i582 = zext i8 %_31.i to i64
  %_29.i583 = shl nuw nsw i64 %_30.i582, 32
  %_10.i584 = or disjoint i64 %_11.i579, %_29.i583
  %48 = getelementptr inbounds nuw i8, ptr %44, i64 4
  %_37.i586 = load i8, ptr %48, align 1, !alias.scope !1591, !noalias !1586, !noundef !135
  %_36.i587 = zext i8 %_37.i586 to i64
  %_35.i588 = shl nuw nsw i64 %_36.i587, 24
  %_9.i589 = or disjoint i64 %_10.i584, %_35.i588
  %49 = getelementptr inbounds nuw i8, ptr %44, i64 5
  %_43.i = load i8, ptr %49, align 1, !alias.scope !1591, !noalias !1586, !noundef !135
  %_42.i = zext i8 %_43.i to i64
  %_41.i592 = shl nuw nsw i64 %_42.i, 16
  %_8.i593 = or disjoint i64 %_9.i589, %_41.i592
  %50 = getelementptr inbounds nuw i8, ptr %44, i64 6
  %_49.i596 = load i8, ptr %50, align 1, !alias.scope !1591, !noalias !1586, !noundef !135
  %_48.i = zext i8 %_49.i596 to i64
  %_47.i = shl nuw nsw i64 %_48.i, 8
  %_7.i597 = or i64 %_8.i593, %_47.i
  %51 = getelementptr inbounds nuw i8, ptr %44, i64 7
  %_54.i = load i8, ptr %51, align 1, !alias.scope !1591, !noalias !1586, !noundef !135
  %_53.i = zext i8 %_54.i to i64
  %52 = or i64 %_7.i597, %_53.i
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit: ; preds = %bb1.i559, %bb2.i562
  %_0.sroa.0.0.i602 = phi i64 [ %52, %bb2.i562 ], [ 0, %bb1.i559 ]
  %53 = icmp eq i64 %_0.sroa.0.0.i670, %_0.sroa.0.0.i602
  br i1 %53, label %bb2.i255, label %bb15.i227.thread

bb15.i227:                                        ; preds = %bb2.i255
  br i1 %_24.i2313068.not, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit275, label %bb19.i237

bb15.i227.thread:                                 ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit
  %_0.sroa.0.0.i602.lcssa = phi i64 [ %_0.sroa.0.0.i602, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit ]
  %_0.sroa.0.0.i670.lcssa302 = phi i64 [ %_0.sroa.0.0.i670, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit ]
  %k.sroa.0.0.i2263067.lcssa301 = phi i64 [ %k.sroa.0.0.i2263067, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit ]
  %x.i266 = xor i64 %_0.sroa.0.0.i602.lcssa, %_0.sroa.0.0.i670.lcssa302
  %54 = tail call range(i64 0, 65) i64 @llvm.ctlz.i64(i64 %x.i266, i1 true)
  %_2018.i267 = lshr i64 %54, 3
  %_22.0.i268 = or disjoint i64 %_2018.i267, %k.sroa.0.0.i2263067.lcssa301
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit275

bb19.i237:                                        ; preds = %bb15.i227, %bb22.i247
  %k.sroa.0.2.i2303070 = phi i64 [ %k.sroa.0.3.i252, %bb22.i247 ], [ %30, %bb15.i227 ]
  %_30.0.i235 = add nuw nsw i64 %k.sroa.0.2.i2303070, %start1.sroa.0.0.i3075
  %_32.i238 = icmp samesign ult i64 %_30.0.i235, 500000
  br i1 %_32.i238, label %bb20.i240, label %panic4.i239

bb20.i240:                                        ; preds = %bb19.i237
  %55 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_30.0.i235
  %_27.i241 = load i8, ptr %55, align 1, !alias.scope !1595, !noalias !1586, !noundef !135
  %_36.0.i242 = add i64 %k.sroa.0.2.i2303070, %p.sroa.0.1.i3155.fr
  %_36.1.i243 = icmp ult i64 %_36.0.i242, %p.sroa.0.1.i3155.fr
  br i1 %_36.1.i243, label %panic5.i253, label %bb21.i244

panic4.i239:                                      ; preds = %bb19.i237
  %_30.0.i235.lcssa303 = phi i64 [ %_30.0.i235, %bb19.i237 ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_30.0.i235.lcssa303, i64 noundef range(i64 0, -9223372036854775808) 500000, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_333f7815cbdde125b13aaef2eac5916c) #13, !noalias !1586
  unreachable

bb21.i244:                                        ; preds = %bb20.i240
  %_37.i245 = icmp ult i64 %_36.0.i242, 500000
  br i1 %_37.i245, label %bb22.i247, label %panic6.i246

panic5.i253:                                      ; preds = %bb20.i240
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_44247feb933c63f72105b72612a623ee) #13, !noalias !1586
  unreachable

bb22.i247:                                        ; preds = %bb21.i244
  %56 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_36.0.i242
  %_33.i248 = load i8, ptr %56, align 1, !alias.scope !1595, !noalias !1586, !noundef !135
  %_26.i249 = icmp eq i8 %_27.i241, %_33.i248
  %_38.0.i250 = zext i1 %_26.i249 to i64
  %k.sroa.0.3.i252 = add nuw nsw i64 %k.sroa.0.2.i2303070, %_38.0.i250
  %_24.i231 = icmp samesign ult i64 %k.sroa.0.3.i252, %spec.store.select3.i21
  %or.cond.i232 = select i1 %_26.i249, i1 %_24.i231, i1 false
  br i1 %or.cond.i232, label %bb19.i237, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit275

panic6.i246:                                      ; preds = %bb21.i244
  %_36.0.i242.lcssa307 = phi i64 [ %_36.0.i242, %bb21.i244 ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_36.0.i242.lcssa307, i64 noundef range(i64 0, -9223372036854775808) 500000, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_c7b835eab7e4664f8dc21896c854bf2b) #13, !noalias !1586
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit275: ; preds = %bb22.i247, %bb15.i227.thread, %bb15.i227
  %k.sroa.0.2.i230.lcssa = phi i64 [ %30, %bb15.i227 ], [ %_22.0.i268, %bb15.i227.thread ], [ %k.sroa.0.3.i252, %bb22.i247 ]
  %_46.i = icmp ugt i64 %k.sroa.0.2.i230.lcssa, %have.sroa.0.0.i3074
  br i1 %_46.i, label %bb19.i, label %bb37.i

bb19.i:                                           ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit275
  %_51.not.i = icmp ult i64 %k.sroa.0.2.i230.lcssa, %spec.store.select.i27
  br i1 %_51.not.i, label %bb26.i, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit

bb26.i:                                           ; preds = %bb19.i
  %_55.0.i = add i64 %k.sroa.0.2.i230.lcssa, %p.sroa.0.1.i3155.fr
  %_55.1.i = icmp ult i64 %_55.0.i, %p.sroa.0.1.i3155.fr
  br i1 %_55.1.i, label %panic7.i, label %bb27.i

bb27.i:                                           ; preds = %bb26.i
  %_53.not.i = icmp ult i64 %_55.0.i, 500000
  br i1 %_53.not.i, label %bb31.i, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit

panic7.i:                                         ; preds = %bb26.i
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_5082c7ce777234b7475a595bf60db7a2) #13, !noalias !1586
  unreachable

bb31.i:                                           ; preds = %bb27.i
  %57 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_55.0.i
  %58 = load i8, ptr %57, align 1, !alias.scope !1583, !noalias !1586, !noundef !135
  br label %bb37.i

bb37.i:                                           ; preds = %bb31.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit275, %bb16.i31
  %pb.sroa.0.3.i = phi i8 [ %pb.sroa.0.1.i3071, %bb16.i31 ], [ %pb.sroa.0.1.i3071, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit275 ], [ %58, %bb31.i ]
  %bd.sroa.0.2.i = phi i64 [ %bd.sroa.0.0.i3072, %bb16.i31 ], [ %bd.sroa.0.0.i3072, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit275 ], [ %d.i, %bb31.i ]
  %have.sroa.0.2.i = phi i64 [ %have.sroa.0.0.i3074, %bb16.i31 ], [ %have.sroa.0.0.i3074, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit275 ], [ %k.sroa.0.2.i230.lcssa, %bb31.i ]
  %_60.i33 = and i64 %start1.sroa.0.0.i3075, 32767
  %59 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_60.i33
  %_59.i = load i32, ptr %59, align 4, !alias.scope !1586, !noalias !1583, !noundef !135
  %nx.i = zext i32 %_59.i to i64
  %_64.i = icmp samesign ule i64 %start1.sroa.0.0.i3075, %nx.i
  %_66.0.i = add nsw i64 %depth.sroa.0.0.i3073, -1
  %_24.not.i = icmp eq i64 %_66.0.i, 0
  %or.cond = select i1 %_64.i, i1 true, i1 %_24.not.i
  br i1 %or.cond, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit, label %bb11.i29

_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit: ; preds = %bb19.i, %bb27.i, %bb37.i, %bb13.i, %bb11.i29
  %have.sroa.0.1.i3357 = phi i64 [ %have.sroa.0.0.i3074, %bb11.i29 ], [ %have.sroa.0.2.i, %bb37.i ], [ %have.sroa.0.0.i3074, %bb13.i ], [ %k.sroa.0.2.i230.lcssa, %bb27.i ], [ %k.sroa.0.2.i230.lcssa, %bb19.i ]
  %bd.sroa.0.1.i3356 = phi i64 [ %bd.sroa.0.0.i3072, %bb11.i29 ], [ %bd.sroa.0.2.i, %bb37.i ], [ %bd.sroa.0.0.i3072, %bb13.i ], [ %d.i, %bb27.i ], [ %d.i, %bb19.i ]
  %.not = icmp eq i64 %bd.sroa.0.1.i3356, 0
  br i1 %.not, label %bb154.i, label %bb16.i.preheader

bb16.i.preheader:                                 ; preds = %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit
  %_39.i3112 = icmp ult i64 %have.sroa.0.1.i3357, 32
  br i1 %_39.i3112, label %bb18.i, label %bb63.i

bb8.i:                                            ; preds = %bb5.i, %bb8.i
  %ins.sroa.0.1.i3065 = phi i64 [ %_23.0.i, %bb8.i ], [ %ins.sroa.0.0.i3154, %bb5.i ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1598)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1601)
  %60 = getelementptr inbounds nuw i8, ptr %input.0, i64 %ins.sroa.0.1.i3065
  %61 = load i32, ptr %60, align 1
  %62 = call i32 @llvm.bswap.i32(i32 %61)
  %63 = zext i32 %62 to i64
  %64 = mul i64 %63, -7046029254386353131
  %65 = lshr i64 %64, 48
  %66 = getelementptr inbounds nuw [4 x i8], ptr %head.i, i64 %65
  %old.i.i = load i32, ptr %66, align 4, !alias.scope !1598, !noalias !1603, !noundef !135
  %_16.i.i = and i64 %ins.sroa.0.1.i3065, 32767
  %67 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_16.i.i
  store i32 %old.i.i, ptr %67, align 4, !alias.scope !1601, !noalias !1605
  %68 = trunc i64 %ins.sroa.0.1.i3065 to i32
  store i32 %68, ptr %66, align 4, !alias.scope !1598, !noalias !1603
  %_23.0.i = add nuw nsw i64 %ins.sroa.0.1.i3065, 1
  %exitcond.not = icmp eq i64 %_23.0.i, %p.sroa.0.1.i3155.fr
  br i1 %exitcond.not, label %bb11.i, label %bb8.i

bb154.i:                                          ; preds = %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1606)
  %_9.i310 = icmp ult i64 %nt.sroa.0.1.i3158, %out.1
  br i1 %_9.i310, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit315, label %panic1.i311

panic1.i311:                                      ; preds = %bb154.i
  %nt.sroa.0.1.i3158.lcssa389 = phi i64 [ %nt.sroa.0.1.i3158, %bb154.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %nt.sroa.0.1.i3158.lcssa389, i64 noundef range(i64 0, 2305843009213693952) %out.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_ce72d480401e07b7a290039044612259) #13, !noalias !1609
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit315: ; preds = %bb154.i
  %69 = getelementptr inbounds nuw [4 x i8], ptr %out.0, i64 %nt.sroa.0.1.i3158
  %70 = extractelement <4 x i8> %21, i64 0
  %71 = zext i8 %70 to i32
  store i32 %71, ptr %69, align 4, !alias.scope !1606, !noalias !1611
  %_219.0.i = add i64 %miss.sroa.0.0.i3157, 1
  %_219.1.i = icmp eq i64 %miss.sroa.0.0.i3157, -1
  br i1 %_219.1.i, label %panic5.i, label %bb157.i

bb157.i:                                          ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit315
  %72 = lshr i64 %_219.0.i, 5
  %nt.sroa.0.3.i3077 = add nuw nsw i64 %nt.sroa.0.1.i3158, 1
  %_225.i3078 = icmp ne i64 %72, 0
  %_227.i3079 = icmp ult i64 %p.sroa.0.1.i3155.fr, 499991
  %or.cond45.i3080 = and i1 %_225.i3078, %_227.i3079
  br i1 %or.cond45.i3080, label %bb164.i.preheader, label %bb170.i

bb164.i.preheader:                                ; preds = %bb157.i
  %spec.store.select.i = tail call i64 @llvm.umin.i64(i64 %72, i64 1000000)
  %73 = add nsw i64 %spec.store.select.i, -1
  %74 = sub nuw nsw i64 499990, %p.sroa.0.1.i3155.fr
  %umin = call i64 @llvm.umin.i64(i64 %73, i64 %74)
  %75 = freeze i64 %umin
  %76 = xor i64 %nt.sroa.0.1.i3158, -1
  %77 = add nsw i64 %out.1, %76
  %umin267 = call i64 @llvm.umin.i64(i64 %75, i64 %77)
  %78 = add i64 %umin267, 1
  %min.iters.check = icmp ult i64 %78, 9
  br i1 %min.iters.check, label %bb164.i.preheader299, label %vector.ph

bb164.i.preheader299:                             ; preds = %vector.body, %bb164.i.preheader
  %nt.sroa.0.3.i3083.ph = phi i64 [ %nt.sroa.0.3.i3077, %bb164.i.preheader ], [ %81, %vector.body ]
  %p.sroa.0.3.i3082.ph = phi i64 [ %_29.0.i, %bb164.i.preheader ], [ %82, %vector.body ]
  %step.sroa.0.0.i3081.ph = phi i64 [ %spec.store.select.i, %bb164.i.preheader ], [ %83, %vector.body ]
  br label %bb164.i

vector.ph:                                        ; preds = %bb164.i.preheader
  %n.mod.vf = and i64 %78, 7
  %79 = icmp eq i64 %n.mod.vf, 0
  %80 = select i1 %79, i64 8, i64 %n.mod.vf
  %n.vec = sub nuw i64 %78, %80
  %81 = add i64 %nt.sroa.0.3.i3077, %n.vec
  %82 = add i64 %_29.0.i, %n.vec
  %83 = sub i64 %spec.store.select.i, %n.vec
  %84 = getelementptr i8, ptr %input.0, i64 %_29.0.i
  %85 = getelementptr [4 x i8], ptr %out.0, i64 %nt.sroa.0.3.i3077
  br label %vector.body

vector.body:                                      ; preds = %vector.body, %vector.ph
  %index = phi i64 [ 0, %vector.ph ], [ %index.next, %vector.body ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1612)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1615)
  %86 = getelementptr i8, ptr %84, i64 %index
  %87 = getelementptr inbounds nuw i8, ptr %86, i64 4
  %wide.load = load <4 x i8>, ptr %86, align 1, !alias.scope !1612, !noalias !1615
  %wide.load268 = load <4 x i8>, ptr %87, align 1, !alias.scope !1612, !noalias !1615
  %88 = getelementptr [4 x i8], ptr %85, i64 %index
  %89 = zext <4 x i8> %wide.load to <4 x i32>
  %90 = zext <4 x i8> %wide.load268 to <4 x i32>
  %91 = getelementptr inbounds nuw i8, ptr %88, i64 16
  store <4 x i32> %89, ptr %88, align 4, !alias.scope !1615, !noalias !1612
  store <4 x i32> %90, ptr %91, align 4, !alias.scope !1615, !noalias !1612
  %index.next = add nuw i64 %index, 8
  %92 = icmp eq i64 %index.next, %n.vec
  br i1 %92, label %bb164.i.preheader299, label %vector.body, !llvm.loop !1617

panic5.i:                                         ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit315
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_6c101138787766aed78cb0daf47995e1) #13
  unreachable

bb170.i:                                          ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit306, %bb157.i
  %p.sroa.0.3.i.lcssa = phi i64 [ %_29.0.i, %bb157.i ], [ %_231.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit306 ]
  %nt.sroa.0.3.i.lcssa = phi i64 [ %nt.sroa.0.3.i3077, %bb157.i ], [ %nt.sroa.0.3.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit306 ]
  %spec.select.i = tail call i64 @llvm.umax.i64(i64 %_29.0.i, i64 %p.sroa.0.3.i.lcssa)
  br label %bb174.i

bb164.i:                                          ; preds = %bb164.i.preheader299, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit306
  %nt.sroa.0.3.i3083 = phi i64 [ %nt.sroa.0.3.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit306 ], [ %nt.sroa.0.3.i3083.ph, %bb164.i.preheader299 ]
  %p.sroa.0.3.i3082 = phi i64 [ %_231.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit306 ], [ %p.sroa.0.3.i3082.ph, %bb164.i.preheader299 ]
  %step.sroa.0.0.i3081 = phi i64 [ %_232.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit306 ], [ %step.sroa.0.0.i3081.ph, %bb164.i.preheader299 ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1612)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1615)
  %exitcond3345.not = icmp eq i64 %nt.sroa.0.3.i3083, %out.1
  br i1 %exitcond3345.not, label %panic1.i302, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit306

panic1.i302:                                      ; preds = %bb164.i
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %out.1, i64 noundef range(i64 0, 2305843009213693952) %out.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_ce72d480401e07b7a290039044612259) #13, !noalias !1618
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit306: ; preds = %bb164.i
  %93 = getelementptr inbounds nuw i8, ptr %input.0, i64 %p.sroa.0.3.i3082
  %_5.i304 = load i8, ptr %93, align 1, !alias.scope !1612, !noalias !1615, !noundef !135
  %94 = getelementptr inbounds nuw [4 x i8], ptr %out.0, i64 %nt.sroa.0.3.i3083
  %95 = zext i8 %_5.i304 to i32
  store i32 %95, ptr %94, align 4, !alias.scope !1615, !noalias !1612
  %_231.0.i = add nuw nsw i64 %p.sroa.0.3.i3082, 1
  %_232.0.i = add nsw i64 %step.sroa.0.0.i3081, -1
  %nt.sroa.0.3.i = add i64 %nt.sroa.0.3.i3083, 1
  %_225.i = icmp ne i64 %_232.0.i, 0
  %_227.i = icmp ult i64 %p.sroa.0.3.i3082, 499991
  %or.cond45.i = select i1 %_225.i, i1 %_227.i, i1 false
  br i1 %or.cond45.i, label %bb164.i, label %bb170.i, !llvm.loop !1619

bb174.i:                                          ; preds = %bb150.i, %bb170.i
  %ins.sroa.0.3.i = phi i64 [ %spec.select150.i, %bb150.i ], [ %spec.select.i, %bb170.i ]
  %p.sroa.0.4.i = phi i64 [ %_19.0.i330, %bb150.i ], [ %p.sroa.0.3.i.lcssa, %bb170.i ]
  %miss.sroa.0.1.i = phi i64 [ 0, %bb150.i ], [ %_219.0.i, %bb170.i ]
  %nt.sroa.0.4.i = phi i64 [ %_17.0.i, %bb150.i ], [ %nt.sroa.0.3.i.lcssa, %bb170.i ]
  %_11.i = icmp ult i64 %p.sroa.0.4.i, 499992
  %_13.i = icmp ne i64 %_15.0.i, 0
  %or.cond.i = select i1 %_11.i, i1 %_13.i, i1 false
  br i1 %or.cond.i, label %bb5.i, label %bb178.i

bb18.i:                                           ; preds = %bb16.i.preheader, %bb59.i
  %nt.sroa.0.5.i3117 = phi i64 [ %_10.0.i287, %bb59.i ], [ %nt.sroa.0.1.i3158, %bb16.i.preheader ]
  %l.sroa.0.0.i3116 = phi i64 [ %l.sroa.0.1.i, %bb59.i ], [ %have.sroa.0.1.i3357, %bb16.i.preheader ]
  %d.sroa.0.0.i3115 = phi i64 [ %d.sroa.0.1.i, %bb59.i ], [ %bd.sroa.0.1.i3356, %bb16.i.preheader ]
  %p.sroa.0.5.i3114 = phi i64 [ %p.sroa.0.6.i, %bb59.i ], [ %p.sroa.0.1.i3155.fr, %bb16.i.preheader ]
  %ins.sroa.0.4.i3113 = phi i64 [ %ins.sroa.0.5.i, %bb59.i ], [ %_29.0.i, %bb16.i.preheader ]
  %_44.0.i = add i64 %p.sroa.0.5.i3114, 1
  %_41.i = icmp ult i64 %p.sroa.0.5.i3114, 499991
  br i1 %_41.i, label %bb21.i, label %bb63.i

bb63.i:                                           ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit, %bb16.i123, %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit155, %bb13.i121, %bb11.i107, %bb35.i, %bb39.i, %bb48.i, %bb59.i, %bb18.i, %bb16.i.preheader
  %ins.sroa.0.4.i.lcssa = phi i64 [ %_29.0.i, %bb16.i.preheader ], [ %_80.0.i, %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit155 ], [ %_80.0.i, %bb13.i121 ], [ %_80.0.i, %bb11.i107 ], [ %ins.sroa.0.5.i, %bb59.i ], [ %_80.0.i, %bb39.i ], [ %_51.0.i, %bb35.i ], [ %_80.0.i, %bb48.i ], [ %ins.sroa.0.4.i3113, %bb18.i ], [ %_80.0.i, %bb16.i123 ], [ %_80.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit ]
  %p.sroa.0.5.i.lcssa = phi i64 [ %p.sroa.0.1.i3155.fr, %bb16.i.preheader ], [ %p.sroa.0.5.i3114, %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit155 ], [ %p.sroa.0.5.i3114, %bb13.i121 ], [ %p.sroa.0.5.i3114, %bb11.i107 ], [ %p.sroa.0.6.i, %bb59.i ], [ %p.sroa.0.5.i3114, %bb39.i ], [ 499990, %bb35.i ], [ %p.sroa.0.5.i3114, %bb48.i ], [ %p.sroa.0.5.i3114, %bb18.i ], [ %p.sroa.0.5.i3114, %bb16.i123 ], [ %p.sroa.0.5.i3114, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit ]
  %d.sroa.0.0.i.lcssa = phi i64 [ %bd.sroa.0.1.i3356, %bb16.i.preheader ], [ %d.sroa.0.0.i3115, %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit155 ], [ %d.sroa.0.0.i3115, %bb13.i121 ], [ %d.sroa.0.0.i3115, %bb11.i107 ], [ %d.sroa.0.1.i, %bb59.i ], [ %d.sroa.0.0.i3115, %bb39.i ], [ %d.sroa.0.0.i3115, %bb35.i ], [ %d.sroa.0.0.i3115, %bb48.i ], [ %d.sroa.0.0.i3115, %bb18.i ], [ %d.sroa.0.0.i3115, %bb16.i123 ], [ %d.sroa.0.0.i3115, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit ]
  %l.sroa.0.0.i.lcssa = phi i64 [ %have.sroa.0.1.i3357, %bb16.i.preheader ], [ %l.sroa.0.0.i3116, %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit155 ], [ %l.sroa.0.0.i3116, %bb13.i121 ], [ %l.sroa.0.0.i3116, %bb11.i107 ], [ %l.sroa.0.1.i, %bb59.i ], [ %l.sroa.0.0.i3116, %bb39.i ], [ %l.sroa.0.0.i3116, %bb35.i ], [ %l.sroa.0.0.i3116, %bb48.i ], [ %l.sroa.0.0.i3116, %bb18.i ], [ %l.sroa.0.0.i3116, %bb16.i123 ], [ %l.sroa.0.0.i3116, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit ]
  %nt.sroa.0.5.i.lcssa = phi i64 [ %nt.sroa.0.1.i3158, %bb16.i.preheader ], [ %nt.sroa.0.5.i3117, %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit155 ], [ %nt.sroa.0.5.i3117, %bb13.i121 ], [ %nt.sroa.0.5.i3117, %bb11.i107 ], [ %_10.0.i287, %bb59.i ], [ %nt.sroa.0.5.i3117, %bb39.i ], [ %nt.sroa.0.5.i3117, %bb35.i ], [ %nt.sroa.0.5.i3117, %bb48.i ], [ %nt.sroa.0.5.i3117, %bb18.i ], [ %nt.sroa.0.5.i3117, %bb16.i123 ], [ %nt.sroa.0.5.i3117, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit ]
  %96 = add i64 %nt.sroa.0.5.i.lcssa, -1
  %97 = icmp ult i64 %96, %out.1
  %_110.i3132 = icmp ult i64 %l.sroa.0.0.i.lcssa, 258
  %or.cond49.i3133 = select i1 %97, i1 %_110.i3132, i1 false
  %_112.i3134 = icmp ult i64 %d.sroa.0.0.i.lcssa, %p.sroa.0.5.i.lcssa
  %or.cond149.i3135 = and i1 %or.cond49.i3133, %_112.i3134
  br i1 %or.cond149.i3135, label %bb71.i, label %bb116.i

bb21.i:                                           ; preds = %bb18.i
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1620)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1623)
  %98 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_44.0.i
  %_11.i395 = load i8, ptr %98, align 1, !alias.scope !1625, !noalias !1628, !noundef !135
  %_10.i396 = zext i8 %_11.i395 to i64
  %_9.i397 = shl nuw nsw i64 %_10.i396, 24
  %99 = getelementptr inbounds nuw i8, ptr %input.0, i64 %p.sroa.0.5.i3114
  %100 = getelementptr inbounds nuw i8, ptr %99, i64 2
  %_15.i402 = load i8, ptr %100, align 1, !alias.scope !1625, !noalias !1628, !noundef !135
  %_14.i403 = zext i8 %_15.i402 to i64
  %_13.i404 = shl nuw nsw i64 %_14.i403, 16
  %_8.i405 = or disjoint i64 %_13.i404, %_9.i397
  %101 = getelementptr inbounds nuw i8, ptr %99, i64 3
  %_21.i410 = load i8, ptr %101, align 1, !alias.scope !1625, !noalias !1628, !noundef !135
  %_20.i411 = zext i8 %_21.i410 to i64
  %_19.i412 = shl nuw nsw i64 %_20.i411, 8
  %_7.i413 = or disjoint i64 %_8.i405, %_19.i412
  %102 = getelementptr inbounds nuw i8, ptr %99, i64 4
  %_26.i418 = load i8, ptr %102, align 1, !alias.scope !1625, !noalias !1628, !noundef !135
  %_25.i419 = zext i8 %_26.i418 to i64
  %103 = or disjoint i64 %_7.i413, %_25.i419
  %104 = mul i64 %103, -7046029254386353131
  %105 = lshr i64 %104, 48
  %106 = getelementptr inbounds nuw [4 x i8], ptr %head.i, i64 %105
  %old.i183.i = load i32, ptr %106, align 4, !alias.scope !1620, !noalias !1629, !noundef !135
  %_16.i184.i = and i64 %_44.0.i, 32767
  %107 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_16.i184.i
  store i32 %old.i183.i, ptr %107, align 4, !alias.scope !1623, !noalias !1631
  %108 = trunc nuw nsw i64 %_44.0.i to i32
  store i32 %108, ptr %106, align 4, !alias.scope !1620, !noalias !1629
  %_0.i185.i = zext i32 %old.i183.i to i64
  %_51.0.i = add nuw nsw i64 %p.sroa.0.5.i3114, 2
  %_56.0.i = add nsw i64 %l.sroa.0.0.i3116, -1
  %spec.select.i10 = tail call i64 @llvm.umax.i64(i64 %_56.0.i, i64 3)
  %_13.0.i11 = sub nuw nsw i64 499999, %p.sroa.0.5.i3114
  %spec.store.select3.i12 = tail call i64 @llvm.umin.i64(i64 %_13.0.i11, i64 258)
  %_19.0.i37 = add nuw nsw i64 %spec.select.i10, %_44.0.i
  %_16.i38 = icmp ult i64 %_19.0.i37, 500000
  br i1 %_16.i38, label %bb7.i92, label %bb11.i49

bb7.i92:                                          ; preds = %bb21.i
  %109 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_19.0.i37
  %110 = load i8, ptr %109, align 1, !alias.scope !1632, !noalias !1635, !noundef !135
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
  %_36.i66 = load i8, ptr %111, align 1, !alias.scope !1632, !noalias !1635, !noundef !135
  %_35.i67 = icmp eq i8 %_36.i66, %pb.sroa.0.0.i40
  br i1 %_35.i67, label %bb2.i203.preheader, label %bb35.i

bb2.i203.preheader:                               ; preds = %bb16.i65
  %112 = and i64 %spec.store.select3.i12, 504
  br label %bb2.i203

bb2.i203:                                         ; preds = %bb2.i203.preheader, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit741
  %k.sroa.0.0.i1743087 = phi i64 [ %_10.0.i204, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit741 ], [ 0, %bb2.i203.preheader ]
  %_10.0.i204 = add nuw nsw i64 %k.sroa.0.0.i1743087, 8
  %_7.not.i207 = icmp samesign ugt i64 %_10.0.i204, %spec.store.select3.i12
  br i1 %_7.not.i207, label %bb15.i175, label %bb4.i208

bb4.i208:                                         ; preds = %bb2.i203
  %_13.i209 = add nuw nsw i64 %k.sroa.0.0.i1743087, %_0.i185.i
  %113 = icmp samesign ugt i64 %_13.i209, 499992
  br i1 %113, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit810, label %bb2.i746

bb2.i746:                                         ; preds = %bb4.i208
  %114 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_13.i209
  %_15.i750 = load i8, ptr %114, align 1, !alias.scope !1637, !noalias !1635, !noundef !135
  %_14.i751 = zext i8 %_15.i750 to i64
  %_13.i752 = shl nuw i64 %_14.i751, 56
  %115 = getelementptr inbounds nuw i8, ptr %114, i64 1
  %_19.i757 = load i8, ptr %115, align 1, !alias.scope !1637, !noalias !1635, !noundef !135
  %_18.i758 = zext i8 %_19.i757 to i64
  %_17.i759 = shl nuw nsw i64 %_18.i758, 48
  %_12.i760 = or disjoint i64 %_17.i759, %_13.i752
  %116 = getelementptr inbounds nuw i8, ptr %114, i64 2
  %_25.i765 = load i8, ptr %116, align 1, !alias.scope !1637, !noalias !1635, !noundef !135
  %_24.i766 = zext i8 %_25.i765 to i64
  %_23.i767 = shl nuw nsw i64 %_24.i766, 40
  %_11.i768 = or disjoint i64 %_12.i760, %_23.i767
  %117 = getelementptr inbounds nuw i8, ptr %114, i64 3
  %_31.i773 = load i8, ptr %117, align 1, !alias.scope !1637, !noalias !1635, !noundef !135
  %_30.i774 = zext i8 %_31.i773 to i64
  %_29.i775 = shl nuw nsw i64 %_30.i774, 32
  %_10.i776 = or disjoint i64 %_11.i768, %_29.i775
  %118 = getelementptr inbounds nuw i8, ptr %114, i64 4
  %_37.i781 = load i8, ptr %118, align 1, !alias.scope !1637, !noalias !1635, !noundef !135
  %_36.i782 = zext i8 %_37.i781 to i64
  %_35.i783 = shl nuw nsw i64 %_36.i782, 24
  %_9.i784 = or disjoint i64 %_10.i776, %_35.i783
  %119 = getelementptr inbounds nuw i8, ptr %114, i64 5
  %_43.i789 = load i8, ptr %119, align 1, !alias.scope !1637, !noalias !1635, !noundef !135
  %_42.i790 = zext i8 %_43.i789 to i64
  %_41.i791 = shl nuw nsw i64 %_42.i790, 16
  %_8.i792 = or disjoint i64 %_9.i784, %_41.i791
  %120 = getelementptr inbounds nuw i8, ptr %114, i64 6
  %_49.i797 = load i8, ptr %120, align 1, !alias.scope !1637, !noalias !1635, !noundef !135
  %_48.i798 = zext i8 %_49.i797 to i64
  %_47.i799 = shl nuw nsw i64 %_48.i798, 8
  %_7.i800 = or i64 %_8.i792, %_47.i799
  %121 = getelementptr inbounds nuw i8, ptr %114, i64 7
  %_54.i805 = load i8, ptr %121, align 1, !alias.scope !1637, !noalias !1635, !noundef !135
  %_53.i806 = zext i8 %_54.i805 to i64
  %122 = or i64 %_7.i800, %_53.i806
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit810

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit810: ; preds = %bb4.i208, %bb2.i746
  %_0.sroa.0.0.i808 = phi i64 [ %122, %bb2.i746 ], [ 0, %bb4.i208 ]
  %_16.i211 = add nuw i64 %k.sroa.0.0.i1743087, %_44.0.i
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1640)
  %_5.1.i673 = icmp ugt i64 %_16.i211, -9
  br i1 %_5.1.i673, label %panic.i740, label %bb1.i674

bb1.i674:                                         ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit810
  %123 = icmp ugt i64 %_16.i211, 499992
  br i1 %123, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit741, label %bb2.i677

panic.i740:                                       ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit810
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_bb314acf14069c2fbedf530b060ebd60) #13, !noalias !1643
  unreachable

bb2.i677:                                         ; preds = %bb1.i674
  %124 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_16.i211
  %_15.i681 = load i8, ptr %124, align 1, !alias.scope !1640, !noalias !1635, !noundef !135
  %_14.i682 = zext i8 %_15.i681 to i64
  %_13.i683 = shl nuw i64 %_14.i682, 56
  %125 = getelementptr inbounds nuw i8, ptr %124, i64 1
  %_19.i688 = load i8, ptr %125, align 1, !alias.scope !1640, !noalias !1635, !noundef !135
  %_18.i689 = zext i8 %_19.i688 to i64
  %_17.i690 = shl nuw nsw i64 %_18.i689, 48
  %_12.i691 = or disjoint i64 %_17.i690, %_13.i683
  %126 = getelementptr inbounds nuw i8, ptr %124, i64 2
  %_25.i696 = load i8, ptr %126, align 1, !alias.scope !1640, !noalias !1635, !noundef !135
  %_24.i697 = zext i8 %_25.i696 to i64
  %_23.i698 = shl nuw nsw i64 %_24.i697, 40
  %_11.i699 = or disjoint i64 %_12.i691, %_23.i698
  %127 = getelementptr inbounds nuw i8, ptr %124, i64 3
  %_31.i704 = load i8, ptr %127, align 1, !alias.scope !1640, !noalias !1635, !noundef !135
  %_30.i705 = zext i8 %_31.i704 to i64
  %_29.i706 = shl nuw nsw i64 %_30.i705, 32
  %_10.i707 = or disjoint i64 %_11.i699, %_29.i706
  %128 = getelementptr inbounds nuw i8, ptr %124, i64 4
  %_37.i712 = load i8, ptr %128, align 1, !alias.scope !1640, !noalias !1635, !noundef !135
  %_36.i713 = zext i8 %_37.i712 to i64
  %_35.i714 = shl nuw nsw i64 %_36.i713, 24
  %_9.i715 = or disjoint i64 %_10.i707, %_35.i714
  %129 = getelementptr inbounds nuw i8, ptr %124, i64 5
  %_43.i720 = load i8, ptr %129, align 1, !alias.scope !1640, !noalias !1635, !noundef !135
  %_42.i721 = zext i8 %_43.i720 to i64
  %_41.i722 = shl nuw nsw i64 %_42.i721, 16
  %_8.i723 = or disjoint i64 %_9.i715, %_41.i722
  %130 = getelementptr inbounds nuw i8, ptr %124, i64 6
  %_49.i728 = load i8, ptr %130, align 1, !alias.scope !1640, !noalias !1635, !noundef !135
  %_48.i729 = zext i8 %_49.i728 to i64
  %_47.i730 = shl nuw nsw i64 %_48.i729, 8
  %_7.i731 = or i64 %_8.i723, %_47.i730
  %131 = getelementptr inbounds nuw i8, ptr %124, i64 7
  %_54.i736 = load i8, ptr %131, align 1, !alias.scope !1640, !noalias !1635, !noundef !135
  %_53.i737 = zext i8 %_54.i736 to i64
  %132 = or i64 %_7.i731, %_53.i737
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit741

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit741: ; preds = %bb1.i674, %bb2.i677
  %_0.sroa.0.0.i739 = phi i64 [ %132, %bb2.i677 ], [ 0, %bb1.i674 ]
  %133 = icmp eq i64 %_0.sroa.0.0.i808, %_0.sroa.0.0.i739
  br i1 %133, label %bb2.i203, label %bb15.i175.thread

bb15.i175:                                        ; preds = %bb2.i203
  %_24.i1793088.not = icmp eq i64 %112, %spec.store.select3.i12
  br i1 %_24.i1793088.not, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit223, label %bb19.i185

bb15.i175.thread:                                 ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit741
  %_0.sroa.0.0.i739.lcssa = phi i64 [ %_0.sroa.0.0.i739, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit741 ]
  %_0.sroa.0.0.i808.lcssa311 = phi i64 [ %_0.sroa.0.0.i808, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit741 ]
  %k.sroa.0.0.i1743087.lcssa310 = phi i64 [ %k.sroa.0.0.i1743087, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit741 ]
  %x.i214 = xor i64 %_0.sroa.0.0.i739.lcssa, %_0.sroa.0.0.i808.lcssa311
  %134 = tail call range(i64 0, 65) i64 @llvm.ctlz.i64(i64 %x.i214, i1 true)
  %_2018.i215 = lshr i64 %134, 3
  %_22.0.i216 = or disjoint i64 %_2018.i215, %k.sroa.0.0.i1743087.lcssa310
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit223

bb19.i185:                                        ; preds = %bb15.i175, %bb22.i195
  %k.sroa.0.2.i1783090 = phi i64 [ %k.sroa.0.3.i200, %bb22.i195 ], [ %112, %bb15.i175 ]
  %_30.0.i183 = add nuw nsw i64 %k.sroa.0.2.i1783090, %_0.i185.i
  %_32.i186 = icmp samesign ult i64 %_30.0.i183, 500000
  br i1 %_32.i186, label %bb21.i192, label %panic4.i187

panic4.i187:                                      ; preds = %bb19.i185
  %_30.0.i183.lcssa = phi i64 [ %_30.0.i183, %bb19.i185 ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_30.0.i183.lcssa, i64 noundef range(i64 0, -9223372036854775808) 500000, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_333f7815cbdde125b13aaef2eac5916c) #13, !noalias !1635
  unreachable

bb21.i192:                                        ; preds = %bb19.i185
  %_36.0.i190 = add nuw nsw i64 %k.sroa.0.2.i1783090, %_44.0.i
  %_37.i193 = icmp ult i64 %_36.0.i190, 500000
  br i1 %_37.i193, label %bb22.i195, label %panic6.i194

bb22.i195:                                        ; preds = %bb21.i192
  %135 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_30.0.i183
  %_27.i189 = load i8, ptr %135, align 1, !alias.scope !1644, !noalias !1635, !noundef !135
  %136 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_36.0.i190
  %_33.i196 = load i8, ptr %136, align 1, !alias.scope !1644, !noalias !1635, !noundef !135
  %_26.i197 = icmp eq i8 %_27.i189, %_33.i196
  %_38.0.i198 = zext i1 %_26.i197 to i64
  %k.sroa.0.3.i200 = add nuw nsw i64 %k.sroa.0.2.i1783090, %_38.0.i198
  %_24.i179 = icmp samesign ult i64 %k.sroa.0.3.i200, %spec.store.select3.i12
  %or.cond.i180 = select i1 %_26.i197, i1 %_24.i179, i1 false
  br i1 %or.cond.i180, label %bb19.i185, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit223

panic6.i194:                                      ; preds = %bb21.i192
  %_36.0.i190.lcssa = phi i64 [ %_36.0.i190, %bb21.i192 ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_36.0.i190.lcssa, i64 noundef range(i64 0, -9223372036854775808) 500000, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_c7b835eab7e4664f8dc21896c854bf2b) #13, !noalias !1635
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit223: ; preds = %bb22.i195, %bb15.i175.thread, %bb15.i175
  %k.sroa.0.2.i178.lcssa = phi i64 [ %112, %bb15.i175 ], [ %_22.0.i216, %bb15.i175.thread ], [ %k.sroa.0.3.i200, %bb22.i195 ]
  %_46.i81 = icmp ugt i64 %k.sroa.0.2.i178.lcssa, %spec.select.i10
  br i1 %_46.i81, label %bb19.i82, label %bb35.i

bb19.i82:                                         ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit223
  %137 = add i64 %k.sroa.0.2.i178.lcssa, -11
  %or.cond.i964 = icmp ult i64 %137, 247
  br i1 %or.cond.i964, label %bb6.i986, label %bb7.i965

bb7.i965:                                         ; preds = %bb6.i986, %bb19.i82
  %c.sroa.0.0.i966 = phi i32 [ %140, %bb6.i986 ], [ 168, %bb19.i82 ]
  %_17.i967 = icmp ugt i64 %d.i50, 4
  br i1 %_17.i967, label %bb12.i982, label %bb13.i968

bb6.i986:                                         ; preds = %bb19.i82
  %138 = trunc nuw nsw i64 %k.sroa.0.2.i178.lcssa to i32
  %_11.i987 = add nsw i32 %138, -3
  %_10.i988 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_11.i987, i1 false)
  %139 = shl nuw nsw i32 %_10.i988, 4
  %140 = sub nuw nsw i32 632, %139
  br label %bb7.i965

bb13.i968:                                        ; preds = %bb12.i982, %bb7.i965
  %c.sroa.0.1.i969 = phi i32 [ %144, %bb12.i982 ], [ %c.sroa.0.0.i966, %bb7.i965 ]
  %_29.i970 = trunc i64 %k.sroa.0.2.i178.lcssa to i32
  %141 = add i32 %_29.i970, -33554432
  %_30.1.i971 = icmp ult i32 %141, -67108864
  br i1 %_30.1.i971, label %panic8.i978, label %bb14.i972

bb12.i982:                                        ; preds = %bb7.i965
  %142 = trunc nuw i64 %d.i50 to i32
  %_22.i980 = add nsw i32 %142, -1
  %_21.i983 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_22.i980, i1 true)
  %143 = shl nuw nsw i32 %_21.i983, 4
  %reass.sub = sub nsw i32 %c.sroa.0.0.i966, %143
  %144 = add nsw i32 %reass.sub, 480
  br label %bb13.i968

bb14.i972:                                        ; preds = %bb13.i968
  %_30.0.i973 = shl nsw i32 %_29.i970, 6
  %145 = tail call { i32, i1 } @llvm.ssub.with.overflow.i32(i32 %_30.0.i973, i32 %c.sroa.0.1.i969)
  %_31.1.i974 = extractvalue { i32, i1 } %145, 1
  br i1 %_31.1.i974, label %panic9.i977, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit989

panic8.i978:                                      ; preds = %bb13.i968
; call core::panicking::panic_const::panic_const_mul_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_mul_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_72bac528c0514d634dbb2acaf4e914ed) #13, !noalias !1635
  unreachable

panic9.i977:                                      ; preds = %bb14.i972
; call core::panicking::panic_const::panic_const_sub_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_72bac528c0514d634dbb2acaf4e914ed) #13, !noalias !1635
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit989: ; preds = %bb14.i972
  %_31.0.i976 = extractvalue { i32, i1 } %145, 0
  %_49.i = icmp sle i32 %_31.0.i976, -1000000
  %.not297 = icmp eq i64 %d.i50, 0
  %or.cond393 = or i1 %_49.i, %.not297
  br i1 %or.cond393, label %bb35.i, label %bb29.i

bb35.i:                                           ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit223, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit989, %bb16.i65, %bb13.i63, %bb11.i49, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1015
  %_70.i.not = icmp eq i64 %p.sroa.0.5.i3114, 499990
  br i1 %_70.i.not, label %bb63.i, label %bb39.i

bb29.i:                                           ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit989
  br i1 %or.cond.i964, label %bb6.i1038, label %bb7.i1017

bb7.i1017:                                        ; preds = %bb6.i1038, %bb29.i
  %c.sroa.0.0.i1018 = phi i32 [ %147, %bb6.i1038 ], [ 168, %bb29.i ]
  %_17.i1019 = icmp ugt i64 %d.i50, 4
  br i1 %_17.i1019, label %bb12.i1034, label %bb14.i1024

bb6.i1038:                                        ; preds = %bb29.i
  %_11.i1039 = add nsw i32 %_29.i970, -3
  %_10.i1040 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_11.i1039, i1 false)
  %146 = shl nuw nsw i32 %_10.i1040, 4
  %147 = sub nuw nsw i32 632, %146
  br label %bb7.i1017

bb12.i1034:                                       ; preds = %bb7.i1017
  %148 = trunc nuw i64 %d.i50 to i32
  %_22.i1032 = add nsw i32 %148, -1
  %_21.i1035 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_22.i1032, i1 true)
  %149 = shl nuw nsw i32 %_21.i1035, 4
  %reass.sub3166 = sub nsw i32 %c.sroa.0.0.i1018, %149
  %150 = add nsw i32 %reass.sub3166, 480
  br label %bb14.i1024

bb14.i1024:                                       ; preds = %bb7.i1017, %bb12.i1034
  %c.sroa.0.1.i1021 = phi i32 [ %150, %bb12.i1034 ], [ %c.sroa.0.0.i1018, %bb7.i1017 ]
  %151 = tail call { i32, i1 } @llvm.ssub.with.overflow.i32(i32 %_30.0.i973, i32 %c.sroa.0.1.i1021)
  %_31.1.i1026 = extractvalue { i32, i1 } %151, 1
  br i1 %_31.1.i1026, label %panic9.i1029, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1041

panic9.i1029:                                     ; preds = %bb14.i1024
; call core::panicking::panic_const::panic_const_sub_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_72bac528c0514d634dbb2acaf4e914ed) #13
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1041: ; preds = %bb14.i1024
  %_31.0.i1028 = extractvalue { i32, i1 } %151, 0
  %152 = add nsw i64 %l.sroa.0.0.i3116, -11
  %or.cond.i990 = icmp ult i64 %152, 247
  br i1 %or.cond.i990, label %bb6.i1012, label %bb7.i991

bb7.i991:                                         ; preds = %bb6.i1012, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1041
  %c.sroa.0.0.i992 = phi i32 [ %155, %bb6.i1012 ], [ 168, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1041 ]
  %_17.i993 = icmp ugt i64 %d.sroa.0.0.i3115, 4
  br i1 %_17.i993, label %bb8.i1005, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1015

bb6.i1012:                                        ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1041
  %153 = trunc nuw nsw i64 %l.sroa.0.0.i3116 to i32
  %_11.i1013 = add nsw i32 %153, -3
  %_10.i1014 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_11.i1013, i1 false)
  %154 = shl nuw nsw i32 %_10.i1014, 4
  %155 = sub nuw nsw i32 632, %154
  br label %bb7.i991

bb8.i1005:                                        ; preds = %bb7.i991
  %156 = trunc i64 %d.sroa.0.0.i3115 to i32
  %_22.i1006 = add i32 %156, -1
  %_25.1.i1007 = icmp ult i32 %_22.i1006, 2
  br i1 %_25.1.i1007, label %panic5.i1011, label %bb12.i1008

panic5.i1011:                                     ; preds = %bb8.i1005
; call core::panicking::panic_const::panic_const_sub_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_cc8257d2c78dd28d3d4ac89f580613b9) #13
  unreachable

bb12.i1008:                                       ; preds = %bb8.i1005
  %_21.i1009 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_22.i1006, i1 true)
  %157 = shl nuw nsw i32 %_21.i1009, 4
  %reass.sub3167 = sub nsw i32 %c.sroa.0.0.i992, %157
  %158 = add nsw i32 %reass.sub3167, 480
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1015

_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1015: ; preds = %bb12.i1008, %bb7.i991
  %c.sroa.0.1.i995 = phi i32 [ %158, %bb12.i1008 ], [ %c.sroa.0.0.i992, %bb7.i991 ]
  %_29.i996 = trunc nuw nsw i64 %l.sroa.0.0.i3116 to i32
  %_30.0.i999 = shl nuw nsw i32 %_29.i996, 6
  %159 = sub nsw i32 %_30.0.i999, %c.sroa.0.1.i995
  %_62.i = icmp sgt i32 %_31.0.i1028, %159
  br i1 %_62.i, label %bb32.i, label %bb35.i

bb32.i:                                           ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1015
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1647)
  %_9.i = icmp ult i64 %nt.sroa.0.5.i3117, %out.1
  br i1 %_9.i, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit, label %panic1.i

panic1.i:                                         ; preds = %bb32.i
  %nt.sroa.0.5.i3117.lcssa328 = phi i64 [ %nt.sroa.0.5.i3117, %bb32.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %nt.sroa.0.5.i3117.lcssa328, i64 noundef range(i64 0, 2305843009213693952) %out.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_ce72d480401e07b7a290039044612259) #13, !noalias !1650
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit: ; preds = %bb32.i
  %_5.i = load i8, ptr %99, align 1, !alias.scope !1647, !noalias !1652, !noundef !135
  br label %bb59.i

bb39.i:                                           ; preds = %bb35.i
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1653)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1656)
  %_9.i363 = shl nuw nsw i64 %_14.i403, 24
  %_13.i370 = shl nuw nsw i64 %_20.i411, 16
  %_8.i371 = or disjoint i64 %_13.i370, %_9.i363
  %_19.i378 = shl nuw nsw i64 %_25.i419, 8
  %_7.i379 = or disjoint i64 %_8.i371, %_19.i378
  %160 = getelementptr inbounds nuw i8, ptr %99, i64 5
  %_26.i384 = load i8, ptr %160, align 1, !alias.scope !1658, !noalias !1661, !noundef !135
  %_25.i385 = zext i8 %_26.i384 to i64
  %161 = or disjoint i64 %_7.i379, %_25.i385
  %162 = mul i64 %161, -7046029254386353131
  %163 = lshr i64 %162, 48
  %164 = getelementptr inbounds nuw [4 x i8], ptr %head.i, i64 %163
  %old.i176.i = load i32, ptr %164, align 4, !alias.scope !1653, !noalias !1662, !noundef !135
  %_16.i177.i = and i64 %_51.0.i, 32767
  %165 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_16.i177.i
  store i32 %old.i176.i, ptr %165, align 4, !alias.scope !1656, !noalias !1664
  %166 = trunc nuw nsw i64 %_51.0.i to i32
  store i32 %166, ptr %164, align 4, !alias.scope !1653, !noalias !1662
  %_0.i178.i = zext i32 %old.i176.i to i64
  %_80.0.i = add nuw nsw i64 %p.sroa.0.5.i3114, 3
  %_84.0.i = sub nuw nsw i64 499998, %p.sroa.0.5.i3114
  %_81.i = icmp ult i64 %_56.0.i, %_84.0.i
  br i1 %_81.i, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_findKj8000_EB4_.exit, label %bb63.i

_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_findKj8000_EB4_.exit: ; preds = %bb39.i
  %spec.store.select3.i = tail call i64 @llvm.umin.i64(i64 %_84.0.i, i64 258)
  %_19.0.i95 = add nuw nsw i64 %spec.select.i10, %_51.0.i
  %_16.i96 = icmp ult i64 %_19.0.i95, 500000
  br i1 %_16.i96, label %bb7.i154, label %bb11.i107

bb7.i154:                                         ; preds = %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_findKj8000_EB4_.exit
  %167 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_19.0.i95
  %168 = load i8, ptr %167, align 1, !alias.scope !1665, !noalias !1668, !noundef !135
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
  %_36.i124 = load i8, ptr %169, align 1, !alias.scope !1665, !noalias !1668, !noundef !135
  %_35.i125 = icmp eq i8 %_36.i124, %pb.sroa.0.0.i98
  br i1 %_35.i125, label %bb2.i.preheader, label %bb63.i

bb2.i.preheader:                                  ; preds = %bb16.i123
  %170 = and i64 %spec.store.select3.i, 504
  br label %bb2.i

bb2.i:                                            ; preds = %bb2.i.preheader, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit879
  %k.sroa.0.0.i3100 = phi i64 [ %_10.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit879 ], [ 0, %bb2.i.preheader ]
  %_10.0.i = add nuw nsw i64 %k.sroa.0.0.i3100, 8
  %_7.not.i = icmp samesign ugt i64 %_10.0.i, %spec.store.select3.i
  br i1 %_7.not.i, label %bb15.i157, label %bb4.i

bb4.i:                                            ; preds = %bb2.i
  %_13.i167 = add nuw nsw i64 %k.sroa.0.0.i3100, %_0.i178.i
  %171 = icmp samesign ugt i64 %_13.i167, 499992
  br i1 %171, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit947, label %bb2.i884

bb2.i884:                                         ; preds = %bb4.i
  %172 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_13.i167
  %_15.i = load i8, ptr %172, align 1, !alias.scope !1670, !noalias !1668, !noundef !135
  %_14.i888 = zext i8 %_15.i to i64
  %_13.i889 = shl nuw i64 %_14.i888, 56
  %173 = getelementptr inbounds nuw i8, ptr %172, i64 1
  %_19.i894 = load i8, ptr %173, align 1, !alias.scope !1670, !noalias !1668, !noundef !135
  %_18.i895 = zext i8 %_19.i894 to i64
  %_17.i896 = shl nuw nsw i64 %_18.i895, 48
  %_12.i897 = or disjoint i64 %_17.i896, %_13.i889
  %174 = getelementptr inbounds nuw i8, ptr %172, i64 2
  %_25.i902 = load i8, ptr %174, align 1, !alias.scope !1670, !noalias !1668, !noundef !135
  %_24.i903 = zext i8 %_25.i902 to i64
  %_23.i904 = shl nuw nsw i64 %_24.i903, 40
  %_11.i905 = or disjoint i64 %_12.i897, %_23.i904
  %175 = getelementptr inbounds nuw i8, ptr %172, i64 3
  %_31.i910 = load i8, ptr %175, align 1, !alias.scope !1670, !noalias !1668, !noundef !135
  %_30.i911 = zext i8 %_31.i910 to i64
  %_29.i912 = shl nuw nsw i64 %_30.i911, 32
  %_10.i913 = or disjoint i64 %_11.i905, %_29.i912
  %176 = getelementptr inbounds nuw i8, ptr %172, i64 4
  %_37.i918 = load i8, ptr %176, align 1, !alias.scope !1670, !noalias !1668, !noundef !135
  %_36.i919 = zext i8 %_37.i918 to i64
  %_35.i920 = shl nuw nsw i64 %_36.i919, 24
  %_9.i921 = or disjoint i64 %_10.i913, %_35.i920
  %177 = getelementptr inbounds nuw i8, ptr %172, i64 5
  %_43.i926 = load i8, ptr %177, align 1, !alias.scope !1670, !noalias !1668, !noundef !135
  %_42.i927 = zext i8 %_43.i926 to i64
  %_41.i928 = shl nuw nsw i64 %_42.i927, 16
  %_8.i929 = or disjoint i64 %_9.i921, %_41.i928
  %178 = getelementptr inbounds nuw i8, ptr %172, i64 6
  %_49.i934 = load i8, ptr %178, align 1, !alias.scope !1670, !noalias !1668, !noundef !135
  %_48.i935 = zext i8 %_49.i934 to i64
  %_47.i936 = shl nuw nsw i64 %_48.i935, 8
  %_7.i937 = or i64 %_8.i929, %_47.i936
  %179 = getelementptr inbounds nuw i8, ptr %172, i64 7
  %_54.i942 = load i8, ptr %179, align 1, !alias.scope !1670, !noalias !1668, !noundef !135
  %_53.i943 = zext i8 %_54.i942 to i64
  %180 = or i64 %_7.i937, %_53.i943
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit947

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit947: ; preds = %bb4.i, %bb2.i884
  %_0.sroa.0.0.i945 = phi i64 [ %180, %bb2.i884 ], [ 0, %bb4.i ]
  %_16.i168 = add nuw i64 %k.sroa.0.0.i3100, %_51.0.i
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1673)
  %_5.1.i811 = icmp ugt i64 %_16.i168, -9
  br i1 %_5.1.i811, label %panic.i878, label %bb1.i812

bb1.i812:                                         ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit947
  %181 = icmp ugt i64 %_16.i168, 499992
  br i1 %181, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit879, label %bb2.i815

panic.i878:                                       ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit947
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_bb314acf14069c2fbedf530b060ebd60) #13, !noalias !1676
  unreachable

bb2.i815:                                         ; preds = %bb1.i812
  %182 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_16.i168
  %_15.i819 = load i8, ptr %182, align 1, !alias.scope !1673, !noalias !1668, !noundef !135
  %_14.i820 = zext i8 %_15.i819 to i64
  %_13.i821 = shl nuw i64 %_14.i820, 56
  %183 = getelementptr inbounds nuw i8, ptr %182, i64 1
  %_19.i826 = load i8, ptr %183, align 1, !alias.scope !1673, !noalias !1668, !noundef !135
  %_18.i827 = zext i8 %_19.i826 to i64
  %_17.i828 = shl nuw nsw i64 %_18.i827, 48
  %_12.i829 = or disjoint i64 %_17.i828, %_13.i821
  %184 = getelementptr inbounds nuw i8, ptr %182, i64 2
  %_25.i834 = load i8, ptr %184, align 1, !alias.scope !1673, !noalias !1668, !noundef !135
  %_24.i835 = zext i8 %_25.i834 to i64
  %_23.i836 = shl nuw nsw i64 %_24.i835, 40
  %_11.i837 = or disjoint i64 %_12.i829, %_23.i836
  %185 = getelementptr inbounds nuw i8, ptr %182, i64 3
  %_31.i842 = load i8, ptr %185, align 1, !alias.scope !1673, !noalias !1668, !noundef !135
  %_30.i843 = zext i8 %_31.i842 to i64
  %_29.i844 = shl nuw nsw i64 %_30.i843, 32
  %_10.i845 = or disjoint i64 %_11.i837, %_29.i844
  %186 = getelementptr inbounds nuw i8, ptr %182, i64 4
  %_37.i850 = load i8, ptr %186, align 1, !alias.scope !1673, !noalias !1668, !noundef !135
  %_36.i851 = zext i8 %_37.i850 to i64
  %_35.i852 = shl nuw nsw i64 %_36.i851, 24
  %_9.i853 = or disjoint i64 %_10.i845, %_35.i852
  %187 = getelementptr inbounds nuw i8, ptr %182, i64 5
  %_43.i858 = load i8, ptr %187, align 1, !alias.scope !1673, !noalias !1668, !noundef !135
  %_42.i859 = zext i8 %_43.i858 to i64
  %_41.i860 = shl nuw nsw i64 %_42.i859, 16
  %_8.i861 = or disjoint i64 %_9.i853, %_41.i860
  %188 = getelementptr inbounds nuw i8, ptr %182, i64 6
  %_49.i866 = load i8, ptr %188, align 1, !alias.scope !1673, !noalias !1668, !noundef !135
  %_48.i867 = zext i8 %_49.i866 to i64
  %_47.i868 = shl nuw nsw i64 %_48.i867, 8
  %_7.i869 = or i64 %_8.i861, %_47.i868
  %189 = getelementptr inbounds nuw i8, ptr %182, i64 7
  %_54.i874 = load i8, ptr %189, align 1, !alias.scope !1673, !noalias !1668, !noundef !135
  %_53.i875 = zext i8 %_54.i874 to i64
  %190 = or i64 %_7.i869, %_53.i875
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit879

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit879: ; preds = %bb1.i812, %bb2.i815
  %_0.sroa.0.0.i877 = phi i64 [ %190, %bb2.i815 ], [ 0, %bb1.i812 ]
  %191 = icmp eq i64 %_0.sroa.0.0.i945, %_0.sroa.0.0.i877
  br i1 %191, label %bb2.i, label %bb15.i157.thread

bb15.i157:                                        ; preds = %bb2.i
  %_24.i3101.not = icmp eq i64 %170, %spec.store.select3.i
  br i1 %_24.i3101.not, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit, label %bb19.i162

bb15.i157.thread:                                 ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit879
  %_0.sroa.0.0.i877.lcssa = phi i64 [ %_0.sroa.0.0.i877, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit879 ]
  %_0.sroa.0.0.i945.lcssa317 = phi i64 [ %_0.sroa.0.0.i945, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit879 ]
  %k.sroa.0.0.i3100.lcssa316 = phi i64 [ %k.sroa.0.0.i3100, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit879 ]
  %x.i = xor i64 %_0.sroa.0.0.i877.lcssa, %_0.sroa.0.0.i945.lcssa317
  %192 = tail call range(i64 0, 65) i64 @llvm.ctlz.i64(i64 %x.i, i1 true)
  %_2018.i = lshr i64 %192, 3
  %_22.0.i = or disjoint i64 %_2018.i, %k.sroa.0.0.i3100.lcssa316
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit

bb19.i162:                                        ; preds = %bb15.i157, %bb22.i
  %k.sroa.0.2.i3103 = phi i64 [ %k.sroa.0.3.i, %bb22.i ], [ %170, %bb15.i157 ]
  %_30.0.i = add nuw nsw i64 %k.sroa.0.2.i3103, %_0.i178.i
  %_32.i = icmp samesign ult i64 %_30.0.i, 500000
  br i1 %_32.i, label %bb21.i164, label %panic4.i163

panic4.i163:                                      ; preds = %bb19.i162
  %_30.0.i.lcssa = phi i64 [ %_30.0.i, %bb19.i162 ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_30.0.i.lcssa, i64 noundef range(i64 0, -9223372036854775808) 500000, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_333f7815cbdde125b13aaef2eac5916c) #13, !noalias !1668
  unreachable

bb21.i164:                                        ; preds = %bb19.i162
  %_36.0.i = add nuw nsw i64 %k.sroa.0.2.i3103, %_51.0.i
  %_37.i = icmp ult i64 %_36.0.i, 500000
  br i1 %_37.i, label %bb22.i, label %panic6.i

bb22.i:                                           ; preds = %bb21.i164
  %193 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_30.0.i
  %_27.i = load i8, ptr %193, align 1, !alias.scope !1677, !noalias !1668, !noundef !135
  %194 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_36.0.i
  %_33.i = load i8, ptr %194, align 1, !alias.scope !1677, !noalias !1668, !noundef !135
  %_26.i = icmp eq i8 %_27.i, %_33.i
  %_38.0.i = zext i1 %_26.i to i64
  %k.sroa.0.3.i = add nuw nsw i64 %k.sroa.0.2.i3103, %_38.0.i
  %_24.i = icmp samesign ult i64 %k.sroa.0.3.i, %spec.store.select3.i
  %or.cond.i159 = select i1 %_26.i, i1 %_24.i, i1 false
  br i1 %or.cond.i159, label %bb19.i162, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit

panic6.i:                                         ; preds = %bb21.i164
  %_36.0.i.lcssa = phi i64 [ %_36.0.i, %bb21.i164 ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_36.0.i.lcssa, i64 noundef range(i64 0, -9223372036854775808) 500000, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_c7b835eab7e4664f8dc21896c854bf2b) #13, !noalias !1668
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit: ; preds = %bb22.i, %bb15.i157.thread, %bb15.i157
  %k.sroa.0.2.i.lcssa = phi i64 [ %170, %bb15.i157 ], [ %_22.0.i, %bb15.i157.thread ], [ %k.sroa.0.3.i, %bb22.i ]
  %_46.i140 = icmp ugt i64 %k.sroa.0.2.i.lcssa, %spec.select.i10
  br i1 %_46.i140, label %bb19.i141, label %bb63.i

bb19.i141:                                        ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit
  %195 = add i64 %k.sroa.0.2.i.lcssa, -11
  %or.cond.i948 = icmp ult i64 %195, 247
  br i1 %or.cond.i948, label %bb6.i, label %bb7.i949

bb7.i949:                                         ; preds = %bb6.i, %bb19.i141
  %c.sroa.0.0.i = phi i32 [ %198, %bb6.i ], [ 168, %bb19.i141 ]
  %_17.i950 = icmp ugt i64 %d.i108, 4
  br i1 %_17.i950, label %bb12.i959, label %bb13.i951

bb6.i:                                            ; preds = %bb19.i141
  %196 = trunc nuw nsw i64 %k.sroa.0.2.i.lcssa to i32
  %_11.i962 = add nsw i32 %196, -3
  %_10.i963 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_11.i962, i1 false)
  %197 = shl nuw nsw i32 %_10.i963, 4
  %198 = sub nuw nsw i32 632, %197
  br label %bb7.i949

bb13.i951:                                        ; preds = %bb12.i959, %bb7.i949
  %c.sroa.0.1.i = phi i32 [ %202, %bb12.i959 ], [ %c.sroa.0.0.i, %bb7.i949 ]
  %_29.i952 = trunc i64 %k.sroa.0.2.i.lcssa to i32
  %199 = add i32 %_29.i952, -33554432
  %_30.1.i953 = icmp ult i32 %199, -67108864
  br i1 %_30.1.i953, label %panic8.i, label %bb14.i

bb12.i959:                                        ; preds = %bb7.i949
  %200 = trunc nuw i64 %d.i108 to i32
  %_22.i958 = add nsw i32 %200, -1
  %_21.i960 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_22.i958, i1 true)
  %201 = shl nuw nsw i32 %_21.i960, 4
  %reass.sub3168 = sub nsw i32 %c.sroa.0.0.i, %201
  %202 = add nsw i32 %reass.sub3168, 480
  br label %bb13.i951

bb14.i:                                           ; preds = %bb13.i951
  %_30.0.i954 = shl nsw i32 %_29.i952, 6
  %203 = tail call { i32, i1 } @llvm.ssub.with.overflow.i32(i32 %_30.0.i954, i32 %c.sroa.0.1.i)
  %_31.1.i = extractvalue { i32, i1 } %203, 1
  br i1 %_31.1.i, label %panic9.i956, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit155

panic8.i:                                         ; preds = %bb13.i951
; call core::panicking::panic_const::panic_const_mul_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_mul_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_72bac528c0514d634dbb2acaf4e914ed) #13, !noalias !1668
  unreachable

panic9.i956:                                      ; preds = %bb14.i
; call core::panicking::panic_const::panic_const_sub_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_72bac528c0514d634dbb2acaf4e914ed) #13, !noalias !1668
  unreachable

_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit155: ; preds = %bb14.i
  %_31.0.i = extractvalue { i32, i1 } %203, 0
  %_49.i143 = icmp sgt i32 %_31.0.i, -1000000
  %spec.select = select i1 %_49.i143, i64 %d.i108, i64 0
  %spec.select3586 = select i1 %_49.i143, i64 %k.sroa.0.2.i.lcssa, i64 %spec.select.i10
  %204 = freeze i64 %spec.select
  %205 = icmp ne i64 %204, 0
  %_87.i = icmp ugt i64 %spec.select3586, 3
  %or.cond3582 = and i1 %205, %_87.i
  br i1 %or.cond3582, label %bb45.i, label %bb63.i

bb45.i:                                           ; preds = %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit155
  %206 = add i64 %spec.select3586, -11
  %or.cond.i1068 = icmp ult i64 %206, 247
  br i1 %or.cond.i1068, label %bb6.i1090, label %bb7.i1069

bb7.i1069:                                        ; preds = %bb6.i1090, %bb45.i
  %c.sroa.0.0.i1070 = phi i32 [ %209, %bb6.i1090 ], [ 168, %bb45.i ]
  %_17.i1071 = icmp ugt i64 %204, 4
  br i1 %_17.i1071, label %bb12.i1086, label %bb13.i1072

bb6.i1090:                                        ; preds = %bb45.i
  %207 = trunc nuw nsw i64 %spec.select3586 to i32
  %_11.i1091 = add nsw i32 %207, -3
  %_10.i1092 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_11.i1091, i1 false)
  %208 = shl nuw nsw i32 %_10.i1092, 4
  %209 = sub nuw nsw i32 632, %208
  br label %bb7.i1069

bb13.i1072:                                       ; preds = %bb12.i1086, %bb7.i1069
  %c.sroa.0.1.i1073 = phi i32 [ %213, %bb12.i1086 ], [ %c.sroa.0.0.i1070, %bb7.i1069 ]
  %_29.i1074 = trunc i64 %spec.select3586 to i32
  %210 = add i32 %_29.i1074, -33554432
  %_30.1.i1075 = icmp ult i32 %210, -67108864
  br i1 %_30.1.i1075, label %panic8.i1082, label %bb14.i1076

bb12.i1086:                                       ; preds = %bb7.i1069
  %211 = trunc nuw i64 %204 to i32
  %_22.i1084 = add nsw i32 %211, -1
  %_21.i1087 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_22.i1084, i1 true)
  %212 = shl nuw nsw i32 %_21.i1087, 4
  %reass.sub3169 = sub nsw i32 %c.sroa.0.0.i1070, %212
  %213 = add nsw i32 %reass.sub3169, 480
  br label %bb13.i1072

bb14.i1076:                                       ; preds = %bb13.i1072
  %_30.0.i1077 = shl nsw i32 %_29.i1074, 6
  %214 = tail call { i32, i1 } @llvm.ssub.with.overflow.i32(i32 %_30.0.i1077, i32 %c.sroa.0.1.i1073)
  %_31.1.i1078 = extractvalue { i32, i1 } %214, 1
  br i1 %_31.1.i1078, label %panic9.i1081, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1093

panic8.i1082:                                     ; preds = %bb13.i1072
; call core::panicking::panic_const::panic_const_mul_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_mul_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_72bac528c0514d634dbb2acaf4e914ed) #13
  unreachable

panic9.i1081:                                     ; preds = %bb14.i1076
; call core::panicking::panic_const::panic_const_sub_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_72bac528c0514d634dbb2acaf4e914ed) #13
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1093: ; preds = %bb14.i1076
  %_31.0.i1080 = extractvalue { i32, i1 } %214, 0
  %215 = add nsw i64 %l.sroa.0.0.i3116, -11
  %or.cond.i1042 = icmp ult i64 %215, 247
  br i1 %or.cond.i1042, label %bb6.i1064, label %bb7.i1043

bb7.i1043:                                        ; preds = %bb6.i1064, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1093
  %c.sroa.0.0.i1044 = phi i32 [ %218, %bb6.i1064 ], [ 168, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1093 ]
  %_17.i1045 = icmp ugt i64 %d.sroa.0.0.i3115, 4
  br i1 %_17.i1045, label %bb8.i1057, label %bb48.i

bb6.i1064:                                        ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit1093
  %216 = trunc nuw nsw i64 %l.sroa.0.0.i3116 to i32
  %_11.i1065 = add nsw i32 %216, -3
  %_10.i1066 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_11.i1065, i1 false)
  %217 = shl nuw nsw i32 %_10.i1066, 4
  %218 = sub nuw nsw i32 632, %217
  br label %bb7.i1043

bb8.i1057:                                        ; preds = %bb7.i1043
  %219 = trunc i64 %d.sroa.0.0.i3115 to i32
  %_22.i1058 = add i32 %219, -1
  %_25.1.i1059 = icmp ult i32 %_22.i1058, 2
  br i1 %_25.1.i1059, label %panic5.i1063, label %bb12.i1060

panic5.i1063:                                     ; preds = %bb8.i1057
; call core::panicking::panic_const::panic_const_sub_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_cc8257d2c78dd28d3d4ac89f580613b9) #13
  unreachable

bb12.i1060:                                       ; preds = %bb8.i1057
  %_21.i1061 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_22.i1058, i1 true)
  %220 = shl nuw nsw i32 %_21.i1061, 4
  %reass.sub3170 = sub nsw i32 %c.sroa.0.0.i1044, %220
  %221 = add nsw i32 %reass.sub3170, 480
  br label %bb48.i

bb48.i:                                           ; preds = %bb7.i1043, %bb12.i1060
  %c.sroa.0.1.i1047 = phi i32 [ %221, %bb12.i1060 ], [ %c.sroa.0.0.i1044, %bb7.i1043 ]
  %_29.i1048 = trunc nuw nsw i64 %l.sroa.0.0.i3116 to i32
  %_30.0.i1051 = shl nuw nsw i32 %_29.i1048, 6
  %222 = or disjoint i32 %_30.0.i1051, 40
  %223 = sub nsw i32 %222, %c.sroa.0.1.i1047
  %_89.i = icmp sgt i32 %_31.0.i1080, %223
  br i1 %_89.i, label %bb49.i, label %bb63.i

bb49.i:                                           ; preds = %bb48.i
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1680)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1683)
  %_9.i292 = icmp ult i64 %nt.sroa.0.5.i3117, %out.1
  br i1 %_9.i292, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit297, label %panic1.i293

panic1.i293:                                      ; preds = %bb49.i
  %nt.sroa.0.5.i3117.lcssa337 = phi i64 [ %nt.sroa.0.5.i3117, %bb49.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %nt.sroa.0.5.i3117.lcssa337, i64 noundef range(i64 0, 2305843009213693952) %out.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_ce72d480401e07b7a290039044612259) #13, !noalias !1685
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit297: ; preds = %bb49.i
  %_5.i295 = load i8, ptr %99, align 1, !alias.scope !1680, !noalias !1683, !noundef !135
  %224 = getelementptr inbounds nuw [4 x i8], ptr %out.0, i64 %nt.sroa.0.5.i3117
  %225 = zext i8 %_5.i295 to i32
  store i32 %225, ptr %224, align 4, !alias.scope !1683, !noalias !1680
  %_10.0.i296 = add nuw nsw i64 %nt.sroa.0.5.i3117, 1
  %_9.i283 = icmp ult i64 %_10.0.i296, %out.1
  br i1 %_9.i283, label %bb59.i, label %panic1.i284

panic1.i284:                                      ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit297
  %_10.0.i296.lcssa = phi i64 [ %_10.0.i296, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit297 ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_10.0.i296.lcssa, i64 noundef range(i64 0, 2305843009213693952) %out.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_ce72d480401e07b7a290039044612259) #13, !noalias !1686
  unreachable

bb59.i:                                           ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit297, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit
  %_10.0.i296.sink = phi i64 [ %nt.sroa.0.5.i3117, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit ], [ %_10.0.i296, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit297 ]
  %_11.i395.sink = phi i8 [ %_5.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit ], [ %_11.i395, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit297 ]
  %.sink = phi i64 [ 1, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit ], [ 2, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit297 ]
  %ins.sroa.0.5.i = phi i64 [ %_51.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit ], [ %_80.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit297 ]
  %p.sroa.0.6.i = phi i64 [ %_44.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit ], [ %_51.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit297 ]
  %d.sroa.0.1.i = phi i64 [ %d.i50, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit ], [ %204, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit297 ]
  %l.sroa.0.1.i = phi i64 [ %k.sroa.0.2.i178.lcssa, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit ], [ %spec.select3586, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit297 ]
  %226 = getelementptr inbounds nuw [4 x i8], ptr %out.0, i64 %_10.0.i296.sink
  %227 = zext i8 %_11.i395.sink to i32
  store i32 %227, ptr %226, align 4, !noalias !135
  %_10.0.i287 = add nuw nsw i64 %nt.sroa.0.5.i3117, %.sink
  %_39.i = icmp ult i64 %l.sroa.0.1.i, 32
  br i1 %_39.i, label %bb18.i, label %bb63.i

bb116.i:                                          ; preds = %bb110.i, %bb63.i
  %p.sroa.0.7.i.lcssa = phi i64 [ %p.sroa.0.5.i.lcssa, %bb63.i ], [ %p.sroa.0.8.i, %bb110.i ]
  %l.sroa.0.2.i.lcssa = phi i64 [ %l.sroa.0.0.i.lcssa, %bb63.i ], [ %l.sroa.0.3.i, %bb110.i ]
  %nt.sroa.0.7.i.lcssa = phi i64 [ %nt.sroa.0.5.i.lcssa, %bb63.i ], [ %nt.sroa.0.8.i, %bb110.i ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1690)
  %_15.i325 = icmp samesign ult i64 %nt.sroa.0.7.i.lcssa, %out.1
  br i1 %_15.i325, label %bb1.i327, label %panic.i326

bb1.i327:                                         ; preds = %bb116.i
  %228 = trunc i64 %l.sroa.0.2.i.lcssa to i32
  %229 = trunc i64 %d.sroa.0.0.i.lcssa to i32
  %_10.i = shl i32 %229, 8
  %_12.i328 = add i32 %_10.i, 16776957
  %_7.i329 = add i32 %_12.i328, %228
  %230 = getelementptr inbounds nuw [4 x i8], ptr %out.0, i64 %nt.sroa.0.7.i.lcssa
  store i32 %_7.i329, ptr %230, align 4, !alias.scope !1690
  %_19.0.i330 = add i64 %l.sroa.0.2.i.lcssa, %p.sroa.0.7.i.lcssa
  %_19.1.i = icmp ult i64 %_19.0.i330, %p.sroa.0.7.i.lcssa
  br i1 %_19.1.i, label %panic2.i332, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse14u118_put_match.exit

panic.i326:                                       ; preds = %bb116.i
  %nt.sroa.0.7.i.lcssa.lcssa = phi i64 [ %nt.sroa.0.7.i.lcssa, %bb116.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef range(i64 0, 2305843009213693952) %nt.sroa.0.7.i.lcssa.lcssa, i64 noundef range(i64 0, 2305843009213693952) %out.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_950cb3d32dbfbf973f57d9a20abe6695) #13, !noalias !1690
  unreachable

panic2.i332:                                      ; preds = %bb1.i327
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_dc5ae93321079a7792fc0613ca37a43e) #13, !noalias !1690
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse14u118_put_match.exit: ; preds = %bb1.i327
  %_17.0.i = add nuw nsw i64 %nt.sroa.0.7.i.lcssa, 1
  %_175.i = add nuw i64 %ins.sroa.0.4.i.lcssa, 16
  %spec.select148.i = tail call i64 @llvm.umin.i64(i64 %_19.0.i330, i64 %_175.i)
  %spec.store.select50.i = tail call i64 @llvm.umin.i64(i64 %spec.select148.i, i64 499992)
  %_181.i3143 = icmp ult i64 %ins.sroa.0.4.i.lcssa, %spec.store.select50.i
  br i1 %_181.i3143, label %bb125.i, label %bb129.i

bb125.i:                                          ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse14u118_put_match.exit, %bb125.i
  %ins.sroa.0.6.i3144 = phi i64 [ %_188.0.i, %bb125.i ], [ %ins.sroa.0.4.i.lcssa, %_RNvNtCs2hd9JHJjR4I_9candidate5parse14u118_put_match.exit ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1693)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1696)
  %231 = getelementptr inbounds nuw i8, ptr %input.0, i64 %ins.sroa.0.6.i3144
  %232 = load i32, ptr %231, align 1
  %233 = call i32 @llvm.bswap.i32(i32 %232)
  %234 = zext i32 %233 to i64
  %235 = mul i64 %234, -7046029254386353131
  %236 = lshr i64 %235, 48
  %237 = getelementptr inbounds nuw [4 x i8], ptr %head.i, i64 %236
  %old.i155.i = load i32, ptr %237, align 4, !alias.scope !1693, !noalias !1698, !noundef !135
  %_16.i156.i = and i64 %ins.sroa.0.6.i3144, 32767
  %238 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_16.i156.i
  store i32 %old.i155.i, ptr %238, align 4, !alias.scope !1696, !noalias !1700
  %239 = trunc i64 %ins.sroa.0.6.i3144 to i32
  store i32 %239, ptr %237, align 4, !alias.scope !1693, !noalias !1698
  %_188.0.i = add nuw i64 %ins.sroa.0.6.i3144, 1
  %exitcond3346.not = icmp eq i64 %_188.0.i, %spec.store.select50.i
  br i1 %exitcond3346.not, label %bb129.i, label %bb125.i

bb129.i:                                          ; preds = %bb125.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse14u118_put_match.exit
  %ins.sroa.0.6.i.lcssa = phi i64 [ %ins.sroa.0.4.i.lcssa, %_RNvNtCs2hd9JHJjR4I_9candidate5parse14u118_put_match.exit ], [ %spec.store.select50.i, %bb125.i ]
  %e2.i = tail call i64 @llvm.usub.sat.i64(i64 %_19.0.i330, i64 8)
  %invariant.umin = tail call i64 @llvm.umin.i64(i64 %e2.i, i64 499992)
  %or.cond51.i3146 = icmp ult i64 %ins.sroa.0.6.i.lcssa, %invariant.umin
  br i1 %or.cond51.i3146, label %bb132.i, label %bb138.i

bb132.i:                                          ; preds = %bb129.i, %bb132.i
  %ins.sroa.0.7.i3147 = phi i64 [ %_5.0.i457, %bb132.i ], [ %ins.sroa.0.6.i.lcssa, %bb129.i ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1701)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1704)
  %_5.0.i457 = add nuw nsw i64 %ins.sroa.0.7.i3147, 4
  %240 = getelementptr inbounds nuw i8, ptr %input.0, i64 %ins.sroa.0.7.i3147
  %241 = load i32, ptr %240, align 1
  %242 = call i32 @llvm.bswap.i32(i32 %241)
  %243 = zext i32 %242 to i64
  %244 = mul i64 %243, -7046029254386353131
  %245 = lshr i64 %244, 48
  %246 = getelementptr inbounds nuw [4 x i8], ptr %head.i, i64 %245
  %old.i162.i = load i32, ptr %246, align 4, !alias.scope !1701, !noalias !1706, !noundef !135
  %_16.i163.i = and i64 %ins.sroa.0.7.i3147, 32767
  %247 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_16.i163.i
  store i32 %old.i162.i, ptr %247, align 4, !alias.scope !1704, !noalias !1708
  %248 = trunc i64 %ins.sroa.0.7.i3147 to i32
  store i32 %248, ptr %246, align 4, !alias.scope !1701, !noalias !1706
  %or.cond51.i = icmp ult i64 %_5.0.i457, %invariant.umin
  br i1 %or.cond51.i, label %bb132.i, label %bb138.i

bb138.i:                                          ; preds = %bb132.i, %bb129.i
  %ins.sroa.0.7.i.lcssa = phi i64 [ %ins.sroa.0.6.i.lcssa, %bb129.i ], [ %_5.0.i457, %bb132.i ]
  %_202.i = add i64 %ins.sroa.0.7.i.lcssa, 4
  %_201.i = icmp ult i64 %_202.i, %_19.0.i330
  br i1 %_201.i, label %bb139.i, label %bb142.i

bb139.i:                                          ; preds = %bb138.i
  %_204.1.i = icmp ult i64 %_19.0.i330, 4
  br i1 %_204.1.i, label %panic18.i, label %bb140.i

bb142.i:                                          ; preds = %bb140.i, %bb138.i
  %ins.sroa.0.8.i = phi i64 [ %_204.0.i, %bb140.i ], [ %ins.sroa.0.7.i.lcssa, %bb138.i ]
  %invariant.umin3149 = tail call i64 @llvm.umin.i64(i64 %_19.0.i330, i64 499992)
  %or.cond52.i3150 = icmp ult i64 %ins.sroa.0.8.i, %invariant.umin3149
  br i1 %or.cond52.i3150, label %bb145.i, label %bb150.i

bb140.i:                                          ; preds = %bb139.i
  %_204.0.i = add i64 %_19.0.i330, -4
  br label %bb142.i

panic18.i:                                        ; preds = %bb139.i
; call core::panicking::panic_const::panic_const_sub_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_30e260b757f13d4a959ad3a108dff26e) #13
  unreachable

bb150.i:                                          ; preds = %bb145.i, %bb142.i
  %ins.sroa.0.9.i.lcssa = phi i64 [ %ins.sroa.0.8.i, %bb142.i ], [ %_213.0.i, %bb145.i ]
  %spec.select150.i = tail call i64 @llvm.umax.i64(i64 %ins.sroa.0.9.i.lcssa, i64 %_19.0.i330)
  br label %bb174.i

bb145.i:                                          ; preds = %bb142.i, %bb145.i
  %ins.sroa.0.9.i3151 = phi i64 [ %_213.0.i, %bb145.i ], [ %ins.sroa.0.8.i, %bb142.i ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1709)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1712)
  %249 = getelementptr inbounds nuw i8, ptr %input.0, i64 %ins.sroa.0.9.i3151
  %250 = load i32, ptr %249, align 1
  %251 = call i32 @llvm.bswap.i32(i32 %250)
  %252 = zext i32 %251 to i64
  %253 = mul i64 %252, -7046029254386353131
  %254 = lshr i64 %253, 48
  %255 = getelementptr inbounds nuw [4 x i8], ptr %head.i, i64 %254
  %old.i169.i = load i32, ptr %255, align 4, !alias.scope !1709, !noalias !1714, !noundef !135
  %_16.i170.i = and i64 %ins.sroa.0.9.i3151, 32767
  %256 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_16.i170.i
  store i32 %old.i169.i, ptr %256, align 4, !alias.scope !1712, !noalias !1716
  %257 = trunc i64 %ins.sroa.0.9.i3151 to i32
  store i32 %257, ptr %255, align 4, !alias.scope !1709, !noalias !1714
  %_213.0.i = add nuw nsw i64 %ins.sroa.0.9.i3151, 1
  %or.cond52.i = icmp ult i64 %_213.0.i, %invariant.umin3149
  br i1 %or.cond52.i, label %bb145.i, label %bb150.i

bb71.i:                                           ; preds = %bb63.i, %bb110.i
  %258 = phi i64 [ %306, %bb110.i ], [ %96, %bb63.i ]
  %nt.sroa.0.7.i3139 = phi i64 [ %nt.sroa.0.8.i, %bb110.i ], [ %nt.sroa.0.5.i.lcssa, %bb63.i ]
  %l.sroa.0.2.i3138 = phi i64 [ %l.sroa.0.3.i, %bb110.i ], [ %l.sroa.0.0.i.lcssa, %bb63.i ]
  %back.sroa.0.0.i3137 = phi i64 [ %back.sroa.0.1.i, %bb110.i ], [ 0, %bb63.i ]
  %p.sroa.0.7.i3136 = phi i64 [ %p.sroa.0.8.i, %bb110.i ], [ %p.sroa.0.5.i.lcssa, %bb63.i ]
  %259 = getelementptr inbounds nuw [4 x i8], ptr %out.0, i64 %258
  %t.i = load i32, ptr %259, align 4, !alias.scope !1560, !noalias !1557, !noundef !135
  %_120.i = icmp ult i32 %t.i, 256
  br i1 %_120.i, label %bb72.i, label %bb84.i

bb84.i:                                           ; preds = %bb71.i
  %_139.i = icmp ugt i32 %t.i, 16777215
  br i1 %_139.i, label %bb87.i, label %bb110.i

bb72.i:                                           ; preds = %bb71.i
  %_125.0.i = add i64 %p.sroa.0.7.i3136, -1
  %_126.i = icmp ult i64 %_125.0.i, 500000
  br i1 %_126.i, label %bb74.i, label %panic25.i

bb74.i:                                           ; preds = %bb72.i
  %_133.0.i = sub i64 %_125.0.i, %d.sroa.0.0.i.lcssa
  %_134.i = icmp ult i64 %_133.0.i, 500000
  br i1 %_134.i, label %bb77.i, label %panic28.i

panic25.i:                                        ; preds = %bb72.i
  %_125.0.i.lcssa = phi i64 [ %_125.0.i, %bb72.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_125.0.i.lcssa, i64 noundef range(i64 0, -9223372036854775808) 500000, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_1f28cc27fa9e18e58cef417bee4fd90b) #13
  unreachable

bb77.i:                                           ; preds = %bb74.i
  %260 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_125.0.i
  %_122.i = load i8, ptr %260, align 1, !alias.scope !1557, !noalias !1560, !noundef !135
  %261 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_133.0.i
  %_127.i = load i8, ptr %261, align 1, !alias.scope !1557, !noalias !1560, !noundef !135
  %_121.i = icmp eq i8 %_122.i, %_127.i
  br i1 %_121.i, label %bb80.i, label %bb110.i

panic28.i:                                        ; preds = %bb74.i
  %_133.0.i.lcssa = phi i64 [ %_133.0.i, %bb74.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_133.0.i.lcssa, i64 noundef range(i64 0, -9223372036854775808) 500000, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_a470f1791914be2ed9860c28a94823b8) #13
  unreachable

bb87.i:                                           ; preds = %bb84.i
  %_142.i = and i32 %t.i, 255
  %_145.0.i = add nuw nsw i32 %_142.i, 3
  %w.i = zext nneg i32 %_145.0.i to i64
  %_149.0.i = add nuw nsw i64 %l.sroa.0.2.i3138, %w.i
  %_146.i = icmp samesign ult i64 %_149.0.i, 259
  %_150.i = icmp uge i64 %p.sroa.0.7.i3136, %w.i
  %or.cond53.i = select i1 %_146.i, i1 %_150.i, i1 false
  br i1 %or.cond53.i, label %bb90.i, label %bb110.i

bb90.i:                                           ; preds = %bb87.i
  %_156.0.i = sub nuw i64 %p.sroa.0.7.i3136, %w.i
  %_152.not.i = icmp ugt i64 %d.sroa.0.0.i.lcssa, %_156.0.i
  br i1 %_152.not.i, label %bb110.i, label %bb95.i

bb95.i:                                           ; preds = %bb90.i
  %_163.0.i = sub nuw i64 %_156.0.i, %d.sroa.0.0.i.lcssa
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1717)
  %262 = and i64 %w.i, 504
  br label %bb2.i1135

bb2.i1135:                                        ; preds = %bb95.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i
  %k.sroa.0.0.i10953128 = phi i64 [ 0, %bb95.i ], [ %_11.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i ]
  %_11.0.i = add nuw nsw i64 %k.sroa.0.0.i10953128, 8
  %_8.not.i = icmp samesign ugt i64 %_11.0.i, %w.i
  br i1 %_8.not.i, label %bb15.i1096, label %bb4.i1137

bb4.i1137:                                        ; preds = %bb2.i1135
  %_16.0.i = add nuw i64 %k.sroa.0.0.i10953128, %_163.0.i
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1720)
  %_5.1.i172.i = icmp ugt i64 %_16.0.i, -9
  br i1 %_5.1.i172.i, label %panic.i238.i, label %bb1.i173.i

bb15.i1096:                                       ; preds = %bb2.i1135
  %_23.i1097.not = icmp eq i64 %262, %w.i
  br i1 %_23.i1097.not, label %bb101.i, label %bb18.i1099

bb1.i173.i:                                       ; preds = %bb4.i1137
  %263 = icmp ugt i64 %_16.0.i, 499992
  br i1 %263, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit239.i, label %bb2.i176.i

panic.i238.i:                                     ; preds = %bb4.i1137
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_bb314acf14069c2fbedf530b060ebd60) #13, !noalias !1723
  unreachable

bb2.i176.i:                                       ; preds = %bb1.i173.i
  %264 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_16.0.i
  %_15.i180.i = load i8, ptr %264, align 1, !alias.scope !1723, !noundef !135
  %_14.i181.i = zext i8 %_15.i180.i to i64
  %_13.i182.i = shl nuw i64 %_14.i181.i, 56
  %265 = getelementptr inbounds nuw i8, ptr %264, i64 1
  %_19.i187.i = load i8, ptr %265, align 1, !alias.scope !1723, !noundef !135
  %_18.i188.i = zext i8 %_19.i187.i to i64
  %_17.i189.i = shl nuw nsw i64 %_18.i188.i, 48
  %_12.i190.i = or disjoint i64 %_17.i189.i, %_13.i182.i
  %266 = getelementptr inbounds nuw i8, ptr %264, i64 2
  %_25.i195.i = load i8, ptr %266, align 1, !alias.scope !1723, !noundef !135
  %_24.i196.i = zext i8 %_25.i195.i to i64
  %_23.i197.i = shl nuw nsw i64 %_24.i196.i, 40
  %_11.i198.i = or disjoint i64 %_12.i190.i, %_23.i197.i
  %267 = getelementptr inbounds nuw i8, ptr %264, i64 3
  %_31.i203.i = load i8, ptr %267, align 1, !alias.scope !1723, !noundef !135
  %_30.i204.i = zext i8 %_31.i203.i to i64
  %_29.i205.i = shl nuw nsw i64 %_30.i204.i, 32
  %_10.i206.i = or disjoint i64 %_11.i198.i, %_29.i205.i
  %268 = getelementptr inbounds nuw i8, ptr %264, i64 4
  %_37.i211.i = load i8, ptr %268, align 1, !alias.scope !1723, !noundef !135
  %_36.i212.i = zext i8 %_37.i211.i to i64
  %_35.i213.i = shl nuw nsw i64 %_36.i212.i, 24
  %_9.i214.i = or disjoint i64 %_10.i206.i, %_35.i213.i
  %269 = getelementptr inbounds nuw i8, ptr %264, i64 5
  %_43.i219.i = load i8, ptr %269, align 1, !alias.scope !1723, !noundef !135
  %_42.i220.i = zext i8 %_43.i219.i to i64
  %_41.i221.i = shl nuw nsw i64 %_42.i220.i, 16
  %_8.i222.i = or disjoint i64 %_9.i214.i, %_41.i221.i
  %270 = getelementptr inbounds nuw i8, ptr %264, i64 6
  %_49.i227.i = load i8, ptr %270, align 1, !alias.scope !1723, !noundef !135
  %_48.i228.i = zext i8 %_49.i227.i to i64
  %_47.i229.i = shl nuw nsw i64 %_48.i228.i, 8
  %_7.i230.i = or i64 %_8.i222.i, %_47.i229.i
  %271 = getelementptr inbounds nuw i8, ptr %264, i64 7
  %_54.i235.i = load i8, ptr %271, align 1, !alias.scope !1723, !noundef !135
  %_53.i236.i = zext i8 %_54.i235.i to i64
  %272 = or i64 %_7.i230.i, %_53.i236.i
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit239.i

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit239.i: ; preds = %bb2.i176.i, %bb1.i173.i
  %_0.sroa.0.0.i237.i = phi i64 [ %272, %bb2.i176.i ], [ 0, %bb1.i173.i ]
  %_20.0.i = add nuw i64 %k.sroa.0.0.i10953128, %_156.0.i
  tail call void @llvm.experimental.noalias.scope.decl(metadata !1724)
  %_5.1.i104.i = icmp ugt i64 %_20.0.i, -9
  br i1 %_5.1.i104.i, label %panic.i170.i, label %bb1.i105.i

bb1.i105.i:                                       ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit239.i
  %_3.not.i107.i = icmp ugt i64 %_20.0.i, 499992
  br i1 %_3.not.i107.i, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i, label %bb2.i108.i

panic.i170.i:                                     ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit239.i
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_bb314acf14069c2fbedf530b060ebd60) #13, !noalias !1727
  unreachable

bb2.i108.i:                                       ; preds = %bb1.i105.i
  %273 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_20.0.i
  %_15.i112.i = load i8, ptr %273, align 1, !alias.scope !1727, !noundef !135
  %_14.i113.i = zext i8 %_15.i112.i to i64
  %_13.i114.i = shl nuw i64 %_14.i113.i, 56
  %274 = getelementptr inbounds nuw i8, ptr %273, i64 1
  %_19.i119.i = load i8, ptr %274, align 1, !alias.scope !1727, !noundef !135
  %_18.i120.i = zext i8 %_19.i119.i to i64
  %_17.i121.i = shl nuw nsw i64 %_18.i120.i, 48
  %_12.i122.i = or disjoint i64 %_17.i121.i, %_13.i114.i
  %275 = getelementptr inbounds nuw i8, ptr %273, i64 2
  %_25.i127.i = load i8, ptr %275, align 1, !alias.scope !1727, !noundef !135
  %_24.i128.i = zext i8 %_25.i127.i to i64
  %_23.i129.i = shl nuw nsw i64 %_24.i128.i, 40
  %_11.i130.i = or disjoint i64 %_12.i122.i, %_23.i129.i
  %276 = getelementptr inbounds nuw i8, ptr %273, i64 3
  %_31.i135.i = load i8, ptr %276, align 1, !alias.scope !1727, !noundef !135
  %_30.i136.i = zext i8 %_31.i135.i to i64
  %_29.i137.i = shl nuw nsw i64 %_30.i136.i, 32
  %_10.i138.i = or disjoint i64 %_11.i130.i, %_29.i137.i
  %277 = getelementptr inbounds nuw i8, ptr %273, i64 4
  %_37.i143.i = load i8, ptr %277, align 1, !alias.scope !1727, !noundef !135
  %_36.i144.i = zext i8 %_37.i143.i to i64
  %_35.i145.i = shl nuw nsw i64 %_36.i144.i, 24
  %_9.i146.i = or disjoint i64 %_10.i138.i, %_35.i145.i
  %278 = getelementptr inbounds nuw i8, ptr %273, i64 5
  %_43.i151.i = load i8, ptr %278, align 1, !alias.scope !1727, !noundef !135
  %_42.i152.i = zext i8 %_43.i151.i to i64
  %_41.i153.i = shl nuw nsw i64 %_42.i152.i, 16
  %_8.i154.i = or disjoint i64 %_9.i146.i, %_41.i153.i
  %279 = getelementptr inbounds nuw i8, ptr %273, i64 6
  %_49.i159.i = load i8, ptr %279, align 1, !alias.scope !1727, !noundef !135
  %_48.i160.i = zext i8 %_49.i159.i to i64
  %_47.i161.i = shl nuw nsw i64 %_48.i160.i, 8
  %_7.i162.i = or i64 %_8.i154.i, %_47.i161.i
  %280 = getelementptr inbounds nuw i8, ptr %273, i64 7
  %_54.i167.i = load i8, ptr %280, align 1, !alias.scope !1727, !noundef !135
  %_53.i168.i = zext i8 %_54.i167.i to i64
  %281 = or i64 %_7.i162.i, %_53.i168.i
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i: ; preds = %bb2.i108.i, %bb1.i105.i
  %_0.sroa.0.0.i169.i = phi i64 [ %281, %bb2.i108.i ], [ 0, %bb1.i105.i ]
  %_12.i.not = icmp eq i64 %_0.sroa.0.0.i237.i, %_0.sroa.0.0.i169.i
  br i1 %_12.i.not, label %bb2.i1135, label %bb110.i

bb18.i1099:                                       ; preds = %bb15.i1096
  %_29.0.i1100 = add i64 %262, %_163.0.i
  %_29.1.i = icmp ult i64 %_29.0.i1100, %_163.0.i
  br i1 %_29.1.i, label %panic4.i1134, label %bb19.i1101

bb19.i1101:                                       ; preds = %bb18.i1099
  %_30.1.i1102 = icmp ugt i64 %_29.0.i1100, -9
  br i1 %_30.1.i1102, label %panic5.i1133, label %bb20.i1103

panic4.i1134:                                     ; preds = %bb18.i1099
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_410f560b7db958092bd73a0bb4ae0379) #13, !noalias !1717
  unreachable

bb20.i1103:                                       ; preds = %bb19.i1101
  %282 = icmp ugt i64 %_29.0.i1100, 499992
  br i1 %282, label %bb40.i.preheader, label %bb21.i1105

bb40.i.preheader:                                 ; preds = %bb23.i, %bb20.i1103
  br label %bb40.i

panic5.i1133:                                     ; preds = %bb19.i1101
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_410f560b7db958092bd73a0bb4ae0379) #13, !noalias !1717
  unreachable

bb21.i1105:                                       ; preds = %bb20.i1103
  %_35.0.i = add i64 %262, %_156.0.i
  %_35.1.i = icmp ult i64 %_35.0.i, %_156.0.i
  br i1 %_35.1.i, label %panic6.i1132, label %bb22.i1106

bb22.i1106:                                       ; preds = %bb21.i1105
  %_36.1.i1107 = icmp ugt i64 %_35.0.i, -9
  br i1 %_36.1.i1107, label %panic7.i1131, label %bb23.i

panic6.i1132:                                     ; preds = %bb21.i1105
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_25f0ab118ce3ac29922df37c6b354aae) #13, !noalias !1717
  unreachable

bb23.i:                                           ; preds = %bb22.i1106
  %_31.not.i = icmp ugt i64 %_35.0.i, 499992
  br i1 %_31.not.i, label %bb40.i.preheader, label %bb30.i

panic7.i1131:                                     ; preds = %bb22.i1106
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_25f0ab118ce3ac29922df37c6b354aae) #13, !noalias !1717
  unreachable

bb40.i:                                           ; preds = %bb40.i.preheader, %bb44.i
  %k.sroa.0.2.i11223130 = phi i64 [ %k.sroa.0.3.i1129, %bb44.i ], [ %262, %bb40.i.preheader ]
  %_62.0.i = add i64 %k.sroa.0.2.i11223130, %_163.0.i
  %_62.1.i = icmp ult i64 %_62.0.i, %_163.0.i
  br i1 %_62.1.i, label %panic8.i1130, label %bb41.i

bb41.i:                                           ; preds = %bb40.i
  %_63.i = icmp ult i64 %_62.0.i, 500000
  br i1 %_63.i, label %bb42.i1124, label %panic9.i1123

panic8.i1130:                                     ; preds = %bb40.i
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_f491bec5a0814d991fa65b29bceb4569) #13, !noalias !1717
  unreachable

bb42.i1124:                                       ; preds = %bb41.i
  %283 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_62.0.i
  %_59.i1125 = load i8, ptr %283, align 1, !alias.scope !1717, !noundef !135
  %_67.0.i = add i64 %k.sroa.0.2.i11223130, %_156.0.i
  %_67.1.i = icmp ult i64 %_67.0.i, %_156.0.i
  br i1 %_67.1.i, label %panic10.i, label %bb43.i1126

panic9.i1123:                                     ; preds = %bb41.i
  %_62.0.i.lcssa339 = phi i64 [ %_62.0.i, %bb41.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_62.0.i.lcssa339, i64 noundef range(i64 0, -9223372036854775808) 500000, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_6423c6cb6214cc14d5219f2068f396e1) #13, !noalias !1717
  unreachable

bb43.i1126:                                       ; preds = %bb42.i1124
  %_68.i = icmp ult i64 %_67.0.i, 500000
  br i1 %_68.i, label %bb44.i, label %panic11.i1127

panic10.i:                                        ; preds = %bb42.i1124
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_0dafef88f4ad7c766190399efdbc2565) #13, !noalias !1717
  unreachable

bb44.i:                                           ; preds = %bb43.i1126
  %284 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_67.0.i
  %_64.i1128 = load i8, ptr %284, align 1, !alias.scope !1717, !noundef !135
  %_58.i = icmp eq i8 %_59.i1125, %_64.i1128
  %_69.0.i = zext i1 %_58.i to i64
  %k.sroa.0.3.i1129 = add nuw nsw i64 %k.sroa.0.2.i11223130, %_69.0.i
  %_56.i = icmp samesign ult i64 %k.sroa.0.3.i1129, %w.i
  %or.cond19.i = select i1 %_58.i, i1 %_56.i, i1 false
  br i1 %or.cond19.i, label %bb40.i, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit

panic11.i1127:                                    ; preds = %bb43.i1126
  %_67.0.i.lcssa343 = phi i64 [ %_67.0.i, %bb43.i1126 ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_67.0.i.lcssa343, i64 noundef range(i64 0, -9223372036854775808) 500000, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_6298bd754cf21e84e6b31996eea28f6b) #13, !noalias !1717
  unreachable

bb30.i:                                           ; preds = %bb23.i
  %_51.0.i1113 = shl nuw nsw i32 %_145.0.i, 3
  %285 = and i32 %_51.0.i1113, 56
  %_54.i1116.not = icmp eq i32 %285, 0
  br i1 %_54.i1116.not, label %panic18.i1117, label %bb32.i1118

bb32.i1118:                                       ; preds = %bb30.i
  %_53.0.i = sub nuw nsw i32 64, %285
  %286 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_35.0.i
  %287 = getelementptr inbounds nuw i8, ptr %286, i64 1
  %_19.i.i = load i8, ptr %287, align 1, !alias.scope !1728, !noundef !135
  %_18.i.i = zext i8 %_19.i.i to i64
  %_17.i.i = shl nuw nsw i64 %_18.i.i, 48
  %_15.i.i = load i8, ptr %286, align 1, !alias.scope !1728, !noundef !135
  %_14.i.i = zext i8 %_15.i.i to i64
  %_13.i.i = shl nuw i64 %_14.i.i, 56
  %_12.i.i1110 = or disjoint i64 %_17.i.i, %_13.i.i
  %288 = getelementptr inbounds nuw i8, ptr %286, i64 2
  %_25.i.i = load i8, ptr %288, align 1, !alias.scope !1728, !noundef !135
  %_24.i.i = zext i8 %_25.i.i to i64
  %_23.i.i = shl nuw nsw i64 %_24.i.i, 40
  %_11.i.i1111 = or disjoint i64 %_12.i.i1110, %_23.i.i
  %289 = getelementptr inbounds nuw i8, ptr %286, i64 3
  %_31.i.i = load i8, ptr %289, align 1, !alias.scope !1728, !noundef !135
  %_30.i.i = zext i8 %_31.i.i to i64
  %_29.i.i = shl nuw nsw i64 %_30.i.i, 32
  %_10.i.i = or disjoint i64 %_11.i.i1111, %_29.i.i
  %290 = getelementptr inbounds nuw i8, ptr %286, i64 4
  %_37.i.i = load i8, ptr %290, align 1, !alias.scope !1728, !noundef !135
  %_36.i.i = zext i8 %_37.i.i to i64
  %_35.i.i = shl nuw nsw i64 %_36.i.i, 24
  %_9.i.i = or disjoint i64 %_10.i.i, %_35.i.i
  %291 = getelementptr inbounds nuw i8, ptr %286, i64 5
  %_43.i.i = load i8, ptr %291, align 1, !alias.scope !1728, !noundef !135
  %_42.i.i = zext i8 %_43.i.i to i64
  %_41.i.i = shl nuw nsw i64 %_42.i.i, 16
  %_8.i.i = or disjoint i64 %_9.i.i, %_41.i.i
  %292 = getelementptr inbounds nuw i8, ptr %286, i64 6
  %_49.i.i = load i8, ptr %292, align 1, !alias.scope !1728, !noundef !135
  %_48.i.i = zext i8 %_49.i.i to i64
  %_47.i.i = shl nuw nsw i64 %_48.i.i, 8
  %_7.i.i = or i64 %_8.i.i, %_47.i.i
  %293 = getelementptr inbounds nuw i8, ptr %286, i64 7
  %_54.i.i = load i8, ptr %293, align 1, !alias.scope !1728, !noundef !135
  %_53.i.i = zext i8 %_54.i.i to i64
  %294 = or i64 %_7.i.i, %_53.i.i
  %295 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_29.0.i1100
  %296 = getelementptr inbounds nuw i8, ptr %295, i64 1
  %_19.i51.i = load i8, ptr %296, align 1, !alias.scope !1731, !noundef !135
  %_18.i52.i = zext i8 %_19.i51.i to i64
  %_17.i53.i = shl nuw nsw i64 %_18.i52.i, 48
  %_15.i44.i = load i8, ptr %295, align 1, !alias.scope !1731, !noundef !135
  %_14.i45.i = zext i8 %_15.i44.i to i64
  %_13.i46.i = shl nuw i64 %_14.i45.i, 56
  %_12.i54.i = or disjoint i64 %_17.i53.i, %_13.i46.i
  %297 = getelementptr inbounds nuw i8, ptr %295, i64 2
  %_25.i59.i = load i8, ptr %297, align 1, !alias.scope !1731, !noundef !135
  %_24.i60.i = zext i8 %_25.i59.i to i64
  %_23.i61.i = shl nuw nsw i64 %_24.i60.i, 40
  %_11.i62.i = or disjoint i64 %_12.i54.i, %_23.i61.i
  %298 = getelementptr inbounds nuw i8, ptr %295, i64 3
  %_31.i67.i = load i8, ptr %298, align 1, !alias.scope !1731, !noundef !135
  %_30.i68.i = zext i8 %_31.i67.i to i64
  %_29.i69.i = shl nuw nsw i64 %_30.i68.i, 32
  %_10.i70.i = or disjoint i64 %_11.i62.i, %_29.i69.i
  %299 = getelementptr inbounds nuw i8, ptr %295, i64 4
  %_37.i75.i = load i8, ptr %299, align 1, !alias.scope !1731, !noundef !135
  %_36.i76.i = zext i8 %_37.i75.i to i64
  %_35.i77.i = shl nuw nsw i64 %_36.i76.i, 24
  %_9.i78.i = or disjoint i64 %_10.i70.i, %_35.i77.i
  %300 = getelementptr inbounds nuw i8, ptr %295, i64 5
  %_43.i83.i = load i8, ptr %300, align 1, !alias.scope !1731, !noundef !135
  %_42.i84.i = zext i8 %_43.i83.i to i64
  %_41.i85.i = shl nuw nsw i64 %_42.i84.i, 16
  %_8.i86.i = or disjoint i64 %_9.i78.i, %_41.i85.i
  %301 = getelementptr inbounds nuw i8, ptr %295, i64 6
  %_49.i91.i = load i8, ptr %301, align 1, !alias.scope !1731, !noundef !135
  %_48.i92.i = zext i8 %_49.i91.i to i64
  %_47.i93.i = shl nuw nsw i64 %_48.i92.i, 8
  %_7.i94.i = or i64 %_8.i86.i, %_47.i93.i
  %302 = getelementptr inbounds nuw i8, ptr %295, i64 7
  %_54.i99.i = load i8, ptr %302, align 1, !alias.scope !1731, !noundef !135
  %_53.i100.i = zext i8 %_54.i99.i to i64
  %303 = or i64 %_7.i94.i, %_53.i100.i
  %x.i1112 = xor i64 %294, %303
  %304 = zext nneg i32 %_53.0.i to i64
  %_46.i1119 = lshr i64 %x.i1112, %304
  %305 = icmp eq i64 %_46.i1119, 0
  br i1 %305, label %bb101.i, label %bb110.i

panic18.i1117:                                    ; preds = %bb30.i
; call core::panicking::panic_const::panic_const_shr_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_shr_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_0d9222021d7218fa4f635bbfc4f9297d) #13, !noalias !1717
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit: ; preds = %bb44.i
  br i1 %_58.i, label %bb101.i, label %bb110.i

bb101.i:                                          ; preds = %bb32.i1118, %bb15.i1096, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit
  %_170.0.i = add nuw nsw i64 %back.sroa.0.0.i3137, 1
  br label %bb110.i

bb110.i:                                          ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i, %bb32.i1118, %bb77.i, %bb80.i, %bb101.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit, %bb90.i, %bb87.i, %bb84.i
  %p.sroa.0.8.i = phi i64 [ %_125.0.i, %bb80.i ], [ %_156.0.i, %bb101.i ], [ %p.sroa.0.7.i3136, %bb84.i ], [ %p.sroa.0.7.i3136, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit ], [ %p.sroa.0.7.i3136, %bb90.i ], [ %p.sroa.0.7.i3136, %bb87.i ], [ %p.sroa.0.7.i3136, %bb77.i ], [ %p.sroa.0.7.i3136, %bb32.i1118 ], [ %p.sroa.0.7.i3136, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i ]
  %back.sroa.0.1.i = phi i64 [ %_138.0.i, %bb80.i ], [ %_170.0.i, %bb101.i ], [ 16, %bb84.i ], [ 16, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit ], [ 16, %bb90.i ], [ 16, %bb87.i ], [ 16, %bb77.i ], [ 16, %bb32.i1118 ], [ 16, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i ]
  %l.sroa.0.3.i = phi i64 [ %_137.0.i, %bb80.i ], [ %_149.0.i, %bb101.i ], [ %l.sroa.0.2.i3138, %bb84.i ], [ %l.sroa.0.2.i3138, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit ], [ %l.sroa.0.2.i3138, %bb90.i ], [ %l.sroa.0.2.i3138, %bb87.i ], [ %l.sroa.0.2.i3138, %bb77.i ], [ %l.sroa.0.2.i3138, %bb32.i1118 ], [ %l.sroa.0.2.i3138, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i ]
  %nt.sroa.0.8.i = phi i64 [ %258, %bb80.i ], [ %258, %bb101.i ], [ %nt.sroa.0.7.i3139, %bb84.i ], [ %nt.sroa.0.7.i3139, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit ], [ %nt.sroa.0.7.i3139, %bb90.i ], [ %nt.sroa.0.7.i3139, %bb87.i ], [ %nt.sroa.0.7.i3139, %bb77.i ], [ %nt.sroa.0.7.i3139, %bb32.i1118 ], [ %nt.sroa.0.7.i3139, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i ]
  %_103.i = icmp ult i64 %back.sroa.0.1.i, 16
  %306 = add i64 %nt.sroa.0.8.i, -1
  %307 = icmp ult i64 %306, %out.1
  %or.cond48.i = select i1 %_103.i, i1 %307, i1 false
  %_110.i = icmp ult i64 %l.sroa.0.3.i, 258
  %or.cond49.i = select i1 %or.cond48.i, i1 %_110.i, i1 false
  %_112.i = icmp ult i64 %d.sroa.0.0.i.lcssa, %p.sroa.0.8.i
  %or.cond149.i = select i1 %or.cond49.i, i1 %_112.i, i1 false
  br i1 %or.cond149.i, label %bb71.i, label %bb116.i

bb80.i:                                           ; preds = %bb77.i
  %_137.0.i = add nuw nsw i64 %l.sroa.0.2.i3138, 1
  %_138.0.i = add nuw nsw i64 %back.sroa.0.0.i3137, 1
  br label %bb110.i

_RINvNtCs2hd9JHJjR4I_9candidate5parse8u118_runKj10000_Kj8000_Kmffffffff_Kj4_Kj6_Kj20_Kj5_Kjf4240_Kj40_Kj1_Kj10_KB18_Kl40_KB1C_EB4_.exit: ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit324, %bb178.i
  %nt.sroa.0.2.i.lcssa = phi i64 [ %nt.sroa.0.4.i.lcssa, %bb178.i ], [ %_10.0.i323, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit324 ]
  ret i64 %nt.sroa.0.2.i.lcssa
}