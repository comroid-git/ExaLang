using System.Reflection;
using Antlr4.Runtime;
using ExaLang.Antlr;
using ExaLang.Code;

namespace ExaLang.Model;

public sealed class ExaRuntime
{
    public static readonly DirectoryInfo SdkHome;
    public static readonly FileInfo Executable;
    public static readonly DirectoryInfo TempDir;

    static ExaRuntime()
    {
        SdkHome = new FileInfo(typeof(ExaRuntime).Assembly.Location).Directory!;
        Executable = new(Path.Combine(SdkHome.FullName, Environment.OSVersion.Platform switch
        {
            PlatformID.Win32S or PlatformID.Win32Windows or PlatformID.Win32NT or PlatformID.WinCE => "exa.exe",
            PlatformID.Unix or PlatformID.MacOSX => "exa",
            _ => throw new ArgumentOutOfRangeException(nameof(Environment.OSVersion.Platform), Environment.OSVersion.Platform, "Unsupported Platform")
        }));
        TempDir = new(Path.Combine(Path.GetTempPath(), "exa"));
    }

    public CodeBase Compile(string code) => Compile(new AntlrInputStream(code));
    public CodeBase Compile(FileInfo file) => Compile(new AntlrFileStream(file.FullName));

    public CodeBase Compile(BaseInputCharStream input)
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
        code.Write(BytecodeFile(code.CodeID));
        return code;
    }

    public CodeBase Load(Guid codeId)
    {
        var code = new CodeBase();
        code.Load(BytecodeFile(codeId));
        return code;
    }

    public static FileInfo BytecodeFile(Guid codeId) => new(Path.Combine(TempDir.FullName, $"code-{codeId}.exaCode"));
    public static FileInfo ExaFile(Guid exaId) => new(Path.Combine(TempDir.FullName, $"data-{exaId}.exaData"));
}