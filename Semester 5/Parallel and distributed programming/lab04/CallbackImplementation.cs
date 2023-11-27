using System.Net.Sockets;
using System.Text;

static class CallbackImplementation
{
    public static void Run(List<string> hostnames)
    {
        // a CountdownEvent to wait for completion of all connections
        CountdownEvent cde = new(hostnames.Count);

        // start a client for each hostname
        for (var index = 0; index < hostnames.Count; index++)
            StartClient(hostnames[index], index, cde);

        // wait until all connections are completed
        cde.Wait();
    }

    private static void StartClient(string host, int id, CountdownEvent cde)
    {
        // create a SocketWrapper instance for the connection
        var wrapper = SocketWrapper.New(host, id, cde);

        // begin connecting to the remote endpoint asynchronously
        wrapper.Socket.BeginConnect(wrapper.IPEndpoint, Connected, wrapper);
    }

    private static void Connected(IAsyncResult result)
    {
        // retrieve information from the asynchronous result
        var wrapper = result.AsyncState as SocketWrapper;
        var socket = wrapper.Socket;
        var id = wrapper.ID;
        var hostname = wrapper.HostName;

        // complete the connection
        socket.EndConnect(result);

        // print a message indicating successful connection
        Console.WriteLine($"Connection {id}: Socket connected to {hostname} ({socket.RemoteEndPoint})");

        // prepare an HTTP request and begin sending it asynchronously
        var data = Encoding.ASCII.GetBytes(Parser.RequestString(wrapper.HostName, wrapper.Endpoint));
        socket.BeginSend(data, 0, data.Length, 0, Sent, wrapper);
    }

    private static void Sent(IAsyncResult result)
    {
        // retrieve information from the asynchronous result
        var wrapper = result.AsyncState as SocketWrapper;
        var socket = wrapper.Socket;
        var id = wrapper.ID;

        // complete the send operation and print a message
        var sent = socket.EndSend(result);
        Console.WriteLine($"Connection {id}: Sent {sent} bytes to server.");

        // begin receiving data asynchronously
        socket.BeginReceive(wrapper.Buffer, 0, SocketWrapper.BufferSize, 0, Receiving, wrapper);
    }

    private static void Receiving(IAsyncResult result)
    {
        // retrieve information from the asynchronous result
        var wrapper = result.AsyncState as SocketWrapper;
        var socket = wrapper.Socket;

        try
        {
            // complete the receive operation and get the number of bytes read
            var bytesRead = socket.EndReceive(result);

            // append the received data to the response
            wrapper.Response.Append(Encoding.ASCII.GetString(wrapper.Buffer, 0, bytesRead));

            // check if the full response has been received
            if (!Parser.ReceivedFullResponse(wrapper.Response.ToString()))
                // if not, continue receiving asynchronously
                socket.BeginReceive(wrapper.Buffer, 0, SocketWrapper.BufferSize, 0, Receiving, wrapper);
            else
            {
                // if the full response is received, print content length and close the connection
                Console.WriteLine($"Connection {wrapper.ID}: Content length: {Parser.ContentLength(wrapper.Response.ToString())}");

                socket.Shutdown(SocketShutdown.Both);
                socket.Close();

                // write the received content to a file and signal the CountdownEvent
                File.WriteAllText($"Downloads/{wrapper.HostName}.html", wrapper.Response.ToString());
                wrapper.CDE.Signal();
            }
        }
        catch (Exception e)
        {
            // handle exceptions that might occur during receiving
            Console.WriteLine(e);
        }
    }
}