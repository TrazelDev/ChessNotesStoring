using ChessMessages;
using Google.Protobuf;
using Microsoft.AspNetCore.SignalR.Client;

namespace chessBackendAPI
{
    public class ServerCommunication
    {
        public static async Task<ServerCommunication> getInstance()
        {
            if(s_instance == null)
            {
                s_instance = new ServerCommunication();
                s_instance.startConnection();
            }

            return s_instance;
        }
        
        
        public async Task<T> sendMsg<T>(byte[] msg, string functionName)
        {
            return await s_connection.InvokeAsync<T>(functionName, msg);
            
        }
        private ServerCommunication()
        {
            s_connection = new HubConnectionBuilder()
               .WithUrl("http://localhost:6162/userHub")
               .Build();
        }

        private async void startConnection()
        {
            // Start the connection
            await s_connection.StartAsync();
        }

        private static ServerCommunication s_instance = null;
        private HubConnection s_connection;
        
    }
}
