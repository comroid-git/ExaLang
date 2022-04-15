namespace ExaLang.Code;

public sealed class CodeBase
{
    public readonly List<StatementBase> Code = new();
    public readonly Dictionary<string, int> Labels = new();
}