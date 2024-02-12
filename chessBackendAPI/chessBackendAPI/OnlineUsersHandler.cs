namespace chessBackendAPI
{
    public class OnlineUsersHandler
    {
        public OnlineUsersHandler getInstane()
        {
            if(s_instance == null)
            {
                s_instance = new OnlineUsersHandler();
            }
            return s_instance;
        }
        
        public bool addActiveUser(string username)
        {
            if (m_activeUsers.ContainsKey(username))
            {
                m_activeUsers.Add(username, true);
                return true;
            }

            return false;
        }

        public bool removeUsers(string userName)
        {
            if(m_activeUsers.ContainsKey(userName))
            {
                m_activeUsers.Remove(userName);
                return true;
            }

            return false;
        }

        private OnlineUsersHandler()
        {
            m_activeUsers = new Dictionary<string, bool>();
        }

        private static OnlineUsersHandler s_instance = null;
        private Dictionary<string, bool> m_activeUsers = null; // <userName, active or not>
    }
}
