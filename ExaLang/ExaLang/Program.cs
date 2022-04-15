using System.Globalization;
using ExaLang.Code;
using ExaLang.Model;

namespace ExaLang;

public static class Program
{
    public static readonly ExaRuntime VM;

    static Program()
    {
        CultureInfo.DefaultThreadCurrentCulture = CultureInfo.InvariantCulture;
        CultureInfo.DefaultThreadCurrentUICulture = CultureInfo.InvariantCulture;
        
        VM = new();
    }

    public static int Main(string[] args)
    {
        switch (args.Length)
        {
            case 0:
                return RunStdio();
            case 1:
                return RunFile(new FileInfo(args[0]));
            case 4:
                return args[2] switch
                {
                    "label" => RunReplLabel(Guid.Parse(args[0]), Guid.Parse(args[1]), args[3]),
                    "index" => RunReplIndex(Guid.Parse(args[0]), Guid.Parse(args[1]), int.Parse(args[3])),
                    _ => throw new Exception("Invalid REPL order: " + args[2])
                };
            default:
                throw new ArgumentOutOfRangeException(nameof(args), args.Length, "Invalid Argument count");
        }
    }

    private static int RunStdio()
    {
        var exa = new Exa(null!);
        int yield = -1;
        while (exa.Active)
        {
            Console.Write(exa.Directory.FullName + " exa> ");
            var input = Console.ReadLine();
            var code = VM.Compile(input!);
            yield = RunCodeBase(exa, code);
        }
        return yield;
    }

    private static int RunFile(FileInfo fileInfo)
    {
        var codeBase = VM.Compile(fileInfo);
        var exa = new Exa(codeBase);
        return RunExa(exa);
    }

    private static int RunReplLabel(Guid codeId, Guid exaId, string codeLabel)
    {
        var codeBase = VM.Load(codeId);
        var exa = new Exa(codeBase) { CodeIndex = codeBase.Labels[codeLabel] };
        exa.Load(ExaRuntime.ExaFile(exaId));
        return RunExa(exa);
    }

    private static int RunReplIndex(Guid codeId, Guid exaId, int codeIndex)
    {
        var codeBase = VM.Load(codeId);
        var exa = new Exa(codeBase) { CodeIndex = codeIndex };
        exa.Load(ExaRuntime.ExaFile(exaId));
        return RunExa(exa);
    }

    private static int RunExa(Exa exa) => RunCodeBase(exa, exa.CodeBase, exa.CodeIndex);
    
    private static int RunCodeBase(Exa exa, CodeBase codeBase, int codeIndex = 0)
    {
        Value? yield = null;
        for (; exa.CodeIndex < exa.CodeBase.Code.Count; exa.CodeIndex++)
            yield = exa.CodeBase.Code[exa.CodeIndex].Evaluate(VM, exa);
        return yield!.ToInt(exa);
    }
}