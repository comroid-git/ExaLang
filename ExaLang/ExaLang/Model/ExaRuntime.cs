using Antlr4.Runtime;
using ExaLang.Antlr;
using ExaLang.Code;

namespace ExaLang.Model;

public sealed class ExaRuntime
{
    public Exa Compile(string code) => Compile(new AntlrInputStream(code));
    public Exa Compile(FileInfo file) => Compile(new AntlrFileStream(file.FullName));

    public Exa Compile(BaseInputCharStream input)
    {
        var lexer = new ExaLangLexer(input);
        var tokens = new CommonTokenStream(lexer);
        var parser = new ExaLangParser(tokens);
        var visitor = new CodeVisitor(this);
        var code = new CodeBase();
        var ctx = parser.file().stmt();
        for (var i = 0; i < ctx.Length; i++)
        {
            var stmt = visitor.Visit(ctx[i]);
            code.Code.Add(stmt);

            if (stmt is StatementUnary { LexerToken: ExaLangLexer.MARK } mark)
                code.Labels[mark.Operand.Arg!] = i;
        }

        return new Exa(code);
    }
}