namespace ExaLang.Code;

public sealed class CodeBase
{
    public readonly Guid CodeID = Guid.NewGuid();
    public readonly List<StatementBase> Code = new();
    public readonly Dictionary<string, int> Labels = new();

    public void Write(FileInfo bytecodeFile)
    {
        throw new NotImplementedException();
    }

    public void Load(FileInfo bytecodeFile)
    {
        throw new NotImplementedException();
    }
}