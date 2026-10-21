define internal fastcc noundef i64 @_RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row9(ptr noalias nofree noundef nonnull readonly captures(address, read_provenance) %input.0, i64 noundef range(i64 0, -9223372036854775808) %input.1, ptr noalias nofree noundef nonnull align 4 captures(none) %out.0, i64 noundef range(i64 0, 2305843009213693952) %out.1) unnamed_addr #0 !guid !2596 {
start:
  %prev.i = alloca [131072 x i8], align 4
  %head.i = alloca [262144 x i8], align 4
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2597)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2600)
  %_4.i = icmp samesign ugt i64 %input.1, 16
  br i1 %_4.i, label %bb5.i.preheader, label %bb178.i

bb178.i:                                          ; preds = %bb177.i, %start
  %p.sroa.0.0.i = phi i64 [ %p.sroa.0.4.i.lcssa, %bb177.i ], [ 0, %start ]
  %nt.sroa.0.0.i = phi i64 [ %nt.sroa.0.4.i.lcssa, %bb177.i ], [ 0, %start ]
  %_237.i2182 = icmp ult i64 %p.sroa.0.0.i, %input.1
  br i1 %_237.i2182, label %bb1.i173.preheader, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse8u118_runKj10000_Kj8000_Kmffffffff_Kj4_Kjc_Kj40_Kj6_Kjf4240_Kj80_Kj1_Kj10_KB18_Kl40_Kj0_EB4_.exit

bb1.i173.preheader:                               ; preds = %bb178.i
  %umax = tail call i64 @llvm.umax.i64(i64 %nt.sroa.0.0.i, i64 %out.1)
  %0 = xor i64 %p.sroa.0.0.i, -1
  %1 = add nsw i64 %input.1, %0
  %2 = sub i64 %umax, %nt.sroa.0.0.i
  %3 = call i64 @llvm.umin.i64(i64 %1, i64 %2)
  %4 = add i64 %3, 1
  %min.iters.check2721 = icmp ult i64 %4, 9
  br i1 %min.iters.check2721, label %bb1.i173.preheader2743, label %vector.ph2722

bb1.i173.preheader2743:                           ; preds = %vector.body2725, %bb1.i173.preheader
  %nt.sroa.0.2.i2184.ph = phi i64 [ %nt.sroa.0.0.i, %bb1.i173.preheader ], [ %7, %vector.body2725 ]
  %p.sroa.0.2.i2183.ph = phi i64 [ %p.sroa.0.0.i, %bb1.i173.preheader ], [ %8, %vector.body2725 ]
  br label %bb1.i173

vector.ph2722:                                    ; preds = %bb1.i173.preheader
  %n.mod.vf2723 = and i64 %4, 7
  %5 = icmp eq i64 %n.mod.vf2723, 0
  %6 = select i1 %5, i64 8, i64 %n.mod.vf2723
  %n.vec2724 = sub nuw i64 %4, %6
  %7 = add i64 %nt.sroa.0.0.i, %n.vec2724
  %8 = add i64 %p.sroa.0.0.i, %n.vec2724
  %9 = getelementptr i8, ptr %input.0, i64 %p.sroa.0.0.i
  %10 = getelementptr [4 x i8], ptr %out.0, i64 %nt.sroa.0.0.i
  br label %vector.body2725

vector.body2725:                                  ; preds = %vector.body2725, %vector.ph2722
  %index2726 = phi i64 [ 0, %vector.ph2722 ], [ %index.next2729, %vector.body2725 ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2602)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2605)
  %11 = getelementptr i8, ptr %9, i64 %index2726
  %12 = getelementptr inbounds nuw i8, ptr %11, i64 4
  %wide.load2727 = load <4 x i8>, ptr %11, align 1, !alias.scope !2602, !noalias !2605
  %wide.load2728 = load <4 x i8>, ptr %12, align 1, !alias.scope !2602, !noalias !2605
  %13 = getelementptr [4 x i8], ptr %10, i64 %index2726
  %14 = zext <4 x i8> %wide.load2727 to <4 x i32>
  %15 = zext <4 x i8> %wide.load2728 to <4 x i32>
  %16 = getelementptr inbounds nuw i8, ptr %13, i64 16
  store <4 x i32> %14, ptr %13, align 4, !alias.scope !2605, !noalias !2602
  store <4 x i32> %15, ptr %16, align 4, !alias.scope !2605, !noalias !2602
  %index.next2729 = add nuw i64 %index2726, 8
  %17 = icmp eq i64 %index.next2729, %n.vec2724
  br i1 %17, label %bb1.i173.preheader2743, label %vector.body2725, !llvm.loop !2607

bb5.i.preheader:                                  ; preds = %start
  call void @llvm.lifetime.start.p0(ptr nonnull %head.i), !noalias !2608
  call void @llvm.memset.p0.i64(ptr noundef nonnull align 4 dereferenceable(262144) %head.i, i8 0, i64 262144, i1 false), !noalias !2608
  call void @llvm.lifetime.start.p0(ptr nonnull %prev.i), !noalias !2608
  call void @llvm.memset.p0.i64(ptr noundef nonnull align 4 dereferenceable(131072) %prev.i, i8 0, i64 131072, i1 false), !noalias !2608
  %_8.0.i = add nsw i64 %input.1, -8
  %18 = add nuw i64 %input.1, 16
  %19 = add nsw i64 %input.1, -10
  br label %bb5.i

bb177.i:                                          ; preds = %bb174.i
  %p.sroa.0.4.i.lcssa = phi i64 [ %p.sroa.0.4.i, %bb174.i ]
  %nt.sroa.0.4.i.lcssa = phi i64 [ %nt.sroa.0.4.i, %bb174.i ]
  call void @llvm.lifetime.end.p0(ptr nonnull %prev.i), !noalias !2608
  call void @llvm.lifetime.end.p0(ptr nonnull %head.i), !noalias !2608
  br label %bb178.i

bb5.i:                                            ; preds = %bb5.i.preheader, %bb174.i
  %nt.sroa.0.1.i2179 = phi i64 [ %nt.sroa.0.4.i, %bb174.i ], [ 0, %bb5.i.preheader ]
  %miss.sroa.0.0.i2178 = phi i64 [ %miss.sroa.0.1.i, %bb174.i ], [ 0, %bb5.i.preheader ]
  %fuel.sroa.0.0.i2177 = phi i64 [ %_15.0.i, %bb174.i ], [ %18, %bb5.i.preheader ]
  %p.sroa.0.1.i2176 = phi i64 [ %p.sroa.0.4.i, %bb174.i ], [ 0, %bb5.i.preheader ]
  %ins.sroa.0.0.i2175 = phi i64 [ %ins.sroa.0.3.i, %bb174.i ], [ 0, %bb5.i.preheader ]
  %p.sroa.0.1.i2176.fr = freeze i64 %p.sroa.0.1.i2176
  %_15.0.i = add i64 %fuel.sroa.0.0.i2177, -1
  %_16.i2098 = icmp ult i64 %ins.sroa.0.0.i2175, %p.sroa.0.1.i2176.fr
  br i1 %_16.i2098, label %bb8.i, label %bb11.i

bb1.i173:                                         ; preds = %bb1.i173.preheader2743, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit179
  %nt.sroa.0.2.i2184 = phi i64 [ %_10.0.i178, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit179 ], [ %nt.sroa.0.2.i2184.ph, %bb1.i173.preheader2743 ]
  %p.sroa.0.2.i2183 = phi i64 [ %_241.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit179 ], [ %p.sroa.0.2.i2183.ph, %bb1.i173.preheader2743 ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2602)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2605)
  %exitcond2325.not = icmp eq i64 %nt.sroa.0.2.i2184, %umax
  br i1 %exitcond2325.not, label %panic1.i175, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit179

panic1.i175:                                      ; preds = %bb1.i173
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %umax, i64 noundef range(i64 0, 2305843009213693952) %out.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_ce72d480401e07b7a290039044612259) #13, !noalias !2609
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit179: ; preds = %bb1.i173
  %20 = getelementptr inbounds nuw i8, ptr %input.0, i64 %p.sroa.0.2.i2183
  %_5.i177 = load i8, ptr %20, align 1, !alias.scope !2602, !noalias !2605, !noundef !135
  %21 = getelementptr inbounds nuw [4 x i8], ptr %out.0, i64 %nt.sroa.0.2.i2184
  %22 = zext i8 %_5.i177 to i32
  store i32 %22, ptr %21, align 4, !alias.scope !2605, !noalias !2602
  %_10.0.i178 = add i64 %nt.sroa.0.2.i2184, 1
  %_241.0.i = add i64 %p.sroa.0.2.i2183, 1
  %exitcond2326.not = icmp eq i64 %_241.0.i, %input.1
  br i1 %exitcond2326.not, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse8u118_runKj10000_Kj8000_Kmffffffff_Kj4_Kjc_Kj40_Kj6_Kjf4240_Kj80_Kj1_Kj10_KB18_Kl40_Kj0_EB4_.exit, label %bb1.i173, !llvm.loop !2610

bb11.i:                                           ; preds = %bb8.i, %bb5.i
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2611)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2614)
  %23 = getelementptr inbounds nuw i8, ptr %input.0, i64 %p.sroa.0.1.i2176.fr
  %24 = load <4 x i8>, ptr %23, align 1, !alias.scope !2616, !noalias !2619
  %25 = bitcast <4 x i8> %24 to i32
  %26 = call i32 @llvm.bswap.i32(i32 %25)
  %27 = zext i32 %26 to i64
  %28 = mul i64 %27, -7046029254386353131
  %29 = lshr i64 %28, 48
  %30 = getelementptr inbounds nuw [4 x i8], ptr %head.i, i64 %29
  %old.i173.i = load i32, ptr %30, align 4, !alias.scope !2611, !noalias !2620, !noundef !135
  %_16.i174.i = and i64 %p.sroa.0.1.i2176.fr, 32767
  %31 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_16.i174.i
  store i32 %old.i173.i, ptr %31, align 4, !alias.scope !2614, !noalias !2622
  %32 = trunc i64 %p.sroa.0.1.i2176.fr to i32
  store i32 %32, ptr %30, align 4, !alias.scope !2611, !noalias !2620
  %_0.i175.i = zext i32 %old.i173.i to i64
  %_29.0.i = add i64 %p.sroa.0.1.i2176.fr, 1
  %_13.0.i9 = sub i64 %input.1, %p.sroa.0.1.i2176.fr
  %spec.store.select3.i10 = tail call i64 @llvm.umin.i64(i64 %_13.0.i9, i64 258)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2623)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2626)
  %spec.store.select.i16 = tail call i64 @llvm.umin.i64(i64 %_13.0.i9, i64 128)
  %33 = and i64 %spec.store.select3.i10, 504
  %34 = extractelement <4 x i8> %24, i64 3
  %_24.i1042102.not = icmp eq i64 %33, %spec.store.select3.i10
  br label %bb11.i18

bb11.i18:                                         ; preds = %bb37.i, %bb11.i
  %start1.sroa.0.0.i2109 = phi i64 [ %_0.i175.i, %bb11.i ], [ %nx.i, %bb37.i ]
  %have.sroa.0.0.i2108 = phi i64 [ 3, %bb11.i ], [ %have.sroa.0.2.i, %bb37.i ]
  %depth.sroa.0.0.i2107 = phi i64 [ 12, %bb11.i ], [ %_66.0.i, %bb37.i ]
  %bd.sroa.0.0.i2106 = phi i64 [ 0, %bb11.i ], [ %bd.sroa.0.2.i, %bb37.i ]
  %pb.sroa.0.1.i2105 = phi i8 [ %34, %bb11.i ], [ %pb.sroa.0.3.i, %bb37.i ]
  %d.i = sub nsw i64 %p.sroa.0.1.i2176.fr, %start1.sroa.0.0.i2109
  %_29.i = add nsw i64 %d.i, -1
  %_28.i = icmp ult i64 %_29.i, 32768
  br i1 %_28.i, label %bb13.i, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit

bb13.i:                                           ; preds = %bb11.i18
  %_34.0.i = add nuw nsw i64 %start1.sroa.0.0.i2109, %have.sroa.0.0.i2108
  %_30.i = icmp ult i64 %_34.0.i, %input.1
  br i1 %_30.i, label %bb16.i19, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit

bb16.i19:                                         ; preds = %bb13.i
  %35 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_34.0.i
  %_36.i = load i8, ptr %35, align 1, !alias.scope !2623, !noalias !2626, !noundef !135
  %_35.i20 = icmp eq i8 %_36.i, %pb.sroa.0.1.i2105
  br i1 %_35.i20, label %bb2.i128, label %bb37.i

bb2.i128:                                         ; preds = %bb16.i19, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit
  %k.sroa.0.0.i992101 = phi i64 [ %_10.0.i129, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit ], [ 0, %bb16.i19 ]
  %_10.0.i129 = add nuw nsw i64 %k.sroa.0.0.i992101, 8
  %_7.not.i132 = icmp samesign ugt i64 %_10.0.i129, %spec.store.select3.i10
  br i1 %_7.not.i132, label %bb15.i100, label %bb4.i133

bb4.i133:                                         ; preds = %bb2.i128
  %_13.i134 = add nuw nsw i64 %k.sroa.0.0.i992101, %start1.sroa.0.0.i2109
  %_5.0.i426 = add nuw nsw i64 %_13.i134, 8
  %_3.not.i427 = icmp samesign ugt i64 %_5.0.i426, %input.1
  br i1 %_3.not.i427, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit492, label %bb2.i428

