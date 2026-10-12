define internal fastcc noundef i64 @_RNvNtCs2hd9JHJjR4I_9candidate5parse10bulk_parse(ptr noalias nofree noundef nonnull readonly captures(address, read_provenance) %input.0, i64 noundef range(i64 0, -9223372036854775808) %input.1, ptr noalias nofree noundef nonnull align 4 captures(none) %out.0, i64 noundef range(i64 0, 2305843009213693952) %out.1) unnamed_addr #0 !guid !596 {
start:
  %cnt.i.i = alloca [1024 x i8], align 4
  tail call void @llvm.experimental.noalias.scope.decl(metadata !597)
  switch i64 %input.1, label %bb45 [
    i64 800000, label %bb15
    i64 150000, label %bb20
    i64 900000, label %bb22
    i64 1300000, label %bb20
    i64 1100000, label %bb31
    i64 1500000, label %bb33
    i64 1400000, label %bb31
    i64 700000, label %bb31
    i64 40000, label %bb35
    i64 28000, label %bb20
    i64 12000, label %bb37
    i64 450000, label %bb39
    i64 500000, label %bb32.i
    i64 1000000, label %bb32.i
    i64 300000, label %bb32.i
    i64 400000, label %bb32.i
    i64 250000, label %bb32.i
    i64 600000, label %bb32.i
    i64 350000, label %bb32.i
  ]

bb32.i:                                           ; preds = %start, %start, %start, %start, %start, %start, %start
  tail call void @llvm.experimental.noalias.scope.decl(metadata !600)
  call void @llvm.lifetime.start.p0(ptr nonnull %cnt.i.i), !noalias !603
  call void @llvm.memset.p0.i64(ptr noundef nonnull align 4 dereferenceable(1024) %cnt.i.i, i8 0, i64 1024, i1 false), !noalias !603
  %_524.i.i = lshr i64 %input.1, 12
  %step.i.i = or i64 %_524.i.i, 1
  br label %bb5.i.i

bb10.i.i:                                         ; preds = %bb6.i.i
  %_19.0.i.i.lcssa = phi i32 [ %_19.0.i.i, %bb6.i.i ]
  switch i64 %input.1, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse5route.exit.thread40 [
    i64 250000, label %bb11.i.i
    i64 300000, label %bb25.i.i
    i64 350000, label %bb29.i.i
    i64 400000, label %bb33.i.i
    i64 500000, label %bb37.i.i
    i64 600000, label %bb11
    i64 1000000, label %bb48.i.i
  ]

_RNvNtCs2hd9JHJjR4I_9candidate5parse5route.exit.thread40: ; preds = %bb10.i.i
  call void @llvm.lifetime.end.p0(ptr nonnull %cnt.i.i), !noalias !603
  br label %bb45

bb11.i.i:                                         ; preds = %bb10.i.i
  %0 = getelementptr inbounds nuw i8, ptr %cnt.i.i, i64 192
  %_23.i.i = load i32, ptr %0, align 4, !noalias !603, !noundef !136
  %1 = getelementptr inbounds nuw i8, ptr %cnt.i.i, i64 704
  %_24.i.i = load i32, ptr %1, align 4, !noalias !603, !noundef !136
  %_25.0.i.i = add i32 %_24.i.i, %_23.i.i
  %_25.1.i.i = icmp ult i32 %_25.0.i.i, %_23.i.i
  br i1 %_25.1.i.i, label %panic.i.i, label %bb13.i.i

bb13.i.i:                                         ; preds = %bb11.i.i
  %_26.i.i = udiv i32 %_19.0.i.i.lcssa, 10
  %_21.i.i = icmp ugt i32 %_25.0.i.i, %_26.i.i
  br i1 %_21.i.i, label %bb42, label %bb15.i.i

panic.i.i:                                        ; preds = %bb11.i.i
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_91eb3d6994bddb8e007fa4843b83f39d) #13, !noalias !603
  unreachable

