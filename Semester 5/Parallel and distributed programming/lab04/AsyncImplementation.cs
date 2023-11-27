using System.Net.Sockets;
using System.Text;

static class AsyncImplementation
{
    // list to store hostnames
    private static List<string> hosts;

    public static void Run(List<string> hostnames)
    {
        // store hostnames in the class variable
        hosts = hostnames;

        // create an array of tasks for each hostname
        var tasks =
          Enumerable.Range(0, hostnames.Count)
          .Select(i => Task.Factory.StartNew(() => StartAsyncClient(hosts[i], i)))
          .ToArray();

        // wait for all tasks to complete
        Task.WaitAll(tasks);
    }

    private static async void StartAsyncClient(string host, int id)
    {
        // create a SocketWrapper instance for the connection
        var wrapper = SocketWrapper.New(host, id);

        // asynchronously connect to the remote endpoint, send an HTTP request, and receive the server's response
        await ConnectAsync(wrapper);
        await SendAsync(wrapper, Parser.RequestString(wrapper.HostName, wrapper.Endpoint));
        await ReceiveAsync(wrapper);

        Console.WriteLine($"Connection {id}: Content length: {Parser.ContentLength(wrapper.Response.ToString())}");

        // shutdown and close the socket
        wrapper.Socket.Shutdown(SocketShutdown.Both);
        wrapper.Socket.Close();
    }

    private static async Task ConnectAsync(SocketWrapper wrapper)
    {
        wrapper.Socket.BeginConnect(wrapper.IPEndpoint, ConnectCallback, wrapper);
        await Task.FromResult(wrapper.ConnectDone.WaitOne());
    }

    private static void ConnectCallback(IAsyncResult result)
    {
        // retrieve information from the asynchronous result
        var wrapper = result.AsyncState as SocketWrapper;
        var socket = wrapper.Socket;
        var id = wrapper.ID;
        var hostname = wrapper.HostName;

        // complete the connection
        socket.EndConnect(result);

        Console.WriteLine($"Connection {id}: Socket connected to {hostname} ({socket.RemoteEndPoint})");

        // signal that the connection is done
        wrapper.ConnectDone.Set();
    }

    private static async Task SendAsync(SocketWrapper wrapper, string data)
    {
        var bytes = Encoding.ASCII.GetBytes(data);

        wrapper.Socket.BeginSend(bytes, 0, bytes.Length, 0, SendCallback, wrapper);
        await Task.FromResult(wrapper.SendDone.WaitOne());
    }

    private static void SendCallback(IAsyncResult result)
    {
        // retrieve information from the asynchronous result
        var wrapper = result.AsyncState as SocketWrapper;
        var socket = wrapper.Socket;
        var id = wrapper.ID;

        // complete the send operation and print a message
        var sent = socket.EndSend(result);

        Console.WriteLine($"Connection {id}: Sent {sent} bytes to server.");

        // signal that the send operation is done
        wrapper.SendDone.Set();
    }

    private static async Task ReceiveAsync(SocketWrapper wrapper)
    {
        wrapper.Socket.BeginReceive(wrapper.Buffer, 0, SocketWrapper.BufferSize, 0, ReceiveCallback, wrapper);
        await Task.FromResult(wrapper.ReceiveDone.WaitOne());
    }

    private static void ReceiveCallback(IAsyncResult result)
    {
        // retrieve information from the asynchronous result
        var wrapper = result.AsyncState as SocketWrapper;
        var socket = wrapper.Socket;

        try
        {
            // complete the receive operation and get the number of bytes read
            var bytes = socket.EndReceive(result);
            wrapper.Response.Append(Encoding.ASCII.GetString(wrapper.Buffer, 0, bytes));

            // check if the full response has been received
            if (!Parser.ReceivedFullResponse(wrapper.Response.ToString()))
                socket.BeginReceive(wrapper.Buffer, 0, SocketWrapper.BufferSize, 0, ReceiveCallback, wrapper);
            else
                wrapper.ReceiveDone.Set();
        }
        catch (Exception e)
        {
            Console.WriteLine(e);
        }
    }
}