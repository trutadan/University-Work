Directory.CreateDirectory("Downloads");

List<string> hosts = new() {
  "cs.ubbcluj.ro/~rlupsa/edu/pdp",
  "learn.microsoft.com/en-us/dotnet/standard/parallel-programming/task-parallel-library-tpl",
  "reddit.com/r/programare/"
};

Console.WriteLine("Callbacks");
CallbackImplementation.Run(hosts);

Thread.Sleep(2500);

Console.WriteLine("\nTPL");
TaskImplementation.Run(hosts);

Thread.Sleep(2500);

Console.WriteLine("\nTPL Async");
AsyncImplementation.Run(hosts);