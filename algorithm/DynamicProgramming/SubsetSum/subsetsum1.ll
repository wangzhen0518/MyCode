; ModuleID = 'subsetsum1.cpp'
source_filename = "subsetsum1.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [4 x i8] c"%4d\00", align 1
@.str.2 = private unnamed_addr constant [30 x i8] c"Found a subset with given sum\00", align 1

; Function Attrs: mustprogress nofree nounwind uwtable
define dso_local zeroext i1 @_Z11isSubsetSumPiii(i32* nocapture readonly %0, i32 %1, i32 %2) local_unnamed_addr #0 {
  %4 = add i32 %1, 1
  %5 = zext i32 %4 to i64
  %6 = add i32 %2, 1
  %7 = zext i32 %6 to i64
  %8 = mul nuw i64 %7, %5
  %9 = alloca i8, i64 %8, align 16
  %10 = icmp slt i32 %1, 0
  br i1 %10, label %28, label %11

11:                                               ; preds = %3
  %12 = add nsw i64 %5, -1
  %13 = and i64 %5, 3
  %14 = icmp ult i64 %12, 3
  br i1 %14, label %17, label %15

15:                                               ; preds = %11
  %16 = and i64 %5, 4294967292
  br label %30

17:                                               ; preds = %30, %11
  %18 = phi i64 [ 0, %11 ], [ %44, %30 ]
  %19 = icmp eq i64 %13, 0
  br i1 %19, label %28, label %20

20:                                               ; preds = %17, %20
  %21 = phi i64 [ %25, %20 ], [ %18, %17 ]
  %22 = phi i64 [ %26, %20 ], [ 0, %17 ]
  %23 = mul nuw nsw i64 %21, %7
  %24 = getelementptr inbounds i8, i8* %9, i64 %23
  store i8 1, i8* %24, align 1, !tbaa !3
  %25 = add nuw nsw i64 %21, 1
  %26 = add i64 %22, 1
  %27 = icmp eq i64 %26, %13
  br i1 %27, label %28, label %20, !llvm.loop !7

28:                                               ; preds = %17, %20, %3
  %29 = icmp slt i32 %2, 1
  br i1 %29, label %61, label %47

30:                                               ; preds = %30, %15
  %31 = phi i64 [ 0, %15 ], [ %44, %30 ]
  %32 = phi i64 [ 0, %15 ], [ %45, %30 ]
  %33 = mul nuw nsw i64 %31, %7
  %34 = getelementptr inbounds i8, i8* %9, i64 %33
  store i8 1, i8* %34, align 4, !tbaa !3
  %35 = or i64 %31, 1
  %36 = mul nuw nsw i64 %35, %7
  %37 = getelementptr inbounds i8, i8* %9, i64 %36
  store i8 1, i8* %37, align 1, !tbaa !3
  %38 = or i64 %31, 2
  %39 = mul nuw nsw i64 %38, %7
  %40 = getelementptr inbounds i8, i8* %9, i64 %39
  store i8 1, i8* %40, align 2, !tbaa !3
  %41 = or i64 %31, 3
  %42 = mul nuw nsw i64 %41, %7
  %43 = getelementptr inbounds i8, i8* %9, i64 %42
  store i8 1, i8* %43, align 1, !tbaa !3
  %44 = add nuw nsw i64 %31, 4
  %45 = add i64 %32, 4
  %46 = icmp eq i64 %45, %16
  br i1 %46, label %17, label %30, !llvm.loop !9

47:                                               ; preds = %28
  %48 = getelementptr inbounds i8, i8* %9, i64 1
  %49 = zext i32 %2 to i64
  call void @llvm.memset.p0i8.i64(i8* nonnull align 1 %48, i8 0, i64 %49, i1 false)
  %50 = icmp slt i32 %1, 1
  br i1 %50, label %61, label %51