bb2.i428:                                         ; preds = %bb4.i133
  %36 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_13.i134
  %_15.i432 = load i8, ptr %36, align 1, !alias.scope !2628, !noalias !2626, !noundef !135
  %_14.i433 = zext i8 %_15.i432 to i64
  %_13.i434 = shl nuw i64 %_14.i433, 56
  %37 = getelementptr inbounds nuw i8, ptr %36, i64 1
  %_19.i439 = load i8, ptr %37, align 1, !alias.scope !2628, !noalias !2626, !noundef !135
  %_18.i440 = zext i8 %_19.i439 to i64
  %_17.i441 = shl nuw nsw i64 %_18.i440, 48
  %_12.i442 = or disjoint i64 %_17.i441, %_13.i434
  %38 = getelementptr inbounds nuw i8, ptr %36, i64 2
  %_25.i447 = load i8, ptr %38, align 1, !alias.scope !2628, !noalias !2626, !noundef !135
  %_24.i448 = zext i8 %_25.i447 to i64
  %_23.i449 = shl nuw nsw i64 %_24.i448, 40
  %_11.i450 = or disjoint i64 %_12.i442, %_23.i449
  %39 = getelementptr inbounds nuw i8, ptr %36, i64 3
  %_31.i455 = load i8, ptr %39, align 1, !alias.scope !2628, !noalias !2626, !noundef !135
  %_30.i456 = zext i8 %_31.i455 to i64
  %_29.i457 = shl nuw nsw i64 %_30.i456, 32
  %_10.i458 = or disjoint i64 %_11.i450, %_29.i457
  %40 = getelementptr inbounds nuw i8, ptr %36, i64 4
  %_37.i463 = load i8, ptr %40, align 1, !alias.scope !2628, !noalias !2626, !noundef !135
  %_36.i464 = zext i8 %_37.i463 to i64
  %_35.i465 = shl nuw nsw i64 %_36.i464, 24
  %_9.i466 = or disjoint i64 %_10.i458, %_35.i465
  %41 = getelementptr inbounds nuw i8, ptr %36, i64 5
  %_43.i471 = load i8, ptr %41, align 1, !alias.scope !2628, !noalias !2626, !noundef !135
  %_42.i472 = zext i8 %_43.i471 to i64
  %_41.i473 = shl nuw nsw i64 %_42.i472, 16
  %_8.i474 = or disjoint i64 %_9.i466, %_41.i473
  %42 = getelementptr inbounds nuw i8, ptr %36, i64 6
  %_49.i479 = load i8, ptr %42, align 1, !alias.scope !2628, !noalias !2626, !noundef !135
  %_48.i480 = zext i8 %_49.i479 to i64
  %_47.i481 = shl nuw nsw i64 %_48.i480, 8
  %_7.i482 = or i64 %_8.i474, %_47.i481
  %43 = getelementptr inbounds nuw i8, ptr %36, i64 7
  %_54.i487 = load i8, ptr %43, align 1, !alias.scope !2628, !noalias !2626, !noundef !135
  %_53.i488 = zext i8 %_54.i487 to i64
  %44 = or i64 %_7.i482, %_53.i488
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit492

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit492: ; preds = %bb4.i133, %bb2.i428
  %_0.sroa.0.0.i490 = phi i64 [ %44, %bb2.i428 ], [ 0, %bb4.i133 ]
  %_16.i136 = add nuw i64 %k.sroa.0.0.i992101, %p.sroa.0.1.i2176.fr
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2631)
  %_5.1.i = icmp ugt i64 %_16.i136, -9
  br i1 %_5.1.i, label %panic.i423, label %bb1.i380

bb1.i380:                                         ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit492
  %_5.0.i381 = add nuw i64 %_16.i136, 8
  %_3.not.i382 = icmp ugt i64 %_5.0.i381, %input.1
  br i1 %_3.not.i382, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit, label %bb2.i383

panic.i423:                                       ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit492
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_bb314acf14069c2fbedf530b060ebd60) #13, !noalias !2634
  unreachable

bb2.i383:                                         ; preds = %bb1.i380
  %45 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_16.i136
  %_15.i387 = load i8, ptr %45, align 1, !alias.scope !2631, !noalias !2626, !noundef !135
  %_14.i388 = zext i8 %_15.i387 to i64
  %_13.i389 = shl nuw i64 %_14.i388, 56
  %46 = getelementptr inbounds nuw i8, ptr %45, i64 1
  %_19.i392 = load i8, ptr %46, align 1, !alias.scope !2631, !noalias !2626, !noundef !135
  %_18.i393 = zext i8 %_19.i392 to i64
  %_17.i = shl nuw nsw i64 %_18.i393, 48
  %_12.i394 = or disjoint i64 %_17.i, %_13.i389
  %47 = getelementptr inbounds nuw i8, ptr %45, i64 2
  %_25.i398 = load i8, ptr %47, align 1, !alias.scope !2631, !noalias !2626, !noundef !135
  %_24.i399 = zext i8 %_25.i398 to i64
  %_23.i = shl nuw nsw i64 %_24.i399, 40
  %_11.i400 = or disjoint i64 %_12.i394, %_23.i
  %48 = getelementptr inbounds nuw i8, ptr %45, i64 3
  %_31.i = load i8, ptr %48, align 1, !alias.scope !2631, !noalias !2626, !noundef !135
  %_30.i403 = zext i8 %_31.i to i64
  %_29.i404 = shl nuw nsw i64 %_30.i403, 32
  %_10.i405 = or disjoint i64 %_11.i400, %_29.i404
  %49 = getelementptr inbounds nuw i8, ptr %45, i64 4
  %_37.i407 = load i8, ptr %49, align 1, !alias.scope !2631, !noalias !2626, !noundef !135
  %_36.i408 = zext i8 %_37.i407 to i64
  %_35.i409 = shl nuw nsw i64 %_36.i408, 24
  %_9.i410 = or disjoint i64 %_10.i405, %_35.i409
  %50 = getelementptr inbounds nuw i8, ptr %45, i64 5
  %_43.i = load i8, ptr %50, align 1, !alias.scope !2631, !noalias !2626, !noundef !135
  %_42.i = zext i8 %_43.i to i64
  %_41.i413 = shl nuw nsw i64 %_42.i, 16
  %_8.i414 = or disjoint i64 %_9.i410, %_41.i413
  %51 = getelementptr inbounds nuw i8, ptr %45, i64 6
  %_49.i417 = load i8, ptr %51, align 1, !alias.scope !2631, !noalias !2626, !noundef !135
  %_48.i = zext i8 %_49.i417 to i64
  %_47.i = shl nuw nsw i64 %_48.i, 8
  %_7.i418 = or i64 %_8.i414, %_47.i
  %52 = getelementptr inbounds nuw i8, ptr %45, i64 7
  %_54.i = load i8, ptr %52, align 1, !alias.scope !2631, !noalias !2626, !noundef !135
  %_53.i = zext i8 %_54.i to i64
  %53 = or i64 %_7.i418, %_53.i
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit: ; preds = %bb1.i380, %bb2.i383
  %_0.sroa.0.0.i422 = phi i64 [ %53, %bb2.i383 ], [ 0, %bb1.i380 ]
  %54 = icmp eq i64 %_0.sroa.0.0.i490, %_0.sroa.0.0.i422
  br i1 %54, label %bb2.i128, label %bb15.i100.thread

bb15.i100:                                        ; preds = %bb2.i128
  br i1 %_24.i1042102.not, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit148, label %bb19.i110

bb15.i100.thread:                                 ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit
  %_0.sroa.0.0.i422.lcssa = phi i64 [ %_0.sroa.0.0.i422, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit ]
  %_0.sroa.0.0.i490.lcssa2747 = phi i64 [ %_0.sroa.0.0.i490, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit ]
  %k.sroa.0.0.i992101.lcssa2746 = phi i64 [ %k.sroa.0.0.i992101, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit ]
  %x.i139 = xor i64 %_0.sroa.0.0.i422.lcssa, %_0.sroa.0.0.i490.lcssa2747
  %55 = tail call range(i64 0, 65) i64 @llvm.ctlz.i64(i64 %x.i139, i1 true)
  %_2018.i140 = lshr i64 %55, 3
  %_22.0.i141 = or disjoint i64 %_2018.i140, %k.sroa.0.0.i992101.lcssa2746
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit148

bb19.i110:                                        ; preds = %bb15.i100, %bb22.i120
  %k.sroa.0.2.i1032104 = phi i64 [ %k.sroa.0.3.i125, %bb22.i120 ], [ %33, %bb15.i100 ]
  %_30.0.i108 = add nuw nsw i64 %k.sroa.0.2.i1032104, %start1.sroa.0.0.i2109
  %_32.i111 = icmp samesign ult i64 %_30.0.i108, %input.1
  br i1 %_32.i111, label %bb20.i113, label %panic4.i112

bb20.i113:                                        ; preds = %bb19.i110
  %56 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_30.0.i108
  %_27.i114 = load i8, ptr %56, align 1, !alias.scope !2635, !noalias !2626, !noundef !135
  %_36.0.i115 = add i64 %k.sroa.0.2.i1032104, %p.sroa.0.1.i2176.fr
  %_36.1.i116 = icmp ult i64 %_36.0.i115, %p.sroa.0.1.i2176.fr
  br i1 %_36.1.i116, label %panic5.i126, label %bb21.i117

panic4.i112:                                      ; preds = %bb19.i110
  %_30.0.i108.lcssa2748 = phi i64 [ %_30.0.i108, %bb19.i110 ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_30.0.i108.lcssa2748, i64 noundef range(i64 0, -9223372036854775808) %input.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_333f7815cbdde125b13aaef2eac5916c) #13, !noalias !2626
  unreachable

bb21.i117:                                        ; preds = %bb20.i113
  %_37.i118 = icmp ult i64 %_36.0.i115, %input.1
  br i1 %_37.i118, label %bb22.i120, label %panic6.i119

panic5.i126:                                      ; preds = %bb20.i113
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_44247feb933c63f72105b72612a623ee) #13, !noalias !2626
  unreachable

bb22.i120:                                        ; preds = %bb21.i117
  %57 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_36.0.i115
  %_33.i121 = load i8, ptr %57, align 1, !alias.scope !2635, !noalias !2626, !noundef !135
  %_26.i122 = icmp eq i8 %_27.i114, %_33.i121
  %_38.0.i123 = zext i1 %_26.i122 to i64
  %k.sroa.0.3.i125 = add nuw nsw i64 %k.sroa.0.2.i1032104, %_38.0.i123
  %_24.i104 = icmp samesign ult i64 %k.sroa.0.3.i125, %spec.store.select3.i10
  %or.cond.i105 = select i1 %_26.i122, i1 %_24.i104, i1 false
  br i1 %or.cond.i105, label %bb19.i110, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit148

panic6.i119:                                      ; preds = %bb21.i117
  %_36.0.i115.lcssa2752 = phi i64 [ %_36.0.i115, %bb21.i117 ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_36.0.i115.lcssa2752, i64 noundef range(i64 0, -9223372036854775808) %input.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_c7b835eab7e4664f8dc21896c854bf2b) #13, !noalias !2626
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit148: ; preds = %bb22.i120, %bb15.i100.thread, %bb15.i100
  %k.sroa.0.2.i103.lcssa = phi i64 [ %33, %bb15.i100 ], [ %_22.0.i141, %bb15.i100.thread ], [ %k.sroa.0.3.i125, %bb22.i120 ]
  %_46.i = icmp ugt i64 %k.sroa.0.2.i103.lcssa, %have.sroa.0.0.i2108
  br i1 %_46.i, label %bb19.i, label %bb37.i

bb19.i:                                           ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit148
  %_51.not.i = icmp ult i64 %k.sroa.0.2.i103.lcssa, %spec.store.select.i16
  br i1 %_51.not.i, label %bb26.i, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit

bb26.i:                                           ; preds = %bb19.i
  %_55.0.i = add i64 %k.sroa.0.2.i103.lcssa, %p.sroa.0.1.i2176.fr
  %_55.1.i = icmp ult i64 %_55.0.i, %p.sroa.0.1.i2176.fr
  br i1 %_55.1.i, label %panic7.i, label %bb27.i

bb27.i:                                           ; preds = %bb26.i
  %_53.not.i = icmp ult i64 %_55.0.i, %input.1
  br i1 %_53.not.i, label %bb31.i, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit

panic7.i:                                         ; preds = %bb26.i
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_5082c7ce777234b7475a595bf60db7a2) #13, !noalias !2626
  unreachable

bb31.i:                                           ; preds = %bb27.i
  %58 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_55.0.i
  %59 = load i8, ptr %58, align 1, !alias.scope !2623, !noalias !2626, !noundef !135
  br label %bb37.i

bb37.i:                                           ; preds = %bb31.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit148, %bb16.i19
  %pb.sroa.0.3.i = phi i8 [ %pb.sroa.0.1.i2105, %bb16.i19 ], [ %pb.sroa.0.1.i2105, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit148 ], [ %59, %bb31.i ]
  %bd.sroa.0.2.i = phi i64 [ %bd.sroa.0.0.i2106, %bb16.i19 ], [ %bd.sroa.0.0.i2106, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit148 ], [ %d.i, %bb31.i ]
  %have.sroa.0.2.i = phi i64 [ %have.sroa.0.0.i2108, %bb16.i19 ], [ %have.sroa.0.0.i2108, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit148 ], [ %k.sroa.0.2.i103.lcssa, %bb31.i ]
  %_60.i21 = and i64 %start1.sroa.0.0.i2109, 32767
  %60 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_60.i21
  %_59.i = load i32, ptr %60, align 4, !alias.scope !2626, !noalias !2623, !noundef !135
  %nx.i = zext i32 %_59.i to i64
  %_64.i = icmp samesign ule i64 %start1.sroa.0.0.i2109, %nx.i
  %_66.0.i = add nsw i64 %depth.sroa.0.0.i2107, -1
  %_24.not.i = icmp eq i64 %_66.0.i, 0
  %or.cond = select i1 %_64.i, i1 true, i1 %_24.not.i
  br i1 %or.cond, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit, label %bb11.i18

_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit: ; preds = %bb19.i, %bb27.i, %bb37.i, %bb13.i, %bb11.i18
  %have.sroa.0.1.i2335 = phi i64 [ %have.sroa.0.0.i2108, %bb11.i18 ], [ %have.sroa.0.2.i, %bb37.i ], [ %have.sroa.0.0.i2108, %bb13.i ], [ %k.sroa.0.2.i103.lcssa, %bb27.i ], [ %k.sroa.0.2.i103.lcssa, %bb19.i ]
  %bd.sroa.0.1.i2334 = phi i64 [ %bd.sroa.0.0.i2106, %bb11.i18 ], [ %bd.sroa.0.2.i, %bb37.i ], [ %bd.sroa.0.0.i2106, %bb13.i ], [ %d.i, %bb27.i ], [ %d.i, %bb19.i ]
  %.not = icmp eq i64 %bd.sroa.0.1.i2334, 0
  br i1 %.not, label %bb154.i, label %bb16.i.preheader

bb16.i.preheader:                                 ; preds = %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit
  %_39.i2133 = icmp ult i64 %have.sroa.0.1.i2335, 64
  br i1 %_39.i2133, label %bb18.i.preheader, label %bb63.i

bb18.i.preheader:                                 ; preds = %bb16.i.preheader
  %61 = xor i64 %p.sroa.0.1.i2176.fr, -1
  %62 = add i64 %input.1, %61
  %umax2713 = call i64 @llvm.umax.i64(i64 %_8.0.i, i64 %_29.0.i)
  %umax2714 = call i64 @llvm.umax.i64(i64 %nt.sroa.0.1.i2179, i64 %out.1)
  br label %bb18.i

