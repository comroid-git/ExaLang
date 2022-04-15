using ExaLang.Antlr;
using ExaLang.Model;

namespace ExaLang.Code;

public sealed class CodeVisitor : ExaLangBaseVisitor<StatementBase>
{
    private readonly ExaRuntime _vm;

    public CodeVisitor(ExaRuntime vm)
    {
        _vm = vm;
    }

    public override StatementControl VisitVStmtControl(ExaLangParser.VStmtControlContext context) => new(context);
    public override StatementUnary VisitVStmtUnary(ExaLangParser.VStmtUnaryContext context) => new(context);
    public override StatementBinary VisitVStmtBinary(ExaLangParser.VStmtBinaryContext context) => new(context);
    public override StatementTrinary VisitVStmtTrinary(ExaLangParser.VStmtTrinaryContext context) => new(context);

    public override StatementBase VisitStmtTestCompare(ExaLangParser.StmtTestCompareContext context)
    {
        throw new NotImplementedException();
    }

    public override StatementBase VisitStmtTestMrd(ExaLangParser.StmtTestMrdContext context)
    {
        throw new NotImplementedException();
    }

    public override StatementBase VisitStmtTestEof(ExaLangParser.StmtTestEofContext context)
    {
        throw new NotImplementedException();
    }
}