51:                                               ; preds = %47, %69
  %52 = phi i64 [ %70, %69 ], [ 1, %47 ]
  %53 = add nsw i64 %52, -1
  %54 = getelementptr inbounds i32, i32* %0, i64 %53
  %55 = mul nuw nsw i64 %53, %7
  %56 = getelementptr inbounds i8, i8* %9, i64 %55
  %57 = mul nuw nsw i64 %52, %7
  %58 = getelementptr inbounds i8, i8* %9, i64 %57
  %59 = load i32, i32* %54, align 4, !tbaa !11
  %60 = sext i32 %59 to i64
  br label %72

61:                                               ; preds = %69, %28, %47
  br i1 %10, label %99, label %62

62:                                               ; preds = %61
  %63 = icmp slt i32 %2, 0
  br i1 %63, label %64, label %95

64:                                               ; preds = %62, %64
  %65 = phi i32 [ %67, %64 ], [ 0, %62 ]
  %66 = tail call i32 @putchar(i32 10)
  %67 = add nuw i32 %65, 1
  %68 = icmp eq i32 %65, %1
  br i1 %68, label %99, label %64, !llvm.loop !13

69:                                               ; preds = %92
  %70 = add nuw nsw i64 %52, 1
  %71 = icmp eq i64 %70, %5
  br i1 %71, label %61, label %51, !llvm.loop !14

72:                                               ; preds = %51, %92
  %73 = phi i64 [ 1, %51 ], [ %93, %92 ]
  %74 = icmp slt i64 %73, %60
  %75 = getelementptr inbounds i8, i8* %56, i64 %73
  %76 = load i8, i8* %75, align 1, !tbaa !3, !range !15
  br i1 %74, label %77, label %79

77:                                               ; preds = %72
  %78 = getelementptr inbounds i8, i8* %58, i64 %73
  store i8 %76, i8* %78, align 1, !tbaa !3
  br label %92

79:                                               ; preds = %72
  %80 = icmp eq i8 %76, 0
  br i1 %80, label %81, label %88

81:                                               ; preds = %79
  %82 = trunc i64 %73 to i32
  %83 = sub nsw i32 %82, %59
  %84 = sext i32 %83 to i64
  %85 = getelementptr inbounds i8, i8* %56, i64 %84
  %86 = load i8, i8* %85, align 1, !tbaa !3, !range !15
  %87 = icmp ne i8 %86, 0
  br label %88

88:                                               ; preds = %81, %79
  %89 = phi i1 [ true, %79 ], [ %87, %81 ]
  %90 = getelementptr inbounds i8, i8* %58, i64 %73
  %91 = zext i1 %89 to i8
  store i8 %91, i8* %90, align 1, !tbaa !3
  br label %92

92:                                               ; preds = %77, %88
  %93 = add nuw nsw i64 %73, 1
  %94 = icmp eq i64 %93, %7
  br i1 %94, label %69, label %72, !llvm.loop !16

95:                                               ; preds = %62, %107
  %96 = phi i64 [ %109, %107 ], [ 0, %62 ]
  %97 = mul nuw nsw i64 %96, %7
  %98 = getelementptr inbounds i8, i8* %9, i64 %97
  br label %111

99:                                               ; preds = %107, %64, %61
  %100 = sext i32 %1 to i64
  %101 = mul nsw i64 %7, %100
  %102 = getelementptr inbounds i8, i8* %9, i64 %101
  %103 = sext i32 %2 to i64
  %104 = getelementptr inbounds i8, i8* %102, i64 %103
  %105 = load i8, i8* %104, align 1, !tbaa !3, !range !15
  %106 = icmp ne i8 %105, 0
  ret i1 %106

107:                                              ; preds = %111
  %108 = tail call i32 @putchar(i32 10)
  %109 = add nuw nsw i64 %96, 1
  %110 = icmp eq i64 %109, %5
  br i1 %110, label %99, label %95, !llvm.loop !13

111:                                              ; preds = %95, %111
  %112 = phi i64 [ 0, %95 ], [ %117, %111 ]
  %113 = getelementptr inbounds i8, i8* %98, i64 %112
  %114 = load i8, i8* %113, align 1, !tbaa !3, !range !15
  %115 = zext i8 %114 to i32
  %116 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 %115)
  %117 = add nuw nsw i64 %112, 1
  %118 = icmp eq i64 %117, %7
  br i1 %118, label %107, label %111, !llvm.loop !17
}