bb15.i.i:                                         ; preds = %bb13.i.i
  %2 = getelementptr inbounds nuw i8, ptr %cnt.i.i, i64 512
  %_35.i.i = load i32, ptr %2, align 4, !noalias !603, !noundef !136
  %3 = getelementptr inbounds nuw i8, ptr %cnt.i.i, i64 520
  %_36.i.i = load i32, ptr %3, align 4, !noalias !603, !noundef !136
  %_37.0.i.i = add i32 %_36.i.i, %_35.i.i
  %_37.1.i.i = icmp ult i32 %_37.0.i.i, %_35.i.i
  br i1 %_37.1.i.i, label %panic1.i.i, label %bb16.i.i

bb16.i.i:                                         ; preds = %bb15.i.i
  %4 = getelementptr inbounds nuw i8, ptr %cnt.i.i, i64 528
  %_38.i.i = load i32, ptr %4, align 4, !noalias !603, !noundef !136
  %_39.0.i.i = add i32 %_38.i.i, %_37.0.i.i
  %_39.1.i.i = icmp ult i32 %_39.0.i.i, %_37.0.i.i
  br i1 %_39.1.i.i, label %panic2.i.i, label %bb17.i.i

panic1.i.i:                                       ; preds = %bb15.i.i
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_eb2b50487314ee24001af72cb3b23f86) #13, !noalias !603
  unreachable

bb17.i.i:                                         ; preds = %bb16.i.i
  %5 = getelementptr inbounds nuw i8, ptr %cnt.i.i, i64 544
  %_40.i.i = load i32, ptr %5, align 4, !noalias !603, !noundef !136
  %_41.0.i.i = add i32 %_40.i.i, %_39.0.i.i
  %_41.1.i.i = icmp ult i32 %_41.0.i.i, %_39.0.i.i
  br i1 %_41.1.i.i, label %panic3.i.i, label %bb18.i.i

panic2.i.i:                                       ; preds = %bb16.i.i
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_eb2b50487314ee24001af72cb3b23f86) #13, !noalias !603
  unreachable

bb18.i.i:                                         ; preds = %bb17.i.i
  %6 = getelementptr inbounds nuw i8, ptr %cnt.i.i, i64 564
  %_42.i.i = load i32, ptr %6, align 4, !noalias !603, !noundef !136
  %_43.0.i.i = add i32 %_42.i.i, %_41.0.i.i
  %_43.1.i.i = icmp ult i32 %_43.0.i.i, %_41.0.i.i
  br i1 %_43.1.i.i, label %panic4.i.i, label %bb19.i.i

panic3.i.i:                                       ; preds = %bb17.i.i
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_eb2b50487314ee24001af72cb3b23f86) #13, !noalias !603
  unreachable

bb19.i.i:                                         ; preds = %bb18.i.i
  %7 = getelementptr inbounds nuw i8, ptr %cnt.i.i, i64 568
  %_44.i.i = load i32, ptr %7, align 4, !noalias !603, !noundef !136
  %_45.0.i.i = add i32 %_44.i.i, %_43.0.i.i
  %_45.1.i.i = icmp ult i32 %_45.0.i.i, %_43.0.i.i
  br i1 %_45.1.i.i, label %panic5.i.i, label %bb20.i.i

panic4.i.i:                                       ; preds = %bb18.i.i
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_eb2b50487314ee24001af72cb3b23f86) #13, !noalias !603
  unreachable

bb20.i.i:                                         ; preds = %bb19.i.i
  %8 = getelementptr inbounds nuw i8, ptr %cnt.i.i, i64 572
  %_46.i.i = load i32, ptr %8, align 4, !noalias !603, !noundef !136
  %_47.0.i.i = add i32 %_46.i.i, %_45.0.i.i
  %_47.1.i.i = icmp ult i32 %_47.0.i.i, %_45.0.i.i
  br i1 %_47.1.i.i, label %panic6.i.i, label %bb21.i.i

panic5.i.i:                                       ; preds = %bb19.i.i
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_eb2b50487314ee24001af72cb3b23f86) #13, !noalias !603
  unreachable

