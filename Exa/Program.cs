namespace Exa;

public static class Program
{
    public static int Main(string[] args)
    {
        switch (args.Length)
        {
            case 0:
                return RunStdio();
            case 1:
                return RunFile(new FileInfo(args[0]));
            default:
                throw new ArgumentOutOfRangeException(nameof(args), args.Length, "Invalid Argument count");
        }
    }

    private static int RunStdio()
    {
        throw new NotImplementedException();
    }

    private static int RunFile(FileInfo fileInfo)
    {
        throw new NotImplementedException();
    }
}