bb8.i:                                            ; preds = %bb5.i, %bb8.i
  %ins.sroa.0.1.i2099 = phi i64 [ %_23.0.i, %bb8.i ], [ %ins.sroa.0.0.i2175, %bb5.i ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2638)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2641)
  %63 = getelementptr inbounds nuw i8, ptr %input.0, i64 %ins.sroa.0.1.i2099
  %64 = load i32, ptr %63, align 1
  %65 = call i32 @llvm.bswap.i32(i32 %64)
  %66 = zext i32 %65 to i64
  %67 = mul i64 %66, -7046029254386353131
  %68 = lshr i64 %67, 48
  %69 = getelementptr inbounds nuw [4 x i8], ptr %head.i, i64 %68
  %old.i.i = load i32, ptr %69, align 4, !alias.scope !2638, !noalias !2643, !noundef !135
  %_16.i.i = and i64 %ins.sroa.0.1.i2099, 32767
  %70 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_16.i.i
  store i32 %old.i.i, ptr %70, align 4, !alias.scope !2641, !noalias !2645
  %71 = trunc i64 %ins.sroa.0.1.i2099 to i32
  store i32 %71, ptr %69, align 4, !alias.scope !2638, !noalias !2643
  %_23.0.i = add nuw nsw i64 %ins.sroa.0.1.i2099, 1
  %exitcond.not = icmp eq i64 %_23.0.i, %p.sroa.0.1.i2176.fr
  br i1 %exitcond.not, label %bb11.i, label %bb8.i

bb154.i:                                          ; preds = %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2646)
  %_9.i165 = icmp ult i64 %nt.sroa.0.1.i2179, %out.1
  br i1 %_9.i165, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit170, label %panic1.i166

panic1.i166:                                      ; preds = %bb154.i
  %nt.sroa.0.1.i2179.lcssa2815 = phi i64 [ %nt.sroa.0.1.i2179, %bb154.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %nt.sroa.0.1.i2179.lcssa2815, i64 noundef range(i64 0, 2305843009213693952) %out.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_ce72d480401e07b7a290039044612259) #13, !noalias !2649
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit170: ; preds = %bb154.i
  %72 = getelementptr inbounds nuw [4 x i8], ptr %out.0, i64 %nt.sroa.0.1.i2179
  %73 = extractelement <4 x i8> %24, i64 0
  %74 = zext i8 %73 to i32
  store i32 %74, ptr %72, align 4, !alias.scope !2646, !noalias !2651
  %_219.0.i = add i64 %miss.sroa.0.0.i2178, 1
  %_219.1.i = icmp eq i64 %miss.sroa.0.0.i2178, -1
  br i1 %_219.1.i, label %panic5.i, label %bb157.i

bb157.i:                                          ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit170
  %75 = lshr i64 %_219.0.i, 6
  %nt.sroa.0.3.i2111 = add nuw nsw i64 %nt.sroa.0.1.i2179, 1
  %_225.i2112 = icmp ne i64 %75, 0
  %_227.i2113 = icmp ult i64 %_29.0.i, %_8.0.i
  %or.cond45.i2114 = select i1 %_225.i2112, i1 %_227.i2113, i1 false
  br i1 %or.cond45.i2114, label %bb164.i.preheader, label %bb170.i

bb164.i.preheader:                                ; preds = %bb157.i
  %spec.store.select.i = tail call i64 @llvm.umin.i64(i64 %75, i64 1000000)
  %76 = sub i64 %19, %p.sroa.0.1.i2176.fr
  %77 = add nsw i64 %spec.store.select.i, -1
  %umin2715 = call i64 @llvm.umin.i64(i64 %76, i64 %77)
  %78 = freeze i64 %umin2715
  %79 = xor i64 %nt.sroa.0.1.i2179, -1
  %80 = add nsw i64 %out.1, %79
  %umin2716 = call i64 @llvm.umin.i64(i64 %78, i64 %80)
  %81 = add i64 %umin2716, 1
  %min.iters.check = icmp ult i64 %81, 9
  br i1 %min.iters.check, label %bb164.i.preheader2744, label %vector.ph

bb164.i.preheader2744:                            ; preds = %vector.body, %bb164.i.preheader
  %nt.sroa.0.3.i2117.ph = phi i64 [ %nt.sroa.0.3.i2111, %bb164.i.preheader ], [ %84, %vector.body ]
  %p.sroa.0.3.i2116.ph = phi i64 [ %_29.0.i, %bb164.i.preheader ], [ %85, %vector.body ]
  %step.sroa.0.0.i2115.ph = phi i64 [ %spec.store.select.i, %bb164.i.preheader ], [ %86, %vector.body ]
  br label %bb164.i

vector.ph:                                        ; preds = %bb164.i.preheader
  %n.mod.vf = and i64 %81, 7
  %82 = icmp eq i64 %n.mod.vf, 0
  %83 = select i1 %82, i64 8, i64 %n.mod.vf
  %n.vec = sub nuw i64 %81, %83
  %84 = add i64 %nt.sroa.0.3.i2111, %n.vec
  %85 = add i64 %_29.0.i, %n.vec
  %86 = sub i64 %spec.store.select.i, %n.vec
  %87 = getelementptr i8, ptr %input.0, i64 %_29.0.i
  %88 = getelementptr [4 x i8], ptr %out.0, i64 %nt.sroa.0.3.i2111
  br label %vector.body

vector.body:                                      ; preds = %vector.body, %vector.ph
  %index = phi i64 [ 0, %vector.ph ], [ %index.next, %vector.body ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2652)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2655)
  %89 = getelementptr i8, ptr %87, i64 %index
  %90 = getelementptr inbounds nuw i8, ptr %89, i64 4
  %wide.load = load <4 x i8>, ptr %89, align 1, !alias.scope !2652, !noalias !2655
  %wide.load2717 = load <4 x i8>, ptr %90, align 1, !alias.scope !2652, !noalias !2655
  %91 = getelementptr [4 x i8], ptr %88, i64 %index
  %92 = zext <4 x i8> %wide.load to <4 x i32>
  %93 = zext <4 x i8> %wide.load2717 to <4 x i32>
  %94 = getelementptr inbounds nuw i8, ptr %91, i64 16
  store <4 x i32> %92, ptr %91, align 4, !alias.scope !2655, !noalias !2652
  store <4 x i32> %93, ptr %94, align 4, !alias.scope !2655, !noalias !2652
  %index.next = add nuw i64 %index, 8
  %95 = icmp eq i64 %index.next, %n.vec
  br i1 %95, label %bb164.i.preheader2744, label %vector.body, !llvm.loop !2657

panic5.i:                                         ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit170
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_6c101138787766aed78cb0daf47995e1) #13
  unreachable

bb170.i:                                          ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit161, %bb157.i
  %p.sroa.0.3.i.lcssa = phi i64 [ %_29.0.i, %bb157.i ], [ %_231.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit161 ]
  %nt.sroa.0.3.i.lcssa = phi i64 [ %nt.sroa.0.3.i2111, %bb157.i ], [ %nt.sroa.0.3.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit161 ]
  %spec.select.i = tail call i64 @llvm.umax.i64(i64 %_29.0.i, i64 %p.sroa.0.3.i.lcssa)
  br label %bb174.i

bb164.i:                                          ; preds = %bb164.i.preheader2744, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit161
  %nt.sroa.0.3.i2117 = phi i64 [ %nt.sroa.0.3.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit161 ], [ %nt.sroa.0.3.i2117.ph, %bb164.i.preheader2744 ]
  %p.sroa.0.3.i2116 = phi i64 [ %_231.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit161 ], [ %p.sroa.0.3.i2116.ph, %bb164.i.preheader2744 ]
  %step.sroa.0.0.i2115 = phi i64 [ %_232.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit161 ], [ %step.sroa.0.0.i2115.ph, %bb164.i.preheader2744 ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2652)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2655)
  %exitcond2323.not = icmp eq i64 %nt.sroa.0.3.i2117, %out.1
  br i1 %exitcond2323.not, label %panic1.i157, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit161

panic1.i157:                                      ; preds = %bb164.i
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %out.1, i64 noundef range(i64 0, 2305843009213693952) %out.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_ce72d480401e07b7a290039044612259) #13, !noalias !2658
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit161: ; preds = %bb164.i
  %96 = getelementptr inbounds nuw i8, ptr %input.0, i64 %p.sroa.0.3.i2116
  %_5.i159 = load i8, ptr %96, align 1, !alias.scope !2652, !noalias !2655, !noundef !135
  %97 = getelementptr inbounds nuw [4 x i8], ptr %out.0, i64 %nt.sroa.0.3.i2117
  %98 = zext i8 %_5.i159 to i32
  store i32 %98, ptr %97, align 4, !alias.scope !2655, !noalias !2652
  %_231.0.i = add nuw nsw i64 %p.sroa.0.3.i2116, 1
  %_232.0.i = add nsw i64 %step.sroa.0.0.i2115, -1
  %nt.sroa.0.3.i = add i64 %nt.sroa.0.3.i2117, 1
  %_225.i = icmp ne i64 %_232.0.i, 0
  %_227.i = icmp ult i64 %_231.0.i, %_8.0.i
  %or.cond45.i = select i1 %_225.i, i1 %_227.i, i1 false
  br i1 %or.cond45.i, label %bb164.i, label %bb170.i, !llvm.loop !2659

bb174.i:                                          ; preds = %bb150.i, %bb170.i
  %ins.sroa.0.3.i = phi i64 [ %spec.select140.i, %bb150.i ], [ %spec.select.i, %bb170.i ]
  %p.sroa.0.4.i = phi i64 [ %_19.0.i185, %bb150.i ], [ %p.sroa.0.3.i.lcssa, %bb170.i ]
  %miss.sroa.0.1.i = phi i64 [ 0, %bb150.i ], [ %_219.0.i, %bb170.i ]
  %nt.sroa.0.4.i = phi i64 [ %_17.0.i, %bb150.i ], [ %nt.sroa.0.3.i.lcssa, %bb170.i ]
  %_11.i = icmp ult i64 %p.sroa.0.4.i, %_8.0.i
  %_13.i = icmp ne i64 %_15.0.i, 0
  %or.cond.i = select i1 %_11.i, i1 %_13.i, i1 false
  br i1 %or.cond.i, label %bb5.i, label %bb177.i

bb18.i:                                           ; preds = %bb18.i.preheader, %bb59.i
  %indvars.iv = phi i64 [ %62, %bb18.i.preheader ], [ %indvars.iv.next, %bb59.i ]
  %nt.sroa.0.5.i2138 = phi i64 [ %nt.sroa.0.1.i2179, %bb18.i.preheader ], [ %_10.0.i152, %bb59.i ]
  %l.sroa.0.0.i2137 = phi i64 [ %have.sroa.0.1.i2335, %bb18.i.preheader ], [ %k.sroa.0.2.i.lcssa, %bb59.i ]
  %d.sroa.0.0.i2136 = phi i64 [ %bd.sroa.0.1.i2334, %bb18.i.preheader ], [ %d.i37, %bb59.i ]
  %p.sroa.0.5.i2135 = phi i64 [ %p.sroa.0.1.i2176.fr, %bb18.i.preheader ], [ %_44.0.i, %bb59.i ]
  %umin = call i64 @llvm.umin.i64(i64 %indvars.iv, i64 258)
  %99 = and i64 %umin, 504
  %_44.0.i = add i64 %p.sroa.0.5.i2135, 1
  %_41.i = icmp ult i64 %_44.0.i, %_8.0.i
  br i1 %_41.i, label %bb21.i, label %bb63.i

bb63.i.loopexit.split.loop.exit2819:              ; preds = %bb59.i
  %p.sroa.0.5.i2135.lcssa2880 = phi i64 [ %p.sroa.0.5.i2135, %bb59.i ]
  %p.sroa.0.5.i.lcssa.ph.ph2821 = phi i64 [ %_44.0.i, %bb59.i ]
  %d.sroa.0.0.i.lcssa.ph.ph2822 = phi i64 [ %d.i37, %bb59.i ]
  %l.sroa.0.0.i.lcssa.ph.ph2823 = phi i64 [ %k.sroa.0.2.i.lcssa, %bb59.i ]
  %nt.sroa.0.5.i.lcssa.ph.ph2824 = phi i64 [ %_10.0.i152, %bb59.i ]
  %_51.0.i.le2879 = add nuw nsw i64 %p.sroa.0.5.i2135.lcssa2880, 2
  br label %bb63.i

bb63.i.loopexit.split.loop.exit2825:              ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit671
  %p.sroa.0.5.i2135.lcssa2878 = phi i64 [ %p.sroa.0.5.i2135, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit671 ]
  %d.sroa.0.0.i.lcssa.ph.ph2828 = phi i64 [ %d.sroa.0.0.i2136, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit671 ]
  %l.sroa.0.0.i.lcssa.ph.ph2829 = phi i64 [ %l.sroa.0.0.i2137, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit671 ]
  %nt.sroa.0.5.i.lcssa.ph.ph2830 = phi i64 [ %nt.sroa.0.5.i2138, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit671 ]
  %_51.0.i.le2877 = add nuw nsw i64 %p.sroa.0.5.i2135.lcssa2878, 2
  br label %bb63.i

bb63.i.loopexit.split.loop.exit2831:              ; preds = %bb11.i36
  %p.sroa.0.5.i2135.lcssa2876 = phi i64 [ %p.sroa.0.5.i2135, %bb11.i36 ]
  %d.sroa.0.0.i.lcssa.ph.ph2834 = phi i64 [ %d.sroa.0.0.i2136, %bb11.i36 ]
  %l.sroa.0.0.i.lcssa.ph.ph2835 = phi i64 [ %l.sroa.0.0.i2137, %bb11.i36 ]
  %nt.sroa.0.5.i.lcssa.ph.ph2836 = phi i64 [ %nt.sroa.0.5.i2138, %bb11.i36 ]
  %_51.0.i.le2875 = add nuw nsw i64 %p.sroa.0.5.i2135.lcssa2876, 2
  br label %bb63.i

bb63.i.loopexit.split.loop.exit2837:              ; preds = %bb13.i50
  %p.sroa.0.5.i2135.lcssa2874 = phi i64 [ %p.sroa.0.5.i2135, %bb13.i50 ]
  %d.sroa.0.0.i.lcssa.ph.ph2840 = phi i64 [ %d.sroa.0.0.i2136, %bb13.i50 ]
  %l.sroa.0.0.i.lcssa.ph.ph2841 = phi i64 [ %l.sroa.0.0.i2137, %bb13.i50 ]
  %nt.sroa.0.5.i.lcssa.ph.ph2842 = phi i64 [ %nt.sroa.0.5.i2138, %bb13.i50 ]
  %_51.0.i.le2873 = add nuw nsw i64 %p.sroa.0.5.i2135.lcssa2874, 2
  br label %bb63.i

bb63.i.loopexit.split.loop.exit2843:              ; preds = %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit80
  %p.sroa.0.5.i2135.lcssa2872 = phi i64 [ %p.sroa.0.5.i2135, %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit80 ]
  %d.sroa.0.0.i.lcssa.ph.ph2846 = phi i64 [ %d.sroa.0.0.i2136, %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit80 ]
  %l.sroa.0.0.i.lcssa.ph.ph2847 = phi i64 [ %l.sroa.0.0.i2137, %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit80 ]
  %nt.sroa.0.5.i.lcssa.ph.ph2848 = phi i64 [ %nt.sroa.0.5.i2138, %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit80 ]
  %_51.0.i.le2871 = add nuw nsw i64 %p.sroa.0.5.i2135.lcssa2872, 2
  br label %bb63.i