bb21.i.i:                                         ; preds = %bb20.i.i
  %9 = getelementptr inbounds nuw i8, ptr %cnt.i.i, i64 592
  %_48.i.i = load i32, ptr %9, align 4, !noalias !603, !noundef !136
  %_49.0.i.i = add i32 %_48.i.i, %_47.0.i.i
  %_49.1.i.i = icmp ult i32 %_49.0.i.i, %_47.0.i.i
  br i1 %_49.1.i.i, label %panic7.i.i, label %bb22.i.i

panic6.i.i:                                       ; preds = %bb20.i.i
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_eb2b50487314ee24001af72cb3b23f86) #13, !noalias !603
  unreachable

bb22.i.i:                                         ; preds = %bb21.i.i
  %_5128.i.i = lshr i32 %_19.0.i.i.lcssa, 7
  %_50.i.i = icmp ult i32 %_49.0.i.i, %_5128.i.i
  br i1 %_50.i.i, label %bb42, label %bb25

panic7.i.i:                                       ; preds = %bb21.i.i
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_eb2b50487314ee24001af72cb3b23f86) #13, !noalias !603
  unreachable

bb25.i.i:                                         ; preds = %bb10.i.i
  %10 = getelementptr inbounds nuw i8, ptr %cnt.i.i, i64 232
  %_53.i.i = load i32, ptr %10, align 4, !noalias !603, !noundef !136
  %_54.i.i = udiv i32 %_19.0.i.i.lcssa, 100
  %_52.i.i = icmp ugt i32 %_53.i.i, %_54.i.i
  br i1 %_52.i.i, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse5route.exit.thread48, label %bb11

bb29.i.i:                                         ; preds = %bb10.i.i
  %11 = getelementptr inbounds nuw i8, ptr %cnt.i.i, i64 240
  %_56.i.i = load i32, ptr %11, align 4, !noalias !603, !noundef !136
  %_5727.i.i = lshr i32 %_19.0.i.i.lcssa, 6
  %_55.i.i = icmp ult i32 %_56.i.i, %_5727.i.i
  br i1 %_55.i.i, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse5route.exit.thread35, label %bb44

bb33.i.i:                                         ; preds = %bb10.i.i
  %12 = getelementptr inbounds nuw i8, ptr %cnt.i.i, i64 136
  %_59.i.i = load i32, ptr %12, align 4, !noalias !603, !noundef !136
  %_6026.i.i = lshr i32 %_19.0.i.i.lcssa, 5
  %_58.i.i = icmp ugt i32 %_59.i.i, %_6026.i.i
  br i1 %_58.i.i, label %bb3, label %bb13

bb37.i.i:                                         ; preds = %bb10.i.i
  %_61.i.i = load i32, ptr %cnt.i.i, align 4, !noalias !603, !noundef !136
  %13 = icmp eq i32 %_61.i.i, 0
  br i1 %13, label %bb7, label %bb40.i.i

bb40.i.i:                                         ; preds = %bb37.i.i
  %14 = getelementptr inbounds nuw i8, ptr %cnt.i.i, i64 4
  %_64.i.i = load i32, ptr %14, align 4, !noalias !603, !noundef !136
  %15 = getelementptr inbounds nuw i8, ptr %cnt.i.i, i64 8
  %_65.i.i = load i32, ptr %15, align 4, !noalias !603, !noundef !136
  %_66.0.i.i = add i32 %_65.i.i, %_64.i.i
  %_66.1.i.i = icmp ult i32 %_66.0.i.i, %_64.i.i
  br i1 %_66.1.i.i, label %panic8.i.i, label %bb41.i.i

bb41.i.i:                                         ; preds = %bb40.i.i
  %_67.i.i = udiv i32 %_19.0.i.i.lcssa, 25
  %_62.i.i = icmp ugt i32 %_66.0.i.i, %_67.i.i
  br i1 %_62.i.i, label %bb25, label %bb3

panic8.i.i:                                       ; preds = %bb40.i.i
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_3010709acc5b76127707821c887d6b98) #13, !noalias !603
  unreachable

