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
    public static readonly Value Zero = new(ValueType.LiteralNum) { Obj = 0 };
    public static readonly Value One = new(ValueType.LiteralNum) { Obj = 1 };
    public readonly ValueType ValueType;
    public readonly string? Arg;
    public object? Obj { get; set; }

    public Value(ValueType valueType, string? arg = null, object? obj = null)
    {
        ValueType = valueType;
        Arg = arg;
        Obj = obj;
    }

    public int ToInt(Exa exa) => GetRec(exa, (v, e) => v.ToInt(e));
    public string ToString(Exa exa) => GetRec(exa, (v, e) => v.ToString(e));
    private T GetRec<T>(Exa exa, Func<Value, Exa, T> recFunc) => ValueType == ValueType.Register ? recFunc(exa.Registers[Arg!], exa) : (T)Obj!;
}