bb63.i.loopexit.split.loop.exit2849:              ; preds = %bb16.i52
  %p.sroa.0.5.i2135.lcssa2870 = phi i64 [ %p.sroa.0.5.i2135, %bb16.i52 ]
  %d.sroa.0.0.i.lcssa.ph.ph2852 = phi i64 [ %d.sroa.0.0.i2136, %bb16.i52 ]
  %l.sroa.0.0.i.lcssa.ph.ph2853 = phi i64 [ %l.sroa.0.0.i2137, %bb16.i52 ]
  %nt.sroa.0.5.i.lcssa.ph.ph2854 = phi i64 [ %nt.sroa.0.5.i2138, %bb16.i52 ]
  %_51.0.i.le2869 = add nuw nsw i64 %p.sroa.0.5.i2135.lcssa2870, 2
  br label %bb63.i

bb63.i.loopexit.split.loop.exit2855:              ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit
  %p.sroa.0.5.i2135.lcssa2868 = phi i64 [ %p.sroa.0.5.i2135, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit ]
  %d.sroa.0.0.i.lcssa.ph.ph2858 = phi i64 [ %d.sroa.0.0.i2136, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit ]
  %l.sroa.0.0.i.lcssa.ph.ph2859 = phi i64 [ %l.sroa.0.0.i2137, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit ]
  %nt.sroa.0.5.i.lcssa.ph.ph2860 = phi i64 [ %nt.sroa.0.5.i2138, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit ]
  %_51.0.i.le2867 = add nuw nsw i64 %p.sroa.0.5.i2135.lcssa2868, 2
  br label %bb63.i

bb63.i.loopexit.split.loop.exit2861:              ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit
  %p.sroa.0.5.i2135.lcssa = phi i64 [ %p.sroa.0.5.i2135, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit ]
  %d.sroa.0.0.i.lcssa.ph.ph2864 = phi i64 [ %d.sroa.0.0.i2136, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit ]
  %l.sroa.0.0.i.lcssa.ph.ph2865 = phi i64 [ %l.sroa.0.0.i2137, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit ]
  %nt.sroa.0.5.i.lcssa.ph.ph2866 = phi i64 [ %nt.sroa.0.5.i2138, %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit ]
  %_51.0.i.le = add nuw nsw i64 %p.sroa.0.5.i2135.lcssa, 2
  br label %bb63.i

bb63.i:                                           ; preds = %bb63.i.loopexit.split.loop.exit2819, %bb63.i.loopexit.split.loop.exit2825, %bb63.i.loopexit.split.loop.exit2831, %bb63.i.loopexit.split.loop.exit2837, %bb63.i.loopexit.split.loop.exit2843, %bb63.i.loopexit.split.loop.exit2849, %bb63.i.loopexit.split.loop.exit2855, %bb63.i.loopexit.split.loop.exit2861, %bb18.i, %bb16.i.preheader
  %ins.sroa.0.4.i.lcssa = phi i64 [ %_29.0.i, %bb16.i.preheader ], [ %_51.0.i.le2873, %bb63.i.loopexit.split.loop.exit2837 ], [ %_51.0.i.le2875, %bb63.i.loopexit.split.loop.exit2831 ], [ %_51.0.i.le2877, %bb63.i.loopexit.split.loop.exit2825 ], [ %_51.0.i.le, %bb63.i.loopexit.split.loop.exit2861 ], [ %_51.0.i.le2879, %bb63.i.loopexit.split.loop.exit2819 ], [ %_51.0.i.le2867, %bb63.i.loopexit.split.loop.exit2855 ], [ %_51.0.i.le2871, %bb63.i.loopexit.split.loop.exit2843 ], [ %_51.0.i.le2869, %bb63.i.loopexit.split.loop.exit2849 ], [ %umax2713, %bb18.i ]
  %p.sroa.0.5.i.lcssa = phi i64 [ %p.sroa.0.1.i2176.fr, %bb16.i.preheader ], [ %p.sroa.0.5.i2135.lcssa2874, %bb63.i.loopexit.split.loop.exit2837 ], [ %p.sroa.0.5.i2135.lcssa2876, %bb63.i.loopexit.split.loop.exit2831 ], [ %p.sroa.0.5.i2135.lcssa2878, %bb63.i.loopexit.split.loop.exit2825 ], [ %p.sroa.0.5.i2135.lcssa, %bb63.i.loopexit.split.loop.exit2861 ], [ %p.sroa.0.5.i.lcssa.ph.ph2821, %bb63.i.loopexit.split.loop.exit2819 ], [ %p.sroa.0.5.i2135.lcssa2868, %bb63.i.loopexit.split.loop.exit2855 ], [ %p.sroa.0.5.i2135.lcssa2872, %bb63.i.loopexit.split.loop.exit2843 ], [ %p.sroa.0.5.i2135.lcssa2870, %bb63.i.loopexit.split.loop.exit2849 ], [ %p.sroa.0.5.i2135, %bb18.i ]
  %d.sroa.0.0.i.lcssa = phi i64 [ %bd.sroa.0.1.i2334, %bb16.i.preheader ], [ %d.sroa.0.0.i.lcssa.ph.ph2840, %bb63.i.loopexit.split.loop.exit2837 ], [ %d.sroa.0.0.i.lcssa.ph.ph2834, %bb63.i.loopexit.split.loop.exit2831 ], [ %d.sroa.0.0.i.lcssa.ph.ph2828, %bb63.i.loopexit.split.loop.exit2825 ], [ %d.sroa.0.0.i.lcssa.ph.ph2864, %bb63.i.loopexit.split.loop.exit2861 ], [ %d.sroa.0.0.i.lcssa.ph.ph2822, %bb63.i.loopexit.split.loop.exit2819 ], [ %d.sroa.0.0.i.lcssa.ph.ph2858, %bb63.i.loopexit.split.loop.exit2855 ], [ %d.sroa.0.0.i.lcssa.ph.ph2846, %bb63.i.loopexit.split.loop.exit2843 ], [ %d.sroa.0.0.i.lcssa.ph.ph2852, %bb63.i.loopexit.split.loop.exit2849 ], [ %d.sroa.0.0.i2136, %bb18.i ]
  %l.sroa.0.0.i.lcssa = phi i64 [ %have.sroa.0.1.i2335, %bb16.i.preheader ], [ %l.sroa.0.0.i.lcssa.ph.ph2841, %bb63.i.loopexit.split.loop.exit2837 ], [ %l.sroa.0.0.i.lcssa.ph.ph2835, %bb63.i.loopexit.split.loop.exit2831 ], [ %l.sroa.0.0.i.lcssa.ph.ph2829, %bb63.i.loopexit.split.loop.exit2825 ], [ %l.sroa.0.0.i.lcssa.ph.ph2865, %bb63.i.loopexit.split.loop.exit2861 ], [ %l.sroa.0.0.i.lcssa.ph.ph2823, %bb63.i.loopexit.split.loop.exit2819 ], [ %l.sroa.0.0.i.lcssa.ph.ph2859, %bb63.i.loopexit.split.loop.exit2855 ], [ %l.sroa.0.0.i.lcssa.ph.ph2847, %bb63.i.loopexit.split.loop.exit2843 ], [ %l.sroa.0.0.i.lcssa.ph.ph2853, %bb63.i.loopexit.split.loop.exit2849 ], [ %l.sroa.0.0.i2137, %bb18.i ]
  %nt.sroa.0.5.i.lcssa = phi i64 [ %nt.sroa.0.1.i2179, %bb16.i.preheader ], [ %nt.sroa.0.5.i.lcssa.ph.ph2842, %bb63.i.loopexit.split.loop.exit2837 ], [ %nt.sroa.0.5.i.lcssa.ph.ph2836, %bb63.i.loopexit.split.loop.exit2831 ], [ %nt.sroa.0.5.i.lcssa.ph.ph2830, %bb63.i.loopexit.split.loop.exit2825 ], [ %nt.sroa.0.5.i.lcssa.ph.ph2866, %bb63.i.loopexit.split.loop.exit2861 ], [ %nt.sroa.0.5.i.lcssa.ph.ph2824, %bb63.i.loopexit.split.loop.exit2819 ], [ %nt.sroa.0.5.i.lcssa.ph.ph2860, %bb63.i.loopexit.split.loop.exit2855 ], [ %nt.sroa.0.5.i.lcssa.ph.ph2848, %bb63.i.loopexit.split.loop.exit2843 ], [ %nt.sroa.0.5.i.lcssa.ph.ph2854, %bb63.i.loopexit.split.loop.exit2849 ], [ %nt.sroa.0.5.i2138, %bb18.i ]
  %100 = add i64 %nt.sroa.0.5.i.lcssa, -1
  %101 = icmp ult i64 %100, %out.1
  %_110.i2153 = icmp ult i64 %l.sroa.0.0.i.lcssa, 258
  %or.cond49.i2154 = select i1 %101, i1 %_110.i2153, i1 false
  %_112.i2155 = icmp ult i64 %d.sroa.0.0.i.lcssa, %p.sroa.0.5.i.lcssa
  %or.cond139.i2156 = and i1 %or.cond49.i2154, %_112.i2155
  br i1 %or.cond139.i2156, label %bb71.i, label %bb116.i

bb21.i:                                           ; preds = %bb18.i
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2660)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2663)
  %102 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_44.0.i
  %103 = getelementptr inbounds nuw i8, ptr %input.0, i64 %p.sroa.0.5.i2135
  %104 = load i32, ptr %102, align 1
  %105 = call i32 @llvm.bswap.i32(i32 %104)
  %106 = zext i32 %105 to i64
  %107 = mul i64 %106, -7046029254386353131
  %108 = lshr i64 %107, 48
  %109 = getelementptr inbounds nuw [4 x i8], ptr %head.i, i64 %108
  %old.i166.i = load i32, ptr %109, align 4, !alias.scope !2660, !noalias !2665, !noundef !135
  %_16.i167.i = and i64 %_44.0.i, 32767
  %110 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_16.i167.i
  store i32 %old.i166.i, ptr %110, align 4, !alias.scope !2663, !noalias !2667
  %111 = trunc i64 %_44.0.i to i32
  store i32 %111, ptr %109, align 4, !alias.scope !2660, !noalias !2665
  %_0.i168.i = zext i32 %old.i166.i to i64
  %_56.0.i = add nsw i64 %l.sroa.0.0.i2137, -1
  %spec.select.i3 = tail call i64 @llvm.umax.i64(i64 %_56.0.i, i64 3)
  %_13.0.i = sub nuw nsw i64 %input.1, %_44.0.i
  %spec.store.select3.i = tail call i64 @llvm.umin.i64(i64 %_13.0.i, i64 258)
  %_19.0.i24 = add nuw i64 %spec.select.i3, %_44.0.i
  %_16.i25 = icmp ult i64 %_19.0.i24, %input.1
  br i1 %_16.i25, label %bb7.i79, label %bb11.i36

bb7.i79:                                          ; preds = %bb21.i
  %112 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_19.0.i24
  %113 = load i8, ptr %112, align 1, !alias.scope !2668, !noalias !2671, !noundef !135
  br label %bb11.i36

bb11.i36:                                         ; preds = %bb21.i, %bb7.i79
  %pb.sroa.0.0.i27 = phi i8 [ %113, %bb7.i79 ], [ 0, %bb21.i ]
  %d.i37 = sub nsw i64 %_44.0.i, %_0.i168.i
  %_29.i38 = add nsw i64 %d.i37, -1
  %_28.i39 = icmp ult i64 %_29.i38, 32768
  br i1 %_28.i39, label %bb13.i50, label %bb63.i.loopexit.split.loop.exit2831

bb13.i50:                                         ; preds = %bb11.i36
  %_34.0.i48 = add nuw nsw i64 %spec.select.i3, %_0.i168.i
  %_30.i51 = icmp ult i64 %_34.0.i48, %input.1
  br i1 %_30.i51, label %bb16.i52, label %bb63.i.loopexit.split.loop.exit2837

bb16.i52:                                         ; preds = %bb13.i50
  %114 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_34.0.i48
  %_36.i53 = load i8, ptr %114, align 1, !alias.scope !2668, !noalias !2671, !noundef !135
  %_35.i54 = icmp eq i8 %_36.i53, %pb.sroa.0.0.i27
  br i1 %_35.i54, label %bb2.i, label %bb63.i.loopexit.split.loop.exit2849

bb2.i:                                            ; preds = %bb16.i52, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit561
  %k.sroa.0.0.i2121 = phi i64 [ %_10.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit561 ], [ 0, %bb16.i52 ]
  %_10.0.i = add nuw nsw i64 %k.sroa.0.0.i2121, 8
  %_7.not.i = icmp samesign ugt i64 %_10.0.i, %spec.store.select3.i
  br i1 %_7.not.i, label %bb15.i82, label %bb4.i

bb4.i:                                            ; preds = %bb2.i
  %_13.i92 = add nuw nsw i64 %k.sroa.0.0.i2121, %_0.i168.i
  %_5.0.i564 = add nuw nsw i64 %_13.i92, 8
  %_3.not.i565 = icmp samesign ugt i64 %_5.0.i564, %input.1
  br i1 %_3.not.i565, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit629, label %bb2.i566