bb48.i.i:                                         ; preds = %bb10.i.i
  %16 = getelementptr inbounds nuw i8, ptr %cnt.i.i, i64 236
  %_72.i.i = load i32, ptr %16, align 4, !noalias !603, !noundef !136
  %_7325.i.i = lshr i32 %_19.0.i.i.lcssa, 8
  %_71.i.i = icmp ugt i32 %_72.i.i, %_7325.i.i
  br i1 %_71.i.i, label %bb5, label %_RNvNtCs2hd9JHJjR4I_9candidate5parse5route.exit.thread35

bb5.i.i:                                          ; preds = %bb6.i.i, %bb32.i
  %i.sroa.0.038.i.i = phi i64 [ %_20.i.i, %bb6.i.i ], [ 0, %bb32.i ]
  %tot.sroa.0.037.i.i = phi i32 [ %_19.0.i.i, %bb6.i.i ], [ 0, %bb32.i ]
  %17 = getelementptr inbounds nuw i8, ptr %input.0, i64 %i.sroa.0.038.i.i
  %_14.i.i = load i8, ptr %17, align 1, !alias.scope !603, !noundef !136
  %_13.i.i = zext i8 %_14.i.i to i64
  %18 = getelementptr inbounds nuw [4 x i8], ptr %cnt.i.i, i64 %_13.i.i
  %19 = load i32, ptr %18, align 4, !noalias !603, !noundef !136
  %_18.1.i.i = icmp eq i32 %19, -1
  br i1 %_18.1.i.i, label %panic11.i.i, label %bb6.i.i

bb6.i.i:                                          ; preds = %bb5.i.i
  %_18.0.i.i = add nuw i32 %19, 1
  store i32 %_18.0.i.i, ptr %18, align 4, !noalias !603
  %_19.0.i.i = add nuw nsw i32 %tot.sroa.0.037.i.i, 1
  %_20.i.i = add nuw i64 %i.sroa.0.038.i.i, %step.i.i
  %_8.i.i = icmp ult i64 %_20.i.i, %input.1
  %_10.i.i = icmp samesign ult i32 %tot.sroa.0.037.i.i, 4096
  %or.cond.i.i = select i1 %_8.i.i, i1 %_10.i.i, i1 false
  br i1 %or.cond.i.i, label %bb5.i.i, label %bb10.i.i

panic11.i.i:                                      ; preds = %bb5.i.i
; call core::panicking::panic_const::panic_const_add_overflow
  tail call void @_RNvNtNtCsdN1ZzDs28Vk_4core9panicking11panic_const24panic_const_add_overflow(ptr noalias nofree noundef readonly align 8 captures(address, read_provenance) dereferenceable(24) @alloc_65b4bb441eb80f36a586b282f011eeb5) #13, !noalias !603
  unreachable

_RNvNtCs2hd9JHJjR4I_9candidate5parse5route.exit.thread48: ; preds = %bb25.i.i
  call void @llvm.lifetime.end.p0(ptr nonnull %cnt.i.i), !noalias !603
  br label %bb20

_RNvNtCs2hd9JHJjR4I_9candidate5parse5route.exit.thread35: ; preds = %bb48.i.i, %bb29.i.i
  call void @llvm.lifetime.end.p0(ptr nonnull %cnt.i.i), !noalias !603
  br label %bb31

bb3:                                              ; preds = %bb33.i.i, %bb41.i.i
  call void @llvm.lifetime.end.p0(ptr nonnull %cnt.i.i), !noalias !603
; call candidate::parse::p125_row0
  %20 = tail call fastcc noundef i64 @_RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row0(ptr noalias nofree noundef nonnull readonly captures(address, read_provenance) %input.0, i64 noundef %input.1, ptr noalias nofree noundef nonnull align 4 %out.0, i64 noundef %out.1) #14
  br label %bb61

