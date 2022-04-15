using ExaLang.Code;

namespace ExaLang.Model;

public sealed class Exa
{
    public readonly IDictionary<string, Value> Registers = new Dictionary<string, Value>();
    public readonly CodeBase CodeBase;
    public int CodeIndex;

    public Exa(CodeBase codeBase)
    {
        CodeBase = codeBase;
    }

    public bool Active { get; set; } = true;

    public Value? Execute(ExaRuntime vm)
    {
        Value? yield = null;
        for (CodeIndex = 0; CodeIndex < CodeBase.Code.Count; CodeIndex++)
            CodeBase.Code[CodeIndex].Evaluate(vm, this);
        return yield;
    }
}