bb2.i566:                                         ; preds = %bb4.i
  %115 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_13.i92
  %_15.i = load i8, ptr %115, align 1, !alias.scope !2673, !noalias !2671, !noundef !135
  %_14.i570 = zext i8 %_15.i to i64
  %_13.i571 = shl nuw i64 %_14.i570, 56
  %116 = getelementptr inbounds nuw i8, ptr %115, i64 1
  %_19.i576 = load i8, ptr %116, align 1, !alias.scope !2673, !noalias !2671, !noundef !135
  %_18.i577 = zext i8 %_19.i576 to i64
  %_17.i578 = shl nuw nsw i64 %_18.i577, 48
  %_12.i579 = or disjoint i64 %_17.i578, %_13.i571
  %117 = getelementptr inbounds nuw i8, ptr %115, i64 2
  %_25.i584 = load i8, ptr %117, align 1, !alias.scope !2673, !noalias !2671, !noundef !135
  %_24.i585 = zext i8 %_25.i584 to i64
  %_23.i586 = shl nuw nsw i64 %_24.i585, 40
  %_11.i587 = or disjoint i64 %_12.i579, %_23.i586
  %118 = getelementptr inbounds nuw i8, ptr %115, i64 3
  %_31.i592 = load i8, ptr %118, align 1, !alias.scope !2673, !noalias !2671, !noundef !135
  %_30.i593 = zext i8 %_31.i592 to i64
  %_29.i594 = shl nuw nsw i64 %_30.i593, 32
  %_10.i595 = or disjoint i64 %_11.i587, %_29.i594
  %119 = getelementptr inbounds nuw i8, ptr %115, i64 4
  %_37.i600 = load i8, ptr %119, align 1, !alias.scope !2673, !noalias !2671, !noundef !135
  %_36.i601 = zext i8 %_37.i600 to i64
  %_35.i602 = shl nuw nsw i64 %_36.i601, 24
  %_9.i603 = or disjoint i64 %_10.i595, %_35.i602
  %120 = getelementptr inbounds nuw i8, ptr %115, i64 5
  %_43.i608 = load i8, ptr %120, align 1, !alias.scope !2673, !noalias !2671, !noundef !135
  %_42.i609 = zext i8 %_43.i608 to i64
  %_41.i610 = shl nuw nsw i64 %_42.i609, 16
  %_8.i611 = or disjoint i64 %_9.i603, %_41.i610
  %121 = getelementptr inbounds nuw i8, ptr %115, i64 6
  %_49.i616 = load i8, ptr %121, align 1, !alias.scope !2673, !noalias !2671, !noundef !135
  %_48.i617 = zext i8 %_49.i616 to i64
  %_47.i618 = shl nuw nsw i64 %_48.i617, 8
  %_7.i619 = or i64 %_8.i611, %_47.i618
  %122 = getelementptr inbounds nuw i8, ptr %115, i64 7
  %_54.i624 = load i8, ptr %122, align 1, !alias.scope !2673, !noalias !2671, !noundef !135
  %_53.i625 = zext i8 %_54.i624 to i64
  %123 = or i64 %_7.i619, %_53.i625
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit629

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit629: ; preds = %bb4.i, %bb2.i566
  %_0.sroa.0.0.i627 = phi i64 [ %123, %bb2.i566 ], [ 0, %bb4.i ]
  %_16.i93 = add nuw i64 %k.sroa.0.0.i2121, %_44.0.i
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2676)
  %_5.1.i493 = icmp ugt i64 %_16.i93, -9
  br i1 %_5.1.i493, label %panic.i560, label %bb1.i494

bb1.i494:                                         ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit629
  %_5.0.i495 = add nuw i64 %_16.i93, 8
  %_3.not.i496 = icmp ugt i64 %_5.0.i495, %input.1
  br i1 %_3.not.i496, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit561, label %bb2.i497

panic.i560:                                       ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit629
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_bb314acf14069c2fbedf530b060ebd60) #13, !noalias !2679
  unreachable

bb2.i497:                                         ; preds = %bb1.i494
  %124 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_16.i93
  %_15.i501 = load i8, ptr %124, align 1, !alias.scope !2676, !noalias !2671, !noundef !135
  %_14.i502 = zext i8 %_15.i501 to i64
  %_13.i503 = shl nuw i64 %_14.i502, 56
  %125 = getelementptr inbounds nuw i8, ptr %124, i64 1
  %_19.i508 = load i8, ptr %125, align 1, !alias.scope !2676, !noalias !2671, !noundef !135
  %_18.i509 = zext i8 %_19.i508 to i64
  %_17.i510 = shl nuw nsw i64 %_18.i509, 48
  %_12.i511 = or disjoint i64 %_17.i510, %_13.i503
  %126 = getelementptr inbounds nuw i8, ptr %124, i64 2
  %_25.i516 = load i8, ptr %126, align 1, !alias.scope !2676, !noalias !2671, !noundef !135
  %_24.i517 = zext i8 %_25.i516 to i64
  %_23.i518 = shl nuw nsw i64 %_24.i517, 40
  %_11.i519 = or disjoint i64 %_12.i511, %_23.i518
  %127 = getelementptr inbounds nuw i8, ptr %124, i64 3
  %_31.i524 = load i8, ptr %127, align 1, !alias.scope !2676, !noalias !2671, !noundef !135
  %_30.i525 = zext i8 %_31.i524 to i64
  %_29.i526 = shl nuw nsw i64 %_30.i525, 32
  %_10.i527 = or disjoint i64 %_11.i519, %_29.i526
  %128 = getelementptr inbounds nuw i8, ptr %124, i64 4
  %_37.i532 = load i8, ptr %128, align 1, !alias.scope !2676, !noalias !2671, !noundef !135
  %_36.i533 = zext i8 %_37.i532 to i64
  %_35.i534 = shl nuw nsw i64 %_36.i533, 24
  %_9.i535 = or disjoint i64 %_10.i527, %_35.i534
  %129 = getelementptr inbounds nuw i8, ptr %124, i64 5
  %_43.i540 = load i8, ptr %129, align 1, !alias.scope !2676, !noalias !2671, !noundef !135
  %_42.i541 = zext i8 %_43.i540 to i64
  %_41.i542 = shl nuw nsw i64 %_42.i541, 16
  %_8.i543 = or disjoint i64 %_9.i535, %_41.i542
  %130 = getelementptr inbounds nuw i8, ptr %124, i64 6
  %_49.i548 = load i8, ptr %130, align 1, !alias.scope !2676, !noalias !2671, !noundef !135
  %_48.i549 = zext i8 %_49.i548 to i64
  %_47.i550 = shl nuw nsw i64 %_48.i549, 8
  %_7.i551 = or i64 %_8.i543, %_47.i550
  %131 = getelementptr inbounds nuw i8, ptr %124, i64 7
  %_54.i556 = load i8, ptr %131, align 1, !alias.scope !2676, !noalias !2671, !noundef !135
  %_53.i557 = zext i8 %_54.i556 to i64
  %132 = or i64 %_7.i551, %_53.i557
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit561

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit561: ; preds = %bb1.i494, %bb2.i497
  %_0.sroa.0.0.i559 = phi i64 [ %132, %bb2.i497 ], [ 0, %bb1.i494 ]
  %133 = icmp eq i64 %_0.sroa.0.0.i627, %_0.sroa.0.0.i559
  br i1 %133, label %bb2.i, label %bb15.i82.thread

bb15.i82:                                         ; preds = %bb2.i
  %_24.i2122 = icmp samesign ult i64 %99, %spec.store.select3.i
  br i1 %_24.i2122, label %bb18.i86, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit

bb15.i82.thread:                                  ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit561
  %_0.sroa.0.0.i559.lcssa = phi i64 [ %_0.sroa.0.0.i559, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit561 ]
  %_0.sroa.0.0.i627.lcssa2756 = phi i64 [ %_0.sroa.0.0.i627, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit561 ]
  %k.sroa.0.0.i2121.lcssa2755 = phi i64 [ %k.sroa.0.0.i2121, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit561 ]
  %x.i = xor i64 %_0.sroa.0.0.i559.lcssa, %_0.sroa.0.0.i627.lcssa2756
  %134 = tail call range(i64 0, 65) i64 @llvm.ctlz.i64(i64 %x.i, i1 true)
  %_2018.i = lshr i64 %134, 3
  %_22.0.i = or disjoint i64 %_2018.i, %k.sroa.0.0.i2121.lcssa2755
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit

bb18.i86:                                         ; preds = %bb15.i82, %bb22.i
  %k.sroa.0.2.i2124 = phi i64 [ %k.sroa.0.3.i, %bb22.i ], [ %99, %bb15.i82 ]
  %_30.0.i = add i64 %k.sroa.0.2.i2124, %_0.i168.i
  %_30.1.i = icmp ult i64 %_30.0.i, %_0.i168.i
  br i1 %_30.1.i, label %panic3.i, label %bb19.i87

bb19.i87:                                         ; preds = %bb18.i86
  %_32.i = icmp ult i64 %_30.0.i, %input.1
  br i1 %_32.i, label %bb20.i, label %panic4.i88

panic3.i:                                         ; preds = %bb18.i86
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_ff83526048c448fdb7f174b76564f0a2) #13, !noalias !2671
  unreachable

bb20.i:                                           ; preds = %bb19.i87
  %135 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_30.0.i
  %_27.i = load i8, ptr %135, align 1, !alias.scope !2680, !noalias !2671, !noundef !135
  %_36.0.i = add i64 %k.sroa.0.2.i2124, %_44.0.i
  %_36.1.i.not = icmp ugt i64 %_36.0.i, %p.sroa.0.5.i2135
  br i1 %_36.1.i.not, label %bb21.i89, label %panic5.i90

panic4.i88:                                       ; preds = %bb19.i87
  %_30.0.i.lcssa2757 = phi i64 [ %_30.0.i, %bb19.i87 ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_30.0.i.lcssa2757, i64 noundef range(i64 0, -9223372036854775808) %input.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_333f7815cbdde125b13aaef2eac5916c) #13, !noalias !2671
  unreachable

bb21.i89:                                         ; preds = %bb20.i
  %_37.i = icmp ult i64 %_36.0.i, %input.1
  br i1 %_37.i, label %bb22.i, label %panic6.i

panic5.i90:                                       ; preds = %bb20.i
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_44247feb933c63f72105b72612a623ee) #13, !noalias !2671
  unreachable

bb22.i:                                           ; preds = %bb21.i89
  %136 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_36.0.i
  %_33.i = load i8, ptr %136, align 1, !alias.scope !2680, !noalias !2671, !noundef !135
  %_26.i = icmp eq i8 %_27.i, %_33.i
  %_38.0.i = zext i1 %_26.i to i64
  %k.sroa.0.3.i = add nuw i64 %k.sroa.0.2.i2124, %_38.0.i
  %_24.i = icmp ult i64 %k.sroa.0.3.i, %spec.store.select3.i
  %or.cond.i84 = select i1 %_26.i, i1 %_24.i, i1 false
  br i1 %or.cond.i84, label %bb18.i86, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit

panic6.i:                                         ; preds = %bb21.i89
  %_36.0.i.lcssa2761 = phi i64 [ %_36.0.i, %bb21.i89 ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_36.0.i.lcssa2761, i64 noundef range(i64 0, -9223372036854775808) %input.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_c7b835eab7e4664f8dc21896c854bf2b) #13, !noalias !2671
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit: ; preds = %bb22.i, %bb15.i82.thread, %bb15.i82
  %k.sroa.0.2.i.lcssa = phi i64 [ %99, %bb15.i82 ], [ %_22.0.i, %bb15.i82.thread ], [ %k.sroa.0.3.i, %bb22.i ]
  %_46.i68 = icmp ugt i64 %k.sroa.0.2.i.lcssa, %spec.select.i3
  br i1 %_46.i68, label %bb19.i69, label %bb63.i.loopexit.split.loop.exit2861

bb19.i69:                                         ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse11u118_common.exit
  %137 = add i64 %k.sroa.0.2.i.lcssa, -11
  %or.cond.i630 = icmp ult i64 %137, 247
  br i1 %or.cond.i630, label %bb6.i, label %bb7.i631

bb7.i631:                                         ; preds = %bb6.i, %bb19.i69
  %c.sroa.0.0.i = phi i32 [ %140, %bb6.i ], [ 168, %bb19.i69 ]
  %_17.i632 = icmp ugt i64 %d.i37, 4
  br i1 %_17.i632, label %bb12.i641, label %bb13.i633

bb6.i:                                            ; preds = %bb19.i69
  %138 = trunc nuw nsw i64 %k.sroa.0.2.i.lcssa to i32
  %_11.i644 = add nsw i32 %138, -3
  %_10.i645 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_11.i644, i1 false)
  %139 = shl nuw nsw i32 %_10.i645, 4
  %140 = sub nuw nsw i32 632, %139
  br label %bb7.i631

bb13.i633:                                        ; preds = %bb12.i641, %bb7.i631
  %c.sroa.0.1.i = phi i32 [ %144, %bb12.i641 ], [ %c.sroa.0.0.i, %bb7.i631 ]
  %_29.i634 = trunc i64 %k.sroa.0.2.i.lcssa to i32
  %141 = add i32 %_29.i634, -33554432
  %_30.1.i635 = icmp ult i32 %141, -67108864
  br i1 %_30.1.i635, label %panic8.i, label %bb14.i

bb12.i641:                                        ; preds = %bb7.i631
  %142 = trunc nuw i64 %d.i37 to i32
  %_22.i640 = add nsw i32 %142, -1
  %_21.i642 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_22.i640, i1 true)
  %143 = shl nuw nsw i32 %_21.i642, 4
  %reass.sub = sub nsw i32 %c.sroa.0.0.i, %143
  %144 = add nsw i32 %reass.sub, 480
  br label %bb13.i633

bb14.i:                                           ; preds = %bb13.i633
  %_30.0.i636 = shl nsw i32 %_29.i634, 6
  %145 = tail call { i32, i1 } @llvm.ssub.with.overflow.i32(i32 %_30.0.i636, i32 %c.sroa.0.1.i)
  %_31.1.i = extractvalue { i32, i1 } %145, 1
  br i1 %_31.1.i, label %panic9.i638, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit

panic8.i:                                         ; preds = %bb13.i633
; call core::panicking::panic_const::panic_const_mul_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_mul_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_72bac528c0514d634dbb2acaf4e914ed) #13, !noalias !2671
  unreachable

panic9.i638:                                      ; preds = %bb14.i
; call core::panicking::panic_const::panic_const_sub_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_72bac528c0514d634dbb2acaf4e914ed) #13, !noalias !2671
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit: ; preds = %bb14.i
  %_31.0.i = extractvalue { i32, i1 } %145, 0
  %_49.i = icmp sgt i32 %_31.0.i, -1000000
  br i1 %_49.i, label %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit80, label %bb63.i.loopexit.split.loop.exit2855

_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit80: ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit
  %.not2742 = icmp eq i64 %d.i37, 0
  br i1 %.not2742, label %bb63.i.loopexit.split.loop.exit2843, label %bb29.i

bb29.i:                                           ; preds = %_RINvNtCs2hd9JHJjR4I_9candidate5parse9u118_walkKj8000_EB4_.exit80
  br i1 %or.cond.i630, label %bb6.i694, label %bb7.i673

bb7.i673:                                         ; preds = %bb6.i694, %bb29.i
  %c.sroa.0.0.i674 = phi i32 [ %147, %bb6.i694 ], [ 168, %bb29.i ]
  %_17.i675 = icmp ugt i64 %d.i37, 4
  br i1 %_17.i675, label %bb12.i690, label %bb14.i680

bb6.i694:                                         ; preds = %bb29.i
  %_11.i695 = add nsw i32 %_29.i634, -3
  %_10.i696 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_11.i695, i1 false)
  %146 = shl nuw nsw i32 %_10.i696, 4
  %147 = sub nuw nsw i32 632, %146
  br label %bb7.i673

bb12.i690:                                        ; preds = %bb7.i673
  %148 = trunc nuw i64 %d.i37 to i32
  %_22.i688 = add nsw i32 %148, -1
  %_21.i691 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_22.i688, i1 true)
  %149 = shl nuw nsw i32 %_21.i691, 4
  %reass.sub2187 = sub nsw i32 %c.sroa.0.0.i674, %149
  %150 = add nsw i32 %reass.sub2187, 480
  br label %bb14.i680