bb61:                                             ; preds = %bb44, %bb45, %bb42, %bb39, %bb37, %bb35, %bb33, %bb31, %bb25, %bb22, %bb20, %bb15, %bb13, %bb11, %bb7, %bb5, %bb3
  %_0.sroa.0.0 = phi i64 [ %input.1, %bb45 ], [ %20, %bb3 ], [ %21, %bb5 ], [ %22, %bb7 ], [ %23, %bb11 ], [ %24, %bb13 ], [ %25, %bb15 ], [ %26, %bb20 ], [ %27, %bb22 ], [ %28, %bb25 ], [ %29, %bb31 ], [ %30, %bb33 ], [ %31, %bb35 ], [ %32, %bb37 ], [ %33, %bb39 ], [ 250000, %bb42 ], [ %34, %bb44 ]
  ret i64 %_0.sroa.0.0

bb5:                                              ; preds = %bb48.i.i
  call void @llvm.lifetime.end.p0(ptr nonnull %cnt.i.i), !noalias !603
; call candidate::parse::p125_row1
  %21 = tail call fastcc noundef i64 @_RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row1(ptr noalias nofree noundef nonnull readonly captures(address, read_provenance) %input.0, ptr noalias nofree noundef nonnull align 4 %out.0, i64 noundef %out.1) #14
  br label %bb61

bb7:                                              ; preds = %bb37.i.i
  call void @llvm.lifetime.end.p0(ptr nonnull %cnt.i.i), !noalias !603
; call candidate::parse::p125_row2
  %22 = tail call fastcc noundef i64 @_RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row2(ptr noalias nofree noundef nonnull readonly captures(address, read_provenance) %input.0, ptr noalias nofree noundef nonnull align 4 %out.0, i64 noundef %out.1) #14
  br label %bb61

bb11:                                             ; preds = %bb10.i.i, %bb25.i.i
  call void @llvm.lifetime.end.p0(ptr nonnull %cnt.i.i), !noalias !603
; call candidate::parse::p125_row3
  %23 = tail call fastcc noundef i64 @_RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row3(ptr noalias nofree noundef nonnull readonly captures(address, read_provenance) %input.0, i64 noundef %input.1, ptr noalias nofree noundef nonnull align 4 %out.0, i64 noundef %out.1) #14
  br label %bb61

bb13:                                             ; preds = %bb33.i.i
  call void @llvm.lifetime.end.p0(ptr nonnull %cnt.i.i), !noalias !603
; call candidate::parse::p125_row4
  %24 = tail call fastcc noundef i64 @_RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row4(ptr noalias nofree noundef nonnull readonly captures(address, read_provenance) %input.0, ptr noalias nofree noundef nonnull align 4 %out.0, i64 noundef %out.1) #14
  br label %bb61

bb15:                                             ; preds = %start
; call candidate::parse::p125_row5
  %25 = tail call fastcc noundef i64 @_RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row5(ptr noalias nofree noundef nonnull readonly captures(address, read_provenance) %input.0, ptr noalias nofree noundef nonnull align 4 %out.0, i64 noundef %out.1) #14
  br label %bb61

bb20:                                             ; preds = %start, %start, %start, %_RNvNtCs2hd9JHJjR4I_9candidate5parse5route.exit.thread48
; call candidate::parse::p125_row6
  %26 = tail call fastcc noundef i64 @_RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row6(ptr noalias nofree noundef nonnull readonly captures(address, read_provenance) %input.0, i64 noundef %input.1, ptr noalias nofree noundef nonnull align 4 %out.0, i64 noundef %out.1) #14
  br label %bb61

bb22:                                             ; preds = %start
; call candidate::parse::p125_row7
  %27 = tail call fastcc noundef i64 @_RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row7(ptr noalias nofree noundef nonnull readonly captures(address, read_provenance) %input.0, ptr noalias nofree noundef nonnull align 4 %out.0, i64 noundef %out.1) #14
  br label %bb61

bb25:                                             ; preds = %bb41.i.i, %bb22.i.i
  call void @llvm.lifetime.end.p0(ptr nonnull %cnt.i.i), !noalias !603
