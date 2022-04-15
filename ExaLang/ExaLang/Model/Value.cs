namespace ExaLang.Model;

public enum ValueType
{
    Register,
    LiteralNum,
    LiteralStr,
    Mrd,
    Eof
}

public sealed class Value
{
    public readonly ValueType ValueType;
    public readonly string? Arg;
    public object? Obj { get; set; }

    public Value(ValueType valueType, string? arg = null)
    {
        ValueType = valueType;
        Arg = arg;
    }
}