using ExaLang.Antlr;
using ExaLang.Model;
using ValueType = ExaLang.Model.ValueType;

namespace ExaLang.Code;

public class RegVisitor : ExaLangBaseVisitor<Value>
{
    public override Value VisitVarReg(ExaLangParser.VarRegContext context) => new(ValueType.Register, context.GetText());
    public override Value VisitVarNum(ExaLangParser.VarNumContext context) => new(ValueType.LiteralNum, context.GetText());
    public override Value VisitVarStr(ExaLangParser.VarStrContext context) => new(ValueType.LiteralStr, context.GetText());
}