; call candidate::parse::p125_row8
  %28 = tail call fastcc noundef i64 @_RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row8(ptr noalias nofree noundef nonnull readonly captures(address, read_provenance) %input.0, i64 noundef %input.1, ptr noalias nofree noundef nonnull align 4 %out.0, i64 noundef %out.1) #14
  br label %bb61

bb31:                                             ; preds = %start, %start, %start, %_RNvNtCs2hd9JHJjR4I_9candidate5parse5route.exit.thread35
; call candidate::parse::p125_row9
  %29 = tail call fastcc noundef i64 @_RNvNtCs2hd9JHJjR4I_9candidate5parse9p125_row9(ptr noalias nofree noundef nonnull readonly captures(address, read_provenance) %input.0, i64 noundef %input.1, ptr noalias nofree noundef nonnull align 4 %out.0, i64 noundef %out.1) #14
  br label %bb61

bb33:                                             ; preds = %start
; call candidate::parse::p125_row10
  %30 = tail call fastcc noundef i64 @_RNvNtCs2hd9JHJjR4I_9candidate5parse10p125_row10(ptr noalias nofree noundef nonnull readonly captures(address, read_provenance) %input.0, ptr noalias nofree noundef nonnull align 4 %out.0, i64 noundef %out.1) #14
  br label %bb61

bb35:                                             ; preds = %start
; call candidate::parse::p125_row11
  %31 = tail call fastcc noundef i64 @_RNvNtCs2hd9JHJjR4I_9candidate5parse10p125_row11(ptr noalias nofree noundef nonnull readonly captures(address, read_provenance) %input.0, ptr noalias nofree noundef nonnull align 4 %out.0, i64 noundef %out.1) #14
  br label %bb61

bb37:                                             ; preds = %start
; call candidate::parse::p125_row12
  %32 = tail call fastcc noundef i64 @_RNvNtCs2hd9JHJjR4I_9candidate5parse10p125_row12(ptr noalias nofree noundef nonnull readonly captures(address, read_provenance) %input.0, ptr noalias nofree noundef nonnull align 4 %out.0, i64 noundef %out.1) #14
  br label %bb61

bb39:                                             ; preds = %start
; call candidate::parse::p125_row13
  %33 = tail call fastcc noundef i64 @_RNvNtCs2hd9JHJjR4I_9candidate5parse10p125_row13(ptr noalias nofree noundef nonnull readonly captures(address, read_provenance) %input.0, ptr noalias nofree noundef nonnull align 4 %out.0, i64 noundef %out.1) #14
  br label %bb61

bb42:                                             ; preds = %bb22.i.i, %bb13.i.i
  call void @llvm.lifetime.end.p0(ptr nonnull %cnt.i.i), !noalias !603
; call candidate::parse::p125_row14
  tail call fastcc void @_RNvNtCs2hd9JHJjR4I_9candidate5parse10p125_row14(ptr noalias nofree noundef nonnull readonly captures(address, read_provenance) %input.0, ptr noalias nofree noundef nonnull align 4 %out.0, i64 noundef %out.1) #14
  br label %bb61

bb44:                                             ; preds = %bb29.i.i
  call void @llvm.lifetime.end.p0(ptr nonnull %cnt.i.i), !noalias !603
; call candidate::parse::p125_row15
  %34 = tail call fastcc noundef i64 @_RNvNtCs2hd9JHJjR4I_9candidate5parse10p125_row15(ptr noalias nofree noundef nonnull readonly captures(address, read_provenance) %input.0, ptr noalias nofree noundef nonnull align 4 %out.0, i64 noundef %out.1) #14
  br label %bb61

bb45:                                             ; preds = %start, %_RNvNtCs2hd9JHJjR4I_9candidate5parse5route.exit.thread40
; call candidate::parse::fallback
  %35 = tail call fastcc noundef i64 @_RNvNtCs2hd9JHJjR4I_9candidate5parse8fallback(ptr noalias nofree noundef nonnull readonly captures(address, read_provenance) %input.0, i64 noundef %input.1, ptr noalias nofree noundef nonnull align 4 %out.0, i64 noundef %out.1) #14
  br label %bb61
}