bb14.i680:                                        ; preds = %bb7.i673, %bb12.i690
  %c.sroa.0.1.i677 = phi i32 [ %150, %bb12.i690 ], [ %c.sroa.0.0.i674, %bb7.i673 ]
  %151 = tail call { i32, i1 } @llvm.ssub.with.overflow.i32(i32 %_30.0.i636, i32 %c.sroa.0.1.i677)
  %_31.1.i682 = extractvalue { i32, i1 } %151, 1
  br i1 %_31.1.i682, label %panic9.i685, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit697

panic9.i685:                                      ; preds = %bb14.i680
; call core::panicking::panic_const::panic_const_sub_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_72bac528c0514d634dbb2acaf4e914ed) #13
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit697: ; preds = %bb14.i680
  %_31.0.i684 = extractvalue { i32, i1 } %151, 0
  %152 = add nsw i64 %l.sroa.0.0.i2137, -11
  %or.cond.i646 = icmp ult i64 %152, 247
  br i1 %or.cond.i646, label %bb6.i668, label %bb7.i647

bb7.i647:                                         ; preds = %bb6.i668, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit697
  %c.sroa.0.0.i648 = phi i32 [ %155, %bb6.i668 ], [ 168, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit697 ]
  %_17.i649 = icmp ugt i64 %d.sroa.0.0.i2136, 4
  br i1 %_17.i649, label %bb8.i661, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit671

bb6.i668:                                         ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit697
  %153 = trunc nuw nsw i64 %l.sroa.0.0.i2137 to i32
  %_11.i669 = add nsw i32 %153, -3
  %_10.i670 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_11.i669, i1 false)
  %154 = shl nuw nsw i32 %_10.i670, 4
  %155 = sub nuw nsw i32 632, %154
  br label %bb7.i647

bb8.i661:                                         ; preds = %bb7.i647
  %156 = trunc i64 %d.sroa.0.0.i2136 to i32
  %_22.i662 = add nsw i32 %156, -1
  %_25.1.i663 = icmp ult i32 %_22.i662, 2
  br i1 %_25.1.i663, label %panic5.i667, label %bb12.i664

panic5.i667:                                      ; preds = %bb8.i661
; call core::panicking::panic_const::panic_const_sub_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_cc8257d2c78dd28d3d4ac89f580613b9) #13
  unreachable

bb12.i664:                                        ; preds = %bb8.i661
  %_21.i665 = tail call range(i32 0, 33) i32 @llvm.ctlz.i32(i32 %_22.i662, i1 true)
  %157 = shl nuw nsw i32 %_21.i665, 4
  %reass.sub2188 = sub nsw i32 %c.sroa.0.0.i648, %157
  %158 = add nsw i32 %reass.sub2188, 480
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit671

_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit671: ; preds = %bb12.i664, %bb7.i647
  %c.sroa.0.1.i651 = phi i32 [ %158, %bb12.i664 ], [ %c.sroa.0.0.i648, %bb7.i647 ]
  %_29.i652 = trunc nuw nsw i64 %l.sroa.0.0.i2137 to i32
  %_30.0.i655 = shl nuw nsw i32 %_29.i652, 6
  %159 = sub nsw i32 %_30.0.i655, %c.sroa.0.1.i651
  %_62.i = icmp sgt i32 %_31.0.i684, %159
  br i1 %_62.i, label %bb32.i, label %bb63.i.loopexit.split.loop.exit2825

bb32.i:                                           ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_gain.exit671
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2683)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2686)
  %exitcond.not2733 = icmp eq i64 %nt.sroa.0.5.i2138, %umax2714
  br i1 %exitcond.not2733, label %panic1.i, label %bb59.i

panic1.i:                                         ; preds = %bb32.i
  %nt.sroa.0.5.i2138.lcssa2772 = phi i64 [ %nt.sroa.0.5.i2138, %bb32.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %nt.sroa.0.5.i2138.lcssa2772, i64 noundef range(i64 0, 2305843009213693952) %out.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_ce72d480401e07b7a290039044612259) #13, !noalias !2688
  unreachable

bb59.i:                                           ; preds = %bb32.i
  %_5.i = load i8, ptr %103, align 1, !alias.scope !2683, !noalias !2686, !noundef !135
  %160 = getelementptr inbounds nuw [4 x i8], ptr %out.0, i64 %nt.sroa.0.5.i2138
  %161 = zext i8 %_5.i to i32
  store i32 %161, ptr %160, align 4, !alias.scope !2686, !noalias !2683
  %_10.0.i152 = add i64 %nt.sroa.0.5.i2138, 1
  %_39.i = icmp ult i64 %k.sroa.0.2.i.lcssa, 64
  %indvars.iv.next = add i64 %indvars.iv, -1
  br i1 %_39.i, label %bb18.i, label %bb63.i.loopexit.split.loop.exit2819

bb116.i:                                          ; preds = %bb110.i, %bb63.i
  %p.sroa.0.7.i.lcssa = phi i64 [ %p.sroa.0.5.i.lcssa, %bb63.i ], [ %p.sroa.0.8.i, %bb110.i ]
  %l.sroa.0.2.i.lcssa = phi i64 [ %l.sroa.0.0.i.lcssa, %bb63.i ], [ %l.sroa.0.3.i, %bb110.i ]
  %nt.sroa.0.7.i.lcssa = phi i64 [ %nt.sroa.0.5.i.lcssa, %bb63.i ], [ %nt.sroa.0.8.i, %bb110.i ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2689)
  %_15.i180 = icmp samesign ult i64 %nt.sroa.0.7.i.lcssa, %out.1
  br i1 %_15.i180, label %bb1.i182, label %panic.i181

bb1.i182:                                         ; preds = %bb116.i
  %162 = trunc i64 %l.sroa.0.2.i.lcssa to i32
  %163 = trunc i64 %d.sroa.0.0.i.lcssa to i32
  %_10.i = shl i32 %163, 8
  %_12.i183 = add i32 %_10.i, 16776957
  %_7.i184 = add i32 %_12.i183, %162
  %164 = getelementptr inbounds nuw [4 x i8], ptr %out.0, i64 %nt.sroa.0.7.i.lcssa
  store i32 %_7.i184, ptr %164, align 4, !alias.scope !2689
  %_19.0.i185 = add i64 %l.sroa.0.2.i.lcssa, %p.sroa.0.7.i.lcssa
  %_19.1.i = icmp ult i64 %_19.0.i185, %p.sroa.0.7.i.lcssa
  br i1 %_19.1.i, label %panic2.i187, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse14u118_put_match.exit

panic.i181:                                       ; preds = %bb116.i
  %nt.sroa.0.7.i.lcssa.lcssa = phi i64 [ %nt.sroa.0.7.i.lcssa, %bb116.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef range(i64 0, 2305843009213693952) %nt.sroa.0.7.i.lcssa.lcssa, i64 noundef range(i64 0, 2305843009213693952) %out.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_950cb3d32dbfbf973f57d9a20abe6695) #13, !noalias !2689
  unreachable

panic2.i187:                                      ; preds = %bb1.i182
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_dc5ae93321079a7792fc0613ca37a43e) #13, !noalias !2689
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse14u118_put_match.exit: ; preds = %bb1.i182
  %_17.0.i = add nuw nsw i64 %nt.sroa.0.7.i.lcssa, 1
  %_175.i = add nuw i64 %ins.sroa.0.4.i.lcssa, 16
  %spec.select138.i = tail call i64 @llvm.umin.i64(i64 %_19.0.i185, i64 %_175.i)
  %spec.store.select50.i = tail call i64 @llvm.umin.i64(i64 %spec.select138.i, i64 %_8.0.i)
  %_181.i2164 = icmp ult i64 %ins.sroa.0.4.i.lcssa, %spec.store.select50.i
  br i1 %_181.i2164, label %bb125.i, label %bb129.i

bb125.i:                                          ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse14u118_put_match.exit, %bb125.i
  %ins.sroa.0.5.i2165 = phi i64 [ %_188.0.i, %bb125.i ], [ %ins.sroa.0.4.i.lcssa, %_RNvNtCs2hd9JHJjR4I_9candidate5parse14u118_put_match.exit ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2692)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2695)
  %165 = getelementptr inbounds nuw i8, ptr %input.0, i64 %ins.sroa.0.5.i2165
  %166 = load i32, ptr %165, align 1
  %167 = call i32 @llvm.bswap.i32(i32 %166)
  %168 = zext i32 %167 to i64
  %169 = mul i64 %168, -7046029254386353131
  %170 = lshr i64 %169, 48
  %171 = getelementptr inbounds nuw [4 x i8], ptr %head.i, i64 %170
  %old.i145.i = load i32, ptr %171, align 4, !alias.scope !2692, !noalias !2697, !noundef !135
  %_16.i146.i = and i64 %ins.sroa.0.5.i2165, 32767
  %172 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_16.i146.i
  store i32 %old.i145.i, ptr %172, align 4, !alias.scope !2695, !noalias !2699
  %173 = trunc i64 %ins.sroa.0.5.i2165 to i32
  store i32 %173, ptr %171, align 4, !alias.scope !2692, !noalias !2697
  %_188.0.i = add nuw i64 %ins.sroa.0.5.i2165, 1
  %exitcond2324.not = icmp eq i64 %_188.0.i, %spec.store.select50.i
  br i1 %exitcond2324.not, label %bb129.i, label %bb125.i

bb129.i:                                          ; preds = %bb125.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse14u118_put_match.exit
  %ins.sroa.0.5.i.lcssa = phi i64 [ %ins.sroa.0.4.i.lcssa, %_RNvNtCs2hd9JHJjR4I_9candidate5parse14u118_put_match.exit ], [ %spec.store.select50.i, %bb125.i ]
  %e2.i = tail call i64 @llvm.usub.sat.i64(i64 %_19.0.i185, i64 8)
  %invariant.umin = tail call i64 @llvm.umin.i64(i64 %e2.i, i64 %_8.0.i)
  %or.cond51.i2167 = icmp ult i64 %ins.sroa.0.5.i.lcssa, %invariant.umin
  br i1 %or.cond51.i2167, label %bb132.i, label %bb138.i

bb132.i:                                          ; preds = %bb129.i, %bb132.i
  %ins.sroa.0.6.i2168 = phi i64 [ %_5.0.i278, %bb132.i ], [ %ins.sroa.0.5.i.lcssa, %bb129.i ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2700)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2703)
  %_5.0.i278 = add nuw i64 %ins.sroa.0.6.i2168, 4
  %174 = getelementptr inbounds nuw i8, ptr %input.0, i64 %ins.sroa.0.6.i2168
  %175 = load i32, ptr %174, align 1
  %176 = call i32 @llvm.bswap.i32(i32 %175)
  %177 = zext i32 %176 to i64
  %178 = mul i64 %177, -7046029254386353131
  %179 = lshr i64 %178, 48
  %180 = getelementptr inbounds nuw [4 x i8], ptr %head.i, i64 %179
  %old.i152.i = load i32, ptr %180, align 4, !alias.scope !2700, !noalias !2705, !noundef !135
  %_16.i153.i = and i64 %ins.sroa.0.6.i2168, 32767
  %181 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_16.i153.i
  store i32 %old.i152.i, ptr %181, align 4, !alias.scope !2703, !noalias !2707
  %182 = trunc i64 %ins.sroa.0.6.i2168 to i32
  store i32 %182, ptr %180, align 4, !alias.scope !2700, !noalias !2705
  %or.cond51.i = icmp ult i64 %_5.0.i278, %invariant.umin
  br i1 %or.cond51.i, label %bb132.i, label %bb138.i

bb138.i:                                          ; preds = %bb132.i, %bb129.i
  %ins.sroa.0.6.i.lcssa = phi i64 [ %ins.sroa.0.5.i.lcssa, %bb129.i ], [ %_5.0.i278, %bb132.i ]
  %_202.i = add i64 %ins.sroa.0.6.i.lcssa, 4
  %_201.i = icmp ult i64 %_202.i, %_19.0.i185
  br i1 %_201.i, label %bb139.i, label %bb142.i

bb139.i:                                          ; preds = %bb138.i
  %_204.1.i = icmp ult i64 %_19.0.i185, 4
  br i1 %_204.1.i, label %panic18.i, label %bb140.i

bb142.i:                                          ; preds = %bb140.i, %bb138.i
  %ins.sroa.0.7.i = phi i64 [ %_204.0.i, %bb140.i ], [ %ins.sroa.0.6.i.lcssa, %bb138.i ]
  %invariant.umin2170 = tail call i64 @llvm.umin.i64(i64 %_19.0.i185, i64 %_8.0.i)
  %or.cond52.i2171 = icmp ult i64 %ins.sroa.0.7.i, %invariant.umin2170
  br i1 %or.cond52.i2171, label %bb145.i, label %bb150.i

bb140.i:                                          ; preds = %bb139.i
  %_204.0.i = add i64 %_19.0.i185, -4
  br label %bb142.i

panic18.i:                                        ; preds = %bb139.i
; call core::panicking::panic_const::panic_const_sub_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_sub_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_30e260b757f13d4a959ad3a108dff26e) #13
  unreachable

bb150.i:                                          ; preds = %bb145.i, %bb142.i
  %ins.sroa.0.8.i.lcssa = phi i64 [ %ins.sroa.0.7.i, %bb142.i ], [ %_213.0.i, %bb145.i ]
  %spec.select140.i = tail call i64 @llvm.umax.i64(i64 %ins.sroa.0.8.i.lcssa, i64 %_19.0.i185)
  br label %bb174.i

bb145.i:                                          ; preds = %bb142.i, %bb145.i
  %ins.sroa.0.8.i2172 = phi i64 [ %_213.0.i, %bb145.i ], [ %ins.sroa.0.7.i, %bb142.i ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2708)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2711)
  %183 = getelementptr inbounds nuw i8, ptr %input.0, i64 %ins.sroa.0.8.i2172
  %184 = load i32, ptr %183, align 1
  %185 = call i32 @llvm.bswap.i32(i32 %184)
  %186 = zext i32 %185 to i64
  %187 = mul i64 %186, -7046029254386353131
  %188 = lshr i64 %187, 48
  %189 = getelementptr inbounds nuw [4 x i8], ptr %head.i, i64 %188
  %old.i159.i = load i32, ptr %189, align 4, !alias.scope !2708, !noalias !2713, !noundef !135
  %_16.i160.i = and i64 %ins.sroa.0.8.i2172, 32767
  %190 = getelementptr inbounds nuw [4 x i8], ptr %prev.i, i64 %_16.i160.i
  store i32 %old.i159.i, ptr %190, align 4, !alias.scope !2711, !noalias !2715
  %191 = trunc i64 %ins.sroa.0.8.i2172 to i32
  store i32 %191, ptr %189, align 4, !alias.scope !2708, !noalias !2713
  %_213.0.i = add nuw nsw i64 %ins.sroa.0.8.i2172, 1
  %or.cond52.i = icmp ult i64 %_213.0.i, %invariant.umin2170
  br i1 %or.cond52.i, label %bb145.i, label %bb150.i

