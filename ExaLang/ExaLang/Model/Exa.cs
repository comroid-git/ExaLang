using System.Diagnostics;
using System.Globalization;
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
    public DirectoryInfo Directory { get; set; }

    public void Write(FileInfo exaFile)
    {
        using (var writer = new StreamWriter(exaFile.FullName, false))
        using (var stream = new CsvWriter(writer, CultureInfo.InvariantCulture))
        {
        }
    }

    public void Load(FileInfo exaFile)
    {
        throw new NotImplementedException();
    }
}