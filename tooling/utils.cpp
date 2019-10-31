#include "utils.hpp"

struct TypeVisitor : public clang::RecursiveASTVisitor<TypeVisitor> {
  explicit TypeVisitor(clang::ASTContext *context)
      : m_context(context) {}

  bool VisitType(clang::Type *type) {
    m_leaf = type;
    return true;
  }

  clang::ASTContext *m_context;
  clang::Type *m_leaf;
};

clang::QualType GetDesugaredType(clang::ASTContext *ctx, clang::QualType t) {
  auto type = t.split().Ty;

  clang::BuiltinType const *builtin = type->getAs<clang::BuiltinType>();
  if (builtin) {
    return clang::QualType(builtin, 0);
  }

  clang::RecordType const *record = type->getAs<clang::RecordType>();
  if (record) {
    return clang::QualType(record, 0);
  }

  /* Fallback to traversing the type manually. */
  TypeVisitor visitor(ctx);
  visitor.TraverseType(t);
  return clang::QualType(visitor.m_leaf, 0);
}

SmallString<32> GenerateQualifier(clang::ASTContext *ctx, clang::QualType type) {
  clang::Type const *t = type.getTypePtrOrNull();

  /* CV Qualifier: */
  int cvQual = 0;
  if (type.isConstant(*ctx))
    cvQual |= 0x1;

  if (type.isVolatileQualified())
    cvQual |= 0x2;

  /* RefQualifier: */
  int refQual = 0;
  if (t->isLValueReferenceType())
    refQual = 1;

  if (t->isRValueReferenceType())
    refQual = 2;

  /* StorageClass: */
  int storageClass = 0;
  /* TODO: Implement! */

  /* Pointer detection: */
  int isPointer = t->isPointerType();

  /* Array detection: */
  int isArray = t->isArrayType();
  int arrayLen = 0;
  if (isArray) {
    /* TODO: How to handle non-constant arrays? */
    clang::ArrayType const *arr = t->getAsArrayTypeUnsafe();
    if (arr->isConstantSizeType()) {
      assert(arr != nullptr && "arr is null");
      auto carr = (clang::ConstantArrayType const *)arr;
      auto size = carr->getSize();
      arrayLen = *size.getRawData();
    }
  }

  SmallString<32> out;
  raw_svector_ostream os(out);
  os << "Qualifier(" << cvQual << ", " << refQual << ", " << storageClass
     << ", " << isPointer << ", " << isArray << ", " << arrayLen << ")";
  return out;
}

SmallString<8> PrintfFormatForType(clang::ASTContext *ctx, clang::QualType t) {
  clang::QualType desugared = GetDesugaredType(ctx, t);
  clang::Type const *type = desugared.getTypePtrOrNull();
  if (type == nullptr) {
    printf("TODO: TYPE IS NULLPTR\n");
    return SmallString<8>("");
  }

  bool isFundamental = type->isFundamentalType();
  printf("isFundamental: %d\n", isFundamental);
  if (isFundamental) {
    clang::BuiltinType const *builtin = type->getAs<clang::BuiltinType>();
    switch (builtin->getKind()) {
      case clang::BuiltinType::Kind::Bool:
      case clang::BuiltinType::Kind::SChar:
      case clang::BuiltinType::Kind::Short:
      case clang::BuiltinType::Kind::Int:
      return SmallString<8>("%d");
      case clang::BuiltinType::Kind::UChar:
      case clang::BuiltinType::Kind::UShort:
      case clang::BuiltinType::Kind::UInt:
      return SmallString<8>("%u");
      case clang::BuiltinType::Kind::Long:
      return SmallString<8>("%ld");
      case clang::BuiltinType::Kind::ULong:
      return SmallString<8>("%lu");
      case clang::BuiltinType::Kind::LongLong:
      return SmallString<8>("%lld");
      case clang::BuiltinType::Kind::ULongLong:
      return SmallString<8>("%llu");
      case clang::BuiltinType::Kind::Float:
      case clang::BuiltinType::Kind::Double:
      case clang::BuiltinType::Kind::LongDouble:
      return SmallString<8>("%f");
    default:
      break;
    }
  }

  return SmallString<8>("");
}