bb71.i:                                           ; preds = %bb63.i, %bb110.i
  %192 = phi i64 [ %244, %bb110.i ], [ %100, %bb63.i ]
  %nt.sroa.0.7.i2160 = phi i64 [ %nt.sroa.0.8.i, %bb110.i ], [ %nt.sroa.0.5.i.lcssa, %bb63.i ]
  %l.sroa.0.2.i2159 = phi i64 [ %l.sroa.0.3.i, %bb110.i ], [ %l.sroa.0.0.i.lcssa, %bb63.i ]
  %back.sroa.0.0.i2158 = phi i64 [ %back.sroa.0.1.i, %bb110.i ], [ 0, %bb63.i ]
  %p.sroa.0.7.i2157 = phi i64 [ %p.sroa.0.8.i, %bb110.i ], [ %p.sroa.0.5.i.lcssa, %bb63.i ]
  %193 = getelementptr inbounds nuw [4 x i8], ptr %out.0, i64 %192
  %t.i = load i32, ptr %193, align 4, !alias.scope !2600, !noalias !2597, !noundef !135
  %_120.i = icmp ult i32 %t.i, 256
  br i1 %_120.i, label %bb72.i, label %bb84.i

bb84.i:                                           ; preds = %bb71.i
  %_139.i = icmp ugt i32 %t.i, 16777215
  br i1 %_139.i, label %bb87.i, label %bb110.i

bb72.i:                                           ; preds = %bb71.i
  %_125.0.i = add i64 %p.sroa.0.7.i2157, -1
  %_126.i = icmp ult i64 %_125.0.i, %input.1
  br i1 %_126.i, label %bb74.i, label %panic25.i

bb74.i:                                           ; preds = %bb72.i
  %_133.0.i = sub i64 %_125.0.i, %d.sroa.0.0.i.lcssa
  %_134.i = icmp ult i64 %_133.0.i, %input.1
  br i1 %_134.i, label %bb77.i, label %panic28.i

panic25.i:                                        ; preds = %bb72.i
  %_125.0.i.lcssa = phi i64 [ %_125.0.i, %bb72.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_125.0.i.lcssa, i64 noundef range(i64 0, -9223372036854775808) %input.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_1f28cc27fa9e18e58cef417bee4fd90b) #13
  unreachable

bb77.i:                                           ; preds = %bb74.i
  %194 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_125.0.i
  %_122.i = load i8, ptr %194, align 1, !alias.scope !2597, !noalias !2600, !noundef !135
  %195 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_133.0.i
  %_127.i = load i8, ptr %195, align 1, !alias.scope !2597, !noalias !2600, !noundef !135
  %_121.i = icmp eq i8 %_122.i, %_127.i
  br i1 %_121.i, label %bb80.i, label %bb110.i

panic28.i:                                        ; preds = %bb74.i
  %_133.0.i.lcssa = phi i64 [ %_133.0.i, %bb74.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_133.0.i.lcssa, i64 noundef range(i64 0, -9223372036854775808) %input.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_a470f1791914be2ed9860c28a94823b8) #13
  unreachable

bb87.i:                                           ; preds = %bb84.i
  %_142.i = and i32 %t.i, 255
  %_145.0.i = add nuw nsw i32 %_142.i, 3
  %w.i = zext nneg i32 %_145.0.i to i64
  %_149.0.i = add nuw nsw i64 %l.sroa.0.2.i2159, %w.i
  %_146.i = icmp samesign ult i64 %_149.0.i, 259
  %_150.i = icmp uge i64 %p.sroa.0.7.i2157, %w.i
  %or.cond53.i = select i1 %_146.i, i1 %_150.i, i1 false
  br i1 %or.cond53.i, label %bb90.i, label %bb110.i

bb90.i:                                           ; preds = %bb87.i
  %_156.0.i = sub nuw i64 %p.sroa.0.7.i2157, %w.i
  %_152.not.i = icmp ugt i64 %d.sroa.0.0.i.lcssa, %_156.0.i
  br i1 %_152.not.i, label %bb110.i, label %bb95.i

bb95.i:                                           ; preds = %bb90.i
  %_163.0.i = sub nuw i64 %_156.0.i, %d.sroa.0.0.i.lcssa
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2716)
  %196 = and i64 %w.i, 504
  br label %bb2.i737

bb2.i737:                                         ; preds = %bb95.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i
  %k.sroa.0.0.i6992149 = phi i64 [ 0, %bb95.i ], [ %_11.0.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i ]
  %_11.0.i = add nuw nsw i64 %k.sroa.0.0.i6992149, 8
  %_8.not.i = icmp samesign ugt i64 %_11.0.i, %w.i
  br i1 %_8.not.i, label %bb15.i700, label %bb4.i739

bb4.i739:                                         ; preds = %bb2.i737
  %_16.0.i = add nuw i64 %k.sroa.0.0.i6992149, %_163.0.i
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2719)
  %_5.1.i172.i = icmp ugt i64 %_16.0.i, -9
  br i1 %_5.1.i172.i, label %panic.i238.i, label %bb1.i173.i

bb15.i700:                                        ; preds = %bb2.i737
  %_23.i701.not = icmp eq i64 %196, %w.i
  br i1 %_23.i701.not, label %bb101.i, label %bb18.i703

bb1.i173.i:                                       ; preds = %bb4.i739
  %_5.0.i174.i = add nuw i64 %_16.0.i, 8
  %_3.not.i175.i = icmp ugt i64 %_5.0.i174.i, %input.1
  br i1 %_3.not.i175.i, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit239.i, label %bb2.i176.i

panic.i238.i:                                     ; preds = %bb4.i739
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_bb314acf14069c2fbedf530b060ebd60) #13, !noalias !2722
  unreachable

bb2.i176.i:                                       ; preds = %bb1.i173.i
  %197 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_16.0.i
  %_15.i180.i = load i8, ptr %197, align 1, !alias.scope !2722, !noundef !135
  %_14.i181.i = zext i8 %_15.i180.i to i64
  %_13.i182.i = shl nuw i64 %_14.i181.i, 56
  %198 = getelementptr inbounds nuw i8, ptr %197, i64 1
  %_19.i187.i = load i8, ptr %198, align 1, !alias.scope !2722, !noundef !135
  %_18.i188.i = zext i8 %_19.i187.i to i64
  %_17.i189.i = shl nuw nsw i64 %_18.i188.i, 48
  %_12.i190.i = or disjoint i64 %_17.i189.i, %_13.i182.i
  %199 = getelementptr inbounds nuw i8, ptr %197, i64 2
  %_25.i195.i = load i8, ptr %199, align 1, !alias.scope !2722, !noundef !135
  %_24.i196.i = zext i8 %_25.i195.i to i64
  %_23.i197.i = shl nuw nsw i64 %_24.i196.i, 40
  %_11.i198.i = or disjoint i64 %_12.i190.i, %_23.i197.i
  %200 = getelementptr inbounds nuw i8, ptr %197, i64 3
  %_31.i203.i = load i8, ptr %200, align 1, !alias.scope !2722, !noundef !135
  %_30.i204.i = zext i8 %_31.i203.i to i64
  %_29.i205.i = shl nuw nsw i64 %_30.i204.i, 32
  %_10.i206.i = or disjoint i64 %_11.i198.i, %_29.i205.i
  %201 = getelementptr inbounds nuw i8, ptr %197, i64 4
  %_37.i211.i = load i8, ptr %201, align 1, !alias.scope !2722, !noundef !135
  %_36.i212.i = zext i8 %_37.i211.i to i64
  %_35.i213.i = shl nuw nsw i64 %_36.i212.i, 24
  %_9.i214.i = or disjoint i64 %_10.i206.i, %_35.i213.i
  %202 = getelementptr inbounds nuw i8, ptr %197, i64 5
  %_43.i219.i = load i8, ptr %202, align 1, !alias.scope !2722, !noundef !135
  %_42.i220.i = zext i8 %_43.i219.i to i64
  %_41.i221.i = shl nuw nsw i64 %_42.i220.i, 16
  %_8.i222.i = or disjoint i64 %_9.i214.i, %_41.i221.i
  %203 = getelementptr inbounds nuw i8, ptr %197, i64 6
  %_49.i227.i = load i8, ptr %203, align 1, !alias.scope !2722, !noundef !135
  %_48.i228.i = zext i8 %_49.i227.i to i64
  %_47.i229.i = shl nuw nsw i64 %_48.i228.i, 8
  %_7.i230.i = or i64 %_8.i222.i, %_47.i229.i
  %204 = getelementptr inbounds nuw i8, ptr %197, i64 7
  %_54.i235.i = load i8, ptr %204, align 1, !alias.scope !2722, !noundef !135
  %_53.i236.i = zext i8 %_54.i235.i to i64
  %205 = or i64 %_7.i230.i, %_53.i236.i
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit239.i

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit239.i: ; preds = %bb2.i176.i, %bb1.i173.i
  %_0.sroa.0.0.i237.i = phi i64 [ %205, %bb2.i176.i ], [ 0, %bb1.i173.i ]
  %_20.0.i = add nuw i64 %k.sroa.0.0.i6992149, %_156.0.i
  tail call void @llvm.experimental.noalias.scope.decl(metadata !2723)
  %_5.1.i104.i = icmp ugt i64 %_20.0.i, -9
  br i1 %_5.1.i104.i, label %panic.i170.i, label %bb1.i105.i

bb1.i105.i:                                       ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit239.i
  %_5.0.i106.i = add nuw i64 %_20.0.i, 8
  %_3.not.i107.i = icmp ugt i64 %_5.0.i106.i, %input.1
  br i1 %_3.not.i107.i, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i, label %bb2.i108.i

panic.i170.i:                                     ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit239.i
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_bb314acf14069c2fbedf530b060ebd60) #13, !noalias !2726
  unreachable

bb2.i108.i:                                       ; preds = %bb1.i105.i
  %206 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_20.0.i
  %_15.i112.i = load i8, ptr %206, align 1, !alias.scope !2726, !noundef !135
  %_14.i113.i = zext i8 %_15.i112.i to i64
  %_13.i114.i = shl nuw i64 %_14.i113.i, 56
  %207 = getelementptr inbounds nuw i8, ptr %206, i64 1
  %_19.i119.i = load i8, ptr %207, align 1, !alias.scope !2726, !noundef !135
  %_18.i120.i = zext i8 %_19.i119.i to i64
  %_17.i121.i = shl nuw nsw i64 %_18.i120.i, 48
  %_12.i122.i = or disjoint i64 %_17.i121.i, %_13.i114.i
  %208 = getelementptr inbounds nuw i8, ptr %206, i64 2
  %_25.i127.i = load i8, ptr %208, align 1, !alias.scope !2726, !noundef !135
  %_24.i128.i = zext i8 %_25.i127.i to i64
  %_23.i129.i = shl nuw nsw i64 %_24.i128.i, 40
  %_11.i130.i = or disjoint i64 %_12.i122.i, %_23.i129.i
  %209 = getelementptr inbounds nuw i8, ptr %206, i64 3
  %_31.i135.i = load i8, ptr %209, align 1, !alias.scope !2726, !noundef !135
  %_30.i136.i = zext i8 %_31.i135.i to i64
  %_29.i137.i = shl nuw nsw i64 %_30.i136.i, 32
  %_10.i138.i = or disjoint i64 %_11.i130.i, %_29.i137.i
  %210 = getelementptr inbounds nuw i8, ptr %206, i64 4
  %_37.i143.i = load i8, ptr %210, align 1, !alias.scope !2726, !noundef !135
  %_36.i144.i = zext i8 %_37.i143.i to i64
  %_35.i145.i = shl nuw nsw i64 %_36.i144.i, 24
  %_9.i146.i = or disjoint i64 %_10.i138.i, %_35.i145.i
  %211 = getelementptr inbounds nuw i8, ptr %206, i64 5
  %_43.i151.i = load i8, ptr %211, align 1, !alias.scope !2726, !noundef !135
  %_42.i152.i = zext i8 %_43.i151.i to i64
  %_41.i153.i = shl nuw nsw i64 %_42.i152.i, 16
  %_8.i154.i = or disjoint i64 %_9.i146.i, %_41.i153.i
  %212 = getelementptr inbounds nuw i8, ptr %206, i64 6
  %_49.i159.i = load i8, ptr %212, align 1, !alias.scope !2726, !noundef !135
  %_48.i160.i = zext i8 %_49.i159.i to i64
  %_47.i161.i = shl nuw nsw i64 %_48.i160.i, 8
  %_7.i162.i = or i64 %_8.i154.i, %_47.i161.i
  %213 = getelementptr inbounds nuw i8, ptr %206, i64 7
  %_54.i167.i = load i8, ptr %213, align 1, !alias.scope !2726, !noundef !135
  %_53.i168.i = zext i8 %_54.i167.i to i64
  %214 = or i64 %_7.i162.i, %_53.i168.i
  br label %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i

_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i: ; preds = %bb2.i108.i, %bb1.i105.i
  %_0.sroa.0.0.i169.i = phi i64 [ %214, %bb2.i108.i ], [ 0, %bb1.i105.i ]
  %_12.i.not = icmp eq i64 %_0.sroa.0.0.i237.i, %_0.sroa.0.0.i169.i
  br i1 %_12.i.not, label %bb2.i737, label %bb110.i

bb18.i703:                                        ; preds = %bb15.i700
  %_29.0.i704 = add i64 %196, %_163.0.i
  %_29.1.i = icmp ult i64 %_29.0.i704, %_163.0.i
  br i1 %_29.1.i, label %panic4.i736, label %bb19.i705

bb19.i705:                                        ; preds = %bb18.i703
  %_30.1.i706 = icmp ugt i64 %_29.0.i704, -9
  br i1 %_30.1.i706, label %panic5.i735, label %bb20.i707

panic4.i736:                                      ; preds = %bb18.i703
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_410f560b7db958092bd73a0bb4ae0379) #13, !noalias !2716
  unreachable

bb20.i707:                                        ; preds = %bb19.i705
  %_30.0.i708 = add nuw i64 %_29.0.i704, 8
  %_25.not.i = icmp ugt i64 %_30.0.i708, %input.1
  br i1 %_25.not.i, label %bb40.i.preheader, label %bb21.i709

bb40.i.preheader:                                 ; preds = %bb23.i, %bb20.i707
  br label %bb40.i

panic5.i735:                                      ; preds = %bb19.i705
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_410f560b7db958092bd73a0bb4ae0379) #13, !noalias !2716
  unreachable

