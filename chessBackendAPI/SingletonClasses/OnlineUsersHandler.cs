namespace chessBackendAPI
{
    public class OnlineUsersHandler : Singleton<OnlineUsersHandler>
    {
        internal OnlineUsersHandler()
        {
            m_activeUsers = new Dictionary<string, bool>();
        }

        private Dictionary<string, bool> m_activeUsers = null; // <userName, active or not>
    }
}
