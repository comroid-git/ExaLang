using System.Diagnostics;
using ExaLang.Antlr;
using ExaLang.Model;
using ValueType = ExaLang.Model.ValueType;

namespace ExaLang.Code;

public abstract class StatementBase
{
    public readonly int LexerToken;

    protected StatementBase(int lexerToken)
    {
        LexerToken = lexerToken;
    }

    public abstract Value? Evaluate(ExaRuntime vm, Exa exa);

    protected static Process Repl(Exa exa, string order, object orderArg)
    {
        var startInfo = new ProcessStartInfo(ExaRuntime.Executable.FullName)
        {
            Arguments = $"{exa.CodeBase.CodeID} {order} {orderArg}",
            WorkingDirectory = exa.Directory.FullName,
            RedirectStandardOutput = true,
            RedirectStandardInput = true,
            RedirectStandardError = true,
            CreateNoWindow = true
        };
        return Process.Start(startInfo) ?? throw new Exception("Could not REPL");
    }
}

public sealed class StatementControl : StatementBase
{
    public StatementControl(ExaLangParser.VStmtControlContext ctx) : base(ctx.Start.TokenIndex)
    {
    }

    public override Value? Evaluate(ExaRuntime vm, Exa exa)
    {
        switch (LexerToken)
        {
            case ExaLangLexer.HALT:
                exa.Active = false;
                break;
            case ExaLangLexer.KILL:
                throw new NotImplementedException();
            case ExaLangLexer.REPL:
                Repl(exa, "index", exa.CodeIndex);
                break;
            case ExaLangLexer.MODE:
                throw new NotImplementedException();
            case ExaLangLexer.MAKE:
                throw new NotImplementedException();
            case ExaLangLexer.WIPE:
                throw new NotImplementedException();
            case ExaLangLexer.NOOP:
                break;
            default:
                throw new ArgumentOutOfRangeException(nameof(LexerToken), LexerToken, "Invalid control Statement: " + ExaLangLexer.ruleNames[LexerToken - 1]);
        }

        return null;
    }
}

public sealed class StatementUnary : StatementBase
{
    public readonly Value Operand;
    
    public StatementUnary(ExaLangParser.VStmtUnaryContext ctx) : base(ctx.Start.TokenIndex)
    {
        Operand = new RegVisitor().Visit(ctx.var());
    }

    public override Value? Evaluate(ExaRuntime vm, Exa exa)
    {
        switch (LexerToken)
        {
            case ExaLangLexer.MARK:
                break;
            case ExaLangLexer.JUMP:
                exa.CodeIndex = exa.CodeBase.Labels[Operand.Arg!];
                break;
            case ExaLangLexer.TJMP:
                if (exa.Registers["T"] is { ValueType: ValueType.LiteralNum, Obj: > 0 })
                {
                    exa.CodeIndex = exa.CodeBase.Labels[Operand.Arg!];
                    return Value.One;
                }
                break;
            case ExaLangLexer.FJMP:
                if (exa.Registers["T"] is { ValueType: ValueType.LiteralNum, Obj: <= 0 })
                {
                    exa.CodeIndex = exa.CodeBase.Labels[Operand.Arg!];
                    return Value.One;
                }
                break;
            case ExaLangLexer.DROP:
                throw new NotImplementedException();
            case ExaLangLexer.REPL:
                Repl(exa, "label", Operand.ToString(exa));
                break;
            case ExaLangLexer.LINK:
                if (Operand is { ValueType: ValueType.LiteralNum, Obj: -1 })
                    exa.Directory = exa.Directory.Parent ?? throw new Exception("Could not LINK into parent directory");
                else exa.Directory = new DirectoryInfo(Path.Combine(exa.Directory.FullName, Operand.ToString(exa)));
                break;
            case ExaLangLexer.HOST:
                return new Value(ValueType.LiteralStr, obj: exa.Directory);
            case ExaLangLexer.VOID:
                throw new NotImplementedException();
            case ExaLangLexer.GRAB:
                throw new NotImplementedException();
            case ExaLangLexer.FILE:
                throw new NotImplementedException();
            case ExaLangLexer.SEEK:
                throw new NotImplementedException();
            default:
                throw new ArgumentOutOfRangeException(nameof(LexerToken), LexerToken, "Invalid unary Statement: " + ExaLangLexer.ruleNames[LexerToken - 1]);
        }

        return null;
    }
}

public sealed class StatementBinary : StatementBase
{
    public readonly Value OperandLeft;
    public readonly Value OperandRight;
    
    public StatementBinary(ExaLangParser.VStmtBinaryContext ctx) : base(ctx.Start.TokenIndex)
    {
        OperandLeft = new RegVisitor().Visit(ctx.var(0));
        OperandRight = new RegVisitor().Visit(ctx.var(1));
    }

    public override Value? Evaluate(ExaRuntime vm, Exa exa)
    {
        switch (LexerToken)
        {
            case ExaLangLexer.COPY:
                throw new NotImplementedException();
            default:
                throw new ArgumentOutOfRangeException(nameof(LexerToken), LexerToken, "Invalid binary Statement: " + ExaLangLexer.ruleNames[LexerToken - 1]);
        }

        return null;
    }
}

public sealed class StatementTrinary : StatementBase
{
    public readonly Value OperandLeft;
    public readonly Value OperandRight;
    public readonly Value OperandOutput;

    public StatementTrinary(ExaLangParser.VStmtTrinaryContext ctx) : base(ctx.Start.TokenIndex)
    {
        OperandLeft = new RegVisitor().Visit(ctx.var(0));
        OperandRight = new RegVisitor().Visit(ctx.var(1));
        OperandOutput = new RegVisitor().Visit(ctx.var(2));
    }

    public override Value? Evaluate(ExaRuntime vm, Exa exa)
    {
        switch (LexerToken)
        {
            case ExaLangLexer.SWIZ:
                throw new NotImplementedException();
            case ExaLangLexer.RAND:
                throw new NotImplementedException();
            case ExaLangLexer.ADDI:
                throw new NotImplementedException();
            case ExaLangLexer.SUBI:
                throw new NotImplementedException();
            case ExaLangLexer.MULI:
                throw new NotImplementedException();
            case ExaLangLexer.DIVI:
                throw new NotImplementedException();
            case ExaLangLexer.MODI:
                throw new NotImplementedException();
            default:
                throw new ArgumentOutOfRangeException(nameof(LexerToken), LexerToken, "Invalid trinary Statement: " + ExaLangLexer.ruleNames[LexerToken - 1]);
        }

        return null;
    }
}