bb21.i709:                                        ; preds = %bb20.i707
  %_35.0.i = add i64 %196, %_156.0.i
  %_35.1.i = icmp ult i64 %_35.0.i, %_156.0.i
  br i1 %_35.1.i, label %panic6.i734, label %bb22.i710

bb22.i710:                                        ; preds = %bb21.i709
  %_36.1.i711 = icmp ugt i64 %_35.0.i, -9
  br i1 %_36.1.i711, label %panic7.i733, label %bb23.i

panic6.i734:                                      ; preds = %bb21.i709
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_25f0ab118ce3ac29922df37c6b354aae) #13, !noalias !2716
  unreachable

bb23.i:                                           ; preds = %bb22.i710
  %_36.0.i712 = add nuw i64 %_35.0.i, 8
  %_31.not.i = icmp ugt i64 %_36.0.i712, %input.1
  br i1 %_31.not.i, label %bb40.i.preheader, label %bb30.i

panic7.i733:                                      ; preds = %bb22.i710
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_25f0ab118ce3ac29922df37c6b354aae) #13, !noalias !2716
  unreachable

bb40.i:                                           ; preds = %bb40.i.preheader, %bb44.i
  %k.sroa.0.2.i7262151 = phi i64 [ %k.sroa.0.3.i731, %bb44.i ], [ %196, %bb40.i.preheader ]
  %_62.0.i = add i64 %k.sroa.0.2.i7262151, %_163.0.i
  %_62.1.i = icmp ult i64 %_62.0.i, %_163.0.i
  br i1 %_62.1.i, label %panic8.i732, label %bb41.i

bb41.i:                                           ; preds = %bb40.i
  %_63.i = icmp ult i64 %_62.0.i, %input.1
  br i1 %_63.i, label %bb42.i, label %panic9.i727

panic8.i732:                                      ; preds = %bb40.i
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_f491bec5a0814d991fa65b29bceb4569) #13, !noalias !2716
  unreachable

bb42.i:                                           ; preds = %bb41.i
  %215 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_62.0.i
  %_59.i728 = load i8, ptr %215, align 1, !alias.scope !2716, !noundef !135
  %_67.0.i = add i64 %k.sroa.0.2.i7262151, %_156.0.i
  %_67.1.i = icmp ult i64 %_67.0.i, %_156.0.i
  br i1 %_67.1.i, label %panic10.i, label %bb43.i

panic9.i727:                                      ; preds = %bb41.i
  %_62.0.i.lcssa2773 = phi i64 [ %_62.0.i, %bb41.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_62.0.i.lcssa2773, i64 noundef range(i64 0, -9223372036854775808) %input.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_6423c6cb6214cc14d5219f2068f396e1) #13, !noalias !2716
  unreachable

bb43.i:                                           ; preds = %bb42.i
  %_68.i = icmp ult i64 %_67.0.i, %input.1
  br i1 %_68.i, label %bb44.i, label %panic11.i729

panic10.i:                                        ; preds = %bb42.i
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_0dafef88f4ad7c766190399efdbc2565) #13, !noalias !2716
  unreachable

bb44.i:                                           ; preds = %bb43.i
  %216 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_67.0.i
  %_64.i730 = load i8, ptr %216, align 1, !alias.scope !2716, !noundef !135
  %_58.i = icmp eq i8 %_59.i728, %_64.i730
  %_69.0.i = zext i1 %_58.i to i64
  %k.sroa.0.3.i731 = add nuw nsw i64 %k.sroa.0.2.i7262151, %_69.0.i
  %_56.i = icmp samesign ult i64 %k.sroa.0.3.i731, %w.i
  %or.cond19.i = select i1 %_58.i, i1 %_56.i, i1 false
  br i1 %or.cond19.i, label %bb40.i, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit

panic11.i729:                                     ; preds = %bb43.i
  %_67.0.i.lcssa2777 = phi i64 [ %_67.0.i, %bb43.i ]
; call core::panicking::panic_bounds_check
  tail call void @_RNvNtCsdN1ZzDs28Vk_4core9panicking18panic_bounds_check(i64 noundef %_67.0.i.lcssa2777, i64 noundef range(i64 0, -9223372036854775808) %input.1, ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_6298bd754cf21e84e6b31996eea28f6b) #13, !noalias !2716
  unreachable

bb30.i:                                           ; preds = %bb23.i
  %_51.0.i717 = shl nuw nsw i32 %_145.0.i, 3
  %217 = and i32 %_51.0.i717, 56
  %_54.i720.not = icmp eq i32 %217, 0
  br i1 %_54.i720.not, label %panic18.i721, label %bb32.i722

bb32.i722:                                        ; preds = %bb30.i
  %_53.0.i = sub nuw nsw i32 64, %217
  %218 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_35.0.i
  %219 = getelementptr inbounds nuw i8, ptr %218, i64 1
  %_19.i.i = load i8, ptr %219, align 1, !alias.scope !2727, !noundef !135
  %_18.i.i = zext i8 %_19.i.i to i64
  %_17.i.i = shl nuw nsw i64 %_18.i.i, 48
  %_15.i.i = load i8, ptr %218, align 1, !alias.scope !2727, !noundef !135
  %_14.i.i = zext i8 %_15.i.i to i64
  %_13.i.i = shl nuw i64 %_14.i.i, 56
  %_12.i.i714 = or disjoint i64 %_17.i.i, %_13.i.i
  %220 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_35.0.i
  %221 = getelementptr inbounds nuw i8, ptr %220, i64 2
  %_25.i.i = load i8, ptr %221, align 1, !alias.scope !2727, !noundef !135
  %_24.i.i = zext i8 %_25.i.i to i64
  %_23.i.i = shl nuw nsw i64 %_24.i.i, 40
  %_11.i.i715 = or disjoint i64 %_12.i.i714, %_23.i.i
  %222 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_35.0.i
  %223 = getelementptr inbounds nuw i8, ptr %222, i64 3
  %_31.i.i = load i8, ptr %223, align 1, !alias.scope !2727, !noundef !135
  %_30.i.i = zext i8 %_31.i.i to i64
  %_29.i.i = shl nuw nsw i64 %_30.i.i, 32
  %_10.i.i = or disjoint i64 %_11.i.i715, %_29.i.i
  %224 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_35.0.i
  %225 = getelementptr inbounds nuw i8, ptr %224, i64 4
  %_37.i.i = load i8, ptr %225, align 1, !alias.scope !2727, !noundef !135
  %_36.i.i = zext i8 %_37.i.i to i64
  %_35.i.i = shl nuw nsw i64 %_36.i.i, 24
  %_9.i.i = or disjoint i64 %_10.i.i, %_35.i.i
  %226 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_35.0.i
  %227 = getelementptr inbounds nuw i8, ptr %226, i64 5
  %_43.i.i = load i8, ptr %227, align 1, !alias.scope !2727, !noundef !135
  %_42.i.i = zext i8 %_43.i.i to i64
  %_41.i.i = shl nuw nsw i64 %_42.i.i, 16
  %_8.i.i = or disjoint i64 %_9.i.i, %_41.i.i
  %228 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_35.0.i
  %229 = getelementptr inbounds nuw i8, ptr %228, i64 6
  %_49.i.i = load i8, ptr %229, align 1, !alias.scope !2727, !noundef !135
  %_48.i.i = zext i8 %_49.i.i to i64
  %_47.i.i = shl nuw nsw i64 %_48.i.i, 8
  %_7.i.i = or i64 %_8.i.i, %_47.i.i
  %230 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_35.0.i
  %231 = getelementptr inbounds nuw i8, ptr %230, i64 7
  %_54.i.i = load i8, ptr %231, align 1, !alias.scope !2727, !noundef !135
  %_53.i.i = zext i8 %_54.i.i to i64
  %232 = or i64 %_7.i.i, %_53.i.i
  %233 = getelementptr inbounds nuw i8, ptr %input.0, i64 %_29.0.i704
  %234 = getelementptr inbounds nuw i8, ptr %233, i64 1
  %_19.i51.i = load i8, ptr %234, align 1, !alias.scope !2730, !noundef !135
  %_18.i52.i = zext i8 %_19.i51.i to i64
  %_17.i53.i = shl nuw nsw i64 %_18.i52.i, 48
  %_15.i44.i = load i8, ptr %233, align 1, !alias.scope !2730, !noundef !135
  %_14.i45.i = zext i8 %_15.i44.i to i64
  %_13.i46.i = shl nuw i64 %_14.i45.i, 56
  %_12.i54.i = or disjoint i64 %_17.i53.i, %_13.i46.i
  %235 = getelementptr inbounds nuw i8, ptr %233, i64 2
  %_25.i59.i = load i8, ptr %235, align 1, !alias.scope !2730, !noundef !135
  %_24.i60.i = zext i8 %_25.i59.i to i64
  %_23.i61.i = shl nuw nsw i64 %_24.i60.i, 40
  %_11.i62.i = or disjoint i64 %_12.i54.i, %_23.i61.i
  %236 = getelementptr inbounds nuw i8, ptr %233, i64 3
  %_31.i67.i = load i8, ptr %236, align 1, !alias.scope !2730, !noundef !135
  %_30.i68.i = zext i8 %_31.i67.i to i64
  %_29.i69.i = shl nuw nsw i64 %_30.i68.i, 32
  %_10.i70.i = or disjoint i64 %_11.i62.i, %_29.i69.i
  %237 = getelementptr inbounds nuw i8, ptr %233, i64 4
  %_37.i75.i = load i8, ptr %237, align 1, !alias.scope !2730, !noundef !135
  %_36.i76.i = zext i8 %_37.i75.i to i64
  %_35.i77.i = shl nuw nsw i64 %_36.i76.i, 24
  %_9.i78.i = or disjoint i64 %_10.i70.i, %_35.i77.i
  %238 = getelementptr inbounds nuw i8, ptr %233, i64 5
  %_43.i83.i = load i8, ptr %238, align 1, !alias.scope !2730, !noundef !135
  %_42.i84.i = zext i8 %_43.i83.i to i64
  %_41.i85.i = shl nuw nsw i64 %_42.i84.i, 16
  %_8.i86.i = or disjoint i64 %_9.i78.i, %_41.i85.i
  %239 = getelementptr inbounds nuw i8, ptr %233, i64 6
  %_49.i91.i = load i8, ptr %239, align 1, !alias.scope !2730, !noundef !135
  %_48.i92.i = zext i8 %_49.i91.i to i64
  %_47.i93.i = shl nuw nsw i64 %_48.i92.i, 8
  %_7.i94.i = or i64 %_8.i86.i, %_47.i93.i
  %240 = getelementptr inbounds nuw i8, ptr %233, i64 7
  %_54.i99.i = load i8, ptr %240, align 1, !alias.scope !2730, !noundef !135
  %_53.i100.i = zext i8 %_54.i99.i to i64
  %241 = or i64 %_7.i94.i, %_53.i100.i
  %x.i716 = xor i64 %232, %241
  %242 = zext nneg i32 %_53.0.i to i64
  %_46.i723 = lshr i64 %x.i716, %242
  %243 = icmp eq i64 %_46.i723, 0
  br i1 %243, label %bb101.i, label %bb110.i

panic18.i721:                                     ; preds = %bb30.i
; call core::panicking::panic_const::panic_const_shr_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_shr_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_0d9222021d7218fa4f635bbfc4f9297d) #13, !noalias !2716
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit: ; preds = %bb44.i
  br i1 %_58.i, label %bb101.i, label %bb110.i

bb101.i:                                          ; preds = %bb32.i722, %bb15.i700, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit
  %_170.0.i = add nuw nsw i64 %back.sroa.0.0.i2158, 1
  br label %bb110.i

bb110.i:                                          ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i, %bb32.i722, %bb77.i, %bb80.i, %bb101.i, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit, %bb90.i, %bb87.i, %bb84.i
  %p.sroa.0.8.i = phi i64 [ %_125.0.i, %bb80.i ], [ %_156.0.i, %bb101.i ], [ %p.sroa.0.7.i2157, %bb84.i ], [ %p.sroa.0.7.i2157, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit ], [ %p.sroa.0.7.i2157, %bb90.i ], [ %p.sroa.0.7.i2157, %bb87.i ], [ %p.sroa.0.7.i2157, %bb77.i ], [ %p.sroa.0.7.i2157, %bb32.i722 ], [ %p.sroa.0.7.i2157, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i ]
  %back.sroa.0.1.i = phi i64 [ %_138.0.i, %bb80.i ], [ %_170.0.i, %bb101.i ], [ 16, %bb84.i ], [ 16, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit ], [ 16, %bb90.i ], [ 16, %bb87.i ], [ 16, %bb77.i ], [ 16, %bb32.i722 ], [ 16, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i ]
  %l.sroa.0.3.i = phi i64 [ %_137.0.i, %bb80.i ], [ %_149.0.i, %bb101.i ], [ %l.sroa.0.2.i2159, %bb84.i ], [ %l.sroa.0.2.i2159, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit ], [ %l.sroa.0.2.i2159, %bb90.i ], [ %l.sroa.0.2.i2159, %bb87.i ], [ %l.sroa.0.2.i2159, %bb77.i ], [ %l.sroa.0.2.i2159, %bb32.i722 ], [ %l.sroa.0.2.i2159, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i ]
  %nt.sroa.0.8.i = phi i64 [ %192, %bb80.i ], [ %192, %bb101.i ], [ %nt.sroa.0.7.i2160, %bb84.i ], [ %nt.sroa.0.7.i2160, %_RNvNtCs2hd9JHJjR4I_9candidate5parse9u118_same.exit ], [ %nt.sroa.0.7.i2160, %bb90.i ], [ %nt.sroa.0.7.i2160, %bb87.i ], [ %nt.sroa.0.7.i2160, %bb77.i ], [ %nt.sroa.0.7.i2160, %bb32.i722 ], [ %nt.sroa.0.7.i2160, %_RNvNtCs2hd9JHJjR4I_9candidate5parse8u118_be8.exit171.i ]
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
  %_137.0.i = add nuw nsw i64 %l.sroa.0.2.i2159, 1
  %_138.0.i = add nuw nsw i64 %back.sroa.0.0.i2158, 1
  br label %bb110.i

_RINvNtCs2hd9JHJjR4I_9candidate5parse8u118_runKj10000_Kj8000_Kmffffffff_Kj4_Kjc_Kj40_Kj6_Kjf4240_Kj80_Kj1_Kj10_KB18_Kl40_Kj0_EB4_.exit: ; preds = %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit179, %bb178.i
  %nt.sroa.0.2.i.lcssa = phi i64 [ %nt.sroa.0.0.i, %bb178.i ], [ %_10.0.i178, %_RNvNtCs2hd9JHJjR4I_9candidate5parse12u118_put_lit.exit179 ]
  ret i64 %nt.sroa.0.2.i.lcssa
}