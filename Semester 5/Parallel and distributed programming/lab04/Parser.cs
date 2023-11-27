static class Parser
{
    // default http port
    public const int Port = 80;

    // htttp request string
    public static string RequestString(string hostname, string endpoint) =>
      $"GET {endpoint} HTTP/1.1\r\n" +
        $"Host: {hostname}\r\n" +
            $"Content-Length: 0\r\n\r\n";

    // parse the content to find the value of the length header
    public static int ContentLength(string content)
    {
        foreach (string responseLine in content.Split('\r', '\n'))
        {
            var headDetails = responseLine.Split(':');

            if (headDetails[0] == "Content-Length")
                return int.Parse(headDetails[1]);
        }

        throw new Exception("No Content-Length header received");
    }

    // check if a complete http response has been received
    public static bool ReceivedFullResponse(string content) =>
      content.Contains("\r\n\r\n");
}