; Function Attrs: mustprogress nofree nosync nounwind willreturn
declare i8* @llvm.stacksave() #1

; Function Attrs: nofree nounwind
declare dso_local noundef i32 @printf(i8* nocapture noundef readonly, ...) local_unnamed_addr #2

; Function Attrs: mustprogress nofree nosync nounwind willreturn
declare void @llvm.stackrestore(i8*) #1

; Function Attrs: mustprogress nofree norecurse nounwind uwtable
define dso_local i32 @main() local_unnamed_addr #3 {
  %1 = tail call i8* @llvm.stacksave()
  %2 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 1) #6
  %3 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %4 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %5 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %6 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %7 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %8 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %9 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %10 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %11 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %12 = tail call i32 @putchar(i32 10) #6
  %13 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 1) #6
  %14 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %15 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %16 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 1) #6
  %17 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %18 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %19 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %20 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %21 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %22 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %23 = tail call i32 @putchar(i32 10) #6
  %24 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 1) #6
  %25 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %26 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %27 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 1) #6
  %28 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %29 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %30 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %31 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %32 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %33 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %34 = tail call i32 @putchar(i32 10) #6
  %35 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 1) #6
  %36 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %37 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %38 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 1) #6
  %39 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 1) #6
  %40 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %41 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %42 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 1) #6
  %43 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %44 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %45 = tail call i32 @putchar(i32 10) #6
  %46 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 1) #6
  %47 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %48 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %49 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 1) #6
  %50 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 1) #6
  %51 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %52 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %53 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 1) #6
  %54 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %55 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %56 = tail call i32 @putchar(i32 10) #6
  %57 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 1) #6
  %58 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %59 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %60 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 1) #6
  %61 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 1) #6
  %62 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 1) #6
  %63 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %64 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 1) #6
  %65 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 1) #6
  %66 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 1) #6
  %67 = tail call i32 @putchar(i32 10) #6
  %68 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 1) #6
  %69 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 0) #6
  %70 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 1) #6
  %71 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 1) #6
  %72 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 1) #6
  %73 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 1) #6
  %74 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 1) #6
  %75 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 1) #6
  %76 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 1) #6
  %77 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 1) #6
  %78 = tail call i32 @putchar(i32 10) #6
  tail call void @llvm.stackrestore(i8* %1)
  %79 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([30 x i8], [30 x i8]* @.str.2, i64 0, i64 0))
  ret i32 0
}

; Function Attrs: nofree nounwind
declare noundef i32 @putchar(i32 noundef) local_unnamed_addr #4

; Function Attrs: argmemonly nofree nounwind willreturn writeonly
declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i1 immarg) #5

attributes #0 = { mustprogress nofree nounwind uwtable "frame-pointer"="none" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { mustprogress nofree nosync nounwind willreturn }
attributes #2 = { nofree nounwind "frame-pointer"="none" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { mustprogress nofree norecurse nounwind uwtable "frame-pointer"="none" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { nofree nounwind }
attributes #5 = { argmemonly nofree nounwind willreturn writeonly }
attributes #6 = { nounwind }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"uwtable", i32 1}
!2 = !{!"Debian clang version 14.0.0-++20211113115108+8ed8d370880b-1~exp1~20211113115638.105"}
!3 = !{!4, !4, i64 0}
!4 = !{!"bool", !5, i64 0}
!5 = !{!"omnipotent char", !6, i64 0}
!6 = !{!"Simple C++ TBAA"}
!7 = distinct !{!7, !8}
!8 = !{!"llvm.loop.unroll.disable"}
!9 = distinct !{!9, !10}
!10 = !{!"llvm.loop.mustprogress"}
!11 = !{!12, !12, i64 0}
!12 = !{!"int", !5, i64 0}
!13 = distinct !{!13, !10}
!14 = distinct !{!14, !10}
!15 = !{i8 0, i8 2}
!16 = distinct !{!16, !10}
!17 = distinct !{!17, !10}
